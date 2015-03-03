#ifndef __FragmentDictionary_H
#define __FragmentDictionary_H

#include <string.h>
#include "KMF4C.h"
/*#include "Dictionary.h"
#include "Instance.h"*/

typedef struct _FragmentDictionary FragmentDictionary;
typedef struct _Dictionary Dictionary;
/*typedef struct _Instance Instance;*/
typedef struct _Visitor Visitor;

typedef char* (*fptrFragDicMetaClassName)(FragmentDictionary*);
typedef char* (*fptrFragDicInternalGetKey)(FragmentDictionary*);
typedef void (*fptrDeleteFragDic)(void*);
typedef void (*fptrVisitAttrFragDic)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsFragDic)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathFragDic)(char*, FragmentDictionary*);

typedef struct _FragmentDictionary {
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
	Dictionary *super;
	char *name;
} FragmentDictionary;

Dictionary* newPoly_FragmentDictionary(void);
FragmentDictionary* new_FragmentDictionary(void);
void deletePoly_FragmentDictionary(void* const this);
void delete_FragmentDictionary(void* const this);
char* FragmentDictionary_internalGetKey(void* const this);
char* FragmentDictionary_metaClassName(void* const this);
void FragmentDictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void FragmentDictionary_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void FragmentDictionary_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void FragmentDictionary_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* FragmentDictionary_FindByPath(char* attribute, void* const this);

#endif /* __FragmentDictionary_H */
