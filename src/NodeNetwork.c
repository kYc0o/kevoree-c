#include "ContainerNode.h"
#include "NodeLink.h"
#include "Visitor.h"
#include "tools.h"
#include "NodeNetwork.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NodeNetwork* new_NodeNetwork()
{
	NodeNetwork* pObj;
	/* Allocating memory */
	pObj = (NodeNetwork*)malloc(sizeof(NodeNetwork));

	if (pObj == NULL)
	{
		return NULL;
	}

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);

	pObj->initBy = NULL;
	pObj->target = NULL;
	pObj->link = NULL;
	pObj->eContainer = NULL;

	pObj->internalGetKey = NodeNetwork_internalGetKey;
	pObj->metaClassName = NodeNetwork_metaClassName;
	pObj->FindLinkByID = NodeNetwork_FindLinkByID;
	pObj->AddLink = NodeNetwork_AddLink;
	pObj->AddInitBy = NodeNetwork_AddInitBy;
	pObj->AddTarget = NodeNetwork_AddTarget;
	pObj->RemoveLink = NodeNetwork_RemoveLink;
	pObj->RemoveInitBy = NodeNetwork_RemoveInitBy;
	pObj->RemoveTarget = NodeNetwork_RemoveTarget;
	pObj->Delete = delete_NodeNetwork;
	pObj->VisitAttributes = NodeNetwork_VisitAttributes;
	pObj->VisitPathAttributes = NodeNetwork_VisitPathAttributes;
	pObj->VisitReferences = NodeNetwork_VisitReferences;
	pObj->VisitPathReferences = NodeNetwork_VisitPathReferences;
	pObj->FindByPath = NodeNetwork_FindByPath;

	return pObj;
}

char* NodeNetwork_internalGetKey(void * const this)
{
	NodeNetwork *pObj = (NodeNetwork*)this;
	return pObj->generated_KMF_ID;
}

char* NodeNetwork_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("NodeNetwork")) + 1);
	if(name != NULL)
		strcpy(name, "NodeNetwork");
	else
		return NULL;

	return name;
}

NodeLink* NodeNetwork_FindLinkByID(NodeNetwork* const this, char* id)
{
	NodeLink* value = NULL;

	if(this->link != NULL)
	{
		if(hashmap_get(this->link, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void NodeNetwork_AddLink(NodeNetwork* const this, NodeLink* ptr)
{
	NodeLink* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NodeLink cannot be added in NodeNetwork because the key is not defined\n");
	}
	else
	{
		if(this->link == NULL)
		{
			this->link = hashmap_new();
		}
		if(hashmap_get(this->link, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (NodeLink*)ptr;*/
			if(hashmap_put(this->link, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen("nodeNetwork[]") + strlen(this->internalGetKey(this))) + 1);
				sprintf(ptr->eContainer, "nodeNetwork[%s]", this->internalGetKey(this));
			}
		}
	}
}

void NodeNetwork_AddInitBy(NodeNetwork* const this, ContainerNode* ptr)
{
	this->initBy = ptr;
}

void NodeNetwork_AddTarget(NodeNetwork* const this, ContainerNode* ptr)
{
	this->target = ptr;
}

void NodeNetwork_RemoveLink(NodeNetwork* const this, NodeLink* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NodeLink cannot be removed in NodeNetwork because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->link, internalKey) == MAP_OK)
		{
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void NodeNetwork_RemoveInitBy(NodeNetwork* const this, ContainerNode *ptr)
{
	free(ptr);
	this->initBy = NULL;
}

void NodeNetwork_RemoveTarget(NodeNetwork* const this, ContainerNode* ptr)
{
	free(ptr);
	this->target = NULL;
}

void delete_NodeNetwork(void * const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		NodeNetwork *pObj = (NodeNetwork*)this;
		/*
		free(pObj->generated_KMF_ID);
		free(pObj->initBy);
		free(pObj->target);
		free(pObj->eContainer);
		*/
		hashmap_free(pObj->link);
		free(pObj);
		/*this = NULL;*/
	}
}

void NodeNetwork_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeNetwork*)this)->metaClassName((NodeNetwork*)this);
	visitor->action(path, STRING, cClass);

	sprintf(path,"%s\\ID", parent);
	visitor->action(path, STRING, ((NodeNetwork*)(this))->generated_KMF_ID);
}

void NodeNetwork_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeNetwork*)this)->metaClassName((NodeNetwork*)this);
	visitor->action(path, STRING, cClass);*/

	sprintf(path,"%s\\ID", parent);
	visitor->action(path, STRING, ((NodeNetwork*)(this))->generated_KMF_ID);
}

void NodeNetwork_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NodeNetwork*)(this))->target != NULL)
	{
		sprintf(path, "%s/target[%s]", parent, ((NodeNetwork*)(this))->target->internalGetKey(((NodeNetwork*)(this))->target));
		((NodeNetwork*)(this))->target->VisitAttributes(((NodeNetwork*)(this))->target, path, visitor, false);
	}

	if(((NodeNetwork*)(this))->initBy != NULL)
	{
		sprintf(path, "%s/initBy[%s]", parent, ((NodeNetwork*)(this))->initBy->internalGetKey(((NodeNetwork*)(this))->initBy));
		((NodeNetwork*)(this))->initBy->VisitAttributes(((NodeNetwork*)(this))->initBy, path, visitor, false);
	}

	if(((NodeNetwork*)(this))->link != NULL)
	{
		int i;

		/* link */
		hashmap_map* m = ((NodeNetwork*)(this))->link;

		/* compare link */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NodeLink* n = data;
				sprintf(path,"%s/link[%s]", parent, n->internalGetKey(n));
				n->VisitAttributes(n, path, visitor, recursive);
				n->VisitReferences(n, path, visitor, recursive);
			}
		}
	}
}

void NodeNetwork_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NodeNetwork*)(this))->target != NULL)
	{
		sprintf(path, "%s/target[%s]", parent, ((NodeNetwork*)(this))->target->internalGetKey(((NodeNetwork*)(this))->target));
		if (visitor->secondAction != NULL) {
			if (visitor->secondAction(path, "target")) {
				((NodeNetwork*)(this))->target->VisitAttributes(((NodeNetwork*)(this))->target, path, visitor, false);
			}
		} else {
			((NodeNetwork*)(this))->target->VisitAttributes(((NodeNetwork*)(this))->target, path, visitor, false);
		}
	}

	if(((NodeNetwork*)(this))->initBy != NULL)
	{
		sprintf(path, "%s/initBy[%s]", parent, ((NodeNetwork*)(this))->initBy->internalGetKey(((NodeNetwork*)(this))->initBy));
		if (visitor->secondAction != NULL) {
			if (visitor->secondAction(path, "initBy")) {
				((NodeNetwork*)(this))->initBy->VisitAttributes(((NodeNetwork*)(this))->initBy, path, visitor, false);
			}
		} else {
			((NodeNetwork*)(this))->initBy->VisitAttributes(((NodeNetwork*)(this))->initBy, path, visitor, false);
		}
	}

	if(((NodeNetwork*)(this))->link != NULL)
	{
		int i;

		/* link */
		hashmap_map* m = ((NodeNetwork*)(this))->link;

		/* compare link */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NodeLink* n = data;
				sprintf(path,"%s/link[%s]", parent, n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "link")) {
						n->VisitPathAttributes(n, path, visitor, recursive);
						n->VisitPathReferences(n, path, visitor, recursive);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, recursive);
					n->VisitPathReferences(n, path, visitor, recursive);
				}
			}
		}
	}
}

void* NodeNetwork_FindByPath(char* attribute, void * const this)
{
	NodeNetwork *pObj = (NodeNetwork*)this;
	/* NamedElement attributes */
	if(!strcmp("generated_KMF_ID", attribute))
	{
		return pObj->generated_KMF_ID;
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

		if(!strcmp("link", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindLinkByID(pObj, key);
			}
			else
			{
				NodeLink* nodelink = pObj->FindLinkByID(pObj, key);
				if(nodelink != NULL)
					return nodelink->FindByPath(nextPath, nodelink);
				else
					return NULL;
			}
		}
		else if(!strcmp("initBy", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->initBy;
			}
			else
			{
				return pObj->initBy->FindByPath(nextPath, pObj->initBy);
			}
		}
		else if(!strcmp("target", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->target;
			}
			else
			{
				return pObj->target->FindByPath(nextPath, pObj->target);
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
