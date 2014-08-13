#ifndef __Port_H
#define __Port_H

#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "Visitor.h"
#include "MBinding.h"
#include "PortTypeRef.h"

typedef struct _MBinding MBinding;
typedef struct _PortTypeRef PortTypeRef;
typedef struct _Port Port;

typedef char* (*fptrPortInternalGetKey)(Port*);
typedef char* (*fptrPortMetaClassName)(Port*);
typedef MBinding* (*fptrPortFindBindingsByID)(Port*, char*);
typedef void (*fptrPortAddBindings)(Port*, MBinding*);
typedef void (*fptrPortAddPortTypeRef)(Port*, PortTypeRef*);
typedef void (*fptrPortRemoveBindings)(Port*, MBinding*);
typedef void (*fptrPortRemovePortTypeRef)(Port*, PortTypeRef*);
typedef void (*fptrVisitAttrPort)(Port*, char*, Visitor*);
typedef void (*fptrVisitRefsPort)(Port*, char*, Visitor*);
typedef void* (*fptrFindByPathPort)(char*, Port*);
typedef void (*fptrDeletePort)(void*);

typedef struct _Port {
	char* generated_KMF_ID;
	map_t bindings;
	PortTypeRef* portTypeRef;
	fptrPortInternalGetKey InternalGetKey;
	fptrPortMetaClassName MetaClassName;
	fptrPortFindBindingsByID FindBindingsByID;
	fptrPortAddBindings AddBindings;
	fptrPortAddPortTypeRef AddPortTypeRef;
	fptrPortRemoveBindings RemoveBindings;
	fptrPortRemovePortTypeRef RemovePortTypeRef;
	fptrFindByPathPort FindByPath;
	fptrVisitAttrPort VisitAttributes;
	fptrVisitRefsPort VisitReferences;
	fptrDeletePort Delete;
} Port;

Port* new_Port(void);
void delete_Port(void*);
char* Port_InternalGetKey(Port* const this);
char* Port_MetaClassName(Port* const this);
MBinding* Port_FindBindingsByID(Port* const this, char* id);
void Port_AddBindings(Port* const this, MBinding* ptr);
void Port_AddPortTypeRef(Port* const this, PortTypeRef* ptr);
void Port_RemoveBindings(Port* const this, MBinding* ptr);
void Port_RemovePortTypeRef(Port* const this, PortTypeRef* ptr);
void Port_VisitAttributes(Port* const this, char* parent, Visitor* visitor);
void Port_VisitReferences(Port* const this, char* parent, Visitor* visitor);
void* Port_FindByPath(char* attribute, Port* const this);

#endif /* __Port_H */