/*#include "DefaultFactorykevoree.h"*/
//#include "Comparekevoree.h"
#include <stdlib.h>
#include <stdio.h>
#include "kevoree.h"


/*void actionprintf(void *val,void *val2,int type)
{
	switch(type)
	{
		case 0:
			if(val != NULL)
				printf("%s - %s \n",(char*)val,(char*)val2);
			break;

		case 1:
			printf("%d\n",(int)val);
			break;
	  
	}
}*/

ContainerRoot *model = NULL;

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

	/*model = factory.createContainerRoot();*/
	model = new_ContainerRoot();

	/*DeployUnit *d =factory.createDeployUnit();
	d->name = "CPPNodeType";
	d->groupName = "org.kevoree.library";
	d->version = "1.0.0-SNAPSHOT";
	d->type ="so";*/
	DeployUnit* d = new_DeployUnit();
	strcpy(d->super->name, "ContikiNodeType");
	strcpy(d->groupName, "org.kevoree.library");
	strcpy(d->version,"1.0.0-SNAPSHOT");
	strcpy(d->type,"ce");

	/*TypeDefinition *nodetype = factory.createNodeType();
	nodetype->name = "CPPNode";
	nodetype->abstract= false;
	nodetype->adddeployUnit(d);*/
	TypeDefinition* nodetype = newPoly_NodeType();
	strcpy(nodetype->super->name, "ContikiNode");
	nodetype->abstract = 0;
	nodetype->AddDeployUnit(nodetype, d);

	/*DeployUnit *dg =factory.createDeployUnit();
	dg->name = "kevoree-group-websocket";
	dg->groupName = "org.kevoree.library";
	dg->version = "1.0.0-SNAPSHOT";
	dg->type ="so";*/
	DeployUnit* dg = new_DeployUnit();
	strcpy(dg->super->name, "kevoree-group-websocket");
	strcpy(dg->groupName, "org.kevoree.library");
	strcpy(dg->version,"1.0.0-SNAPSHOT");
	strcpy(dg->type,"ce");
	
	/*TypeDefinition *grouptype = factory.createGroupType();
	grouptype->abstract= false;
	grouptype->name ="WebSocketGroup";
	grouptype->version = "1.0";*/
	TypeDefinition* grouptype = newPoly_GroupType();
	grouptype->abstract = 0;
	strcpy(grouptype->super->name, "WebSocketGroup");
	strcpy(grouptype->version, "1.0");

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
	node0->super->started = 1;


	/*Group *group = factory.createGroup();
	group->name ="group0";
	group->started = true;
	group->addtypeDefinition(grouptype);*/
	Group* group = new_Group();
	group->super->started = 1;
	group->super->AddTypeDefinition(group->super, grouptype);
	
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
	strcpy(comtype->super->name, "Light");
	comtype->abstract = 0;
	
	
	/*PortTypeRef *reglight = new PortTypeRef();
	reglight->name ="port";
	reglight->optional = true;*/
	PortTypeRef* reglight = new_PortTypeRef();
	strcpy(reglight->super->name, "port");
	reglight->optional = 1;

	/*((ComponentType*)comtype)->addrequired(reglight);*/
	((ComponentType*)comtype->pDerivedObj)->AddRequired((ComponentType*)comtype->pDerivedObj, reglight);

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
	strcpy(dc->super->name, "LightComponent");
	strcpy(dc->groupName, "org.kevoree.library");
	strcpy(dc->version,"1.0.0-SNAPSHOT");
	strcpy(dc->type,"ce");

	/*comtype->adddeployUnit(dc);*/
	comtype->AddDeployUnit(comtype, dc);

	/*node0->addtypeDefinition(nodetype);*/
	node0->super->AddTypeDefinition(node0->super, nodetype);


	/* Temperature */
	/*TypeDefinition *anenotype  = factory.createComponentType();
	anenotype->name = "Temperature";
	anenotype->abstract = false;*/
	TypeDefinition* anenotype = newPoly_ComponentType();
	strcpy(anenotype->super->name, "Temperature");
	anenotype->abstract = 0;

	/*PortTypeRef *reg = new PortTypeRef();
	reg->name ="port";
	reg->optional = true;*/
	PortTypeRef* reg = new_PortTypeRef();
	strcpy(reg->super->name, "port");
	reg->optional = 1;

	/*((ComponentType*)anenotype)->addrequired(reg);*/
	((ComponentType*)comtype->pDerivedObj)->AddRequired((ComponentType*)comtype->pDerivedObj, reg);

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
	strcpy(dcano->super->name, "TemperatureComponent");
	strcpy(dcano->groupName, "org.kevoree.library");
	strcpy(dcano->version,"1.0.0-SNAPSHOT");
	strcpy(dcano->type,"ce");

	/* GW  */

	/*TypeDefinition *gwMQTTtype  = factory.createComponentType();
	gwMQTTtype->name = "WebSocketGatewayMQTT";
	gwMQTTtype->abstract = false;*/
	TypeDefinition* gwMQTTtype = newPoly_ComponentType();
	strcpy(gwMQTTtype->super->name, "WebSocketGatewayMQTT");
	gwMQTTtype->abstract = 0;

	/*DeployUnit *dcMQTTgw =factory.createDeployUnit();
	dcMQTTgw->name = "WebSocketGatewayMQTT";
	dcMQTTgw->groupName = "org.kevoree.library";
	dcMQTTgw->version = "1.0.0-SNAPSHOT";
	dcMQTTgw->type ="so";*/
	DeployUnit* dcMQTTgw = new_DeployUnit();
	strcpy(dcMQTTgw->super->name, "WebSocketGatewayMQTT");
	strcpy(dcMQTTgw->groupName, "org.kevoree.library");
	strcpy(dcMQTTgw->version,"1.0.0-SNAPSHOT");
	strcpy(dcMQTTgw->type,"ce");


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
	gwMQTTtype->AddDeployUnit(gwMQTTtype, dcMQTTgw);


	/*model->addtypeDefinitions(anenotype);
	model->addtypeDefinitions(grouptype);
	model->addtypeDefinitions(nodetype);
	model->addtypeDefinitions(comtype);
	model->addtypeDefinitions(gwMQTTtype);*/
	model->AddTypeDefinitions(model, anenotype);
	model->AddTypeDefinitions(model, grouptype);
	model->AddTypeDefinitions(model, nodetype);
	model->AddTypeDefinitions(model, comtype);
	model->AddTypeDefinitions(model, gwMQTTtype);

	/*model->adddeployUnits(d);
	model->adddeployUnits(dg);
	model->adddeployUnits(dc);
	model->adddeployUnits(dcano);
	model->adddeployUnits(dcMQTTgw);*/
	model->AddDeployUnits(model, d);
	model->AddDeployUnits(model, dg);
	model->AddDeployUnits(model, dc);
	model->AddDeployUnits(model, dcano);
	model->AddDeployUnits(model, dcMQTTgw);

	/*model->addnodes(node0);*/
	model->AddNodes(model, node0);

	/*model->addgroups(group);
	group->addsubNodes(node0);
	node0->addgroups(group);*/
	model->AddGroups(model, group);
	group->AddSubNodes(group, node0);
	node0->AddGroups(node0, group);

	/*kb->setBootstrapModel(model); // boostrapmodel
	kb->start();



	clock_t finish = clock();
	std::cin >> exit;*/


 return 0;
}