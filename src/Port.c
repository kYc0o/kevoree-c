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

	pObj->InternalGetKey = Port_InternalGetKey;
	pObj->MetaClassName = Port_MetaClassName;
	pObj->super->MetaClassName = Port_MetaClassName;
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

char* Port_InternalGetKey(Port* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* Port_MetaClassName(Port* const this)
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

	char *internalKey = ptr->InternalGetKey(ptr);

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
			/*container = (MBinding*)ptr;*/
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
	char *internalKey = ptr->InternalGetKey(ptr);

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

void Port_VisitAttributes(Port *const this, char *parent, Visitor *visitor, bool recursive)
{
	NamedElement_VisitAttributes(this->super, parent, visitor, recursive);
}

void Port_VisitPathAttributes(Port *const this, char *parent, Visitor *visitor, bool recursive)
{
	NamedElement_VisitPathAttributes(this->super, parent, visitor, recursive);
}

void Port_VisitReferences(Port *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	hashmap_map* m = NULL;

	if((m = (hashmap_map*)this->bindings) != NULL)
	{
		int i;
		int length = hashmap_length(this->bindings);

		visitor->action("bindings", SQBRACKET, NULL);
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "mBindings[%s]", n->InternalGetKey(n));
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

	if(this->portTypeRef != NULL)
	{
		visitor->action("portTypeRef", SQBRACKET, NULL);
		sprintf(path, "%s/%s[%s]", this->portTypeRef->eContainer,
				parent,
				this->portTypeRef->InternalGetKey(this->portTypeRef));
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

void Port_VisitPathReferences(Port *const this, char *parent, Visitor *visitor)
{
	int i;
	char path[256];
	memset(&path[0], 0, sizeof(path));

	hashmap_map* m = NULL;

	if((m = (hashmap_map*)this->bindings) != NULL)
	{
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "%s/bindings[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, false);
			}
		}
	}

	if(this->portTypeRef != NULL)
	{
		sprintf(path, "%s/portTypeRef[%s]", parent, this->portTypeRef->InternalGetKey(this->portTypeRef));
		this->portTypeRef->VisitPathAttributes(this->portTypeRef, path, visitor, false);
	}
}

void* Port_FindByPath(char* attribute, Port* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
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

		if(!strcmp("bindings", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{

				return this->FindBindingsByID(this, key);
			}
			else
			{
				MBinding* binding = this->FindBindingsByID(this, key);
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
