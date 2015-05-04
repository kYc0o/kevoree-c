#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "GroupType.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

TypeDefinition* newPoly_GroupType()
{
	GroupType* pGroupTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pGroupTypeObj = (GroupType*)malloc(sizeof(GroupType));

	if (pGroupTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pGroupTypeObj; /* Pointing to derived object */

	pObj->super->metaClassName = GroupType_metaClassName;
	pObj->internalGetKey = GroupType_internalGetKey;
	pObj->VisitAttributes = GroupType_VisitAttributes;
	pObj->VisitPathAttributes = GroupType_VisitPathAttributes;
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	pObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	
	pObj->Delete = deletePoly_GroupType;

	return pObj;
}

GroupType* new_GroupType()
{
	GroupType* pGroupTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pGroupTypeObj = (GroupType*)malloc(sizeof(GroupType));

	if (pGroupTypeObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pGroupTypeObj;  Pointing to derived object */
	pGroupTypeObj->super = pObj;

	pGroupTypeObj->metaClassName = GroupType_metaClassName;
	pGroupTypeObj->internalGetKey = GroupType_internalGetKey;
	pGroupTypeObj->VisitAttributes = GroupType_VisitAttributes;
	pGroupTypeObj->VisitPathAttributes = GroupType_VisitPathAttributes;
	pGroupTypeObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	
	pGroupTypeObj->Delete = delete_GroupType;

	return pGroupTypeObj;
}

char* GroupType_metaClassName(void* const this)
{
	/*
	char *name;

	name = malloc(sizeof(char) * (strlen("GroupType")) + 1);
	if(name != NULL)
		strcpy(name, "GroupType");
	else
		return NULL;
	
	return name;
	*/
	return "GroupType";
}

char* GroupType_internalGetKey(void* const this)
{
	return TypeDefinition_internalGetKey((TypeDefinition*)this);
}

void deletePoly_GroupType(void* const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	GroupType* pGroupTypeObj;
	pGroupTypeObj = pObj->pDerivedObj;
	/*destroy derived obj*/
	free(pGroupTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(pObj);
}
void delete_GroupType(void* const this)
{
	GroupType *pObj = (GroupType*)this;
	/* destroy base object */
	delete_TypeDefinition(pObj->super);
	/* destroy data memebers */
	free(this);
}

void GroupType_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}

void GroupType_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}
