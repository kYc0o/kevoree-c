#ifndef __Channel_H
#define __Channel_H

#include <string.h>
#include "hashmap.h"

typedef struct _MBinding MBinding;
typedef struct _Channel Channel;
typedef struct _Instance Instance;
typedef struct _ContainerRoot ContainerRoot;
typedef struct _Visitor Visitor;

typedef char* (*fptrChannelInternalGetKey)(Channel*);
typedef char* (*fptrChannelMetaClassName)(Channel*);
typedef void (*fptrChannelAddBindings)(Channel*, MBinding*);
typedef void (*fptrChannelRemoveBindings)(Channel*, MBinding*);
typedef MBinding* (*fptrChannelFindBindingsByID)(Channel*, char*);
typedef void (*fptrVisitAttrChannel)(void*, char*, Visitor*, int);
typedef void (*fptrVisitRefsChannel)(void*, char*, Visitor*, int);
typedef void* (*fptrFindByPathChannel)(char*, Channel*);
typedef void (*fptrDeleteChannel)(void*);

typedef struct _Channel {
	Instance *super;
	map_t bindings;
	ContainerRoot *eContainer;
	fptrChannelMetaClassName MetaClassName;
	fptrChannelInternalGetKey InternalGetKey;
	fptrChannelFindBindingsByID FindBindingsByID;
	fptrChannelAddBindings AddBindings;
	fptrChannelRemoveBindings RemoveBindings;
	fptrVisitAttrChannel VisitAttributes;
	fptrVisitRefsChannel VisitReferences;
	fptrFindByPathChannel FindByPath;
	fptrDeleteChannel Delete;
} Channel;

Instance* newPoly_Channel(void);
Channel* new_Channel(void);
void deletePoly_Channel(void* const this);
void delete_Channel(void* const this);
char* Channel_MetaClassName(Channel* const this);
char* Channel_InternalGetKey(Channel* const this);
void Channel_AddBindings(Channel* const this, MBinding* ptr);
void Channel_RemoveBindings(Channel* const this, MBinding* ptr);
MBinding* Channel_FindBindingsByID(Channel* const this, char* id);
void Channel_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive);
void Channel_VisitReferences(void* const this, char* parent, Visitor* visitor, int recursive);
void* Channel_FindByPath(char* attribute, Channel* const this);

#endif /*__Channel_H */
