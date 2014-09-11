/*#include "DefaultFactorykevoree.h"
#include "Comparekevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include "kevoree.h"

int mem_count = 0;

void* my_malloc(size_t s)
{
	mem_count += s;
	return malloc(s);
}

void* my_calloc(size_t nmemb, size_t size)
{
	mem_count += size;
	return calloc(nmemb, size);
}

void str_free(char* ptr)
{
	mem_count -= strlen(ptr) + 1;
	free(ptr);
}

int main(void)
{
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
	strcpy(serverNodeLocal->value, "aaaa::0:0:5");

	/* NetworkInfo ip */
	NetworkInfo* contikiNodeIP = new_NetworkInfo();
	contikiNodeIP->super->name = my_malloc(sizeof(char) * (strlen("ip")) + 1);
	strcpy(contikiNodeIP->super->name, "ip");

	contikiNodeIP->AddValues(contikiNodeIP, contikiNodeFront);
	contikiNodeIP->AddValues(contikiNodeIP, contikiNodeLocal);

	/* NetworkInfo ip */
	NetworkInfo* serverNodeIP = new_NetworkInfo();
	serverNodeIP->super->name = my_malloc(sizeof(char) * (strlen("ip")) + 1);
	strcpy(serverNodeIP->super->name, "ip");

	serverNodeIP->AddValues(serverNodeIP, serverNodeFront);
	serverNodeIP->AddValues(serverNodeIP, serverNodeLocal);

	/*serverNode->AddNetworkInformation(serverNode, serverNodeIP);*/

	/* TypeDefinition ContikiNode/1.0.0 */
	TypeDefinition* contikiNodeType = newPoly_NodeType();
	contikiNodeType->super->name = my_malloc(sizeof(char) * (strlen("ContikiNode")) + 1);
	strcpy(contikiNodeType->super->name, "ContikiNode");
	contikiNodeType->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(contikiNodeType->version, "0.0.1");
	contikiNodeType->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNodeType->bean, "");
	contikiNodeType->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(contikiNodeType->factoryBean, "");
	contikiNodeType->abstract = false;

	/*serverNode->super->AddTypeDefinition(serverNode->super, contikiNodeType);*/

	/* TypeDefinition CoAPGroup/1.0.0 */
	TypeDefinition* coapGroupType = newPoly_GroupType();
	coapGroupType->abstract = false;
	coapGroupType->super->name = my_malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(coapGroupType->super->name, "CoAPGroup");
	coapGroupType->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	strcpy(coapGroupType->version, "0.0.1");
	coapGroupType->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroupType->bean, "");
	coapGroupType->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroupType->factoryBean, "");

	/* TypeDefinition CoAPChan/0.0.1
	  	TypeDefinition* coapChanType = newPoly_ChannelType();
	  	coapChanType->abstract = false;
	  	coapChanType->super->name = my_malloc(sizeof(char) * (strlen("CoAPChan")) + 1);
	  	strcpy(coapChanType->super->name, "CoAPChan");
	  	coapChanType->version = my_malloc(sizeof(char) * (strlen("0.0.1")) + 1);
	  	strcpy(coapChanType->version, "0.0.1");
	  	coapChanType->bean = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(coapChanType->bean, "");
	  	coapChanType->factoryBean = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(coapChanType->factoryBean, "");
	  	((ChannelType*)coapChanType->pDerivedObj)->upperBindings = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->lowerBindings = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->upperFragments = 0;
	  	((ChannelType*)coapChanType->pDerivedObj)->lowerFragments = 0;*/

	/* TypeDefinition FakeConsoleType
	  		TypeDefinition* ctFakeConsole = newPoly_ComponentType();
	  		ctFakeConsole->abstract = false;
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
	contiki->AddSubTypes(contiki, contikiNodeType);
	contiki->AddSubTypes(contiki, coapGroupType);

	/* TypeLibrary Default */
	TypeLibrary* defLib = new_TypeLibrary();
	defLib->super->name = my_malloc(sizeof(char) * (strlen("Default")) + 1);
	strcpy(defLib->super->name, "Default");

	/* Channel CoAPChannel
	  	Channel* defaultChannel = new_Channel();
	  	defaultChannel->super->super->name = my_malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	  	strcpy(defaultChannel->super->super->name, "DefaultChannel");
	  	defaultChannel->super->started = true;
	  	defaultChannel->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(defaultChannel->super->metaData, "");*/

	/* Channel FragmentDictionary server-node
	  		FragmentDictionary* fdChannelServerNode = new_FragmentDictionary();
	  		fdChannelServerNode->name = my_malloc(sizeof(char) * (strlen("server-node")) + 1);
	  		strcpy(fdChannelServerNode->name, "server-node");*/

	/* Channel FragmentDictionary contiki-node
	  	FragmentDictionary* fdChannelContikiNode = new_FragmentDictionary();
	  	fdChannelContikiNode->name = my_malloc(sizeof(char) * (strlen("contiki-node")) + 1);
	  	strcpy(fdChannelContikiNode->name, "contiki-node");*/

	/*defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelContikiNode);*/
	/*defaultChannel->super->AddFragmentDictionary(defaultChannel->super, fdChannelServerNode);*/

	/*Channel FragmentDictionary server-node */
	FragmentDictionary* fdContikiNode = new_FragmentDictionary();
	fdContikiNode->name = my_malloc(sizeof(char) * (strlen("contiki-node")) + 1);
	strcpy(fdContikiNode->name, "contiki-node");

	/* Channel DictionaryValue host
	  	DictionaryValue* chanValueHost = new_DictionaryValue();
	  	chanValueHost->name = my_malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanValueHost->name, "host");
	  	chanValueHost->value = my_malloc(sizeof(char) * (strlen("contiki.kevoree.org")) + 1);
	  	strcpy(chanValueHost->value, "contiki.kevoree.org");*/

	/* Channel DictionaryValue port
	  	DictionaryValue* chanValuePort = new_DictionaryValue();
	  	chanValuePort->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanValuePort->name, "port");
	  	chanValuePort->value = my_malloc(sizeof(char) * (strlen("80")) + 1);
	  	strcpy(chanValuePort->value, "80");*/

	/* Channel DictionaryValue path
	  	DictionaryValue* chanValuePath = new_DictionaryValue();
	  	chanValuePath->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanValuePath->name, "path");
	  	chanValuePath->value = my_malloc(sizeof(char) * (strlen("DefaultChannel")) + 1);
	  	strcpy(chanValuePath->value, "DefaultChannel");*/

	/* Channel DictionaryValue port
	  	DictionaryValue* dvPortContikiNode = new_DictionaryValue();
	  	dvPortContikiNode->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(dvPortContikiNode->name, "port");
	  	dvPortContikiNode->value = my_malloc(sizeof(char) * (strlen("5683")) + 1);
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

	/* ChannelType DictionaryAttribute host
	  	DictionaryAttribute* chanDicoAttrHost = new_DictionaryAttribute();
	  	chanDicoAttrHost->fragmentDependant = false;
	  	chanDicoAttrHost->optional = false;
	  	chanDicoAttrHost->super->super->name = my_malloc(sizeof(char) * (strlen("host")) + 1);
	  	strcpy(chanDicoAttrHost->super->super->name, "host");
	  	chanDicoAttrHost->state = false;
	  	chanDicoAttrHost->datatype = my_malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrHost->datatype, "string");
	  	chanDicoAttrHost->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(chanDicoAttrHost->defaultValue, "");*/

	/* ChannelType DictionaryAttribute port
	  	DictionaryAttribute* chanDicoAttrPort = new_DictionaryAttribute();
	  	chanDicoAttrPort->fragmentDependant = false;
	  	chanDicoAttrPort->optional = false;
	  	chanDicoAttrPort->super->super->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	  	strcpy(chanDicoAttrPort->super->super->name, "port");
	  	chanDicoAttrPort->state = false;
	  	chanDicoAttrPort->datatype = my_malloc(sizeof(char) * (strlen("number")) + 1);
	  	strcpy(chanDicoAttrPort->datatype, "number");
	  	chanDicoAttrPort->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(chanDicoAttrPort->defaultValue, "");*/

	/* ChannelType DictionaryAttribute path
	  	DictionaryAttribute* chanDicoAttrPath = new_DictionaryAttribute();
	  	chanDicoAttrPath->fragmentDependant = false;
	  	chanDicoAttrPath->optional = false;
	  	chanDicoAttrPath->super->super->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	  	strcpy(chanDicoAttrPath->super->super->name, "path");
	  	chanDicoAttrPath->state = false;
	  	chanDicoAttrPath->datatype = my_malloc(sizeof(char) * (strlen("string")) + 1);
	  	strcpy(chanDicoAttrPath->datatype, "string");
	  	chanDicoAttrPath->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	  	strcpy(chanDicoAttrPath->defaultValue, "");*/

	/* GroupType DictionaryAttribute port */
	DictionaryAttribute* gtDicAttrPort = new_DictionaryAttribute();
	gtDicAttrPort->fragmentDependant = true;
	gtDicAttrPort->optional = true;
	gtDicAttrPort->super->super->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(gtDicAttrPort->super->super->name, "port");
	gtDicAttrPort->state = false;
	gtDicAttrPort->datatype = my_malloc(sizeof(char) * (strlen("number")) + 1);
	strcpy(gtDicAttrPort->datatype, "number");
	gtDicAttrPort->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrPort->defaultValue, "");

	/* GroupType DictionaryAttribute path */
	DictionaryAttribute* gtDicAttrPath = new_DictionaryAttribute();
	gtDicAttrPath->fragmentDependant = true;
	gtDicAttrPath->optional = true;
	gtDicAttrPath->super->super->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(gtDicAttrPath->super->super->name, "path");
	gtDicAttrPath->state = false;
	gtDicAttrPath->datatype = my_malloc(sizeof(char) * (strlen("string")) + 1);
	strcpy(gtDicAttrPath->datatype, "string");
	gtDicAttrPath->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrPath->defaultValue, "");

	/* GroupType DictionaryAttribute proxy_port */
	DictionaryAttribute* gtDicAttrProxy = new_DictionaryAttribute();
	gtDicAttrProxy->fragmentDependant = true;
	gtDicAttrProxy->optional = true;
	gtDicAttrProxy->super->super->name = my_malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(gtDicAttrProxy->super->super->name, "proxy_port");
	gtDicAttrProxy->state = false;
	gtDicAttrProxy->datatype = my_malloc(sizeof(char) * (strlen("int")) + 1);
	strcpy(gtDicAttrProxy->datatype, "int");
	gtDicAttrProxy->defaultValue = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(gtDicAttrProxy->defaultValue, "9000");

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

	/* ComponentInstance DictionaryType FakeConsole
	  		DictionaryType* dtFakeConsole = new_DictionaryType();
	  		dtFakeConsole->AddAttributes(dtFakeConsole, daFakeConsoleProxy);*/

	/* ComponentInstance DictionaryType HelloWorld */
	DictionaryType* dtHelloWorld = new_DictionaryType();

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
	strcpy(kevContikiNode->type,"ce");

	/* DeployUnit //kevoree-group-coap/0.0.1 */
	DeployUnit* kevGroupCoap = new_DeployUnit();
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
	strcpy(kevGroupCoap->type,"ce");

	/* DeployUnit //kevoree-chan-coap/0.0.1
	  	DeployUnit* kevChanCoap = new_DeployUnit();
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
	  	strcpy(kevChanCoap->type,"ce");*/

	/* DeployUnit //kevoree-comp-fakeconsole/0.0.1
	  		DeployUnit* duFakeConsole = new_DeployUnit();
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
	  		strcpy(ptrSendMsg->super->name, "sendMsg");
	  		ptrSendMsg->noDependency = true;
	  		ptrSendMsg->optional = true;*/

	/* PortTypeRef inMsg
	  		PortTypeRef* ptrInMsg = new_PortTypeRef();
	  		ptrInMsg->super->name = my_malloc(sizeof(char) * (strlen("inMsg")) + 1);
	  		strcpy(ptrInMsg->super->name, "inMsg");
	  		ptrInMsg->noDependency = true;
	  		ptrInMsg->optional = true;*/

	/* PortTypeRef sendText
	  	PortTypeRef* ptrSendText = new_PortTypeRef();
	  	ptrSendText->super->name = my_malloc(sizeof(char) * (strlen("sendText")) + 1);
	  	strcpy(ptrSendText->super->name, "sendText");
	  	ptrSendText->noDependency = true;
	  	ptrSendText->optional = true;*/

	/* PortTypeRef fake */
	PortTypeRef* ptrFake = new_PortTypeRef();
	ptrFake->super->name = my_malloc(sizeof(char) * (strlen("fake")) + 1);
	strcpy(ptrFake->super->name, "fake");
	ptrFake->noDependency = true;
	ptrFake->optional = true;

	/* Port inMsg
	  		Port* pInMsg = new_Port();
	  		pInMsg->super->name = my_malloc(sizeof(char) * (strlen("inMsg")) + 1);
	  		strcpy(pInMsg->super->name, "inMsg");
	  		pInMsg->AddPortTypeRef(pInMsg, ptrInMsg);*/

	/* Port sendMsg
	  		Port* pSendMsg = new_Port();
	  		pSendMsg->super->name = my_malloc(sizeof(char) * (strlen("sendMsg")) + 1);
	  		strcpy(pSendMsg->super->name, "sendMsg");
	  		pSendMsg->AddPortTypeRef(pSendMsg, ptrSendMsg);*/

	/* Port fake
	  	Port* pFake = new_Port();
	  	pFake->super->name = my_malloc(sizeof(char) * (strlen("fake")) + 1);
	  	strcpy(pFake->super->name, "fake");
	  	pFake->AddPortTypeRef(pFake, ptrFake);*/

	/* Port sendMsg
	  	Port* pSendText = new_Port();
	  	pSendText->super->name = my_malloc(sizeof(char) * (strlen("sendText")) + 1);
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
	coapGroup->super->super->name = my_malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
	strcpy(coapGroup->super->super->name, "CoAPGroup");
	coapGroup->super->started = true;
	coapGroup->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
	strcpy(coapGroup->super->metaData, "");

	/*coapGroup->AddSubNodes(coapGroup, serverNode);*/
	coapGroup->super->AddTypeDefinition(coapGroup->super, coapGroupType);

	/* FragmentDictionary contiki-node */
	FragmentDictionary* contikiNodeFragDico = new_FragmentDictionary();
	contikiNodeFragDico->name = my_malloc(sizeof(char) * (strlen("contiki-node")) + 1);
	strcpy(contikiNodeFragDico->name, "contiki-node");

	/* Group DictionaryValue port */
	DictionaryValue* groupValuePort = new_DictionaryValue();
	groupValuePort->name = my_malloc(sizeof(char) * (strlen("port")) + 1);
	strcpy(groupValuePort->name, "port");
	groupValuePort->value = my_malloc(sizeof(char) * (strlen("5683")) + 1);
	strcpy(groupValuePort->value, "5683");

	/* Group DictionaryValue proxy_port */
	DictionaryValue* groupValueProxy = new_DictionaryValue();
	groupValueProxy->name = my_malloc(sizeof(char) * (strlen("proxy_port")) + 1);
	strcpy(groupValueProxy->name, "proxy_port");
	groupValueProxy->value = my_malloc(sizeof(char) * (strlen("9000")) + 1);
	strcpy(groupValueProxy->value, "9000");

	/* Group DictionaryValue path */
	DictionaryValue* groupValuePath = new_DictionaryValue();
	groupValuePath->name = my_malloc(sizeof(char) * (strlen("path")) + 1);
	strcpy(groupValuePath->name, "path");
	groupValuePath->value = my_malloc(sizeof(char) * (strlen("CoAPGroup")) + 1);
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
	  		ciFakeConsole->super->super->name = my_malloc(sizeof(char) * (strlen("fakeconsole")) + 1);
	  		strcpy(ciFakeConsole->super->super->name, "fakeconsole");
	  		ciFakeConsole->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
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
	ctHelloWorld->AddDeployUnit(ctHelloWorld, duHelloWorld);
	contikiNodeType->AddDeployUnit(contikiNodeType, kevContikiNode);
	coapGroupType->AddDeployUnit(coapGroupType, kevGroupCoap);
	/*coapChanType->AddDeployUnit(coapChanType, kevChanCoap);*/

	/*ctFakeConsole->AddDictionaryType(ctFakeConsole, dtFakeConsole);*/
	ctHelloWorld->AddDictionaryType(ctHelloWorld, dtHelloWorld);
	coapGroupType->AddDictionaryType(coapGroupType, gtDicType);
	/*coapChanType->AddDictionaryType(coapChanType, chanDicType);*/

	/*defaultChannel->AddBindings(defaultChannel, mbInMsg);*/
	/*defaultChannel->AddBindings(defaultChannel, mbFake);*/
	/*defaultChannel->AddBindings(defaultChannel, mbSendMsg);*/
	/*defaultChannel->AddBindings(defaultChannel, mbSendText);*/

	/*((ComponentType*)ctFakeConsole->pDerivedObj)->AddProvided((ComponentType*)ctFakeConsole->pDerivedObj, ptrInMsg);
	  		((ComponentType*)ctFakeConsole->pDerivedObj)->AddRequired((ComponentType*)ctFakeConsole->pDerivedObj, ptrSendMsg);*/
	/*((ComponentType*)ctHelloWorld->pDerivedObj)->AddProvided((ComponentType*)ctHelloWorld->pDerivedObj, ptrFake);
	  	((ComponentType*)ctHelloWorld->pDerivedObj)->AddRequired((ComponentType*)ctHelloWorld->pDerivedObj, ptrSendText);*/

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

	int i = 0;
	int j = 0;

	for(i = 0; i < 36; i++)
	{
		/* ContainerNode contikiNode */
		ContainerNode* contikiNode = new_ContainerNode();
		contikiNode->super->super->name = my_malloc(sizeof(char) * (strlen("XX")) + 1);
		sprintf(contikiNode->super->super->name, "%d", i);
		contikiNode->super->started = true;
		contikiNode->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
		strcpy(contikiNode->super->metaData, "");

		/*contiki->AddSubTypes(contiki, coapChanType);*/
		contikiNode->AddNetworkInformation(contikiNode, contikiNodeIP);
		contikiNode->super->AddTypeDefinition(contikiNode->super, contikiNodeType);
		contikiNode->AddGroups(contikiNode, coapGroup);

		for(j = 0; j < 3; j++)
		{
			ComponentInstance* ciHelloWorld = new_ComponentInstance();
			ciHelloWorld->super->super->name = my_malloc(sizeof(char) * (strlen("XX")) + 1);
			sprintf(ciHelloWorld->super->super->name, "%d", j);
			ciHelloWorld->super->metaData = my_malloc(sizeof(char) * (strlen("")) + 1);
			strcpy(ciHelloWorld->super->metaData, "");
			ciHelloWorld->super->started = true;
			ciHelloWorld->super->AddTypeDefinition(ciHelloWorld->super, ctHelloWorld);
			/*ciHelloWorld->AddProvided(ciHelloWorld, pFake);
				ciHelloWorld->AddRequired(ciHelloWorld, pSendText);*/

			contikiNode->AddComponents(contikiNode, ciHelloWorld);
		}

		coapGroup->AddSubNodes(coapGroup, contikiNode);


		modelX->AddNodes(modelX, contikiNode);
		/*printf("%d\n", mem_count);*/
	}

	/*printf("Elapsed time: %d\n", RTIMER_NOW());*/
	modelX->Visit(modelX, visitor_print);

	/*modelX->Visit(modelX, visitor_print);*/

	return 0;
}
