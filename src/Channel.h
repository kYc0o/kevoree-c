#ifndef __Channel_H
#define __Channel_H

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

typedef struct _MBinding MBinding;
typedef struct _Channel Channel;
typedef struct _Instance Instance;
typedef struct _Visitor Visitor;

typedef char* (*fptrChannelInternalGetKey)(Channel*);
typedef char* (*fptrChannelMetaClassName)(Channel*);
typedef void (*fptrChannelAddBindings)(Channel*, MBinding*);
typedef void (*fptrChannelRemoveBindings)(Channel*, MBinding*);
typedef MBinding* (*fptrChannelFindBindingsByID)(Channel*, char*);
typedef void (*fptrVisitAttrChannel)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsChannel)(void*, char*, Visitor*, bool);
typedef void* (*fptrFindByPathChannel)(char*, Channel*);
typedef void (*fptrDeleteChannel)(void*);

typedef struct _Channel {
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
	Instance *super;
	map_t bindings;
	fptrChannelFindBindingsByID FindBindingsByID;
	fptrChannelAddBindings AddBindings;
	fptrChannelRemoveBindings RemoveBindings;
} Channel;

Instance* newPoly_Channel(void);
Channel* new_Channel(void);
void deletePoly_Channel(void* const this);
void delete_Channel(void* const this);
char* Channel_metaClassName(void* const this);
char* Channel_internalGetKey(void* const this);
void Channel_AddBindings(Channel* const this, MBinding* ptr);
void Channel_RemoveBindings(Channel* const this, MBinding* ptr);
MBinding* Channel_FindBindingsByID(Channel* const this, char* id);
void Channel_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Channel_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Channel_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void Channel_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* Channel_FindByPath(char* attribute, void* const this);

#endif /*__Channel_H */
