#include <stdlib.h>
#include <stdio.h>
#include "NamedElement.h"
#include "NetworkProperty.h"
#include "ContainerNode.h"
#include "Visitor.h"
#include "NetworkInfo.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NamedElement* newPoly_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNetInfoObj; /* Pointing to derived object */

	pNetInfoObj->values = NULL;
	pNetInfoObj->eContainer = NULL;
	pNetInfoObj->path = NULL;

	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;

	pObj->metaClassName = NetworkInfo_metaClassName;
	pObj->internalGetKey = NetworkInfo_internalGetKey;
	pObj->VisitAttributes = NetworkInfo_VisitAttributes;
	pObj->VisitPathAttributes = NetworkInfo_VisitPathAttributes;
	pObj->VisitReferences = NetworkInfo_VisitReferences;
	pObj->VisitPathReferences = NetworkInfo_VisitPathReferences;
	pObj->FindByPath = NetworkInfo_FindByPath;

	pObj->Delete = deletePoly_NetworkInfo;

	return pObj;
}

NetworkInfo* new_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNetInfoObj;  Pointing to derived object */
	pNetInfoObj->super = pObj;

	pNetInfoObj->values = NULL;
	pNetInfoObj->eContainer = NULL;
	pNetInfoObj->path = NULL;

	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;

	pNetInfoObj->metaClassName = NetworkInfo_metaClassName;
	pObj->metaClassName = NetworkInfo_metaClassName;
	pNetInfoObj->internalGetKey = NetworkInfo_internalGetKey;
	pNetInfoObj->VisitAttributes = NetworkInfo_VisitAttributes;
	pNetInfoObj->VisitPathAttributes = NetworkInfo_VisitPathAttributes;
	pNetInfoObj->VisitReferences = NetworkInfo_VisitReferences;
	pNetInfoObj->VisitPathReferences = NetworkInfo_VisitPathReferences;
	pNetInfoObj->FindByPath = NetworkInfo_FindByPath;

	pNetInfoObj->Delete = delete_NetworkInfo;

	return pNetInfoObj;
}

char* NetworkInfo_internalGetKey(void * const this)
{
	NetworkInfo *pObj = (NetworkInfo*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* NetworkInfo_metaClassName(void * const this)
{
	/*char *name;

	name = malloc(sizeof(char) * (strlen("NetworkInfo")) + 1);
	if(name != NULL)
		strcpy(name, "NetworkInfo");
	else
		return NULL;

	return name;
	*/
	return "NetworkInfo";
}

void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkProperty cannot be added in NetworkInfo because the key is not defined\n");
	}
	else
	{
		if(this->values == NULL)
		{
			this->values = hashmap_new();
		}
		if(hashmap_get(this->values, internalKey, (void**)(&container)) == MAP_MISSING)
		{
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

void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkProperty cannot be removed in NetworkInfo because the key is not defined\n");
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

NetworkProperty* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id)
{
	NetworkProperty* value = NULL;

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

void deletePoly_NetworkInfo(void * const this)
{
	if(this != NULL)
	{
		NetworkInfo *pObj = (NetworkInfo*)this;
		NetworkInfo* pNetInfoObj;
		pNetInfoObj = pObj->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pNetInfoObj->values);
		free(pNetInfoObj->eContainer);
		free(pNetInfoObj);
		/*destroy base Obj*/
		delete_NamedElement(pObj);
	}
}

void delete_NetworkInfo(void * const this)
{
	if(this != NULL)
	{
		NetworkInfo *pObj = (NetworkInfo*)this;
		/* destroy base object */
		delete_NamedElement(pObj->super);
		/* destroy data memebers */
		hashmap_free(pObj->values);
		free(pObj->eContainer);
		free(pObj);
	}

}

void NetworkInfo_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	NamedElement_VisitAttributes(((NetworkInfo*)(this))->super, parent, visitor, true);
}

void NetworkInfo_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	NamedElement_VisitPathAttributes(((NetworkInfo*)(this))->super, parent, visitor, true);
}

void NetworkInfo_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NetworkInfo*)(this))->values != NULL)
	{
		visitor->action("values", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((NetworkInfo*)(this))->values);

		/* values */
		hashmap_map* m = ((NetworkInfo*)(this))->values;

		/* compare values */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				n->VisitAttributes(n, path, visitor, recursive);
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

void NetworkInfo_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NetworkInfo*)(this))->values != NULL)
	{
		int i;

		/* values */
		hashmap_map* m = ((NetworkInfo*)(this))->values;

		/* compare values */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				sprintf(path,"%s/values[%s]", parent, n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "values")) {
						n->VisitPathAttributes(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
				}
			}
		}
	}
}

void* NetworkInfo_FindByPath(char* attribute, void * const this)
{
	NetworkInfo *pObj = (NetworkInfo*)this;
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

		if(!strcmp("values", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindValuesByID(pObj, key);
			}
			else
			{
				NetworkProperty* netprop = pObj->FindValuesByID(pObj, key);
				if(netprop != NULL)
					return netprop->FindByPath(nextPath, netprop);
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
