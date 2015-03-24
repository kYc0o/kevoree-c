#include "NetworkProperty.h"
#include "NodeNetwork.h"
#include "Visitor.h"
#include "tools.h"
#include "NodeLink.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NodeLink* new_NodeLink()
{
	NodeLink* pObj;
	/* Allocating memory */
	pObj = (NodeLink*)malloc(sizeof(NodeLink));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);

	pObj->networkType = NULL;
	pObj->estimatedRate = -1;
	pObj->lastCheck = NULL;
	pObj->zoneID = NULL;
	pObj->networkProperties = NULL;

	pObj->internalGetKey = NodeLink_internalGetKey;
	pObj->metaClassName = NodeLink_metaClassName;
	pObj->FindNetworkPropertiesByID = NodeLink_FindNetworkPropertiesByID;
	pObj->AddNetworkProperties = NodeLink_AddNetworkProperties;
	pObj->RemoveNetworkProperties = NodeLink_RemoveNetworkProperties;
	pObj->Delete = delete_NodeLink;
	pObj->VisitAttributes = NodeLink_VisitAttributes;
	pObj->VisitPathAttributes = NodeLink_VisitPathAttributes;
	pObj->VisitReferences = NodeLink_VisitReferences;
	pObj->VisitPathReferences = NodeLink_VisitPathReferences;
	pObj->FindByPath = NodeLink_FindByPath;

	return pObj;
}

char* NodeLink_internalGetKey(void * const this)
{
	NodeLink *pObj = (NodeLink*)this;
	return pObj->generated_KMF_ID;
}

char* NodeLink_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("NodeLink")) + 1);
	if(name != NULL)
		strcpy(name, "NodeLink");
	else
		return NULL;

	return name;
}

NetworkProperty* NodeLink_FindNetworkPropertiesByID(NodeLink* const this, char* id)
{
	NetworkProperty* value = NULL;

	if(this->networkProperties != NULL)
	{
		if(hashmap_get(this->networkProperties, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

}

void NodeLink_AddNetworkProperties(NodeLink* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkProperty cannot be added in NodeLink because the key is not defined\n");
	}
	else
	{
		if(this->networkProperties == NULL)
		{
			this->networkProperties = hashmap_new();
		}
		if(hashmap_get(this->networkProperties, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (NetworkProperty*)ptr;*/
			if(hashmap_put(this->networkProperties, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/networkProperties[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/networkProperties[%s]", this->path, internalKey);
			}
		}
	}
}

void NodeLink_RemoveNetworkProperties(NodeLink* const this, NetworkProperty* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkProperty cannot be removed in NodeLink because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->networkProperties, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void delete_NodeLink(void * const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		NodeLink *pObj = (NodeLink*)this;
		free(pObj->networkType);
		free(pObj->lastCheck);
		free(pObj->zoneID);
		free(pObj->generated_KMF_ID);
		hashmap_free(pObj->networkProperties);
		free(pObj->eContainer);
		free(pObj);
	}
}

void NodeLink_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeLink*)this)->metaClassName((NodeLink*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);

	sprintf(path, "%s\\ID", parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->generated_KMF_ID);

	sprintf(path, "%s\\networkType", parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->networkType);

	sprintf(path,"%s\\lastCheck",parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->lastCheck);

	sprintf(path,"%s\\zoneID",parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->zoneID);

	sprintf(path, "%s\\estimatedRate", parent);
	visitor->action(path, INTEGER, (void*)((NodeLink*)(this))->estimatedRate);
}

void NodeLink_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeLink*)this)->metaClassName((NodeLink*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path, "%s\\ID", parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->generated_KMF_ID);

	sprintf(path, "%s\\networkType", parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->networkType);

	sprintf(path,"%s\\lastCheck",parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->lastCheck);

	sprintf(path,"%s\\zoneID",parent);
	visitor->action(path, STRING, ((NodeLink*)(this))->zoneID);

	sprintf(path, "%s\\estimatedRate", parent);
	visitor->action(path, BOOL, (void*)((NodeLink*)(this))->estimatedRate);
}

void NodeLink_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NodeLink*)(this))->networkProperties != NULL)
	{
		int i;

		/* networkProperties */
		hashmap_map* m = ((NodeLink*)(this))->networkProperties;

		/* compare networkProperties */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				sprintf(path,"%s/networkProperties[%s]", parent, n->internalGetKey(n));
				n->VisitAttributes(n, path, visitor, recursive);
			}
		}
	}
}

void NodeLink_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NodeLink*)(this))->networkProperties != NULL)
	{
		int i;

		/* networkProperties */
		hashmap_map* m = ((NodeLink*)(this))->networkProperties;

		/* compare networkProperties */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkProperty* n = data;
				sprintf(path,"%s/networkProperties[%s]", parent, n->internalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, recursive);
			}
		}
	}
}

void* NodeLink_FindByPath(char* attribute, void * const this)
{
	NodeLink *pObj = (NodeLink*)this;
	/* Local attributes */
	if(!strcmp("networkType", attribute))
	{
		return pObj->networkType;
	}
	else if(!strcmp("estimatedRate", attribute))
	{
		return (void*)pObj->estimatedRate;
	}
	else if(!strcmp("lastCheck", attribute))
	{
		return pObj->lastCheck;
	}
	else if(!strcmp("zoneID", attribute))
	{
		return pObj->zoneID;
	}
	/*else if(!strcmp("generated_KMF_ID", attribute))
	{
		return this->generated_KMF_ID;
	}*/
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

		if(!strcmp("networkProperties", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindNetworkPropertiesByID(pObj, key);
			}
			else
			{
				NetworkProperty* netprop = pObj->FindNetworkPropertiesByID(pObj, key);
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
