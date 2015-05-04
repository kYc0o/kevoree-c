#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "ChannelType.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

TypeDefinition* newPoly_ChannelType()
{
	ChannelType* pChanTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pChanTypeObj = (ChannelType*)malloc(sizeof(ChannelType));

	if (pChanTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pChanTypeObj; /* Pointing to derived object */
	pChanTypeObj->super = pObj;
	
	pChanTypeObj->path = NULL;
	pChanTypeObj->eContainer = NULL;
	pChanTypeObj->refs = NULL;
	pChanTypeObj->lowerBindings = -1;
	pChanTypeObj->upperBindings = -1;
	pChanTypeObj->lowerFragments = -1;
	pChanTypeObj->upperFragments = -1;

	pObj->metaClassName = ChannelType_metaClassName;
	pObj->super->metaClassName = ChannelType_metaClassName;
	pObj->internalGetKey = ChannelType_internalGetKey;
	pObj->VisitAttributes = ChannelType_VisitAttributes;
	pObj->VisitPathAttributes = ChannelType_VisitPathAttributes;
	pObj->VisitReferences = ChannelType_VisitReferences;
	pObj->VisitPathReferences = ChannelType_VisitPathReferences;
	pObj->FindByPath = ChannelType_FindByPath;
	
	pObj->Delete = deletePoly_ChannelType;

	return pObj;
}

ChannelType* new_ChannelType()
{
	ChannelType* pChanTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pChanTypeObj = (ChannelType*)malloc(sizeof(ChannelType));

	if (pChanTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	/*pObj->pDerivedObj = pChanTypeObj;  Pointing to derived object */
	pObj->pDerivedObj = NULL;
	pChanTypeObj->super = pObj;
	
	pChanTypeObj->eContainer = NULL;
	pChanTypeObj->path = NULL;
	pChanTypeObj->refs = NULL;
	pChanTypeObj->lowerBindings = -1;
	pChanTypeObj->upperBindings = -1;
	pChanTypeObj->lowerFragments = -1;
	pChanTypeObj->upperFragments = -1;

	pChanTypeObj->metaClassName = ChannelType_metaClassName;
	pChanTypeObj->internalGetKey = ChannelType_internalGetKey;
	pChanTypeObj->VisitAttributes = ChannelType_VisitAttributes;
	pChanTypeObj->VisitPathAttributes = ChannelType_VisitPathAttributes;
	pChanTypeObj->VisitReferences = ChannelType_VisitReferences;
	pChanTypeObj->VisitPathReferences = ChannelType_VisitPathReferences;
	
	pChanTypeObj->Delete = delete_ChannelType;

	return pChanTypeObj;
}

void deletePoly_ChannelType(void* const this)
{
	if(this != NULL)
	{
		ChannelType* pChanTypeObj;
		pChanTypeObj = (ChannelType*)((TypeDefinition*)this)->pDerivedObj;
		/*destroy derived obj*/
		free(pChanTypeObj);
		/*destroy base Obj*/
		delete_TypeDefinition((TypeDefinition*)this);
	}
}

void delete_ChannelType(void* const this)
{
	/* destroy base object */
	delete_TypeDefinition(((ChannelType*)this)->super);
	/* destroy data memebers */
	free(this);
}

char* ChannelType_internalGetKey(void* const this)
{
	if (this == NULL)
		return NULL;
	
	return TypeDefinition_internalGetKey((TypeDefinition*)this);
}

char* ChannelType_metaClassName(void* const this)
{
	/*ChannelType *pObj = (ChannelType*)this;
	char *name = NULL;

	name = malloc(sizeof(char) * (strlen("ChannelType")) + 1);
	if(name != NULL)
		strcpy(name, "ChannelType");
	else
		return NULL;
	
	return name;
	*/
	return "ChannelType";
}

void ChannelType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	/* Local attributes */
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		/* TypeDefinition attributes */
		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);

		sprintf(path, "lowerBindings");
		visitor->action(path, INTEGER, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->lowerBindings);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "upperBindings");
		visitor->action(path, INTEGER, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->upperBindings);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "lowerFragments");
		visitor->action(path, INTEGER, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->lowerFragments);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "upperFragments");
		visitor->action(path, INTEGER, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->upperFragments);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		/* TypeDefinition attributes */
		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
	}
}

void ChannelType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	/* Local attributes */
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		/* TypeDefinition attributes */
		TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);

		sprintf(path, "%s\\lowerBindings", parent);
		visitor->action(path, BOOL, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->lowerBindings);
		sprintf(path, "%s\\upperBindings", parent);
		visitor->action(path, BOOL, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->upperBindings);
		sprintf(path, "%s\\lowerFragments", parent);
		visitor->action(path, BOOL, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->lowerFragments);
		sprintf(path, "%s\\upperFragments", parent);
		visitor->action(path, BOOL, (void*)((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->upperFragments);
	}
	else
	{
		/* TypeDefinition attributes */
		TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
	}
}

void ChannelType_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	TypeDefinition_VisitReferences((TypeDefinition*)this, parent, visitor, recursive);
}

void ChannelType_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	TypeDefinition_VisitPathReferences((TypeDefinition*)this, parent, visitor, recursive);
}

void* ChannelType_FindByPath(char* attribute, void* const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	/*
	 * TODO Fix polymorphism
	 */
	/* TypeDefinition attributes */
	if(!strcmp("name",attribute) ||  !strcmp("version",attribute) || !strcmp("factoryBean",attribute) || !strcmp("bean",attribute) || !strcmp("abstract",attribute))
	{
		return TypeDefinition_FindByPath(attribute, pObj);
	}
	/* Local attributes */
	else if(!strcmp("lowerBindings",attribute))
	{
		return (void*)((ChannelType*)pObj->pDerivedObj)->lowerBindings;
	}
	else if(!strcmp("upperBindings",attribute))
	{
		return (void*)((ChannelType*)pObj->pDerivedObj)->upperBindings;
	}
	else if(!strcmp("lowerFragments",attribute))
	{
		return (void*)((ChannelType*)pObj->pDerivedObj)->lowerFragments;
	}
	else if(!strcmp("upperFragments",attribute))
	{
		return (void*)((ChannelType*)pObj->pDerivedObj)->upperFragments;
	}
	/* TypeDefinition references */
	else
	{
		return TypeDefinition_FindByPath(attribute, pObj);
	}
}
