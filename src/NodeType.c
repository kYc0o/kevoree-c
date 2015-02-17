#include <string.h>
#include "NodeType.h"
#include "TypeDefinition.h"
#include "NamedElement.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

TypeDefinition* newPoly_NodeType()
{
	NodeType* pNodeTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	/* Allocating memory */
	pNodeTypeObj = (NodeType*)malloc(sizeof(NodeType));

	if (pNodeTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNodeTypeObj; /* Pointing to derived object */
	pNodeTypeObj->super = pObj;

	pObj->super->metaClassName = NodeType_metaClassName;
	pObj->internalGetKey = NodeType_internalGetKey;
	pObj->VisitAttributes = NodeType_VisitAttributes;
	pObj->VisitPathAttributes = NodeType_VisitPathAttributes;
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	pObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	
	pObj->Delete = deletePoly_NodeType;

	return pObj;
}

NodeType* new_NodeType()
{
	NodeType* pNodeTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pNodeTypeObj = (NodeType*)malloc(sizeof(NodeType));

	if (pNodeTypeObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNodeTypeObj;  Pointing to derived object */
	pNodeTypeObj->super = pObj;

	pNodeTypeObj->metaClassName = NodeType_metaClassName;
	pNodeTypeObj->internalGetKey = NodeType_internalGetKey;
	pNodeTypeObj->VisitAttributes = NodeType_VisitAttributes;
	pNodeTypeObj->VisitPathAttributes = NodeType_VisitPathAttributes;
	pNodeTypeObj->VisitReferences = TypeDefinition_VisitAttributes;
	pNodeTypeObj->VisitPathReferences = TypeDefinition_VisitPathAttributes;
	pNodeTypeObj->FindByPath = TypeDefinition_FindByPath;
	
	pNodeTypeObj->Delete = delete_NodeType;

	return pNodeTypeObj;
}

char* NodeType_internalGetKey(void* const this)
{
	return TypeDefinition_internalGetKey((TypeDefinition*)this);
}

char* NodeType_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("NodeType")) + 1);
	if(name != NULL)
		strcpy(name, "NodeType");
	else
		return NULL;
	
	return name;
}

void deletePoly_NodeType(void * const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	NodeType* pNodeTypeObj;
	pNodeTypeObj = pObj->pDerivedObj;
	/*destroy derived obj*/
	free(pNodeTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(this);
}

void delete_NodeType(void * const this)
{
	NodeType *pObj = (NodeType*)this;
	/* destroy base object */
	delete_TypeDefinition(pObj->super);
	/* destroy data memebers */
	free(pObj);
	
}

void NodeType_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}

void NodeType_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}
