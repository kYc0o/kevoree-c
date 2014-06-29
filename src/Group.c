#include "Group.h"

Instance* newPoly_Group()
{
	Group* pGroupObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pGroupObj = (Group*)malloc(sizeof(Group));

	if (pGroupObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pGroupObj; /* Pointing to derived object */
	
	/*pGroupObj->subNodes = hashmap_new();*/
	pGroupObj->subNodes = NULL;;
	
	pGroupObj->AddSubNodes = Group_AddSubNodes;
	pGroupObj->RemoveSubNodes = Group_RemoveSubNodes;
	
	pObj->InternalGetKey = Group_InternalGetKey;
	pObj->MetaClassName = Group_MetaClassName;
	pObj->VisitAttributes = Group_VisitAttributes;
	pObj->VisitReferences = Group_VisitReferences;
	
	pObj->Delete = deletePoly_Group;

	return pObj;
}

Group* new_Group()
{
	Group* pGroupObj = NULL;
	Instance* pObj = new_Instance();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pGroupObj = (Group*)malloc(sizeof(Group));

	if (pGroupObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pGroupObj; Pointing to derived object */
	pGroupObj->super = pObj;
	
	/*pGroupObj->subNodes = hashmap_new();*/
	pGroupObj->subNodes = NULL;
	
	pGroupObj->AddSubNodes = Group_AddSubNodes;
	pGroupObj->RemoveSubNodes = Group_RemoveSubNodes;
	
	pGroupObj->InternalGetKey = Group_InternalGetKey;
	pGroupObj->MetaClassName = Group_MetaClassName;
	pGroupObj->VisitAttributes = Group_VisitAttributes;
	pGroupObj->VisitReferences = Group_VisitReferences;
	pGroupObj->Delete = delete_Group;

	return pGroupObj;
}

char* Group_InternalGetKey(Group* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->super->name);

	return internalKey;
}

char* Group_MetaClassName(Group* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("Group") + 1));
	strcpy(name, "Group");
	
	return name;
}

/*void Group::addsubNodes(ContainerNode *ptr)*/
void Group_AddSubNodes(Group* const this, ContainerNode* ptr)
{
	ContainerNode* container = (ContainerNode*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be added in Group because the key is not defined");*/
		printf("The ContainerNode cannot be added in Group because the key is not defined\n");
	}
	else
	{
		/*if(subNodes.find(container->internalGetKey()) == subNodes.end())*/
		if(this->subNodes == NULL)
		{
			this->subNodes = hashmap_new();
		}
		if(hashmap_get(this->subNodes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*subNodes[container->internalGetKey()]=ptr;*/
			container = (ContainerNode*)ptr;
			hashmap_put(this->subNodes, container->InternalGetKey(container), ptr);
		}
	}
}

/*void Group::removesubNodes(ContainerNode *ptr)*/
void Group_RemoveSubNodes(Group* const this, ContainerNode* ptr)
{
	ContainerNode* container = (ContainerNode*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be removed in Group because the key is not defined");*/
		printf("The ContainerNode cannot be removed in Group because the key is not defined\n");
	}
	else
	{
		/*subNodes.erase( subNodes.find(container->internalGetKey()));*/
		hashmap_remove(this->subNodes, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_Group(Instance* const this)
{
	Group* pGroupObj;
	pGroupObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pGroupObj->subNodes);
	free(pGroupObj);
	/*destroy base Obj*/
	delete_Instance(this);
}

void delete_Group(Group* const this)
{
	/* destroy base object */
	delete_Instance(this->super);
	/* destroy data memebers */
	hashmap_free(this->subNodes);
	free(this);
}

void Group_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	sprintf(path, "%s/%s", parent, ((Group*)(this))->super->super->name);

	sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((Group*)(this))->super->super->name);
}

void Group_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));
	
	if(((Group*)(this))->subNodes != NULL)
	{
		int i;
		
		sprintf(path,"%s/subNodes[%s]", parent, ((Group*)(this))->super->super->name);
		
		/* subNodes */
		hashmap_map* m = ((Group*)(this))->subNodes;

		/* compare subNodes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				n->VisitAttributes(n, parent, visitor);
				/*n->VisitReferences(n, parent, visitor);*/
			}
		}
	}
}

/*int _acceptGroup(Group* this, Group* c, Visitor* visitor)
{
	int i;

	for(i = 0; i < this->count_subNodes; i++)
	{
		visitor->action((void*)this->subNodes, (void*)c->subNodes, 0);
	}
}*/
