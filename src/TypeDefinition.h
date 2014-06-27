#ifndef H_TypeDefinition
#define H_TypeDefinition

#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <string.h>
#include "DeployUnit.h"
#include "NamedElement.h"
#include "hashmap.h"

typedef struct _TypeDefinition TypeDefinition;

/* Declaration of pointers to functions */
typedef char* (*fptrTypeDefInternalGetKey)(TypeDefinition*);
typedef void (*fptrTypeDefAddDeployUnit)(TypeDefinition*, DeployUnit*);
/*typedef void adddictionaryType(DictionaryType*);*/
typedef void (*fptrAddSuperTypes)(TypeDefinition*, TypeDefinition*);
typedef void (*fptrTypeDefRemoveDeployUnit)(TypeDefinition*, DeployUnit*);
/*typedef void removedictionaryType(DictionaryType *ptr);*/
typedef void (*fptrRemoveSuperTypes)(TypeDefinition*, TypeDefinition*);
typedef char* (*fptrTypeDefMetaClassName)(TypeDefinition*);
typedef void (*fptrDeleteTypeDef)(TypeDefinition*);
typedef void )(fptrVisitAttrTypeDefinition)(void*, char*, Visitor*);

typedef struct _TypeDefinition {
	NamedElement* super;
	void* pDerivedObj;
	char* version;
	char* factoryBean;
	char* bean;
	int abstract;
	DeployUnit* deployUnits;
	/*int count_typeDefinitions;
	TypeDefinition** superTypes;*/
	map_t superTypes;
	/*int (*accept)(struct _TypeDefinition*, struct _TypeDefinition*, Visitor*);*/
	fptrTypeDefInternalGetKey InternalGetKey;
	fptrTypeDefAddDeployUnit AddDeployUnit;
	fptrAddSuperTypes AddSuperTypes;
	fptrTypeDefRemoveDeployUnit RemoveDeployUnit;
	fptrRemoveSuperTypes RemoveSuperTypes;
	fptrTypeDefMetaClassName MetaClassName;
	fptrDeleteTypeDef Delete;
	fptrVisitAttrTypeDefinition VisitAttributes;
} TypeDefinition;

char* TypeDefinition_InternalGetKey(TypeDefinition* const this);
void TypeDefinition_AddDeployUnit(TypeDefinition* const this, DeployUnit *ptr);
/*void adddictionaryType(DictionaryType *ptr);*/
void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition *ptr);
void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit *ptr);
/*void removedictionaryType(DictionaryType *ptr);*/
void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition *ptr);
char* TypeDefinition_MetaClassName(TypeDefinition* const this);
NamedElement* newPoly_TypeDefinition(void);
TypeDefinition* new_TypeDefinition(void);
/*int _acceptTypeDefinition(TypeDefinition* this, TypeDefinition* c, Visitor* visitor);*/
void deletePoly_TypeDefinition(NamedElement* const this);
void delete_TypeDefinition(TypeDefinition* const this);
void TypeDefinition_VisitAttributes(void* const this, char* parent, Visitor* visitor);

#endif /* H_TypeDefinition */
