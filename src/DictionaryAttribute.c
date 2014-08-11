#include "DictionaryAttribute.h"

TypedElement* newPoly_DictionaryAttribute()
{
	DictionaryAttribute* pDicAttrObj = NULL;
	TypedElement* pObj = new_TypedElement();

	/* Allocating memory */
	pDicAttrObj = (DictionaryAttribute*)malloc(sizeof(DictionaryAttribute));

	if (pDicAttrObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pDicAttrObj; /* Pointing to derived object */
	((DictionaryAttribute*)pObj->pDerivedObj)->super = pObj;
	pObj->VisitAttributes = DictionaryAttribute_VisitAttributes;
	pObj->VisitReferences = DictionaryAttribute_VisitReferences;
	
	pObj->MetaClassName = DictionaryAttribute_MetaClassName;
	pObj->InternalGetKey = DictionaryAttribute_InternalGetKey;
	
	pDicAttrObj->optional = -1;
	pDicAttrObj->state = -1;
	pDicAttrObj->datatype = NULL;
	pDicAttrObj->fragmentDependant = -1;
	pDicAttrObj->defaultValue = NULL;
	
	pObj->FindByPath = DictionaryAttribute_FindByPath;
	
	pObj->Delete = deletePoly_DictionaryAttribute;

	return pObj;
}

DictionaryAttribute* new_DictionaryAttribute()
{
	DictionaryAttribute* pDicAttrObj = NULL;
	TypedElement* pObj = new_TypedElement();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pDicAttrObj = (DictionaryAttribute*)malloc(sizeof(DictionaryAttribute));

	if (pDicAttrObj == NULL)
	{
		return NULL;
	}

	pDicAttrObj->super = pObj;
	pDicAttrObj->VisitAttributes = DictionaryAttribute_VisitAttributes;
	pDicAttrObj->VisitReferences = DictionaryAttribute_VisitReferences;
	
	pDicAttrObj->optional = -1;
	pDicAttrObj->state = -1;
	pDicAttrObj->datatype = NULL;
	pDicAttrObj->fragmentDependant = -1;
	pDicAttrObj->defaultValue = NULL;
	
	pDicAttrObj->MetaClassName = DictionaryAttribute_MetaClassName;
	pDicAttrObj->InternalGetKey = DictionaryAttribute_InternalGetKey;
	pDicAttrObj->FindByPath = DictionaryAttribute_FindByPath;
	
	pDicAttrObj->Delete = delete_DictionaryAttribute;

	return pDicAttrObj;
}

void deletePoly_DictionaryAttribute(void* const this)
{
	if(this != NULL)
	{
		DictionaryAttribute* pDicAttrObj;
		pDicAttrObj = (DictionaryAttribute*)((TypedElement*)this)->pDerivedObj;
		/*destroy derived obj*/
		pDicAttrObj->optional = -1;
		pDicAttrObj->state = -1;
		free(pDicAttrObj->datatype);
		pDicAttrObj->fragmentDependant = -1;
		free(pDicAttrObj->defaultValue);
		free(pDicAttrObj);
		/*destroy base Obj*/
		delete_TypedElement(((TypedElement*)this));
	}
}

void delete_DictionaryAttribute(void* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_TypedElement(((DictionaryAttribute*)this)->super);
		/* destroy data memebers */
		DictionaryAttribute* pDicAttrObj = (DictionaryAttribute*)this;
		pDicAttrObj->optional = -1;
		pDicAttrObj->state = -1;
		free(pDicAttrObj->datatype);
		pDicAttrObj->fragmentDependant = -1;
		free(pDicAttrObj->defaultValue);
		free(this);
	}
}

char* DictionaryAttribute_InternalGetKey(DictionaryAttribute* const this)
{
	return TypedElement_InternalGetKey(this->super);
}

char* DictionaryAttribute_MetaClassName(DictionaryAttribute* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("DictionaryAttribute") + 1));
	strcpy(name, "DictionaryAttribute");
	
	return name;
}

void DictionaryAttribute_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
  
	/* TypedElement attributes */
	TypedElement_VisitAttributes(((DictionaryAttribute*)this)->super, parent, visitor);
	
	/* Local attributes */
	sprintf(path, "%s\\optional", parent);
	visitor->action(path, BOOL, ((DictionaryAttribute*)(this))->optional);
	sprintf(path, "%s\\state", parent);
	visitor->action(path, BOOL, ((DictionaryAttribute*)(this))->state);
	sprintf(path, "%s\\datatype", parent);
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->datatype);
	sprintf(path, "%s\\fragmentDependant", parent);
	visitor->action(path, BOOL, ((DictionaryAttribute*)(this))->fragmentDependant);
	sprintf(path, "%s\\defaultValue", parent);
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->defaultValue);
}

void DictionaryAttribute_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	TypedElement_VisitReferences(((DictionaryAttribute*)(this))->super, parent, visitor);
}

void* DictionaryAttribute_FindByPath(char* attribute, DictionaryAttribute* const this)
{
	/* TypedElement attributes and references */
	if(!strcmp("name", attribute) || !strcmp("genericTypes", attribute))
	{
		return TypedElement_FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("optional", attribute))
	{
		return this->optional;
	}
	else if(!strcmp("state", attribute))
	{
		return this->state;
	}
	else if(!strcmp("datatype", attribute))
	{
		return this->datatype;
	}
	else if(!strcmp("fragmentDependant", attribute))
	{
		return this->fragmentDependant;
	}
	else if(!strcmp("defaultValue", attribute))
	{
		return this->defaultValue;
	}
	/* There is no local references */
	else
	{
		printf("Wrong attribute or reference\n");
		return NULL;
	}
}