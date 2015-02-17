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

	pObj->super->metaClassName = PortType_metaClassName;
	pObj->internalGetKey = PortType_internalGetKey;
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
	
	pPortTypeObj->metaClassName = PortType_metaClassName;
	pPortTypeObj->internalGetKey = PortType_internalGetKey;
	pPortTypeObj->VisitAttributes = PortType_VisitAttributes;
	pPortTypeObj->VisitPathAttributes = PortType_VisitPathAttributes;
	pPortTypeObj->VisitReferences = TypeDefinition_VisitReferences;
	pPortTypeObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	pPortTypeObj->FindByPath = PortType_FindByPath;
	
	pPortTypeObj->Delete = delete_PortType;

	return pPortTypeObj;
}

char* PortType_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("PortType")) + 1);
	if(name != NULL)
		strcpy(name, "PortType");
	else
		return NULL;
	
	return name;
}

char* PortType_internalGetKey(void * const this)
{
	return TypeDefinition_internalGetKey((TypeDefinition*)this);
}

void deletePoly_PortType(void * const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	PortType* pPortTypeObj;
	pPortTypeObj = pObj->pDerivedObj;
	/*destroy derived obj*/
	free(pPortTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(pObj);
}

void delete_PortType(void * const this)
{
	PortType *pObj = (PortType*)this;
	/* destroy base object */
	delete_TypeDefinition(pObj->super);
	/* destroy data memebers */
	free(pObj);
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

void* PortType_FindByPath(char* attribute, void * const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	/* TypeDefinition attributes */
	if(!strcmp("name",attribute) ||  !strcmp("version",attribute) || !strcmp("factoryBean",attribute) || !strcmp("bean",attribute) || !strcmp("abstract",attribute))
	{
		return TypeDefinition_FindByPath(attribute, pObj);
	}
	/* Local attributes */
	else if(!strcmp("synchrone", attribute))
	{
		PortType* porttype = pObj->pDerivedObj;
		return (void*)porttype->synchrone;
	}
	/* TypeDefinition references */
	else
	{
		return TypeDefinition_FindByPath(attribute, pObj);
	}
}
