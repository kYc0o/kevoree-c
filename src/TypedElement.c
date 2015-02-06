#include <stdbool.h>
#include "NamedElement.h"
#include "ContainerRoot.h"
#include "Visitor.h"
#include "TypedElement.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NamedElement* newPoly_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeElemObj = (TypedElement*)malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeElemObj; /* Pointing to derived object */

	pTypeElemObj->genericTypes = NULL;
	pTypeElemObj->eContainer = NULL;

	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;

	pObj->MetaClassName = TypedElement_MetaClassName;
	pObj->InternalGetKey = TypedElement_InternalGetKey;
	pObj->Delete = deletePoly_TypedElement;
	pObj->VisitAttributes = TypedElement_VisitAttributes;
	pObj->VisitPathAttributes = TypedElement_VisitPathAttributes;
	pObj->VisitReferences = TypedElement_VisitReferences;
	pObj->VisitPathReferences = TypedElement_VisitPathReferences;
	pObj->FindByPath = TypedElement_FindByPath;

	return pObj;
}

TypedElement* new_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pTypeElemObj = (TypedElement*)malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		return NULL;
	}

	pObj->pDerivedObj = pObj;  /*Pointing to derived object */
	pTypeElemObj->super = pObj;

	pTypeElemObj->genericTypes = NULL;
	pTypeElemObj->eContainer = NULL;

	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;

	pTypeElemObj->MetaClassName = TypedElement_MetaClassName;
	pObj->MetaClassName = TypedElement_MetaClassName;
	pTypeElemObj->InternalGetKey = TypedElement_InternalGetKey;
	pTypeElemObj->Delete = delete_TypedElement;
	pTypeElemObj->VisitAttributes = TypedElement_VisitAttributes;
	pTypeElemObj->VisitPathAttributes = TypedElement_VisitPathAttributes;
	pTypeElemObj->VisitReferences = TypedElement_VisitReferences;
	pTypeElemObj->VisitPathReferences = TypedElement_VisitPathReferences;
	pTypeElemObj->FindByPath = TypedElement_FindByPath;

	return pTypeElemObj;
}

char* TypedElement_MetaClassName(TypedElement* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("TypedElement")) + 1);
	if(name != NULL)
		strcpy(name, "TypedElement");
	else
		return NULL;

	return name;
}

char* TypedElement_InternalGetKey(TypedElement* const this)
{
	return this->super->InternalGetKey(this->super);
}

TypedElement* TypedElement_FindGenericTypesByID(TypedElement* const this, char* id)
{
	TypedElement* value = NULL;

	if(this->genericTypes)
	{
		if(hashmap_get(this->genericTypes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void TypedElement_AddGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	TypedElement* container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypedElement cannot be added in TypedElement because the key is not defined");
	}
	else
	{
		if(this->genericTypes == NULL)
		{
			this->genericTypes = hashmap_new();
		}
		if(hashmap_get(this->genericTypes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypedElement*)ptr;*/
			hashmap_put(this->genericTypes, internalKey, ptr);
		}
	}
}

void TypedElement_RemoveGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypedElement cannot be removed in TypedElement because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->genericTypes, internalKey);
		free(internalKey);
	}
}

void deletePoly_TypedElement(NamedElement* const this)
{
	if(this != NULL)
	{
		TypedElement* pTypeElemObj;
		pTypeElemObj = this->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pTypeElemObj->genericTypes);
		free(pTypeElemObj->eContainer);
		free(pTypeElemObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_TypedElement(TypedElement* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		hashmap_free(this->genericTypes);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void TypedElement_VisitAttributes(void *const this, char *parent, Visitor *visitor)
{
	NamedElement_VisitAttributes(((TypedElement*)(this))->super, parent, visitor, true);
}

void TypedElement_VisitPathAttributes(void *const this, char *parent, Visitor *visitor)
{
	NamedElement_VisitPathAttributes(((TypedElement*)(this))->super, parent, visitor, true);
}

void TypedElement_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypedElement*)(this))->genericTypes != NULL)
	{
		visitor->action("genericTypes", SQBRACKET, NULL);
		int i;

		/* genericTypes */
		hashmap_map* m = ((TypedElement*)(this))->genericTypes;

		/* compare genericTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypedElement* n = data;
				sprintf(path,"genericTypes[%s]", n->InternalGetKey(n));
				visitor->action(path, STRREF, NULL);
				visitor->action(NULL, RETURN, NULL);
			}
		}
	}
}

void TypedElement_VisitPathReferences(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypedElement*)(this))->genericTypes != NULL)
	{
		int i;

		/* genericTypes */
		hashmap_map *m = ((TypedElement*)(this))->genericTypes;

		/* compare genericTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypedElement *n = data;
				sprintf(path,"%s/genericTypes[%s]", parent, n->super->name);
				n->VisitPathAttributes(n, path, visitor);
				n->VisitPathReferences(n, path, visitor);
			}
		}
	}
}

void* TypedElement_FindByPath(char* attribute, TypedElement* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return this->super->FindByPath(attribute, this->super);
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
				nextAttribute = strtok(NULL, "\\");
				strcpy(nextPath, ++nextAttribute);
				PRINTF("Next Path: %s\n", nextPath);
				nextAttribute = NULL;
			}
		}
		else
		{
			nextAttribute = strtok(path, "\\");
			nextAttribute = strtok(NULL, "\\");
			PRINTF("Attribute: %s\n", nextAttribute);
		}

		if(!strcmp("genericTypes", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->FindGenericTypesByID(this, key);
			}
			else
			{
				TypedElement* typelem = this->FindGenericTypesByID(this, key);
				if(typelem != NULL)
					return typelem->FindByPath(nextPath, typelem);
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
