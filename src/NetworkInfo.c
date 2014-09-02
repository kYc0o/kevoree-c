#include "NetworkInfo.h"

NamedElement* newPoly_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)my_malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNetInfoObj; /* Pointing to derived object */
	
	pNetInfoObj->values = NULL;
	pNetInfoObj->eContainer = NULL;
	
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
	pNetInfoObj = (NetworkInfo*)my_malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNetInfoObj;  Pointing to derived object */
	pNetInfoObj->super = pObj;
	
	pNetInfoObj->values = NULL;
	pNetInfoObj->eContainer = NULL;
	
	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;
	
	pNetInfoObj->MetaClassName = NetworkInfo_MetaClassName;
	pObj->MetaClassName = NetworkInfo_MetaClassName;
	pNetInfoObj->InternalGetKey = NetworkInfo_InternalGetKey;
	pNetInfoObj->VisitAttributes = NetworkInfo_VisitAttributes;
	pNetInfoObj->VisitReferences = NetworkInfo_VisitReferences;
	
	pNetInfoObj->Delete = delete_NetworkInfo;

	return pNetInfoObj;
}

char* NetworkInfo_InternalGetKey(NetworkInfo* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* NetworkInfo_MetaClassName(NetworkInfo* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("NetworkInfo")) + 1);
	if(name != NULL)
		strcpy(name, "NetworkInfo");
	else
		return NULL;
	
	return name;
}

void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The NetworkProperty cannot be added in NetworkInfo because the key is not defined\n");
	}
	else
	{
		if(this->values == NULL)
		{
			this->values = hashmap_new();
		}
		if(hashmap_get(this->values, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (NetworkProperty*)ptr;*/
			hashmap_put(this->values, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The NetworkProperty cannot be removed in NetworkInfo because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->values, ptr->InternalGetKey(ptr));
	}
}

NetworkProperty* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id)
{
	NetworkProperty* value = NULL;

	if(this->values != NULL)
	{
		if(hashmap_get(this->values, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void deletePoly_NetworkInfo(NamedElement* const this)
{
	if(this != NULL)
	{
		NetworkInfo* pNetInfoObj;
		pNetInfoObj = this->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pNetInfoObj->values);
		free(pNetInfoObj->eContainer);
		free(pNetInfoObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_NetworkInfo(NetworkInfo* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		hashmap_free(this->values);
		free(this->eContainer);
		free(this);
	}
	
}

void NetworkInfo_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	/*char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((NetworkInfo*)this)->MetaClassName((NetworkInfo*)this));*/

	NamedElement_VisitAttributes(((NetworkInfo*)(this))->super, parent, visitor, 1);
}

void NetworkInfo_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	if(((NetworkInfo*)(this))->values != NULL)
	{
		visitor->action("values", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((NetworkInfo*)(this))->values);
		
		/* values */
		hashmap_map* m = ((NetworkInfo*)(this))->values;

		/* compare values */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				/*sprintf(path,"%s/values[%s]", parent, n->InternalGetKey(n));*/
				n->VisitAttributes(n, path, visitor);
				/*n->VisitReferences(n, parent, visitor);*/
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
	else
	{
		visitor->action("values", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
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
