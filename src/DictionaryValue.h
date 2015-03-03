#ifndef __DictionaryValue_H
#define __DictionaryValue_H

#include "KMF4C.h"

typedef struct _DictionaryValue DictionaryValue;
typedef struct _Visitor Visitor;

typedef char* (*fptrDicValMetaClassName)(DictionaryValue*);
typedef char* (*fptrDicValInternalGetKey)(DictionaryValue*);
typedef void (*fptrDeleteDicVal)(DictionaryValue*);
typedef void (*fptrVisitAttrDicVal)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathDicVal)(char*, DictionaryValue*);

typedef struct _DictionaryValue {
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
	char *name;
	char *value;
} DictionaryValue;

DictionaryValue* new_DictionaryValue(void);
void delete_DictionaryValue(void* const this);
char* DictionaryValue_internalGetKey(void* const this);
char* DictionaryValue_metaClassName(void* const this);
void DictionaryValue_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryValue_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void* DictionaryValue_FindByPath(char* attribute, void* const this);

#endif /* __DictionaryValue_H */
