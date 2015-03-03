#ifndef H_TypeDefinition
#define H_TypeDefinition

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

typedef struct _TypeDefinition TypeDefinition;
typedef struct _DeployUnit DeployUnit;
typedef struct _NamedElement NamedElement;
typedef struct _DictionaryType DictionaryType;
typedef struct _Visitor Visitor;

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
typedef void (*fptrVisitAttrTypeDefinition)(void*, char*, Visitor*, bool recursive);
typedef void (*fptrVisitRefsTypeDefinition)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathTypeDefinition)(char*, TypeDefinition*);

typedef struct _TypeDefinition {
	void *pDerivedObj;
	char *eContainer;
	char *path;
	map_t refs;
	fptrKMFMetaClassName metaClassName;
	fptrKMFInternalGetKey internalGetKey;
	fptrVisitAttr VisitAttributes;
	fptrVisitAttr VisitPathAttributes;
	fptrVisitRefs VisitReferences;
	fptrVisitRefs VisitPathReferences;
	fptrFindByPath FindByPath;
	fptrDelete Delete;
	NamedElement *super;
	char *version;
	char *factoryBean;
	char *bean;
	bool abstract;
	char *internalKey;
	DeployUnit *deployUnits;
	DictionaryType *dictionaryType;
	map_t superTypes;
	fptrTypeDefAddDeployUnit AddDeployUnit;
	fptrTypeDefAddDictionaryType AddDictionaryType;
	fptrTypeDefAddSuperTypes AddSuperTypes;
	fptrTypeDefRemoveDeployUnit RemoveDeployUnit;
	fptrTypeDefRemoveDictionaryType RemoveDictionaryType;
	fptrTypeDefRemoveSuperTypes RemoveSuperTypes;
} TypeDefinition;

char* TypeDefinition_internalGetKey(void * const this);
void TypeDefinition_AddDeployUnit(TypeDefinition* const this, DeployUnit *ptr);
void TypeDefinition_AddDictionaryType(TypeDefinition* const this, DictionaryType *ptr);
void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition *ptr);
void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit *ptr);
void TypeDefinition_RemoveDictionaryType(TypeDefinition* const this, DictionaryType *ptr);
void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition *ptr);
char* TypeDefinition_metaClassName(void * const this);
NamedElement* newPoly_TypeDefinition(void);
TypeDefinition* new_TypeDefinition(void);
void deletePoly_TypeDefinition(void * const this);
void delete_TypeDefinition(void * const this);
void TypeDefinition_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypeDefinition_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypeDefinition_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypeDefinition_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* TypeDefinition_FindByPath(char* attribute, void * const this);

#endif /* H_TypeDefinition */
