#include "Channel.h"

Instance* newPoly_Channel()
{
	Channel* pChannelObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pChannelObj = (Channel*)malloc(sizeof(Channel));

	if (pChannelObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pChannelObj; /* Pointing to derived object */
	pObj->VisitAttributes = Channel_VisitAttributes;
	pObj->VisitReferences = Channel_VisitReferences;
	
	pObj->MetaClassName = Channel_MetaClassName;
	pObj->InternalGetKey = Channel_InternalGetKey;
	
	pChannelObj->bindings = NULL;
	
	pChannelObj->FindBindingsByID = Channel_FindBindingsByID;
	pChannelObj->AddBindings = Channel_AddBindings;
	pChannelObj->RemoveBindings = Channel_RemoveBindings;
	
	pObj->FindByPath = Channel_FindByPath;
	
	pObj->Delete = deletePoly_Channel;

	return pObj;
}

Channel* new_Channel()
{
	Channel* pChannelObj = NULL;
	Instance* pObj = new_Instance();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pChannelObj = (Channel*)malloc(sizeof(Channel));

	if (pChannelObj == NULL)
	{
		return NULL;
	}

	/*((Instance*)(pObj->pDerivedObj))->pDerivedObj = pChannelObj; Pointing to derived object */
	pChannelObj->super = pObj;
	pChannelObj->VisitAttributes = Channel_VisitAttributes;
	pChannelObj->VisitReferences = Channel_VisitReferences;
	
	pChannelObj->bindings = NULL;
	
	pChannelObj->FindBindingsByID = Channel_FindBindingsByID;
	pChannelObj->AddBindings = Channel_AddBindings;
	pChannelObj->RemoveBindings = Channel_RemoveBindings;
	
	pChannelObj->MetaClassName = Channel_MetaClassName;
	pChannelObj->InternalGetKey = Channel_InternalGetKey;
	pChannelObj->FindByPath = Channel_FindByPath;
	
	pChannelObj->Delete = delete_Channel;

	return pChannelObj;
}

void deletePoly_Channel(void* const this)
{
	Channel* pChannelObj;
	pChannelObj = (Channel*)((Instance*)this)->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pChannelObj->bindings);
	free(pChannelObj);
	/*destroy base Obj*/
	delete_Instance(((Instance*)this));
}

void delete_Channel(void* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_Instance(((Channel*)this)->super);
		/* destroy data memebers */
		hashmap_free(((Channel*)this)->bindings);
		free(this);
	}
}

char* Channel_MetaClassName(Channel* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("Channel") + 1));
	strcpy(name, "Channel");
	
	return name;
}

char* Channel_InternalGetKey(Channel* const this)
{
	return this->super->InternalGetKey(this->super);
}

void Channel_AddBindings(Channel* const this, MBinding* ptr)
{
	MBinding* container = (MBinding*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The MBinding cannot be added in Channel because the key is not defined\n");
	}
	else
	{
		if(this->bindings == NULL)
		{
			this->bindings = hashmap_new();
		}
		if(hashmap_get(this->bindings, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (MBinding*)ptr;
			hashmap_put(this->bindings, container->InternalGetKey(container), ptr);
		}
	}
}
void Channel_RemoveBindings(Channel* const this, MBinding* ptr)
{
	MBinding* container = (MBinding*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The MBinding cannot be removed in Channel because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->bindings, container->InternalGetKey(container));
	}
}

MBinding* Channel_FindBindingsByID(Channel* const this, char* id)
{
	MBinding* value;

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

void Channel_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	Instance_VisitAttributes(((Channel*)this)->super, parent, visitor);
}

void Channel_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	hashmap_map* m = NULL;
	
	if((m = (hashmap_map*) ((Channel*)(this))->bindings) != NULL)
	{
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "%s/bindings[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
}
void* Channel_FindByPath(char* attribute, Channel* const this)
{
	/* There is no local attributes */
	
	/* Instance attributes and references */
	if(!strcmp("name", attribute) ||  !strcmp("metaData", attribute) || !strcmp("started", attribute) || !strcmp("typeDefinition", attribute))
	{
		return Instance_FindByPath(attribute, this->super);
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
		/* Instance references */
		else
		{
			return Instance_FindByPath(attribute, this->super);
		}
	}
}