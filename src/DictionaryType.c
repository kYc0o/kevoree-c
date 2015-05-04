#include "DictionaryAttribute.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "DictionaryType.h"
#include "tools.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

DictionaryType* new_DictionaryType()
{
	DictionaryType* pObj = NULL;
	/* Allocating memory */
	pObj = (DictionaryType*)malloc(sizeof(DictionaryType));

	if (pObj == NULL)
	{
		return NULL;
	}

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);

	pObj->attributes = NULL;
	pObj->eContainer = NULL;
	pObj->path = NULL;

	pObj->AddAttributes = DictionaryType_AddAttributes;
	pObj->RemoveAttributes = DictionaryType_RemoveAttributes;
	pObj->FindAttributesByID = DictionaryType_FindAttributesByID;

	pObj->internalGetKey = DictionaryType_internalGetKey;
	pObj->metaClassName = DictionaryType_metaClassName;
	pObj->Delete = delete_DictionaryType;
	pObj->VisitAttributes = DictionaryType_VisitAttributes;
	pObj->VisitPathAttributes = DictionaryType_VisitPathAttributes;
	pObj->VisitReferences = DictionaryType_VisitReferences;
	pObj->VisitPathReferences = DictionaryType_VisitPathReferences;
	pObj->FindByPath = DictionaryType_FindByPath;

	return pObj;
}

void delete_DictionaryType(void* const this)
{
	if(this != NULL)
	{
		DictionaryType *pObj = (DictionaryType*)this;
		free(pObj->generated_KMF_ID);
		/* TODO check if hashmap is not NULL */
		hashmap_free(pObj->attributes);
		free(pObj->eContainer);
		free(pObj);
		/*this = NULL;*/
	}
}

char* DictionaryType_internalGetKey(void* const this)
{
	DictionaryType *pObj = (DictionaryType*)this;
	return pObj->generated_KMF_ID;
}

char* DictionaryType_metaClassName(void* const this)
{
	/*
	char *name;

	name = malloc(sizeof(char) * (strlen("DictionaryType")) + 1);
	if(name != NULL)
		strcpy(name, "DictionaryType");
	else
		return NULL;

	return name;
	*/
	return "DictionaryType";
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

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DictionaryAttribute cannot be added in DictionaryType because the key is not defined\n");
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
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/attributes[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/attributes[%s]", this->path, internalKey);
			}
		}
	}
}

void DictionaryType_RemoveAttributes(DictionaryType* const this, DictionaryAttribute* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DictionaryValue cannot be removed in Dictionary because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->attributes, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void DictionaryType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((DictionaryType*)this)->metaClassName((DictionaryType*)this))) + 1);
	sprintf(cClass, "org.kevoree.%s", ((DictionaryType*)this)->metaClassName((DictionaryType*)this));
	sprintf(path, "eClass");
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	free(cClass);

	sprintf(path, "generated_KMF_ID");
	visitor->action(path, STRING, ((DictionaryType*)(this))->generated_KMF_ID);
	visitor->action(NULL, COLON, NULL);
}

void DictionaryType_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((DictionaryType*)this)->metaClassName((DictionaryType*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path, "%s\\generated_KMF_ID", parent);
	visitor->action(path, STRING, ((DictionaryType*)(this))->generated_KMF_ID);
}

void DictionaryType_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
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
				n->VisitAttributes(n, path, visitor,true);
				n->VisitReferences(n, path, visitor, true);
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

void DictionaryType_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));

	hashmap_map* m = NULL;

	if((m = (hashmap_map*) ((DictionaryType*)(this))->attributes) != NULL)
	{
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DictionaryAttribute* n = data;
				sprintf(path, "%s/attributes[%s]", parent, n->internalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, true);
				n->VisitPathReferences(n, path, visitor, true);
			}
		}
	}
}

void* DictionaryType_FindByPath(char* attribute, void* const this)
{
	DictionaryType *pObj = (DictionaryType*)this;
	/* Local attributes */
	if(!strcmp("generated_KMF_ID", attribute))
	{
		return pObj->generated_KMF_ID;
	}
	/* Local references */
	else
	{
		char path[250];
		memset(&path[0], 0, sizeof(path));
		char token[100];
		memset(&token[0], 0, sizeof(token));
		char *obj = NULL;
		char key[50];
		memset(&key[0], 0, sizeof(key));
		char nextPath[150];
		memset(&nextPath[0], 0, sizeof(nextPath));
		char *nextAttribute = NULL;

		strcpy(path, attribute);

		if(strchr(path, '[') != NULL)
		{
			obj = strdup(strtok(path, "["));
			strcpy(path, attribute);
			PRINTF("Object: %s\n", obj);
			strcpy(token, strtok(path, "]"));
			strcpy(path, attribute);
			sprintf(token, "%s]", token);
			PRINTF("Token: %s\n", token);
			sscanf(token, "%*[^[][%[^]]", key);
			PRINTF("Key: %s\n", key);

			if((strchr(path, '\\')) != NULL)
			{
				nextAttribute = strtok(NULL, "\\");
				PRINTF("Attribute: %s\n", nextAttribute);

				if(strchr(nextAttribute, '['))
				{
					sprintf(nextPath, "%s\\%s", ++nextAttribute, strtok(NULL, "\\"));
					PRINTF("Next Path: %s\n", nextPath);
				}
				else
				{
					strcpy(nextPath, nextAttribute);
					PRINTF("Next Path: %s\n", nextPath);
				}
			}
			else
			{
				nextAttribute = strtok(path, "]");
				bool isFirst = true;
				char *fragPath = NULL;
				while ((fragPath = strtok(NULL, "]")) != NULL) {
					PRINTF("Attribute: %s]\n", fragPath);
					if (isFirst) {
						sprintf(nextPath, "%s]", ++fragPath);
						isFirst = false;
					} else {
						sprintf(nextPath, "%s/%s]", nextPath, ++fragPath);
					}
					PRINTF("Next Path: %s\n", nextPath);
				}
				if (strlen(nextPath) == 0) {
					PRINTF("Attribute: NULL\n");
					PRINTF("Next Path: NULL\n");
					nextAttribute = NULL;
				}
			}
		}
		else
		{
			if ((nextAttribute = strtok(path, "\\")) != NULL) {
				if ((nextAttribute = strtok(NULL, "\\")) != NULL) {
					PRINTF("Attribute: %s\n", nextAttribute);
				} else {
					nextAttribute = strtok(path, "\\");
					PRINTF("Attribute: %s\n", nextAttribute);
				}
			}
		}

		if(!strcmp("attributes", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				DictionaryAttribute *dicattr =  pObj->FindAttributesByID(pObj, key);
				PRINTF("DEBUG: returning %s object\n", dicattr->metaClassName(dicattr));
				return dicattr;
			}
			else
			{
				DictionaryAttribute* value = pObj->FindAttributesByID(pObj, key);
				if(value != NULL)
					return value->FindByPath(nextPath, value);
				else
					return NULL;
			}
		}
		else
		{
			free(obj);
			PRINTF("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
