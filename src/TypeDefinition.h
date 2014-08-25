#ifndef H_TypeDefinition
#define H_TypeDefinition

#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <string.h>
#include "DeployUnit.h"
#include "DictionaryType.h"
#include "NamedElement.h"
#include "hashmap.h"

typedef struct _TypeDefinition TypeDefinition;

/* Declaration of pointers to functions */
typedef char* (*fptrTypeDefInternalGetKey)(TypeDefinition*);
typedef void (*fptrTypeDefAddDeployUnit)(TypeDefinition*, DeployUnit*);
typedef void (*fptrTypeDefAddDictionaryType)(TypeDefinition*, DictionaryType*);
typedef void (*fptrTypeDefAddSuperTypes)(TypeDefinition*, TypeDefinition*);
typedef void (*fptrTypeDefRemoveDeployUnit)(TypeDefinition*, DeployUnit*);
typedef void (*fptrTypeDefRemoveDictionaryType)(TypeDefinition*, DictionaryType*);
typedef void (*fptrTypeDefRemoveSuperTypes)(TypeDefinition*, TypeDefinition*);
typedef char* (*fptrTypeDefMetaClassName)(TypeDefinition*);
typedef void (*fptrDeleteTypeDef)(TypeDefinition*);
typedef void (*fptrVisitAttrTypeDefinition)(void*, char*, Visitor*, int recursive);
typedef void (*fptrVisitRefsTypeDefinition)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathTypeDefinition)(char*, TypeDefinition*);

typedef struct _TypeDefinition {
	NamedElement* super;
	void* pDerivedObj;
	char* version;
	char* factoryBean;
	char* bean;
	int abstract;
	DeployUnit* deployUnits;
	DictionaryType* dictionaryType;
	map_t superTypes;
	fptrTypeDefInternalGetKey InternalGetKey;
	fptrTypeDefAddDeployUnit AddDeployUnit;
	fptrTypeDefAddDictionaryType AddDictionaryType;
	fptrTypeDefAddSuperTypes AddSuperTypes;
	fptrTypeDefRemoveDeployUnit RemoveDeployUnit;
	fptrTypeDefRemoveDictionaryType RemoveDictionaryType;
	fptrTypeDefRemoveSuperTypes RemoveSuperTypes;
	fptrTypeDefMetaClassName MetaClassName;
	fptrDeleteTypeDef Delete;
	fptrVisitAttrTypeDefinition VisitAttributes;
	fptrVisitRefsTypeDefinition VisitReferences;
	fptrFindByPathTypeDefinition FindByPath;
} TypeDefinition;

char* TypeDefinition_InternalGetKey(TypeDefinition* const this);
void TypeDefinition_AddDeployUnit(TypeDefinition* const this, DeployUnit *ptr);
void TypeDefinition_AddDictionaryType(TypeDefinition* const this, DictionaryType *ptr);
void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition *ptr);
void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit *ptr);
void TypeDefinition_RemoveDictionaryType(TypeDefinition* const this, DictionaryType *ptr);
void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition *ptr);
char* TypeDefinition_MetaClassName(TypeDefinition* const this);
NamedElement* newPoly_TypeDefinition(void);
TypeDefinition* new_TypeDefinition(void);
void deletePoly_TypeDefinition(NamedElement* const this);
void delete_TypeDefinition(TypeDefinition* const this);
void TypeDefinition_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive);
void TypeDefinition_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* TypeDefinition_FindByPath(char* attribute, TypeDefinition* const this);

#endif /* H_TypeDefinition */
