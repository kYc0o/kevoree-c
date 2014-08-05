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
	/*Logger::Start(Logger::DEBUG, "kevoree.log");

	DefaultkevoreeFactory factory;
	JSONModelLoader loader;

	signal (SIGINT,my_handler);
	int exit=0;
	clock_t start = clock();

	kb = new KevoreeBootStrap();

	// FIX ME PARAM
	kb->setNodeName("node0");
	kb->setBasePath("/tmp/.m2"); // FIX ME $HOME/.m2




	loader.setFactory(&factory);*/
	printf("Starting kevoree C implementation\n");

	/*model = factory.createContainerRoot();*/
	model = new_ContainerRoot();
	model2 = new_ContainerRoot();
	printf("ContainerRoot '%s' created\n", model2->InternalGetKey(model2));

	/*DeployUnit *d =factory.createDeployUnit();
	d->name = "CPPNodeType";
	d->groupName = "org.kevoree.library";
	d->version = "1.0.0-SNAPSHOT";
	d->type ="so";*/
	DeployUnit* d = new_DeployUnit();
	/*printf("DeployUnit 'd' created -> %i\n", d);*/
	d->super->name = malloc(sizeof(char) * (strlen("ContikiNodeType") + 1));
	strcpy(d->super->name, "ContikiNodeType");
	d->groupName = malloc(sizeof(char) * (strlen("org.kevoree.library") + 1));
	strcpy(d->groupName, "org.kevoree.library");
	d->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(d->version,"1.0.0-SNAPSHOT");
	d->url = malloc(sizeof(char) * (strlen("dummyURL") + 1));
	strcpy(d->url, "dummyURL");
	d->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(d->type,"ce");
	/*printf("DeployUnit 'd' initialized -> %i\n", d);*/

	/*TypeDefinition *nodetype = factory.createNodeType();
	nodetype->name = "CPPNode";
	nodetype->abstract= false;
	nodetype->adddeployUnit(d);*/
	TypeDefinition* nodetype = newPoly_NodeType();
	nodetype->super->name = malloc(sizeof(char) * (strlen("ContikiNode") + 1));
	strcpy(nodetype->super->name, "ContikiNode");
	nodetype->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(nodetype->version, "1.0.0-SNAPSHOT");
	nodetype->abstract = 0;
	/*printf("NodeType nodetype created\n");*/
	nodetype->AddDeployUnit(nodetype, d);
	/*printf("Adding DeployUnit 'd' -> %i to 'nodetype' -> %i\n", d, nodetype);*/

	/*DeployUnit *dg =factory.createDeployUnit();
	dg->name = "kevoree-group-websocket";
	dg->groupName = "org.kevoree.library";
	dg->version = "1.0.0-SNAPSHOT";
	dg->type ="so";*/
	/*DeployUnit* dg = new_DeployUnit();
	dg->super->name = malloc(sizeof(char) * (strlen("kevoree-group-websocket") + 1));
	strcpy(dg->super->name, "kevoree-group-websocket");
	dg->groupName = malloc(sizeof(char) * (strlen("org.kevoree.library") + 1));
	strcpy(dg->groupName, "org.kevoree.library");
	dg->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(dg->version,"1.0.0-SNAPSHOT");
	dg->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(dg->type,"ce");*/
	/*printf("DeployUnit 'dg' created\n");*/
	
	/*TypeDefinition *grouptype = factory.createGroupType();
	grouptype->abstract= false;
	grouptype->name ="WebSocketGroup";
	grouptype->version = "1.0";*/
	/*TypeDefinition* grouptype = newPoly_GroupType();
	grouptype->abstract = 0;
	grouptype->super->name = malloc(sizeof(char) * (strlen("WebSocketGroup") + 1));
	strcpy(grouptype->super->name, "WebSocketGroup");
	grouptype->version = malloc(sizeof(char) * (strlen("1.0") + 1));
	strcpy(grouptype->version, "1.0");*/
	/*printf("GroupType 'grouptype' created\n");*/

	/*DictionaryType *typegroup= factory.createDictionaryType();
	DictionaryAttribute *attport = factory.createDictionaryAttribute();
	attport->optional = false;
	attport->datatype = "int";
	attport->fragmentDependant = true;
	attport->name ="port";
	attport->defaultValue = "9001";
	typegroup->addattributes(attport);

	grouptype->adddictionaryType(typegroup);

	grouptype->adddeployUnit(dg);*/

	/*ContainerNode *node0 = factory.createContainerNode();
	node0->name = "node0";
	node0->started= true;
	node0->started = true;*/
	ContainerNode* node0 = new_ContainerNode();
	/*printf("ContainerNode 'node0' created\n");*/
	node0->super->super->name = malloc(sizeof(char) * (strlen("node0") + 1));
	strcpy(node0->super->super->name, "node0");
	node0->super->started = 1;
	
	ContainerNode* node1 = new_ContainerNode();
	/*printf("ContainerNode 'node0' created\n");*/
	node1->super->super->name = malloc(sizeof(char) * (strlen("node1") + 1));
	strcpy(node1->super->super->name, "node1");
	node1->super->started = 1;
	
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

	node0->AddComponents(node0, c1);
	node1->AddComponents(node1, c2);
	
	/*Group *group = factory.createGroup();
	group->name ="group0";
	group->started = true;
	group->addtypeDefinition(grouptype);*/
	Group* group = new_Group();
	/*printf("Group 'group' created\n");*/
	group->super->super->name = malloc(sizeof(char) * (strlen("group0") + 1));
	strcpy(group->super->super->name, "group0");
	group->super->metaData = malloc(sizeof(char) * (strlen("dummy_MetaData") + 1));
	strcpy(group->super->metaData, "dummy_MetaData");
	group->super->started = 1;
	/*group->super->AddTypeDefinition(group->super, grouptype);*/
	/*printf("Adding 'grouptype' to 'group'\n");*/
	
	/*FragmentDictionary *dico =factory.createFragmentDictionary();

	dico->name ="node0";
	DictionaryValue *valport = factory.createDictionaryValue();
	valport->name ="port";
	valport->value ="9001";

	dico->addvalues(valport);


	group->addfragmentDictionary(dico);*/

	/*TypeDefinition *comtype  = factory.createComponentType();
	comtype->name = "Light";
	comtype->abstract = false;*/
	TypeDefinition* comtype = newPoly_ComponentType();
	/*printf("ComponentType 'comtype' created\n");*/
	comtype->super->name = malloc(sizeof(char) * (strlen("Light") + 1));
	strcpy(comtype->super->name, "Light");
	comtype->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(comtype->version, "1.0.0-SNAPSHOT");
	comtype->abstract = 0;
	/*printf("'comtype' initialized\n");*/
	
	/*PortTypeRef *reglight = new PortTypeRef();
	reglight->name ="port";
	reglight->optional = true;*/
	PortTypeRef* reglight = new_PortTypeRef();
	/*printf("PortTypeRef 'reglight' created\n");*/
	reglight->super->name = malloc(sizeof(char) * (strlen("port0") + 1));
	strcpy(reglight->super->name, "port0");
	reglight->optional = 1;
	/*printf("'reglight' initialized\n");*/

	/*((ComponentType*)comtype)->addrequired(reglight);*/
	((ComponentType*)(comtype->pDerivedObj))->AddRequired((ComponentType*)(comtype->pDerivedObj), reglight);
	/*printf("Adding required PortTypeRef 'reglight' to ComponentType 'comtype'\n");*/
	
	
	/*DictionaryType *typegroup2= factory.createDictionaryType();
	DictionaryAttribute *attport2 = factory.createDictionaryAttribute();
	attport2->optional = false;
	attport2->datatype = "Boolean";
	attport2->fragmentDependant = false;
	attport2->name ="enable";
	attport2->defaultValue = "true";
	typegroup2->addattributes(attport2);




	DictionaryAttribute *attport3 = factory.createDictionaryAttribute();
	attport3->optional = false;
	attport3->datatype = "int";
	attport3->fragmentDependant = false;
	attport3->name ="pin";
	attport3->defaultValue = "7";

	typegroup2->addattributes(attport3);
	comtype->adddictionaryType(typegroup2);*/


	/*DeployUnit *dc =factory.createDeployUnit();
	dc->name = "LightComponent";
	dc->groupName = "org.kevoree.library";
	dc->version = "1.0.0-SNAPSHOT";
	dc->type ="so";*/
	DeployUnit* dc = new_DeployUnit();
	/*printf("DeployUnit 'dc' created\n");*/
	dc->super->name = malloc(sizeof(char) * (strlen("LightComponent") + 1));
	strcpy(dc->super->name, "LightComponent");
	dc->groupName = malloc(sizeof(char) * (strlen("org.kevoree.library") + 1));
	strcpy(dc->groupName, "org.kevoree.library");
	dc->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(dc->version, "1.0.0-SNAPSHOT");
	dc->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(dc->type,"ce");
	/*printf("DeployUnit 'dc' initialized\n");*/

	/*comtype->adddeployUnit(dc);*/
	comtype->AddDeployUnit(comtype, dc);
	/*printf("Adding 'dc' to 'comtype'\n");*/

	/*node0->addtypeDefinition(nodetype);*/
	node0->super->AddTypeDefinition(node0->super, nodetype);
	/*printf("Adding 'nodetype' to 'node0'\n");*/


	/* Temperature */
	/*TypeDefinition *anenotype  = factory.createComponentType();
	anenotype->name = "Temperature";
	anenotype->abstract = false;*/
	TypeDefinition* anenotype = newPoly_ComponentType();
	/*printf("ComponentType 'anenotype' created\n");*/
	anenotype->super->name = malloc(sizeof(char) * (strlen("Temperature") + 1));
	strcpy(anenotype->super->name, "Temperature");
	anenotype->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(anenotype->version, "1.0.0-SNAPSHOT");
	anenotype->abstract = 0;
	/*printf("ComponentType 'anenotype' initialized\n");*/
	
	/*ComponentType* test = new_ComponentType();
	test->super->super->name = malloc(sizeof(char) * (strlen("Test") + 1));
	strcpy(test->super->super->name, "Test");
	test->super->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(test->super->version, "1.0.0-SNAPSHOT");
	test->super->abstract = 0;*/
	

	/*PortTypeRef *reg = new PortTypeRef();
	reg->name ="port";
	reg->optional = true;*/
	PortTypeRef* reg = new_PortTypeRef();
	/*printf("PortTypeRef 'reg' created\n");*/
	reg->super->name = malloc(sizeof(char) * (strlen("port0") + 1));
	strcpy(reg->super->name, "port0");
	reg->optional = 1;
	/*printf("PortTypeRef 'reg' initialized\n");*/

	/*((ComponentType*)anenotype)->addrequired(reg);*/
	((ComponentType*)anenotype->pDerivedObj)->AddRequired((ComponentType*)anenotype->pDerivedObj, reg);
	/*printf("Adding required PortTypeRef 'reg' to ComponentType 'comtype'\n");*/

	/*DictionaryType *typeanomo= factory.createDictionaryType();
	anenotype->adddictionaryType(typeanomo);

	DictionaryAttribute *attportanom = factory.createDictionaryAttribute();
	attportanom->optional = false;
	attportanom->datatype = "int";
	attportanom->fragmentDependant = false;
	attportanom->name ="pin";
	attportanom->defaultValue = "7";
	typeanomo->addattributes(attportanom);*/

	/*DeployUnit *dcano =factory.createDeployUnit();
	dcano->name = "TemperatureComponent";
	dcano->groupName = "org.kevoree.library";
	dcano->version = "1.0.0-SNAPSHOT";
	dcano->type ="so";*/
	DeployUnit* dcano = new_DeployUnit();
	/*printf("DeployUnit 'dcano' created\n");*/
	dcano->super->name = malloc(sizeof(char) * (strlen("TemperatureComponent") + 1));
	strcpy(dcano->super->name, "TemperatureComponent");
	dcano->groupName = malloc(sizeof(char) * (strlen("org.kevoree.library") + 1));
	strcpy(dcano->groupName, "org.kevoree.library");
	dcano->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(dcano->version, "1.0.0-SNAPSHOT");
	dcano->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(dcano->type,"ce");
	/*printf("DeployUnit 'dcano' initialized\n");*/

	/* GW  */

	/*TypeDefinition *gwMQTTtype  = factory.createComponentType();
	gwMQTTtype->name = "WebSocketGatewayMQTT";
	gwMQTTtype->abstract = false;*/
	/*TypeDefinition* gwMQTTtype = newPoly_ComponentType();
	gwMQTTtype->super->name = malloc(sizeof(char) * (strlen("WebSocketGatewayMQTT") + 1));
	strcpy(gwMQTTtype->super->name, "WebSocketGatewayMQTT");
	gwMQTTtype->abstract = 0;*/

	/*DeployUnit *dcMQTTgw =factory.createDeployUnit();
	dcMQTTgw->name = "WebSocketGatewayMQTT";
	dcMQTTgw->groupName = "org.kevoree.library";
	dcMQTTgw->version = "1.0.0-SNAPSHOT";
	dcMQTTgw->type ="so";*/
	/*DeployUnit* dcMQTTgw = new_DeployUnit();
	dcMQTTgw->super->name = malloc(sizeof(char) * (strlen("WebSocketGatewayMQTT") + 1));
	strcpy(dcMQTTgw->super->name, "WebSocketGatewayMQTT");
	dcMQTTgw->groupName = malloc(sizeof(char) * (strlen("org.kevoree.library") + 1));
	strcpy(dcMQTTgw->groupName, "org.kevoree.library");
	dcMQTTgw->version = malloc(sizeof(char) * (strlen("1.0.0-SNAPSHOT") + 1));
	strcpy(dcMQTTgw->version,"1.0.0-SNAPSHOT");
	dcMQTTgw->type = malloc(sizeof(char) * (strlen("ce") + 1));
	strcpy(dcMQTTgw->type,"ce");*/


	/*DictionaryType *typegwMQTT= factory.createDictionaryType();
	DictionaryAttribute *attportGW = factory.createDictionaryAttribute();
	attportGW->optional = false;
	attportGW->datatype = "int";
	attportGW->fragmentDependant = false;
	attportGW->name ="port_gw";
	attportGW->defaultValue = "18883";
	typegwMQTT->addattributes(attportGW);
	gwMQTTtype->adddictionaryType(typegwMQTT);


	DictionaryAttribute *attportGW2 = factory.createDictionaryAttribute();
	attportGW2->optional = false;
	attportGW2->datatype = "int";
	attportGW2->fragmentDependant = false;
	attportGW2->name ="port_MQTT";
	attportGW2->defaultValue = "1883";
	typegwMQTT->addattributes(attportGW2);




	DictionaryAttribute *attportGW3 = factory.createDictionaryAttribute();
	attportGW3->optional = false;
	attportGW3->datatype = "int";
	attportGW3->fragmentDependant = false;
	attportGW3->name ="HOST_MQTT";
	attportGW3->defaultValue = "localhost";
	typegwMQTT->addattributes(attportGW3);

	gwMQTTtype->adddictionaryType(typegwMQTT);*/


	/*gwMQTTtype->adddeployUnit(dcMQTTgw);*/
	/*gwMQTTtype->AddDeployUnit(gwMQTTtype, dcMQTTgw);*/
	/*printf("Adding DeployUnit 'dcMQTTgw' to 'gwMQTTtype'\n");*/


	/*model->addtypeDefinitions(anenotype);
	model->addtypeDefinitions(grouptype);
	model->addtypeDefinitions(nodetype);
	model->addtypeDefinitions(comtype);
	model->addtypeDefinitions(gwMQTTtype);*/
	/*model->AddTypeDefinitions(model, anenotype);*/
	/*model->AddTypeDefinitions(model, grouptype);*/
	/*model->AddTypeDefinitions(model, nodetype);*/
	/*model->AddTypeDefinitions(model, comtype);*/
	/*model->AddTypeDefinitions(model, gwMQTTtype);*/
	/*printf("Adding TypeDefinition 'anenotype', 'grouptype', 'nodetype', 'comtype', 'gwMQTTtype' to 'model'\n");*/

	/*model->adddeployUnits(d);
	model->adddeployUnits(dg);
	model->adddeployUnits(dc);
	model->adddeployUnits(dcano);
	model->adddeployUnits(dcMQTTgw);*/
	model->AddDeployUnits(model, d);
	/*model->AddDeployUnits(model, dg);*/
	model->AddDeployUnits(model, dc);
	model->AddDeployUnits(model, dcano);
	/*model->AddDeployUnits(model, dcMQTTgw);*/
	/*printf("Adding DeployUnit 'd', 'dg', 'dc', 'dcano', 'dcMQTTgw' to 'model'\n");*/

	/*model->addnodes(node0);*/
	model->AddNodes(model, node0);
	/*model->AddNodes(model, node1->pDerivedObj);*/
	/*printf("Adding 'node0' -> %s to 'model' -> %i\n", node0->super->super->name, model);*/
	model2->AddNodes(model2, node0);
	model2->AddNodes(model2, node1);
	printf("node0 and node1 added to \"%s\"\n", model2->InternalGetKey(model2));

	/*model->addgroups(group);
	group->addsubNodes(node0);
	node0->addgroups(group);*/
	model->AddGroups(model, group);
	/*printf("Adding 'group' -> %s to 'model' -> %i\n", group->super->super->name, model);*/
	group->AddSubNodes(group, node0);
	/*printf("Adding subnode '%s' to group '%s'\n", node0->super->super->name, group->super->super->name);*/
	node0->AddGroups(node0, group);
	/*printf("Adding group '%s' to node '%s'\n", group->super->super->name, node0->super->super->name);*/

	/*kb->setBootstrapModel(model); // boostrapmodel
	kb->start();

	clock_t finish = clock();
	std::cin >> exit;*/
	printf("Model created with sucess!\n");
	
	Visitor* visitor_print = (Visitor*)malloc(sizeof(Visitor));

	/*visitor_print->action =  actionprintf;*/
	visitor_print->action =  ActionCompare;

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
