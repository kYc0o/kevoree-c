#include "ContainerNode.h"

Instance* newPoly_ContainerNode()
{
	ContainerNode* pContNodeObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pContNodeObj = (ContainerNode*)malloc(sizeof(pContNodeObj));

	if (pContNodeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pContNodeObj; /* Pointing to derived object */
	/*pContNodeObj->super = pObj;*/
	
	/*pContNodeObj->components = hashmap_new();
	pContNodeObj->hosts = hashmap_new();
	pContNodeObj->groups = hashmap_new();
	pContNodeObj->networkInformation = hashmap_new();*/
	pContNodeObj->components = NULL;
	pContNodeObj->hosts = NULL;
	pContNodeObj->host = NULL;
	pContNodeObj->groups = NULL;
	pContNodeObj->networkInformation = NULL;
	
	pContNodeObj->FindComponentsByID = ContainerNode_FindComponentsByID;
	pContNodeObj->FindHostsByID = ContainerNode_FindHostsByID;
	pContNodeObj->FindGroupsByID = ContainerNode_FindGroupsByID;
	pContNodeObj->FindNetworkInformationByID = ContainerNode_FindNetworkInformationByID;
	pContNodeObj->AddComponents = ContainerNode_AddComponents;
	pContNodeObj->AddHosts = ContainerNode_AddHosts;
	pContNodeObj->AddHost = ContainerNode_AddHost;
	pContNodeObj->AddGroups = ContainerNode_AddGroups;
	pContNodeObj->AddNetworkInformation = ContainerNode_AddNetworkInformation;
	pContNodeObj->RemoveComponents = ContainerNode_RemoveComponents;
	pContNodeObj->RemoveHost = ContainerNode_RemoveHost;
	pContNodeObj->RemoveHosts = ContainerNode_RemoveHosts;
	pContNodeObj->RemoveGroups = ContainerNode_RemoveGroups;
	pContNodeObj->RemoveNetworkInformation = ContainerNode_RemoveNetworkInformation;
	
	pObj->MetaClassName = ContainerNode_MetaClassName;
	pObj->InternalGetKey = ContainerNode_InternalGetKey;
	pObj->VisitAttributes = ContainerNode_VisitAttributes;
	pObj->VisitReferences = ContainerNode_VisitReferences;
	pObj->FindByPath = ContainerNode_FindByPath;
	
	pObj->Delete = deletePoly_ContainerNode;

	return pObj;
}

ContainerNode* new_ContainerNode()
{
	ContainerNode* pContNodeObj = NULL;
	Instance* pObj = new_Instance();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pContNodeObj = (ContainerNode*)malloc(sizeof(ContainerNode));

	if (pContNodeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	/*pObj->pDerivedObj = pContNodeObj; Pointing to derived object */
	pContNodeObj->super = pObj;
	
	/*pContNodeObj->components = hashmap_new();
	pContNodeObj->hosts = hashmap_new();
	pContNodeObj->groups = hashmap_new();
	pContNodeObj->networkInformation = hashmap_new();*/
	pContNodeObj->components = NULL;
	pContNodeObj->hosts = NULL;
	pContNodeObj->host = NULL;
	pContNodeObj->groups = NULL;
	pContNodeObj->networkInformation = NULL;
	
	pContNodeObj->FindComponentsByID = ContainerNode_FindComponentsByID;
	pContNodeObj->FindHostsByID = ContainerNode_FindHostsByID;
	pContNodeObj->FindGroupsByID = ContainerNode_FindGroupsByID;
	pContNodeObj->FindNetworkInformationByID = ContainerNode_FindNetworkInformationByID;
	pContNodeObj->AddComponents = ContainerNode_AddComponents;
	pContNodeObj->AddHosts = ContainerNode_AddHosts;
	pContNodeObj->AddHost = ContainerNode_AddHost;
	pContNodeObj->AddGroups = ContainerNode_AddGroups;
	pContNodeObj->AddNetworkInformation = ContainerNode_AddNetworkInformation;
	pContNodeObj->RemoveComponents = ContainerNode_RemoveComponents;
	pContNodeObj->RemoveHost = ContainerNode_RemoveHost;
	pContNodeObj->RemoveHosts = ContainerNode_RemoveHosts;
	pContNodeObj->RemoveGroups = ContainerNode_RemoveGroups;
	pContNodeObj->RemoveNetworkInformation = ContainerNode_RemoveNetworkInformation;
	
	pContNodeObj->MetaClassName = ContainerNode_MetaClassName;
	pContNodeObj->InternalGetKey = ContainerNode_InternalGetKey;
	pContNodeObj->VisitAttributes = ContainerNode_VisitAttributes;
	pContNodeObj->VisitReferences = ContainerNode_VisitReferences;
	pContNodeObj->FindByPath = ContainerNode_FindByPath;
	
	pContNodeObj->Delete = delete_ContainerNode;

	return pContNodeObj;
}

char* ContainerNode_InternalGetKey(ContainerNode* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->super->name);

	return internalKey;
}

char* ContainerNode_MetaClassName(ContainerNode* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("ContainerNode") + 1));
	strcpy(name, "ContainerNode");
	
	return name;
}

/*ComponentInstance* ContainerNode::findcomponentsByID(std::string id){*/
ComponentInstance* ContainerNode_FindComponentsByID(ContainerNode* const this, char* id)
{
	ComponentInstance* value;
	
	if(this->components != NULL)
	{
		if(hashmap_get(this->components, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

	/*return components[id];*/
}

/*ContainerNode* ContainerNode::findhostsByID(std::string id)*/
ContainerNode* ContainerNode_FindHostsByID(ContainerNode* const this, char* id)
{
	ContainerNode* value;
	
	if(this->hosts != NULL)
	{
		if(hashmap_get(this->hosts, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

	/*return hosts[id];*/
}

/*Group* ContainerNode::findgroupsByID(std::string id)*/
Group* ContainerNode_FindGroupsByID(ContainerNode* const this, char* id)
{
	Group* value;

	if(this->groups != NULL)
	{
		if(hashmap_get(this->groups, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

	/*return groups[id];*/
}

/*NetworkInfo* ContainerNode::findnetworkInformationByID(std::string id)*/
NetworkInfo* ContainerNode_FindNetworkInformationByID(ContainerNode* const this, char* id)
{
	NetworkInfo* value;

	if(this->networkInformation != NULL)
	{
		if(hashmap_get(this->networkInformation, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

	/*return networkInformation[id];*/
}

/*void ContainerNode::addcomponents(ComponentInstance *ptr)*/
void ContainerNode_AddComponents(ContainerNode* const this, ComponentInstance* ptr)
{
	ComponentInstance* container = (ComponentInstance*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The ComponentInstance cannot be added in ContainerNode because the key is not defined");*/
		printf("The ComponentInstance cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*if(components.find(container->internalGetKey()) == components.end())*/
		if(this->components == NULL)
		{
			this->components = hashmap_new();
		}
		if(hashmap_get(this->components, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING)
		{
			/*components[container->internalGetKey()]=ptr;*/
			container = (ComponentInstance*)ptr;
			hashmap_put(this->components, container->InternalGetKey(container), ptr);
			/*any ptr_any = container;
			RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"components",ptr_any);
			container->setEContainer(this,cmd,"components");*/
		}
	}
}

/*void ContainerNode::addhosts(ContainerNode *ptr)*/
void ContainerNode_AddHosts(ContainerNode* const this, ContainerNode* ptr)
{
	ContainerNode* container = (ContainerNode*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be added in ContainerNode because the key is not defined");*/
		printf("The ContainerNode cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*if(hosts.find(container->internalGetKey()) == hosts.end())*/
		if(this->hosts == NULL)
		{
			this->hosts = hashmap_new();
		}
		if(hashmap_get(this->hosts, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING)
		{
			/*hosts[container->internalGetKey()]=ptr;*/
			container = (ContainerNode*)ptr;
			hashmap_put(this->hosts, container->InternalGetKey(container), ptr);
		}
	}
}

/*void ContainerNode::addhost(ContainerNode *ptr)*/
void ContainerNode_AddHost(ContainerNode* const this, ContainerNode* ptr)
{
	this->host = ptr;
	/*host =ptr;*/
}

/*void ContainerNode::addgroups(Group *ptr)*/
void ContainerNode_AddGroups(ContainerNode* const this, Group* ptr)
{
	Group* container = (Group*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The Group cannot be added in ContainerNode because the key is not defined");*/
		printf("The Group cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*if(groups.find(container->internalGetKey()) == groups.end())*/
		if(this->groups == NULL)
		{
			this->groups = hashmap_new();
		}
		if(hashmap_get(this->groups, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING)
		{
			/*groups[container->internalGetKey()]=ptr;*/
			container = (Group*)ptr;
			hashmap_put(this->groups, container->InternalGetKey(container), ptr);
		}
	}
}

/*void ContainerNode::addnetworkInformation(NetworkInfo *ptr)*/
void ContainerNode_AddNetworkInformation(ContainerNode* const this, NetworkInfo* ptr)
{
	NetworkInfo* container = (NetworkInfo*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkInfo cannot be added in ContainerNode because the key is not defined");*/
		printf("The NetworkInfo cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*if(networkInformation.find(container->internalGetKey()) == networkInformation.end())*/
		if(this->networkInformation == NULL)
		{
			this->networkInformation = hashmap_new();
		}
		if(hashmap_get(this->networkInformation, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING)
		{
			/*networkInformation[container->internalGetKey()]=ptr;*/
			container = (NetworkInfo*)ptr;
			hashmap_put(this->networkInformation, container->InternalGetKey(container), ptr);
			/*any ptr_any = container;
			RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"networkInformation",ptr_any);
			container->setEContainer(this,cmd,"networkInformation");*/
		}
	}
}

/*void ContainerNode::removecomponents(ComponentInstance *ptr)*/
void ContainerNode_RemoveComponents(ContainerNode* const this, ComponentInstance* ptr)
{
	ComponentInstance* container = (ComponentInstance*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The ComponentInstance cannot be removed in ContainerNode because the key is not defined");*/
		printf("The ComponentInstance cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*components.erase( components.find(container->internalGetKey()));*/
		hashmap_remove(this->components, container->InternalGetKey(container));
		/*delete container;
		container->setEContainer(NULL,NULL,"");*/
	}
}

/*void ContainerNode::removehosts(ContainerNode *ptr)*/
void ContainerNode_RemoveHosts(ContainerNode* const this, ContainerNode* ptr)
{
	ContainerNode* container = (ContainerNode*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be removed in ContainerNode because the key is not defined");*/
		printf("The ContainerNode cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*hosts.erase( hosts.find(container->internalGetKey()));*/
		hashmap_remove(this->hosts, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

/*void ContainerNode::removehost(ContainerNode *ptr)*/
void ContainerNode_RemoveHost(ContainerNode* const this, ContainerNode* ptr)
{
	/*delete ptr;*/
	free(ptr);
}

/*void ContainerNode::removegroups(Group *ptr)*/
void ContainerNode_RemoveGroups(ContainerNode* const this, Group* ptr)
{
	Group* container = (Group*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The Group cannot be removed in ContainerNode because the key is not defined");*/
		printf("The Group cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*groups.erase( groups.find(container->internalGetKey()));*/
		hashmap_remove(this->groups, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

/*void ContainerNode::removenetworkInformation(NetworkInfo *ptr)*/
void ContainerNode_RemoveNetworkInformation(ContainerNode* const this, NetworkInfo* ptr)
{
	NetworkInfo* container = (NetworkInfo*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkInfo cannot be removed in ContainerNode because the key is not defined");*/
		printf("The NetworkInfo cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		/*networkInformation.erase( networkInformation.find(container->internalGetKey()));*/
		hashmap_remove(this->networkInformation, container->InternalGetKey(container));
		/*delete container;
		container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_ContainerNode(Instance* const this)
{
	ContainerNode* pContNodeObj;
	pContNodeObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pContNodeObj->components);
	hashmap_free(pContNodeObj->hosts);
	hashmap_free(pContNodeObj->groups);
	hashmap_free(pContNodeObj->networkInformation);
	free(pContNodeObj->host);
	free(pContNodeObj);
	/*destroy base Obj*/
	delete_Instance(this);
}

void delete_ContainerNode(ContainerNode* const this)
{
	/* destroy base object */
	delete_Instance(this->super);
	/* destroy data memebers */
	hashmap_free(this->components);
	hashmap_free(this->hosts);
	hashmap_free(this->groups);
	hashmap_free(this->networkInformation);
	free(this->host);
	free(this);
}

void ContainerNode_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	/*char path[128];
	memset(&path[0], 0, sizeof(path));*/
	
	/*sprintf(path, "%s/%s", parent, ((ContainerNode*)(this))->super->super->name);*/
	
	/*sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((ContainerNode*)(this))->super->super->name);

	sprintf(path,"%s\\started", parent);
	visitor->action(path, BOOL, (void*)((ContainerNode*)(this))->super->started);*/
	Instance_VisitAttributes(((ContainerNode*)(this))->super, parent, visitor);
}

void ContainerNode_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	Instance_VisitReferences(((ContainerNode*)(this))->super, parent, visitor);
	
	if(((ContainerNode*)(this))->components != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/components[%s]", parent, ((ContainerNode*)(this))->super->super->name);*/
		
		/* components */
		hashmap_map* m = ((ContainerNode*)(this))->components;

		/* compare components */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ComponentInstance* n = data;
				sprintf(path,"%s/components[%s]", parent, /*n->super->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
	
	if(((ContainerNode*)(this))->hosts != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/hosts[%s]", parent, ((ContainerNode*)(this))->super->super->name);*/
		
		/* hosts */
		hashmap_map* m = ((ContainerNode*)(this))->hosts;

		/* compare hosts */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				sprintf(path,"%s/hosts[%s]", parent, /*n->super->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
	
	if(((ContainerNode*)(this))->host != NULL)
	{
		sprintf(path, "%s/host[%s]", parent, /*((ContainerNode*)(this))->host->super->super->name*/((ContainerNode*)(this))->host->InternalGetKey(((ContainerNode*)(this))->host));
		((ContainerNode*)(this))->host->VisitAttributes(((ContainerNode*)(this))->host, path, visitor);
		((ContainerNode*)(this))->host->VisitReferences(((ContainerNode*)(this))->host, path, visitor);
	}
	
	if(((ContainerNode*)(this))->networkInformation != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/networkInformation[%s]", parent, ((ContainerNode*)(this))->super->super->name);*/
		
		/* networkInformation */
		hashmap_map* m = ((ContainerNode*)(this))->networkInformation;

		/* compare networkInformation */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkInfo* n = data;
				sprintf(path,"%s/networkInformation[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
	
	if(((ContainerNode*)(this))->groups != NULL)
	{
		int i;
		
		sprintf(path,"%s/groups[%s]", parent, ((ContainerNode*)(this))->super->super->name);
		
		/* groups */
		hashmap_map* m = ((ContainerNode*)(this))->groups;

		/* compare groups */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				sprintf(path, "%s/groups[%s]", parent, /*n->super->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				/*n->VisitReferences(n, path, visitor);*/
			}
		}
	}
}

void* ContainerNode_FindByPath(char* attribute, ContainerNode* const this)
{
	/* There is no local attributes */
	
	/* Instance attributes and references */
	if(!strcmp("name", attribute) ||  !strcmp("metaData", attribute) || !strcmp("started", attribute) || !strcmp("typeDefinition", attribute))
	{
		return Instance_FindByPath(attribute, this->super);/*return this->super->metaData;*/
	}
	/* Local references */
	else
	{
		char* nextAttribute = NULL;
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
			/*nextAttribute = strtok(NULL, "\\");
			sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));*/
			/*printf("pch: %s\n", pch);*/
			if(strchr(attribute,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);*/
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not found...\n");*/
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}
		
		printf("Token: %s\n", pch);

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);
	  
		if(!strcmp("components", relationName))
		{
			if(nextAttribute == NULL)
			{
				
				return this->FindComponentsByID(this, queryID);
			}
			else
			{
				ComponentInstance* compins = this->FindComponentsByID(this, queryID);
				if(compins != NULL)
					return compins->FindByPath(nextAttribute, compins);
				else
					return NULL;
			}
		}
		else if(!strcmp("hosts", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindHostsByID(this, queryID);
			}
			else
			{
				ContainerNode* contnode = this->FindHostsByID(this, queryID);
				if(contnode != NULL)
					return contnode->FindByPath(nextAttribute, contnode);
				else
					return NULL;
			}
		}
		else if(!strcmp("host", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->host;
			}
			else
			{
				return this->host->FindByPath(nextAttribute, this->host);
			}
		}
		else if(!strcmp("networkInformation", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindNetworkInformationByID(this, queryID);
			}
			else
			{
				NetworkInfo* netinfo = this->FindNetworkInformationByID(this, queryID);
				if(netinfo != NULL)
					return netinfo->FindByPath(nextAttribute, netinfo);
				else
					return NULL;
			}
		}
		else if(!strcmp("groups", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindGroupsByID(this, queryID);
			}
			else
			{
				Group* group = this->FindGroupsByID(this, queryID);
				if(group != NULL)
					return group->FindByPath(nextAttribute, group);
				else
					return NULL;
			}
		}
		/* Instance references */
		else
		{
			return Instance_FindByPath(attribute, this->super);
		}
	}
}

/*int _acceptContainerNode(ContainerNode* this, ContainerNode* c, Visitor* visitor)
{
	int i;

	for(i = 0; i < this->count_components; i++)
	{
		visitor->action((void*)this->components, (void*)c->components, 0);
	}
	
	for(i = 0; i < this->count_groups; i++)
	{
		visitor->action((void*)this->groups, (void*)c->groups, 0);
	}

	for(i = 0; i < this->count_networkInformation; i++)
	{
		visitor->action((void*)this->networkInformation, (void*)c->networkInformation, 0);
	}
}*/