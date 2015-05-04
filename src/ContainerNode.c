#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NamedElement.h"
#include "Instance.h"
#include "ComponentInstance.h"
#include "Group.h"
#include "Visitor.h"
#include "NetworkInfo.h"
#include "tools.h"
#include "ContainerNode.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

Instance* newPoly_ContainerNode()
{
	ContainerNode* pContNodeObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pContNodeObj = (ContainerNode*)malloc(sizeof(pContNodeObj));

	if (pContNodeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pContNodeObj; /* Pointing to derived object */
	pContNodeObj->super = pObj;

	pContNodeObj->components = NULL;
	pContNodeObj->hosts = NULL;
	pContNodeObj->host = NULL;
	pContNodeObj->groups = NULL;
	pContNodeObj->networkInformation = NULL;
	pContNodeObj->eContainer = NULL;
	pContNodeObj->path = NULL;
	pContNodeObj->refs = NULL;

	pContNodeObj->FindComponentsByID = ContainerNode_FindComponentsByID;
	pContNodeObj->FindHostsByID = ContainerNode_FindHostsByID;
	pContNodeObj->FindGroupsByID = ContainerNode_FindGroupsByID;
	pContNodeObj->FindNetworkInformationByID = ContainerNode_FindNetworkInformationByID;
	pContNodeObj->AddComponents = ContainerNode_AddComponents;
	pContNodeObj->AddHosts = ContainerNode_AddHosts;
	pContNodeObj->AddHost = ContainerNode_AddHost;
	pContNodeObj->AddGroups = ContainerNode_AddGroups;
	pContNodeObj->AddNetworkInformation = ContainerNode_AddNetworkInformation;
	pContNodeObj->RemoveComponents = ContainerNode_RemoveComponents;
	pContNodeObj->RemoveHost = ContainerNode_RemoveHost;
	pContNodeObj->RemoveHosts = ContainerNode_RemoveHosts;
	pContNodeObj->RemoveGroups = ContainerNode_RemoveGroups;
	pContNodeObj->RemoveNetworkInformation = ContainerNode_RemoveNetworkInformation;

	pObj->metaClassName = ContainerNode_metaClassName;
	pObj->internalGetKey = ContainerNode_internalGetKey;
	pObj->VisitAttributes = ContainerNode_VisitAttributes;
	pObj->VisitPathAttributes = ContainerNode_VisitPathAttributes;
	pObj->VisitReferences = ContainerNode_VisitReferences;
	pObj->VisitPathReferences = ContainerNode_VisitPathReferences;
	pObj->FindByPath = ContainerNode_FindByPath;

	pObj->Delete = deletePoly_ContainerNode;

	return pObj;
}

ContainerNode* new_ContainerNode()
{
	ContainerNode* pContNodeObj = NULL;
	Instance* pObj = new_Instance();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pContNodeObj = (ContainerNode*)malloc(sizeof(ContainerNode));

	if (pContNodeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	/*pObj->pDerivedObj = pContNodeObj; Pointing to derived object */
	pContNodeObj->super = pObj;

	pContNodeObj->components = NULL;
	pContNodeObj->hosts = NULL;
	pContNodeObj->host = NULL;
	pContNodeObj->groups = NULL;
	pContNodeObj->networkInformation = NULL;
	pContNodeObj->eContainer = NULL;
	pContNodeObj->path = NULL;
	pContNodeObj->refs = NULL;

	pContNodeObj->FindComponentsByID = ContainerNode_FindComponentsByID;
	pContNodeObj->FindHostsByID = ContainerNode_FindHostsByID;
	pContNodeObj->FindGroupsByID = ContainerNode_FindGroupsByID;
	pContNodeObj->FindNetworkInformationByID = ContainerNode_FindNetworkInformationByID;
	pContNodeObj->AddComponents = ContainerNode_AddComponents;
	pContNodeObj->AddHosts = ContainerNode_AddHosts;
	pContNodeObj->AddHost = ContainerNode_AddHost;
	pContNodeObj->AddGroups = ContainerNode_AddGroups;
	pContNodeObj->AddNetworkInformation = ContainerNode_AddNetworkInformation;
	pContNodeObj->RemoveComponents = ContainerNode_RemoveComponents;
	pContNodeObj->RemoveHost = ContainerNode_RemoveHost;
	pContNodeObj->RemoveHosts = ContainerNode_RemoveHosts;
	pContNodeObj->RemoveGroups = ContainerNode_RemoveGroups;
	pContNodeObj->RemoveNetworkInformation = ContainerNode_RemoveNetworkInformation;

	pContNodeObj->metaClassName = ContainerNode_metaClassName;
	pObj->super->metaClassName = ContainerNode_metaClassName;
	pContNodeObj->internalGetKey = ContainerNode_internalGetKey;
	pContNodeObj->VisitAttributes = ContainerNode_VisitAttributes;
	pContNodeObj->VisitPathAttributes = ContainerNode_VisitPathAttributes;
	pContNodeObj->VisitReferences = ContainerNode_VisitReferences;
	pContNodeObj->VisitPathReferences = ContainerNode_VisitPathReferences;
	pContNodeObj->FindByPath = ContainerNode_FindByPath;

	pContNodeObj->Delete = delete_ContainerNode;

	return pContNodeObj;
}

char* ContainerNode_internalGetKey(void* const this)
{
	ContainerNode *pObj = (ContainerNode*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* ContainerNode_metaClassName(void* const this)
{
	/*
	ContainerNode *pObj = (ContainerNode*)this;
	char *name;

	name = malloc(sizeof(char) * (strlen("ContainerNode")) + 1);
	if(name != NULL)
		strcpy(name, "ContainerNode");
	else
		return NULL;

	return name;
	*/
	return "ContainerNode";
}

ComponentInstance* ContainerNode_FindComponentsByID(ContainerNode* const this, char* id)
{
	ComponentInstance* value = NULL;

	if(this->components != NULL)
	{
		if(hashmap_get(this->components, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

}

ContainerNode* ContainerNode_FindHostsByID(ContainerNode* const this, char* id)
{
	ContainerNode* value = NULL;

	if(this->hosts != NULL)
	{
		if(hashmap_get(this->hosts, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

}

Group* ContainerNode_FindGroupsByID(ContainerNode* const this, char* id)
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

NetworkInfo* ContainerNode_FindNetworkInformationByID(ContainerNode* const this, char* id)
{
	NetworkInfo* value = NULL;

	if(this->networkInformation != NULL)
	{
		if(hashmap_get(this->networkInformation, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}

}

void ContainerNode_AddComponents(ContainerNode* const this, ComponentInstance* ptr)
{
	/*
	 * Is containment
	 */
	ComponentInstance* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ComponentInstance cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->components == NULL)
		{
			this->components = hashmap_new();
		}

		if(hashmap_get(this->components, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (ComponentInstance*)ptr;*/
			if(hashmap_put(this->components, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->super->eContainer = ptr->eContainer;
				ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/components[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/components[%s]", this->path, internalKey);
				ptr->super->path = ptr->path;
			}
		}
	}
}

void ContainerNode_AddHosts(ContainerNode* const this, ContainerNode* ptr)
{
	/*
	 * Is reference
	 */
	ContainerNode* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ContainerNode cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->hosts == NULL)
		{
			/*
			 * TODO if == NULL
			 */
			this->hosts = hashmap_new();
		}
		if(hashmap_get(this->hosts, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (ContainerNode*)ptr;*/
			if ((hashmap_put(this->hosts, internalKey, ptr)) == MAP_OK) {
				/*if (ptr->refs == NULL) {
					if ((ptr->refs = hashmap_new()) == MAP_OK) {
						PRINTF("INFO: hosts references created successfully!\n");
					} else {
						PRINTF("ERROR: hosts references cannot be created!\n");
					}
				}
				if (ptr->refs != NULL) {
					char *ref = malloc(sizeof(char) * (strlen("node[]") + strlen(this->internalGetKey(this))) + 1);
					sprintf(ref, "node[%s]", this->internalGetKey(this));
					if ((hashmap_put(ptr->refs, this->internalGetKey(this), (void**)&ref)) == MAP_OK) {
						PRINTF("INFO: hosts reference added successfully!\n");
					} else {
						PRINTF("ERROR: hosts reference cannot be added!\n");
					}
				}*/
			}
		}
	}
}

void ContainerNode_AddHost(ContainerNode* const this, ContainerNode* ptr)
{
	/*
	 * Is reference
	 */
	this->host = ptr;
	/*if (ptr->refs == NULL) {
		if ((ptr->refs = hashmap_new()) == MAP_OK) {
			PRINTF("INFO: hosts references created successfully!\n");
		} else {
			PRINTF("ERROR: hosts references cannot be created!\n");
		}
	}
	if (ptr->refs != NULL) {
		char *ref = malloc(sizeof(char) * (strlen("node[]") + strlen(this->internalGetKey(this))) + 1);
		sprintf(ref, "node[%s]", this->internalGetKey(this));
		if ((hashmap_put(ptr->refs, this->internalGetKey(this), (void**)&ref)) == MAP_OK) {
			PRINTF("INFO: hosts reference added successfully!\n");
		} else {
			PRINTF("ERROR: hosts reference cannot be added!\n");
		}
	}*/
}

void ContainerNode_AddGroups(ContainerNode* const this, Group* ptr)
{
	/*
	 * Is reference
	 */
	Group* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Group cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->groups == NULL)
		{
			this->groups = hashmap_new();
		}
		if(hashmap_get(this->groups, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			if ((hashmap_put(this->groups, internalKey, ptr)) == MAP_OK) {
				PRINTF("INFO: Successfully added Group %s to ContainerNode %s\n", internalKey, this->internalGetKey(this));
			}
		}
	}
}

void ContainerNode_AddNetworkInformation(ContainerNode* const this, NetworkInfo* ptr)
{
	NetworkInfo* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkInfo cannot be added in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(this->networkInformation == NULL)
		{
			this->networkInformation = hashmap_new();
		}
		if(hashmap_get(this->networkInformation, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (NetworkInfo*)ptr;*/
			if(hashmap_put(this->networkInformation, internalKey, ptr) == 0)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) +	strlen("/networkInformation[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/networkInformation[%s]", this->path, internalKey);
			}
		}
	}
}

void ContainerNode_RemoveComponents(ContainerNode* const this, ComponentInstance* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ComponentInstance cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->components, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ContainerNode_RemoveHosts(ContainerNode* const this, ContainerNode* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ContainerNode cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		if ((hashmap_remove(this->hosts, internalKey)) == MAP_OK) {
			/*if ((hashmap_remove(ptr->refs, this->path)) == MAP_OK) {
				PRINTF("INFO: hosts reference removed\n");
			} else {
				PRINTF("INFO: cannot remove hosts reference\n");
			}*/
		}
	}
}

void ContainerNode_RemoveHost(ContainerNode* const this, ContainerNode* ptr)
{
	this->host = NULL;
	if ((hashmap_remove(this->hosts, ptr->internalGetKey(ptr))) == MAP_OK) {
		/*if ((hashmap_remove(ptr->refs, this->path)) == MAP_OK) {
			PRINTF("INFO: host reference removed\n");
		} else {
			PRINTF("INFO: cannot remove host reference\n");
		}*/
	}
}

void ContainerNode_RemoveGroups(ContainerNode* const this, Group* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The Group cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		if ((hashmap_remove(this->groups, internalKey)) == MAP_OK) {
			/*if ((hashmap_remove(ptr->refs, this->path)) == MAP_OK) {
				PRINTF("INFO: groups reference removed\n");
			} else {
				PRINTF("ERROR: cannot remove groups reference\n");
			}*/
		}
	}
}

void ContainerNode_RemoveNetworkInformation(ContainerNode* const this, NetworkInfo* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The NetworkInfo cannot be removed in ContainerNode because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->networkInformation, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void deletePoly_ContainerNode(void* const this)
{
	Instance *pObj = (Instance*)this;
	ContainerNode* pContNodeObj;
	pContNodeObj = pObj->pDerivedObj;
	/*destroy derived obj*/
	/*
	 * TODO Check for NULLity
	 * TODO fix polymorphism
	 */
	hashmap_free(pContNodeObj->components);
	hashmap_free(pContNodeObj->hosts);
	hashmap_free(pContNodeObj->groups);
	hashmap_free(pContNodeObj->networkInformation);
	free(pContNodeObj->host);
	free(pContNodeObj->eContainer);
	free(pContNodeObj);
	/*destroy base Obj*/
	delete_Instance(this);
}

void delete_ContainerNode(void* const this)
{
	if(this != NULL)
	{
		ContainerNode *pObj = (ContainerNode*)this;
		/* destroy base object */
		delete_Instance(pObj->super);
		/* destroy data memebers */
		/*
		 * TODO check NULLity
		 */
		hashmap_free(pObj->components);
		hashmap_free(pObj->hosts);
		hashmap_free(pObj->groups);
		hashmap_free(pObj->networkInformation);
		free(pObj->host);
		free(pObj->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void ContainerNode_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	/*
	 * TODO create "this" object type
	 */
	Instance_VisitAttributes(((ContainerNode*)(this))->super, parent, visitor, recursive);
}

void ContainerNode_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	/*
	 * TODO create "this" object type
	 */
	Instance_VisitPathAttributes(((ContainerNode*)(this))->super, parent, visitor, recursive);
}

void ContainerNode_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	/*
	 * TODO create "this" object type
	 */
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((ContainerNode*)(this))->components != NULL)
	{
		visitor->action("components", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((ContainerNode*)(this))->components);

		/* components */
		hashmap_map* m = ((ContainerNode*)(this))->components;

		/* compare components */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				ComponentInstance* n = data;
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
		visitor->action("components", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((ContainerNode*)(this))->hosts != NULL)
	{
		visitor->action("hosts", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((ContainerNode*)(this))->hosts);

		/* hosts */
		hashmap_map* m = ((ContainerNode*)(this))->hosts;

		/* compare hosts */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				n->VisitAttributes(n, path, visitor, false);
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
		visitor->action("hosts", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((ContainerNode*)(this))->host != NULL)
	{
		visitor->action("host", SQBRACKET, NULL);
		sprintf(path, "%s/host[%s]", parent, ((ContainerNode*)(this))->host->internalGetKey(((ContainerNode*)(this))->host));
		((ContainerNode*)(this))->host->VisitAttributes(((ContainerNode*)(this))->host, path, visitor, false);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("host", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((ContainerNode*)(this))->groups != NULL)
	{
		visitor->action("groups", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((ContainerNode*)(this))->groups);

		/* groups */
		hashmap_map* m = ((ContainerNode*)(this))->groups;

		/* compare groups */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				sprintf(path, "groups[%s]", n->internalGetKey(n));
				visitor->action(path, STRREF, NULL);
				if(length > 1)
				{
					visitor->action(NULL, COLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, RETURN, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("groups", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((ContainerNode*)(this))->networkInformation != NULL)
	{
		visitor->action("networkInformation", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((ContainerNode*)(this))->networkInformation);

		/* networkInformation */
		hashmap_map* m = ((ContainerNode*)(this))->networkInformation;

		/* compare networkInformation */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				NetworkInfo* n = data;
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
		visitor->action("networkInformation", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	Instance_VisitReferences(((ContainerNode*)(this))->super, parent, visitor, false);

}

void ContainerNode_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	/*
	 * TODO create "this" object type
	 */
	char path[256];
	memset(&path[0], 0, sizeof(path));

	Instance_VisitPathReferences(((ContainerNode*)(this))->super, parent, visitor, false);

	if(((ContainerNode*)(this))->components != NULL)
	{
		int i;

		/* components */
		hashmap_map* m = ((ContainerNode*)(this))->components;

		/* compare components */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ComponentInstance* n = data;
				sprintf(path,"%s/components[%s]", parent, n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "components")) {
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

	if(((ContainerNode*)(this))->hosts != NULL)
	{
		int i;

		/* hosts */
		hashmap_map* m = ((ContainerNode*)(this))->hosts;

		/* compare hosts */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				sprintf(path,"%s/%s\\hosts", parent, n->path);
				/*n->VisitPathAttributes(n, path, visitor, false);*/
				visitor->action(path, REFERENCE, parent);
			}
		}
	}

	if(((ContainerNode*)(this))->host != NULL)
	{
		sprintf(path, "%s/%s\\host", parent, ((ContainerNode*)(this))->host->path);
		/*((ContainerNode*)(this))->host->VisitPathAttributes(((ContainerNode*)(this))->host, path, visitor, false);*/
		visitor->action(path, REFERENCE, parent);
	}

	if(((ContainerNode*)(this))->groups != NULL)
	{
		int i;

		/* groups */
		hashmap_map* m = ((ContainerNode*)(this))->groups;

		/* compare groups */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				Group* n = data;
				sprintf(path, "%s/%s\\groups", parent, n->path);
				/*n->VisitPathAttributes(n, path, visitor, false);*/
				visitor->action(path, REFERENCE, parent);
			}
		}
	}

	if(((ContainerNode*)(this))->networkInformation != NULL)
	{
		int i;

		/* networkInformation */
		hashmap_map* m = ((ContainerNode*)(this))->networkInformation;

		/* compare networkInformation */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				NetworkInfo* n = data;
				sprintf(path,"%s/networkInformation[%s]", parent, n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "networkInformation")) {
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

void* ContainerNode_FindByPath(char* attribute, void* const this)
{
	ContainerNode *pObj = (ContainerNode*)this;
	/* There is no local attributes */

	/* Instance attributes and references */
	if(!strcmp("name", attribute) ||  !strcmp("metaData", attribute) || !strcmp("started", attribute))
	{
		return Instance_FindByPath(attribute, pObj->super);
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

		if(!strcmp("components", obj))
		{
			if(nextAttribute == NULL)
			{
				free(obj);
				return pObj->FindComponentsByID(pObj, key);
			}
			else
			{
				free(obj);
				ComponentInstance* compins = pObj->FindComponentsByID(pObj, key);
				if(compins != NULL)
					return compins->FindByPath(nextPath, compins);
				else
					return NULL;
			}
		}
		else if(!strcmp("hosts", obj))
		{
			if(nextAttribute == NULL)
			{
				free(obj);
				return pObj->FindHostsByID(pObj, key);
			}
			else
			{
				free(obj);
				ContainerNode* contnode = pObj->FindHostsByID(pObj, key);
				if(contnode != NULL)
					return contnode->FindByPath(nextPath, contnode);
				else
					return NULL;
			}
		}
		else if(!strcmp("host", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->host;
			}
			else
			{
				return pObj->host->FindByPath(nextPath, pObj->host);
			}
		}
		else if(!strcmp("networkInformation", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindNetworkInformationByID(pObj, key);
			}
			else
			{
				NetworkInfo* netinfo = pObj->FindNetworkInformationByID(pObj, key);
				if(netinfo != NULL)
					return netinfo->FindByPath(nextPath, netinfo);
				else
					return NULL;
			}
		}
		else if(!strcmp("groups", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindGroupsByID(pObj, key);
			}
			else
			{
				Group* group = pObj->FindGroupsByID(pObj, key);
				if(group != NULL)
					return group->FindByPath(nextPath, group);
				else
					return NULL;
			}
		}
		/* Instance references */
		else
		{
			free(obj);
			return Instance_FindByPath(attribute, pObj->super);
		}
	}
}
