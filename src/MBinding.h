#ifndef __MBinding_H
#define __MBinding_H

#include <stdbool.h>

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
	char generated_KMF_ID[9];
	Port* port;
	Channel* channel;
	char *eContainer;
	fptrMBindingInternalGetKey InternalGetKey;
	fptrMBindingMetaClassName MetaClassName;
	fptrMBindingAddPort AddPort;
	fptrMbindingAddHub AddHub;
	fptrMBindingRemovePort RemovePort;
	fptrMbindingRemoveHub RemoveHub;
	fptrVisitAttrMBinding VisitAttributes;
	fptrVisitAttrMBinding VisitPathAttributes;
	fptrVisitRefsMbinding VisitReferences;
	fptrVisitRefsMbinding VisitPathReferences;
	fptrFindByPathMBinding FindByPath;
	fptrDeleteMBinding Delete;
} MBinding;

MBinding* new_MBinding(void);
void delete_MBinding(void* const this);
char* MBinding_MetaClassName(MBinding* const this);
char* MBinding_InternalGetKey(MBinding* const this);
void MBinding_AddPort(MBinding* const this, Port* ptr);
void MBinding_AddHub(MBinding* const this, Channel* ptr);
void MBinding_RemovePort(MBinding* const this, Port* ptr);
void MBinding_RemoveHub(MBinding* const this, Channel* ptr);
void MBinding_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void MBinding_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void MBinding_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void MBinding_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* MBinding_FindByPath(char* attribute, MBinding* const this);

#endif /* __MBinding_H */
