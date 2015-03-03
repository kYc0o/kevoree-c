#ifndef __MBinding_H
#define __MBinding_H

#include <stdbool.h>
#include "KMF4C.h"

typedef struct _Channel Channel;
typedef struct _Port Port;
typedef struct _MBinding MBinding;
typedef struct _Visitor Visitor;

typedef char* (*fptrMBindingInternalGetKey)(MBinding*);
typedef char* (*fptrMBindingMetaClassName)(MBinding*);
typedef void (*fptrMBindingAddPort)(MBinding*, Port*);
typedef void (*fptrMbindingAddHub)(MBinding*, Channel*);
typedef void (*fptrMBindingRemovePort)(MBinding*, Port*);
typedef void (*fptrMbindingRemoveHub)(MBinding*, Channel*);
typedef void (*fptrVisitAttrMBinding)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsMbinding)(void*, char*, Visitor*, bool);
typedef void* (*fptrFindByPathMBinding)(char*, MBinding*);
typedef void (*fptrDeleteMBinding)(void*);

typedef struct _MBinding {
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
	Port* port;
	Channel* channel;
	fptrMBindingAddPort AddPort;
	fptrMbindingAddHub AddHub;
	fptrMBindingRemovePort RemovePort;
	fptrMbindingRemoveHub RemoveHub;
} MBinding;

MBinding* new_MBinding(void);
void delete_MBinding(void * const this);
char* MBinding_metaClassName(void * const this);
char* MBinding_internalGetKey(void * const this);
void MBinding_AddPort(MBinding* const this, Port* ptr);
void MBinding_AddHub(MBinding* const this, Channel* ptr);
void MBinding_RemovePort(MBinding* const this, Port* ptr);
void MBinding_RemoveHub(MBinding* const this, Channel* ptr);
void MBinding_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void MBinding_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void MBinding_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void MBinding_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* MBinding_FindByPath(char* attribute, void * const this);

#endif /* __MBinding_H */
