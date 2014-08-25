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
	pContNodeObj->super = pObj;

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
	return this->super->InternalGetKey(this->super);
}

char* ContainerNode_MetaClassName(ContainerNode* const this)
{
	char name[14];
	memset(&name[0], 0, sizeof(name));

	/*name = malloc(sizeof(char) * (strlen("ContainerNode") + 1));*/
	strcpy(name, "ContainerNode");
	
	return name;
}

ComponentInstance* ContainerNode_FindComponentsByID(ContainerNode* const this, char* id)
{
	ComponentInstance* value = NULL;
	
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

}

ContainerNode* ContainerNode_FindHostsByID(ContainerNode* const this, char* id)
{
	ContainerNode* value = NULL;
	
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

}

Group* ContainerNode_FindGroupsByID(ContainerNode* const this, char* id)
{
	Group* value = NULL;

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

}

NetworkInfo* ContainerNode_FindNetworkInformationByID(ContainerNode* const this, char* id)
{
	NetworkInfo* value = NULL;

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

}

void ContainerNode_AddComponents(ContainerNode* const this, ComponentInstance* ptr)
{
	ComponentInstance* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The ComponentInstance cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->components == NULL)
		{
			this->components = hashmap_new();
		}
		if(hashmap_get(this->components, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (ComponentInstance*)ptr;*/
			hashmap_put(this->components, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void ContainerNode_AddHosts(ContainerNode* const this, ContainerNode* ptr)
{
	ContainerNode* container = NULL;

	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The ContainerNode cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->hosts == NULL)
		{
			this->hosts = hashmap_new();
		}
		if(hashmap_get(this->hosts, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (ContainerNode*)ptr;*/
			hashmap_put(this->hosts, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void ContainerNode_AddHost(ContainerNode* const this, ContainerNode* ptr)
{
	this->host = ptr;
}

void ContainerNode_AddGroups(ContainerNode* const this, Group* ptr)
{
	Group* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The Group cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->groups == NULL)
		{
			this->groups = hashmap_new();
		}
		if(hashmap_get(this->groups, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (Group*)ptr;*/
			hashmap_put(this->groups, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void ContainerNode_AddNetworkInformation(ContainerNode* const this, NetworkInfo* ptr)
{
	NetworkInfo* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The NetworkInfo cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->networkInformation == NULL)
		{
			this->networkInformation = hashmap_new();
		}
		if(hashmap_get(this->networkInformation, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (NetworkInfo*)ptr;*/
			hashmap_put(this->networkInformation, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void ContainerNode_RemoveComponents(ContainerNode* const this, ComponentInstance* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The ComponentInstance cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->components, ptr->InternalGetKey(ptr));
	}
}

void ContainerNode_RemoveHosts(ContainerNode* const this, ContainerNode* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The ContainerNode cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->hosts, ptr->InternalGetKey(ptr));
	}
}

void ContainerNode_RemoveHost(ContainerNode* const this, ContainerNode* ptr)
{
	free(ptr);
}

void ContainerNode_RemoveGroups(ContainerNode* const this, Group* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The Group cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->groups, ptr->InternalGetKey(ptr));
	}
}

void ContainerNode_RemoveNetworkInformation(ContainerNode* const this, NetworkInfo* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The NetworkInfo cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->networkInformation, ptr->InternalGetKey(ptr));
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

void ContainerNode_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	Instance_VisitAttributes(((ContainerNode*)(this))->super, parent, visitor, recursive);
}

void ContainerNode_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	Instance_VisitReferences(((ContainerNode*)(this))->super, parent, visitor, 0);
	
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
				sprintf(path,"%s/components[%s]", parent, n->InternalGetKey(n));
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
				sprintf(path,"%s/hosts[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor, 0);
				/*n->VisitReferences(n, path, visitor);*/
			}
		}
	}
	
	if(((ContainerNode*)(this))->host != NULL)
	{
		sprintf(path, "%s/host[%s]", parent, ((ContainerNode*)(this))->host->InternalGetKey(((ContainerNode*)(this))->host));
		((ContainerNode*)(this))->host->VisitAttributes(((ContainerNode*)(this))->host, path, visitor, 0);
		/*((ContainerNode*)(this))->host->VisitReferences(((ContainerNode*)(this))->host, path, visitor);*/
	}
	
	if(((ContainerNode*)(this))->groups != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/groups[%s]", parent, ((ContainerNode*)(this))->super->super->name);*/
		
		/* groups */
		hashmap_map* m = ((ContainerNode*)(this))->groups;

		/* compare groups */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				sprintf(path, "%s/groups[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor, 0);
				/*n->VisitReferences(n, path, visitor);*/
			}
		}
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
}

void* ContainerNode_FindByPath(char* attribute, ContainerNode* const this)
{
	/* There is no local attributes */
	
	/* Instance attributes and references */
	if(!strcmp("name", attribute) ||  !strcmp("metaData", attribute) || !strcmp("started", attribute) /*|| !strcmp("typeDefinition", attribute)*/)
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
