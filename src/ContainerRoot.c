#include "ContainerRoot.h"

ContainerRoot* new_ContainerRoot(void)
{
	ContainerRoot* pObj;
	/* Allocating memory */
	pObj = (ContainerRoot*)malloc(sizeof(ContainerRoot));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;

	/*pObj->generated_KMF_ID = Uuid::getSingleton().generateUUID();*/
	pObj->nodes = hashmap_new();
	pObj->typeDefinitions = hashmap_new();
	pObj->repositories = hashmap_new();
	pObj->dataTypes = hashmap_new();
	pObj->libraries = hashmap_new();
	/*pObj->hubs = hashmap_new();
	pObj->mBindings = hashmap_new();*/
	pObj->deployUnits = hashmap_new();
	pObj->nodeNetworks = hashmap_new();
	pObj->groups = hashmap_new();
	
	pObj->InternalGetKey = ContainerRoot_InternalGetKey;
	pObj->MetaClassName = ContainerRoot_MetaClassName;
	pObj->FindNodesByID = ContainerRoot_FindNodesByID;
	pObj->FindTypeDefsByID = ContainerRoot_FindTypeDefsByID;
	pObj->FindRepositoriesByID = ContainerRoot_FindRepositoriesByID;
	pObj->FindDataTypesByID = ContainerRoot_FindDataTypesByID;
	pObj->FindLibrariesByID = ContainerRoot_FindLibrariesByID;
	/*pObj->FindHubsByID = ContainerRoot_FindHubsByID;
	pObj->FindBindingsByID = ContainerRoot_FindBndingsByID;*/
	pObj->FindDeployUnitsByID = ContainerRoot_FindDeployUnitsByID;
	pObj->FindNodeNetworksByID = ContainerRoot_FindNodeNetworksByID;
	pObj->FindGroupsByID = ContainerRoot_FindGroupsByID;
	pObj->AddNodes = ContainerRoot_AddNodes;
	pObj->AddTypeDefinitions = ContainerRoot_AddTypeDefinitions;
	pObj->AddRepositories = ContainerRoot_AddRepositories;
	pObj->AddDataTypes = ContainerRoot_AddDataTypes;
	pObj->AddLibraries = ContainerRoot_AddLibraries;
	/*pObj->AddHubs = ContainerRoot_AddHubs;
	pObj->AddBindings = ContainerRoot_AddBindings*/
	pObj->AddDeployUnits = ContainerRoot_AddDeployUnits;
	pObj->AddNodeNetworks = ContainerRoot_AddNodeNetworks;
	pObj->AddGroups = ContainerRoot_AddGroups;
	pObj->RemoveNodes = ContainerRoot_RemoveNodes;
	pObj->RemoveTypeDefinitions = ContainerRoot_RemoveTypeDefinitions;
	pObj->RemoveRepositories = ContainerRoot_RemoveRepositories;
	pObj->RemoveDataTypes = ContainerRoot_RemoveDataTypes;
	pObj->RemoveLibraries = ContainerRoot_RemoveLibraries;
	/*pObj->RemoveHubs = ContainerRoot_RemoveHubs;
	pObj->RemoveBindings = ContainerRoot_RemoveBindings;*/
	pObj->RemoveDeployUnits = ContainerRoot_RemoveDeployUnits;
	pObj->RemoveNodeNetworks = ContainerRoot_RemoveNodeNetworks;
	pObj->RemoveGroups = ContainerRoot_RemoveGroups;
	pObj->Delete = delete_ContainerRoot;
	
	return pObj;
}

char* ContainerRoot_MetaClassName(ContainerRoot* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("ContainerRoot") + 1));
	strcpy(name, "ContainerRoot");
	
	return name;
}

char* ContainerRoot_InternalGetKey(ContainerRoot* const this)
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

ContainerNode* ContainerRoot_FindNodesByID(ContainerRoot* const this, char* id)
{
	ContainerNode* value;

	if(hashmap_get(this->nodes, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

TypeDefinition* ContainerRoot_FindTypeDefsByID(ContainerRoot* const this, char* id)
{
	TypeDefinition* value;

	if(hashmap_get(this->typeDefinitions, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

Repository* ContainerRoot_FindRepositoriesByID(ContainerRoot* const this, char* id)
{
	Repository* value;

	if(hashmap_get(this->repositories, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

TypedElement* ContainerRoot_FindDataTypesByID(ContainerRoot* const this, char* id)
{
	TypedElement* value;

	if(hashmap_get(this->dataTypes, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

TypeLibrary* ContainerRoot_FindLibrariesByID(ContainerRoot* const this, char* id)
{
	TypeLibrary* value;

	if(hashmap_get(this->libraries, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

/*Channel* ContainerRoot_FindHubsByID(ContainerRoot* const this, char* id)
 * {
 * 	Channel* value;

	if(hashmap_get(this->hubs, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
 * }

MBinding* ContainerRoot_FindBndingsByID(ContainerRoot* const this, char* id)
{
	MBinding* value;

	if(hashmap_get(this->mBindings, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}
*/

DeployUnit* ContainerRoot_FindDeployUnitsByID(ContainerRoot* const this, char* id)
{
	DeployUnit* value;

	if(hashmap_get(this->deployUnits, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

NodeNetwork* ContainerRoot_FindNodeNetworksByID(ContainerRoot* const this, char* id)
{
	NodeNetwork* value;

	if(hashmap_get(this->nodeNetworks, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

Group* ContainerRoot_FindGroupsByID(ContainerRoot* const this, char* id)
{
	Group* value;

	if(hashmap_get(this->groups, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void ContainerRoot_AddNodes(ContainerRoot* const this, ContainerNode* ptr)
{
	ContainerNode* container = (ContainerNode*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The ContainerNode cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->nodes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->nodes, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_AddTypeDefinitions(ContainerRoot* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypeDefinition cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->typeDefinitions, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->typeDefinitions, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_AddRepositories(ContainerRoot* const this, Repository* ptr)
{
	Repository* container = (Repository*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The Repository cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->repositories, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->repositories, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_AddDataTypes(ContainerRoot* const this, TypedElement* ptr)
{
	TypedElement* container = (TypedElement*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypedElement cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->dataTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->dataTypes, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_AddLibraries(ContainerRoot* const this, TypeLibrary* ptr)
{
	TypeLibrary* container = (TypeLibrary*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypeLibrary cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->libraries, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->libraries, container->InternalGetKey(container), ptr);
		}
	}
}
/*void ContainerRoot_AddHubs(ContainerRoot* const this, Channel* ptr)
 * {
 * 	Channel* container = (Channel*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The Channel cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->hubs, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->hubs, container->InternalGetKey(container), ptr);
		}
	}
 * }
void ContainerRoot_AddBindings(ContainerRoot* const this, MBinding* ptr)
{
	MBinding* container = (MBinding*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The MBinding cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->mBindings, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->mBindings, container->InternalGetKey(container), ptr);
		}
	}
}*/

void ContainerRoot_AddDeployUnits(ContainerRoot* const this, DeployUnit* ptr)
{
	DeployUnit* container = (DeployUnit*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The DeployUnit cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->deployUnits, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->deployUnits, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_AddNodeNetworks(ContainerRoot* const this, NodeNetwork* ptr)
{
	NodeNetwork* container = (NodeNetwork*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The NodeNetwork cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->nodeNetworks, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->nodeNetworks, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_AddGroups(ContainerRoot* const this, Group* ptr)
{
	Group* container = (Group*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The Group cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_get(this->groups, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			hashmap_put(this->groups, container->InternalGetKey(container), ptr);
		}
	}
}

void ContainerRoot_RemoveNodes(ContainerRoot* const this, ContainerNode* ptr)
{
	ContainerNode* container = (ContainerNode*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The ContainerNode cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->nodes, container->InternalGetKey(container));
	}
}

void ContainerRoot_RemoveTypeDefinitions(ContainerRoot* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypeDefinition cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->nodes, container->InternalGetKey(container));
	}
}

void ContainerRoot_RemoveRepositories(ContainerRoot* const this, Repository* ptr)
{
	Repository* container = (Repository*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The Repository cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->repositories, container->InternalGetKey(container));
	}
}
void ContainerRoot_RemoveDataTypes(ContainerRoot* const this, TypedElement* ptr)
{
	TypedElement* container = (TypedElement*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypedElement cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->dataTypes, container->InternalGetKey(container));
	}
}

void ContainerRoot_RemoveLibraries(ContainerRoot* const this, TypeLibrary* ptr)
{
	TypeLibrary* container = (TypeLibrary*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypeLibrary cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->libraries, container->InternalGetKey(container));
	}
}

/*void ContainerRoot_RemoveHubs(ContainerRoot* const this, Channel* ptr)
 * {
 * 	Channel* container = (Channel*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The Channel cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->hubs, container->InternalGetKey(container));
	}
 * }
 
void ContainerRoot_RemoveBindings(ContainerRoot* const this, MBinding* ptr)
{
	MBinding* container = (MBinding*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The MBinding cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->mBindings, container->InternalGetKey(container));
	}
}*/

void ContainerRoot_RemoveDeployUnits(ContainerRoot* const this,  DeployUnit* ptr)
{
	DeployUnit* container = (DeployUnit*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The DeployUnit cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->deployUnits, container->InternalGetKey(container));
	}
}

void ContainerRoot_RemoveNodeNetworks(ContainerRoot* const this, NodeNetwork* ptr)
{
	NodeNetwork* container = (NodeNetwork*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The NodeNetwork cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->nodeNetworks, container->InternalGetKey(container));
	}
}

void ContainerRoot_RemoveGroups(ContainerRoot* const this, Group* ptr)
{
	Group* container = (Group*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The Group cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->groups, container->InternalGetKey(container));
	}
}

void delete_ContainerRoot(ContainerRoot* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->generated_KMF_ID);
		hashmap_free(this->nodes);
		hashmap_free(this->typeDefinitions);
		hashmap_free(this->repositories);
		hashmap_free(this->dataTypes);
		hashmap_free(this->libraries);
		/*hashmap_free(this->hubs);
		hashmap_free(this->mBindings);*/
		hashmap_free(this->deployUnits);
		hashmap_free(this->nodeNetworks);
		hashmap_free(this->groups);
		free(this);
	}
}

/*int _acceptContainerRoot(ContainerRoot* this, ContainerRoot* c, Visitor* visitor)
{
	int i;

	for(i = 0; i < this->count_groups; i++)
	{
		visitor->action((void*)this->groups, (void*)c->groups, 0);
	}

	for(i = 0; i < this->count_nodes; i++)
	{
		visitor->action((void*)this->nodes, (void*)c->nodes, 0);
	}

	for(i = 0; i < this->count_nodeNetworks; i++)
	{
		visitor->action((void*)this->nodeNetworks, (void*)c->nodeNetworks, 0);
	}

	for(i = 0; i < this->count_typedefintions; i++)
	{
		visitor->action((void*)this->typedefintions, (void*)c->typedefintions, 0);
	}
	
	for(i = 0; i < this->count_deployUnits; i++)
	{
		visitor->action((void*)this->deployUnits, (void*)c->deployUnits, 0);
	}
}*/