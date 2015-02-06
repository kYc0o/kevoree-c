#ifndef __DictionaryAttribute_H
#define __DictionaryAttribute_H

#include <stdbool.h>

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
	TypedElement* super;
	bool optional;
	bool state;
	char *datatype;
	bool fragmentDependant;
	char *defaultValue;
	char *eContainer;
	fptrDicAttrInternalGetKey InternalGetKey;
	fptrDicAttrMetaClassName MetaClassName;
	fptrDeleteDicAttr Delete;
	fptrVisitAttrDicAttr VisitAttributes;
	fptrVisitAttrDicAttr VisitPathAttributes;
	fptrVisitRefsDicAttr VisitReferences;
	fptrVisitRefsDicAttr VisitPathReferences;
	fptrFindByPathDicAttr FindByPath;
} DictionaryAttribute;

TypedElement* newPoly_DictionaryAttribute(void);
DictionaryAttribute* new_DictionaryAttribute(void);
void deletePoly_DictionaryAttribute(void* const this);
void delete_DictionaryAttribute(void* const this);
char* DictionaryAttribute_InternalGetKey(DictionaryAttribute* const this);
char* DictionaryAttribute_MetaClassName(DictionaryAttribute* const this);
void DictionaryAttribute_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void DictionaryAttribute_VisitPathAttributes(void* const this, char* parent, Visitor* visitor);
void DictionaryAttribute_VisitReferences(void* const this, char* parent, Visitor* visitor);
void DictionaryAttribute_VisitPathReferences(void* const this, char* parent, Visitor* visitor);
void* DictionaryAttribute_FindByPath(char* attribute, DictionaryAttribute* const this);

#endif /* __DictionaryAttribute_H */
