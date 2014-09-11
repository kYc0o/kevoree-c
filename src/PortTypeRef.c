#include <string.h>
#include "NamedElement.h"
#include "PortType.h"
#include "PortTypeMapping.h"
#include "ComponentType.h"
#include "Visitor.h"
#include "PortTypeRef.h"

NamedElement* newPoly_PortTypeRef(void)
{
	PortTypeRef* pPortTypeRefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pPortTypeRefObj = (PortTypeRef*)my_malloc(sizeof(PortTypeRef));

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
	
	pObj->MetaClassName = PortTypeRef_MetaClassName;
	pObj->InternalGetKey = PortTypeRef_InternalGetKey;
	pObj->Delete = deletePoly_PortTypeRef;
	pObj->VisitAttributes = PortTypeRef_VisitAttributes;
	pObj->VisitReferences = PortTypeRef_VisitReferences;
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
	pPortTypeRefObj = (PortTypeRef*)my_malloc(sizeof(PortTypeRef));

	if (pPortTypeRefObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pPortTypeRefObj;  Pointing to derived object */
	pPortTypeRefObj->super = pObj;
	
	/*pPortTypeRefObj->mappings = hashmap_new();*/
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
	
	pPortTypeRefObj->MetaClassName = PortTypeRef_MetaClassName;
	pObj->MetaClassName = PortTypeRef_MetaClassName;
	pPortTypeRefObj->InternalGetKey = PortTypeRef_InternalGetKey;
	pPortTypeRefObj->Delete = delete_PortTypeRef;
	pPortTypeRefObj->VisitAttributes = PortTypeRef_VisitAttributes;
	pPortTypeRefObj->VisitReferences = PortTypeRef_VisitReferences;
	pPortTypeRefObj->FindByPath = PortTypeRef_FindByPath;

	return pPortTypeRefObj;
}

char* PortTypeRef_MetaClassName(PortTypeRef* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("PortTypeRef")) + 1);
	if(name != NULL)
		strcpy(name, "PortTypeRef");
	else
		return NULL;
	
	return name;
}

char* PortTypeRef_InternalGetKey(PortTypeRef* const this)
{
	return this->super->InternalGetKey(this->super);
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
	
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The PortTypeMapping cannot be added in PortTypeRef because the key is not defined\n");
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
				ptr->eContainer = this;
		}
	}
}

void PortTypeRef_RemoveRef(PortTypeRef* const this, PortType* ptr)
{
	free(ptr);
	this->ref = NULL;
}

void PortTypeRef_RemoveMappings(PortTypeRef* const this, PortTypeMapping* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The PortTypeMapping cannot be removed in PortTypeRef because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(this->mappings, internalKey) == MAP_OK)
		{
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void deletePoly_PortTypeRef(NamedElement* const this)
{
	if(this != NULL)
	{
		PortTypeRef* pPortTypeRefObj;
		pPortTypeRefObj = this->pDerivedObj;
		/*destroy derived obj*/
		free(pPortTypeRefObj->ref);
		hashmap_free(pPortTypeRefObj->mappings);
		free(pPortTypeRefObj->eContainer);
		free(pPortTypeRefObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_PortTypeRef(PortTypeRef* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		hashmap_free(this->mappings);
		free(this->ref);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void PortTypeRef_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		/*sprintf(path,"%s\\cClass", parent);
		visitor->action(path, STRING, ((PortTypeRef*)this)->MetaClassName((PortTypeRef*)this));*/

		NamedElement_VisitAttributes(((PortTypeRef*)(this))->super, parent, visitor, recursive);

		/*sprintf(path,"%s\\optional",parent);*/
		sprintf(path, "optional");
		visitor->action(path, BOOL, (void*)((PortTypeRef*)(this))->optional);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path,"%s\\noDependency",parent);*/
		sprintf(path, "noDependency");
		visitor->action(path, BOOL, (void*)((PortTypeRef*)(this))->noDependency);
		visitor->action(NULL, RETURN, NULL);
	}
	else
	{
		NamedElement_VisitAttributes(((PortTypeRef*)(this))->super, parent, visitor, recursive);
	}
}

void PortTypeRef_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((PortTypeRef*)(this))->ref != NULL)
	{
		sprintf(path, "%s/ref[%s]", parent, ((PortTypeRef*)(this))->ref->InternalGetKey(((PortTypeRef*)(this))->ref));
		((PortTypeRef*)(this))->ref->VisitAttributes(((PortTypeRef*)(this))->ref, path, visitor, 0);
		/*((PortTypeRef*)(this))->ref->VisitReferences(((PortTypeRef*)(this))->ref, path, visitor);*/
	}
	
	if(((PortTypeRef*)(this))->mappings != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/mappings[%s]", parent, ((PortTypeRef*)(this))->super->name);*/
		
		/* mappings */
		hashmap_map* m = ((PortTypeRef*)(this))->mappings;

		/* compare mappings */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				PortTypeMapping* n = data;
				sprintf(path,"%s/mappings[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, parent, visitor);
				/*n->VisitReferences(n, parent, visitor);*/
			}
		}
	}
}

void* PortTypeRef_FindByPath(char* attribute, PortTypeRef* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("optional", attribute))
	{
		return (void*)this->optional;
	}
	else if(!strcmp("noDependency", attribute))
	{
		return (void*)this->noDependency;
	}
	/* Local references */
	else
	{
		char* nextAttribute = NULL;
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
			/*nextAttribute = strtok(NULL, "\\");
			sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));*/
			if(strchr(attribute,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);*/
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not found, looking for path\n");*/
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}
		
		/*printf("Token: %s\n", pch);*/

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		/*printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);*/
	  
		if(!strcmp("mappings", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindMappingsByID(this, queryID);
			}
			else
			{
				PortTypeMapping* ptmapping = this->FindMappingsByID(this, queryID);
				if(ptmapping != NULL)
					return ptmapping->FindByPath(nextAttribute, ptmapping);
				else
					return NULL;
			}
		}
		else if(!strcmp("ref", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->ref;
			}
			else
			{
				return this->ref->FindByPath(attribute, this->ref->super);
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
