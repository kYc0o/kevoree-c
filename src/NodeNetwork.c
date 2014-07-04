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

	sprintf(path,"%s/%s",parent, ((NodeNetwork*)(this))->generated_KMF_ID);

	sprintf(path,"%s\\ID",parent);
	visitor->action(path, STRING, ((NodeNetwork*)(this))->generated_KMF_ID);
}
void NodeNetwork_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	if(((NodeNetwork*)(this))->target != NULL)
	{
		sprintf(path, "%s/target[%s]", parent, ((NodeNetwork*)(this))->target->super->super->name);
		((NodeNetwork*)(this))->target->VisitAttributes(((NodeNetwork*)(this))->target, parent, visitor);
	}
	
	if(((NodeNetwork*)(this))->initBy != NULL)
	{
		sprintf(path, "%s/initBy[%s]", parent, ((NodeNetwork*)(this))->initBy->super->super->name);
		((NodeNetwork*)(this))->initBy->VisitAttributes(((NodeNetwork*)(this))->initBy, parent, visitor);
	}
	
	if(((NodeNetwork*)(this))->link != NULL)
	{
		int i;
		
		sprintf(path,"%s/link[%s]", parent, ((NodeNetwork*)(this))->generated_KMF_ID);
		
		/* link */
		hashmap_map* m = ((NodeNetwork*)(this))->link;

		/* compare link */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NodeLink* n = data;
				n->VisitAttributes(n, parent, visitor);
				n->VisitReferences(n, parent, visitor);
			}
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