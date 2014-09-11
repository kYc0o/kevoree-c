#include <string.h>
#include "NamedElement.h"
#include "Instance.h"
#include "Port.h"
#include "TypeDefinition.h"
#include "ContainerNode.h"
#include "Visitor.h"
#include "ComponentInstance.h"

Instance* newPoly_ComponentInstance()
{
	ComponentInstance* pCompInstanceObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pCompInstanceObj = (ComponentInstance*)my_malloc(sizeof(ComponentInstance));

	if (pCompInstanceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pCompInstanceObj; /* Pointing to derived object */
	pObj->VisitAttributes = ComponentInstance_VisitAttributes;
	
	pCompInstanceObj->provided = NULL;
	pCompInstanceObj->required = NULL;

	pCompInstanceObj->AddProvided = ComponentInstance_AddProvided;
	pCompInstanceObj->AddRequired = ComponentInstance_AddRequired;
	pCompInstanceObj->RemoveProvided = ComponentInstance_RemoveProvided;
	pCompInstanceObj->RemoveRequired = ComponentInstance_RemoveRequired;

	pObj->MetaClassName = ComponentInstance_MetaClassName;
	pObj->InternalGetKey = ComponentInstance_InternalGetKey;
	
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
	pCompInstanceObj = (ComponentInstance*)my_malloc(sizeof(ComponentInstance));

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
	pCompInstanceObj->VisitReferences = ComponentInstance_VisitReferences;
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

	name = my_malloc(sizeof(char) * (strlen("ComponentInstance")) + 1);
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
		printf("The Port cannot be added in ComponentInstance because the key is not defined\n");
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
				ptr->eContainer = this;
		}
	}
}

void ComponentInstance_AddRequired(ComponentInstance* const this, Port* ptr)
{
	Port *container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The Port cannot be added in ComponentInstance because the key is not defined\n");
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
				ptr->eContainer = this;
		}
	}
}

void ComponentInstance_RemoveProvided(ComponentInstance* const this, Port* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The Port cannot be removed in ComponentInstance because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->provided, internalKey) == MAP_OK)
		{
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
		printf("The Port cannot be removed in ComponentInstance because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->required, internalKey) == MAP_OK)
		{
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void ComponentInstance_VisitAttributes(void* const this, char *parent, Visitor* visitor)
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
				sprintf(path, "typeDefinitions[%s]/required", ((ComponentInstance*)this)->super->typeDefinition->InternalGetKey(((ComponentInstance*)this)->super->typeDefinition));
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

void* ComponentInstance_FindByPath(char* attribute, ComponentInstance* const this)
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
		char* nextAttribute = NULL;
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
			/*nextAttribute = strtok(NULL, "\\");
			sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));*/
			/*printf("pch: %s\n", pch);*/
			if(strchr(attribute,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);*/
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not found...\n");*/
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}

		printf("Token: %s\n", pch);

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);

		printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);

		if(!strcmp("provided", relationName))
		{
			if(nextAttribute == NULL)
			{

				return this->FindProvidedByID(this, queryID);
			}
			else
			{
				Port* port = this->FindProvidedByID(this, queryID);
				if(port != NULL)
					return port->FindByPath(nextAttribute, port);
				else
					return NULL;
			}
		}
		else if(!strcmp("required", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindRequiredByID(this, queryID);
			}
			else
			{
				Port* port = this->FindRequiredByID(this, queryID);
				if(port != NULL)
					return port->FindByPath(nextAttribute, port);
				else
					return NULL;
			}
		}
		/* Instance references */
		else
		{
			return Instance_FindByPath(attribute, this->super);
		}
	}
}
