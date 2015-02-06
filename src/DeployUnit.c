#include <string.h>
#include <stdio.h>
#include "tools.h"
#include "NamedElement.h"
#include "DeployUnit.h"
#include "Visitor.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NamedElement* newPoly_DeployUnit()
{
	DeployUnit* pDepUnitObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pDepUnitObj = (DeployUnit*)malloc(sizeof(DeployUnit));

	if (pDepUnitObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pDepUnitObj; /* Pointing to derived object */

	pDepUnitObj->groupName = NULL;
	pDepUnitObj->version = NULL;
	pDepUnitObj->url = NULL;
	pDepUnitObj->hashcode = NULL;
	pDepUnitObj->type = NULL;
	pDepUnitObj->requiredLibs = NULL;
	pDepUnitObj->eContainer = NULL;

	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;

	pObj->MetaClassName = DeployUnit_MetaClassName;
	pObj->InternalGetKey = DeployUnit_InternalGetKey;
	pObj->VisitAttributes = DeployUnit_VisitAttributes;
	pObj->VisitPathAttributes = DeployUnit_VisitPathAttributes;
	pObj->VisitReferences = DeployUnit_VisitReferences;
	pObj->VisitPathReferences = DeployUnit_VisitPathReferences;
	pObj->FindByPath = DeployUnit_FindByPath;

	pObj->Delete = deletePoly_DeployUnit;

	return pObj;
}

DeployUnit* new_DeployUnit()
{
	DeployUnit* pDepUnitObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pDepUnitObj = (DeployUnit*)malloc(sizeof(DeployUnit));

	if (pDepUnitObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pDepUnitObj;  Pointing to derived object */
	pDepUnitObj->super = pObj; /* Pointing to the base object */

	pDepUnitObj->groupName = NULL;
	pDepUnitObj->version = NULL;
	pDepUnitObj->url = NULL;
	pDepUnitObj->hashcode = NULL;
	pDepUnitObj->type = NULL;
	pDepUnitObj->requiredLibs = NULL;
	pDepUnitObj->eContainer = NULL;

	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;

	pDepUnitObj->MetaClassName = DeployUnit_MetaClassName;
	pObj->MetaClassName = DeployUnit_MetaClassName;
	pDepUnitObj->InternalGetKey = DeployUnit_InternalGetKey;
	pDepUnitObj->VisitAttributes = DeployUnit_VisitAttributes;
	pDepUnitObj->VisitPathAttributes = DeployUnit_VisitPathAttributes;
	pDepUnitObj->VisitReferences = DeployUnit_VisitReferences;
	pDepUnitObj->VisitPathReferences = DeployUnit_VisitPathReferences;
	pDepUnitObj->FindByPath = DeployUnit_FindByPath;

	pDepUnitObj->Delete = delete_DeployUnit;

	return pDepUnitObj;
}

char* DeployUnit_InternalGetKey(DeployUnit* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	/*internalKey = my_malloc(sizeof(char) * (strlen("groupName=") + strlen(this->groupName) + strlen(",") +
										strlen("hashcode=") + strlen(this->hashcode) + strlen(",") +
										strlen("name=") + strlen(this->super->name) + strlen(",") +
										strlen("version=") + strlen(this->version)) + 1);*/
	internalKey = malloc(sizeof(char) * (strlen(this->groupName) + strlen("/") +
			strlen(this->hashcode) + strlen("/") +
			strlen(this->super->name) + strlen("/") +
			strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	sprintf(internalKey, "%s/%s/%s/%s", this->groupName, this->hashcode, this->super->name, this->version);

	return internalKey;
}

char* DeployUnit_MetaClassName(DeployUnit* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("DeployUnit")) + 1);
	if(name != NULL)
		strcpy(name, "DeployUnit");
	else
		return NULL;

	return name;
}

void DeployUnit_AddRequiredLibs(DeployUnit* const this, DeployUnit* ptr)
{
	DeployUnit* container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DeployUnit cannot be added in DeployUnit because the key is not defined\n");
	}
	else
	{
		if(this->requiredLibs == NULL)
		{
			this->requiredLibs = hashmap_new();
		}
		if(hashmap_get(this->requiredLibs, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (DeployUnit*)ptr;*/
			hashmap_put(this->requiredLibs, internalKey, ptr);
		}
	}
}

void DeployUnit_RemoveRequiredLibs(DeployUnit* const this, DeployUnit *ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The DeployUnit cannot be removed in DeployUnit because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->requiredLibs, internalKey);
		free(internalKey);
	}
}

DeployUnit* DeployUnit_FindRequiredLibsByID(DeployUnit* const this, char* id)
{
	DeployUnit* value = NULL;

	if(hashmap_get(this->requiredLibs, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void deletePoly_DeployUnit(NamedElement* const this)
{
	if(this != NULL)
	{
		DeployUnit* pDepUnitObj;
		pDepUnitObj = this->pDerivedObj;
		/*destroy derived obj*/
		free(pDepUnitObj->groupName);
		free(pDepUnitObj->version);
		free(pDepUnitObj->url);
		free(pDepUnitObj->hashcode);
		free(pDepUnitObj->type);
		hashmap_free(pDepUnitObj->requiredLibs);
		free(pDepUnitObj->eContainer);
		free(pDepUnitObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_DeployUnit(DeployUnit* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		free(this->groupName);
		free(this->version);
		free(this->url);
		free(this->hashcode);
		free(this->type);
		hashmap_free(this->requiredLibs);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void DeployUnit_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		NamedElement_VisitAttributes(((DeployUnit*)(this))->super, parent, visitor, recursive);

		sprintf(path, "groupName");
		visitor->action(path, STRING, ((DeployUnit*)(this))->groupName);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "version");
		visitor->action(path, STRING, ((DeployUnit*)(this))->version);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "url");
		visitor->action(path, STRING, ((DeployUnit*)(this))->url);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "hashcode");
		visitor->action(path, STRING, ((DeployUnit*)(this))->hashcode);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "type");
		visitor->action(path, STRING, ((DeployUnit*)(this))->type);
		visitor->action(NULL, RETURN, NULL);
	}
	else
	{
		NamedElement_VisitAttributes(((DeployUnit*)(this))->super, parent, visitor, recursive);
	}
}

void DeployUnit_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		NamedElement_VisitPathAttributes(((DeployUnit*)(this))->super, parent, visitor, recursive);

		sprintf(path,"%s\\groupName", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->groupName);

		sprintf(path, "%s\\version", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->version);

		sprintf(path,"%s\\url",parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->url);

		sprintf(path, "%s\\hashcode", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->hashcode);

		sprintf(path, "%s\\type", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->type);
	}
	else
	{
		NamedElement_VisitPathAttributes(((DeployUnit*)(this))->super, parent, visitor, recursive);
	}
}

void DeployUnit_VisitReferences(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((DeployUnit*)(this))->requiredLibs != NULL)
	{
		visitor->action("requiredLibs", SQBRACKET, NULL);
		int i;

		/* requiredLibs */
		hashmap_map* m = ((DeployUnit*)(this))->requiredLibs;

		/* compare requiredLibs */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path,"requiredLibs[%s]", n->InternalGetKey(n));
				visitor->action(path, STRREF, NULL);
				visitor->action(NULL, COLON, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
}

void DeployUnit_VisitPathReferences(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((DeployUnit*)(this))->requiredLibs != NULL)
	{
		int i;

		/* requiredLibs */
		hashmap_map* m = ((DeployUnit*)(this))->requiredLibs;

		/* compare requiredLibs */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path,"%s/requiredLibs[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, false);
			}
		}
	}
}

void *DeployUnit_FindByPath(char *attribute, DeployUnit *const this)
{	
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("groupName", attribute))
	{
		return this->groupName;
	}
	else if(!strcmp("version", attribute))
	{
		return this->version;
	}
	else if(!strcmp("url", attribute))
	{
		return this->url;
	}
	else if(!strcmp("hashcode", attribute))
	{
		return this->hashcode;
	}
	else if(!strcmp("type", attribute))
	{
		return this->type;
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

		if(!strcmp("requiredLibs", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->FindRequiredLibsByID(this, key);
			}
			else
			{
				DeployUnit* reqlibs = this->FindRequiredLibsByID(this, key);
				if(reqlibs != NULL)
					return reqlibs->FindByPath(nextPath, reqlibs);
				else
					return NULL;
			}
		}
		else
		{
			free(obj);
			PRINTF("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
