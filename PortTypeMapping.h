#ifndef __PortTypeMapping_H
#define __PortTypeMapping_H

#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct _PortTypeMapping PortTypeMapping;

typedef char* (*fptrPortTypMapMetaClassName)(PortTypeMapping*);
typedef char* (*fptrPortTypMapInternalGetKey)(PortTypeMapping*);
typedef void (*fptrDeletePortTypeMapping)(PortTypeMapping*);

typedef struct _PortTypeMapping {
	void* pDerivedObj;
	char* beanMethodName;
	char* serviceMethodName;
	char* paramTypes;
	char* generated_KMF_ID;
	fptrPortTypMapMetaClassName MetaClassName;
	fptrPortTypMapInternalGetKey InternalGetKey;
	fptrDeletePortTypeMapping Delete;
} PortTypeMapping;

PortTypeMapping* new_PortTypeMapping(void);
char* PortTypeMapping_MetaClassName(PortTypeMapping* const this);
char* PortTypeMapping_InternalGetKey(PortTypeMapping* const this);
void delete_PortTypeMapping(PortTypeMapping* const this);

#endif /*__PortTypeMapping_H */