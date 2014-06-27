#include "TypedElement.h"

NamedElement* newPoly_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeElemObj = (TypedElement*)malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeElemObj; /* Pointing to derived object */
	
	/*pTypeElemObj->genericTypes = hashmap_new();*/
	pTypeElemObj->genericTypes = NULL;
	
	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;
	
	pObj->MetaClassName = TypedElement_MetaClassName;
	pObj->InternalGetKey = TypedElement_InternalGetKey;
	pObj->Delete = deletePoly_TypedElement;
	pObj->VisitAttributes = TypedElement_VisitAttributes;

	return pObj;
}

TypedElement* new_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;
	
	/* Allocating memory */
	pTypeElemObj = (TypedElement*)malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pTypeElemObj;  Pointing to derived object */
	pTypeElemObj->super = pObj;
	
	/*pTypeElemObj->genericTypes = hashmap_new();*/
	pTypeElemObj->genericTypes = NULL;
	
	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;
	
	pTypeElemObj->MetaClassName = TypedElement_MetaClassName;
	pTypeElemObj->InternalGetKey = TypedElement_InternalGetKey;
	pTypeElemObj->Delete = delete_TypedElement;
	pTypeElemObj->VisitAttributes = TypedElement_VisitAttributes;

	return pTypeElemObj;
}

char* TypedElement_MetaClassName(TypedElement* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("TypedElement") + 1));
	strcpy(name, "TypedElement");
	
	return name;
}

char* TypedElement_InternalGetKey(TypedElement* const this)
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

TypedElement* TypedElement_FindGenericTypesByID(TypedElement* const this, char* id)
{
	TypedElement* value;

	if(hashmap_get(this->genericTypes, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

/*void TypedElement::addgenericTypes(TypedElement *ptr)*/
void TypedElement_AddGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	TypedElement* container = (TypedElement*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be added in TypedElement because the key is not defined");*/
		printf("The TypedElement cannot be added in TypedElement because the key is not defined");
	}
	else
	{
		/*if(genericTypes.find(container->internalGetKey()) == genericTypes.end())*/
		if(this->genericTypes == NULL)
		{
			this->genericTypes = hashmap_new();
		}
		if(hashmap_get(this->genericTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*genericTypes[container->internalGetKey()]=ptr;*/
			container = (TypedElement*)ptr;
			hashmap_put(this->genericTypes, container->InternalGetKey(container), ptr);
		}
	}
}

/*void TypedElement::removegenericTypes(TypedElement *ptr)*/
void TypedElement_RemoveGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	TypedElement* container = (TypedElement*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be removed in TypedElement because the key is not defined");*/
		printf("The TypedElement cannot be removed in TypedElement because the key is not defined\n");
	}
	else
	{
		/*genericTypes.erase( genericTypes.find(container->internalGetKey()));*/
		hashmap_remove(this->genericTypes, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_TypedElement(NamedElement* const this)
{
	TypedElement* pTypeElemObj;
	pTypeElemObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pTypeElemObj->genericTypes);
	free(pTypeElemObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_TypedElement(TypedElement* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->genericTypes);
	free(this);
}