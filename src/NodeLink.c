#include "NodeLink.h"

NodeLink* new_NodeLink()
{
	NodeLink* pObj;
	/* Allocating memory */
	pObj = (NodeLink*)malloc(sizeof(NodeLink));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;

	/*pObj->generated_KMF_ID = malloc(sizeof(char) * (strlen("dummyKMFID_NodeLink") + 1));Uuid::getSingleton().generateUUID();
	strcpy(pObj->generated_KMF_ID, "dummyKMFID_NodeLink");*/
	pObj->generated_KMF_ID = malloc(sizeof(char) * 8 + 1);
	rand_str(pObj->generated_KMF_ID, 8);
	/*pObj->networkProperties = hashmap_new();*/
	pObj->networkType = NULL;
	pObj->estimatedRate = -1;
	pObj->lastCheck = NULL;
	pObj->zoneID = NULL;
	pObj->networkProperties = NULL;
	
	pObj->InternalGetKey = NodeLink_InternalGetKey;
	pObj->MetaClassName = NodeLink_MetaClassName;
	pObj->FindNetworkPropertiesByID = NodeLink_FindNetworkPropertiesByID;
	pObj->AddNetworkProperties = NodeLink_AddNetworkProperties;
	pObj->RemoveNetworkProperties = NodeLink_RemoveNetworkProperties;
	pObj->Delete = delete_NodeLink;
	pObj->VisitAttributes = NodeLink_VisitAttributes;
	pObj->VisitReferences = NodeLink_VisitReferences;
	pObj->FindByPath = NodeLink_FindByPath;
	
	return pObj;
}

char* NodeLink_InternalGetKey(NodeLink* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->generated_KMF_ID)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->generated_KMF_ID);

	return internalKey;
}

char* NodeLink_MetaClassName(NodeLink* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NodeLink") + 1));
	strcpy(name, "NodeLink");
	
	return name;
}

/*NetworkProperty* NodeLink::findnetworkPropertiesByID(std::string id)*/
NetworkProperty* NodeLink_FindNetworkPropertiesByID(NodeLink* const this, char* id)
{
	NetworkProperty* value;

	if(hashmap_get(this->networkProperties, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
	/*return networkProperties[id];*/
}

/*void NodeLink::addnetworkProperties(NetworkProperty *ptr)*/
void NodeLink_AddNetworkProperties(NodeLink* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = (NetworkProperty*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be added in NodeLink because the key is not defined");*/
		printf("The NetworkProperty cannot be added in NodeLink because the key is not defined\n");
	}
	else
	{
		/*if(networkProperties.find(container->internalGetKey()) == networkProperties.end())*/
		if(this->networkProperties == NULL)
		{
			this->networkProperties = hashmap_new();
		}
		if(hashmap_get(this->networkProperties, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*networkProperties[container->internalGetKey()]=ptr;*/
			container = (NetworkProperty*)ptr;
			hashmap_put(this->networkProperties, container->InternalGetKey(container), ptr);
			/*any ptr_any = container;
			RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"networkProperties",ptr_any);
			container->setEContainer(this,cmd,"networkProperties");*/
		}
	}
}

/*void NodeLink::removenetworkProperties(NetworkProperty *ptr)*/
void NodeLink_RemoveNetworkProperties(NodeLink* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = (NetworkProperty*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be removed in NodeLink because the key is not defined");*/
		printf("The NetworkProperty cannot be removed in NodeLink because the key is not defined\n");
	}
	else
	{
		/*networkProperties.erase( networkProperties.find(container->internalGetKey()));*/
		hashmap_remove(this->networkProperties, container->InternalGetKey(container));
		/*delete container;
		container->setEContainer(NULL,NULL,"");*/
	}
}

void delete_NodeLink(NodeLink* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->networkType);
		free(this->lastCheck);
		free(this->zoneID);
		free(this->generated_KMF_ID);
		hashmap_free(this->networkProperties);
		free(this);
	}
}

void NodeLink_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path, "%s/%s", parent, ((NodeLink*)(this))->generated_KMF_ID);*/

	sprintf(path, "%s\\ID", parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->generated_KMF_ID);
	
	sprintf(path, "%s\\networkType", parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->networkType);
	
	sprintf(path,"%s\\lastCheck",parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->lastCheck);
	
	sprintf(path,"%s\\zoneID",parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->zoneID);
	
	sprintf(path, "%s\\estimatedRate", parent);
	visitor->action(path, BOOL, ((NodeLink*)(this))->estimatedRate);
}

void NodeLink_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	if(((NodeLink*)(this))->networkProperties != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/networkProperties[%s]", parent, ((NodeLink*)(this))->generated_KMF_ID);*/
		
		/* networkProperties */
		hashmap_map* m = ((NodeLink*)(this))->networkProperties;

		/* compare networkProperties */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				sprintf(path,"%s/networkProperties[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				/*n->VisitReferences(n, parent, visitor);*/
			}
		}
	}
}

void* NodeLink_FindByPath(char* attribute, NodeLink* const this)
{
	/* Local attributes */
	if(!strcmp("networkType", attribute))
	{
		return this->networkType;
	}
	else if(!strcmp("estimatedRate", attribute))
	{
		return this->estimatedRate;
	}
	else if(!strcmp("lastCheck", attribute))
	{
		return this->lastCheck;
	}
	else if(!strcmp("zoneID", attribute))
	{
		return this->zoneID;
	}
	/*else if(!strcmp("generated_KMF_ID", attribute))
	{
		return this->generated_KMF_ID;
	}*/
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
			if(strchr(attribute,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);*/
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not found, looking for path\n");*/
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}
		
		/*printf("Token: %s\n", pch);*/

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		/*printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);*/
	  
		if(!strcmp("networkProperties", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindNetworkPropertiesByID(this, queryID);
			}
			else
			{
				NetworkProperty* netprop = this->FindNetworkPropertiesByID(this, queryID);
				if(netprop != NULL)
					return netprop->FindByPath(nextAttribute, netprop);
				else
					return NULL;
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}