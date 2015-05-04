#include <string.h>
#include "NamedElement.h"
#include "PortType.h"
#include "PortTypeMapping.h"
#include "ComponentType.h"
#include "Visitor.h"
#include "PortTypeRef.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NamedElement* newPoly_PortTypeRef(void)
{
	PortTypeRef* pPortTypeRefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pPortTypeRefObj = (PortTypeRef*)malloc(sizeof(PortTypeRef));

	if (pPortTypeRefObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pPortTypeRefObj; /* Pointing to derived object */

	pPortTypeRefObj->mappings = NULL;
	pPortTypeRefObj->ref = NULL;
	pPortTypeRefObj->optional = -1;
	pPortTypeRefObj->noDependency = -1;
	pPortTypeRefObj->eContainer = NULL;

	pPortTypeRefObj->FindMappingsByID = PortTypeRef_FindMappingsByID;
	pPortTypeRefObj->AddRef = PortTypeRef_AddRef;
	pPortTypeRefObj->AddMappings = PortTypeRef_AddMappings;
	pPortTypeRefObj->RemoveRef = PortTypeRef_RemoveRef;
	pPortTypeRefObj->RemoveMappings = PortTypeRef_RemoveMappings;

	pObj->metaClassName = PortTypeRef_metaClassName;
	pObj->internalGetKey = PortTypeRef_internalGetKey;
	pObj->Delete = deletePoly_PortTypeRef;
	pObj->VisitAttributes = PortTypeRef_VisitAttributes;
	pObj->VisitPathAttributes = PortTypeRef_VisitPathAttributes;
	pObj->VisitReferences = PortTypeRef_VisitReferences;
	pObj->VisitPathReferences = PortTypeRef_VisitPathReferences;
	pObj->FindByPath = PortTypeRef_FindByPath;

	return pObj;
}

PortTypeRef* new_PortTypeRef(void)
{
	PortTypeRef* pPortTypeRefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pPortTypeRefObj = (PortTypeRef*)malloc(sizeof(PortTypeRef));

	if (pPortTypeRefObj == NULL)
	{
		return NULL;
	}

	pPortTypeRefObj->super = pObj;

	pPortTypeRefObj->mappings = NULL;
	pPortTypeRefObj->ref = NULL;
	pPortTypeRefObj->optional = -1;
	pPortTypeRefObj->noDependency = -1;
	pPortTypeRefObj->eContainer = NULL;

	pPortTypeRefObj->FindMappingsByID = PortTypeRef_FindMappingsByID;
	pPortTypeRefObj->AddRef = PortTypeRef_AddRef;
	pPortTypeRefObj->AddMappings = PortTypeRef_AddMappings;
	pPortTypeRefObj->RemoveRef = PortTypeRef_RemoveRef;
	pPortTypeRefObj->RemoveMappings = PortTypeRef_RemoveMappings;

	pPortTypeRefObj->metaClassName = PortTypeRef_metaClassName;
	pObj->metaClassName = PortTypeRef_metaClassName;
	pPortTypeRefObj->internalGetKey = PortTypeRef_internalGetKey;
	pPortTypeRefObj->Delete = delete_PortTypeRef;
	pPortTypeRefObj->VisitAttributes = PortTypeRef_VisitAttributes;
	pPortTypeRefObj->VisitPathAttributes = PortTypeRef_VisitPathAttributes;
	pPortTypeRefObj->VisitReferences = PortTypeRef_VisitReferences;
	pPortTypeRefObj->VisitPathReferences = PortTypeRef_VisitPathReferences;
	pPortTypeRefObj->FindByPath = PortTypeRef_FindByPath;

	return pPortTypeRefObj;
}

char* PortTypeRef_metaClassName(void * const this)
{
	/*
	char *name;

	name = malloc(sizeof(char) * (strlen("PortTypeRef")) + 1);
	if(name != NULL)
		strcpy(name, "PortTypeRef");
	else
		return NULL;

	return name;
	*/
	return "PortTypeRef";
}

char* PortTypeRef_internalGetKey(void * const this)
{
	PortTypeRef *pObj = (PortTypeRef*)this;
	return pObj->super->internalGetKey(pObj->super);
}

PortTypeMapping* PortTypeRef_FindMappingsByID(PortTypeRef* const this, char* id)
{
	PortTypeMapping* value = NULL;

	if(this->mappings != NULL)
	{
		if(hashmap_get(this->mappings, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void PortTypeRef_AddRef(PortTypeRef* const this, PortType* ptr)
{
	this->ref = ptr;
}

void PortTypeRef_AddMappings(PortTypeRef* const this, PortTypeMapping* ptr)
{
	PortTypeMapping* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The PortTypeMapping cannot be added in PortTypeRef because the key is not defined\n");
	}
	else
	{
		if(this->mappings == NULL)
		{
			this->mappings = hashmap_new();
		}
		if(hashmap_get(this->mappings, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (PortTypeMapping*)ptr;*/
			if(hashmap_put(this->mappings, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/mappings[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/mappings[%s]", this->path, internalKey);
			}
		}
	}
}

void PortTypeRef_RemoveRef(PortTypeRef* const this, PortType* ptr)
{
	this->ref = NULL;
}

void PortTypeRef_RemoveMappings(PortTypeRef* const this, PortTypeMapping* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The PortTypeMapping cannot be removed in PortTypeRef because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->mappings, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void deletePoly_PortTypeRef(void * const this)
{
	if(this != NULL)
	{
		NamedElement *pObj = (NamedElement*)this;
		PortTypeRef* pPortTypeRefObj;
		pPortTypeRefObj = pObj->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pPortTypeRefObj->mappings);
		free(pPortTypeRefObj->eContainer);
		free(pPortTypeRefObj);
		/*destroy base Obj*/
		delete_NamedElement(pObj);
	}
}

void delete_PortTypeRef(void * const this)
{
	if(this != NULL)
	{
		PortTypeRef *pObj = (PortTypeRef*)this;
		/* destroy base object */
		delete_NamedElement(pObj->super);
		/* destroy data memebers */
		hashmap_free(pObj->mappings);
		free(pObj->eContainer);
		free(pObj);
		/*this = NULL;*/
	}
}

void PortTypeRef_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		NamedElement_VisitAttributes(((PortTypeRef*)(this))->super, parent, visitor, recursive);

		sprintf(path, "optional");
		visitor->action(path, BOOL, (void*)((PortTypeRef*)(this))->optional);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "noDependency");
		visitor->action(path, BOOL, (void*)((PortTypeRef*)(this))->noDependency);
		visitor->action(NULL, RETURN, NULL);
	}
	else
	{
		NamedElement_VisitAttributes(((PortTypeRef*)(this))->super, parent, visitor, recursive);
	}
}

void PortTypeRef_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		NamedElement_VisitPathAttributes(((PortTypeRef*)(this))->super, parent, visitor, recursive);

		sprintf(path,"%s\\optional",parent);
		visitor->action(path, BOOL, (void*)((PortTypeRef*)(this))->optional);

		sprintf(path,"%s\\noDependency",parent);
		visitor->action(path, BOOL, (void*)((PortTypeRef*)(this))->noDependency);
	}
	else
	{
		NamedElement_VisitPathAttributes(((PortTypeRef*)(this))->super, parent, visitor, recursive);
	}
}

void PortTypeRef_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((PortTypeRef*)(this))->ref != NULL)
	{
		sprintf(path, "%s/ref[%s]", parent, ((PortTypeRef*)(this))->ref->internalGetKey(((PortTypeRef*)(this))->ref));
		((PortTypeRef*)(this))->ref->VisitAttributes(((PortTypeRef*)(this))->ref, path, visitor, false);
	}

	if(((PortTypeRef*)(this))->mappings != NULL)
	{
		int i;

		/* mappings */
		hashmap_map* m = ((PortTypeRef*)(this))->mappings;

		/* compare mappings */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				PortTypeMapping* n = data;
				sprintf(path,"%s/mappings[%s]", parent, n->internalGetKey(n));
				n->VisitAttributes(n, parent, visitor, recursive);
			}
		}
	}
}

void PortTypeRef_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((PortTypeRef*)(this))->ref != NULL)
	{
		sprintf(path, "%s/ref[%s]", parent, ((PortTypeRef*)(this))->ref->internalGetKey(((PortTypeRef*)(this))->ref));
		((PortTypeRef*)(this))->ref->VisitPathAttributes(((PortTypeRef*)(this))->ref, path, visitor, false);
	}

	if(((PortTypeRef*)(this))->mappings != NULL)
	{
		int i;

		/* mappings */
		hashmap_map* m = ((PortTypeRef*)(this))->mappings;

		/* compare mappings */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				PortTypeMapping* n = data;
				sprintf(path,"%s/mappings[%s]", parent, n->internalGetKey(n));
				n->VisitPathAttributes(n, parent, visitor, recursive);
			}
		}
	}
}

void* PortTypeRef_FindByPath(char* attribute, void * const this)
{
	PortTypeRef *pObj = (PortTypeRef*)this;
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return pObj->super->FindByPath(attribute, pObj->super);
	}
	/* Local attributes */
	else if(!strcmp("optional", attribute))
	{
		return (void*)pObj->optional;
	}
	else if(!strcmp("noDependency", attribute))
	{
		return (void*)pObj->noDependency;
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

		if(!strcmp("mappings", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindMappingsByID(pObj, key);
			}
			else
			{
				PortTypeMapping* ptmapping = pObj->FindMappingsByID(pObj, key);
				if(ptmapping != NULL)
					return ptmapping->FindByPath(nextPath, ptmapping);
				else
					return NULL;
			}
		}
		else if(!strcmp("ref", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->ref;
			}
			else
			{
				return pObj->ref->FindByPath(attribute, pObj->ref->super);
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
