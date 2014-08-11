#ifndef __Dictionary_H
#define __Dictionary_H

#include <string.h>
#include "tools.h"
#include "hashmap.h"
#include "Visitor.h"
#include "DictionaryValue.h"

typedef struct _DictionaryValue DictionaryValue;
typedef struct _Dictionary Dictionary;

typedef char* (*fptrDicoMetaClassName)(Dictionary*);
typedef char* (*fptrDicoInternalGetKey)(Dictionary*);
typedef void (*fptrDicoAddValues)(Dictionary*, DictionaryValue*);
typedef void (*fptrDicoRemoveValues)(Dictionary*, DictionaryValue*);
typedef DictionaryValue* (*fptrDicoFindValuesByID)(Dictionary*, char*);
typedef void (*fptrDeleteDictionary)(Dictionary*);
typedef void (*fptrVisitAttrDico)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsDico)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathDictionary)(char*, Dictionary*);

typedef struct _Dictionary {
	void* pDerivedObj;
	char* generated_KMF_ID;
	map_t values;
	fptrDicoFindValuesByID FindValuesByID;
	fptrDicoAddValues AddValues;
	fptrDicoRemoveValues RemoveValues;
	fptrDicoInternalGetKey InternalGetKey;
	fptrDicoMetaClassName MetaClassName;
	fptrDeleteDictionary Delete;
	fptrVisitAttrDico VisitAttributes;
	fptrVisitRefsDico VisitReferences;
	fptrFindByPathDictionary FindByPath;
} Dictionary;

Dictionary* new_Dictionary(void);
void delete_Dictionary(Dictionary* const this);
DictionaryValue* Dictionary_FindValuesByID(Dictionary* const this, char* id);
void Dictionary_AddValues(Dictionary* const this, DictionaryValue* ptr);
void Dictionary_RemoveValues(Dictionary* const this, DictionaryValue* ptr);
char* Dictionary_InternalGetKey(Dictionary* const this);
char* Dictionary_MetaClassName(Dictionary* const this);
void Dictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void Dictionary_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* Dictionary_FindByPath(char* attribute, Dictionary* const this);

#endif /* __Dictionary_H */
