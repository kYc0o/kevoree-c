#include <string.h>
#include "Instance.h"
#include "ContainerRoot.h"
#include "MBinding.h"
#include "tools.h"
#include "Channel.h"
#include "NamedElement.h"
#include "Visitor.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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
	pObj->VisitPathAttributes = Channel_VisitPathAttributes;
	pObj->VisitReferences = Channel_VisitReferences;
	pObj->VisitPathReferences = Channel_VisitPathReferences;

	pObj->metaClassName = Channel_metaClassName;
	pObj->internalGetKey = Channel_internalGetKey;

	pChannelObj->bindings = NULL;
	pChannelObj->eContainer = NULL;
	pChannelObj->path = NULL;
	pChannelObj->refs = NULL;

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
	pChannelObj->VisitPathAttributes = Channel_VisitPathAttributes;
	pChannelObj->VisitReferences = Channel_VisitReferences;
	pChannelObj->VisitPathReferences = Channel_VisitPathReferences;

	pChannelObj->bindings = NULL;
	pChannelObj->eContainer = NULL;
	pChannelObj->path = NULL;
	pChannelObj->refs =  NULL;

	pChannelObj->FindBindingsByID = Channel_FindBindingsByID;
	pChannelObj->AddBindings = Channel_AddBindings;
	pChannelObj->RemoveBindings = Channel_RemoveBindings;

	pChannelObj->metaClassName = Channel_metaClassName;
	pObj->super->metaClassName = Channel_metaClassName;
	pChannelObj->internalGetKey = Channel_internalGetKey;
	pChannelObj->FindByPath = Channel_FindByPath;

	pChannelObj->Delete = delete_Channel;

	return pChannelObj;
}

void deletePoly_Channel(void* const this)
{
	if(this != NULL)
	{
		Channel* pChannelObj;
		pChannelObj = (Channel*)((Instance*)this)->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pChannelObj->bindings);
		free(pChannelObj->eContainer);
		free(pChannelObj);
		/*destroy base Obj*/
		delete_Instance(((Instance*)this));
	}
}

void delete_Channel(void* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_Instance(((Channel*)this)->super);
		/* destroy data memebers */
		hashmap_free(((Channel*)this)->bindings);
		free(((Channel*)this)->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* Channel_metaClassName(void* const this)
{
	/*
	Channel *pObj = (Channel*)this;
	char *name = NULL;

	name = malloc(sizeof(char) * (strlen("Channel")) + 1);
	if(name != NULL)
		strcpy(name, "Channel");
	else
		return NULL;

	return name;
	*/
	return "Channel";
}

char* Channel_internalGetKey(void* const this)
{
	Channel *pObj = (Channel*)this;
	return pObj->super->internalGetKey(pObj->super);
}

void Channel_AddBindings(Channel* const this, MBinding* ptr)
{
	/*
	 * TODO change map by reference 1..1
	 */
	MBinding* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The MBinding cannot be added in Channel because the key is not defined\n");
	}
	else
	{
		if(this->bindings == NULL)
		{
			/*
			 * TODO add if == NULL
			 */
			this->bindings = hashmap_new();
		}
		if(hashmap_get(this->bindings, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (MBinding*)ptr;*/
			if ((hashmap_put(this->bindings, internalKey, ptr)) == MAP_OK) {
				if (ptr->refs == NULL) {
					if ((ptr->refs = hashmap_new()) != NULL) {
						char *reference;
						if ((reference = malloc(sizeof(char) * strlen("hubs[]") + strlen(this->internalGetKey(this)) + 1)) != NULL) {
							sprintf(reference, "hubs[%s]", this->internalGetKey(this));
							if ((hashmap_put(ptr->refs, this->path, (void**)&reference)) == MAP_OK) {
								PRINTF("INFO: reference added!\n");
							} else {
								PRINTF("ERROR: cannot add reference to map!\n");
							}
						} else {
							PRINTF("ERROR: not enough memory for reference!\n");
						}
					} else {
						PRINTF("ERROR: cannot create references map!\n");
					}
				} else {
					char *reference;
					if ((reference = malloc(sizeof(char) * strlen("hubs[]") + strlen(this->internalGetKey(this)) + 1)) != NULL) {
						sprintf(reference, "hubs[%s]", this->internalGetKey(this));
						if ((hashmap_put(ptr->refs, this->path, (void**)&reference)) == MAP_OK) {
							PRINTF("INFO: reference added!\n");
						} else {
							PRINTF("ERROR: cannot add reference to map!\n");
						}
					} else {
						PRINTF("ERROR: not enough memory for reference!\n");
					}
				}
			} else {
				PRINTF("ERROR: cannot add binding!\n");
			}
		}
	}
}
void Channel_RemoveBindings(Channel* const this, MBinding* ptr)
{
	/*
	 * TODO change map by reference 1..1
	 * TODO remove reference too
	 */
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The MBinding cannot be removed in Channel because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->bindings, internalKey);
	}
}

MBinding* Channel_FindBindingsByID(Channel* const this, char* id)
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

void Channel_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	Instance_VisitAttributes(((Channel*)this)->super, parent, visitor, recursive);
}

void Channel_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	Instance_VisitPathAttributes(((Channel*)this)->super, parent, visitor, recursive);
}

void Channel_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* Local references */
	hashmap_map* m = NULL;

	if((m = (hashmap_map*) ((Channel*)(this))->bindings) != NULL)
	{
		int length = hashmap_length(((Channel*)(this))->bindings);

		visitor->action("bindings", SQBRACKET, NULL);
		/* compare bindings*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				/*sprintf(path, "%s/bindings[%s]", parent, n->internalGetKey(n));*/
				sprintf(path, "mBindings[%s]", n->internalGetKey(n));
				/*n->VisitAttributes(n, path, visitor, 0);
				n->VisitReferences(n, path, visitor);*/
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

	/* Instance references */
	Instance_VisitReferences(((Instance*)this)->super, parent, visitor, false);
}

void Channel_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* Local references */
	hashmap_map* m = NULL;

	if((m = (hashmap_map*) ((Channel*)(this))->bindings) != NULL)
	{
		/* compare bindings*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "%s\\bindings", n->path);
				visitor->action(path, REFERENCE, parent);
				/*n->VisitReferences(n, path, visitor);*/
			}
		}
	}

	/* Instance references */
	Instance_VisitPathReferences(((Instance*)this)->super, parent, visitor, true);
}

void* Channel_FindByPath(char* attribute, void* const this)
{
	Channel *pObj = (Channel*)this;
	/* There is no local attributes */

	/* Instance attributes and references */
	if(!strcmp("name", attribute) ||  !strcmp("metaData", attribute) || !strcmp("started", attribute) || !strcmp("typeDefinition", attribute))
	{
		return Instance_FindByPath(attribute, pObj->super);
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
		/* Instance references */
		else
		{
			free(obj);
			return Instance_FindByPath(attribute, pObj->super);
		}
	}
}
