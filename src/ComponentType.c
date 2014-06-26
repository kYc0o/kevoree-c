#include "ComponentType.h"

TypeDefinition* newPoly_ComponentType(void)
{
	ComponentType* pCompTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompTypeObj = (ComponentType*)malloc(sizeof(ComponentType));

	if (pCompTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pCompTypeObj; /* Pointing to derived object */
	
	
	/*pCompTypeObj->required = hashmap_new();
	pCompTypeObj->provided = hashmap_new();*/
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;
	
	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pObj->MetaClassName = ComponentType_MetaClassName;
	pObj->InternalGetKey = ComponentType_InternalGetKey;
	
	pObj->Delete = deletePoly_ComponentType;

	return pObj;
}

ComponentType* new_ComponentType(void)
{
	ComponentType* pCompTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompTypeObj = (ComponentType*)malloc(sizeof(ComponentType));

	if (pCompTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	/*pObj->pDerivedObj = pCompTypeObj;  Pointing to derived object */
	pCompTypeObj->super = pObj;
	
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;
	
	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pCompTypeObj->MetaClassName = ComponentType_MetaClassName;
	pCompTypeObj->InternalGetKey = ComponentType_InternalGetKey;
	
	pCompTypeObj->Delete = delete_ComponentType;

	return pCompTypeObj;
}

char* ComponentType_MetaClassName(ComponentType* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->super->name) + strlen("/") + strlen(this->super->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->super->name);
	strcat(internalKey, "/");
	strcat(internalKey, this->super->version);

	return internalKey;
}

char* ComponentType_InternalGetKey(ComponentType* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("ComponentType") + 1));
	strcpy(name, "ComponentType");
	
	return name;
}

PortTypeRef* ComponentType_FindRequiredByID(ComponentType* const this, char* id)
{
	PortTypeRef* value;

	if(hashmap_get(this->required, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

PortTypeRef* ComponentType_FindProvidedByID(ComponentType* const this, char* id)
{
	PortTypeRef* value;

	if(hashmap_get(this->provided, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void ComponentType_AddRequired(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->required == NULL)
		{
			this->required = hashmap_new();
		}

		if(hashmap_get(this->required, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (PortTypeRef*)ptr;
			hashmap_put(this->required, container->InternalGetKey(container), ptr);
		}
	}
}

void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->provided == NULL)
		{
			this->provided = hashmap_new();
		}
		if(hashmap_get(this->provided, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (PortTypeRef*)ptr;
			hashmap_put(this->provided, container->InternalGetKey(container), ptr);
		}
	}
}

void ComponentType_RemoveRequired(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->required, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void ComponentType_RemoveProvided(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->provided, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_ComponentType(TypeDefinition* const this)
{
	ComponentType* pCompTypeObj;
	pCompTypeObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pCompTypeObj->required);
	hashmap_free(pCompTypeObj->provided);
	free(pCompTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(this);
}
void delete_ComponentType(ComponentType* const this)
{
	/* destroy base object */
	delete_TypeDefinition(this->super);
	/* destroy data memebers */
	hashmap_free(this->required);
	hashmap_free(this->provided);
	free(this);
}