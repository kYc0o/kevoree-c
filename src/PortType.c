#include <string.h>
#include <stdlib.h>
#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "PortType.h"

TypeDefinition* newPoly_PortType()
{
	PortType* pPortTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	/* Allocating memory */
	pPortTypeObj = (PortType*)my_malloc(sizeof(PortType));

	if (pPortTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pPortTypeObj; /* Pointing to derived object */
	pPortTypeObj->super = pObj;
	
	pPortTypeObj->synchrone = -1;

	pObj->super->MetaClassName = PortType_MetaClassName;
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
	pPortTypeObj = (PortType*)my_malloc(sizeof(PortType));

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
	char *name;

	name = my_malloc(sizeof(char) * (strlen("PortType")) + 1);
	if(name != NULL)
		strcpy(name, "PortType");
	else
		return NULL;
	
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

void PortType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	if(recursive)
	{
		PortType* porttype = ((TypeDefinition*)this)->pDerivedObj;

		char path[256];
		memset(&path[0], 0, sizeof(path));

		/*sprintf(path,"%s\\cClass", parent);
		visitor->action(path, STRING, ((TypeDefinition*)this)->MetaClassName((TypeDefinition*)this));*/

		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);

		/*sprintf(path, "%s\\synchrone", parent);*/
		sprintf(path, "synchrone");
		visitor->action(path, BOOL, (void*)porttype->synchrone);
		visitor->action(NULL, RETURN, NULL);
	}
	else
	{
		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
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
		return (void*)porttype->synchrone;
	}
	/* TypeDefinition references */
	else
	{
		return TypeDefinition_FindByPath(attribute, this);
	}
}
