#include "NodeType.h"

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

	pObj->MetaClassName = NodeType_MetaClassName;
	pObj->InternalGetKey = NodeType_InternalGetKey;
	
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
	
	pNodeTypeObj->Delete = delete_NodeType;

	return pNodeTypeObj;
}

char* NodeType_InternalGetKey(NodeType* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->super->name) + strlen("/") + strlen(this->super->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->super->name);
	strcat(internalKey, "/");
	strcat(internalKey, this->super->version);

	return internalKey;
}

char* NodeType_MetaClassName(NodeType* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NodeType") + 1));
	strcpy(name, "NodeType");
	
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