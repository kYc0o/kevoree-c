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