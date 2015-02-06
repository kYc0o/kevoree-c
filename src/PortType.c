#include <string.h>
#include <stdlib.h>
#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "PortType.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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

	pObj->super->MetaClassName = PortType_MetaClassName;
	pObj->InternalGetKey = PortType_InternalGetKey;
	pObj->VisitAttributes = PortType_VisitAttributes;
	pObj->VisitPathAttributes = PortType_VisitPathAttributes;
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	pObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
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

	pPortTypeObj->super = pObj;

	pPortTypeObj->synchrone = -1;
	
	pPortTypeObj->MetaClassName = PortType_MetaClassName;
	pPortTypeObj->InternalGetKey = PortType_InternalGetKey;
	pPortTypeObj->VisitAttributes = PortType_VisitAttributes;
	pPortTypeObj->VisitPathAttributes = PortType_VisitPathAttributes;
	pPortTypeObj->VisitReferences = TypeDefinition_VisitReferences;
	pPortTypeObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	pPortTypeObj->FindByPath = PortType_FindByPath;
	
	pPortTypeObj->Delete = delete_PortType;

	return pPortTypeObj;
}

char* PortType_MetaClassName(PortType* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("PortType")) + 1);
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

void PortType_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		PortType* porttype = ((TypeDefinition*)this)->pDerivedObj;

		char path[256];
		memset(&path[0], 0, sizeof(path));

		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);

		sprintf(path, "synchrone");
		visitor->action(path, BOOL, (void*)porttype->synchrone);
		visitor->action(NULL, RETURN, NULL);
	}
	else
	{
		TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
	}
}

void PortType_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		PortType* porttype = ((TypeDefinition*)this)->pDerivedObj;

		char path[256];
		memset(&path[0], 0, sizeof(path));

		TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);

		sprintf(path, "%s\\synchrone", parent);
		visitor->action(path, BOOL, (void*)(porttype->synchrone));
	}
	else
	{
		TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
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
