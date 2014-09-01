/*#include "DefaultFactorykevoree.h"
#include "Comparekevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include "kevoree.h"

ContainerRoot* model = NULL;
ContainerRoot* model2 = NULL;

void ActionCompare(char* _path, Type type, void* value)
{
	char* path = strdup(_path);
	switch(type)
	{
		case STRING:
			printf("path = %s  value = %s\n", path, (char*)value);
			/*if(indexOf(path,"/") != -1)*/
			path = strtok(path, "\\");
			/*printf("Simple path: %s\n", path);*/
			/*char* string = model2->FindByPath(path, model2);
			printf("Attribute value: %s\n", string);*/
			if(model2->FindByPath(path, model2) == NULL)
			{
				printf("Path %s does not exist in model, removing...\n\n", path);
			}
			else
			{
				printf("path = %s  value = %s\n", _path, (char*)value);
				char* string = model->FindByPath(_path, model);
				char* string2 = model2->FindByPath(_path, model2);
				printf("Current attribute value: %s\n", string);
				printf("New attribute value: %s\n", string2);
				if(string != NULL && string2 != NULL)
				{
					if(!strcmp(string2, string))
					{
						printf("Identical attributes, nothing to change...\n\n");
					}
					else
					{
						printf("Changing attribute to %s in current model\n\n", string2);
					}
				}
				else if(string == NULL && string2 != NULL)
				{
					printf("Current attribute is NULL, changing to new attribute '%s'\n\n", string2);
				}
				else if(string != NULL && string2 == NULL)
				{
					printf("Changing attribute to NULL\n\n");
				}
				else
				{
					printf("Both attributes are NULL, nothing to change\n\n");
				}
			}
			break;

		case BOOL:
			printf("path = %s  value = %d\n", path, (int)value);
			path = strtok(path, "\\");
			/*printf("Simple path: %s\n", path);*/
			/*int v = model->FindByPath(path, model);*/
			if(model2->FindByPath(path, model2) == NULL)
			{
				printf("Path %s does not exist in model, removing...\n\n", path);
			}
			else
			{
				int v = model->FindByPath(_path, model);
				int v2 = model2->FindByPath(_path, model2);
				printf("Current attribute value: %d\n", v);
				printf("New attribute value: %d\n", v2);
				if(v == v2)
				{
					printf("Identical attributes, nothing to change...\n\n");
				}
				else
				{
					printf("Changing attribute to %s in current model\n\n", v2);
				}

			}
			break;
	}
}
/*KevoreeBootStrap *kb=NULL;*/

int main(void)
{
	printf("Starting kevoree C implementation\n");

	model = new_ContainerRoot();
	model2 = new_ContainerRoot();

	/* ContainerNode contikiNode */
	ContainerNode* contikiNode = new_ContainerNode();
	contikiNode->super->super->name = malloc(sizeof(char) * (strlen("contiki-node") + 1));
	strcpy(contikiNode->super->super->name, "contiki-node");
	contikiNode->super->started = 1;
	contikiNode->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(contikiNode->super->metaData, "");

	/* ContainerNode contikiNode */
	ContainerNode* serverNode = new_ContainerNode();
	serverNode->super->super->name = malloc(sizeof(char) * (strlen("server-node") + 1));
	strcpy(serverNode->super->super->name, "server-node");
	serverNode->super->started = 1;
	serverNode->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(serverNode->super->metaData, "");

	/* NeworkProperty front */
	NetworkProperty* contikiNodeFront = new_NetworkProperty();
	contikiNodeFront->super->name = malloc(sizeof(char) * (strlen("front") + 1));
	strcpy(contikiNodeFront->super->name, "front");
	contikiNodeFront->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org") + 1));
	strcpy(contikiNodeFront->value, "contiki.kevoree.org");

	/* NeworkProperty local */
	NetworkProperty* contikiNodeLocal = new_NetworkProperty();
	contikiNodeLocal->super->name = malloc(sizeof(char) * (strlen("local") + 1));
	strcpy(contikiNodeLocal->super->name, "local");
	contikiNodeLocal->value = malloc(sizeof(char) * (strlen("aaaa::0:0:3") + 1));
	strcpy(contikiNodeLocal->value, "aaaa::0:0:3");

	/* NeworkProperty front */
	NetworkProperty* serverNodeFront = new_NetworkProperty();
	serverNodeFront->super->name = malloc(sizeof(char) * (strlen("front") + 1));
	strcpy(serverNodeFront->super->name, "front");
	serverNodeFront->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org") + 1));
	strcpy(serverNodeFront->value, "contiki.kevoree.org");

	/* NeworkProperty local */
	NetworkProperty* serverNodeLocal = new_NetworkProperty();
	serverNodeLocal->super->name = malloc(sizeof(char) * (strlen("local") + 1));
	strcpy(serverNodeLocal->super->name, "local");
	serverNodeLocal->value = malloc(sizeof(char) * (strlen("aaaa::0:0:3") + 1));
	strcpy(serverNodeLocal->value, "aaaa::0:0:5");

	/* NetworkInfo ip */
	NetworkInfo* contikiNodeIP = new_NetworkInfo();
	contikiNodeIP->super->name = malloc(sizeof(char) * (strlen("ip") + 1));
	strcpy(contikiNodeIP->super->name, "ip");

	contikiNodeIP->AddValues(contikiNodeIP, contikiNodeFront);
	contikiNodeIP->AddValues(contikiNodeIP, contikiNodeLocal);

	/* NetworkInfo ip */
	NetworkInfo* serverNodeIP = new_NetworkInfo();
	serverNodeIP->super->name = malloc(sizeof(char) * (strlen("ip") + 1));
	strcpy(serverNodeIP->super->name, "ip");

	serverNodeIP->AddValues(serverNodeIP, serverNodeFront);
	serverNodeIP->AddValues(serverNodeIP, serverNodeLocal);

	contikiNode->AddNetworkInformation(contikiNode, contikiNodeIP);
	serverNode->AddNetworkInformation(serverNode, serverNodeIP);

	/* TypeDefinition ContikiNode/1.0.0 */
	TypeDefinition* contikiNodeType = newPoly_NodeType();
	contikiNodeType->super->name = malloc(sizeof(char) * (strlen("ContikiNode") + 1));
	strcpy(contikiNodeType->super->name, "ContikiNode");
	contikiNodeType->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(contikiNodeType->version, "0.0.1");
	contikiNodeType->bean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(contikiNodeType->bean, "");
	contikiNodeType->factoryBean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(contikiNodeType->factoryBean, "");

	contikiNode->super->AddTypeDefinition(contikiNode->super, contikiNodeType);
	serverNode->super->AddTypeDefinition(serverNode->super, contikiNodeType);

	/* TypeDefinition CoAPGroup/1.0.0 */
	TypeDefinition* coapGroupType = newPoly_GroupType();
	coapGroupType->abstract = 0;
	coapGroupType->super->name = malloc(sizeof(char) * (strlen("CoAPGroup") + 1));
	strcpy(coapGroupType->super->name, "CoAPGroup");
	coapGroupType->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(coapGroupType->version, "0.0.1");
	coapGroupType->bean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(coapGroupType->bean, "");
	coapGroupType->factoryBean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(coapGroupType->factoryBean, "");

	/* TypeDefinition CoAPChan/0.0.1 */
	TypeDefinition* coapChanType = newPoly_ChannelType();
	coapChanType->abstract = 0;
	coapChanType->super->name = malloc(sizeof(char) * (strlen("CoAPChan") + 1));
	strcpy(coapChanType->super->name, "CoAPChan");
	coapChanType->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(coapChanType->version, "0.0.1");
	coapChanType->bean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(coapChanType->bean, "");
	coapChanType->factoryBean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(coapChanType->factoryBean, "");
	((ChannelType*)coapChanType->pDerivedObj)->upperBindings = 0;
	((ChannelType*)coapChanType->pDerivedObj)->lowerBindings = 0;
	((ChannelType*)coapChanType->pDerivedObj)->upperFragments = 0;
	((ChannelType*)coapChanType->pDerivedObj)->lowerFragments = 0;

	/* TypeDefinition FakeConsoleType */
	TypeDefinition* ctFakeConsole = newPoly_ComponentType();
	ctFakeConsole->abstract = 0;
	ctFakeConsole->super->name = malloc(sizeof(char) * (strlen("FakeConsole") + 1));
	strcpy(ctFakeConsole->super->name, "FakeConsole");
	ctFakeConsole->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(ctFakeConsole->version, "0.0.1");
	ctFakeConsole->bean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(ctFakeConsole->bean, "");
	ctFakeConsole->factoryBean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(ctFakeConsole->factoryBean, "");

	/* TypeDefinition HelloWorldType */
	TypeDefinition* ctHelloWorld = newPoly_ComponentType();
	ctHelloWorld->abstract = 0;
	ctHelloWorld->super->name = malloc(sizeof(char) * (strlen("HelloWorld") + 1));
	strcpy(ctHelloWorld->super->name, "HelloWorld");
	ctHelloWorld->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(ctHelloWorld->version, "0.0.1");
	ctHelloWorld->bean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(ctHelloWorld->bean, "");
	ctHelloWorld->factoryBean = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(ctHelloWorld->factoryBean, "");

	/* TypeLibrary Contiki */
	TypeLibrary* contiki = new_TypeLibrary();
	contiki->super->name = malloc(sizeof(char) * (strlen("Contiki")) + 1);
	strcpy(contiki->super->name, "Contiki");
	contiki->AddSubTypes(contiki, ctFakeConsole);
	contiki->AddSubTypes(contiki, ctHelloWorld);
	contiki->AddSubTypes(contiki, contikiNodeType);
	contiki->AddSubTypes(contiki, coapGroupType);
	contiki->AddSubTypes(contiki, coapChanType);

	/* TypeLibrary Default */
	TypeLibrary* defLib = new_TypeLibrary();
	defLib->super->name = malloc(sizeof(char) * (strlen("Default")) + 1);
	strcpy(defLib->super->name, "Default");

	/* Channel CoAPChannel */
	Channel* defaultChannel = new_Channel();
	defaultChannel->super->super->name = malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	strcpy(defaultChannel->super->super->name, "DefaultChannel");
	defaultChannel->super->started = 1;
	defaultChannel->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(defaultChannel->super->metaData, "");

	/* Channel FragmentDictionary server-node */
	FragmentDictionary* fdChannelServerNode = new_FragmentDictionary();
	fdChannelServerNode->name = malloc(sizeof(char) * (strlen("server-node")) + 1);
	strcpy(fdChannelServerNode->name, "server-node");

	/* Channel FragmentDictionary server-node */
	FragmentDictionary* fdChannelContikiNode = new_FragmentDictionary();
	fdChannelContikiNode->name = malloc(sizeof(char) * (strlen("contiki-node")) + 1);
	strcpy(fdChannelContikiNode->name, "contiki-node");

	defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelContikiNode);
	defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelServerNode);

	/* Channel DictionaryValue host */
	DictionaryValue* chanValueHost = new_DictionaryValue();
	chanValueHost->name = malloc(sizeof(char) * (strlen("host") + 1));
	strcpy(chanValueHost->name, "host");
	chanValueHost->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
	strcpy(chanValueHost->value, "contiki.kevoree.org");

	/* Channel DictionaryValue port */
	DictionaryValue* chanValuePort = new_DictionaryValue();
	chanValuePort->name = malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(chanValuePort->name, "port");
	chanValuePort->value = malloc(sizeof(char) * (strlen("80")) + 1);
	strcpy(chanValuePort->value, "80");

	/* Channel DictionaryValue path */
	DictionaryValue* chanValuePath = new_DictionaryValue();
	chanValuePath->name = malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(chanValuePath->name, "path");
	chanValuePath->value = malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	strcpy(chanValuePath->value, "DefaultChannel");

	/* Channel Dictionary */
	Dictionary* chanDico = new_Dictionary();
	chanDico->AddValues(chanDico, chanValueHost);
	chanDico->AddValues(chanDico, chanValuePort);
	chanDico->AddValues(chanDico, chanValuePath);

	defaultChannel->super->AddDictionary(defaultChannel->super, chanDico);
	defaultChannel->super->AddTypeDefinition(defaultChannel->super, coapChanType);

	/* ComponentType DictionaryAttribute FakeConsole */
	DictionaryAttribute* daFakeConsoleProxy = new_DictionaryAttribute();
	daFakeConsoleProxy->fragmentDependant = 0;
	daFakeConsoleProxy->optional = 1;
	daFakeConsoleProxy->super->super->name = malloc(sizeof(char) * (strlen("proxy")) + 1);
	strcpy(daFakeConsoleProxy->super->super->name, "proxy");
	daFakeConsoleProxy->state = 0;
	daFakeConsoleProxy->datatype = malloc(sizeof(char) * (strlen("boolean")) + 1);
	strcpy(daFakeConsoleProxy->datatype, "boolean");
	daFakeConsoleProxy->defaultValue = malloc(sizeof(char) * (strlen("false")) + 1);
	strcpy(daFakeConsoleProxy->defaultValue, "false");

	/* ChannelType DictionaryAttribute host */
	DictionaryAttribute* chanDicoAttrHost = new_DictionaryAttribute();
	chanDicoAttrHost->fragmentDependant = 0;
	chanDicoAttrHost->optional = 0;
	chanDicoAttrHost->super->super->name = malloc(sizeof(char) * (strlen("host") + 1));
	strcpy(chanDicoAttrHost->super->super->name, "host");
	chanDicoAttrHost->state = 0;
	chanDicoAttrHost->datatype = malloc(sizeof(char) * (strlen("string") + 1));
	strcpy(chanDicoAttrHost->datatype, "string");
	chanDicoAttrHost->defaultValue = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(chanDicoAttrHost->defaultValue, "");

	/* ChannelType DictionaryAttribute port */
	DictionaryAttribute* chanDicoAttrPort = new_DictionaryAttribute();
	chanDicoAttrPort->fragmentDependant = 0;
	chanDicoAttrPort->optional = 0;
	chanDicoAttrPort->super->super->name = malloc(sizeof(char) * (strlen("port") + 1));
	strcpy(chanDicoAttrPort->super->super->name, "port");
	chanDicoAttrPort->state = 0;
	chanDicoAttrPort->datatype = malloc(sizeof(char) * (strlen("number") + 1));
	strcpy(chanDicoAttrPort->datatype, "number");
	chanDicoAttrPort->defaultValue = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(chanDicoAttrPort->defaultValue, "");

	/* ChannelType DictionaryAttribute path */
	DictionaryAttribute* chanDicoAttrPath = new_DictionaryAttribute();
	chanDicoAttrPath->fragmentDependant = 0;
	chanDicoAttrPath->optional = 0;
	chanDicoAttrPath->super->super->name = malloc(sizeof(char) * (strlen("path") + 1));
	strcpy(chanDicoAttrPath->super->super->name, "path");
	chanDicoAttrPath->state = 0;
	chanDicoAttrPath->datatype = malloc(sizeof(char) * (strlen("string") + 1));
	strcpy(chanDicoAttrPath->datatype, "string");
	chanDicoAttrPath->defaultValue = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(chanDicoAttrPath->defaultValue, "");

	/* GroupType DictionaryAttribute port */
	DictionaryAttribute* gtDicAttrPort = new_DictionaryAttribute();
	gtDicAttrPort->fragmentDependant = 1;
	gtDicAttrPort->optional = 1;
	gtDicAttrPort->super->super->name = malloc(sizeof(char) * (strlen("port") + 1));
	strcpy(gtDicAttrPort->super->super->name, "port");
	gtDicAttrPort->state = 0;
	gtDicAttrPort->datatype = malloc(sizeof(char) * (strlen("number") + 1));
	strcpy(gtDicAttrPort->datatype, "number");
	gtDicAttrPort->defaultValue = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(gtDicAttrPort->defaultValue, "");

	/* GroupType DictionaryAttribute path */
	DictionaryAttribute* gtDicAttrPath = new_DictionaryAttribute();
	gtDicAttrPath->fragmentDependant = 1;
	gtDicAttrPath->optional = 1;
	gtDicAttrPath->super->super->name = malloc(sizeof(char) * (strlen("path") + 1));
	strcpy(gtDicAttrPath->super->super->name, "path");
	gtDicAttrPath->state = 0;
	gtDicAttrPath->datatype = malloc(sizeof(char) * (strlen("string") + 1));
	strcpy(gtDicAttrPath->datatype, "string");
	gtDicAttrPath->defaultValue = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(gtDicAttrPath->defaultValue, "");

	/* GroupType DictionaryAttribute proxy_port */
	DictionaryAttribute* gtDicAttrProxy = new_DictionaryAttribute();
	gtDicAttrProxy->fragmentDependant = 1;
	gtDicAttrProxy->optional = 1;
	gtDicAttrProxy->super->super->name = malloc(sizeof(char) * (strlen("proxy_port") + 1));
	strcpy(gtDicAttrProxy->super->super->name, "proxy_port");
	gtDicAttrProxy->state = 0;
	gtDicAttrProxy->datatype = malloc(sizeof(char) * (strlen("number") + 1));
	strcpy(gtDicAttrProxy->datatype, "number");
	gtDicAttrProxy->defaultValue = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(gtDicAttrProxy->defaultValue, "");

	/* ComponentInstance DictionaryType FakeConsole */
	DictionaryType* dtFakeConsole = new_DictionaryType();
	dtFakeConsole->AddAttributes(dtFakeConsole, daFakeConsoleProxy);

	/* ComponentInstance DictionaryType HelloWorld */
	DictionaryType* dtHelloWorld = new_DictionaryType();

	/* GroupType DictionaryType */
	DictionaryType* gtDicType = new_DictionaryType();
	gtDicType->AddAttributes(gtDicType, gtDicAttrPort);
	gtDicType->AddAttributes(gtDicType, gtDicAttrPath);
	gtDicType->AddAttributes(gtDicType, gtDicAttrProxy);

	/* ChannelType DictionaryType */
	DictionaryType* chanDicType = new_DictionaryType();
	chanDicType->AddAttributes(chanDicType, chanDicoAttrHost);
	chanDicType->AddAttributes(chanDicType, chanDicoAttrPort);
	chanDicType->AddAttributes(chanDicType, chanDicoAttrPath);

	/* DeployUnit //kevoree-contiki-node/0.0.1 */
	DeployUnit* kevContikiNode = new_DeployUnit();
	kevContikiNode->super->name = malloc(sizeof(char) * (strlen("kevoree-contiki-node") + 1));
	strcpy(kevContikiNode->super->name, "kevoree-contiki-node");
	kevContikiNode->groupName = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevContikiNode->groupName, "");
	kevContikiNode->hashcode = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevContikiNode->hashcode, "");
	kevContikiNode->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(kevContikiNode->version,"0.0.1");
	kevContikiNode->url = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevContikiNode->url, "");
	kevContikiNode->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(kevContikiNode->type,"ce");

	/* DeployUnit //kevoree-group-coap/0.0.1 */
	DeployUnit* kevGroupCoap = new_DeployUnit();
	kevGroupCoap->super->name = malloc(sizeof(char) * (strlen("kevoree-group-coap") + 1));
	strcpy(kevGroupCoap->super->name, "kevoree-group-coap");
	kevGroupCoap->groupName = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevGroupCoap->groupName, "");
	kevGroupCoap->hashcode = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevGroupCoap->hashcode, "");
	kevGroupCoap->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(kevGroupCoap->version,"0.0.1");
	kevGroupCoap->url = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevGroupCoap->url, "");
	kevGroupCoap->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(kevGroupCoap->type,"ce");

	/* DeployUnit //kevoree-chan-coap/0.0.1 */
	DeployUnit* kevChanCoap = new_DeployUnit();
	kevChanCoap->super->name = malloc(sizeof(char) * (strlen("kevoree-chan-coap") + 1));
	strcpy(kevChanCoap->super->name, "kevoree-chan-coap");
	kevChanCoap->groupName = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevChanCoap->groupName, "");
	kevChanCoap->hashcode = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevChanCoap->hashcode, "");
	kevChanCoap->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(kevChanCoap->version,"0.0.1");
	kevChanCoap->url = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevChanCoap->url, "");
	kevChanCoap->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(kevChanCoap->type,"ce");

	/* DeployUnit //kevoree-comp-fakeconsole/0.0.1 */
	DeployUnit* duFakeConsole = new_DeployUnit();
	duFakeConsole->super->name = malloc(sizeof(char) * (strlen("kevoree-comp-fakeconsole") + 1));
	strcpy(duFakeConsole->super->name, "kevoree-comp-fakeconsole");
	duFakeConsole->groupName = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(duFakeConsole->groupName, "");
	duFakeConsole->hashcode = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(duFakeConsole->hashcode, "");
	duFakeConsole->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(duFakeConsole->version,"0.0.1");
	duFakeConsole->url = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(duFakeConsole->url, "");
	duFakeConsole->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(duFakeConsole->type,"ce");

	/* DeployUnit //kevoree-comp-helloworld/0.0.1 */
	DeployUnit* duHelloWorld = new_DeployUnit();
	duHelloWorld->super->name = malloc(sizeof(char) * (strlen("kevoree-comp-helloworld") + 1));
	strcpy(duHelloWorld->super->name, "kevoree-comp-helloworld");
	duHelloWorld->groupName = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(duHelloWorld->groupName, "");
	duHelloWorld->hashcode = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(duHelloWorld->hashcode, "");
	duHelloWorld->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(duHelloWorld->version,"0.0.1");
	duHelloWorld->url = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(duHelloWorld->url, "");
	duHelloWorld->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(duHelloWorld->type,"ce");

	/* PortTypeRef sendMsg */
	PortTypeRef* ptrSendMsg = new_PortTypeRef();
	ptrSendMsg->super->name = malloc(sizeof(char) * (strlen("sendMsg") + 1));
	strcpy(ptrSendMsg->super->name, "sendMsg");
	ptrSendMsg->noDependency = 1;
	ptrSendMsg->optional = 1;

	/* PortTypeRef inMsg */
	PortTypeRef* ptrInMsg = new_PortTypeRef();
	ptrInMsg->super->name = malloc(sizeof(char) * (strlen("inMsg") + 1));
	strcpy(ptrInMsg->super->name, "inMsg");
	ptrInMsg->noDependency = 1;
	ptrInMsg->optional = 1;

	/* PortTypeRef sendText */
	PortTypeRef* ptrSendText = new_PortTypeRef();
	ptrSendText->super->name = malloc(sizeof(char) * (strlen("sendText") + 1));
	strcpy(ptrSendText->super->name, "sendText");
	ptrSendText->noDependency = 1;
	ptrSendText->optional = 1;

	/* PortTypeRef fake */
	PortTypeRef* ptrFake = new_PortTypeRef();
	ptrFake->super->name = malloc(sizeof(char) * (strlen("fake") + 1));
	strcpy(ptrFake->super->name, "fake");
	ptrFake->noDependency = 1;
	ptrFake->optional = 1;

	/* Port inMsg */
	Port* pInMsg = new_Port();
	pInMsg->super->name = malloc(sizeof(char) * (strlen("inMsg") + 1));
	strcpy(pInMsg->super->name, "inMsg");
	pInMsg->AddPortTypeRef(pInMsg, ptrInMsg);

	/* Port sendMsg */
	Port* pSendMsg = new_Port();
	pSendMsg->super->name = malloc(sizeof(char) * (strlen("sendMsg") + 1));
	strcpy(pSendMsg->super->name, "sendMsg");
	pSendMsg->AddPortTypeRef(pSendMsg, ptrSendMsg);

	/* Port fake */
	Port* pFake = new_Port();
	pFake->super->name = malloc(sizeof(char) * (strlen("fake") + 1));
	strcpy(pFake->super->name, "fake");
	pFake->AddPortTypeRef(pFake, ptrFake);

	/* Port sendMsg */
	Port* pSendText = new_Port();
	pSendText->super->name = malloc(sizeof(char) * (strlen("sendText") + 1));
	strcpy(pSendText->super->name, "sendText");
	pSendText->AddPortTypeRef(pSendText, ptrSendText);

	/* MBinding inMsg */
	MBinding* mbInMsg = new_MBinding();
	mbInMsg->AddHub(mbInMsg, defaultChannel);
	mbInMsg->AddPort(mbInMsg, pInMsg);
	pInMsg->AddBindings(pInMsg, mbInMsg);

	/* MBinding fake */
	MBinding* mbFake = new_MBinding();
	mbFake->AddHub(mbFake, defaultChannel);
	mbFake->AddPort(mbFake, pFake);
	pFake->AddBindings(pFake, mbFake);

	/* MBinding sendMsg */
	MBinding* mbSendMsg = new_MBinding();
	mbSendMsg->AddHub(mbSendMsg, defaultChannel);
	mbSendMsg->AddPort(mbSendMsg, pSendMsg);
	pSendMsg->AddBindings(pSendMsg, mbSendMsg);

	/* MBinding sendText */
	MBinding* mbSendText = new_MBinding();
	mbSendText->AddHub(mbSendText, defaultChannel);
	mbSendText->AddPort(mbSendText, pSendText);
	pSendText->AddBindings(pSendText, mbSendText);

	/* Group CoAP */
	Group* coapGroup = new_Group();
	coapGroup->super->super->name = malloc(sizeof(char) * (strlen("CoAPGroup") + 1));
	strcpy(coapGroup->super->super->name, "CoAPGroup");
	coapGroup->super->started = 1;
	coapGroup->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(coapGroup->super->metaData, "");

	coapGroup->AddSubNodes(coapGroup, contikiNode);
	coapGroup->AddSubNodes(coapGroup, serverNode);
	coapGroup->super->AddTypeDefinition(coapGroup->super, coapGroupType);

	/* FragmentDictionary contiki-node */
	FragmentDictionary* contikiNodeFragDico = new_FragmentDictionary();
	contikiNodeFragDico->name = malloc(sizeof(char) * (strlen("contiki-node") + 1));
	strcpy(contikiNodeFragDico->name, "contiki-node");

	/* Group DictionaryValue port */
	DictionaryValue* groupValuePort = new_DictionaryValue();
	groupValuePort->name = malloc(sizeof(char) * (strlen("port") + 1));
	strcpy(groupValuePort->name, "port");
	groupValuePort->value = malloc(sizeof(char) * (strlen("5683") + 1));
	strcpy(groupValuePort->value, "5683");

	/* Group DictionaryValue proxy_port */
	DictionaryValue* groupValueProxy = new_DictionaryValue();
	groupValueProxy->name = malloc(sizeof(char) * (strlen("proxy_port") + 1));
	strcpy(groupValueProxy->name, "proxy_port");
	groupValueProxy->value = malloc(sizeof(char) * (strlen("9000") + 1));
	strcpy(groupValueProxy->value, "9000");

	/* Group DictionaryValue path */
	DictionaryValue* groupValuePath = new_DictionaryValue();
	groupValuePath->name = malloc(sizeof(char) * (strlen("path") + 1));
	strcpy(groupValuePath->name, "path");
	groupValuePath->value = malloc(sizeof(char) * (strlen("CoAPGroup") + 1));
	strcpy(groupValuePath->value, "CoAPGroup");

	/* Adding values to FragmentDictionary ContikiNode */
	contikiNodeFragDico->super->AddValues(contikiNodeFragDico->super, groupValuePort);
	contikiNodeFragDico->super->AddValues(contikiNodeFragDico->super, groupValueProxy);
	contikiNodeFragDico->super->AddValues(contikiNodeFragDico->super, groupValuePath);

	coapGroup->super->AddFragmentDictionary(coapGroup->super, contikiNodeFragDico);

	/* DictionaryType contikiNodeDicType */
	DictionaryType* contikiNodeDicType = new_DictionaryType();
	contikiNodeType->AddDictionaryType(contikiNodeType, contikiNodeDicType);

	ComponentInstance* ciFakeConsole = new_ComponentInstance();
	ciFakeConsole->super->super->name = malloc(sizeof(char) * (strlen("fakeconsole") + 1));
	strcpy(ciFakeConsole->super->super->name, "fakeconsole");
	ciFakeConsole->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(ciFakeConsole->super->metaData, "");
	ciFakeConsole->super->started = 1;
	ciFakeConsole->super->AddTypeDefinition(ciFakeConsole->super, ctFakeConsole);
	ciFakeConsole->AddProvided(ciFakeConsole, pInMsg);
	ciFakeConsole->AddRequired(ciFakeConsole, pSendMsg);

	ComponentInstance* ciHelloWorld = new_ComponentInstance();
	ciHelloWorld->super->super->name = malloc(sizeof(char) * (strlen("helloworld") + 1));
	strcpy(ciHelloWorld->super->super->name, "helloworld");
	ciHelloWorld->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(ciHelloWorld->super->metaData, "");
	ciHelloWorld->super->started = 1;
	ciHelloWorld->super->AddTypeDefinition(ciHelloWorld->super, ctHelloWorld);
	ciHelloWorld->AddProvided(ciHelloWorld, pFake);
	ciHelloWorld->AddRequired(ciHelloWorld, pSendText);

	contikiNode->AddGroups(contikiNode, coapGroup);
	contikiNode->AddComponents(contikiNode, ciFakeConsole);
	contikiNode->AddComponents(contikiNode, ciHelloWorld);

	serverNode->AddGroups(serverNode, coapGroup);
	serverNode->AddComponents(serverNode, ciFakeConsole);
	serverNode->AddComponents(serverNode, ciHelloWorld);

	ctFakeConsole->AddDeployUnit(ctFakeConsole, duFakeConsole);
	ctHelloWorld->AddDeployUnit(ctHelloWorld, duHelloWorld);
	contikiNodeType->AddDeployUnit(contikiNodeType, kevContikiNode);
	coapGroupType->AddDeployUnit(coapGroupType, kevGroupCoap);
	coapChanType->AddDeployUnit(coapChanType, kevChanCoap);

	ctFakeConsole->AddDictionaryType(ctFakeConsole, dtFakeConsole);
	ctHelloWorld->AddDictionaryType(ctHelloWorld, dtHelloWorld);
	coapGroupType->AddDictionaryType(coapGroupType, gtDicType);
	coapChanType->AddDictionaryType(coapChanType, chanDicType);

	defaultChannel->AddBindings(defaultChannel, mbInMsg);
	defaultChannel->AddBindings(defaultChannel, mbFake);
	defaultChannel->AddBindings(defaultChannel, mbSendMsg);
	defaultChannel->AddBindings(defaultChannel, mbSendText);

	((ComponentType*)ctFakeConsole->pDerivedObj)->AddProvided((ComponentType*)ctFakeConsole->pDerivedObj, ptrInMsg);
	((ComponentType*)ctFakeConsole->pDerivedObj)->AddRequired((ComponentType*)ctFakeConsole->pDerivedObj, ptrSendMsg);
	((ComponentType*)ctHelloWorld->pDerivedObj)->AddProvided((ComponentType*)ctHelloWorld->pDerivedObj, ptrFake);
	((ComponentType*)ctHelloWorld->pDerivedObj)->AddRequired((ComponentType*)ctHelloWorld->pDerivedObj, ptrSendText);

	model->AddNodes(model, contikiNode);
	model->AddNodes(model, serverNode);
	model->AddTypeDefinitions(model, ctFakeConsole);
	model->AddTypeDefinitions(model, ctHelloWorld);
	model->AddTypeDefinitions(model, contikiNodeType);
	model->AddTypeDefinitions(model, coapGroupType);
	model->AddTypeDefinitions(model, coapChanType);
	model->AddLibraries(model, contiki);
	model->AddHubs(model, defaultChannel);
	model->AddBindings(model, mbInMsg);
	model->AddBindings(model, mbFake);
	model->AddBindings(model, mbSendMsg);
	model->AddBindings(model, mbSendText);
	model->AddDeployUnits(model, duFakeConsole);
	model->AddDeployUnits(model, duHelloWorld);
	model->AddDeployUnits(model, kevContikiNode);
	model->AddDeployUnits(model, kevGroupCoap);
	model->AddDeployUnits(model, kevChanCoap);
	model->AddGroups(model, coapGroup);

	printf("Model %s created with success!\n\n", model->InternalGetKey(model));

	model2->AddNodes(model2, contikiNode);
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
	model2->AddNodes(model2, contikiNode);

	printf("Model %s created with success! \n\n", model2->InternalGetKey(model2));

	Visitor* visitor_print = (Visitor*)malloc(sizeof(Visitor));

	visitor_print->action =  actionprintf;
	/*visitor_print->action =  ActionCompare;*/

	model->Visit(model, visitor_print);
	/*printf("\nVisiting model2 \n\n");
	model2->Visit(model2, visitor_print);*/
	printf("Process finished!\n\n");

	return 0;
}
