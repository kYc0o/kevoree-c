#include "Port.h"

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
	
	pObj->AddBindings = Port_AddBindings;
	pObj->AddPortTypeRef = Port_AddPortTypeRef;
	pObj->RemoveBindings = Port_RemoveBindings;
	pObj->RemovePortTypeRef = Port_RemovePortTypeRef;

	pObj->InternalGetKey = Port_InternalGetKey;
	pObj->MetaClassName = Port_MetaClassName;
	pObj->super->MetaClassName = Port_MetaClassName;
	pObj->Delete = delete_Port;
	pObj->VisitAttributes = Port_VisitAttributes;
	pObj->VisitReferences = Port_VisitReferences;
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

	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The MBinding cannot be added in Port because the key is not defined\n");
	}
	else
	{
		if(this->bindings == NULL)
		{
			this->bindings = hashmap_new();
		}

		if(hashmap_get(this->bindings, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (MBinding*)ptr;*/
			hashmap_put(this->bindings, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void Port_AddPortTypeRef(Port* const this, PortTypeRef* ptr)
{
	this->portTypeRef = ptr;
}

void Port_RemoveBindings(Port* const this, MBinding* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The MBinding cannot be removed in Port because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->bindings, ptr->InternalGetKey(ptr));
	}
}

void Port_RemovePortTypeRef(Port* const this, PortTypeRef* ptr)
{
	free(ptr);
	this->portTypeRef = NULL;
}

void Port_VisitAttributes(Port* const this, char* parent, Visitor* visitor, int recursive)
{
	/*char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, this->MetaClassName(this));*/

	NamedElement_VisitAttributes(this->super, parent, visitor, recursive);
}

void Port_VisitReferences(Port* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	hashmap_map* m = NULL;
	
	if((m = (hashmap_map*)this->bindings) != NULL)
	{
		/*int i;*/
		visitor->action("bindings", SQBRACKET, NULL);
		for(int i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				/*sprintf(path, "%s/bindings[%s]", parent, n->InternalGetKey(n));*/
				/*n->VisitAttributes(n, path, visitor, 0);*/
				/*n->VisitReferences(n, path, visitor);*/
				sprintf(path, "bindings[%s]", n->InternalGetKey(n));
				visitor->action(path, STRREF, NULL);
					visitor->action(NULL, COLON, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	
	if(this->portTypeRef != NULL)
	{
		visitor->action("portTypeRef", SQBRACKET, NULL);
		/*sprintf(path, "%s/portTypeRef[%s]", parent, this->portTypeRef->InternalGetKey(this->portTypeRef));
		this->portTypeRef->VisitAttributes(this->portTypeRef, path, visitor, 0);*/
		/*this->portTypeRef->VisitReferences(this->portTypeRef, path, visitor);*/
		sprintf(path, "portTypeRef[%s]", this->portTypeRef->InternalGetKey(this->portTypeRef));
		visitor->action(path, STRREF, NULL);
		visitor->action(NULL, RETURN, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
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
	  
		if(!strcmp("bindings", relationName))
		{
			if(nextAttribute == NULL)
			{
				
				return this->FindBindingsByID(this, queryID);
			}
			else
			{
				MBinding* binding = this->FindBindingsByID(this, queryID);
				if(binding != NULL)
					return binding->FindByPath(nextAttribute, binding);
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
