#include "Dictionary.h"

Dictionary* new_Dictionary()
{
	Dictionary* pObj = NULL;
	/* Allocating memory */
	pObj = (Dictionary*)malloc(sizeof(Dictionary));

	if (pObj == NULL)
	{
		return NULL;
	}
	
	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	/*pObj->generated_KMF_ID = malloc(sizeof(char) * 8 + 1);*/
	rand_str(pObj->generated_KMF_ID, 8);
	
	pObj->values = NULL;
	
	pObj->AddValues = Dictionary_AddValues;
	pObj->RemoveValues = Dictionary_RemoveValues;
	pObj->FindValuesByID = Dictionary_FindValuesByID;

	pObj->InternalGetKey = Dictionary_InternalGetKey;
	pObj->MetaClassName = Dictionary_MetaClassName;
	pObj->Delete = delete_Dictionary;
	pObj->VisitAttributes = Dictionary_VisitAttributes;
	pObj->VisitReferences = Dictionary_VisitReferences;
	pObj->FindByPath = Dictionary_FindByPath;
	
	return pObj;
}

void delete_Dictionary(Dictionary* const this)
{
	if(this != NULL)
	{
		free(this->generated_KMF_ID);
		/* TODO check if hashmap is not NULL */
		hashmap_free(this->values);
		free(this);
	}
}

DictionaryValue* Dictionary_FindValuesByID(Dictionary* const this, char* id)
{
	DictionaryValue* value = NULL;

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

void Dictionary_AddValues(Dictionary* const this, DictionaryValue* ptr)
{
	DictionaryValue* container = NULL;

	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The DictionaryValue cannot be added in Dictionary because the key is not defined\n");
	}
	else
	{
		if(this->values == NULL)
		{
			this->values = hashmap_new();
		}
		if(hashmap_get(this->values, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (DictionaryValue*)ptr;*/
			hashmap_put(this->values, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void Dictionary_RemoveValues(Dictionary* const this, DictionaryValue* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The DictionaryValue cannot be removed in Dictionary because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->values, ptr->InternalGetKey(ptr));
	}
}

char* Dictionary_InternalGetKey(Dictionary* const this)
{
	return this->generated_KMF_ID;
}

char* Dictionary_MetaClassName(Dictionary* const this)
{
	char* name;
	memset(&name[0], 0, sizeof(name));

	/*name = malloc(sizeof(char) * (strlen("Dictionary") + 1));*/
	strcpy(name, "Dictionary");
	
	return name;
}

void Dictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path, "%s\\generated_KMF_ID", parent);
	visitor->action(path, STRING, ((Dictionary*)(this))->generated_KMF_ID);
}

void Dictionary_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	hashmap_map* m = NULL;
	
	if((m = (hashmap_map*) ((Dictionary*)(this))->values) != NULL)
	{
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DictionaryValue* n = data;
				sprintf(path, "%s/values[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
			}
		}
	}
}

void* Dictionary_FindByPath(char* attribute, Dictionary* const this)
{
	/* Local attributes */
	if(!strcmp("generated_KMF_ID", attribute))
	{
		return this->generated_KMF_ID;
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
			
			if(strchr(attribute,'\\') != NULL)
			{
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
	  
		if(!strcmp("values", relationName))
		{
			if(nextAttribute == NULL)
			{
				
				return this->FindValuesByID(this, queryID);
			}
			else
			{
				DictionaryValue* value = this->FindValuesByID(this, queryID);
				if(value != NULL)
					return value->FindByPath(nextAttribute, value);
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
