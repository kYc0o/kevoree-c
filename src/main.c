/*#include "DefaultFactorykevoree.h"
#include "Comparekevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include "kevoree.h"

<<<<<<< Updated upstream
int mem_count = 0;
=======
#include "list.h"

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
>>>>>>> Stashed changes

void* my_malloc(size_t s)
{
<<<<<<< Updated upstream
	mem_count += s;
	return malloc(s);
}
=======
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
>>>>>>> Stashed changes

void* my_calloc(size_t nmemb, size_t size)
{
	mem_count += size;
	return calloc(nmemb, size);
}

<<<<<<< Updated upstream
void str_free(char* ptr)
{
	mem_count -= strlen(ptr) + 1;
	free(ptr);
=======
void actionprintpath(char *path, Type type, void *value)
{
	switch(type)
	{
	case STRING:
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
	char *path = strdup(_path);
	/*
	 * TODO return if memory is full
	 */
	switch(type)
	{
	case STRING:
		path = strtok(path, "\\");
		if(new_model->FindByPath(path, new_model) == NULL)
		{
			/*printf("path = %s  value = %s\n", path, (char*)value);
			printf("Path %s does not exist in new_model, removing...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelRemoveTrace(path, (char*)value, path);
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
					ModelTrace *mt = newPoly_ModelSetTrace(path, string2, "STRING");
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
				ModelTrace *mt = newPoly_ModelSetTrace(path, string2, "STRING");
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
				ModelTrace *mt = newPoly_ModelSetTrace(path, "NULL", "STRING");
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
		path = strtok(path, "\\");
		if(new_model->FindByPath(path, new_model) == NULL)
		{
			/*printf("path = %s  value = %d\n", path, (int)value);
			printf("Path %s does not exist in new_model, removing...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelRemoveTrace(path, (char*)value, path);
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
			char v2str[4] = {0};
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
				ModelTrace *mt = newPoly_ModelSetTrace(path, v2str, "INT");
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
}

void actionAdd(char* _path, Type type, void* value)
{
	char *path = strdup(_path);
	/*
	 * TODO return if memory is full
	 */
	switch(type)
	{
	case STRING:
		/*printf("path = %s  value = %s\n", path, (char*)value);*/
		/*path = strtok(path, "\\");*/
		if(current_model->FindByPath(path, current_model) == NULL)
		{
			/*printf("Path %s does not exist in curent_model, adding...\n\n", path);*/
			ModelTrace *mt = newPoly_ModelAddTrace(path, (char*)value, path, "STRING");
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
	free(path);
>>>>>>> Stashed changes
}

int main(void)
{
<<<<<<< Updated upstream
	//printf("Starting kevoree C implementation\n");

	/* ContainerNode contikiNode
	  		ContainerNode* serverNode = new_ContainerNode();
	  		serverNode->super->super->name = my_malloc(sizeof(char) * (strlen("server-node")) + 1);
	  		strcpy(serverNode->super->super->name, "server-node");
	  		serverNode->super->started = true;
	  		serverNode->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(serverNode->super->metaData, "");*/

	/* NeworkProperty front */
	NetworkProperty* contikiNodeFront = new_NetworkProperty();
	contikiNodeFront->super->name = my_malloc(sizeof(char) * (strlen("front")) + 1);
	strcpy(contikiNodeFront->super->name, "front");
	contikiNodeFront->value = my_malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
	strcpy(contikiNodeFront->value, "contiki.kevoree.org");

	/* NeworkProperty local */
	NetworkProperty* contikiNodeLocal = new_NetworkProperty();
	contikiNodeLocal->super->name = my_malloc(sizeof(char) * (strlen("local")) + 1);
	strcpy(contikiNodeLocal->super->name, "local");
	contikiNodeLocal->value = my_malloc(sizeof(char) * (strlen("aaaa::0:0:3")) + 1);
	strcpy(contikiNodeLocal->value, "aaaa::0:0:3");

	/* NeworkProperty front */
	NetworkProperty* serverNodeFront = new_NetworkProperty();
	serverNodeFront->super->name = my_malloc(sizeof(char) * (strlen("front")) + 1);
	strcpy(serverNodeFront->super->name, "front");
	serverNodeFront->value = my_malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
	strcpy(serverNodeFront->value, "contiki.kevoree.org");

	/* NeworkProperty local */
	NetworkProperty* serverNodeLocal = new_NetworkProperty();
	serverNodeLocal->super->name = my_malloc(sizeof(char) * (strlen("local")) + 1);
	strcpy(serverNodeLocal->super->name, "local");
	serverNodeLocal->value = my_malloc(sizeof(char) * (strlen("aaaa::0:0:3")) + 1);
=======
	printf("Starting kevoree C implementation\n");

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
>>>>>>> Stashed changes
	strcpy(serverNodeLocal->value, "aaaa::0:0:5");
	/*get_local_addresses(serverNodeLocal->value);*/

<<<<<<< Updated upstream
	/* NetworkInfo ip */
	NetworkInfo* contikiNodeIP = new_NetworkInfo();
	contikiNodeIP->super->name = my_malloc(sizeof(char) * (strlen("ip")) + 1);
	strcpy(contikiNodeIP->super->name, "ip");
=======
	/* NetworkInfo ip
		NetworkInfo* contikiNodeIP = new_NetworkInfo();
		contikiNodeIP->super->name = malloc(sizeof(char) * (strlen("ip")) + 1);
		strcpy(contikiNodeIP->super->name, "ip");
>>>>>>> Stashed changes

		contikiNodeIP->AddValues(contikiNodeIP, contikiNodeFront);
		contikiNodeIP->AddValues(contikiNodeIP, contikiNodeLocal);*/

	/* NetworkInfo ip */
	NetworkInfo* serverNodeIP = new_NetworkInfo();
<<<<<<< Updated upstream
	serverNodeIP->super->name = my_malloc(sizeof(char) * (strlen("ip")) + 1);
=======
	serverNodeIP->super->name = malloc(sizeof(char) * (strlen("ip")) + 1);
>>>>>>> Stashed changes
	strcpy(serverNodeIP->super->name, "ip");

	serverNodeIP->AddValues(serverNodeIP, serverNodeFront);
	serverNodeIP->AddValues(serverNodeIP, serverNodeLocal);

	/*serverNode->AddNetworkInformation(serverNode, serverNodeIP);*/

	/* TypeDefinition ContikiNode/1.0.0 */
	TypeDefinition* contikiNodeType = newPoly_NodeType();
<<<<<<< Updated upstream
	contikiNodeType->super->name = my_malloc(sizeof(char) * (strlen("ContikiNode")) + 1);
	strcpy(contikiNodeType->super->name, "ContikiNode");
	contikiNodeType->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(contikiNodeType->version, "0.0.1");
	contikiNodeType->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNodeType->bean, "");
	contikiNodeType->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	contikiNodeType->super->name = malloc(sizeof(char) * (strlen("ContikiNode")) + 1);
	strcpy(contikiNodeType->super->name, "ContikiNode");
	contikiNodeType->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(contikiNodeType->version, "0.0.1");
	contikiNodeType->bean = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNodeType->bean, "");
	contikiNodeType->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	strcpy(contikiNodeType->factoryBean, "");
	contikiNodeType->abstract = false;

	/*serverNode->super->AddTypeDefinition(serverNode->super, contikiNodeType);*/

	/* TypeDefinition CoAPGroup/1.0.0 */
	TypeDefinition* coapGroupType = newPoly_GroupType();
	coapGroupType->abstract = false;
<<<<<<< Updated upstream
	coapGroupType->super->name = my_malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(coapGroupType->super->name, "CoAPGroup");
	coapGroupType->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(coapGroupType->version, "0.0.1");
	coapGroupType->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroupType->bean, "");
	coapGroupType->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	coapGroupType->super->name = malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(coapGroupType->super->name, "CoAPGroup");
	coapGroupType->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(coapGroupType->version, "0.0.1");
	coapGroupType->bean = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroupType->bean, "");
	coapGroupType->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	strcpy(coapGroupType->factoryBean, "");

	/* TypeDefinition CoAPChan/0.0.1
	  	TypeDefinition* coapChanType = newPoly_ChannelType();
	  	coapChanType->abstract = false;
<<<<<<< Updated upstream
	  	coapChanType->super->name = my_malloc(sizeof(char) * (strlen("CoAPChan")) + 1);
	  	strcpy(coapChanType->super->name, "CoAPChan");
	  	coapChanType->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  	strcpy(coapChanType->version, "0.0.1");
	  	coapChanType->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(coapChanType->bean, "");
	  	coapChanType->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	  	coapChanType->super->name = malloc(sizeof(char) * (strlen("CoAPChan")) + 1);
	  	strcpy(coapChanType->super->name, "CoAPChan");
	  	coapChanType->version = malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  	strcpy(coapChanType->version, "0.0.1");
	  	coapChanType->bean = malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(coapChanType->bean, "");
	  	coapChanType->factoryBean = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	  	strcpy(coapChanType->factoryBean, "");
	  	((ChannelType*)coapChanType->pDerivedObj)->upperBindings = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->lowerBindings = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->upperFragments = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->lowerFragments = 0;*/

	/* TypeDefinition FakeConsoleType
	  		TypeDefinition* ctFakeConsole = newPoly_ComponentType();
	  		ctFakeConsole->abstract = false;
<<<<<<< Updated upstream
	  		ctFakeConsole->super->name = my_malloc(sizeof(char) * (strlen("FakeConsole")) + 1);
	  		strcpy(ctFakeConsole->super->name, "FakeConsole");
	  		ctFakeConsole->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  		strcpy(ctFakeConsole->version, "0.0.1");
	  		ctFakeConsole->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(ctFakeConsole->bean, "");
	  		ctFakeConsole->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(ctFakeConsole->factoryBean, "");*/

	/* TypeDefinition HelloWorldType */
	TypeDefinition* ctHelloWorld = newPoly_ComponentType();
	ctHelloWorld->abstract = false;
	ctHelloWorld->super->name = my_malloc(sizeof(char) * (strlen("BlinkType")) + 1);
	strcpy(ctHelloWorld->super->name, "BlinkType");
	ctHelloWorld->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(ctHelloWorld->version, "0.0.1");
	ctHelloWorld->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(ctHelloWorld->bean, "");
	ctHelloWorld->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(ctHelloWorld->factoryBean, "");

	/* TypeLibrary Contiki */
	TypeLibrary* contiki = new_TypeLibrary();
	contiki->super->name = my_malloc(sizeof(char) * (strlen("Contiki")) + 1);
	strcpy(contiki->super->name, "Contiki");
	/*contiki->AddSubTypes(contiki, ctFakeConsole);*/
	contiki->AddSubTypes(contiki, ctHelloWorld);
=======
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

	/* TypeLibrary Contiki */
	TypeLibrary* contiki = new_TypeLibrary();
	contiki->super->name = malloc(sizeof(char) * (strlen("ContikiLib")) + 1);
	strcpy(contiki->super->name, "ContikiLib");
	/*contiki->AddSubTypes(contiki, ctFakeConsole);*/
	/*contiki->AddSubTypes(contiki, ctHelloWorld);*/
>>>>>>> Stashed changes
	contiki->AddSubTypes(contiki, contikiNodeType);
	contiki->AddSubTypes(contiki, coapGroupType);

	/* TypeLibrary Default */
	TypeLibrary* defLib = new_TypeLibrary();
	defLib->super->name = my_malloc(sizeof(char) * (strlen("Default")) + 1);
	strcpy(defLib->super->name, "Default");

	/* Channel CoAPChannel
	  	Channel* defaultChannel = new_Channel();
<<<<<<< Updated upstream
	  	defaultChannel->super->super->name = my_malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	  	strcpy(defaultChannel->super->super->name, "DefaultChannel");
	  	defaultChannel->super->started = true;
	  	defaultChannel->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	  	defaultChannel->super->super->name = malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	  	strcpy(defaultChannel->super->super->name, "DefaultChannel");
	  	defaultChannel->super->started = true;
	  	defaultChannel->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	  	strcpy(defaultChannel->super->metaData, "");*/

	/* Channel FragmentDictionary server-node
	  		FragmentDictionary* fdChannelServerNode = new_FragmentDictionary();
<<<<<<< Updated upstream
	  		fdChannelServerNode->name = my_malloc(sizeof(char) * (strlen("server-node")) + 1);
=======
	  		fdChannelServerNode->name = malloc(sizeof(char) * (strlen("server-node")) + 1);
>>>>>>> Stashed changes
	  		strcpy(fdChannelServerNode->name, "server-node");*/

	/* Channel FragmentDictionary contiki-node
	  	FragmentDictionary* fdChannelContikiNode = new_FragmentDictionary();
<<<<<<< Updated upstream
	  	fdChannelContikiNode->name = my_malloc(sizeof(char) * (strlen("contiki-node")) + 1);
=======
	  	fdChannelContikiNode->name = malloc(sizeof(char) * (strlen("contiki-node")) + 1);
>>>>>>> Stashed changes
	  	strcpy(fdChannelContikiNode->name, "contiki-node");*/

	/*defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelContikiNode);*/
	/*defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelServerNode);*/

	/*Channel FragmentDictionary server-node */
	FragmentDictionary* fdContikiNode = new_FragmentDictionary();
<<<<<<< Updated upstream
	fdContikiNode->name = my_malloc(sizeof(char) * (strlen("contiki-node")) + 1);
=======
	fdContikiNode->name = malloc(sizeof(char) * (strlen("contiki-node")) + 1);
>>>>>>> Stashed changes
	strcpy(fdContikiNode->name, "contiki-node");

	/* Channel DictionaryValue host
	  	DictionaryValue* chanValueHost = new_DictionaryValue();
<<<<<<< Updated upstream
	  	chanValueHost->name = my_malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanValueHost->name, "host");
	  	chanValueHost->value = my_malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
=======
	  	chanValueHost->name = malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanValueHost->name, "host");
	  	chanValueHost->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
>>>>>>> Stashed changes
	  	strcpy(chanValueHost->value, "contiki.kevoree.org");*/

	/* Channel DictionaryValue port
	  	DictionaryValue* chanValuePort = new_DictionaryValue();
<<<<<<< Updated upstream
	  	chanValuePort->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanValuePort->name, "port");
	  	chanValuePort->value = my_malloc(sizeof(char) * (strlen("80")) + 1);
=======
	  	chanValuePort->name = malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanValuePort->name, "port");
	  	chanValuePort->value = malloc(sizeof(char) * (strlen("80")) + 1);
>>>>>>> Stashed changes
	  	strcpy(chanValuePort->value, "80");*/

	/* Channel DictionaryValue path
	  	DictionaryValue* chanValuePath = new_DictionaryValue();
<<<<<<< Updated upstream
	  	chanValuePath->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanValuePath->name, "path");
	  	chanValuePath->value = my_malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
=======
	  	chanValuePath->name = malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanValuePath->name, "path");
	  	chanValuePath->value = malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
>>>>>>> Stashed changes
	  	strcpy(chanValuePath->value, "DefaultChannel");*/

	/* Channel DictionaryValue port
	  	DictionaryValue* dvPortContikiNode = new_DictionaryValue();
<<<<<<< Updated upstream
	  	dvPortContikiNode->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(dvPortContikiNode->name, "port");
	  	dvPortContikiNode->value = my_malloc(sizeof(char) * (strlen("5683")) + 1);
=======
	  	dvPortContikiNode->name = malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(dvPortContikiNode->name, "port");
	  	dvPortContikiNode->value = malloc(sizeof(char) * (strlen("5683")) + 1);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	  		DictionaryAttribute* daFakeConsoleProxy = new_DictionaryAttribute();
	  		daFakeConsoleProxy->fragmentDependant = false;
	  		daFakeConsoleProxy->optional = true;
	  		daFakeConsoleProxy->super->super->name = my_malloc(sizeof(char) * (strlen("proxy")) + 1);
	  		strcpy(daFakeConsoleProxy->super->super->name, "proxy");
	  		daFakeConsoleProxy->state = false;
	  		daFakeConsoleProxy->datatype = my_malloc(sizeof(char) * (strlen("boolean")) + 1);
	  		strcpy(daFakeConsoleProxy->datatype, "boolean");
	  		daFakeConsoleProxy->defaultValue = my_malloc(sizeof(char) * (strlen("false")) + 1);
	  		strcpy(daFakeConsoleProxy->defaultValue, "false");*/
=======
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
>>>>>>> Stashed changes

	/* ChannelType DictionaryAttribute host
	  	DictionaryAttribute* chanDicoAttrHost = new_DictionaryAttribute();
	  	chanDicoAttrHost->fragmentDependant = false;
	  	chanDicoAttrHost->optional = false;
<<<<<<< Updated upstream
	  	chanDicoAttrHost->super->super->name = my_malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanDicoAttrHost->super->super->name, "host");
	  	chanDicoAttrHost->state = false;
	  	chanDicoAttrHost->datatype = my_malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrHost->datatype, "string");
	  	chanDicoAttrHost->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	  	chanDicoAttrHost->super->super->name = malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanDicoAttrHost->super->super->name, "host");
	  	chanDicoAttrHost->state = false;
	  	chanDicoAttrHost->datatype = malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrHost->datatype, "string");
	  	chanDicoAttrHost->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	  	strcpy(chanDicoAttrHost->defaultValue, "");*/

	/* ChannelType DictionaryAttribute port
	  	DictionaryAttribute* chanDicoAttrPort = new_DictionaryAttribute();
	  	chanDicoAttrPort->fragmentDependant = false;
	  	chanDicoAttrPort->optional = false;
<<<<<<< Updated upstream
	  	chanDicoAttrPort->super->super->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanDicoAttrPort->super->super->name, "port");
	  	chanDicoAttrPort->state = false;
	  	chanDicoAttrPort->datatype = my_malloc(sizeof(char) * (strlen("number")) + 1);
	  	strcpy(chanDicoAttrPort->datatype, "number");
	  	chanDicoAttrPort->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	  	chanDicoAttrPort->super->super->name = malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanDicoAttrPort->super->super->name, "port");
	  	chanDicoAttrPort->state = false;
	  	chanDicoAttrPort->datatype = malloc(sizeof(char) * (strlen("number")) + 1);
	  	strcpy(chanDicoAttrPort->datatype, "number");
	  	chanDicoAttrPort->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	  	strcpy(chanDicoAttrPort->defaultValue, "");*/

	/* ChannelType DictionaryAttribute path
	  	DictionaryAttribute* chanDicoAttrPath = new_DictionaryAttribute();
	  	chanDicoAttrPath->fragmentDependant = false;
	  	chanDicoAttrPath->optional = false;
<<<<<<< Updated upstream
	  	chanDicoAttrPath->super->super->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanDicoAttrPath->super->super->name, "path");
	  	chanDicoAttrPath->state = false;
	  	chanDicoAttrPath->datatype = my_malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrPath->datatype, "string");
	  	chanDicoAttrPath->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	  	chanDicoAttrPath->super->super->name = malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanDicoAttrPath->super->super->name, "path");
	  	chanDicoAttrPath->state = false;
	  	chanDicoAttrPath->datatype = malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrPath->datatype, "string");
	  	chanDicoAttrPath->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	  	strcpy(chanDicoAttrPath->defaultValue, "");*/

	/* GroupType DictionaryAttribute port */
	DictionaryAttribute* gtDicAttrPort = new_DictionaryAttribute();
	gtDicAttrPort->fragmentDependant = true;
	gtDicAttrPort->optional = true;
<<<<<<< Updated upstream
	gtDicAttrPort->super->super->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(gtDicAttrPort->super->super->name, "port");
	gtDicAttrPort->state = false;
	gtDicAttrPort->datatype = my_malloc(sizeof(char) * (strlen("number")) + 1);
	strcpy(gtDicAttrPort->datatype, "number");
	gtDicAttrPort->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	gtDicAttrPort->super->super->name = malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(gtDicAttrPort->super->super->name, "port");
	gtDicAttrPort->state = false;
	gtDicAttrPort->datatype = malloc(sizeof(char) * (strlen("number")) + 1);
	strcpy(gtDicAttrPort->datatype, "number");
	gtDicAttrPort->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	strcpy(gtDicAttrPort->defaultValue, "");

	/* GroupType DictionaryAttribute path */
	DictionaryAttribute* gtDicAttrPath = new_DictionaryAttribute();
	gtDicAttrPath->fragmentDependant = true;
	gtDicAttrPath->optional = true;
<<<<<<< Updated upstream
	gtDicAttrPath->super->super->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(gtDicAttrPath->super->super->name, "path");
	gtDicAttrPath->state = false;
	gtDicAttrPath->datatype = my_malloc(sizeof(char) * (strlen("string")) + 1);
	strcpy(gtDicAttrPath->datatype, "string");
	gtDicAttrPath->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	gtDicAttrPath->super->super->name = malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(gtDicAttrPath->super->super->name, "path");
	gtDicAttrPath->state = false;
	gtDicAttrPath->datatype = malloc(sizeof(char) * (strlen("string")) + 1);
	strcpy(gtDicAttrPath->datatype, "string");
	gtDicAttrPath->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	strcpy(gtDicAttrPath->defaultValue, "");

	/* GroupType DictionaryAttribute proxy_port */
	DictionaryAttribute* gtDicAttrProxy = new_DictionaryAttribute();
	gtDicAttrProxy->fragmentDependant = true;
	gtDicAttrProxy->optional = true;
<<<<<<< Updated upstream
	gtDicAttrProxy->super->super->name = my_malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(gtDicAttrProxy->super->super->name, "proxy_port");
	gtDicAttrProxy->state = false;
	gtDicAttrProxy->datatype = my_malloc(sizeof(char) * (strlen("int")) + 1);
	strcpy(gtDicAttrProxy->datatype, "int");
	gtDicAttrProxy->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrProxy->defaultValue, "9000");
=======
	gtDicAttrProxy->super->super->name = malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(gtDicAttrProxy->super->super->name, "proxy_port");
	gtDicAttrProxy->state = false;
	gtDicAttrProxy->datatype = malloc(sizeof(char) * (strlen("int")) + 1);
	strcpy(gtDicAttrProxy->datatype, "int");
	gtDicAttrProxy->defaultValue = malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrProxy->defaultValue, "20000");
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
	/* ComponentInstance DictionaryType FakeConsole
	  		DictionaryType* dtFakeConsole = new_DictionaryType();
	  		dtFakeConsole->AddAttributes(dtFakeConsole, daFakeConsoleProxy);*/

	/* ComponentInstance DictionaryType HelloWorld */
	DictionaryType* dtHelloWorld = new_DictionaryType();
=======
	/* ComponentInstance DictionaryType HelloWorld
		DictionaryType* dtHelloWorld = new_DictionaryType();
		dtHelloWorld->AddAttributes(dtHelloWorld, daHelloWorld);*/

	/* ComponentInstance DictionaryType HelloWorld
		DictionaryType* dtHelloWorld = new_DictionaryType();*/
>>>>>>> Stashed changes

	/* GroupType DictionaryType */
	DictionaryType* gtDicType = new_DictionaryType();
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
<<<<<<< Updated upstream
	kevContikiNode->super->name = my_malloc(sizeof(char) * (strlen("kevoree-contiki-node")) + 1);
	strcpy(kevContikiNode->super->name, "kevoree-contiki-node");
	kevContikiNode->groupName = my_malloc(sizeof(char) * (strlen("org.kevoree.library.c")) + 1);
	strcpy(kevContikiNode->groupName, "org.kevoree.library.c");
	kevContikiNode->hashcode = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevContikiNode->hashcode, "");
	kevContikiNode->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(kevContikiNode->version,"0.0.1");
	kevContikiNode->url = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevContikiNode->url, "");
	kevContikiNode->type = my_malloc(sizeof(char) * (strlen("ce")) + 1);
=======
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
>>>>>>> Stashed changes
	strcpy(kevContikiNode->type,"ce");

	/* DeployUnit //kevoree-group-coap/0.0.1 */
	DeployUnit* kevGroupCoap = new_DeployUnit();
<<<<<<< Updated upstream
	kevGroupCoap->super->name = my_malloc(sizeof(char) * (strlen("kevoree-group-coap")) + 1);
	strcpy(kevGroupCoap->super->name, "kevoree-group-coap");
	kevGroupCoap->groupName = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevGroupCoap->groupName, "");
	kevGroupCoap->hashcode = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevGroupCoap->hashcode, "");
	kevGroupCoap->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(kevGroupCoap->version,"0.0.1");
	kevGroupCoap->url = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(kevGroupCoap->url, "");
	kevGroupCoap->type = my_malloc(sizeof(char) * (strlen("ce")) + 1);
=======
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
>>>>>>> Stashed changes
	strcpy(kevGroupCoap->type,"ce");

	/* DeployUnit //kevoree-chan-coap/0.0.1
	  	DeployUnit* kevChanCoap = new_DeployUnit();
<<<<<<< Updated upstream
	  	kevChanCoap->super->name = my_malloc(sizeof(char) * (strlen("kevoree-chan-coap")) + 1);
	  	strcpy(kevChanCoap->super->name, "kevoree-chan-coap");
	  	kevChanCoap->groupName = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(kevChanCoap->groupName, "");
	  	kevChanCoap->hashcode = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(kevChanCoap->hashcode, "");
	  	kevChanCoap->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  	strcpy(kevChanCoap->version,"0.0.1");
	  	kevChanCoap->url = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(kevChanCoap->url, "");
	  	kevChanCoap->type = my_malloc(sizeof(char) * (strlen("ce")) + 1);
=======
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
>>>>>>> Stashed changes
	  	strcpy(kevChanCoap->type,"ce");*/

	/* DeployUnit //kevoree-comp-fakeconsole/0.0.1
	  		DeployUnit* duFakeConsole = new_DeployUnit();
<<<<<<< Updated upstream
	  		duFakeConsole->super->name = my_malloc(sizeof(char) * (strlen("kevoree-comp-fakeconsole")) + 1);
	  		strcpy(duFakeConsole->super->name, "kevoree-comp-fakeconsole");
	  		duFakeConsole->groupName = my_malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(duFakeConsole->groupName, "");
	  		duFakeConsole->hashcode = my_malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(duFakeConsole->hashcode, "");
	  		duFakeConsole->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  		strcpy(duFakeConsole->version,"0.0.1");
	  		duFakeConsole->url = my_malloc(sizeof(char) * (strlen("")) + 1);
	  		strcpy(duFakeConsole->url, "");
	  		duFakeConsole->type = my_malloc(sizeof(char) * (strlen("ce")) + 1);
	  		strcpy(duFakeConsole->type,"ce");*/

	/* DeployUnit //kevoree-comp-helloworld/0.0.1 */
	DeployUnit* duHelloWorld = new_DeployUnit();
	duHelloWorld->super->name = my_malloc(sizeof(char) * (strlen("kevoree-comp-blink")) + 1);
	strcpy(duHelloWorld->super->name, "kevoree-comp-blink");
	duHelloWorld->groupName = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(duHelloWorld->groupName, "");
	duHelloWorld->hashcode = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(duHelloWorld->hashcode, "");
	duHelloWorld->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(duHelloWorld->version,"0.0.1");
	duHelloWorld->url = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(duHelloWorld->url, "");
	duHelloWorld->type = my_malloc(sizeof(char) * (strlen("ce")) + 1);
	strcpy(duHelloWorld->type,"ce");

	/* PortTypeRef sendMsg
	  		PortTypeRef* ptrSendMsg = new_PortTypeRef();
	  		ptrSendMsg->super->name = my_malloc(sizeof(char) * (strlen("sendMsg")) + 1);
=======
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
>>>>>>> Stashed changes
	  		strcpy(ptrSendMsg->super->name, "sendMsg");
	  		ptrSendMsg->noDependency = true;
	  		ptrSendMsg->optional = true;*/

	/* PortTypeRef inMsg
	  		PortTypeRef* ptrInMsg = new_PortTypeRef();
<<<<<<< Updated upstream
	  		ptrInMsg->super->name = my_malloc(sizeof(char) * (strlen("inMsg")) + 1);
=======
	  		ptrInMsg->super->name = malloc(sizeof(char) * (strlen("inMsg")) + 1);
>>>>>>> Stashed changes
	  		strcpy(ptrInMsg->super->name, "inMsg");
	  		ptrInMsg->noDependency = true;
	  		ptrInMsg->optional = true;*/

<<<<<<< Updated upstream
	/* PortTypeRef sendText */
	PortTypeRef* ptrSendText = new_PortTypeRef();
	ptrSendText->super->name = my_malloc(sizeof(char) * (strlen("sendText")) + 1);
	strcpy(ptrSendText->super->name, "sendText");
	ptrSendText->noDependency = true;
	ptrSendText->optional = true;

	/* PortTypeRef fake */
	PortTypeRef* ptrFake = new_PortTypeRef();
	ptrFake->super->name = my_malloc(sizeof(char) * (strlen("fake")) + 1);
	strcpy(ptrFake->super->name, "fake");
	ptrFake->noDependency = true;
	ptrFake->optional = true;

	/* Port inMsg
	  		Port* pInMsg = new_Port();
	  		pInMsg->super->name = my_malloc(sizeof(char) * (strlen("inMsg")) + 1);
=======
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
>>>>>>> Stashed changes
	  		strcpy(pInMsg->super->name, "inMsg");
	  		pInMsg->AddPortTypeRef(pInMsg, ptrInMsg);*/

	/* Port sendMsg
	  		Port* pSendMsg = new_Port();
<<<<<<< Updated upstream
	  		pSendMsg->super->name = my_malloc(sizeof(char) * (strlen("sendMsg")) + 1);
	  		strcpy(pSendMsg->super->name, "sendMsg");
	  		pSendMsg->AddPortTypeRef(pSendMsg, ptrSendMsg);*/

	/* Port fake */
	Port* pFake = new_Port();
	pFake->super->name = my_malloc(sizeof(char) * (strlen("fake")) + 1);
	strcpy(pFake->super->name, "fake");
	pFake->AddPortTypeRef(pFake, ptrFake);

	/* Port sendMsg */
	Port* pSendText = new_Port();
	pSendText->super->name = my_malloc(sizeof(char) * (strlen("sendText")) + 1);
	strcpy(pSendText->super->name, "sendText");
	pSendText->AddPortTypeRef(pSendText, ptrSendText);
=======
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
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
	coapGroup->super->super->name = my_malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(coapGroup->super->super->name, "CoAPGroup");
	coapGroup->super->started = true;
	coapGroup->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	coapGroup->super->super->name = malloc(sizeof(char) * (strlen("group0")) + 1);
	strcpy(coapGroup->super->super->name, "group0");
	coapGroup->super->started = true;
	coapGroup->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
	strcpy(coapGroup->super->metaData, "");

	/*coapGroup->AddSubNodes(coapGroup, serverNode);*/
	coapGroup->super->AddTypeDefinition(coapGroup->super, coapGroupType);

	/* FragmentDictionary contiki-node */
	FragmentDictionary* contikiNodeFragDico = new_FragmentDictionary();
<<<<<<< Updated upstream
	contikiNodeFragDico->name = my_malloc(sizeof(char) * (strlen("contiki-node")) + 1);
=======
	contikiNodeFragDico->name = malloc(sizeof(char) * (strlen("contiki-node")) + 1);
>>>>>>> Stashed changes
	strcpy(contikiNodeFragDico->name, "contiki-node");

	/* Group DictionaryValue port */
	DictionaryValue* groupValuePort = new_DictionaryValue();
<<<<<<< Updated upstream
	groupValuePort->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(groupValuePort->name, "port");
	groupValuePort->value = my_malloc(sizeof(char) * (strlen("5683")) + 1);
=======
	groupValuePort->name = malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(groupValuePort->name, "port");
	groupValuePort->value = malloc(sizeof(char) * (strlen("5683")) + 1);
>>>>>>> Stashed changes
	strcpy(groupValuePort->value, "5683");

	/* Group DictionaryValue proxy_port */
	DictionaryValue* groupValueProxy = new_DictionaryValue();
<<<<<<< Updated upstream
	groupValueProxy->name = my_malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(groupValueProxy->name, "proxy_port");
	groupValueProxy->value = my_malloc(sizeof(char) * (strlen("9000")) + 1);
	strcpy(groupValueProxy->value, "9000");

	/* Group DictionaryValue path */
	DictionaryValue* groupValuePath = new_DictionaryValue();
	groupValuePath->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(groupValuePath->name, "path");
	groupValuePath->value = my_malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
=======
	groupValueProxy->name = malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(groupValueProxy->name, "proxy_port");
	groupValueProxy->value = malloc(sizeof(char) * (strlen("20000")) + 1);
	strcpy(groupValueProxy->value, "20000");

	/* Group DictionaryValue path */
	DictionaryValue* groupValuePath = new_DictionaryValue();
	groupValuePath->name = malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(groupValuePath->name, "path");
	groupValuePath->value = malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
>>>>>>> Stashed changes
	strcpy(groupValuePath->value, "CoAPGroup");

	/* Adding values to FragmentDictionary ContikiNode */
	contikiNodeFragDico->super->AddValues(contikiNodeFragDico->super, groupValuePort);
	contikiNodeFragDico->super->AddValues(contikiNodeFragDico->super, groupValueProxy);
	contikiNodeFragDico->super->AddValues(contikiNodeFragDico->super, groupValuePath);

	coapGroup->super->AddFragmentDictionary(coapGroup->super, fdContikiNode);

	/* DictionaryType contikiNodeDicType */
	DictionaryType* contikiNodeDicType = new_DictionaryType();
	contikiNodeType->AddDictionaryType(contikiNodeType, contikiNodeDicType);

	/*ComponentInstance* ciFakeConsole = new_ComponentInstance();
<<<<<<< Updated upstream
	  		ciFakeConsole->super->super->name = my_malloc(sizeof(char) * (strlen("fakeconsole")) + 1);
	  		strcpy(ciFakeConsole->super->super->name, "fakeconsole");
	  		ciFakeConsole->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
=======
	  		ciFakeConsole->super->super->name = malloc(sizeof(char) * (strlen("fakeconsole")) + 1);
	  		strcpy(ciFakeConsole->super->super->name, "fakeconsole");
	  		ciFakeConsole->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	ctHelloWorld->AddDeployUnit(ctHelloWorld, duHelloWorld);
=======
	/*ctHelloWorld->AddDeployUnit(ctHelloWorld, duHelloWorld);*/
>>>>>>> Stashed changes
	contikiNodeType->AddDeployUnit(contikiNodeType, kevContikiNode);
	coapGroupType->AddDeployUnit(coapGroupType, kevGroupCoap);
	/*coapChanType->AddDeployUnit(coapChanType, kevChanCoap);*/

	/*ctFakeConsole->AddDictionaryType(ctFakeConsole, dtFakeConsole);*/
<<<<<<< Updated upstream
	ctHelloWorld->AddDictionaryType(ctHelloWorld, dtHelloWorld);
=======
	/*ctHelloWorld->AddDictionaryType(ctHelloWorld, dtHelloWorld);*/
>>>>>>> Stashed changes
	coapGroupType->AddDictionaryType(coapGroupType, gtDicType);
	/*coapChanType->AddDictionaryType(coapChanType, chanDicType);*/

	/*defaultChannel->AddBindings(defaultChannel, mbInMsg);*/
	/*defaultChannel->AddBindings(defaultChannel, mbFake);*/
	/*defaultChannel->AddBindings(defaultChannel, mbSendMsg);*/
	/*defaultChannel->AddBindings(defaultChannel, mbSendText);*/

	/*((ComponentType*)ctFakeConsole->pDerivedObj)->AddProvided((ComponentType*)ctFakeConsole->pDerivedObj, ptrInMsg);
	  		((ComponentType*)ctFakeConsole->pDerivedObj)->AddRequired((ComponentType*)ctFakeConsole->pDerivedObj, ptrSendMsg);*/
<<<<<<< Updated upstream


	/*for(int i = 0; i < 20; i++)
	  		{*/

	/*model->AddNodes(model, contikiNode);*/
	/*model->AddNodes(model, serverNode);
	  		model->AddTypeDefinitions(model, ctFakeConsole);*/
	/*model->AddTypeDefinitions(model, ctHelloWorld);
	  	model->AddTypeDefinitions(model, contikiNodeType);
	  	model->AddTypeDefinitions(model, coapGroupType);
	  	model->AddTypeDefinitions(model, coapChanType);
	  	model->AddLibraries(model, contiki);
	  	model->AddHubs(model, defaultChannel);*/

	/*model->AddBindings(model, mbInMsg);*/
	/*model->AddBindings(model, mbFake);*/
	/*model->AddBindings(model, mbSendMsg);*/
	/*model->AddBindings(model, mbSendText);*/

	/*model->AddDeployUnits(model, duFakeConsole);*/
	/*model->AddDeployUnits(model, duHelloWorld);
	  	model->AddDeployUnits(model, kevContikiNode);
	  	model->AddDeployUnits(model, kevGroupCoap);
	  	model->AddDeployUnits(model, kevChanCoap);
	  	model->AddGroups(model, coapGroup);*/

	/*printf("Model %s created with success!\n\n", model->InternalGetKey(model));*/

	/*model2->AddNodes(model2, contikiNode);
	  		model2->AddNodes(model2, serverNode);
	  		model2->AddTypeDefinitions(model2, ctFakeConsole);
	  		model2->AddTypeDefinitions(model2, ctHelloWorld);
	  		model2->AddTypeDefinitions(model2, contikiNodeType);
	  		model2->AddTypeDefinitions(model2, coapGroupType);
	  		model2->AddTypeDefinitions(model2, coapChanType);
	  		model2->AddLibraries(model2, contiki);
	  		model2->AddHubs(model2, defaultChannel);
	  		model2->AddBindings(model2, mbInMsg);
	  		model2->AddBindings(model2, mbFake);
	  		model2->AddBindings(model2, mbSendMsg);
	  		model2->AddBindings(model2, mbSendText);
	  		model2->AddDeployUnits(model2, duFakeConsole);
	  		model2->AddDeployUnits(model2, duHelloWorld);
	  		model2->AddDeployUnits(model2, kevContikiNode);
	  		model2->AddDeployUnits(model2, kevGroupCoap);
	  		model2->AddDeployUnits(model2, kevChanCoap);
	  		model2->AddGroups(model2, coapGroup);
	  		model2->AddNodes(model2, contikiNode);*/

	/*printf("Model %s created with success! \n\n", model2->InternalGetKey(model2));*/

	Visitor* visitor_print = (Visitor*)my_malloc(sizeof(Visitor));

	visitor_print->action =  actionprintf;
	/*visitor_print->action =  ActionCompare;*/

	/*model->Visit(model, visitor_print);*/
	/*printf("\nVisiting model2 \n\n");
	  		model2->Visit(model2, visitor_print);*/
	//	printf("Process finished!\n\n");

	ContainerRoot* modelX = new_ContainerRoot();

	modelX->AddLibraries(modelX, contiki);

	/*type definition*/
	modelX->AddTypeDefinitions(modelX, ctHelloWorld);
	modelX->AddTypeDefinitions(modelX, contikiNodeType);
	modelX->AddTypeDefinitions(modelX, coapGroupType);



	/*deploy unit*/
	modelX->AddDeployUnits(modelX, duHelloWorld);
	modelX->AddDeployUnits(modelX, kevContikiNode);
	modelX->AddDeployUnits(modelX, kevGroupCoap);


	/*instances*/
	modelX->AddGroups(modelX, coapGroup);
=======
	/*((ComponentType*)ctHelloWorld->pDerivedObj)->AddProvided((ComponentType*)ctHelloWorld->pDerivedObj, ptrFake);
	  	((ComponentType*)ctHelloWorld->pDerivedObj)->AddRequired((ComponentType*)ctHelloWorld->pDerivedObj, ptrSendText);*/

	current_model = new_ContainerRoot();

	current_model->AddLibraries(current_model, contiki);
	current_model->AddLibraries(current_model, defLib);

	/*type definition*/
	current_model->AddTypeDefinitions(current_model, contikiNodeType);
	current_model->AddTypeDefinitions(current_model, coapGroupType);
	/*current_model->AddTypeDefinitions(current_model, ctHelloWorld);*/

	/*deploy unit*/
	/*modelX->AddDeployUnits(modelX, duHelloWorld);*/
	current_model->AddDeployUnits(current_model, kevContikiNode);
	current_model->AddDeployUnits(current_model, kevGroupCoap);
	/*current_model->AddDeployUnits(current_model, duHelloWorld);*/


	/*instances*/
	current_model->AddGroups(current_model, coapGroup);
>>>>>>> Stashed changes

	int i = 0;
	int j = 0;

	for(i = 0; i < 1; i++)
	{
		/* ContainerNode contikiNode */
		ContainerNode* contikiNode = new_ContainerNode();
<<<<<<< Updated upstream
		contikiNode->super->super->name = my_malloc(sizeof(char) * (strlen("XX")) + 1);
		sprintf(contikiNode->super->super->name, "%d", i);
		contikiNode->super->started = true;
		contikiNode->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(contikiNode->super->metaData, "");

		/*contiki->AddSubTypes(contiki, coapChanType);*/
		contikiNode->AddNetworkInformation(contikiNode, contikiNodeIP);
		contikiNode->super->AddTypeDefinition(contikiNode->super, contikiNodeType);
		contikiNode->AddGroups(contikiNode, coapGroup);

		for(j = 0; j < 1; j++)
		{
			ComponentInstance* ciHelloWorld = new_ComponentInstance();
			ciHelloWorld->super->super->name = my_malloc(sizeof(char) * (strlen("XX")) + 1);
			sprintf(ciHelloWorld->super->super->name, "%d", j);
			ciHelloWorld->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
			strcpy(ciHelloWorld->super->metaData, "");
			ciHelloWorld->super->started = true;


			ciHelloWorld->super->AddTypeDefinition(ciHelloWorld->super, ctHelloWorld);

			((ComponentType*)ctHelloWorld->pDerivedObj)->AddProvided(ctHelloWorld->pDerivedObj, ptrFake);
			((ComponentType*)ctHelloWorld->pDerivedObj)->AddRequired(ctHelloWorld->pDerivedObj, ptrSendText);
			contikiNode->AddComponents(contikiNode, ciHelloWorld);
			ciHelloWorld->AddProvided(ciHelloWorld, pFake);
			ciHelloWorld->AddRequired(ciHelloWorld, pSendText);

		}

		coapGroup->AddSubNodes(coapGroup, contikiNode);

		modelX->AddNodes(modelX, contikiNode);
		/*printf("%d\n", mem_count);*/
	}



	/*printf("Elapsed time: %d\n", RTIMER_NOW());*/
	modelX->Visit(modelX, visitor_print);

	/*modelX->Visit(modelX, visitor_print);*/

	return 0;
=======
		contikiNode->super->super->name = malloc(sizeof(char) * (strlen("nodeX")) + 1);
		sprintf(contikiNode->super->super->name, "node%d", i);
		contikiNode->super->started = true;
		contikiNode->super->metaData = malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(contikiNode->super->metaData, "");

		/*contiki->AddSubTypes(contiki, coapChanType);*/
		contikiNode->AddNetworkInformation(contikiNode, serverNodeIP);
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


		current_model->AddNodes(current_model, contikiNode);
		/*printf("%d\n", mem_count);*/
	}

	visitor_print = (Visitor*)malloc(sizeof(Visitor));

	/*visitor_print->action = actionstore;*/
	visitor_print->action = actionprintf;
	/*visitor_print->action = actionprintpath;*/
	current_model->Visit(current_model, visitor_print);

	return EXIT_SUCCESS;
>>>>>>> Stashed changes
}
