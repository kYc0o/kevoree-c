#ifndef __DictionaryValue_H
#define __DictionaryValue_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*#include "Visitor.h"
#include "Dictionary.h"*/

typedef struct _DictionaryValue DictionaryValue;
typedef struct _Dictionary Dictionary;
typedef struct _Visitor Visitor;

typedef char* (*fptrDicValMetaClassName)(DictionaryValue*);
typedef char* (*fptrDicValInternalGetKey)(DictionaryValue*);
typedef void (*fptrDeleteDicVal)(DictionaryValue*);
typedef void (*fptrVisitAttrDicVal)(void*, char*, Visitor*);
/*typedef void (*fptrVisitRefsDicVal)(void*, char*, Visitor*);*/
typedef void* (*fptrFindByPathDicVal)(char*, DictionaryValue*);

typedef struct _DictionaryValue {
	char *name;
	char *value;
	Dictionary *eContainer;
	fptrDicValInternalGetKey InternalGetKey;
	fptrDicValMetaClassName MetaClassName;
	fptrDeleteDicVal Delete;
	fptrVisitAttrDicVal VisitAttributes;
	/*fptrVisitRefsDicVal VisitReferences;*/
	fptrFindByPathDicVal FindByPath;
} DictionaryValue;

DictionaryValue* new_DictionaryValue(void);
void delete_DictionaryValue(DictionaryValue* const this);
char* DictionaryValue_InternalGetKey(DictionaryValue* const this);
char* DictionaryValue_MetaClassName(DictionaryValue* const this);
void DictionaryValue_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void* DictionaryValue_FindByPath(char* attribute, DictionaryValue* const this);

#endif /* __DictionaryValue_H */
