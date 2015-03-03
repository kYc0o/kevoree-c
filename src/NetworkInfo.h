#ifndef H_NetworkInfo
#define H_NetworkInfo

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

typedef struct _NetworkInfo NetworkInfo;
typedef struct _NamedElement NamedElement;
typedef struct _NetworkProperty NetworkProperty;

typedef char* (*fptrNetInfoMetaClassName)(NetworkInfo*);
typedef char* (*fptrNetInfoInternalGetKey)(NetworkInfo*);
typedef void (*fptrNetInfoAddValues)(NetworkInfo*, NetworkProperty*);
typedef void (*fptrNetInfoRemoveValues)(NetworkInfo*, NetworkProperty*);
typedef NetworkProperty* (*fptrNetInfoFindValuesByID)(NetworkInfo*, char*);
typedef void (*fptrDeleteNetInfo)(NetworkInfo*);
typedef void (*fptrVisitAttrNetworkInfo)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsNetworkInfo)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNetworkInfo)(char*, NetworkInfo*);

typedef struct _NetworkInfo {
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
	map_t values;
	fptrNetInfoAddValues AddValues;
	fptrNetInfoRemoveValues RemoveValues;
	fptrNetInfoFindValuesByID FindValuesByID;
} NetworkInfo;

NamedElement* newPoly_NetworkInfo(void);
NetworkInfo* new_NetworkInfo(void);
char* NetworkInfo_metaClassName(void * const this);
char* NetworkInfo_internalGetKey(void * const this);
void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr);
void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr);
NetworkProperty* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id);
void deletePoly_NetworkInfo(void * const this);
void delete_NetworkInfo(void * const this);
void NetworkInfo_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NetworkInfo_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive);
void NetworkInfo_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void NetworkInfo_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive);
void* NetworkInfo_FindByPath(char* attribute, void * const this);

#endif /* H_NetworkInfo */
