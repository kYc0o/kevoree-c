#ifndef __ChannelType_H
#define __ChannelType_H

#include <stdbool.h>
#include "KMF4C.h"
typedef struct _ChannelType ChannelType;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _Visitor Visitor;

typedef char* (*fptrChanTypeMetaClassName)(ChannelType*);
typedef char* (*fptrChanTypeInternalGetKey)(void*);
typedef void (*fptrDeleteChannelType)(void*);
typedef void (*fptrVisitAttrChanType)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsChanType)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathChanType)(char*, TypeDefinition*);

typedef struct _ChannelType {
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
	TypeDefinition* super;
	int lowerBindings;
	int upperBindings;
	int lowerFragments;
	int upperFragments;
} ChannelType;

TypeDefinition* newPoly_ChannelType(void);
ChannelType* new_ChannelType(void);
void deletePoly_ChannelType(void* const this);
void delete_ChannelType(void* const this);
char* ChannelType_internalGetKey(void* const this);
char* ChannelType_metaClassName(void* const this);
void ChannelType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ChannelType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ChannelType_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void ChannelType_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* ChannelType_FindByPath(char* attribute, void* const this);

#endif /* __ChannelType_H */
