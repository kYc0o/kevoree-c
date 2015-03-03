#ifndef __Port_H
#define __Port_H

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

typedef struct _NamedElement NamedElement;
typedef struct _MBinding MBinding;
typedef struct _PortTypeRef PortTypeRef;
typedef struct _Port Port;
typedef struct _MBinding MBinding;
typedef struct _Visitor Visitor;

typedef char* (*fptrPortInternalGetKey)(Port*);
typedef char* (*fptrPortMetaClassName)(Port*);
typedef MBinding* (*fptrPortFindBindingsByID)(Port*, char*);
typedef void (*fptrPortAddBindings)(Port*, MBinding*);
typedef void (*fptrPortAddPortTypeRef)(Port*, PortTypeRef*);
typedef void (*fptrPortRemoveBindings)(Port*, MBinding*);
typedef void (*fptrPortRemovePortTypeRef)(Port*, PortTypeRef*);
typedef void (*fptrVisitAttrPort)(Port*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsPort)(Port*, char*, Visitor*);
typedef void* (*fptrFindByPathPort)(char*, Port*);
typedef void (*fptrDeletePort)(void*);

typedef struct _Port {
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
	NamedElement *super;
	map_t bindings;
	PortTypeRef *portTypeRef;
	fptrPortFindBindingsByID FindBindingsByID;
	fptrPortAddBindings AddBindings;
	fptrPortAddPortTypeRef AddPortTypeRef;
	fptrPortRemoveBindings RemoveBindings;
	fptrPortRemovePortTypeRef RemovePortTypeRef;
} Port;

Port* new_Port(void);
void delete_Port(void*);
char* Port_internalGetKey(void * const this);
char* Port_metaClassName(void * const this);
MBinding* Port_FindBindingsByID(Port* const this, char* id);
void Port_AddBindings(Port* const this, MBinding* ptr);
void Port_AddPortTypeRef(Port* const this, PortTypeRef* ptr);
void Port_RemoveBindings(Port* const this, MBinding* ptr);
void Port_RemovePortTypeRef(Port* const this, PortTypeRef* ptr);
void Port_VisitAttributes(void * const this, char* parent, Visitor* visitor, bool recursive);
void Port_VisitPathAttributes(void * const this, char* parent, Visitor* visitor, bool recursive);
void Port_VisitReferences(void * const this, char* parent, Visitor* visitor, bool recursive);
void Port_VisitPathReferences(void * const this, char* parent, Visitor* visitor, bool recursive);
void* Port_FindByPath(char* attribute, void * const this);

#endif /* __Port_H */
