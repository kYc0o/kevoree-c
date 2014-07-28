#include "ContainerRoot.h"

int result;

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
	
	pObj->generated_KMF_ID = malloc(sizeof(char) * 8 + 1);
	rand_str(pObj->generated_KMF_ID, 8);

	/*pObj->generated_KMF_ID = malloc(sizeof(char) * (strlen("dummyKMFID_ContainerRoot") + 1));
	strcpy(pObj->generated_KMF_ID, "dummyKMFID_ContainerRoot");*/
	pObj->nodes = NULL;
	pObj->typeDefinitions = NULL;
	pObj->repositories = NULL;
	pObj->dataTypes = NULL;
	pObj->libraries = NULL;
	/*pObj->hubs = NULL;
	pObj->mBindings = NULL;*/
	pObj->deployUnits = NULL;
	pObj->nodeNetworks = NULL;
	pObj->groups = NULL;
	
	
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
	pObj->Visit = ContainerRoot_Visit;
	pObj->FindByPath = ContainerRoot_FindByPath;
	
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

	if(this->nodes != NULL)
	{
		if(hashmap_get(this->nodes, id, (void**)(&value)) == MAP_OK)
		{
			return value;
		}
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

TypeDefinition* ContainerRoot_FindTypeDefsByID(ContainerRoot* const this, char* id)
{
	TypeDefinition* value;

	if(this->typeDefinitions != NULL)
	{
		if(hashmap_get(this->typeDefinitions, id, (void**)(&value)) == MAP_OK)
		{
			return value;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

Repository* ContainerRoot_FindRepositoriesByID(ContainerRoot* const this, char* id)
{
	Repository* value;

	if(this->repositories != NULL)
	{
		if(hashmap_get(this->repositories, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

TypedElement* ContainerRoot_FindDataTypesByID(ContainerRoot* const this, char* id)
{
	TypedElement* value;

	if(this->dataTypes != NULL)
	{
		if(hashmap_get(this->dataTypes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

TypeLibrary* ContainerRoot_FindLibrariesByID(ContainerRoot* const this, char* id)
{
	TypeLibrary* value;

	if(this->libraries != NULL)
	{
		if(hashmap_get(this->libraries, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
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

	if(this->deployUnits != NULL)
	{
		if(hashmap_get(this->deployUnits, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

NodeNetwork* ContainerRoot_FindNodeNetworksByID(ContainerRoot* const this, char* id)
{
	NodeNetwork* value;

	if(this->nodeNetworks != NULL)
	{
		if(hashmap_get(this->nodeNetworks, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

Group* ContainerRoot_FindGroupsByID(ContainerRoot* const this, char* id)
{
	Group* value;

	if(this->groups != NULL)
	{
		if(hashmap_get(this->groups, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
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
		if(this->nodes == NULL)
		{
			this->nodes = hashmap_new();
		}
		if(hashmap_get(this->nodes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (ContainerNode*)ptr;
			result = hashmap_put(this->nodes, container->InternalGetKey(container), ptr);
			/*printf("ContainerNode %s added to ContainerRoot %s Result: %d \n", ptr->super->super->name, this->generated_KMF_ID, result);*/
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
		if(this->typeDefinitions == NULL)
		{
			this->typeDefinitions = hashmap_new();
		}
		if(hashmap_get(this->typeDefinitions, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (TypeDefinition*)ptr;
			result = hashmap_put(this->typeDefinitions, container->InternalGetKey(container), ptr);
			/*printf("TypeDefinition %s added to ContainerRoot %s Result: %d\n", ptr->super->name, this->generated_KMF_ID, result);*/
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
		if(this->repositories == NULL)
		{
			this->repositories = hashmap_new();
		}
		if(hashmap_get(this->repositories, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (Repository*)ptr;
			result = hashmap_put(this->repositories, container->InternalGetKey(container), ptr);
			/*printf("Repository %s added to ContainerRoot %s Result: %d\n", ptr->url, this->generated_KMF_ID, result);*/
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
		if(this->dataTypes == NULL)
		{
			this->dataTypes = hashmap_new();
		}
		if(hashmap_get(this->dataTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (TypedElement*)ptr;
			hashmap_put(this->dataTypes, container->InternalGetKey(container), ptr);
			/*printf("TypedElement %s added to ContainerRoot %s Result: %d\n", ptr->super->name, this->generated_KMF_ID, result);*/
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
		if(this->libraries == NULL)
		{
			this->libraries = hashmap_new();
		}
		if(hashmap_get(this->libraries, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (TypeLibrary*)ptr;
			hashmap_put(this->libraries, container->InternalGetKey(container), ptr);
			/*printf("TypeLibrary %s added to ContainerRoot %s Result: %d\n", ptr->super->name, this->generated_KMF_ID, result);*/
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
		if(this->hubs == NULL)
		{
			this->hubs = hashmap_new();
		}
		if(hashmap_get(this->hubs, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (Channel*)ptr;
			hashmap_put(this->hubs, container->InternalGetKey(container), ptr);
			printf("Channel %s added to ContainerRoot %s\n", ptr->super->super->name, this->generated_KMF_ID);
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
		if(this->mBindings == NULL)
		{
			this->mBindings = hashmap_new();
		}
		if(hashmap_get(this->mBindings, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (MBinding*)ptr;
			hashmap_put(this->mBindings, container->InternalGetKey(container), ptr);
			printf("TypeDefinition %s added to ContainerRoot %s\n", ptr->generated_KMF_ID, this->generated_KMF_ID);
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
		if(this->deployUnits == NULL)
		{
			this->deployUnits = hashmap_new();
		}
		if(hashmap_get(this->deployUnits, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (DeployUnit*)ptr;
			result = hashmap_put(this->deployUnits, container->InternalGetKey(container), ptr);
			/*printf("DeployUnit %s added to ContainerRoot %s Result: %d\n", ptr->super->name, this->generated_KMF_ID, result);*/
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
		if(this->nodeNetworks == NULL)
		{
			this->nodeNetworks = hashmap_new();
		}
		if(hashmap_get(this->nodeNetworks, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (NodeNetwork*)ptr;
			result = hashmap_put(this->nodeNetworks, container->InternalGetKey(container), ptr);
			/*printf("NodeNetwork %s added to ContainerRoot %s Result: %d\n", ptr->generated_KMF_ID, this->generated_KMF_ID, result);*/
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
		if(this->groups == NULL)
		{
			this->groups = hashmap_new();
		}
		if(hashmap_get(this->groups, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (Group*)ptr;
			result = hashmap_put(this->groups, container->InternalGetKey(container), ptr);
			/*printf("Group %s added to ContainerRoot %s Result: %d\n", ptr->super->super->name, this->generated_KMF_ID, result);*/
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

void ContainerRoot_Visit(void* const this, Visitor* visitor)
{
	int i;

	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	sprintf(path, "%s\\generated_KMF_ID", ((ContainerRoot*)(this))->generated_KMF_ID);
	visitor->action(path, STRING, ((ContainerRoot*)(this))->generated_KMF_ID);

	hashmap_map* m = NULL;
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->nodes) != NULL)
	{
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				sprintf(path, "nodes[%s]", /*n->super->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->typeDefinitions) != NULL)
	{
		
		/* compare typeDefinitions*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path, "typeDefinitions[%s]", /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->repositories) != NULL)
		/* compare repositories*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Repository* n = data;
				sprintf(path, "repositories[%s]", /*n->url*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitAttributes(n, path, visitor);
			}
		}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->dataTypes) != NULL)
		/* compare dataTypes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypedElement* n = data;
				sprintf(path, "dataTypes[%s]", /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->libraries) != NULL)
		/* compare libraries*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeLibrary* n = data;
				sprintf(path, "libraries[%s]", /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->deployUnits) != NULL)
		/* compare deployUnits*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path, "deployUnits[%s]", /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->nodeNetworks) != NULL)
		/* compare nodeNetworks*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NodeNetwork* n = data;
				sprintf(path, "nodeNetworks[%s]", /*n->generated_KMF_ID*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitAttributes(n, path, visitor);
			}
		}
	
	if((m = (hashmap_map*) ((ContainerRoot*)(this))->groups) != NULL)
		/* compare groups*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				sprintf(path, "groups[%s]", /*n->super->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
}

void* ContainerRoot_FindByPath(char* _path, ContainerRoot* const this)
{
	/*printf("CONTAINER ROOT\n\n");*/
	/* ContainerRoot attributes */
	char* root = strdup(_path);
	char* root2 = strtok(root, "\\");
	/*printf("Root: %s\n", root);*/
	if(!strcmp(this->generated_KMF_ID, root))
	{
		return this->generated_KMF_ID;
	}
	/* ContainerRoot references */
	else
	{
		char* path = strdup(_path);
		char* pch;
		char* attribute = NULL;/*strtok(path, "\\");*/
		
		/*attribute = strtok(NULL, "\\");*/

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path, "/");
			/*printf("pch: %s\n", pch);*/
			if(strchr(_path,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(_path,'\\')-_path+1);*/
				attribute = strtok(NULL, "\\");
				sprintf(attribute, "%s\\%s", attribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not present in path\n");*/
				attribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			attribute = strtok(pch, "\\");
			attribute = strtok(NULL, "\\");
		}
		
		/*printf("Token: %s\n", pch);*/

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		/*printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("attribute: %s\n", attribute);*/
		
		if(!strcmp("nodes", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindNodesByID(this, queryID);
			}
			else
			{
				ContainerNode* node = this->FindNodesByID(this, queryID);
				if(node != NULL)
					return node->FindByPath(attribute, node);
				else
					return NULL;
			}
		}	
		else if(!strcmp("typeDefinitions", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindTypeDefsByID(this, queryID);
			}
			else
			{
				TypeDefinition* typDef = this->FindTypeDefsByID(this, queryID);
				if(typDef != NULL)
					return typDef->FindByPath(attribute, typDef);
				else
					return NULL;
			}
		}
		else if(!strcmp("repositories", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindRepositoriesByID(this, queryID);
			}
			else
			{
				Repository* repo = this->FindRepositoriesByID(this, queryID);
				if(repo != NULL)
					return repo->FindByPath(attribute, repo);
				else
					return NULL;
			}
		}
		else if(!strcmp("dataTypes", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindDataTypesByID(this, queryID);
			}
			else
			{
				TypedElement* typel = this->FindDataTypesByID(this, queryID);
				if(typel != NULL)
					return typel->FindByPath(attribute, typel);
				else
					return NULL;
			}
		}
		else if(!strcmp("libraries", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindLibrariesByID(this, queryID);
			}
			else
			{
				TypeLibrary* typlib = this->FindLibrariesByID(this, queryID);
				if(typlib != NULL)
					return typlib->FindByPath(attribute, typlib);
				else
					return NULL;
			}
		}
		else if(!strcmp("deployUnits", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindDeployUnitsByID(this, queryID);
			}
			else
			{
				DeployUnit* depunit = this->FindDeployUnitsByID(this, queryID);
				if(depunit != NULL)
					return depunit->FindByPath(attribute, depunit);
				else
					return NULL;
			}
		}
		else if(!strcmp("nodeNetworks", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindNodeNetworksByID(this, queryID);
			}
			else
			{
				NodeNetwork* nodenet = this->FindNodeNetworksByID(this, queryID);
				if(nodenet != NULL)
					return nodenet->FindByPath(attribute, nodenet);
				else
					return NULL;
			}
		}
		else if(!strcmp("groups", relationName))
		{
			if(attribute == NULL)
			{
				return this->FindGroupsByID(this, queryID);
			}
			else
			{
				Group* group = this->FindGroupsByID(this, queryID);
				if(group != NULL)
					return group->FindByPath(attribute, group);
				else
					return NULL;
			}
		}
		else
		{
			printf("Path %s does not exist in this model...\n\n", _path);
			return NULL;
		}
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