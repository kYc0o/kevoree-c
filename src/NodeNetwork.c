#include "ContainerNode.h"
#include "NodeLink.h"
#include "Visitor.h"
#include "tools.h"
#include "NodeNetwork.h"

NodeNetwork* new_NodeNetwork()
{
	NodeNetwork* pObj;
	/* Allocating memory */
	pObj = (NodeNetwork*)my_malloc(sizeof(NodeNetwork));

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
	
	pObj->InternalGetKey = NodeNetwork_InternalGetKey;
	pObj->MetaClassName = NodeNetwork_MetaClassName;
	pObj->FindLinkByID = NodeNetwork_FindLinkByID;
	pObj->AddLink = NodeNetwork_AddLink;
	pObj->AddInitBy = NodeNetwork_AddInitBy;
	pObj->AddTarget = NodeNetwork_AddTarget;
	pObj->RemoveLink = NodeNetwork_RemoveLink;
	pObj->RemoveInitBy = NodeNetwork_RemoveInitBy;
	pObj->RemoveTarget = NodeNetwork_RemoveTarget;
	pObj->Delete = delete_NodeNetwork;
	pObj->VisitAttributes = NodeNetwork_VisitAttributes;
	pObj->VisitReferences = NodeNetwork_VisitReferences;
	pObj->FindByPath = NodeNetwork_FindByPath;
	
	return pObj;
}

char* NodeNetwork_InternalGetKey(NodeNetwork* const this)
{
	return this->generated_KMF_ID;
}

char* NodeNetwork_MetaClassName(NodeNetwork* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("NodeNetwork")) + 1);
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

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The NodeLink cannot be added in NodeNetwork because the key is not defined\n");
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
				ptr->eContainer = my_malloc(sizeof(char) * (strlen("nodeNetwork[]") + strlen(this->InternalGetKey(this))) + 1);
				sprintf(ptr->eContainer, "nodeNetwork[%s]", this->InternalGetKey(this));
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
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The NodeLink cannot be removed in NodeNetwork because the key is not defined\n");
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

void delete_NodeNetwork(NodeNetwork* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->generated_KMF_ID);
		free(this->initBy);
		free(this->target);
		free(this->eContainer);
		hashmap_free(this->link);
		free(this);
		/*this = NULL;*/
	}
}

void NodeNetwork_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((NodeNetwork*)this)->MetaClassName((NodeNetwork*)this);
	visitor->action(path, STRING, cClass);

	sprintf(path,"%s\\ID", parent);
	visitor->action(path, STRING, ((NodeNetwork*)(this))->generated_KMF_ID);
}
void NodeNetwork_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((NodeNetwork*)(this))->target != NULL)
	{
		sprintf(path, "%s/target[%s]", parent, ((NodeNetwork*)(this))->target->InternalGetKey(((NodeNetwork*)(this))->target));
		((NodeNetwork*)(this))->target->VisitAttributes(((NodeNetwork*)(this))->target, path, visitor, 0);
		/*((NodeNetwork*)(this))->target->VisitReferences(((NodeNetwork*)(this))->target, path, visitor);*/
	}
	
	if(((NodeNetwork*)(this))->initBy != NULL)
	{
		sprintf(path, "%s/initBy[%s]", parent, /*((NodeNetwork*)(this))->initBy->super->super->name*/((NodeNetwork*)(this))->initBy->InternalGetKey(((NodeNetwork*)(this))->initBy));
		((NodeNetwork*)(this))->initBy->VisitAttributes(((NodeNetwork*)(this))->initBy, path, visitor, 0);
		/*((NodeNetwork*)(this))->initBy->VisitReferences(((NodeNetwork*)(this))->initBy, path, visitor);*/
	}
	
	if(((NodeNetwork*)(this))->link != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/link[%s]", parent, ((NodeNetwork*)(this))->generated_KMF_ID);*/
		
		/* link */
		hashmap_map* m = ((NodeNetwork*)(this))->link;

		/* compare link */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NodeLink* n = data;
				sprintf(path,"%s/link[%s]", parent, /*n->generated_KMF_ID*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
}

void* NodeNetwork_FindByPath(char* attribute, NodeNetwork* const this)
{
	/* NamedElement attributes */
	if(!strcmp("generated_KMF_ID", attribute))
	{
		return this->generated_KMF_ID;
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
			if(strchr(attribute,'\\') != NULL)
			{
				printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				printf("Attribute not found, looking for path\n");
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}
		
		/*printf("Token: %s\n", pch);*/

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		/*printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);*/
		
		if(!strcmp("link", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindLinkByID(this, queryID);
			}
			else
			{
				NodeLink* nodelink = this->FindLinkByID(this, queryID);
				if(nodelink != NULL)
					return nodelink->FindByPath(nextAttribute, nodelink);
				else
					return NULL;
			}
		}
		else if(!strcmp("initBy", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->initBy;
			}
			else
			{
				return this->initBy->FindByPath(nextAttribute, this->initBy);
			}
		}
		else if(!strcmp("target", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->target;
			}
			else
			{
				return this->target->FindByPath(nextAttribute, this->target);
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
