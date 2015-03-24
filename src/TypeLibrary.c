#include <string.h>
#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "TypeLibrary.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NamedElement* newPoly_TypeLibrary(void)
{
	TypeLibrary* pTypeLibObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeLibObj = (TypeLibrary*)malloc(sizeof(TypeLibrary));

	if (pTypeLibObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeLibObj; /* Pointing to derived object */

	pTypeLibObj->subTypes = NULL;
	pTypeLibObj->eContainer = NULL;

	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;

	pObj->metaClassName = TypeLibrary_metaClassName;
	pObj->internalGetKey = TypeLibrary_internalGetKey;
	pObj->Delete = deletePoly_TypeLibrary;
	pObj->VisitAttributes = TypeLibrary_VisitAttributes;
	pObj->VisitPathAttributes = TypeLibrary_VisitPathAttributes;
	pObj->VisitReferences = TypeLibrary_VisitReferences;
	pObj->VisitPathReferences = TypeLibrary_VisitPathReferences;
	pObj->FindByPath = TypeLibrary_FindByPath;

	return pObj;
}

TypeLibrary* new_TypeLibrary()
{
	TypeLibrary* pTypeLibObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pTypeLibObj = (TypeLibrary*)malloc(sizeof(TypeLibrary));

	if (pTypeLibObj == NULL)
	{
		return NULL;
	}

	pTypeLibObj->super = pObj;

	pTypeLibObj->subTypes = NULL;
	pTypeLibObj->eContainer = NULL;

	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;

	pTypeLibObj->metaClassName = TypeLibrary_metaClassName;
	pObj->metaClassName = TypeLibrary_metaClassName;
	pTypeLibObj->internalGetKey = TypeLibrary_internalGetKey;
	pTypeLibObj->Delete = delete_TypeLibrary;
	pTypeLibObj->VisitAttributes = TypeLibrary_VisitAttributes;
	pTypeLibObj->VisitPathAttributes = TypeLibrary_VisitPathAttributes;
	pTypeLibObj->VisitReferences = TypeLibrary_VisitReferences;
	pTypeLibObj->VisitPathReferences = TypeLibrary_VisitPathReferences;
	pTypeLibObj->FindByPath = TypeLibrary_FindByPath;

	return pTypeLibObj;
}

char* TypeLibrary_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("TypeLibrary")) + 1);
	if(name != NULL)
		strcpy(name, "TypeLibrary");
	else
		return NULL;

	return name;
}

char* TypeLibrary_internalGetKey(void * const this)
{
	TypeLibrary *pObj = (TypeLibrary*)this;
	return pObj->super->internalGetKey(pObj->super);
}

TypeDefinition* TypeLibrary_FindSubTypesByID(TypeLibrary* const this, char* id)
{
	TypeDefinition* value = NULL;

	if(this->subTypes != NULL)
	{
		if(hashmap_get(this->subTypes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void TypeLibrary_AddSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be added in TypeLibrary because the key is not defined\n");
	}
	else
	{
		if(this->subTypes == NULL)
		{
			this->subTypes = hashmap_new();
		}
		if(hashmap_get(this->subTypes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypeDefinition*)ptr;*/
			hashmap_put(this->subTypes, internalKey, ptr);
		}
	}
}

void TypeLibrary_RemoveSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be removed in TypeLibrary because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->subTypes, internalKey);
		free(internalKey);
	}
}

void deletePoly_TypeLibrary(void * const this)
{
	if(this != NULL)
	{
		NamedElement *pObj = (NamedElement*)this;
		TypeLibrary* pTypeLibObj;
		pTypeLibObj = pObj->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pTypeLibObj->subTypes);
		free(pTypeLibObj->eContainer);
		free(pTypeLibObj);
		/*destroy base Obj*/
		delete_NamedElement(pObj);
	}
}

void delete_TypeLibrary(void * const this)
{
	if(this != NULL)
	{
		TypeLibrary *pObj = (TypeLibrary*)this;
		/* destroy base object */
		delete_NamedElement(pObj->super);
		/* destroy data memebers */
		hashmap_free(pObj->subTypes);
		free(pObj->eContainer);
		free(pObj);
	}
}

void TypeLibrary_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	NamedElement_VisitAttributes(((TypeLibrary*)(this))->super, parent, visitor, true);
}

void TypeLibrary_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	NamedElement_VisitPathAttributes(((TypeLibrary*)(this))->super, parent, visitor, true);
}

void TypeLibrary_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeLibrary*)(this))->subTypes != NULL)
	{
		visitor->action("subTypes", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((TypeLibrary*)(this))->subTypes);

		/* subTypes */
		hashmap_map* m = ((TypeLibrary*)(this))->subTypes;

		/* compare subTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path, "typeDefinitions[%s]", n->internalGetKey(n));
				visitor->action(path, STRREF, NULL);
				if(length > 1)
				{
					visitor->action(NULL, COLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, RETURN, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
	else
	{
		visitor->action("subTypes", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
}

void TypeLibrary_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeLibrary*)(this))->subTypes != NULL)
	{
		int i;

		/* subTypes */
		hashmap_map* m = ((TypeLibrary*)(this))->subTypes;

		/* compare subTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path,"%s/subTypes[%s]", parent, n->internalGetKey(n));
				visitor->action(path, REFERENCE, parent);
			}
		}
	}
}

void* TypeLibrary_FindByPath(char* attribute, void * const this)
{
	TypeLibrary *pObj = (TypeLibrary*)this;
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return pObj->super->FindByPath(attribute, pObj->super);
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

		if(!strcmp("subTypes", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindSubTypesByID(pObj, key);
			}
			else
			{
				TypeDefinition* typdef = pObj->FindSubTypesByID(pObj, key);
				if(typdef != NULL)
					return typdef->FindByPath(nextPath, typdef);
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
