#include "Visitor.h"
#include "DictionaryValue.h"
#include "Instance.h"
#include "Dictionary.h"

Dictionary* new_Dictionary()
{
	Dictionary* pObj = NULL;
	/* Allocating memory */
	pObj = (Dictionary*)my_malloc(sizeof(Dictionary));

	if (pObj == NULL)
	{
		return NULL;
	}
	
	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);
	
	pObj->values = NULL;
	pObj->eContainer = NULL;
	
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
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
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

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The DictionaryValue cannot be added in Dictionary because the key is not defined\n");
	}
	else
	{
		if(this->values == NULL)
		{
			this->values = hashmap_new();
		}
		if(hashmap_get(this->values, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (DictionaryValue*)ptr;*/
			if(hashmap_put(this->values, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = my_malloc(sizeof(char) * (strlen("dictionary[]") + strlen(this->InternalGetKey(this))) + 1);
				sprintf(ptr->eContainer, "dictionary[%s]", this->InternalGetKey(this));
			}
		}
	}
}

void Dictionary_RemoveValues(Dictionary* const this, DictionaryValue* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The DictionaryValue cannot be removed in Dictionary because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->values, internalKey) == MAP_OK)
		{
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

char* Dictionary_InternalGetKey(Dictionary* const this)
{
	return this->generated_KMF_ID;
}

char* Dictionary_MetaClassName(Dictionary* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("Dictionary")) + 1);
	if(name != NULL)
		strcpy(name, "Dictionary");
	else
		return NULL;
	
	return name;
}

void Dictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = my_malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((Dictionary*)this)->MetaClassName((Dictionary*)this))) + 1);
	/*sprintf(path,"%s\\cClass", parent);*/
	sprintf(cClass, "org.kevoree.%s", ((Dictionary*)this)->MetaClassName((Dictionary*)this));
	sprintf(path, "eClass");
	/*cClass = ((Dictionary*)this)->MetaClassName((Dictionary*)this);*/
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	/*free(cClass);*/
	str_free(cClass);

	/*sprintf(path, "%s\\generated_KMF_ID", parent);*/
	sprintf(path, "generated_KMF_ID");
	visitor->action(path, STRING, ((Dictionary*)(this))->generated_KMF_ID);
	visitor->action(NULL, COLON, NULL);
}

void Dictionary_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	hashmap_map* m = NULL;
	
	if((m = (hashmap_map*) ((Dictionary*)(this))->values) != NULL)
	{
		int length = hashmap_length(((Dictionary*)(this))->values);

		visitor->action("values", SQBRACKET, NULL);
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				DictionaryValue* n = data;
				/*sprintf(path, "%s/values[%s]", parent, n->InternalGetKey(n));*/
				n->VisitAttributes(n, path, visitor);
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
