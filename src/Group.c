#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "ContainerNode.h"
#include "Instance.h"
#include "ContainerRoot.h"
#include "Group.h"
#include "NamedElement.h"
#include "Visitor.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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

	pGroupObj->subNodes = NULL;
	pGroupObj->eContainer = NULL;

	pGroupObj->AddSubNodes = Group_AddSubNodes;
	pGroupObj->RemoveSubNodes = Group_RemoveSubNodes;
	pGroupObj->FindSubNodesByID = Group_FindSubNodesByID;
	pGroupObj->FindByPath = Group_FindByPath;

	pObj->InternalGetKey = Group_InternalGetKey;
	pObj->MetaClassName = Group_MetaClassName;
	pObj->VisitAttributes = Group_VisitAttributes;
	pObj->VisitPathAttributes = Group_VisitPathAttributes;
	pObj->VisitReferences = Group_VisitReferences;
	pObj->VisitPathReferences = Group_VisitPathReferences;

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
	pGroupObj->eContainer = NULL;

	pGroupObj->AddSubNodes = Group_AddSubNodes;
	pGroupObj->RemoveSubNodes = Group_RemoveSubNodes;

	pGroupObj->InternalGetKey = Group_InternalGetKey;
	pGroupObj->MetaClassName = Group_MetaClassName;
	pObj->super->MetaClassName = Group_MetaClassName;
	pGroupObj->VisitAttributes = Group_VisitAttributes;
	pGroupObj->VisitPathAttributes = Group_VisitPathAttributes;
	pGroupObj->VisitReferences = Group_VisitReferences;
	pGroupObj->VisitPathReferences = Group_VisitPathReferences;
	pGroupObj->FindSubNodesByID = Group_FindSubNodesByID;
	pGroupObj->FindByPath = Group_FindByPath;
	pGroupObj->Delete = delete_Group;

	return pGroupObj;
}

char* Group_InternalGetKey(Group* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* Group_MetaClassName(Group* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("Group")) + 1);
	if(name != NULL)
		strcpy(name, "Group");
	else
		return NULL;

	return name;
}

ContainerNode* Group_FindSubNodesByID(Group* const this, char* id)
{
	ContainerNode* value = NULL;

	if(this->subNodes != NULL)
	{
		if(hashmap_get(this->subNodes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void Group_AddSubNodes(Group* const this, ContainerNode* ptr)
{
	ContainerNode* container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ContainerNode cannot be added in Group because the key is not defined\n");
	}
	else
	{
		if(this->subNodes == NULL)
		{
			this->subNodes = hashmap_new();
		}
		if(hashmap_get(this->subNodes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (ContainerNode*)ptr;*/
			hashmap_put(this->subNodes, internalKey, ptr);
		}
	}
}

void Group_RemoveSubNodes(Group* const this, ContainerNode* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The ContainerNode cannot be removed in Group because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->subNodes, internalKey);
		free(internalKey);
	}
}

void deletePoly_Group(Instance* const this)
{
	if(this != NULL)
	{
		Group* pGroupObj;
		pGroupObj = this->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pGroupObj->subNodes);
		free(pGroupObj->eContainer);
		free(pGroupObj);
		/*destroy base Obj*/
		delete_Instance(this);
	}
}

void delete_Group(Group* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_Instance(this->super);
		/* destroy data memebers */
		hashmap_free(this->subNodes);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void Group_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	Instance_VisitAttributes(((Group*)(this))->super, parent, visitor, recursive);
}

void Group_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	Instance_VisitPathAttributes(((Group*)(this))->super, parent, visitor, recursive);
}

void Group_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((Group*)(this))->subNodes != NULL)
	{
		visitor->action("subNodes", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(((Group*)(this))->subNodes);

		/* subNodes */
		hashmap_map* m = ((Group*)(this))->subNodes;

		/* compare subNodes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				sprintf(path,"nodes[%s]", n->InternalGetKey(n));
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
		visitor->action("subNodes", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	Instance_VisitReferences(((Group*)(this))->super, parent, visitor, false);

}

void Group_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	Instance_VisitPathReferences(((Group*)(this))->super, parent, visitor, false);

	if(((Group*)(this))->subNodes != NULL)
	{
		int i;

		/* subNodes */
		hashmap_map* m = ((Group*)(this))->subNodes;

		/* compare subNodes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				ContainerNode* n = data;
				sprintf(path,"%s/subNodes[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, false);
			}
		}
	}
}

void* Group_FindByPath(char* attribute, Group* const this)
{
	/* There is no local attributes */

	/* Instance attributes and references */
	if(!strcmp("name",attribute) ||  !strcmp("metaData",attribute) || !strcmp("started",attribute) || !strcmp("typeDefinition",attribute))
	{
		return Instance_FindByPath(attribute, this->super);/*return this->super->metaData;*/
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
				nextAttribute = strtok(NULL, "\\");
				strcpy(nextPath, ++nextAttribute);
				PRINTF("Next Path: %s\n", nextPath);
				nextAttribute = NULL;
			}
		}
		else
		{
			nextAttribute = strtok(path, "\\");
			nextAttribute = strtok(NULL, "\\");
			PRINTF("Attribute: %s\n", nextAttribute);
		}

		if(!strcmp("subNodes", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->FindSubNodesByID(this, key);
			}
			else
			{
				ContainerNode* contnode = this->FindSubNodesByID(this, key);
				if(contnode != NULL)
					return contnode->FindByPath(nextPath, contnode);
				else
					return NULL;
			}
		}
		else
		{
			free(obj);
			return Instance_FindByPath(attribute, this->super);
		}
	}
}
