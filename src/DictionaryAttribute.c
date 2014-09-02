#include "NamedElement.h"
#include "TypedElement.h"
#include "DictionaryType.h"
#include "Visitor.h"
#include "DictionaryAttribute.h"

TypedElement* newPoly_DictionaryAttribute()
{
	DictionaryAttribute* pDicAttrObj = NULL;
	TypedElement* pObj = new_TypedElement();

	/* Allocating memory */
	pDicAttrObj = (DictionaryAttribute*)my_malloc(sizeof(DictionaryAttribute));

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
	pDicAttrObj->eContainer = NULL;
	
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
	pDicAttrObj = (DictionaryAttribute*)my_malloc(sizeof(DictionaryAttribute));

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
	pDicAttrObj->eContainer = NULL;
	
	pDicAttrObj->MetaClassName = DictionaryAttribute_MetaClassName;
	pObj->super->MetaClassName = DictionaryAttribute_MetaClassName;
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
		free(pDicAttrObj->eContainer);
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
		free(pDicAttrObj->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* DictionaryAttribute_InternalGetKey(DictionaryAttribute* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* DictionaryAttribute_MetaClassName(DictionaryAttribute* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("DictionaryAttribute")) + 1);
	if(name != NULL)
		strcpy(name, "DictionaryAttribute");
	else
		return NULL;
	
	return name;
}

void DictionaryAttribute_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((DictionaryAttribute*)this)->MetaClassName((DictionaryAttribute*)this));*/

	/* TypedElement attributes */
	TypedElement_VisitAttributes(((DictionaryAttribute*)this)->super, parent, visitor);
	
	/* Local attributes */
	/*sprintf(path, "%s\\optional", parent);*/
	sprintf(path, "optional");
	visitor->action(path, BOOL, ((DictionaryAttribute*)(this))->optional);
	visitor->action(NULL, COLON, NULL);

	/*sprintf(path, "%s\\state", parent);*/
	sprintf(path, "state");
	visitor->action(path, BOOL, ((DictionaryAttribute*)(this))->state);
	visitor->action(NULL, COLON, NULL);

	/*sprintf(path, "%s\\datatype", parent);*/
	sprintf(path, "datatype");
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->datatype);
	visitor->action(NULL, COLON, NULL);

	/*sprintf(path, "%s\\fragmentDependant", parent);*/
	sprintf(path, "fragmentDependant");
	visitor->action(path, BOOL, ((DictionaryAttribute*)(this))->fragmentDependant);
	visitor->action(NULL, COLON, NULL);

	/*sprintf(path, "%s\\defaultValue", parent);*/
	sprintf(path, "defaultValue");
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->defaultValue);
	visitor->action(NULL, RETURN, NULL);
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
