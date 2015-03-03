#ifndef __DictionaryType_H
#define __DictionaryType_H

#include "hashmap.h"

typedef struct _DictionaryAttribute DictionaryAttribute;
typedef struct _DictionaryType DictionaryType;
typedef struct _Visitor Visitor;

typedef char* (*fptrDicTypeMetaClassName)(DictionaryType*);
typedef char* (*fptrDicTypeInternalGetKey)(DictionaryType*);
typedef void (*fptrDeleteDicType)(DictionaryType*);
typedef DictionaryAttribute* (*fptrDicTypeFindAttrByID)(DictionaryType*, char*);
typedef void (*fptrDicTypeAddAttr)(DictionaryType*, DictionaryAttribute*);
typedef void (*fptrDicTypeRemAttr)(DictionaryType*, DictionaryAttribute*);
typedef void (*fptrVisitAttrDicType)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsDicType)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathDicType)(char*, DictionaryType*);

typedef struct _DictionaryType {
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
	char generated_KMF_ID[9];
	map_t attributes;
	fptrDicTypeFindAttrByID FindAttributesByID;
	fptrDicTypeAddAttr AddAttributes;
	fptrDicTypeRemAttr RemoveAttributes;
} DictionaryType;

DictionaryType* new_DictionaryType(void);
void delete_DictionaryType(void* const this);
char* DictionaryType_internalGetKey(void* const this);
char* DictionaryType_metaClassName(void* const this);
DictionaryAttribute* DictionaryType_FindAttributesByID(DictionaryType* const this, char* id);
void DictionaryType_AddAttributes(DictionaryType* const this, DictionaryAttribute* ptr);
void DictionaryType_RemoveAttributes(DictionaryType* const this, DictionaryAttribute* ptr);
void DictionaryType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryType_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void DictionaryType_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* DictionaryType_FindByPath(char* attribute, void* const this);

#endif /* __DictionaryType_H */
