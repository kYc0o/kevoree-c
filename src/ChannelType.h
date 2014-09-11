#ifndef __ChannelType_H
#define __ChannelType_H

#include <stdbool.h>

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
	TypeDefinition* super;
	int lowerBindings;
	int upperBindings;
	int lowerFragments;
	int upperFragments;
	fptrChanTypeInternalGetKey InternalGetKey;
	fptrChanTypeMetaClassName MetaClassName;
	fptrDeleteChannelType Delete;
	fptrVisitAttrChanType VisitAttributes;
	fptrVisitRefsChanType VisitReferences;
	fptrFindByPathChanType FindByPath;
} ChannelType;

TypeDefinition* newPoly_ChannelType(void);
ChannelType* new_ChannelType(void);
void deletePoly_ChannelType(void* const this);
void delete_ChannelType(void* const this);
char* ChannelType_InternalGetKey(void* const this);
char* ChannelType_MetaClassName(ChannelType* const this);
void ChannelType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ChannelType_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* ChannelType_FindByPath(char* attribute, TypeDefinition* const this);

#endif /* __ChannelType_H */
