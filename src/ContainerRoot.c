#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "kevoree.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

ContainerRoot* new_ContainerRoot()
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

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);

	pObj->eContainer = "";
	pObj->path = "";
	pObj->nodes = NULL;
	pObj->typeDefinitions = NULL;
	pObj->repositories = NULL;
	pObj->dataTypes = NULL;
	pObj->libraries = NULL;
	pObj->hubs = NULL;
	pObj->mBindings = NULL;
	pObj->deployUnits = NULL;
	pObj->nodeNetworks = NULL;
	pObj->groups = NULL;


	pObj->internalGetKey = ContainerRoot_internalGetKey;
	pObj->metaClassName = ContainerRoot_metaClassName;
	pObj->Delete = delete_ContainerRoot;
	pObj->Visit = ContainerRoot_Visit;
	pObj->VisitPaths = ContainerRoot_VisitPaths;
	pObj->FindByPath = ContainerRoot_FindByPath;

	pObj->FindNodesByID = ContainerRoot_FindNodesByID;
	pObj->FindTypeDefsByID = ContainerRoot_FindTypeDefsByID;
	pObj->FindRepositoriesByID = ContainerRoot_FindRepositoriesByID;
	pObj->FindDataTypesByID = ContainerRoot_FindDataTypesByID;
	pObj->FindLibrariesByID = ContainerRoot_FindLibrariesByID;
	pObj->FindHubsByID = ContainerRoot_FindHubsByID;
	pObj->FindBindingsByID = ContainerRoot_FindBndingsByID;
	pObj->FindDeployUnitsByID = ContainerRoot_FindDeployUnitsByID;
	pObj->FindNodeNetworksByID = ContainerRoot_FindNodeNetworksByID;
	pObj->FindGroupsByID = ContainerRoot_FindGroupsByID;
	pObj->AddNodes = ContainerRoot_AddNodes;
	pObj->AddTypeDefinitions = ContainerRoot_AddTypeDefinitions;
	pObj->AddRepositories = ContainerRoot_AddRepositories;
	pObj->AddDataTypes = ContainerRoot_AddDataTypes;
	pObj->AddLibraries = ContainerRoot_AddLibraries;
	pObj->AddHubs = ContainerRoot_AddHubs;
	pObj->AddBindings = ContainerRoot_AddBindings;
	pObj->AddDeployUnits = ContainerRoot_AddDeployUnits;
	pObj->AddNodeNetworks = ContainerRoot_AddNodeNetworks;
	pObj->AddGroups = ContainerRoot_AddGroups;
	pObj->RemoveNodes = ContainerRoot_RemoveNodes;
	pObj->RemoveTypeDefinitions = ContainerRoot_RemoveTypeDefinitions;
	pObj->RemoveRepositories = ContainerRoot_RemoveRepositories;
	pObj->RemoveDataTypes = ContainerRoot_RemoveDataTypes;
	pObj->RemoveLibraries = ContainerRoot_RemoveLibraries;
	pObj->RemoveHubs = ContainerRoot_RemoveHubs;
	pObj->RemoveBindings = ContainerRoot_RemoveBindings;
	pObj->RemoveDeployUnits = ContainerRoot_RemoveDeployUnits;
	pObj->RemoveNodeNetworks = ContainerRoot_RemoveNodeNetworks;
	pObj->RemoveGroups = ContainerRoot_RemoveGroups;

	return pObj;
}

char* ContainerRoot_metaClassName(void* const this)
{
	/*ContainerRoot *pObj = (ContainerRoot*)this;
	char *name;

	name = malloc(sizeof(char) * (strlen("ContainerRoot")) + 1);
	if(name != NULL)
		strcpy(name, "ContainerRoot");
	else
		return NULL;

	return name;
	*/
	return "ContainerRoot";
}

char* ContainerRoot_internalGetKey(void* const this)
{
	if(this == NULL)
		return NULL;

	ContainerRoot *pObj = (ContainerRoot*)this;

	return pObj->generated_KMF_ID;
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
	TypeDefinition* value = NULL;

	if(this->typeDefinitions != NULL)
	{
		if(hashmap_get(this->typeDefinitions, id, (void**)(&value)) == MAP_OK)
		{
			PRINTF("DEBUG: typeDefinition found!\n");
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
	Repository* value = NULL;

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
	TypedElement* value = NULL;

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
	TypeLibrary* value = NULL;

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

Channel* ContainerRoot_FindHubsByID(ContainerRoot* const this, char* id)
{
	Channel* value = NULL;

	if(this->hubs != NULL)
	{
		if(hashmap_get(this->hubs, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

MBinding* ContainerRoot_FindBndingsByID(ContainerRoot* const this, char* id)
{
	MBinding* value = NULL;

	if(this->mBindings != NULL)
	{
		if(hashmap_get(this->mBindings, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

DeployUnit* ContainerRoot_FindDeployUnitsByID(ContainerRoot* const this, char* id)
{
	DeployUnit* value = NULL;

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
	NodeNetwork* value = NULL;

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
	Group* value = NULL;

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
	ContainerNode* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ContainerNode cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->nodes == NULL)
		{
			this->nodes = hashmap_new();
		}
		if(hashmap_get(this->nodes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (ContainerNode*)ptr;*/
			if(hashmap_put(this->nodes, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("nodes[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "nodes[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddTypeDefinitions(ContainerRoot* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->typeDefinitions == NULL)
		{
			this->typeDefinitions = hashmap_new();
		}
		if(hashmap_get(this->typeDefinitions, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypeDefinition*)ptr;*/
			if(hashmap_put(this->typeDefinitions, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("typeDefinitions[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "typeDefinitions[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddRepositories(ContainerRoot* const this, Repository* ptr)
{
	Repository* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Repository cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->repositories == NULL)
		{
			this->repositories = hashmap_new();
		}
		if(hashmap_get(this->repositories, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (Repository*)ptr;*/
			if(hashmap_put(this->repositories, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("repositories[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "repositories[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddDataTypes(ContainerRoot* const this, TypedElement* ptr)
{
	TypedElement* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypedElement cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->dataTypes == NULL)
		{
			this->dataTypes = hashmap_new();
		}
		if(hashmap_get(this->dataTypes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypedElement*)ptr;*/
			if(hashmap_put(this->dataTypes, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("dataTypes[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "dataTypes[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddLibraries(ContainerRoot* const this, TypeLibrary* ptr)
{
	TypeLibrary* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeLibrary cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->libraries == NULL)
		{
			this->libraries = hashmap_new();
		}
		if(hashmap_get(this->libraries, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypeLibrary*)ptr;*/
			if(hashmap_put(this->libraries, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("dataTypes[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "dataTypes[%s]", internalKey);
			}
		}
	}
}
void ContainerRoot_AddHubs(ContainerRoot* const this, Channel* ptr)
{
	Channel* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Channel cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->hubs == NULL)
		{
			this->hubs = hashmap_new();
		}
		if(hashmap_get(this->hubs, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (Channel*)ptr;*/
			if(hashmap_put(this->hubs, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("hubs[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "hubs[%s]", internalKey);
			}
		}
	}
}
void ContainerRoot_AddBindings(ContainerRoot* const this, MBinding* ptr)
{
	MBinding* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The MBinding cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->mBindings == NULL)
		{
			this->mBindings = hashmap_new();
		}
		if(hashmap_get(this->mBindings, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (MBinding*)ptr;*/
			if(hashmap_put(this->mBindings, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("mBindings[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "mBindings[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddDeployUnits(ContainerRoot* const this, DeployUnit* ptr)
{
	DeployUnit* container = NULL;

	char* internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DeployUnit cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->deployUnits == NULL)
		{
			this->deployUnits = hashmap_new();
		}
		if(hashmap_get(this->deployUnits, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (DeployUnit*)ptr;*/
			if(hashmap_put(this->deployUnits, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("deployUnits[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "deployUnits[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddNodeNetworks(ContainerRoot* const this, NodeNetwork* ptr)
{
	NodeNetwork* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NodeNetwork cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->nodeNetworks == NULL)
		{
			this->nodeNetworks = hashmap_new();
		}
		if(hashmap_get(this->nodeNetworks, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (NodeNetwork*)ptr;*/
			if(hashmap_put(this->nodeNetworks, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->path = malloc(sizeof(char) * (strlen("nodeNetworks[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "nodeNetworks[%s]", internalKey);
			}
		}
	}
}

void ContainerRoot_AddGroups(ContainerRoot* const this, Group* ptr)
{
	Group* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Group cannot be added in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(this->groups == NULL)
		{
			this->groups = hashmap_new();
		}
		if(hashmap_get(this->groups, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (Group*)ptr;*/
			if(hashmap_put(this->groups, internalKey, ptr) == MAP_OK) {
				ptr->eContainer = "";
				ptr->super->path = "";
				ptr->path = malloc(sizeof(char) * (strlen("groups[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "groups[%s]", internalKey);
				ptr->super->path = ptr->path;
			}
		}
	}
}

void ContainerRoot_RemoveNodes(ContainerRoot* const this, ContainerNode* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ContainerNode cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->nodes, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveTypeDefinitions(ContainerRoot* const this, TypeDefinition* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->nodes, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveRepositories(ContainerRoot* const this, Repository* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Repository cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->repositories, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;

		}
	}
}
void ContainerRoot_RemoveDataTypes(ContainerRoot* const this, TypedElement* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypedElement cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->dataTypes, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveLibraries(ContainerRoot* const this, TypeLibrary* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeLibrary cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->libraries, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveHubs(ContainerRoot* const this, Channel* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Channel cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->hubs, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveBindings(ContainerRoot* const this, MBinding* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The MBinding cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->mBindings, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveDeployUnits(ContainerRoot* const this,  DeployUnit* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DeployUnit cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->deployUnits, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(internalKey);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveNodeNetworks(ContainerRoot* const this, NodeNetwork* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NodeNetwork cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->nodeNetworks, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerRoot_RemoveGroups(ContainerRoot* const this, Group* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Group cannot be removed in ContainerRoot because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->groups, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void delete_ContainerRoot(void* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		ContainerRoot *pObj = (ContainerRoot*)this;
		free(pObj->generated_KMF_ID);
		/*
		 * TODO Verify NULLity
		 */
		hashmap_free(pObj->nodes);
		hashmap_free(pObj->typeDefinitions);
		hashmap_free(pObj->repositories);
		hashmap_free(pObj->dataTypes);
		hashmap_free(pObj->libraries);
		hashmap_free(pObj->hubs);
		hashmap_free(pObj->mBindings);
		hashmap_free(pObj->deployUnits);
		hashmap_free(pObj->nodeNetworks);
		hashmap_free(pObj->groups);
		free(this);
	}
}

void ContainerRoot_Visit(void* const this, Visitor* visitor)
{
	int i;

	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((ContainerRoot*)this)->metaClassName((ContainerRoot*)this))) + 1);
	sprintf(cClass, "org.kevoree.%s", ((ContainerRoot*)this)->metaClassName((ContainerRoot*)this));
	sprintf(path, "eClass");
	visitor->action(NULL, BRACKET, NULL);
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	/*free(cClass);*/
	free(cClass);

	sprintf(path, "generated_KMF_ID");
	visitor->action(path, STRING, ((ContainerRoot*)(this))->generated_KMF_ID);
	visitor->action(NULL, COLON, NULL);

	hashmap_map* m = NULL;

	int length = hashmap_length(((ContainerRoot*)this)->nodes);

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->nodes) != NULL)
	{
		visitor->action("nodes", SQBRACKET, NULL);
		/* compare nodes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				/*sprintf(path, "nodes[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("nodes", SQBRACKET, NULL);
		visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->typeDefinitions) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->typeDefinitions);

		visitor->action("typeDefinitions", SQBRACKET, NULL);
		/* compare typeDefinitions*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				/*sprintf(path, "typeDefinitions[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("typeDefinitions", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->repositories) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->repositories);

		visitor->action("repositories", SQBRACKET, NULL);
		/* compare repositories*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				Repository* n = data;
				/*sprintf(path, "repositories[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitAttributes(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("repositories", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->dataTypes) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->dataTypes);

		visitor->action("dataTypes", SQBRACKET, NULL);
		/* compare dataTypes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				TypedElement* n = data;
				/*sprintf(path, "dataTypes[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("dataTypes", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->libraries) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->libraries);

		visitor->action("libraries", SQBRACKET, NULL);
		/* compare libraries*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				TypeLibrary* n = data;
				/*sprintf(path, "libraries[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("libraries", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->hubs) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->hubs);

		visitor->action("hubs", SQBRACKET, NULL);
		/* compare hubs */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				Channel* n = data;
				/*sprintf(path, "hubs[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, 1);
				n->VisitReferences(n, path, visitor, 1);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("hubs", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->mBindings) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->mBindings);

		visitor->action("mBindings", SQBRACKET, NULL);
		/* compare mBindings*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				/*sprintf(path, "nodes[%s]/components[%s]", ((ContainerRoot*)(this))->FindNodesByID->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, 1);
				n->VisitReferences(n, path, visitor, 1);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("mBindings", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->deployUnits) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->deployUnits);

		visitor->action("deployUnits", SQBRACKET, NULL);
		/* compare deployUnits*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path, "deployUnits[%s]", n->internalGetKey(n));
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("deployUnits", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->nodeNetworks) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->nodeNetworks);

		visitor->action("nodeNetworks", SQBRACKET, NULL);
		/* compare nodeNetworks*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				NodeNetwork* n = data;
				/*sprintf(path, "nodeNetworks[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitAttributes(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("nodeNetworks", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->groups) != NULL)
	{
		int length = hashmap_length(((ContainerRoot*)this)->groups);

		visitor->action("groups", SQBRACKET, NULL);
		/* compare groups*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				/*sprintf(path, "groups[%s]", n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, 1);
				n->VisitReferences(n, path, visitor, 1);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
	else
	{
		visitor->action("groups", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
	visitor->action(NULL, CLOSEBRACKET, NULL);
}

void ContainerRoot_VisitPaths(void *const this, Visitor *visitor)
{
	int i;

	char path[256];
	/*char *cClass = NULL;*/
	memset(&path[0], 0, sizeof(path));

	/*cClass = ((ContainerRoot*)this)->metaClassName((ContainerRoot*)this);
	sprintf(path, "%s\\cClass", cClass);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path, "\\generated_KMF_ID");
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
				sprintf(path, "nodes[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "nodes")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
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
				sprintf(path, "typeDefinitions[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "typeDefinitions")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->repositories) != NULL)
	{
		/* compare repositories*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Repository* n = data;
				sprintf(path, "repositories[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "repositories")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->dataTypes) != NULL)
	{
		/* compare dataTypes*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypedElement* n = data;
				sprintf(path, "dataTypes[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "dataTypes")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->libraries) != NULL)
	{
		/* compare libraries*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeLibrary* n = data;
				sprintf(path, "libraries[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "libraries")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->hubs) != NULL)
	{
		/* compare hubs */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Channel* n = data;
				sprintf(path, "hubs[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "hubs")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->mBindings) != NULL)
	{
		/* compare mBindings*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				MBinding* n = data;
				sprintf(path, "mBindings[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "mBindings")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->deployUnits) != NULL)
	{
		/* compare deployUnits*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path, "deployUnits[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "deployUnits")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->nodeNetworks) != NULL)
	{
		/* compare nodeNetworks*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NodeNetwork* n = data;
				sprintf(path, "nodeNetworks[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "nodeNetworks")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}

	if((m = (hashmap_map*) ((ContainerRoot*)(this))->groups) != NULL)
	{
		/* compare groups*/
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				sprintf(path, "groups[%s]", n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "groups")) {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, true);
					n->VisitPathReferences(n, path, visitor, true);
				}
			}
		}
	}
}

void *ContainerRoot_FindByPath(char *_path, void *const this)
{
	ContainerRoot *pObj = (ContainerRoot*)this;
	/* ContainerRoot attributes */

	if(!strcmp("", _path))
	{
		return pObj;
		/*return this;*/
	} else if (!strcmp("\\generated_KMF_ID", _path)) {
		return pObj->generated_KMF_ID;
	}
	/* ContainerRoot references */
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
		char *attribute = NULL;

		strcpy(path, _path);

		if(strchr(path, '[') != NULL)
		{
			obj = strdup(strtok(path, "["));
			strcpy(path, _path);
			PRINTF("Object: %s\n", obj);
			strcpy(token, strtok(path, "]"));
			strcpy(path, _path);
			sprintf(token, "%s]", token);
			PRINTF("Token: %s\n", token);
			sscanf(token, "%*[^[][%[^]]", key);
			PRINTF("Key: %s\n", key);

			if((strchr(path, '\\')) != NULL)
			{
				attribute = strtok(NULL, "\\");

				if(strchr(attribute, '['))
				{
					sprintf(nextPath, "%s\\", ++attribute);
					if ((attribute = strtok(NULL, "\\")) != NULL) {
						PRINTF("Attribute: %s\n", attribute);
						sprintf(nextPath, "%s%s", nextPath, attribute);
					}
					PRINTF("Next Path: %s\n", nextPath);
				}
				else
				{
					strcpy(nextPath, attribute);
					PRINTF("Next Path: %s\n", nextPath);
				}
			}
			else
			{
				attribute = strtok(path, "]");
				bool isFirst = true;
				char *fragPath = NULL;
				while ((fragPath = strtok(NULL, "]")) != NULL) {
					PRINTF("Attribute: %s]\n", attribute);
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
					attribute = NULL;
				}
			}
		}
		else
		{
			attribute = strtok(path, "\\");
			attribute = strtok(NULL, "\\");
			PRINTF("Attribute: %s\n", attribute);
		}

		if(!strcmp("nodes", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindNodesByID(pObj, key);
			}
			else
			{
				free(obj);
				ContainerNode* node = pObj->FindNodesByID(pObj, key);
				if(node != NULL)
				{
					return node->FindByPath(nextPath, node);
				}
				else
				{
					return NULL;
				}
			}
		}	
		else if(!strcmp("typeDefinitions", obj))
		{
			if(attribute == NULL)
			{
				PRINTF("DEBUG: found!\n");
				free(obj);
				return pObj->FindTypeDefsByID(pObj, key);
			}
			else
			{
				free(obj);
				TypeDefinition* typDef = pObj->FindTypeDefsByID(pObj, key);
				if (typDef != NULL) {
					PRINTF("DEBUG: found!\n");
					return typDef->FindByPath(nextPath, typDef);
				} else {
					PRINTF("DEBUG: not found...\n");
					return NULL;
				}
			}
		}
		else if(!strcmp("repositories", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindRepositoriesByID(pObj, key);
			}
			else
			{
				free(obj);
				Repository* repo = pObj->FindRepositoriesByID(pObj, key);
				if(repo != NULL)
					return repo->FindByPath(nextPath, repo);
				else
					return NULL;
			}
		}
		else if(!strcmp("dataTypes", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindDataTypesByID(pObj, key);
			}
			else
			{
				free(obj);
				TypedElement* typel = pObj->FindDataTypesByID(pObj, key);
				if(typel != NULL)
					return typel->FindByPath(nextPath, typel);
				else
					return NULL;
			}
		}
		else if(!strcmp("libraries", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindLibrariesByID(pObj, key);
			}
			else
			{
				free(obj);
				TypeLibrary* typlib = pObj->FindLibrariesByID(pObj, key);
				if(typlib != NULL)
					return typlib->FindByPath(nextPath, typlib);
				else
					return NULL;
			}
		}
		else if(!strcmp("deployUnits", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindDeployUnitsByID(pObj, key);
			}
			else
			{
				free(obj);
				DeployUnit* depunit = pObj->FindDeployUnitsByID(pObj, key);
				if(depunit != NULL)
					return depunit->FindByPath(nextPath, depunit);
				else
					return NULL;
			}
		}
		else if(!strcmp("nodeNetworks", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindNodeNetworksByID(pObj, key);
			}
			else
			{
				free(obj);
				NodeNetwork* nodenet = pObj->FindNodeNetworksByID(pObj, key);
				if(nodenet != NULL)
					return nodenet->FindByPath(nextPath, nodenet);
				else
					return NULL;
			}
		}
		else if(!strcmp("groups", obj))
		{
			if(attribute == NULL)
			{
				free(obj);
				return pObj->FindGroupsByID(pObj, key);
			}
			else
			{
				free(obj);
				Group* group = pObj->FindGroupsByID(pObj, key);
				if(group != NULL)
					return group->FindByPath(nextPath, group);
				else
					return NULL;
			}
		}
		else
		{
			free(obj);
			return NULL;
		}
	}
}
