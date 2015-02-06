#ifndef H_NamedElement
#define H_NamedElement

#include <stdbool.h>
#include "tools.h"

typedef struct _NamedElement NamedElement;
typedef struct _Visitor Visitor;

typedef void (*fptrDeleteNamedElement)(NamedElement*);
typedef char* (*fptrNamedElementInternalGetKey)(NamedElement*);
typedef char* (*fptrNamedElementMetaClassName)(NamedElement*);
typedef void (*fptrVisitAttrNamedElement)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsNamedElement)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNamedElement)(char*, NamedElement*);

typedef struct _NamedElement {
	void* pDerivedObj;
	char* name;
	fptrNamedElementInternalGetKey InternalGetKey;
	fptrNamedElementMetaClassName MetaClassName;
	fptrDeleteNamedElement Delete;
	fptrVisitAttrNamedElement VisitAttributes;
	fptrVisitAttrNamedElement VisitPathAttributes;
	fptrVisitRefsNamedElement VisitReferences;
	fptrVisitRefsNamedElement VisitPathReferences;
	fptrFindByPathNamedElement FindByPath;
}NamedElement;

NamedElement* new_NamedElement(void);
char* NamedElement_InternalGetKey(NamedElement* const this);
char* NamedElement_MetaClassName(NamedElement* const this);
void delete_NamedElement(NamedElement*);
void NamedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NamedElement_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void* NamedElement_FindByPath(char* attribute, NamedElement* const this);

#endif
