#ifndef __DictionaryType_H
#define __DictionaryType_H

#include <string.h>
#include "hashmap.h"
#include "DictionaryAttribute.h"

typedef struct _DictionaryAttribute DictionaryAttribute;
typedef struct _DictionaryType DictionaryType;

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
	char* generated_KMF_ID;
	map_t attributes;
	fptrDicTypeFindAttrByID FindAttributesByID;
	fptrDicTypeAddAttr AddAttributes;
	fptrDicTypeRemAttr RemoveAttributes;
	fptrDicTypeInternalGetKey InternalGetKey;
	fptrDicTypeMetaClassName MetaClassName;
	fptrVisitAttrDicType VisitAttributes;
	fptrVisitRefsDicType VisitReferences;
	fptrFindByPathDicType FindByPath;
	fptrDeleteDicType Delete;
} DictionaryType;

DictionaryType* new_DictionaryType(void);
void delete_DictionaryType(DictionaryType* const this);
char* DictionaryType_InternalGetKey(DictionaryType* const this);
char* DictionaryType_MetaClassName(DictionaryType* const this);
DictionaryAttribute* DictionaryType_FindAttributesByID(DictionaryType* const this, char* id);
void DictionaryType_AddAttributes(DictionaryType* const this, DictionaryAttribute* ptr);
void DictionaryType_RemoveAttributes(DictionaryType* const this, DictionaryAttribute* ptr);
void DictionaryType_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void DictionaryType_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* DictionaryType_FindByPath(char* attribute, DictionaryType* const this);

#endif /* __DictionaryType_H */
