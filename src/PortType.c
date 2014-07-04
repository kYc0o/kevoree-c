#include "PortType.h"

TypeDefinition* newPoly_PortType()
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
	pObj->VisitAttributes = PortType_VisitAttributes;
	pObj->VisitReferences = TypeDefinition_VisitAttributes;
	
	pObj->Delete = deletePoly_PortType;

	return pObj;
}

PortType* new_PortType()
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
	pPortTypeObj->VisitAttributes = PortType_VisitAttributes;
	pPortTypeObj->VisitReferences = TypeDefinition_VisitAttributes;
	
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

void PortType_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s",parent, ((PortType*)(this))->super->super->name);

	/*sprintf(path,"%s\\name",parent);
	visitor->action(path, STRING, ((PortType*)(this))->super->super->name);*/
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), path, visitor);
	
	/*sprintf(path, "%s\\synchrone", parent);
	visitor->action(path, BOOL, ((PortType*)(this))->synchrone);*/
}