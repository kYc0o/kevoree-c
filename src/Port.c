#include <string.h>
#include <stdlib.h>
#include "Visitor.h"
#include "MBinding.h"
#include "PortTypeRef.h"
#include "ComponentInstance.h"
#include "TypeDefinition.h"
#include "NamedElement.h"
#include "Port.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

Port* new_Port()
{
	Port* pObj = NULL;
	/* Allocating memory */
	pObj = (Port*)malloc(sizeof(Port));

	if (pObj == NULL)
	{
		return NULL;
	}

	pObj->super = new_NamedElement();

	if(pObj->super == NULL)
	{
		return NULL;
	}

	pObj->bindings = NULL;
	pObj->portTypeRef = NULL;
	pObj->eContainer = NULL;

	pObj->AddBindings = Port_AddBindings;
	pObj->AddPortTypeRef = Port_AddPortTypeRef;
	pObj->RemoveBindings = Port_RemoveBindings;
	pObj->RemovePortTypeRef = Port_RemovePortTypeRef;

	pObj->internalGetKey = Port_internalGetKey;
	pObj->metaClassName = Port_metaClassName;
	pObj->super->metaClassName = Port_metaClassName;
	pObj->Delete = delete_Port;
	pObj->VisitAttributes = Port_VisitAttributes;
	pObj->VisitPathAttributes = Port_VisitPathAttributes;
	pObj->VisitReferences = Port_VisitReferences;
	pObj->VisitPathReferences = Port_VisitPathReferences;
	pObj->FindByPath = Port_FindByPath;

	return pObj;
}

void delete_Port(void* this)
{
	if((Port*)this != NULL)
	{
		delete_NamedElement(((Port*)this)->super);
		hashmap_free(((Port*)this)->bindings);
		free(((Port*)this)->portTypeRef);
		free(((Port*)this)->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* Port_internalGetKey(void * const this)
{
	Port *pObj = (Port*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* Port_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("Port")) + 1);
	if(name != NULL)
		strcpy(name, "Port");
	else
		return NULL;

	return name;
}

MBinding* Port_FindBindingsByID(Port* const this, char* id)
{
	MBinding* value = NULL;

	if(this->bindings != NULL)
	{
		if(hashmap_get(this->bindings, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void Port_AddBindings(Port* const this, MBinding* ptr)
{
	MBinding* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The MBinding cannot be added in Port because the key is not defined\n");
	}
	else
	{
		if(this->bindings == NULL)
		{
			this->bindings = hashmap_new();
		}

		if(hashmap_get(this->bindings, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			hashmap_put(this->bindings, internalKey, ptr);
		}
	}
}

void Port_AddPortTypeRef(Port* const this, PortTypeRef* ptr)
{
	this->portTypeRef = ptr;
}

void Port_RemoveBindings(Port* const this, MBinding* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The MBinding cannot be removed in Port because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->bindings, internalKey);
		free(internalKey);
	}
}

void Port_RemovePortTypeRef(Port* const this, PortTypeRef* ptr)
{
	free(ptr);
	this->portTypeRef = NULL;
}

void Port_VisitAttributes(void * const this, char *parent, Visitor *visitor, bool recursive)
{
	Port *pObj = (Port*)this;
	NamedElement_VisitAttributes(pObj->super, parent, visitor, recursive);
}

void Port_VisitPathAttributes(void * const this, char *parent, Visitor *visitor, bool recursive)
{
	Port *pObj = (Port*)this;
	NamedElement_VisitPathAttributes(pObj->super, parent, visitor, recursive);
}

void Port_VisitReferences(void * const this, char *parent, Visitor *visitor, bool recursive)
{
	Port *pObj = (Port*)this;
	char path[256];
	memset(&path[0], 0, sizeof(path));

	hashmap_map* m = NULL;

	if((m = (hashmap_map*)pObj->bindings) != NULL)
	{
		int i;
		int length = hashmap_length(pObj->bindings);

		visitor->action("bindings", SQBRACKET, NULL);
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "mBindings[%s]", n->internalGetKey(n));
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
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("bindings", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(pObj->portTypeRef != NULL)
	{
		visitor->action("portTypeRef", SQBRACKET, NULL);
		sprintf(path, "%s/%s[%s]", pObj->portTypeRef->eContainer,
				parent,
				pObj->portTypeRef->internalGetKey(pObj->portTypeRef));
		visitor->action(path, STRREF, NULL);
		visitor->action(NULL, RETURN, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
	else
	{
		visitor->action("portTypeRef", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
}

void Port_VisitPathReferences(void * const this, char *parent, Visitor *visitor, bool recursive)
{
	Port *pObj = (Port*)this;
	int i;
	char path[256];
	memset(&path[0], 0, sizeof(path));

	hashmap_map* m = NULL;

	if((m = (hashmap_map*)pObj->bindings) != NULL)
	{
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "%s/%s\\bindings", parent, n->path);
				visitor->action(path, REFERENCE, parent);
			}
		}
	}

	if(pObj->portTypeRef != NULL)
	{
		sprintf(path, "%s/%s\\portTypeRef", parent, pObj->portTypeRef->path);
		visitor->action(path, REFERENCE, parent);
	}
}

void* Port_FindByPath(char* attribute, void * const this)
{
	Port * pObj = (Port*)this;
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
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

		if(!strcmp("bindings", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{

				return pObj->FindBindingsByID(pObj, key);
			}
			else
			{
				MBinding* binding = pObj->FindBindingsByID(pObj, key);
				if(binding != NULL)
					return binding->FindByPath(nextPath, binding);
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
