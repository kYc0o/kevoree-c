#ifndef __DictionaryAttribute_H
#define __DictionaryAttribute_H

#include <stdbool.h>
#include "KMF4C.h"

typedef struct _DictionaryAttribute DictionaryAttribute;
typedef struct _TypedElement TypedElement;
typedef struct _Visitor Visitor;

typedef char* (*fptrDicAttrMetaClassName)(DictionaryAttribute*);
typedef char* (*fptrDicAttrInternalGetKey)(DictionaryAttribute*);
typedef void (*fptrDeleteDicAttr)(void*);
typedef void (*fptrVisitAttrDicAttr)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsDicAttr)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathDicAttr)(char*, DictionaryAttribute*);

typedef struct _DictionaryAttribute {
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
	TypedElement* super;
	bool optional;
	bool state;
	char *datatype;
	bool fragmentDependant;
	char *defaultValue;
} DictionaryAttribute;

TypedElement* newPoly_DictionaryAttribute(void);
DictionaryAttribute* new_DictionaryAttribute(void);
void deletePoly_DictionaryAttribute(void* const this);
void delete_DictionaryAttribute(void* const this);
char* DictionaryAttribute_internalGetKey(void* const this);
char* DictionaryAttribute_metaClassName(void* const this);
void DictionaryAttribute_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryAttribute_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryAttribute_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryAttribute_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* DictionaryAttribute_FindByPath(char* attribute, void* const this);

#endif /* __DictionaryAttribute_H */
