#include "PortTypeRef.h"

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
	
	/*pPortTypeRefObj->mappings = hashmap_new();*/
	pPortTypeRefObj->mappings = NULL;
	pPortTypeRefObj->ref = NULL;
	
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
	pPortTypeRefObj = (PortTypeRef*)malloc(sizeof(PortTypeRef));

	if (pPortTypeRefObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pPortTypeRefObj;  Pointing to derived object */
	pPortTypeRefObj->super = pObj;
	
	/*pPortTypeRefObj->mappings = hashmap_new();*/
	pPortTypeRefObj->mappings = NULL;
	pPortTypeRefObj->ref = NULL;
	
	pPortTypeRefObj->FindMappingsByID = PortTypeRef_FindMappingsByID;
	pPortTypeRefObj->AddRef = PortTypeRef_AddRef;
	pPortTypeRefObj->AddMappings = PortTypeRef_AddMappings;
	pPortTypeRefObj->RemoveRef = PortTypeRef_RemoveRef;
	pPortTypeRefObj->RemoveMappings = PortTypeRef_RemoveMappings;
	
	pPortTypeRefObj->MetaClassName = PortTypeRef_MetaClassName;
	pPortTypeRefObj->InternalGetKey = PortTypeRef_InternalGetKey;
	pPortTypeRefObj->Delete = delete_PortTypeRef;
	pPortTypeRefObj->VisitAttributes = PortTypeRef_VisitAttributes;
	pPortTypeRefObj->VisitReferences = PortTypeRef_VisitReferences;
	pPortTypeRefObj->FindByPath = PortTypeRef_FindByPath;

	return pPortTypeRefObj;
}

char* PortTypeRef_MetaClassName(PortTypeRef* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("PortTypeRef") + 1));
	strcpy(name, "PortTypeRef");
	
	return name;
}

char* PortTypeRef_InternalGetKey(PortTypeRef* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->name);

	return internalKey;
}

PortTypeMapping* PortTypeRef_FindMappingsByID(PortTypeRef* const this, char* id)
{
	PortTypeMapping* value;

	if(hashmap_get(this->mappings, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void PortTypeRef_AddRef(PortTypeRef* const this, PortType* ptr)
{
	this->ref = ptr;
}

void PortTypeRef_AddMappings(PortTypeRef* const this, PortTypeMapping* ptr)
{
	PortTypeMapping* container = (PortTypeMapping*)ptr;
	
	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeMapping cannot be added in PortTypeRef because the key is not defined\n");
	}
	else
	{
		if(this->mappings == NULL)
		{
			this->mappings = hashmap_new();
		}
		if(hashmap_get(this->mappings, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (PortTypeMapping*)ptr;
			hashmap_put(this->mappings, container->InternalGetKey(container), ptr);
		}
	}
}

void PortTypeRef_RemoveRef(PortTypeRef* const this, PortType* ptr)
{
	free(ptr);
}

void PortTypeRef_RemoveMappings(PortTypeRef* const this, PortTypeMapping* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeMapping cannot be removed in PortTypeRef because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->mappings, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_PortTypeRef(NamedElement* const this)
{
	PortTypeRef* pPortTypeRefObj;
	pPortTypeRefObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pPortTypeRefObj->ref);
	hashmap_free(pPortTypeRefObj->mappings);
	free(pPortTypeRefObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_PortTypeRef(PortTypeRef* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->mappings);
	free(this->ref);
	free(this);
}

void PortTypeRef_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	
	/*sprintf(path,"%s",parent);*/
	NamedElement_VisitAttributes(((PortTypeRef*)(this))->super, parent, visitor);
	
	sprintf(path,"%s\\optional",parent);
	visitor->action(path, BOOL, ((PortTypeRef*)(this))->optional);

	sprintf(path,"%s\\noDependency",parent);
	visitor->action(path, BOOL, ((PortTypeRef*)(this))->noDependency);
}

void PortTypeRef_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((PortTypeRef*)(this))->ref != NULL)
	{
		sprintf(path, "%s/ref[%s]", parent, /*((PortTypeRef*)(this))->ref->super->super->name*/((PortTypeRef*)(this))->ref->InternalGetKey(((PortTypeRef*)(this))->ref));
		((PortTypeRef*)(this))->ref->VisitAttributes(((PortTypeRef*)(this))->ref, path, visitor);
		((PortTypeRef*)(this))->ref->VisitReferences(((PortTypeRef*)(this))->ref, path, visitor);
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
				sprintf(path,"%s/mappings[%s]", parent, /*n->generated_KMF_ID*/n->InternalGetKey(n));
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
		return this->optional;
	}
	else if(!strcmp("noDependency", attribute))
	{
		return this->noDependency;
	}
	/* Local references */
	else
	{
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
		}
		else
		{
			pch = path;
		}
		
		printf("Token: %s\n", pch);

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		char* nextAttribute = strtok(NULL, "\\");
		printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);
	  
		if(!strcmp("mappings", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindMappingsByID(this, queryID);
			}
			else
			{
				PortTypeMapping* ptmapping = this->FindMappingsByID(this, queryID);
				return ptmapping->FindByPath(nextAttribute, ptmapping);
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