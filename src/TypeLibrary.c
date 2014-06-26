#include "TypeLibrary.h"

NamedElement* newPoly_TypeLibrary(void)
{
	TypeLibrary* pTypeLibObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeLibObj = (TypeLibrary*)malloc(sizeof(TypeLibrary));

	if (pTypeLibObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeLibObj; /* Pointing to derived object */
	
	/*pTypeLibObj->subTypes = hashmap_new();*/
	pTypeLibObj->subTypes = NULL;
	
	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;
	
	pObj->MetaClassName = TypeLibrary_MetaClassname;
	pObj->InternalGetKey = TypeLibrary_InternalGetKey;
	pObj->Delete = deletePoly_TypeLibrary;

	return pObj;
}

TypeLibrary* new_TypeLibrary(void)
{
	TypeLibrary* pTypeLibObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;
	
	/* Allocating memory */
	pTypeLibObj = (TypeLibrary*)malloc(sizeof(TypeLibrary));

	if (pTypeLibObj == NULL)
	{
		return NULL;
	}

	/* pObj->pDerivedObj = pTypeLibObj; Pointing to derived object */
	pTypeLibObj->super = pObj;
	
	/*pTypeLibObj->subTypes = hashmap_new();*/
	pTypeLibObj->subTypes = NULL;
	
	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;
	
	pTypeLibObj->MetaClassName = TypeLibrary_MetaClassname;
	pTypeLibObj->InternalGetKey = TypeLibrary_InternalGetKey;
	pTypeLibObj->Delete = delete_TypeLibrary;

	return pTypeLibObj;
}

char* TypeLibrary_MetaClassname(TypeLibrary* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("TypeLibrary") + 1));
	strcpy(name, "TypeLibrary");
	
	return name;
}

char* TypeLibrary_InternalGetKey(TypeLibrary* const this)
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

TypeDefinition* TypeLibrary_FindSubTypesByID(TypeLibrary* const this, char* id)
{
	TypeDefinition* value;

	if(hashmap_get(this->subTypes, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

/*void TypeLibrary::addsubTypes(TypeDefinition *ptr)*/
void TypeLibrary_AddSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be added in TypeLibrary because the key is not defined");*/
		printf("The TypeDefinition cannot be added in TypeLibrary because the key is not defined\n");
	}
	else
	{
		/*if(subTypes.find(container->internalGetKey()) == subTypes.end())*/
		if(this->subTypes == NULL)
		{
			this->subTypes = hashmap_new();
		}
		if(hashmap_get(this->subTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*subTypes[container->internalGetKey()]=ptr;*/
			container = (TypeDefinition*)ptr;
			hashmap_put(this->subTypes, container->InternalGetKey(container), ptr);
		}
	}
}

/*void TypeLibrary::removesubTypes(TypeDefinition *ptr)*/
void TypeLibrary_RemoveSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;

	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be removed in TypeLibrary because the key is not defined");*/
		printf("The TypeDefinition cannot be removed in TypeLibrary because the key is not defined\n");
	}
	else
	{
		/*subTypes.erase( subTypes.find(container->internalGetKey()));*/
		hashmap_remove(this->subTypes, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_TypeLibrary(NamedElement* const this)
{
	TypeLibrary* pTypeLibObj;
	pTypeLibObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pTypeLibObj->subTypes);
	free(pTypeLibObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_TypeLibrary(TypeLibrary* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->subTypes);
	free(this);
}