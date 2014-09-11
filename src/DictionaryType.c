#include "DictionaryAttribute.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "DictionaryType.h"

DictionaryType* new_DictionaryType()
{
	DictionaryType* pObj = NULL;
	/* Allocating memory */
	pObj = (DictionaryType*)my_malloc(sizeof(DictionaryType));

	if (pObj == NULL)
	{
		return NULL;
	}

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	/*pObj->generated_KMF_ID = malloc(sizeof(char) * 8 + 1);*/
	rand_str(pObj->generated_KMF_ID, 8);
	
	pObj->attributes = NULL;
	pObj->eContainer = NULL;
	
	pObj->AddAttributes = DictionaryType_AddAttributes;
	pObj->RemoveAttributes = DictionaryType_RemoveAttributes;
	pObj->FindAttributesByID = DictionaryType_FindAttributesByID;

	pObj->InternalGetKey = DictionaryType_InternalGetKey;
	pObj->MetaClassName = DictionaryType_MetaClassName;
	pObj->Delete = delete_DictionaryType;
	pObj->VisitAttributes = DictionaryType_VisitAttributes;
	pObj->VisitReferences = DictionaryType_VisitReferences;
	pObj->FindByPath = DictionaryType_FindByPath;
	
	return pObj;
}

void delete_DictionaryType(DictionaryType* const this)
{
	if(this != NULL)
	{
		free(this->generated_KMF_ID);
		/* TODO check if hashmap is not NULL */
		hashmap_free(this->attributes);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* DictionaryType_InternalGetKey(DictionaryType* const this)
{
	return this->generated_KMF_ID;
}

char* DictionaryType_MetaClassName(DictionaryType* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("DictionaryType")) + 1);
	if(name != NULL)
		strcpy(name, "DictionaryType");
	else
		return NULL;
	
	return name;
}

DictionaryAttribute* DictionaryType_FindAttributesByID(DictionaryType* const this, char* id)
{
	DictionaryAttribute* value = NULL;

	if(this->attributes != NULL)
	{
		if(hashmap_get(this->attributes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void DictionaryType_AddAttributes(DictionaryType* const this, DictionaryAttribute* ptr)
{
	DictionaryAttribute* container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The DictionaryAttribute cannot be added in DictionaryType because the key is not defined\n");
	}
	else
	{
		if(this->attributes == NULL)
		{
			this->attributes = hashmap_new();
		}
		if(hashmap_get(this->attributes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (DictionaryAttribute*)ptr;*/
			if(hashmap_put(this->attributes, internalKey, ptr) == MAP_OK)
				ptr->eContainer = this;
		}
	}
}

void DictionaryType_RemoveAttributes(DictionaryType* const this, DictionaryAttribute* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The DictionaryValue cannot be removed in Dictionary because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->attributes, internalKey) == MAP_OK)
		{
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void DictionaryType_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = my_malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((DictionaryType*)this)->MetaClassName((DictionaryType*)this))) + 1);
	/*sprintf(path,"%s\\cClass", parent);*/
	sprintf(cClass, "org.kevoree.%s", ((DictionaryType*)this)->MetaClassName((DictionaryType*)this));
	sprintf(path,"eClass", parent);
	/*cClass = ((DictionaryType*)this)->MetaClassName((DictionaryType*)this);*/
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	/*free(cClass);*/
	str_free(cClass);

	/*sprintf(path, "%s\\generated_KMF_ID", parent);*/
	sprintf(path, "generated_KMF_ID");
	visitor->action(path, STRING, ((DictionaryType*)(this))->generated_KMF_ID);
	visitor->action(NULL, COLON, NULL);
}

void DictionaryType_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	hashmap_map* m = NULL;
	
	if((m = (hashmap_map*) ((DictionaryType*)(this))->attributes) != NULL)
	{
		int length = hashmap_length(((DictionaryType*)(this))->attributes);

		visitor->action("attributes", SQBRACKET, NULL);
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				DictionaryAttribute* n = data;
				/*sprintf(path, "%s/attributes[%s]", parent, n->InternalGetKey(n));*/
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
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
		visitor->action("attributes", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
}

void* DictionaryType_FindByPath(char* attribute, DictionaryType* const this)
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
	  
		if(!strcmp("attributes", relationName))
		{
			if(nextAttribute == NULL)
			{
				
				return this->FindAttributesByID(this, queryID);
			}
			else
			{
				DictionaryAttribute* value = this->FindAttributesByID(this, queryID);
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
