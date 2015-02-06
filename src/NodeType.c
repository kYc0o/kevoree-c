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

	pObj->super->MetaClassName = NodeType_MetaClassName;
	pObj->InternalGetKey = NodeType_InternalGetKey;
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

	pNodeTypeObj->MetaClassName = NodeType_MetaClassName;
	pNodeTypeObj->InternalGetKey = NodeType_InternalGetKey;
	pNodeTypeObj->VisitAttributes = NodeType_VisitAttributes;
	pNodeTypeObj->VisitPathAttributes = NodeType_VisitPathAttributes;
	pNodeTypeObj->VisitReferences = TypeDefinition_VisitAttributes;
	pNodeTypeObj->VisitPathReferences = TypeDefinition_VisitPathAttributes;
	pNodeTypeObj->FindByPath = TypeDefinition_FindByPath;
	
	pNodeTypeObj->Delete = delete_NodeType;

	return pNodeTypeObj;
}

char* NodeType_InternalGetKey(void* const this)
{
	return TypeDefinition_InternalGetKey((TypeDefinition*)this);
}

char* NodeType_MetaClassName(NodeType* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("NodeType")) + 1);
	if(name != NULL)
		strcpy(name, "NodeType");
	else
		return NULL;
	
	return name;
}

void deletePoly_NodeType(TypeDefinition* const this)
{
	NodeType* pNodeTypeObj;
	pNodeTypeObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pNodeTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(this);
}

void delete_NodeType(NodeType* const this)
{
	/* destroy base object */
	delete_TypeDefinition(this->super);
	/* destroy data memebers */
	free(this);
	
}

void NodeType_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}

void NodeType_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}
