#ifndef __FragmentDictionary_H
#define __FragmentDictionary_H

#include <string.h>
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
	Dictionary *super;
	char *name;
	char *eContainer;
	fptrFragDicInternalGetKey InternalGetKey;
	fptrFragDicMetaClassName MetaClassName;
	fptrDeleteFragDic Delete;
	fptrVisitAttrFragDic VisitAttributes;
	fptrVisitAttrFragDic VisitPathAttributes;
	fptrVisitRefsFragDic VisitReferences;
	fptrVisitRefsFragDic VisitPathReferences;
	fptrFindByPathFragDic FindByPath;
} FragmentDictionary;

Dictionary* newPoly_FragmentDictionary(void);
FragmentDictionary* new_FragmentDictionary(void);
void deletePoly_FragmentDictionary(void* const this);
void delete_FragmentDictionary(void* const this);
char* FragmentDictionary_InternalGetKey(FragmentDictionary* const this);
char* FragmentDictionary_MetaClassName(FragmentDictionary* const this);
void FragmentDictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void FragmentDictionary_VisitPathAttributes(void* const this, char* parent, Visitor* visitor);
void FragmentDictionary_VisitReferences(void* const this, char* parent, Visitor* visitor);
void FragmentDictionary_VisitPathReferences(void* const this, char* parent, Visitor* visitor);
void* FragmentDictionary_FindByPath(char* attribute, FragmentDictionary* const this);

#endif /* __FragmentDictionary_H */
