#include "TypeDefinition.h"

NamedElement* newPoly_TypeDefinition()
{
	TypeDefinition* pTypeDefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeDefObj = (TypeDefinition*)malloc(sizeof(TypeDefinition));

	if (pTypeDefObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeDefObj; /* Pointing to derived object */

	pTypeDefObj->deployUnits = NULL;
	/*pTypeDefObj->superTypes = hashmap_new();*/
	pTypeDefObj->superTypes = NULL;

	pTypeDefObj->AddDeployUnit = TypeDefinition_AddDeployUnit;
	pTypeDefObj->AddSuperTypes = TypeDefinition_AddSuperTypes;
	pTypeDefObj->RemoveDeployUnit = TypeDefinition_RemoveDeployUnit;
	pTypeDefObj->RemoveSuperTypes = TypeDefinition_RemoveSuperTypes;
	pObj->MetaClassName = TypeDefinition_MetaClassName;
	pObj->InternalGetKey = TypeDefinition_InternalGetKey;
	pObj->Delete = deletePoly_TypeDefinition;

	return pObj;
}

TypeDefinition* new_TypeDefinition()
{
	TypeDefinition* pTypeDefObj = NULL;
	NamedElement* pObj = new_NamedElement();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pTypeDefObj = (TypeDefinition*)malloc(sizeof(TypeDefinition));

	if (pTypeDefObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pTypeDefObj; Pointing to derived object */
	pTypeDefObj->super = pObj; /* Pointing to base object */
	

	pTypeDefObj->deployUnits = NULL;
	/*pTypeDefObj->superTypes = hashmap_new();*/
	pTypeDefObj->superTypes = NULL;

	pTypeDefObj->AddDeployUnit = TypeDefinition_AddDeployUnit;
	pTypeDefObj->AddSuperTypes = TypeDefinition_AddSuperTypes;
	pTypeDefObj->RemoveDeployUnit = TypeDefinition_RemoveDeployUnit;
	pTypeDefObj->RemoveSuperTypes = TypeDefinition_RemoveSuperTypes;
	pTypeDefObj->MetaClassName = TypeDefinition_MetaClassName;
	pTypeDefObj->InternalGetKey = TypeDefinition_InternalGetKey;
	pTypeDefObj->Delete = delete_TypeDefinition;

	return pTypeDefObj;
}

char* TypeDefinition_InternalGetKey(TypeDefinition* const this)
{
	char* internalKey;
	/*TypeDefinition* pChildTypeDef = (TypeDefinition*)pTypeDefObj->pDerivedObj;*/

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->name) + strlen("/") + strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->name);
	strcat(internalKey, "/");
	strcat(internalKey, this->version);

	return internalKey;
}

char* TypeDefinition_MetaClassName(TypeDefinition* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("TypeDefinition") + 1));
	strcpy(name, "TypeDefinition");
	
	return name;
}

void TypeDefinition_AddDeployUnit(TypeDefinition* const this, DeployUnit* ptr)
{
	this->deployUnits = ptr;
}

void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit* ptr)
{
	free(ptr);
}

void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;
	
	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypeDefinition cannot be added in TypeDefinition because the key is not defined\n");
	}
	else
	{
		/*if(superTypes.find(container->internalGetKey()) == superTypes.end())*/
		if(this->superTypes == NULL)
		{
			this->superTypes = hashmap_new();
		}
		if(hashmap_get(this->superTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*superTypes[container->internalGetKey()]=ptr;*/
			container = (TypeDefinition*)ptr;
			hashmap_put(this->superTypes, container->InternalGetKey(container), ptr);
		}
	}
}

void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
    TypeDefinition* container = (TypeDefinition*)ptr;
    
    /*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		printf("The TypeDefinition cannot be removed in TypeDefinition because the key is not defined\n");
	}
	else
	{
		/*superTypes.erase( superTypes.find(container->internalGetKey()));*/
		hashmap_remove(this->superTypes, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_TypeDefinition(NamedElement* const this)
{
	TypeDefinition* pTypeDefObj;
	pTypeDefObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pTypeDefObj->version);
	free(pTypeDefObj->deployUnits);
	hashmap_free(pTypeDefObj->superTypes);
	free(pTypeDefObj->superTypes);
	free(pTypeDefObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_TypeDefinition(TypeDefinition* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	free(this->version);
	free(this->deployUnits);
	hashmap_free(this->superTypes);
	free(this->superTypes);
	free(this);
	
}

/*int _acceptTypeDefinition(TypeDefinition* this, TypeDefinition* c, Visitor* visitor)
{
	int i;

	visitor->action((void*)this->version, (void*)c->version, 0);
	visitor->action((void*)this->abstract, (void*)c->abstract, 1);
	visitor->action((void*)this->deployUnits, (void*)c->deployUnits, 0);

	for(i = 0; i < this->count_superTypes; i++)
	{
		visitor->action((void*)this->superTypes, (void*)c->superTypes, 0);
	}
}*/