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
	NamedElement* super;
	void* pDerivedObj;
	map_t genericTypes;
	char *eContainer;
	fptrTypElemMetaClassName MetaClassName;
	fptrTypElemInternalGetKey InternalGetKey;
	fptrTypElemFindGenericTypesByID FindGenericTypesByID;
	fptrTypElemAddGenericTypes AddGenericTypes;
	fptrTypElemRemoveGenericTypes RemoveGenericTypes;
	fptrDeleteTypedElement Delete;
	fptrVisitAttrTypedElement VisitAttributes;
	fptrVisitAttrTypedElement VisitPathAttributes;
	fptrVisitRefsTypedElement VisitReferences;
	fptrVisitRefsTypedElement VisitPathReferences;
	fptrFindByPathTypedElement FindByPath;
} TypedElement;

NamedElement* newPoly_TypedElement(void);
TypedElement* new_TypedElement(void);
char* TypedElement_MetaClassName(TypedElement* const this);
char* TypedElement_InternalGetKey(TypedElement* const this);
TypedElement* TypedElement_FindGenericTypesByID(TypedElement* const this, char* id);
void TypedElement_AddGenericTypes(TypedElement* const this, TypedElement* ptr);
void TypedElement_RemoveGenericTypes(TypedElement* const this, TypedElement* ptr);
void deletePoly_TypedElement(NamedElement* const this);
void delete_TypedElement(TypedElement* const this);
void TypedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void TypedElement_VisitPathAttributes(void* const this, char* parent, Visitor* visitor);
void TypedElement_VisitReferences(void* const this, char* parent, Visitor* visitor);
void TypedElement_VisitPathReferences(void* const this, char* parent, Visitor* visitor);
void* TypedElement_FindByPath(char* attribute, TypedElement* const this);

#endif /* __TypedElement_H */
