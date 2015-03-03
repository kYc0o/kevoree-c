/*#include "DefaultFactorykevoree.h"
#include "Comparekevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "kevoree.h"

#include "list.h"
#include "jsonparse.h"

#define MAX_NUMBER 6

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

ContainerRoot *current_model = NULL;
ContainerRoot *new_model = NULL;
Visitor *visitor_print;
LIST(model_traces);


char buffer[100];

void write_to_file(char *buf)
{
	FILE *current_model_json;

	current_model_json = fopen("current_model.json", "a");

	if(current_model_json)
	{
		fprintf(current_model_json, "%s", buf);
		if(fclose(current_model_json)) {
			printf("ERROR: cannot close the file!\n");
		}
	}
	else
	{
		printf("ERROR: could not write to memory\n");
	}
}

void actionstore(char *path, Type type, void *value)
{
	switch(type)
	{
	case STRING:
		sprintf(buffer, "\"%s\" : \"%s\"", path, (char*)value);
		write_to_file(buffer);
		break;

	case STRREF:
		sprintf(buffer, "\"%s\"", path);
		write_to_file(buffer);
		break;

	case BOOL:
		sprintf(buffer, "\"%s\" : \"%d\"", path, (bool)value);
		write_to_file(buffer);
		break;

	case INTEGER:
		sprintf(buffer, "\"%s\" : \"%d\"", path, (int)value);
		write_to_file(buffer);
		break;

	case BRACKET:
		sprintf(buffer, "{\n");
		write_to_file(buffer);
		break;

	case SQBRACKET:
		sprintf(buffer, "\"%s\" : [\n", path);
		write_to_file(buffer);
		break;

	case CLOSEBRACKET:
		sprintf(buffer, "}\n");
		write_to_file(buffer);
		break;

	case CLOSESQBRACKET:
		sprintf(buffer, "]\n");
		write_to_file(buffer);
		break;

	case CLOSEBRACKETCOLON:
		sprintf(buffer, "},\n");
		write_to_file(buffer);
		break;

	case CLOSESQBRACKETCOLON:
		sprintf(buffer, "],\n");
		write_to_file(buffer);
		break;

	case COLON:
		sprintf(buffer, ",\n");
		write_to_file(buffer);
		break;

	case RETURN:
		sprintf(buffer, "\n");
		write_to_file(buffer);
		break;
	}
}

void actionprintf(char *path, Type type, void* value)
{
	switch(type)
	{
	case STRING:
		printf("\"%s\" : \"%s\"", path, (char*)value);
		break;

	case STRREF:
		printf("\"%s\"", path);
		break;

	case BOOL:
	case INTEGER:
		printf("\"%s\" : \"%d\"", path, (int)value);
		break;

	case BRACKET:
		printf("{\n");
		break;

	case SQBRACKET:
		printf("\"%s\" : [\n", path);
		break;

	case CLOSEBRACKET:
		printf("}\n");
		break;

	case CLOSESQBRACKET:
		printf("]\n");
		break;

	case CLOSEBRACKETCOLON:
		printf("},\n");
		break;

	case CLOSESQBRACKETCOLON:
		printf("],\n");
		break;

	case COLON:
		printf(",\n");
		break;

	case RETURN:
		printf("\n");
		break;
	}
}

void actionprintpath(char *path, Type type, void *value)
{
	switch(type)
	{
	case STRING:
	case REFERENCE:
		printf("path = %s  value = %s\n",path,(char*)value);
		break;

	case BOOL:
	case INTEGER:
		printf("path = %s  value = %d\n", path, (int)value);
		break;

	case STRREF:
	case BRACKET:
	case SQBRACKET:
	case CLOSEBRACKET:
	case CLOSESQBRACKET:
	case CLOSEBRACKETCOLON:
	case CLOSESQBRACKETCOLON:
	case COLON:
	case RETURN:
		printf("No valid type!\n");
		break;
	}
}

void actionUpdateDelete(char* _path, Type type, void* value)
{
	char *__path = strdup(_path);
	char path[250];
	char *path2 = strdup(_path);
	char *path3 = NULL;
	char *refname = NULL;
	char *src = NULL;
	KMFContainer *container;
	/*
	 * TODO return if memory is full
	 */


	if ((refname = strtok(path2, "\\")) != NULL) {
		if ((refname = strtok(NULL, "\\")) == NULL) {
			refname = strtok(path2, "\\");
		}
	}

	strcpy(path, strtok(__path, "\\"));

	if (!strcmp("generated_KMF_ID", path)) {
		strcpy(path, "");
	}

	if ((container = new_model->FindByPath(path, new_model)) != NULL) {
		if ((src = strdup(path)) != NULL) {
		} else {
			PRINTF("ERROR: not enough memory for src!\n");
		}
		/*typeName = strdup(container->metaClassName(container));*/
	}

	switch(type)
	{
	case REFERENCE:
		if (container == NULL) {
			if ((container = (KMFContainer*)current_model->FindByPath(path, current_model)) != NULL) {
				if ((src = strdup(path)) != NULL) {
				} else {
					PRINTF("ERROR: not enough memory for src!\n");
				}
			} else {
				PRINTF("ERROR: Cannot retrieve source!\n");
				src = malloc(1);
				strcpy(src, "");
			}

			ModelTrace *mt = newPoly_ModelRemoveTrace(src, refname, path);

			if (mt != NULL)	{
				list_add(model_traces, mt);
			} else {
				printf("ERROR: ModelTrace cannot be added!\n");
				printf("path = %s  value = %s\n", path, (char*)value);
			}
		}
		break;

	case STRING:
		if (container == NULL) {
			/*
			 * TODO check NULL
			 */
			if ((container = (KMFContainer*)current_model->FindByPath(path, current_model)) != NULL) {
				if ((src = strdup(container->eContainer)) != NULL) {
				} else {
					PRINTF("ERROR: not enough memory for src!\n");
				}
			} else {
				PRINTF("ERROR: Cannot retrieve source!\n");
				src = malloc(1);
				strcpy(src, "");
			}
			/*printf("path = %s  value = %s\n", path, (char*)value);
			printf("Path %s does not exist in new_model, removing...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelRemoveTrace(src, refname, path);
			/*char *strTrace = mt->ToString(mt->pDerivedObj);
				PRINTF(strTrace);
			free(strTrace);*/
			if (mt != NULL)	{
				list_add(model_traces, mt);
			} else {
				printf("ERROR: ModelTrace cannot be added!\n");
				printf("path = %s  value = %s\n", path, (char*)value);
			}
		} else {
			/*printf("path = %s  value = %s\n", _path, (char*)value);*/
			char* string = current_model->FindByPath(_path, current_model);
			char* string2 = new_model->FindByPath(_path, new_model);
			/*printf("Current attribute value: %s\n", string);
			printf("New attribute value: %s\n", string2);*/
			if(string != NULL && string2 != NULL)
			{
				if(!strcmp(string2, string))
				{
					/*printf("Identical attributes, nothing to change...\n\n");*/
				}
				else
				{
					/*printf("Changing attribute to %s in current_model\n\n", string2);*/
					ModelTrace *mt = newPoly_ModelSetTrace(src, refname, string2);
					/*char *strTrace = mt->ToString(mt->pDerivedObj);
						PRINTF(strTrace);
						free(strTrace);*/
					if(mt != NULL)
					{
						list_add(model_traces, mt);
					}
					else {
						printf("ERROR: ModelTrace cannot be added!\n");
						printf("path = %s  value = %s\n", path, (char*)value);
					}
				}
			}
			else if(string == NULL && string2 != NULL)
			{
				/*printf("Current attribute is NULL, changing to new attribute '%s'\n\n", string2);*/
				ModelTrace *mt = newPoly_ModelSetTrace(src, refname, string2);
				/*
					char *strTrace = mt->ToString(mt->pDerivedObj);
					PRINTF(strTrace);
					free(strTrace);
				 */
				if(mt != NULL)
				{
					list_add(model_traces, mt);
				}
				else {
					printf("ERROR: ModelTrace cannot be added!\n");
					printf("path = %s  value = %s\n", path, (char*)value);
				}
			}
			else if(string != NULL && string2 == NULL)
			{
				/*printf("Changing attribute to NULL\n\n");*/
				ModelTrace *mt = newPoly_ModelSetTrace(src, refname, "");
				/*char *strTrace = mt->ToString(mt->pDerivedObj);
					PRINTF(strTrace);
					free(strTrace);*/
				if(mt != NULL)
				{
					list_add(model_traces, mt);
				}
				else {
					printf("ERROR: ModelTrace cannot be added!\n");
					printf("path = %s  value = %s\n", path, (char*)value);
				}	printf("path = %s  value = %s\n", path, (char*)value);
			}
		}
		break;

	case BOOL:
	case INTEGER:
		if(container == NULL)/*new_model->FindByPath(path, new_model) == NULL)*/
		{
			/*
			 * TODO check NULL
			 */
			container = (KMFContainer*)current_model->FindByPath(path, current_model);
			src = strdup(container->eContainer);
			PRINTF("src: %s\n", src);
			/*printf("path = %s  value = %d\n", path, (int)value);
			printf("Path %s does not exist in new_model, removing...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelRemoveTrace(src, refname, path);
			/*char *strTrace = mt->ToString(mt->pDerivedObj);
				PRINTF(strTrace);
				free(strTrace);*/
			if(mt != NULL)
			{
				list_add(model_traces, mt);
			}
			else {
				printf("ERROR: ModelTrace cannot be added!\n");
				printf("path = %s  value = %s\n", path, (char*)value);
			}
		}
		else
		{
			/*printf("path = %s  value = %d\n", _path, (int)value);*/
			int v = (int)(current_model->FindByPath(_path, current_model));
			int v2 = (int)(new_model->FindByPath(_path, new_model));
			char v2str[MAX_NUMBER] = {0};
			/*printf("Current attribute value: %d\n", v);
			printf("New attribute value: %d\n", v2);*/
			if(v == v2)
			{
				/*printf("Identical attributes, nothing to change...\n\n");*/
			}
			else
			{
				/*printf("Changing attribute to %d in current_model\n\n", v2);*/
				sprintf(v2str, "%d", v2);
				ModelTrace *mt = newPoly_ModelSetTrace(src, refname, v2str);
				/*char *strTrace = mt->ToString(mt->pDerivedObj);
					PRINTF(strTrace);
					free(strTrace);*/
				if(mt != NULL)
				{
					list_add(model_traces, mt);
				}
				else {
					printf("ERROR: ModelTrace cannot be added!\n");
					printf("path = %s  value = %s\n", path, (char*)value);
				}
			}
		}
		break;

	case STRREF:
	case BRACKET:
	case SQBRACKET:
	case CLOSEBRACKET:
	case CLOSESQBRACKET:
	case CLOSEBRACKETCOLON:
	case CLOSESQBRACKETCOLON:
	case COLON:
	case RETURN:
		printf("Type non valid!\n");
		break;
	}

	free(__path);
	free(path2);
	if (src != NULL) {
		free(src);
	}
}

void actionAdd(char* _path, Type type, void* value)
{
	char *__path = strdup(_path);
	char path[250];
	char *path2 = strdup(_path);
	char *refname = NULL;
	char *src = NULL;
	char *typename = NULL;
	KMFContainer *container;
	/*
	 * TODO return if memory is full
	 */
	if ((refname = strtok(path2, "\\")) != NULL) {
		if ((refname = strtok(NULL, "\\")) == NULL) {
			refname = strtok(path2, "\\");
		}
	}

	strcpy(path, strtok(__path, "\\"));

	if (!strcmp("generated_KMF_ID", path)) {
		strcpy(path, "");
	}
	/*if ((container = current_model->FindByPath(path, current_model)) != NULL) {
		if ((src = strdup(path)) != NULL) {
		} else {
			PRINTF("ERROR: not enough memory for src!\n");
		}
		typename = strdup(container->metaClassName(container));
	} else {
		PRINTF("INFO: adding %s\n", path);
	}*/

	switch(type)
	{
	case STRING:
		/*printf("path = %s  value = %s\n", path, (char*)value);*/
		/*path = strtok(path, "\\");*/
		container = current_model->FindByPath(path, current_model);
		if(container == NULL)
		{
			if ((container = (KMFContainer*)new_model->FindByPath(path, new_model)) != NULL) {
				if ((src = strdup(container->eContainer)) != NULL) {
					typename = strdup(container->metaClassName(container));
				} else {
					PRINTF("ERROR: not enough memory for src!\n");
				}
			} else {
				PRINTF("ERROR: Cannot retrieve source!\n");
			}
			/*printf("Path %s does not exist in curent_model, adding...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelAddTrace(src, refname, path, typename);
			/*char *strTrace = mt->ToString(mt->pDerivedObj);
				PRINTF(strTrace);
				free(strTrace);*/
			if(mt != NULL)
			{
				list_add(model_traces, mt);
			}
			else {
				printf("ERROR: ModelTrace cannot be added!\n");
				printf("path = %s  value = %s\n", path, (char*)value);
			}
		}
		else
		{
			/*printf("Path %s already exists...\n", path);*/
		}
		break;

	case BOOL:
	case INTEGER:
		/*printf("path = %s  value = %d\n", path, (int)value);*/
		/*path = strtok(path, "\\");*/
		if((int)(current_model->FindByPath(path, current_model)) == -1)
		{
			/*printf("Path %s does not exist in current_model, adding...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelAddTrace(path, (char*)value, path, "INT");
			/*char *strTrace = mt->ToString(mt->pDerivedObj);
				PRINTF(strTrace);
				free(strTrace);*/
			if(mt != NULL)
			{
				list_add(model_traces, mt);
			}
			else {
				printf("ERROR: ModelTrace cannot be added!\n");
				printf("path = %s  value = %s\n", path, (char*)value);
			}
		}
		else
		{
			/*printf("Path %s already exists...\n", path);*/
		}
		break;

	case STRREF:
	case BRACKET:
	case SQBRACKET:
	case CLOSEBRACKET:
	case CLOSESQBRACKET:
	case CLOSEBRACKETCOLON:
	case CLOSESQBRACKETCOLON:
	case COLON:
	case RETURN:
		printf("Type non valid!\n");
		break;
	}

	free(__path);
	free(path2);
	if (src != NULL) {
		free(src);
	}
	if (typename != NULL) {
		free(typename);
	}
}

/*KevoreeBootStrap *kb=NULL;*/

int main(void)
{
	printf("Starting kevoree C implementation\n");

	current_model = new_ContainerRoot();

	/* ContainerNode contikiNode */
	ContainerNode* contikiNode = new_ContainerNode();
	contikiNode->super->super->name = malloc(sizeof(char) * (strlen("nodeX")) + 1);
	sprintf(contikiNode->super->super->name, "node0");
	contikiNode->super->started = true;
	contikiNode->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNode->super->metaData, "");

	current_model->AddNodes(current_model, contikiNode);

	/* NetworkInfo ip */
	NetworkInfo* serverNodeIP = new_NetworkInfo();
	serverNodeIP->super->name = malloc(sizeof(char) * (strlen("ip")) + 1);
	strcpy(serverNodeIP->super->name, "ip");

	contikiNode->AddNetworkInformation(contikiNode, serverNodeIP);
	/* NeworkProperty front
		NetworkProperty* contikiNodeFront = new_NetworkProperty();
		contikiNodeFront->super->name = malloc(sizeof(char) * (strlen("front")) + 1);
		strcpy(contikiNodeFront->super->name, "front");
		contikiNodeFront->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
		strcpy(contikiNodeFront->value, "contiki.kevoree.org");*/

	/* NeworkProperty local
		NetworkProperty* contikiNodeLocal = new_NetworkProperty();
		contikiNodeLocal->super->name = malloc(sizeof(char) * (strlen("local")) + 1);
		strcpy(contikiNodeLocal->super->name, "local");
		contikiNodeLocal->value = malloc(sizeof(char) * (strlen("aaaa::0:0:3")) + 1);
		strcpy(contikiNodeLocal->value, "aaaa::0:0:3");*/

	/* NeworkProperty front */
	NetworkProperty* serverNodeFront = new_NetworkProperty();
	serverNodeFront->super->name = malloc(sizeof(char) * (strlen("front")) + 1);
	strcpy(serverNodeFront->super->name, "front");
	serverNodeFront->value = malloc(sizeof(char) * (strlen("m3-XX.lille.iotlab.info")) + 1);
	strcpy(serverNodeFront->value, "m3-XX.lille.iotlab.info");

	/* NeworkProperty local */
	NetworkProperty* serverNodeLocal = new_NetworkProperty();
	serverNodeLocal->super->name = malloc(sizeof(char) * (strlen("local")) + 1);
	strcpy(serverNodeLocal->super->name, "local");
	serverNodeLocal->value = malloc(sizeof(char) * strlen("aaaa::0:0:5") + 1);
	strcpy(serverNodeLocal->value, "aaaa::0:0:5");
	/*get_local_addresses(serverNodeLocal->value);*/

	/* NetworkInfo ip
		NetworkInfo* contikiNodeIP = new_NetworkInfo();
		contikiNodeIP->super->name = malloc(sizeof(char) * (strlen("ip")) + 1);
		strcpy(contikiNodeIP->super->name, "ip");

		contikiNodeIP->AddValues(contikiNodeIP, contikiNodeFront);
		contikiNodeIP->AddValues(contikiNodeIP, contikiNodeLocal);*/


	serverNodeIP->AddValues(serverNodeIP, serverNodeFront);
	serverNodeIP->AddValues(serverNodeIP, serverNodeLocal);

	/*serverNode->AddNetworkInformation(serverNode, serverNodeIP);*/

	/* TypeDefinition ContikiNode/1.0.0 */
	TypeDefinition* contikiNodeType = newPoly_NodeType();
	contikiNodeType->super->name = malloc(sizeof(char) * (strlen("ContikiNode")) + 1);
	strcpy(contikiNodeType->super->name, "ContikiNode");
	contikiNodeType->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(contikiNodeType->version, "0.0.1");
	contikiNodeType->bean = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNodeType->bean, "");
	contikiNodeType->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNodeType->factoryBean, "");
	contikiNodeType->abstract = false;

	/*serverNode->super->AddTypeDefinition(serverNode->super, contikiNodeType);*/

	/* TypeDefinition CoAPGroup/1.0.0 */
	TypeDefinition* coapGroupType = newPoly_GroupType();
	coapGroupType->abstract = false;
	coapGroupType->super->name = malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(coapGroupType->super->name, "CoAPGroup");
	coapGroupType->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(coapGroupType->version, "0.0.1");
	coapGroupType->bean = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroupType->bean, "");
	coapGroupType->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroupType->factoryBean, "");

	current_model->AddTypeDefinitions(current_model, coapGroupType);


	/* TypeLibrary Contiki */
	TypeLibrary* contiki = new_TypeLibrary();
	contiki->super->name = malloc(sizeof(char) * (strlen("ContikiLib")) + 1);
	strcpy(contiki->super->name, "ContikiLib");
	/*contiki->AddSubTypes(contiki, ctFakeConsole);*/
	/*contiki->AddSubTypes(contiki, ctHelloWorld);*/
	contiki->AddSubTypes(contiki, contikiNodeType);
	contiki->AddSubTypes(contiki, coapGroupType);
	/* TypeDefinition CoAPChan/0.0.1
	  	TypeDefinition* coapChanType = newPoly_ChannelType();
	  	coapChanType->abstract = false;
	  	coapChanType->super->name = malloc(sizeof(char) * (strlen("CoAPChan")) + 1);
	  	strcpy(coapChanType->super->name, "CoAPChan");
	  	coapChanType->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  	strcpy(coapChanType->version, "0.0.1");
	  	coapChanType->bean = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(coapChanType->bean, "");
	  	coapChanType->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(coapChanType->factoryBean, "");
	  	((ChannelType*)coapChanType->pDerivedObj)->upperBindings = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->lowerBindings = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->upperFragments = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->lowerFragments = 0;*/

	/* TypeDefinition FakeConsoleType
	  		TypeDefinition* ctFakeConsole = newPoly_ComponentType();
	  		ctFakeConsole->abstract = false;
	  		ctFakeConsole->super->name = malloc(sizeof(char) * (strlen("FakeConsole")) + 1);
	  		strcpy(ctFakeConsole->super->name, "FakeConsole");
	  		ctFakeConsole->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  		strcpy(ctFakeConsole->version, "0.0.1");
	  		ctFakeConsole->bean = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(ctFakeConsole->bean, "");
	  		ctFakeConsole->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(ctFakeConsole->factoryBean, "");*/

	/* TypeDefinition HelloWorldType
		TypeDefinition* ctHelloWorld = newPoly_ComponentType();
		ctHelloWorld->abstract = false;
		ctHelloWorld->super->name = malloc(sizeof(char) * (strlen("hello_world")) + 1);
		strcpy(ctHelloWorld->super->name, "hello_world");
		ctHelloWorld->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
		strcpy(ctHelloWorld->version, "0.0.1");
		ctHelloWorld->bean = malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(ctHelloWorld->bean, "");
		ctHelloWorld->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(ctHelloWorld->factoryBean, "");*/


	/* TypeLibrary Default */
	TypeLibrary* defLib = new_TypeLibrary();
	defLib->super->name = malloc(sizeof(char) * (strlen("Default")) + 1);
	strcpy(defLib->super->name, "Default");

	/* Channel CoAPChannel
	  	Channel* defaultChannel = new_Channel();
	  	defaultChannel->super->super->name = malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	  	strcpy(defaultChannel->super->super->name, "DefaultChannel");
	  	defaultChannel->super->started = true;
	  	defaultChannel->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(defaultChannel->super->metaData, "");*/

	/* Channel FragmentDictionary server-node
	  		FragmentDictionary* fdChannelServerNode = new_FragmentDictionary();
	  		fdChannelServerNode->name = malloc(sizeof(char) * (strlen("server-node")) + 1);
	  		strcpy(fdChannelServerNode->name, "server-node");*/

	/* Channel FragmentDictionary contiki-node
	  	FragmentDictionary* fdChannelContikiNode = new_FragmentDictionary();
	  	fdChannelContikiNode->name = malloc(sizeof(char) * (strlen("contiki-node")) + 1);
	  	strcpy(fdChannelContikiNode->name, "contiki-node");*/

	/*defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelContikiNode);*/
	/*defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelServerNode);*/

	/*Channel FragmentDictionary server-node
	FragmentDictionary* fdContikiNode = new_FragmentDictionary();
	fdContikiNode->name = malloc(sizeof(char) * (strlen("contiki-node")) + 1);
	strcpy(fdContikiNode->name, "contiki-node");*/

	/* Channel DictionaryValue host
	  	DictionaryValue* chanValueHost = new_DictionaryValue();
	  	chanValueHost->name = malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanValueHost->name, "host");
	  	chanValueHost->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
	  	strcpy(chanValueHost->value, "contiki.kevoree.org");*/

	/* Channel DictionaryValue port
	  	DictionaryValue* chanValuePort = new_DictionaryValue();
	  	chanValuePort->name = malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanValuePort->name, "port");
	  	chanValuePort->value = malloc(sizeof(char) * (strlen("80")) + 1);
	  	strcpy(chanValuePort->value, "80");*/

	/* Channel DictionaryValue path
	  	DictionaryValue* chanValuePath = new_DictionaryValue();
	  	chanValuePath->name = malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanValuePath->name, "path");
	  	chanValuePath->value = malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	  	strcpy(chanValuePath->value, "DefaultChannel");*/

	/* Channel DictionaryValue port
	  	DictionaryValue* dvPortContikiNode = new_DictionaryValue();
	  	dvPortContikiNode->name = malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(dvPortContikiNode->name, "port");
	  	dvPortContikiNode->value = malloc(sizeof(char) * (strlen("5683")) + 1);
	  	strcpy(dvPortContikiNode->value, "5683");*/

	/* Channel Dictionary
	  	Dictionary* chanDico = new_Dictionary();
	  	chanDico->AddValues(chanDico, chanValueHost);
	  	chanDico->AddValues(chanDico, chanValuePort);
	  	chanDico->AddValues(chanDico, chanValuePath);*/

	/*defaultChannel->super->AddDictionary(defaultChannel->super, chanDico);
	  	defaultChannel->super->AddTypeDefinition(defaultChannel->super, coapChanType);

	  	fdContikiNode->super->AddValues(fdContikiNode->super, dvPortContikiNode);*/

	/* ComponentType DictionaryAttribute FakeConsole
		DictionaryAttribute *daHelloWorld = new_DictionaryAttribute();
		daHelloWorld->fragmentDependant = false;
		daHelloWorld->optional = false;
		daHelloWorld->super->super->name = malloc(sizeof(char) * (strlen("time")) + 1);
		strcpy(daHelloWorld->super->super->name, "time");
		daHelloWorld->state = false;
		daHelloWorld->datatype = malloc(sizeof(char) * (strlen("int")) + 1);
		strcpy(daHelloWorld->datatype, "int");
		daHelloWorld->defaultValue = malloc(sizeof(char) * (strlen("5")) + 1);
		strcpy(daHelloWorld->defaultValue, "5");*/

	/* ChannelType DictionaryAttribute host
	  	DictionaryAttribute* chanDicoAttrHost = new_DictionaryAttribute();
	  	chanDicoAttrHost->fragmentDependant = false;
	  	chanDicoAttrHost->optional = false;
	  	chanDicoAttrHost->super->super->name = malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanDicoAttrHost->super->super->name, "host");
	  	chanDicoAttrHost->state = false;
	  	chanDicoAttrHost->datatype = malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrHost->datatype, "string");
	  	chanDicoAttrHost->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(chanDicoAttrHost->defaultValue, "");*/

	/* ChannelType DictionaryAttribute port
	  	DictionaryAttribute* chanDicoAttrPort = new_DictionaryAttribute();
	  	chanDicoAttrPort->fragmentDependant = false;
	  	chanDicoAttrPort->optional = false;
	  	chanDicoAttrPort->super->super->name = malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanDicoAttrPort->super->super->name, "port");
	  	chanDicoAttrPort->state = false;
	  	chanDicoAttrPort->datatype = malloc(sizeof(char) * (strlen("number")) + 1);
	  	strcpy(chanDicoAttrPort->datatype, "number");
	  	chanDicoAttrPort->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(chanDicoAttrPort->defaultValue, "");*/

	/* ChannelType DictionaryAttribute path
	  	DictionaryAttribute* chanDicoAttrPath = new_DictionaryAttribute();
	  	chanDicoAttrPath->fragmentDependant = false;
	  	chanDicoAttrPath->optional = false;
	  	chanDicoAttrPath->super->super->name = malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanDicoAttrPath->super->super->name, "path");
	  	chanDicoAttrPath->state = false;
	  	chanDicoAttrPath->datatype = malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrPath->datatype, "string");
	  	chanDicoAttrPath->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(chanDicoAttrPath->defaultValue, "");*/

	/* GroupType DictionaryAttribute port */
	DictionaryAttribute* gtDicAttrPort = new_DictionaryAttribute();
	gtDicAttrPort->fragmentDependant = true;
	gtDicAttrPort->optional = true;
	gtDicAttrPort->super->super->name = malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(gtDicAttrPort->super->super->name, "port");
	gtDicAttrPort->state = false;
	gtDicAttrPort->datatype = malloc(sizeof(char) * (strlen("number")) + 1);
	strcpy(gtDicAttrPort->datatype, "number");
	gtDicAttrPort->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrPort->defaultValue, "");

	/* GroupType DictionaryAttribute path */
	DictionaryAttribute* gtDicAttrPath = new_DictionaryAttribute();
	gtDicAttrPath->fragmentDependant = true;
	gtDicAttrPath->optional = true;
	gtDicAttrPath->super->super->name = malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(gtDicAttrPath->super->super->name, "path");
	gtDicAttrPath->state = false;
	gtDicAttrPath->datatype = malloc(sizeof(char) * (strlen("string")) + 1);
	strcpy(gtDicAttrPath->datatype, "string");
	gtDicAttrPath->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrPath->defaultValue, "");

	/* GroupType DictionaryAttribute proxy_port */
	DictionaryAttribute* gtDicAttrProxy = new_DictionaryAttribute();
	gtDicAttrProxy->fragmentDependant = true;
	gtDicAttrProxy->optional = true;
	gtDicAttrProxy->super->super->name = malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(gtDicAttrProxy->super->super->name, "proxy_port");
	gtDicAttrProxy->state = false;
	gtDicAttrProxy->datatype = malloc(sizeof(char) * (strlen("int")) + 1);
	strcpy(gtDicAttrProxy->datatype, "int");
	gtDicAttrProxy->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrProxy->defaultValue, "20000");

	/* GroupType DictionaryAttribute proxy_port
	  		DictionaryAttribute* gtDicAttrProxy = new_DictionaryAttribute();
	  		gtDicAttrProxy->fragmentDependant = true;
	  		gtDicAttrProxy->optional = true;
	  		gtDicAttrProxy->super->super->name = malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	  		strcpy(gtDicAttrProxy->super->super->name, "proxy_port");
	  		gtDicAttrProxy->state = false;
	  		gtDicAttrProxy->datatype = malloc(sizeof(char) * (strlen("int")) + 1);
	  		strcpy(gtDicAttrProxy->datatype, "int");
	  		gtDicAttrProxy->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(gtDicAttrProxy->defaultValue, "9000");*/

	/* ComponentInstance DictionaryType HelloWorld
		DictionaryType* dtHelloWorld = new_DictionaryType();
		dtHelloWorld->AddAttributes(dtHelloWorld, daHelloWorld);*/

	/* ComponentInstance DictionaryType HelloWorld
		DictionaryType* dtHelloWorld = new_DictionaryType();*/


	/* GroupType DictionaryType */
	DictionaryType* gtDicType = new_DictionaryType();
	coapGroupType->AddDictionaryType(coapGroupType, gtDicType);

	gtDicType->AddAttributes(gtDicType, gtDicAttrPort);
	gtDicType->AddAttributes(gtDicType, gtDicAttrPath);
	gtDicType->AddAttributes(gtDicType, gtDicAttrProxy);

	/* ChannelType DictionaryType
	  	DictionaryType* chanDicType = new_DictionaryType();
	  	chanDicType->AddAttributes(chanDicType, chanDicoAttrHost);
	  	chanDicType->AddAttributes(chanDicType, chanDicoAttrPort);
	  	chanDicType->AddAttributes(chanDicType, chanDicoAttrPath);*/

	/* DeployUnit //kevoree-contiki-node/0.0.1 */
	DeployUnit* kevContikiNode = new_DeployUnit();
	kevContikiNode->super->name = malloc(sizeof(char) * (strlen("kevoree-contiki-node")) + 1);
	strcpy(kevContikiNode->super->name, "kevoree-contiki-node");
	kevContikiNode->groupName = malloc(sizeof(char) * (strlen("org.kevoree.library.c")) + 1);
	strcpy(kevContikiNode->groupName, "org.kevoree.library.c");
	kevContikiNode->hashcode = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevContikiNode->hashcode, "");
	kevContikiNode->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(kevContikiNode->version,"0.0.1");
	kevContikiNode->url = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevContikiNode->url, "");
	kevContikiNode->type = malloc(sizeof(char) * (strlen("ce")) + 1);
	strcpy(kevContikiNode->type,"ce");

	/* DeployUnit //kevoree-group-coap/0.0.1 */
	DeployUnit* kevGroupCoap = new_DeployUnit();
	kevGroupCoap->super->name = malloc(sizeof(char) * (strlen("kevoree-group-coap")) + 1);
	strcpy(kevGroupCoap->super->name, "kevoree-group-coap");
	kevGroupCoap->groupName = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevGroupCoap->groupName, "");
	kevGroupCoap->hashcode = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevGroupCoap->hashcode, "");
	kevGroupCoap->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(kevGroupCoap->version,"0.0.1");
	kevGroupCoap->url = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevGroupCoap->url, "");
	kevGroupCoap->type = malloc(sizeof(char) * (strlen("ce")) + 1);
	strcpy(kevGroupCoap->type,"ce");

	/* DeployUnit //kevoree-chan-coap/0.0.1
	  	DeployUnit* kevChanCoap = new_DeployUnit();
	  	kevChanCoap->super->name = malloc(sizeof(char) * (strlen("kevoree-chan-coap")) + 1);
	  	strcpy(kevChanCoap->super->name, "kevoree-chan-coap");
	  	kevChanCoap->groupName = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(kevChanCoap->groupName, "");
	  	kevChanCoap->hashcode = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(kevChanCoap->hashcode, "");
	  	kevChanCoap->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  	strcpy(kevChanCoap->version,"0.0.1");
	  	kevChanCoap->url = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(kevChanCoap->url, "");
	  	kevChanCoap->type = malloc(sizeof(char) * (strlen("ce")) + 1);
	  	strcpy(kevChanCoap->type,"ce");*/

	/* DeployUnit //kevoree-comp-fakeconsole/0.0.1
	  		DeployUnit* duFakeConsole = new_DeployUnit();
	  		duFakeConsole->super->name = malloc(sizeof(char) * (strlen("kevoree-comp-fakeconsole")) + 1);
	  		strcpy(duFakeConsole->super->name, "kevoree-comp-fakeconsole");
	  		duFakeConsole->groupName = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(duFakeConsole->groupName, "");
	  		duFakeConsole->hashcode = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(duFakeConsole->hashcode, "");
	  		duFakeConsole->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  		strcpy(duFakeConsole->version,"0.0.1");
	  		duFakeConsole->url = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(duFakeConsole->url, "");
	  		duFakeConsole->type = malloc(sizeof(char) * (strlen("ce")) + 1);
	  		strcpy(duFakeConsole->type,"ce");*/

	/* DeployUnit //kevoree-comp-helloworld/0.0.1
		DeployUnit* duHelloWorld = new_DeployUnit();
		duHelloWorld->super->name = malloc(sizeof(char) * (strlen("hello_world")) + 1);
		strcpy(duHelloWorld->super->name, "hello_world");
		duHelloWorld->groupName = malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(duHelloWorld->groupName, "kev_contiki");
		duHelloWorld->hashcode = malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(duHelloWorld->hashcode, "");
		duHelloWorld->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
		strcpy(duHelloWorld->version,"0.0.1");
		duHelloWorld->url = malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(duHelloWorld->url, "");
		duHelloWorld->type = malloc(sizeof(char) * (strlen("ce")) + 1);
		strcpy(duHelloWorld->type,"ce");*/

	/* PortTypeRef sendMsg
	  		PortTypeRef* ptrSendMsg = new_PortTypeRef();
	  		ptrSendMsg->super->name = malloc(sizeof(char) * (strlen("sendMsg")) + 1);
	  		strcpy(ptrSendMsg->super->name, "sendMsg");
	  		ptrSendMsg->noDependency = true;
	  		ptrSendMsg->optional = true;*/

	/* PortTypeRef inMsg
	  		PortTypeRef* ptrInMsg = new_PortTypeRef();
	  		ptrInMsg->super->name = malloc(sizeof(char) * (strlen("inMsg")) + 1);
	  		strcpy(ptrInMsg->super->name, "inMsg");
	  		ptrInMsg->noDependency = true;
	  		ptrInMsg->optional = true;*/

	/* PortTypeRef sendText
		PortTypeRef* ptrSendText = new_PortTypeRef();
		ptrSendText->super->name = malloc(sizeof(char) * (strlen("sendText")) + 1);
		strcpy(ptrSendText->super->name, "sendText");
		ptrSendText->noDependency = true;
		ptrSendText->optional = true;*/

	/* PortTypeRef fake
		PortTypeRef* ptrFake = new_PortTypeRef();
		ptrFake->super->name = malloc(sizeof(char) * (strlen("fake")) + 1);
		strcpy(ptrFake->super->name, "fake");
		ptrFake->noDependency = true;
		ptrFake->optional = true;*/

	/* Port inMsg
	  		Port* pInMsg = new_Port();
	  		pInMsg->super->name = malloc(sizeof(char) * (strlen("inMsg")) + 1);
	  		strcpy(pInMsg->super->name, "inMsg");
	  		pInMsg->AddPortTypeRef(pInMsg, ptrInMsg);*/

	/* Port sendMsg
	  		Port* pSendMsg = new_Port();
	  		pSendMsg->super->name = malloc(sizeof(char) * (strlen("sendMsg")) + 1);
	  		strcpy(pSendMsg->super->name, "sendMsg");
	  		pSendMsg->AddPortTypeRef(pSendMsg, ptrSendMsg);*/

	/* Port fake
		Port* pFake = new_Port();
		pFake->super->name = malloc(sizeof(char) * (strlen("fake")) + 1);
		strcpy(pFake->super->name, "fake");
		pFake->AddPortTypeRef(pFake, ptrFake);*/

	/* Port sendMsg
		Port* pSendText = new_Port();
		pSendText->super->name = malloc(sizeof(char) * (strlen("sendText")) + 1);
		strcpy(pSendText->super->name, "sendText");
		pSendText->AddPortTypeRef(pSendText, ptrSendText);*/

	/* MBinding inMsg
	  		MBinding* mbInMsg = new_MBinding();
	  		mbInMsg->AddHub(mbInMsg, defaultChannel);
	  		mbInMsg->AddPort(mbInMsg, pInMsg);
	  		pInMsg->AddBindings(pInMsg, mbInMsg);*/

	/* MBinding fake
	  	MBinding* mbFake = new_MBinding();
	  	mbFake->AddHub(mbFake, defaultChannel);
	  	mbFake->AddPort(mbFake, pFake);
	  	pFake->AddBindings(pFake, mbFake);*/

	/* MBinding sendMsg
	  		MBinding* mbSendMsg = new_MBinding();
	  		mbSendMsg->AddHub(mbSendMsg, defaultChannel);
	  		mbSendMsg->AddPort(mbSendMsg, pSendMsg);
	  		pSendMsg->AddBindings(pSendMsg, mbSendMsg);*/

	/* MBinding sendText
	  	MBinding* mbSendText = new_MBinding();
	  	mbSendText->AddHub(mbSendText, defaultChannel);
	  	mbSendText->AddPort(mbSendText, pSendText);
	  	pSendText->AddBindings(pSendText, mbSendText);*/

	/* Group CoAP */
	Group* coapGroup = new_Group();
	coapGroup->super->super->name = malloc(sizeof(char) * (strlen("group0")) + 1);
	strcpy(coapGroup->super->super->name, "group0");
	coapGroup->super->started = true;
	coapGroup->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroup->super->metaData, "");

	current_model->AddGroups(current_model, coapGroup);
	/*coapGroup->AddSubNodes(coapGroup, serverNode);*/
	coapGroup->super->AddTypeDefinition(coapGroup->super, coapGroupType);

	/* FragmentDictionary contiki-node */
	FragmentDictionary* coapGroupFragDico = new_FragmentDictionary();
	coapGroupFragDico->name = malloc(sizeof(char) * (strlen("CoAPGroupFragDic")) + 1);
	strcpy(coapGroupFragDico->name, "CoAPGroupFragDic");

	/* Group DictionaryValue port */
	DictionaryValue* groupValuePort = new_DictionaryValue();
	groupValuePort->name = malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(groupValuePort->name, "port");
	groupValuePort->value = malloc(sizeof(char) * (strlen("5683")) + 1);
	strcpy(groupValuePort->value, "5683");

	/* Group DictionaryValue proxy_port */
	DictionaryValue* groupValueProxy = new_DictionaryValue();
	groupValueProxy->name = malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(groupValueProxy->name, "proxy_port");
	groupValueProxy->value = malloc(sizeof(char) * (strlen("20000")) + 1);
	strcpy(groupValueProxy->value, "20000");

	/* Group DictionaryValue path */
	DictionaryValue* groupValuePath = new_DictionaryValue();
	groupValuePath->name = malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(groupValuePath->name, "path");
	groupValuePath->value = malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(groupValuePath->value, "CoAPGroup");

	coapGroup->super->AddFragmentDictionary(coapGroup->super, coapGroupFragDico);
	/* Adding values to FragmentDictionary ContikiNode */
	coapGroupFragDico->super->AddValues(coapGroupFragDico->super, groupValuePort);
	coapGroupFragDico->super->AddValues(coapGroupFragDico->super, groupValueProxy);
	coapGroupFragDico->super->AddValues(coapGroupFragDico->super, groupValuePath);


	/* DictionaryType contikiNodeDicType
	DictionaryType* contikiNodeDicType = new_DictionaryType();
	contikiNodeType->AddDictionaryType(contikiNodeType, contikiNodeDicType);*/

	/*ComponentInstance* ciFakeConsole = new_ComponentInstance();
	  		ciFakeConsole->super->super->name = malloc(sizeof(char) * (strlen("fakeconsole")) + 1);
	  		strcpy(ciFakeConsole->super->super->name, "fakeconsole");
	  		ciFakeConsole->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(ciFakeConsole->super->metaData, "");
	  		ciFakeConsole->super->started = true;
	  		ciFakeConsole->super->AddTypeDefinition(ciFakeConsole->super, ctFakeConsole);
	  		ciFakeConsole->AddProvided(ciFakeConsole, pInMsg);
	  		ciFakeConsole->AddRequired(ciFakeConsole, pSendMsg);*/

	/*contikiNode->AddComponents(contikiNode, ciFakeConsole);*/

	/*serverNode->AddGroups(serverNode, coapGroup);
	  		serverNode->AddComponents(serverNode, ciFakeConsole);
	  		serverNode->AddComponents(serverNode, ciHelloWorld);

	  		ctFakeConsole->AddDeployUnit(ctFakeConsole, duFakeConsole);*/
	/*ctHelloWorld->AddDeployUnit(ctHelloWorld, duHelloWorld);*/
	contikiNodeType->AddDeployUnit(contikiNodeType, kevContikiNode);
	coapGroupType->AddDeployUnit(coapGroupType, kevGroupCoap);
	/*coapChanType->AddDeployUnit(coapChanType, kevChanCoap);*/

	/*ctFakeConsole->AddDictionaryType(ctFakeConsole, dtFakeConsole);*/
	/*ctHelloWorld->AddDictionaryType(ctHelloWorld, dtHelloWorld);*/
	/*coapChanType->AddDictionaryType(coapChanType, chanDicType);*/

	/*defaultChannel->AddBindings(defaultChannel, mbInMsg);*/
	/*defaultChannel->AddBindings(defaultChannel, mbFake);*/
	/*defaultChannel->AddBindings(defaultChannel, mbSendMsg);*/
	/*defaultChannel->AddBindings(defaultChannel, mbSendText);*/

	/*((ComponentType*)ctFakeConsole->pDerivedObj)->AddProvided((ComponentType*)ctFakeConsole->pDerivedObj, ptrInMsg);
	  		((ComponentType*)ctFakeConsole->pDerivedObj)->AddRequired((ComponentType*)ctFakeConsole->pDerivedObj, ptrSendMsg);*/
	/*((ComponentType*)ctHelloWorld->pDerivedObj)->AddProvided((ComponentType*)ctHelloWorld->pDerivedObj, ptrFake);
	  	((ComponentType*)ctHelloWorld->pDerivedObj)->AddRequired((ComponentType*)ctHelloWorld->pDerivedObj, ptrSendText);*/


	current_model->AddLibraries(current_model, contiki);
	current_model->AddLibraries(current_model, defLib);

	/*type definition*/
	current_model->AddTypeDefinitions(current_model, contikiNodeType);
	/*current_model->AddTypeDefinitions(current_model, ctHelloWorld);*/

	/*deploy unit*/
	/*modelX->AddDeployUnits(modelX, duHelloWorld);*/
	current_model->AddDeployUnits(current_model, kevContikiNode);
	current_model->AddDeployUnits(current_model, kevGroupCoap);
	/*current_model->AddDeployUnits(current_model, duHelloWorld);*/


	/*instances*/

	int i = 0;
	int j = 0;

	for(i = 0; i < 1; i++)
	{

		/*contiki->AddSubTypes(contiki, coapChanType);*/
		contikiNode->super->AddTypeDefinition(contikiNode->super, contikiNodeType);
		contikiNode->AddGroups(contikiNode, coapGroup);
		//
		//		for(j = 0; j < 1; j++)
		//		{
		//			ComponentInstance* ciHelloWorld = new_ComponentInstance();
		//			ciHelloWorld->super->super->name = malloc(sizeof(char) * (strlen("HelloWorldXX")) + 1);
		//			sprintf(ciHelloWorld->super->super->name, "HelloWorld%d", j);
		//			ciHelloWorld->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
		//			strcpy(ciHelloWorld->super->metaData, "");
		//			ciHelloWorld->super->started = true;
		//			ciHelloWorld->super->AddTypeDefinition(ciHelloWorld->super, ctHelloWorld);
		//
		//			/*((ComponentType*)ctHelloWorld->pDerivedObj)->AddProvided(ctHelloWorld->pDerivedObj, ptrFake);
		//			((ComponentType*)ctHelloWorld->pDerivedObj)->AddRequired(ctHelloWorld->pDerivedObj, ptrSendText);
		//			contikiNode->AddComponents(contikiNode, ciHelloWorld);
		//			ciHelloWorld->AddProvided(ciHelloWorld, pFake);
		//			ciHelloWorld->AddRequired(ciHelloWorld, pSendText);*/
		//			contikiNode->AddComponents(contikiNode, ciHelloWorld);
		//		}
		//
		coapGroup->AddSubNodes(coapGroup, contikiNode);


		/*printf("%d\n", mem_count);*/
	}

	visitor_print = (Visitor*)malloc(sizeof(Visitor));

	/*visitor_print->action = actionstore;*/
	/*visitor_print->action = actionprintf;*/
	visitor_print->action = actionprintpath;
	/*visitor_print->action = actionUpdateDelete;*/

	current_model->VisitPaths(current_model, visitor_print);
	/*current_model->Visit(current_model, visitor_print);*/


	printf("Starting Kevoree adaptations\n");

	FILE *new_model_json = fopen("new_model.json", "r");
	fseek(new_model_json, 0L, SEEK_END);
	int modelLength = ftell(new_model_json);
	fseek(new_model_json, 0L, SEEK_SET);

	printf("INFO: Trying to load new_model with length %d\n", modelLength);

	char *jsonModel = malloc(modelLength + 1);
	int ch;
	bool firstChar = true;
	bool isFirst = true;
	int listLength = 0;

	while ((ch = fgetc(new_model_json)) != EOF) {
		if (firstChar) {
			sprintf(jsonModel, "%c", ch);
			firstChar = false;
		} else {
			sprintf(jsonModel, "%s%c", jsonModel, ch);
		}
	}

	fclose(new_model_json);

	printf("INFO: new_model JSON loaded in RAM\n");
	printf("%s\n", jsonModel);

	struct jsonparse_state jsonState;

	jsonparse_setup(&jsonState, jsonModel, modelLength + 1);

	new_model = JSONKevDeserializer(&jsonState, jsonparse_next(&jsonState));

	if(new_model != NULL)
	{
		printf("INFO: new_model loaded successfully!\n");
	}
	else
	{
		printf("ERROR: new_model cannot be loaded\n");
	}


	if(new_model != NULL)
	{
		visitor_print->action = actionprintpath;
		/*current_model->VisitPaths(current_model, visitor_print);*/
		printf("\n\n");
		new_model->VisitPaths(new_model, visitor_print);
	}
		/*printf("INFO: new_model detected, comparing with curent_model\n\n");
		visitor_print->action = actionUpdateDelete;
		current_model->VisitPaths(current_model, visitor_print);
		visitor_print->action = actionAdd;
		new_model->VisitPaths(new_model, visitor_print);

		if((listLength = list_length(model_traces)))
		{
			ModelTrace *mt;

			for (i = 0; i < listLength; ++i) {
				if(isFirst)
				{
					mt = list_head(model_traces);
					char *strTrace = mt->ToString(mt->pDerivedObj);
					printf(strTrace);
					free(strTrace);
					isFirst = false;
				}
				else {
					mt = list_item_next(mt);
					char *strTrace = mt->ToString(mt->pDerivedObj);
					printf(strTrace);
					free(strTrace);
				}
			}
		}
	}
	else
	{
		printf("ERROR: New model cannot be visited!\n");
	}

	free(jsonModel);
	*/

	return EXIT_SUCCESS;
}
