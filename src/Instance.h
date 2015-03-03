#ifndef H_Instance
#define H_Instance

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

typedef struct _Instance Instance;
typedef struct _NamedElement NamedElement;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _Dictionary Dictionary;
typedef struct _FragmentDictionary FragmentDictionary;
typedef struct _Visitor Visitor;

typedef char* (*fptrInstInternalGetKey)(Instance*);
typedef char* (*fptrInstMetaClassName)(Instance*);
typedef FragmentDictionary* (*fptrInstFindFragDictByID)(Instance*, char*);
typedef void (*fptrInstAddTypeDefinition)(Instance*, TypeDefinition*);
typedef void (*fptrInstAddDictionary)(Instance*, Dictionary*);
typedef void (*fptrInstAddFragmentDictionary)(Instance*, FragmentDictionary*);
typedef void (*fptrInstRemoveTypeDefinition)(Instance*, TypeDefinition*);
typedef void (*fptrInstRemoveDictionary)(Instance*, Dictionary*);
typedef void (*fptrInstRemoveFragmentDictionary)(Instance*, FragmentDictionary*);
typedef void (*fptrDeleteInstance)(Instance*);
typedef void (*fptrVisitAttrInstance)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsInstance)(void*, char*, Visitor*, bool);
typedef void* (*fptrFindByPathInstance)(char*, Instance*);

typedef struct _Instance {
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
	NamedElement* super;
	char* metaData;
	bool started;
	TypeDefinition* typeDefinition;
	Dictionary* dictionary;
	map_t fragmentDictionary;
	fptrInstFindFragDictByID FindFragmentDictionaryByID;
	fptrInstAddTypeDefinition AddTypeDefinition;
	fptrInstAddDictionary AddDictionary;
	fptrInstAddFragmentDictionary AddFragmentDictionary;
	fptrInstRemoveTypeDefinition RemoveTypeDefinition;
	fptrInstRemoveDictionary RemoveDictionary;
	fptrInstRemoveFragmentDictionary RemoveFragmentDictionary;
} Instance;

NamedElement* newPoly_Instance(void);
Instance* new_Instance(void);
FragmentDictionary* Instance_FindFragmentDictionaryByID(Instance* const this, char* id);
void Instance_AddTypeDefinition(Instance* const this, TypeDefinition* ptr);
void Instance_AddDictionary(Instance* const this, Dictionary* ptr);
void Instance_AddFragmentDictionary(Instance* const this, FragmentDictionary* ptr);
void Instance_RemoveTypeDefinition(Instance* const this, TypeDefinition* ptr);
void Instance_RemoveDictionary(Instance* const this, Dictionary* ptr);
void Instance_RemoveFragmentDictionary(Instance* const this, FragmentDictionary* ptr);
char* Instance_internalGetKey(void * const this);
char* Instance_metaClassName(void * const this);
void deletePoly_Instance(void * const this);
void delete_Instance(void * const this);
void Instance_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Instance_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Instance_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void Instance_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* Instance_FindByPath(char* attribute, void * const this);

#endif /* H_Instance */
