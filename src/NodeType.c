#include "NodeType.h"
#include "TypeDefinition.h"
#include "NamedElement.h"

TypeDefinition* newPoly_NodeType()
{
	NodeType* pNodeTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	/* Allocating memory */
	pNodeTypeObj = (NodeType*)my_malloc(sizeof(NodeType));

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
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	
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
	pNodeTypeObj = (NodeType*)my_malloc(sizeof(NodeType));

	if (pNodeTypeObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNodeTypeObj;  Pointing to derived object */
	pNodeTypeObj->super = pObj;

	pNodeTypeObj->MetaClassName = NodeType_MetaClassName;
	pNodeTypeObj->InternalGetKey = NodeType_InternalGetKey;
	pNodeTypeObj->VisitAttributes = NodeType_VisitAttributes;
	pNodeTypeObj->VisitReferences = TypeDefinition_VisitAttributes;
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

	name = my_malloc(sizeof(char) * (strlen("NodeType")) + 1);
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

void NodeType_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	/*char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((TypeDefinition*)this)->MetaClassName((TypeDefinition*)this));*/

	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}
