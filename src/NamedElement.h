#ifndef H_NamedElement
#define H_NamedElement

#include <stdbool.h>
#include "tools.h"
#include "KMF4C.h"

typedef struct _NamedElement NamedElement;
typedef struct _Visitor Visitor;

typedef void (*fptrDeleteNamedElement)(NamedElement*);
typedef char* (*fptrNamedElementInternalGetKey)(NamedElement*);
typedef char* (*fptrNamedElementMetaClassName)(NamedElement*);
typedef void (*fptrVisitAttrNamedElement)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsNamedElement)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNamedElement)(char*, NamedElement*);

typedef struct _NamedElement {
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
	char* name;
}NamedElement;

NamedElement* new_NamedElement(void);
char* NamedElement_internalGetKey(void * const this);
char* NamedElement_metaClassName(void * const this);
void delete_NamedElement(void * const this);
void NamedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NamedElement_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void* NamedElement_FindByPath(char* attribute, void * const this);

#endif
