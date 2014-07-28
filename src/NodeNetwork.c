#include "NodeNetwork.h"

NodeNetwork* new_NodeNetwork()
{
	NodeNetwork* pObj;
	/* Allocating memory */
	pObj = (NodeNetwork*)malloc(sizeof(NodeNetwork));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;

	pObj->generated_KMF_ID = malloc(sizeof(char) * (strlen("dummyKMFID_NodeNetwork") + 1));/*Uuid::getSingleton().generateUUID();*/
	strcpy(pObj->generated_KMF_ID, "dummyKMFID_NodeNetwork");
	pObj->initBy = NULL;
	pObj->target = NULL;
	/*pObj->link = hashmap_new();*/
	pObj->link = NULL;
	
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
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->generated_KMF_ID)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->generated_KMF_ID);

	return internalKey;
}

char* NodeNetwork_MetaClassName(NodeNetwork* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NodeNetwork") + 1));
	strcpy(name, "NodeNetwork");
	
	return name;
}

NodeLink* NodeNetwork_FindLinkByID(NodeNetwork* const this, char* id)
{
	NodeLink* value;

	if(hashmap_get(this->link, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

/*void NodeNetwork::addlink(NodeLink *ptr)*/
void NodeNetwork_AddLink(NodeNetwork* const this, NodeLink* ptr)
{
	NodeLink* container = (NodeLink*)ptr;

	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NodeLink cannot be added in NodeNetwork because the key is not defined");*/
		printf("The NodeLink cannot be added in NodeNetwork because the key is not defined\n");
	}
	else
	{
		/*if(link.find(container->internalGetKey()) == link.end())*/
		if(this->link == NULL)
		{
			this->link = hashmap_new();
		}
		if(hashmap_get(this->link, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*link[container->internalGetKey()]=ptr;*/
			container = (NodeLink*)ptr;
			hashmap_put(this->link, container->InternalGetKey(container), ptr);
			/*any ptr_any = container;
			RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"link",ptr_any);
			container->setEContainer(this,cmd,"link");*/
		}
	}
}

/*void NodeNetwork::addinitBy(ContainerNode *ptr)*/
void NodeNetwork_AddInitBy(NodeNetwork* const this, ContainerNode* ptr)
{
	/*initBy =ptr;*/
	this->initBy = ptr;
}

/*void NodeNetwork::addtarget(ContainerNode *ptr)*/
void NodeNetwork_AddTarget(NodeNetwork* const this, ContainerNode* ptr)
{
	/*target =ptr;*/
	this->target = ptr;
}

/*void NodeNetwork::removelink(NodeLink *ptr)*/
void NodeNetwork_RemoveLink(NodeNetwork* const this, NodeLink* ptr)
{
	NodeLink *container = (NodeLink*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NodeLink cannot be removed in NodeNetwork because the key is not defined");*/
		printf("The NodeLink cannot be removed in NodeNetwork because the key is not defined\n");
	}
	else
	{
		/*link.erase( link.find(container->internalGetKey()));*/
		hashmap_remove(this->link, container->InternalGetKey(container));
		/*delete container;
		container->setEContainer(NULL,NULL,"");*/
	}
}

/*void NodeNetwork::removeinitBy(ContainerNode *ptr)*/
void NodeNetwork_RemoveInitBy(NodeNetwork* const this, ContainerNode *ptr)
{
	/*delete ptr;*/
	free(ptr);
}

/*void NodeNetwork::removetarget(ContainerNode *ptr)*/
void NodeNetwork_RemoveTarget(NodeNetwork* const this, ContainerNode* ptr)
{
	/*delete ptr;*/
	free(ptr);
}

void delete_NodeNetwork(NodeNetwork* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->generated_KMF_ID);
		free(this->initBy);
		free(this->target);
		hashmap_free(this->link);
		free(this);
	}
}

void NodeNetwork_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s/%s",parent, ((NodeNetwork*)(this))->generated_KMF_ID);*/

	sprintf(path,"%s\\ID", parent);
	visitor->action(path, STRING, ((NodeNetwork*)(this))->generated_KMF_ID);
}
void NodeNetwork_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	if(((NodeNetwork*)(this))->target != NULL)
	{
		sprintf(path, "%s/target[%s]", parent, /*((NodeNetwork*)(this))->target->super->super->name*/((NodeNetwork*)(this))->target->InternalGetKey(((NodeNetwork*)(this))->target));
		((NodeNetwork*)(this))->target->VisitAttributes(((NodeNetwork*)(this))->target, path, visitor);
		((NodeNetwork*)(this))->target->VisitReferences(((NodeNetwork*)(this))->target, path, visitor);
	}
	
	if(((NodeNetwork*)(this))->initBy != NULL)
	{
		sprintf(path, "%s/initBy[%s]", parent, /*((NodeNetwork*)(this))->initBy->super->super->name*/((NodeNetwork*)(this))->initBy->InternalGetKey(((NodeNetwork*)(this))->initBy));
		((NodeNetwork*)(this))->initBy->VisitAttributes(((NodeNetwork*)(this))->initBy, path, visitor);
		((NodeNetwork*)(this))->initBy->VisitReferences(((NodeNetwork*)(this))->initBy, path, visitor);
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

/*int _acceptNodeNetwork(NodeNetwork* this, NodeNetwork* c, Visitor* visitor)
{
	int i;
	
	for(i = 0; i < this->count_links; i++)
	{
		visitor->action((void*)this->links, (void*)c->links, 0);
	}
	
	visitor->action((void*)this->initBy, (void*)c->initBy, 0);
	visitor->action((void*)this->target, (void*)c->target, 0);
}*/