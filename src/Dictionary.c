#include "Visitor.h"
#include "DictionaryValue.h"
#include "Instance.h"
#include "Dictionary.h"
#include "tools.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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
	rand_str(pObj->generated_KMF_ID, 8);

	pObj->values = NULL;
	pObj->eContainer = NULL;
	pObj->path = NULL;

	pObj->AddValues = Dictionary_AddValues;
	pObj->RemoveValues = Dictionary_RemoveValues;
	pObj->FindValuesByID = Dictionary_FindValuesByID;

	pObj->internalGetKey = Dictionary_internalGetKey;
	pObj->metaClassName = Dictionary_metaClassName;
	pObj->Delete = delete_Dictionary;
	pObj->VisitAttributes = Dictionary_VisitAttributes;
	pObj->VisitPathAttributes = Dictionary_VisitPathAttributes;
	pObj->VisitReferences = Dictionary_VisitReferences;
	pObj->VisitPathReferences = Dictionary_VisitPathReferences;
	pObj->FindByPath = Dictionary_FindByPath;

	return pObj;
}

void delete_Dictionary(void* const this)
{
	if(this != NULL)
	{
		Dictionary *pObj = (Dictionary*)this;
		free(pObj->generated_KMF_ID);
		/*
		 * TODO check if hashmap is not NULL
		 */
		hashmap_free(pObj->values);
		free(pObj->eContainer);
		free(pObj);
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

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DictionaryValue cannot be added in Dictionary because the key is not defined\n");
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
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/values[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/values[%s]", this->path, internalKey);
			}
		}
	}
}

void Dictionary_RemoveValues(Dictionary* const this, DictionaryValue* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DictionaryValue cannot be removed in Dictionary because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->values, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

char* Dictionary_internalGetKey(void* const this)
{
	Dictionary *pObj = (Dictionary*)this;
	return pObj->generated_KMF_ID;
}

char* Dictionary_metaClassName(void* const this)
{
	Dictionary *pObj = (Dictionary*)this;
	char *name;

	name = malloc(sizeof(char) * (strlen("Dictionary")) + 1);
	if(name != NULL)
		strcpy(name, "Dictionary");
	else
		return NULL;

	return name;
}

void Dictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((Dictionary*)this)->metaClassName((Dictionary*)this))) + 1);
	sprintf(cClass, "org.kevoree.%s", ((Dictionary*)this)->metaClassName((Dictionary*)this));
	sprintf(path, "eClass");
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	free(cClass);

	sprintf(path, "generated_KMF_ID");
	visitor->action(path, STRING, ((Dictionary*)(this))->generated_KMF_ID);
	visitor->action(NULL, COLON, NULL);
}

void Dictionary_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((Dictionary*)this)->metaClassName((Dictionary*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path, "%s\\generated_KMF_ID", parent);
	visitor->action(path, STRING, ((Dictionary*)(this))->generated_KMF_ID);
}

void Dictionary_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
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
				n->VisitAttributes(n, path, visitor, false);
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

void Dictionary_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
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
				sprintf(path, "%s/values[%s]", parent, n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "values")) {
						n->VisitPathAttributes(n, path, visitor, false);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, false);
				}
			}
		}
	}
}

void* Dictionary_FindByPath(char* attribute, void* const this)
{
	Dictionary *pObj = (Dictionary*)this;
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

		if(!strcmp("values", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{

				return pObj->FindValuesByID(pObj, key);
			}
			else
			{
				DictionaryValue* value = pObj->FindValuesByID(pObj, key);
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
