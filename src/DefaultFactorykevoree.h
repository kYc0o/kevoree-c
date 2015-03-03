#ifndef H_DefaultFactory
#define H_DefaultFactory

/*#include "kevoree.h"
#include "tools.h"
#include <stdlib.h>*/
#include "jsonparse.h"

typedef struct _KMFFactory KMFFactory;
typedef struct _ContainerRoot ContainerRoot;
typedef struct _ContainerNode ContainerNode;
typedef struct _Group Group;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _ComponentInstance ComponentInstance;
typedef struct _NetworkInfo NetworkInfo;
typedef struct _NetworkProperty NetworkProperty;
typedef struct _DeployUnit DeployUnit;
typedef struct _DictionaryType DictionaryType;
typedef struct _DictionaryAttribute DictionaryAttribute;
typedef struct _TypeLibrary TypeLibrary;
typedef struct _FragmentDictionary FragmentDictionary;
typedef struct _DictionaryValue DictionaryValue;
typedef struct _JSONModelLoader JSONModelLoader;
typedef struct _Dictionary Dictionary;
typedef struct _Instance Instance;

typedef ContainerRoot *(*fptrCreateContRoot)(struct jsonparse_state*, char, char*);
typedef ContainerNode *(*fptrCreateContNode)(struct jsonparse_state*, char, char*, ContainerRoot*, JSONModelLoader*);
typedef ComponentInstance *(*fptrCreateCompInst)(struct jsonparse_state*, char, char*, ContainerRoot*, ContainerNode*, JSONModelLoader*);
typedef Group *(*fptrCreateGroup)(struct jsonparse_state*, char, char*, ContainerRoot*, JSONModelLoader*);
typedef TypeDefinition *(*fptrCreateTypeDef)(struct jsonparse_state*, char, char*, ContainerRoot*, JSONModelLoader*);
typedef DeployUnit *(*fptrCreateDepUnit)(struct jsonparse_state*, char, char*, ContainerRoot*);
typedef NetworkInfo *(*fptrCreateNetInfo)(struct jsonparse_state*, char, char*, ContainerNode*);
typedef NetworkProperty *(*fptrCreateNetProp)(struct jsonparse_state*, char, char*);
typedef DictionaryType *(*fptrCreateDicType)(struct jsonparse_state*, char, char*, TypeDefinition*);
typedef DictionaryAttribute *(*fptrCreateDicAttr)(struct jsonparse_state*, char, char*);
typedef TypeLibrary *(*fptrCreateTypeLib)(struct jsonparse_state*, char, char*, ContainerRoot*, JSONModelLoader*);
typedef FragmentDictionary *(*fptrCreateFragDic)(struct jsonparse_state*, char, char*, Instance*);
typedef DictionaryValue *(*fptrCreateDicValue)(struct jsonparse_state*, char, char*);
typedef Dictionary *(*fptrCreateDic)(struct jsonparse_state*, char, char*, Instance*);

typedef struct _KMFFactory {
	fptrCreateContRoot createContainerRoot;
	fptrCreateContRoot createContainerNode;
	fptrCreateCompInst createComponentInstance;
	fptrCreateGroup createGroup;
	fptrCreateTypeDef createTypeDefinition;
	fptrCreateDepUnit createDeployUnit;
	fptrCreateNetInfo createNetworkInfo;
	fptrCreateNetProp createNetworkProperty;
	fptrCreateDicType createDictionaryType;
	fptrCreateDicAttr createDictionaryAttribute;
	fptrCreateTypeLib createTypeLibrary;
	fptrCreateFragDic createFragmentDictionary;
	fptrCreateDicValue createDictionaryValue;
	fptrCreateDic createDictionary;
} KMFFactory;

KMFFactory *new_KMFFactory(void);
void delete_KMFFactory(KMFFactory *const this);
ContainerRoot *createContainerRoot(struct jsonparse_state *jsonState, char jsonType, char *strJson);
ContainerNode *createContainerNode(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader);
ComponentInstance *createComponentInstance(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, ContainerNode *node, JSONModelLoader *loader);
Group *createGroup(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader);
TypeDefinition *createTypeDefinition(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader);
/*NodeNetwork* createNodeNetwork(void);*/
DeployUnit *createDeployUnit(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
NetworkInfo *createNetworkInfo(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerNode *node);
NetworkProperty *createNetworkProperty(struct jsonparse_state *jsonState, char jsonType, char *strJson);
DictionaryType *createDictionaryType(struct jsonparse_state *jsonState, char jsonType, char *strJson, TypeDefinition *typdef);
DictionaryAttribute *createDictionaryAttribute(struct jsonparse_state *jsonState, char jsonType, char *strJson);
TypeLibrary *createTypeLibrary(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader);
FragmentDictionary *createFragmentDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson, Instance *inst);
DictionaryValue *createDictionaryValue(struct jsonparse_state *jsonState, char jsonType, char *strJson);
Dictionary *createDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson, Instance *inst);

#endif
