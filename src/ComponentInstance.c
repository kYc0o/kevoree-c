#include <string.h>
#include "NamedElement.h"
#include "Instance.h"
#include "Port.h"
#include "TypeDefinition.h"
#include "ContainerNode.h"
#include "Visitor.h"
#include "ComponentInstance.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

Instance* newPoly_ComponentInstance()
{
	ComponentInstance* pCompInstanceObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pCompInstanceObj = (ComponentInstance*)malloc(sizeof(ComponentInstance));

	if (pCompInstanceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pCompInstanceObj; /* Pointing to derived object */
	pObj->VisitAttributes = ComponentInstance_VisitAttributes;
	pObj->VisitPathAttributes = ComponentInstance_VisitPathAttributes;
	pObj->VisitReferences = ComponentInstance_VisitReferences;
	pObj->VisitPathReferences = ComponentInstance_VisitPathReferences;

	pCompInstanceObj->provided = NULL;
	pCompInstanceObj->required = NULL;

	pCompInstanceObj->AddProvided = ComponentInstance_AddProvided;
	pCompInstanceObj->AddRequired = ComponentInstance_AddRequired;
	pCompInstanceObj->RemoveProvided = ComponentInstance_RemoveProvided;
	pCompInstanceObj->RemoveRequired = ComponentInstance_RemoveRequired;

	pObj->MetaClassName = ComponentInstance_MetaClassName;
	pObj->InternalGetKey = ComponentInstance_InternalGetKey;
	pObj->FindByPath = ComponentInstance_FindByPath;

	pObj->Delete = deletePoly_ComponentInstance;

	return pObj;
}

ComponentInstance* new_ComponentInstance()
{
	ComponentInstance* pCompInstanceObj = NULL;
	Instance* pObj = new_Instance();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompInstanceObj = (ComponentInstance*)malloc(sizeof(ComponentInstance));

	if (pCompInstanceObj == NULL)
	{
		return NULL;
	}

	/*((Instance*)(pObj->pDerivedObj))->pDerivedObj = pCompInstanceObj; Pointing to derived object */
	pCompInstanceObj->super = pObj;

	pCompInstanceObj->provided = NULL;
	pCompInstanceObj->required = NULL;

	pCompInstanceObj->AddProvided = ComponentInstance_AddProvided;
	pCompInstanceObj->AddRequired = ComponentInstance_AddRequired;
	pCompInstanceObj->RemoveProvided = ComponentInstance_RemoveProvided;
	pCompInstanceObj->RemoveRequired = ComponentInstance_RemoveRequired;

	pCompInstanceObj->VisitAttributes = ComponentInstance_VisitAttributes;
	pCompInstanceObj->VisitPathAttributes = ComponentInstance_VisitPathAttributes;
	pCompInstanceObj->VisitReferences = ComponentInstance_VisitReferences;
	pCompInstanceObj->VisitPathReferences = ComponentInstance_VisitPathReferences;
	pCompInstanceObj->MetaClassName = ComponentInstance_MetaClassName;
	pCompInstanceObj->InternalGetKey = ComponentInstance_InternalGetKey;
	pCompInstanceObj->FindByPath = ComponentInstance_FindByPath;

	pObj->super->MetaClassName = ComponentInstance_MetaClassName;
	pCompInstanceObj->Delete = delete_ComponentInstance;

	return pCompInstanceObj;
}

char* ComponentInstance_InternalGetKey(ComponentInstance* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* ComponentInstance_MetaClassName(ComponentInstance* const this)
{
	char *name = NULL;

	name = malloc(sizeof(char) * (strlen("ComponentInstance")) + 1);
	if(name != NULL)
		strcpy(name, "ComponentInstance");
	else
		return NULL;

	return name;
}

void deletePoly_ComponentInstance(Instance* const this)
{
	ComponentInstance* pCompInstanceObj;
	pCompInstanceObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pCompInstanceObj);
	/*destroy base Obj*/
	delete_Instance(this);
}

void delete_ComponentInstance(ComponentInstance* const this)
{
	/* destroy base object */
	delete_Instance(this->super);
	/* destroy data memebers */
	free(this);

}

Port* ComponentInstance_FindProvidedByID(ComponentInstance* const this, char* id)
{
	Port* value = NULL;

	if(this->provided != NULL)
	{
		if(hashmap_get(this->provided, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

Port* ComponentInstance_FindRequiredByID(ComponentInstance* const this, char* id)
{
	Port* value = NULL;

	if(this->required != NULL)
	{
		if(hashmap_get(this->required, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void ComponentInstance_AddProvided(ComponentInstance* const this, Port* ptr)
{
	Port *container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Port cannot be added in ComponentInstance because the key is not defined\n");
	}
	else
	{
		if(this->provided == NULL)
		{
			this->provided = hashmap_new();
		}
		if(hashmap_get(this->provided, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (MBinding*)ptr;*/
			if(hashmap_put(this->provided, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->eContainer) + strlen("/component[]") + strlen(this->InternalGetKey(this))) + 1);
				sprintf(ptr->eContainer, "%s/component[%s]", this->eContainer, this->InternalGetKey(this));
			}
		}
	}
}

void ComponentInstance_AddRequired(ComponentInstance* const this, Port* ptr)
{
	Port *container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Port cannot be added in ComponentInstance because the key is not defined\n");
	}
	else
	{
		if(this->required == NULL)
		{
			this->required = hashmap_new();
		}
		if(hashmap_get(this->required, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (MBinding*)ptr;*/
			if(hashmap_put(this->required, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->eContainer) + strlen("/component[]") + strlen(this->InternalGetKey(this))) + 1);
				sprintf(ptr->eContainer, "%s/component[%s]", this->eContainer, this->InternalGetKey(this));
			}
			/*
			 * TODO add else
			 */
		}
	}
}

void ComponentInstance_RemoveProvided(ComponentInstance* const this, Port* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Port cannot be removed in ComponentInstance because the key is not defined\n");
		free(internalKey);
	}
	else
	{
		if(hashmap_remove(this->provided, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void ComponentInstance_RemoveRequired(ComponentInstance* const this, Port* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Port cannot be removed in ComponentInstance because the key is not defined\n");
		free(internalKey);
	}
	else
	{
		if(hashmap_remove(this->required, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void ComponentInstance_VisitAttributes(void *const this, char *parent, Visitor *visitor)
{
	/*char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((ComponentInstance*)this)->MetaClassName((ComponentInstance*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	Instance_VisitAttributes(((ComponentInstance*)this)->super, parent, visitor, true);
}

void ComponentInstance_VisitPathAttributes(void *const this, char *parent, Visitor *visitor)
{
	Instance_VisitPathAttributes(((ComponentInstance*)this)->super, parent, visitor, true);
}

void ComponentInstance_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((ComponentInstance*)(this))->provided != NULL)
	{
		visitor->action("provided", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((ComponentInstance*)(this))->provided);

		/* provided */
		hashmap_map* m = ((ComponentInstance*)(this))->provided;

		/* compare provided */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				Port* n = data;
				/*sprintf(path,"%s/provided[%s]", parent, n->InternalGetKey(n));*/
				sprintf(path, "provided");
				n->VisitAttributes(n, path, visitor, true);
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
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("provided", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((ComponentInstance*)(this))->required != NULL)
	{
		visitor->action("required", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((ComponentInstance*)(this))->required);

		/* required */
		hashmap_map* m = ((ComponentInstance*)(this))->required;

		/* compare required */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				Port* n = data;
				/*sprintf(path,"%s/required[%s]", parent, n->InternalGetKey(n));*/
				sprintf(path, "required");
				n->VisitAttributes(n, path, visitor, 1);
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
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("required", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	/* Instance references */
	Instance_VisitReferences(((ComponentInstance*)(this))->super, parent, visitor, false);

}

void ComponentInstance_VisitPathReferences(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* Instance references */
	Instance_VisitPathReferences(((ComponentInstance*)(this))->super, parent, visitor, false);

	if(((ComponentInstance*)(this))->provided != NULL)
	{
		int i;

		/* provided */
		hashmap_map* m = ((ComponentInstance*)(this))->provided;

		/* compare provided */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Port* n = data;
				sprintf(path,"%s/provided[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, false);
				n->VisitPathReferences(n, path, visitor);
			}
		}
	}

	if(((ComponentInstance*)(this))->required != NULL)
	{
		int i;

		/* required */
		hashmap_map* m = ((ComponentInstance*)(this))->required;

		/* compare required */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Port* n = data;
				sprintf(path,"%s/required[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, 1);
				n->VisitPathReferences(n, path, visitor);
			}
		}
	}
}

void *ComponentInstance_FindByPath(char* attribute, ComponentInstance* const this)
{
	/* There is no local attributes */

	/* Instance attributes */
	if(!strcmp("name", attribute) ||  !strcmp("metaData", attribute) || !strcmp("started", attribute) /*|| !strcmp("typeDefinition", attribute)*/)
	{
		return Instance_FindByPath(attribute, this->super);/*return this->super->metaData;*/
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

		if(!strcmp("provided", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{

				return this->FindProvidedByID(this, key);
			}
			else
			{
				Port* port = this->FindProvidedByID(this, key);
				if(port != NULL)
					return port->FindByPath(nextPath, port);
				else
					return NULL;
			}
		}
		else if(!strcmp("required", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->FindRequiredByID(this, key);
			}
			else
			{
				Port* port = this->FindRequiredByID(this, key);
				if(port != NULL)
					return port->FindByPath(nextPath, port);
				else
					return NULL;
			}
		}
		/* Instance references */
		else
		{
			free(obj);
			return Instance_FindByPath(attribute, this->super);
		}
	}
}
