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
	
	pObj->InternalGetKey = Group_InternalGetKey;
	pObj->MetaClassName = Group_MetaClassName;
	
	/*pGroupObj->subNodes = hashmap_new();*/
	pGroupObj->subNodes = NULL;;
	
	pGroupObj->AddSubNodes = Group_AddSubNodes;
	pGroupObj->RemoveSubNodes = Group_RemoveSubNodes;
	
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
	
	pGroupObj->InternalGetKey = Group_InternalGetKey;
	pGroupObj->MetaClassName = Group_MetaClassName;
	
	/*pGroupObj->subNodes = hashmap_new();*/
	pGroupObj->subNodes = NULL;
	
	pGroupObj->AddSubNodes = Group_AddSubNodes;
	pGroupObj->RemoveSubNodes = Group_RemoveSubNodes;
	
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

/*int _acceptGroup(Group* this, Group* c, Visitor* visitor)
{
	int i;

	for(i = 0; i < this->count_subNodes; i++)
	{
		visitor->action((void*)this->subNodes, (void*)c->subNodes, 0);
	}
}*/
