#ifndef __TypeLibrary_H
#define __TypeLibrary_H

#include "hashmap.h"

typedef struct _TypeLibrary TypeLibrary;
typedef struct _NamedElement NamedElement;
typedef struct _TypeDefinition TypeDefinition;

typedef char* (*fptrTypeLibMetaClassName)(TypeLibrary*);
typedef char* (*fptrTypeLibInternalGetKey)(TypeLibrary*);
typedef TypeDefinition* (*fptrTypeLibFindSubTypesByID)(TypeLibrary*, char*);
typedef void (*fptrTypeLibAddSubTypes)(TypeLibrary*, TypeDefinition*);
typedef void (*fptrTypeLibRemoveSubTypes)(TypeLibrary*, TypeDefinition*);
typedef void (*fptrDeleteTypeLib)(TypeLibrary*);
typedef void (*fptrVisitAttrTypeLib)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsTypeLib)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathTypeLibrary)(char*, TypeLibrary*);

typedef struct _TypeLibrary {
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
	map_t subTypes;
	fptrTypeLibFindSubTypesByID FindSubTypesByID;
	fptrTypeLibAddSubTypes AddSubTypes;
	fptrTypeLibRemoveSubTypes RemoveSubTypes;
} TypeLibrary;

NamedElement* newPoly_TypeLibrary(void);
TypeLibrary* new_TypeLibrary(void);
char* TypeLibrary_metaClassName(void * const this);
char* TypeLibrary_internalGetKey(void * const this);
TypeDefinition* TypeLibrary_FindSubTypesByID(TypeLibrary* const this, char* id);
void TypeLibrary_AddSubTypes(TypeLibrary* const this, TypeDefinition* ptr);
void TypeLibrary_RemoveSubTypes(TypeLibrary* const this, TypeDefinition* ptr);
void deletePoly_TypeLibrary(void * const this);
void delete_TypeLibrary(void * const this);
void TypeLibrary_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypeLibrary_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypeLibrary_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypeLibrary_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* TypeLibrary_FindByPath(char* attribute, void * const this);

#endif /* __TypeLibrary_H */
