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

	pObj->InternalGetKey = NodeLink_InternalGetKey;
	pObj->MetaClassName = NodeLink_MetaClassName;
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

char* NodeLink_InternalGetKey(NodeLink* const this)
{
	return this->generated_KMF_ID;
}

char* NodeLink_MetaClassName(NodeLink* const this)
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

	char *internalKey = ptr->InternalGetKey(ptr);

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
				ptr->eContainerNL = malloc(sizeof(char) * (strlen("nodeLink[]") + strlen(this->InternalGetKey(this))) + 1);
				sprintf(ptr->eContainerNL, "nodeLink[%s]", this->InternalGetKey(this));
			}
		}
	}
}

void NodeLink_RemoveNetworkProperties(NodeLink* const this, NetworkProperty* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkProperty cannot be removed in NodeLink because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->networkProperties, internalKey) == MAP_OK)
		{
			ptr->eContainerNL = NULL;
			free(internalKey);
		}
	}
}

void delete_NodeLink(NodeLink* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->networkType);
		free(this->lastCheck);
		free(this->zoneID);
		free(this->generated_KMF_ID);
		hashmap_free(this->networkProperties);
		free(this->eContainer);
		free(this);
	}
}

void NodeLink_VisitAttributes(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeLink*)this)->MetaClassName((NodeLink*)this);
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
	visitor->action(path, INTEGER, ((NodeLink*)(this))->estimatedRate);
}

void NodeLink_VisitPathAttributes(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeLink*)this)->MetaClassName((NodeLink*)this);
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
	visitor->action(path, BOOL, ((NodeLink*)(this))->estimatedRate);
}

void NodeLink_VisitReferences(void *const this, char *parent, Visitor *visitor)
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
				sprintf(path,"%s/networkProperties[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
			}
		}
	}
}

void NodeLink_VisitPathReferences(void *const this, char *parent, Visitor *visitor)
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
				sprintf(path,"%s/networkProperties[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor);
			}
		}
	}
}

void* NodeLink_FindByPath(char* attribute, NodeLink* const this)
{
	/* Local attributes */
	if(!strcmp("networkType", attribute))
	{
		return this->networkType;
	}
	else if(!strcmp("estimatedRate", attribute))
	{
		return this->estimatedRate;
	}
	else if(!strcmp("lastCheck", attribute))
	{
		return this->lastCheck;
	}
	else if(!strcmp("zoneID", attribute))
	{
		return this->zoneID;
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

		if(!strcmp("networkProperties", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->FindNetworkPropertiesByID(this, key);
			}
			else
			{
				NetworkProperty* netprop = this->FindNetworkPropertiesByID(this, key);
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
