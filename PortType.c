#include "PortType.h"

TypeDefinition* newPoly_PortType(void)
{
	PortType* pPortTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	/* Allocating memory */
	pPortTypeObj = (PortType*)malloc(sizeof(PortType));

	if (pPortTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pPortTypeObj; /* Pointing to derived object */

	pObj->MetaClassName = PortType_MetaClassName;
	pObj->InternalGetKey = PortType_InternalGetKey;
	
	pObj->Delete = deletePoly_PortType;

	return pObj;
}

PortType* new_PortType(void)
{
	PortType* pPortTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pPortTypeObj = (PortType*)malloc(sizeof(PortType));

	if (pPortTypeObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pPortTypeObj;  Pointing to derived object */
	pPortTypeObj->super = pObj;

	pPortTypeObj->MetaClassName = PortType_MetaClassName;
	pPortTypeObj->InternalGetKey = PortType_InternalGetKey;
	
	pPortTypeObj->Delete = delete_PortType;

	return pPortTypeObj;
}

char* PortType_MetaClassName(PortType* const this)
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

char* PortType_InternalGetKey(PortType* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("PortType") + 1));
	strcpy(name, "PortType");
	
	return name;
}

void deletePoly_PortType(TypeDefinition* const this)
{
	PortType* pPortTypeObj;
	pPortTypeObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pPortTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(this);
}

void delete_PortType(PortType* const this)
{
	/* destroy base object */
	delete_TypeDefinition(this->super);
	/* destroy data memebers */
	free(this);
}