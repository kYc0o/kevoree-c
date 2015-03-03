#ifndef __TypedElement_H
#define __TypedElement_H

#include "hashmap.h"

typedef struct _TypedElement TypedElement;
typedef struct _NamedElement NamedElement;
typedef struct _Visitor Visitor;

typedef char* (*fptrTypElemMetaClassName)(TypedElement*);
typedef char* (*fptrTypElemInternalGetKey)(TypedElement*);
typedef TypedElement* (*fptrTypElemFindGenericTypesByID)(TypedElement*, char*);
typedef void (*fptrTypElemAddGenericTypes)(TypedElement*, TypedElement*);
typedef void (*fptrTypElemRemoveGenericTypes)(TypedElement*, TypedElement*);
typedef void (*fptrDeleteTypedElement)(TypedElement*);
typedef void (*fptrVisitAttrTypedElement)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsTypedElement)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathTypedElement)(char*, TypedElement*);

typedef struct _TypedElement {
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
	NamedElement* super;
	map_t genericTypes;
	fptrTypElemFindGenericTypesByID FindGenericTypesByID;
	fptrTypElemAddGenericTypes AddGenericTypes;
	fptrTypElemRemoveGenericTypes RemoveGenericTypes;
} TypedElement;

NamedElement* newPoly_TypedElement(void);
TypedElement* new_TypedElement(void);
char* TypedElement_metaClassName(void * const this);
char* TypedElement_internalGetKey(void * const this);
TypedElement* TypedElement_FindGenericTypesByID(TypedElement* const this, char* id);
void TypedElement_AddGenericTypes(TypedElement* const this, TypedElement* ptr);
void TypedElement_RemoveGenericTypes(TypedElement* const this, TypedElement* ptr);
void deletePoly_TypedElement(void * const this);
void delete_TypedElement(void * const this);
void TypedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypedElement_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypedElement_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void TypedElement_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* TypedElement_FindByPath(char* attribute, void * const this);

#endif /* __TypedElement_H */
