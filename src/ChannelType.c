#include "ChannelType.h"

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
	
	pChanTypeObj->lowerBindings = -1;
	pChanTypeObj->upperBindings = -1;
	pChanTypeObj->lowerFragments = -1;
	pChanTypeObj->upperFragments = -1;

	pObj->MetaClassName = ChannelType_MetaClassName;
	pObj->super->MetaClassName = ChannelType_MetaClassName;
	pObj->InternalGetKey = ChannelType_InternalGetKey;
	pObj->VisitAttributes = ChannelType_VisitAttributes;
	pObj->VisitReferences = ChannelType_VisitReferences;
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
	
	pChanTypeObj->lowerBindings = -1;
	pChanTypeObj->upperBindings = -1;
	pChanTypeObj->lowerFragments = -1;
	pChanTypeObj->upperFragments = -1;

	pChanTypeObj->MetaClassName = ChannelType_MetaClassName;
	pChanTypeObj->InternalGetKey = ChannelType_InternalGetKey;
	pChanTypeObj->VisitAttributes = ChannelType_VisitAttributes;
	pChanTypeObj->VisitReferences = ChannelType_VisitReferences;
	
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

char* ChannelType_InternalGetKey(void* const this)
{
	if (this == NULL)
		return NULL;
	
	return TypeDefinition_InternalGetKey((TypeDefinition*)this);
}

char* ChannelType_MetaClassName(ChannelType* const this)
{
	char *name = NULL;

	name = malloc(sizeof(char) * (strlen("ChannelType")) + 1);
	if(name != NULL)
		strcpy(name, "ChannelType");
	else
		return NULL;
	
	return name;
}

void ChannelType_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	/* Local attributes */
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		/*sprintf(path,"%s\\cClass", parent);
		visitor->action(path, STRING, ((TypeDefinition*)this)->MetaClassName((TypeDefinition*)this));*/

		/* TypeDefinition attributes */
		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);

		/*sprintf(path, "%s\\lowerBindings", parent);*/
		sprintf(path, "lowerBindings");
		visitor->action(path, BOOL, ((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->lowerBindings);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path, "%s\\upperBindings", parent);*/
		sprintf(path, "upperBindings");
		visitor->action(path, BOOL, ((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->upperBindings);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path, "%s\\lowerFragments", parent);*/
		sprintf(path, "lowerFragments");
		visitor->action(path, BOOL, ((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->lowerFragments);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path, "%s\\upperFragments", parent);*/
		sprintf(path, "upperFragments", parent);
		visitor->action(path, BOOL, ((ChannelType*)(((TypeDefinition*)this)->pDerivedObj))->upperFragments);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		/* TypeDefinition attributes */
		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
	}
}

void ChannelType_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	TypeDefinition_VisitReferences((TypeDefinition*)this, parent, visitor);
}

void* ChannelType_FindByPath(char* attribute, TypeDefinition* const this)
{
	/* TypeDefinition attributes */
	if(!strcmp("name",attribute) ||  !strcmp("version",attribute) || !strcmp("factoryBean",attribute) || !strcmp("bean",attribute) || !strcmp("abstract",attribute))
	{
		return TypeDefinition_FindByPath(attribute, this);
	}
	/* Local attributes */
	else if(!strcmp("lowerBindings",attribute))
	{
		return ((ChannelType*)this->pDerivedObj)->lowerBindings;
	}
	else if(!strcmp("upperBindings",attribute))
	{
		return ((ChannelType*)this->pDerivedObj)->upperBindings;
	}
	else if(!strcmp("lowerFragments",attribute))
	{
		return ((ChannelType*)this->pDerivedObj)->lowerFragments;
	}
	else if(!strcmp("upperFragments",attribute))
	{
		return ((ChannelType*)this->pDerivedObj)->upperFragments;
	}
	/* TypeDefinition references */
	else
	{
		return TypeDefinition_FindByPath(attribute, this);
	}
}
