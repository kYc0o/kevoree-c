#ifndef __Dictionary_H
#define __Dictionary_H

#include "hashmap.h"
#include "KMF4C.h"

typedef struct _DictionaryValue DictionaryValue;
typedef struct _Dictionary Dictionary;
typedef struct _Visitor Visitor;

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
	/*
	 * TODO fix size
	 */
	char generated_KMF_ID[33];
	map_t values;
	fptrDicoFindValuesByID FindValuesByID;
	fptrDicoAddValues AddValues;
	fptrDicoRemoveValues RemoveValues;
} Dictionary;

Dictionary* new_Dictionary(void);
void delete_Dictionary(void* const this);
DictionaryValue* Dictionary_FindValuesByID(Dictionary* const this, char* id);
void Dictionary_AddValues(Dictionary* const this, DictionaryValue* ptr);
void Dictionary_RemoveValues(Dictionary* const this, DictionaryValue* ptr);
char* Dictionary_internalGetKey(void* const this);
char* Dictionary_metaClassName(void* const this);
void Dictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Dictionary_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Dictionary_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void Dictionary_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* Dictionary_FindByPath(char* attribute, void* const this);

#endif /* __Dictionary_H */
