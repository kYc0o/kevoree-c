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
	pPortTypeObj->super = pObj;
	
	pPortTypeObj->synchrone = -1;

	pObj->MetaClassName = PortType_MetaClassName;
	pObj->InternalGetKey = PortType_InternalGetKey;
	pObj->VisitAttributes = PortType_VisitAttributes;
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	pObj->FindByPath = PortType_FindByPath;
	
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

	pPortTypeObj->synchrone = -1;
	
	pPortTypeObj->MetaClassName = PortType_MetaClassName;
	pPortTypeObj->InternalGetKey = PortType_InternalGetKey;
	pPortTypeObj->VisitAttributes = PortType_VisitAttributes;
	pPortTypeObj->VisitReferences = TypeDefinition_VisitReferences;
	pPortTypeObj->FindByPath = PortType_FindByPath;
	
	pPortTypeObj->Delete = delete_PortType;

	return pPortTypeObj;
}

char* PortType_MetaClassName(PortType* const this)
{
	char name[9];
	memset(&name[0], 0, sizeof(name));

	/*name = malloc(sizeof(char) * (strlen("PortType") + 1));*/
	strcpy(name, "PortType");
	
	return name;
}

char* PortType_InternalGetKey(PortType* const this)
{
	return TypeDefinition_InternalGetKey((TypeDefinition*)this);
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

void PortType_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
	
	PortType* porttype = ((TypeDefinition*)this)->pDerivedObj;
	
	if(recursive)
	{
		sprintf(path, "%s\\synchrone", parent);
		visitor->action(path, BOOL, porttype->synchrone);
	}
}

void* PortType_FindByPath(char* attribute, TypeDefinition* const this)
{
	/* TypeDefinition attributes */
	if(!strcmp("name",attribute) ||  !strcmp("version",attribute) || !strcmp("factoryBean",attribute) || !strcmp("bean",attribute) || !strcmp("abstract",attribute))
	{
		return TypeDefinition_FindByPath(attribute, this);
	}
	/* Local attributes */
	else if(!strcmp("synchrone",attribute))
	{
		PortType* porttype = this->pDerivedObj;
		return porttype->synchrone;
	}
	/* TypeDefinition references */
	else
	{
		return TypeDefinition_FindByPath(attribute, this);
	}
}
