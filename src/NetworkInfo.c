#include "NetworkInfo.h"

NamedElement* newPoly_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNetInfoObj; /* Pointing to derived object */
	
	/*pNetInfoObj->values = hashmap_new();*/
	pNetInfoObj->values = NULL;
	
	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;
	
	pObj->MetaClassName = NetworkInfo_MetaClassName;
	pObj->InternalGetKey = NetworkInfo_InternalGetKey;
	pObj->VisitAttributes = NetworkInfo_VisitAttributes;
	pObj->VisitReferences = NetworkInfo_VisitReferences;
	
	pObj->Delete = deletePoly_NetworkInfo;

	return pObj;
}

NetworkInfo* new_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNetInfoObj;  Pointing to derived object */
	pNetInfoObj->super = pObj;
	
	/*pNetInfoObj->values = hashmap_new();*/
	pNetInfoObj->values = NULL;
	
	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;
	
	pNetInfoObj->MetaClassName = NetworkInfo_MetaClassName;
	pNetInfoObj->InternalGetKey = NetworkInfo_InternalGetKey;
	pNetInfoObj->VisitAttributes = NetworkInfo_VisitAttributes;
	pNetInfoObj->VisitReferences = NetworkInfo_VisitReferences;
	
	pNetInfoObj->Delete = delete_NetworkInfo;

	return pNetInfoObj;
}

char* NetworkInfo_InternalGetKey(NetworkInfo* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->name);

	return internalKey;
}

char* NetworkInfo_MetaClassName(NetworkInfo* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NetworkInfo") + 1));
	strcpy(name, "NetworkInfo");
	
	return name;
}

void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = (NetworkProperty*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be added in NetworkInfo because the key is not defined");*/
		printf("The NetworkProperty cannot be added in NetworkInfo because the key is not defined\n");
	}else
	{
		/*if(values.find(container->internalGetKey()) == values.end())*/
		if(this->values == NULL)
		{
			this->values = hashmap_new();
		}
		if(hashmap_get(this->values, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*values[container->internalGetKey()]=ptr;*/
			container = (NetworkProperty*)ptr;
			hashmap_put(this->values, container->InternalGetKey(container), ptr);
			/*any ptr_any = container;
			RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"values",ptr_any);
			container->setEContainer(this,cmd,"values");*/
		}
	}
}

void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = (NetworkProperty*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be removed in NetworkInfo because the key is not defined");*/
		printf("The NetworkProperty cannot be removed in NetworkInfo because the key is not defined\n");
	}
	else
	{
		/*values.erase( values.find(container->internalGetKey()));*/
		hashmap_remove(this->values, container->InternalGetKey(container));
		/*delete container;
		container->setEContainer(NULL,NULL,"");*/
	}
}

NetworkInfo* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id)
{
	NetworkInfo* value;

	if(hashmap_get(this->values, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void deletePoly_NetworkInfo(NamedElement* const this)
{
	NetworkInfo* pNetInfoObj;
	pNetInfoObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pNetInfoObj->values);
	free(pNetInfoObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_NetworkInfo(NetworkInfo* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->values);
	free(this);
	
}

void NetworkInfo_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	/*char path[128];
	memset(&path[0], 0, sizeof(path));*/

	/*sprintf(path, "%s", parent, ((NetworkInfo*)(this))->super->name);*/

	/*sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((NetworkInfo*)(this))->super->name);*/
	NamedElement_VisitAttributes(((NetworkInfo*)(this))->super, parent, visitor);
}

void NetworkInfo_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	if(((NetworkInfo*)(this))->values != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/values[%s]", parent, ((NetworkInfo*)(this))->super->name);*/
		
		/* values */
		hashmap_map* m = ((NetworkInfo*)(this))->values;

		/* compare values */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				sprintf(path,"%s/values[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				/*n->VisitReferences(n, parent, visitor);*/
			}
		}
	}
}

void* NetworkInfo_FindByPath(char* attribute, NetworkInfo* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return this->super->FindByPath(attribute, this->super);
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
		
		if(!strcmp("values", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindValuesByID(this, queryID);
			}
			else
			{
				NetworkProperty* netprop = this->FindValuesByID(this, queryID);
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

/*int _acceptNetworkInfo(NetworkInfo* this, NetworkInfo* c, Visitor* visitor)
{
	int i;

	for(i = 0; i < this->count_values; i++)
	{
		visitor->action((void*)this->values, (void*)c->values, 0);
	}
}*/