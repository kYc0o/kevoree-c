#ifndef H_DefaultFactory
#define H_DefaultFactory

/*#include "kevoree.h"
#include "tools.h"
#include <stdlib.h>*/
#include "jsonparse.h"

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

ContainerRoot *createContainerRoot(struct jsonparse_state *jsonState, char jsonType, char *strJson);
ContainerNode *createContainerNode(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
ComponentInstance *createComponentInstance(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
Group *createGroup(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
TypeDefinition *createTypeDefinition(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
/*NodeNetwork* createNodeNetwork(void);*/
DeployUnit *createDeployUnit(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
NetworkInfo *createNetworkInfo(struct jsonparse_state *jsonState, char jsonType, char *strJson);
NetworkProperty *createNetworkProperty(struct jsonparse_state *jsonState, char jsonType, char *strJson);
DictionaryType *createDictionaryType(struct jsonparse_state *jsonState, char jsonType, char *strJson);
DictionaryAttribute *createDictionaryAttribute(struct jsonparse_state *jsonState, char jsonType, char *strJson);
TypeLibrary *createTypeLibrary(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root);
FragmentDictionary *createFragmentDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson);
DictionaryValue *createDictionaryValue(struct jsonparse_state *jsonState, char jsonType, char *strJson);
#endif
