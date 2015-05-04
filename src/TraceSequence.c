#include "TraceSequence.h"

/*#include <map>
#include <list>*/
#include "list.h"
#include <stdbool.h>
#include "ModelTrace.h"
/*#include <sstream>
#include <microframework/api/json/Lexer.h>
#include <stdlib.h>
using std::string;
using std::list;*/

/**
 * Author: fco.ja.ac@gmail.com
 * Date: 24/10/13
 * Time: 18:36
 */

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

TraceSequence *new_TraceSequence()
{
	TraceSequence *pTraceSeqObj = (TraceSequence*)malloc(sizeof(TraceSequence));

	if (pTraceSeqObj == NULL)
	{
		return NULL;
	}

	/*pTraceSeqObj->traces_list = NULL;*/
	pTraceSeqObj->traces_list = NULL;
	/*list_init(pTraceSeqObj->traces_list);*/
	LIST_STRUCT_INIT(pTraceSeqObj, traces_list);
	pTraceSeqObj->append = TraceSequence_append;
	pTraceSeqObj->populate = TraceSequence_populate;
	pTraceSeqObj->toString = TraceSequence_toString;
	pTraceSeqObj->delete = delete_TraceSequence;

	return pTraceSeqObj;
}

void delete_TraceSequence(void *const this)
{
	if(this != NULL)
	{
		int i;
		int length;
		TraceSequence *ts = this;

		length = list_length(ts->traces_list);

		for (i = 0; i < length; ++i) {
			list_chop(ts->traces_list);
		}

		free(this);
	}
}

void TraceSequence_append(TraceSequence *const this, TraceSequence *seq)
{
	int i, appLength;

	appLength = list_length(seq->traces_list);

	for (i = 0; i < appLength; ++i) {
		void *temp = list_pop(seq->traces_list);
		list_add(this->traces_list, temp);
	}

	seq->delete(seq);
	seq = NULL;
}

TraceSequence *TraceSequence_populate(TraceSequence *const this, list_t addTraces)
{
	int i, addLength;

	addLength = list_length(addTraces);

	for (i = 0; i < addLength; ++i) {
		void *temp = list_pop(addTraces);
		list_add(this->traces_list, temp);
	}

	PRINTF("TraceSequence populated!\n");

	return this;
}

char *TraceSequence_toString(TraceSequence *const this)
{
	char *sequences;
	/*memset(&sequences[0], 0, sizeof(sequences));*/
	bool isFirst = true;
	int i, listLength;

	ModelTrace *mt;

	PRINTF("Creating string traces!\n");

	listLength = list_length(this->traces_list);
	sequences = malloc(strlen("[]"));
	sprintf(sequences, "[");

	for (i = 0; i < listLength; ++i) {
		if (!isFirst) {
			mt = list_item_next(mt);
			sequences = realloc(sequences, strlen(sequences) +
					strlen(",") +
					strlen(mt->ToString(mt->pDerivedObj)) + 1);
			sprintf(sequences, "%s,%s", sequences, mt->ToString(mt->pDerivedObj));
			/*PRINTF("%s", sequences);*/
		}
		else
		{
			mt = list_head(this->traces_list);
			sequences = realloc(sequences, strlen(sequences) +
					strlen(mt->ToString(mt->pDerivedObj)) + 1);
			sprintf(sequences, "%s%s", sequences, mt->ToString(mt->pDerivedObj));
			/*PRINTF("%s", sequences);*/
			isFirst = false;
		}
	}

	sprintf(sequences, "%s]", sequences);

	return sequences;
}

/*
string TraceSequence::exportToString(){
	string buffer;
	buffer.append("[");
	bool isFirst = true;
	for (std::list<ModelTrace*>::const_iterator iterator = traces.begin(), end = traces.end(); iterator != end; ++iterator)
	{
		if(!isFirst){
			buffer.append(",");
		}
		ModelTrace *t = *iterator;
		buffer.append(t->toString());
		isFirst = false;
	}
	buffer.append("]");
	return buffer;
}


TraceSequence::TraceSequence(){

}

TraceSequence::~TraceSequence(){
	for (std::list<ModelTrace*>::iterator iterator = traces.begin(), end = traces.end(); iterator != end; ++iterator)
	{
		delete *iterator;
	}
	traces.clear();
}


TraceSequence* TraceSequence::populate(std::list<ModelTrace*> *addtraces)
{
	std::copy(addtraces->begin(), addtraces->end(), std::back_insert_iterator<std::list<ModelTrace*> >(traces)); // addAll
	delete addtraces;
	return this;
}


void TraceSequence::append(TraceSequence *seq){
	std::copy(seq->traces.begin(), seq->traces.end(), std::back_insert_iterator<std::list<ModelTrace*> >(traces)); // addAll
}



TraceSequence* TraceSequence::populateFromString(string addtracesTxt){
	std::istringstream ss( addtracesTxt); // convert string to istream
	return populateFromStream(ss);
}


TraceSequence* TraceSequence::populateFromStream(istream &inputStream )
{
	Lexer *lexer= new Lexer(inputStream);
	Token currentToken = lexer->nextToken();

	if(currentToken.tokenType != LEFT_BRACKET)
	{
		throw KevoreeException("TraceSequence::populateFromStream Bad Format : expect [");
	}

	currentToken = lexer->nextToken();

	std::map<string, string> keys;
	string previousName;
	ModelTrace *modeltrace;

	while (currentToken.tokenType != END_OF_FILE && currentToken.tokenType != RIGHT_BRACKET) {

		if(currentToken.tokenType == LEFT_BRACE){
			keys.clear();
		}

		if(currentToken.tokenType == VALUE){
			if(!previousName.empty()){
				keys[previousName] = currentToken.value;
				previousName.clear();
			}   else {
				previousName = currentToken.value;
			}
		}

		if(currentToken.tokenType == RIGHT_BRACE){

			if(keys.find("traceType") != keys.end()){

				string traceType = keys["traceType"];
				string _src = "";
				string _refname = "";
				string _objpath = "";
				string _content = "";
				string _typename = "";
				string _previouspath = "";
				list < string > _l_previousPath;
				list < string > _l_typeName;

				switch(atoi(traceType.c_str())){

				case SET:

					if(keys.find("src") != keys.end()){
						_src =keys["src"];
					}
					if(keys.find("refname") != keys.end()){
						_refname =keys["refname"];
					}
					if(keys.find("objpath") != keys.end()){
						_objpath =keys["objpath"];
					}
					if(keys.find("content") != keys.end()){
						_content =keys["content"];
					}
					if(keys.find("typename") != keys.end()){
						_typename =keys["typename"];
					}

					modeltrace = new ModelSetTrace(_src,_refname,_objpath,_content,_typename);

					traces.push_back(modeltrace);

					break;

				case ADD:
					if(keys.find("src") != keys.end()){
						_src =keys["src"];
					}
					if(keys.find("refname") != keys.end()){
						_refname =keys["refname"];
					}
					if(keys.find("previouspath") != keys.end()){
						_previouspath =keys["previouspath"];
					}

					if(keys.find("typename") != keys.end()){
						_typename =keys["typename"];
					}
					modeltrace =new ModelAddTrace(_src,_refname,_previouspath,_typename);
					traces.push_back(modeltrace);
					break;

				case REMOVE:

					if(keys.find("src") != keys.end()){
						_src =keys["src"];
					}
					if(keys.find("refname") != keys.end()){
						_refname =keys["refname"];
					}
					if(keys.find("objpath") != keys.end()){
						_objpath =keys["objpath"];
					}
					modeltrace= new ModelRemoveTrace(_src,_refname,_objpath);
					traces.push_back(modeltrace);
					break;

				case ADD_ALL:
					cout << "TODO ADD_ALL !!!" <<endl;
					break;

				case REMOVE_ALL:
					cout << "TODO REMOVE_ALL !!!" <<endl;

					break;

				case RENEW_INDEX:
					cout << "TODO RENEW_INDEX !!!" <<endl;
					break;

				default :
					cout << "TRACE LOST !!!" <<endl;
					break;
				}
			}
		}
		currentToken = lexer->nextToken();
	}
	delete lexer;

	return this;
}


string TraceSequence::toString()  {
	return exportToString();
}

void TraceSequence::reverse(){
	traces.reverse();
}
 */
