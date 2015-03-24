#include "NamedElement.h"
#include "TypedElement.h"
#include "DictionaryType.h"
#include "Visitor.h"
#include "DictionaryAttribute.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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
	pObj->VisitPathAttributes = DictionaryAttribute_VisitPathAttributes;
	pObj->VisitReferences = DictionaryAttribute_VisitReferences;
	pObj->VisitPathReferences = DictionaryAttribute_VisitPathReferences;
	
	pObj->metaClassName = DictionaryAttribute_metaClassName;
	pObj->internalGetKey = DictionaryAttribute_internalGetKey;
	
	pDicAttrObj->optional = -1;
	pDicAttrObj->state = -1;
	pDicAttrObj->datatype = NULL;
	pDicAttrObj->fragmentDependant = -1;
	pDicAttrObj->defaultValue = NULL;
	pDicAttrObj->eContainer = NULL;
	pDicAttrObj->path = NULL;
	
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
	pDicAttrObj->VisitPathAttributes = DictionaryAttribute_VisitPathAttributes;
	pDicAttrObj->VisitReferences = DictionaryAttribute_VisitReferences;
	pDicAttrObj->VisitPathReferences = DictionaryAttribute_VisitPathReferences;
	
	pDicAttrObj->optional = -1;
	pDicAttrObj->state = -1;
	pDicAttrObj->datatype = NULL;
	pDicAttrObj->fragmentDependant = -1;
	pDicAttrObj->defaultValue = NULL;
	pDicAttrObj->eContainer = NULL;
	pDicAttrObj->path = NULL;
	
	pDicAttrObj->metaClassName = DictionaryAttribute_metaClassName;
	pObj->super->metaClassName = DictionaryAttribute_metaClassName;
	pDicAttrObj->internalGetKey = DictionaryAttribute_internalGetKey;
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

char* DictionaryAttribute_internalGetKey(void* const this)
{
	DictionaryAttribute *pObj = (DictionaryAttribute*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* DictionaryAttribute_metaClassName(void* const this)
{
	DictionaryAttribute *pObj = (DictionaryAttribute*)this;
	char *name;

	name = malloc(sizeof(char) * (strlen("DictionaryAttribute")) + 1);
	if(name != NULL)
		strcpy(name, "DictionaryAttribute");
	else
		return NULL;
	
	return name;
}

void DictionaryAttribute_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* TypedElement attributes */
	TypedElement_VisitAttributes(((DictionaryAttribute*)this)->super, parent, visitor, recursive);
	
	/* Local attributes */
	sprintf(path, "optional");
	visitor->action(path, BOOL, (void*)((DictionaryAttribute*)(this))->optional);
	visitor->action(NULL, COLON, NULL);

	sprintf(path, "state");
	visitor->action(path, BOOL, (void*)((DictionaryAttribute*)(this))->state);
	visitor->action(NULL, COLON, NULL);

	sprintf(path, "datatype");
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->datatype);
	visitor->action(NULL, COLON, NULL);

	sprintf(path, "fragmentDependant");
	visitor->action(path, BOOL, (void*)((DictionaryAttribute*)(this))->fragmentDependant);
	visitor->action(NULL, COLON, NULL);

	sprintf(path, "defaultValue");
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->defaultValue);
	visitor->action(NULL, RETURN, NULL);
}

void DictionaryAttribute_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* TypedElement attributes */
	TypedElement_VisitPathAttributes(((DictionaryAttribute*)this)->super, parent, visitor, recursive);

	/* Local attributes */
	sprintf(path, "%s\\optional", parent);
	visitor->action(path, BOOL, (void*)((DictionaryAttribute*)(this))->optional);
	sprintf(path, "%s\\state", parent);
	visitor->action(path, BOOL, (void*)((DictionaryAttribute*)(this))->state);
	sprintf(path, "%s\\datatype", parent);
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->datatype);
	sprintf(path, "%s\\fragmentDependant", parent);
	visitor->action(path, BOOL, (void*)((DictionaryAttribute*)(this))->fragmentDependant);
	sprintf(path, "%s\\defaultValue", parent);
	visitor->action(path, STRING, ((DictionaryAttribute*)(this))->defaultValue);
}

void DictionaryAttribute_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	/*
	 * TODO create "this" object
	 */
	TypedElement_VisitReferences(((DictionaryAttribute*)(this))->super, parent, visitor, recursive);
}

void DictionaryAttribute_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	/*
	 * TODO create "this" object
	 */
	TypedElement_VisitPathReferences(((DictionaryAttribute*)(this))->super, parent, visitor, recursive);
}

void *DictionaryAttribute_FindByPath(char *attribute, void *const this)
{
	DictionaryAttribute *pObj = (DictionaryAttribute*)this;
	/* TypedElement attributes and references */
	if(!strcmp("name", attribute) || !strcmp("genericTypes", attribute))
	{
		return TypedElement_FindByPath(attribute, pObj->super);
	}
	/* Local attributes */
	else if(!strcmp("optional", attribute))
	{
		return (void*)pObj->optional;
	}
	else if(!strcmp("state", attribute))
	{
		return (void*)pObj->state;
	}
	else if(!strcmp("datatype", attribute))
	{
		return pObj->datatype;
	}
	else if(!strcmp("fragmentDependant", attribute))
	{
		return (void*)pObj->fragmentDependant;
	}
	else if(!strcmp("defaultValue", attribute))
	{
		return pObj->defaultValue;
	}
	/* There is no local references */
	else
	{
		PRINTF("Wrong attribute or reference\n");
		return NULL;
	}
}
