/*#include "DefaultFactorykevoree.h"
#include "Comparekevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include "kevoree.h"

ContainerRoot* model = NULL;
ContainerRoot* model2 = NULL;

void actionprintf(char *path, Type type, void* value)
{
	switch(type)
	{
		case STRING:
			printf("path = %s  value = %s\n",path,(char*)value);
			break;
		
		case BOOL:
			printf("path = %s  value = %d\n", path, (int)value);
			break;
	}
}

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
	/*model2 = new_ContainerRoot();
	printf("ContainerRoot '%s' created\n", model2->InternalGetKey(model2));*/
	
	/* NeworkProperty front */
	NetworkProperty* front = new_NetworkProperty();
	front->super->name = malloc(sizeof(char) * (strlen("front") + 1));
	strcpy(front->super->name, "front");
	front->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org") + 1));
	strcpy(front->value, "contiki.kevoree.org");
	
	/* NeworkProperty local */
	NetworkProperty* local = new_NetworkProperty();
	local->super->name = malloc(sizeof(char) * (strlen("local") + 1));
	strcpy(local->super->name, "local");
	local->value = malloc(sizeof(char) * (strlen("aaaa::0:0:3") + 1));
	strcpy(local->value, "aaaa::0:0:3");
	
	/* NetworkInfo ip */
	NetworkInfo* ip = new_NetworkInfo();
	ip->super->name = malloc(sizeof(char) * (strlen("ip") + 1));
	strcpy(ip->super->name, "ip");
	
	ip->AddValues(ip, front);
	ip->AddValues(ip, local);

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
	contikiNodeType->abstract = 0;
	
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
	coapGroupType->abstract = 0;
	
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
	coapChanType->abstract = 0;
	((ChannelType*)coapChanType->pDerivedObj)->upperBindings = 0;
	((ChannelType*)coapChanType->pDerivedObj)->lowerBindings = 0;
	((ChannelType*)coapChanType->pDerivedObj)->upperFragments = 0;
	((ChannelType*)coapChanType->pDerivedObj)->lowerFragments = 0;
	
	/* TypeLibrary Contiki */
	TypeLibrary* contiki = new_TypeLibrary();
	contiki->super->name = malloc(sizeof(char) * (strlen("Contiki") + 1));
	strcpy(contiki->super->name, "Contiki");
	contiki->AddSubTypes(contiki, contikiNodeType);
	contiki->AddSubTypes(contiki, coapGroupType);
	contiki->AddSubTypes(contiki, coapChanType);
	
	/* TypeLibrary Default */
	TypeLibrary* defLib = new_TypeLibrary();
	defLib->super->name = malloc(sizeof(char) * (strlen("Default") + 1));
	strcpy(defLib->super->name, "Default");
	
	/* Channel CoAPChannel */
	Channel* defaultChannel = new_Channel();
	defaultChannel->super->super->name = malloc(sizeof(char) * (strlen("DefaultChannel") + 1));
	strcpy(defaultChannel->super->super->name, "DefaultChannel");
	defaultChannel->super->started = 1;
	defaultChannel->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(defaultChannel->super->metaData, "");
	
	/* Channel DictionaryValue host */
	DictionaryValue* chanValueHost = new_DictionaryValue();
	chanValueHost->name = malloc(sizeof(char) * (strlen("host") + 1));
	strcpy(chanValueHost->name, "host");
	chanValueHost->value = malloc(sizeof(char) * (strlen("contiki.kevoree.org") + 1));
	strcpy(chanValueHost->name, "contiki.kevoree.org");
	
	/* Channel DictionaryValue port */
	DictionaryValue* chanValuePort = new_DictionaryValue();
	chanValuePort->name = malloc(sizeof(char) * (strlen("Port") + 1));
	strcpy(chanValuePort->name, "Port");
	chanValuePort->value = malloc(sizeof(char) * (strlen("5683") + 1));
	strcpy(chanValuePort->name, "5683");
	
	/* Channel DictionaryValue path */
	DictionaryValue* chanValuePath = new_DictionaryValue();
	chanValuePath->name = malloc(sizeof(char) * (strlen("path") + 1));
	strcpy(chanValuePath->name, "path");
	chanValuePath->value = malloc(sizeof(char) * (strlen("DefaultChannel") + 1));
	strcpy(chanValuePath->name, "DefaultChannel");
	
	/* Channel Dictionary */
	Dictionary* chanDico = new_Dictionary();
	chanDico->AddValues(chanDico, chanValueHost);
	chanDico->AddValues(chanDico, chanValuePort);
	chanDico->AddValues(chanDico, chanValuePath);
	
	/* Channel DictionaryAttribute host */
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
	
	/* Channel DictionaryAttribute port */
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
	
	/* Channel DictionaryAttribute path */
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
	
	/* Channel DictionaryType */
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
	kevChanCoap->version = malloc(sizeof(char) * (strlen("0.0.1") + 1));
	strcpy(kevChanCoap->version,"0.0.1");
	kevChanCoap->url = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(kevChanCoap->url, "");
	kevChanCoap->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(kevChanCoap->type,"ce");
	
	/* Group CoAP */
	Group* coapGroup = new_Group();
	coapGroup->super->super->name = malloc(sizeof(char) * (strlen("CoAPGroup") + 1));
	strcpy(coapGroup->super->super->name, "CoAPGroup");
	coapGroup->super->started = 1;
	coapGroup->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(coapGroup->super->metaData, "");
	
	/* FragmentDictionary contiki-node */
	FragmentDictionary* contikiFragDico = new_FragmentDictionary();
	contikiFragDico->name = malloc(sizeof(char) * (strlen("contiki-node") + 1));
	strcpy(contikiFragDico->name, "contiki-node");
	
	/* Group DictionaryValue proxy_port */
	DictionaryValue* groupValueProxy = new_DictionaryValue();
	groupValueProxy->name = malloc(sizeof(char) * (strlen("proxy_port") + 1));
	strcpy(groupValueProxy->name, "proxy_port");
	groupValueProxy->value = malloc(sizeof(char) * (strlen("9000") + 1));
	strcpy(groupValueProxy->name, "9000");
	
	/* Group DictionaryValue path */
	DictionaryValue* groupValuePath = new_DictionaryValue();
	groupValuePath->name = malloc(sizeof(char) * (strlen("path") + 1));
	strcpy(groupValuePath->name, "path");
	groupValuePath->value = malloc(sizeof(char) * (strlen("CoAPGroup") + 1));
	strcpy(groupValuePath->name, "CoAPGroup");
	
	contikiFragDico->super->AddValues(contikiFragDico->super, chanValuePort);
	contikiFragDico->super->AddValues(contikiFragDico->super, groupValueProxy);
	contikiFragDico->super->AddValues(contikiFragDico->super, groupValuePath);
	
	coapGroup->super->AddTypeDefinition(coapGroup->super, coapGroupType);
	
	/* DictionaryType contikiNodeDicType */
	DictionaryType* contikiNodeDicType = new_DictionaryType();
	
	contikiNodeType->AddDictionaryType(contikiNodeType, contikiNodeDicType);
	
	ComponentInstance* c1 = new_ComponentInstance();
	c1->super->super->name = malloc(sizeof(char) * (strlen("fakeconsole") + 1));
	strcpy(c1->super->super->name, "fakeconsole");
	c1->super->metaData = malloc(sizeof(char) * (strlen("dummy_MetaData") + 1));
	strcpy(c1->super->metaData, "dummy_MetaData");
	c1->super->started = 1;
	
	ComponentInstance* c2 = new_ComponentInstance();
	c2->super->super->name = malloc(sizeof(char) * (strlen("fakeconsole") + 1));
	strcpy(c2->super->super->name, "fakeconsole");
	c2->super->metaData = malloc(sizeof(char) * (strlen("dummy_MetaDataChanged") + 1));
	strcpy(c2->super->metaData, "dummy_MetaDataChanged");
	c2->super->started = 1;

	ContainerNode* contikiNode = new_ContainerNode();
	contikiNode->super->super->name = malloc(sizeof(char) * (strlen("contiki-node") + 1));
	strcpy(contikiNode->super->super->name, "contiki-node");
	contikiNode->super->started = 1;
	contikiNode->super->metaData = malloc(sizeof(char) * (strlen("") + 1));
	strcpy(contikiNode->super->metaData, "");
	
	
	
	contikiNode->super->AddTypeDefinition(contikiNode->super, contikiNodeType);
	contikiNode->AddGroups(contikiNode, coapGroup);
	contikiNode->AddNetworkInformation(contikiNode, ip);
	
	contikiNodeType->AddDeployUnit(contikiNodeType, kevContikiNode);
	coapGroupType->AddDeployUnit(coapGroupType, kevGroupCoap);
	coapChanType->AddDeployUnit(coapChanType, kevChanCoap);
	
	coapGroupType->super->AddDictionaryType(
	
	model->AddTypeDefinitions(model, contikiNodeType);
	model->AddNodes(model, contikiNode);
	model->AddLibraries(model, contiki);
	model->AddHubs(model, defaultChannel);
	model->AddDeployUnits(model, kevContikiNode);
	model->AddDeployUnits(model, kevGroupCoap);
	model->AddDeployUnits(model, kevChanCoap);
	model->AddGroups(model, coapGroup);
	
	printf("Model created with sucess!\n");
	
	Visitor* visitor_print = (Visitor*)malloc(sizeof(Visitor));

	visitor_print->action =  actionprintf;
	/*visitor_print->action =  ActionCompare;*/
	
	model->Visit(model, visitor_print);
	/*printf("\n\n");
	model2->Visit(model2, visitor_print);*/
	
	/*void* r = model->FindByPath("nodes[node0]/components[fakeconsole]", model);
	
	if(r != NULL)
	{
		printf("OK\n");
		printf("ComponentInstance: %s\n", ((ComponentInstance*)(r))->super->super->name);
	}
	
	void* s = model->FindByPath("nodes[node0]/groups[group0]", model);
	
	if(s != NULL)
	{
		printf("OK\n");
		printf("Group: %s\n", ((Group*)(s))->super->super->name);
	}
	
	void* t = model->FindByPath("typeDefinitions[Light_1.0.0-SNAPSHOT]", model);
	
	if(t != NULL)
	{
		printf("OK\n");
		printf("TypeDefinition: %s\n", ((TypeDefinition*)t)->super->name);
	}
	
	void* u = model->FindByPath("nodes[node0]/typeDefinition[ContikiNode_1.0.0-SNAPSHOT]/deployUnits[org.kevoree.library_ContikiNodeType_1.0.0-SNAPSHOT]", model);
	
	if(u != NULL)
	{
		printf("OK\n");
		printf("DeployUnit: %s\n", ((DeployUnit*)u)->super->name);
	}
	
	void* v = model->FindByPath("typeDefinitions[Temperature_1.0.0-SNAPSHOT]/required[port0]", model);
	
	if(v != NULL)
	{
		printf("OK\n");
		printf("PortTypeRef: %s\n", ((PortTypeRef*)v)->super->name);
	}
	
	void* w = model->FindByPath("groups[group0]/subNodes[node0]", model);
	
	if(w != NULL)
	{
		printf("OK\n");
		printf("SubNode: %s\n", ((ContainerNode*)w)->super->super->name);
	}*/

	return 0;
}
