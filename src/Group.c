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

	pObj->internalGetKey = Group_internalGetKey;
	pObj->metaClassName = Group_metaClassName;
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

	pGroupObj->internalGetKey = Group_internalGetKey;
	pGroupObj->metaClassName = Group_metaClassName;
	pObj->super->metaClassName = Group_metaClassName;
	pGroupObj->VisitAttributes = Group_VisitAttributes;
	pGroupObj->VisitPathAttributes = Group_VisitPathAttributes;
	pGroupObj->VisitReferences = Group_VisitReferences;
	pGroupObj->VisitPathReferences = Group_VisitPathReferences;
	pGroupObj->FindSubNodesByID = Group_FindSubNodesByID;
	pGroupObj->FindByPath = Group_FindByPath;
	pGroupObj->Delete = delete_Group;

	return pGroupObj;
}

char* Group_internalGetKey(void* const this)
{
	Group *pObj = (Group*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* Group_metaClassName(void* const this)
{
	/*
	char *name;

	name = malloc(sizeof(char) * (strlen("Group")) + 1);
	if(name != NULL)
		strcpy(name, "Group");
	else
		return NULL;

	return name;
	*/
	return "Group";
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

	char *internalKey = ptr->internalGetKey(ptr);

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
	char *internalKey = ptr->internalGetKey(ptr);

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

void deletePoly_Group(void* const this)
{
	if(this != NULL)
	{
		Instance *pObj = (Instance*)this;
		Group* pGroupObj;
		pGroupObj = pObj->pDerivedObj;
		/*destroy derived obj*/
		/*
		 * TODO verify NULLity
		 * TODO fix polymorphism
		 */
		hashmap_free(pGroupObj->subNodes);
		free(pGroupObj->eContainer);
		free(pGroupObj);
		/*destroy base Obj*/
		delete_Instance(this);
	}
}

void delete_Group(void* const this)
{
	if(this != NULL)
	{
		Group *pObj = (Group*)this;
		/* destroy base object */
		delete_Instance(pObj->super);
		/* destroy data memebers */
		/*
		 * TODO verify NULLity
		 * TODO fix polymorphism
		 */
		hashmap_free(pObj->subNodes);
		free(pObj->eContainer);
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
				sprintf(path,"nodes[%s]", n->internalGetKey(n));
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
				sprintf(path,"%s/%s\\subNodes", parent, n->path);
				visitor->action(path, REFERENCE, parent);
			}
		}
	}
}

void* Group_FindByPath(char* attribute, void* const this)
{
	Group *pObj = (Group*)this;
	/* There is no local attributes */

	/* Instance attributes and references */
	if(!strcmp("name",attribute) ||  !strcmp("metaData",attribute) || !strcmp("started",attribute) || !strcmp("typeDefinition",attribute))
	{
		return Instance_FindByPath(attribute, pObj->super);/*return this->super->metaData;*/
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

		if(!strcmp("nodes", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindSubNodesByID(pObj, key);
			}
			else
			{
				ContainerNode* contnode = pObj->FindSubNodesByID(pObj, key);
				if(contnode != NULL)
					return contnode->FindByPath(nextPath, contnode);
				else
					return NULL;
			}
		}
		else
		{
			free(obj);
			return Instance_FindByPath(attribute, pObj->super);
		}
	}
}
