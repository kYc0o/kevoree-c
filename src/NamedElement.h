#ifndef H_NamedElement
#define H_NamedElement

#include <string.h>
#include <stdlib.h>
#include "tools.h"

typedef struct _NamedElement NamedElement;

typedef void (*fptrDeleteNamedElement)(NamedElement*);
typedef char* (*fptrNamedElementInternalGetKey)(NamedElement*);
typedef char* (*fptrNamedElementMetaClassName)(NamedElement*);

typedef struct _NamedElement {
	void* pDerivedObj;
	char* name;
	/*int (*accept)(struct _NamedElement*, struct _NamedElement*, Visitor*);*/
	fptrNamedElementInternalGetKey InternalGetKey;
	fptrNamedElementMetaClassName MetaClassName;
	fptrDeleteNamedElement Delete;
}NamedElement;

NamedElement* new_NamedElement(void);
char* NamedElement_InternalGetKey(NamedElement* const this);
char* NamedElement_MetaClassName(NamedElement* const this);
void delete_NamedElement(NamedElement*);

#endif