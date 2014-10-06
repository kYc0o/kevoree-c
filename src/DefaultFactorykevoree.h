#ifndef H_DefaultFactory
#define H_DefaultFactory

/*#include "kevoree.h"
#include "tools.h"
#include <stdlib.h>*/

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

int addContainerRootGroup(ContainerRoot *root, Group *val);
int addContainerRootContainerNode(ContainerRoot *root, ContainerNode *val);
/*int addContainerRootNodeNetwork(ContainerRoot *root, NodeNetwork *val);*/
int addContainerRootTypeDefinition(ContainerRoot *root, TypeDefinition *val);
int addContainerRootDeployUnit(ContainerRoot *root, DeployUnit *val);
int addContainerRootTypeLibrary(ContainerRoot *root, TypeLibrary *val);
int addContainerNodeComponentInstance(ContainerNode *root, ComponentInstance *val);
int addContainerNodeTypeDefinition(ContainerNode *root, TypeDefinition *val);
int addContainerNodeNetworkInfo(ContainerNode *root, NetworkInfo *val);
int addNetworkInfoValues(NetworkInfo *root, NetworkProperty *val);
/*int addContainerNodeNodeNetwork(ContainerNode *root, NodeNetwork *val);*/
int addTypeDefinitionDeployUnit(TypeDefinition *root, DeployUnit *val);
int addTypeDefinitionDictionaryType(TypeDefinition *root, DictionaryType *val);
int addDictionaryTypeAttributes(DictionaryType *root, DictionaryAttribute *val);
int addGroupContainerNode(Group *root, ContainerNode *val);
int addGroupTypeDefinition(Group *root, TypeDefinition *val);
int addGroupFragmentDictionary(Group *root, FragmentDictionary *val);
ContainerRoot *createContainerRoot(void);
ContainerNode *createContainerNode(void);
ComponentInstance *createComponentInstance(void);
Group *createGroup(void);
TypeDefinition *createTypeDefinition(void);
/*NodeNetwork* createNodeNetwork(void);*/
DeployUnit *createDeployUnit(void);
NetworkInfo *createNetworkInfo(void);
NetworkProperty *createNetworkProperty(void);
DictionaryType *createDictionaryType(void);
DictionaryAttribute *createDictionaryAttribute(void);
TypeLibrary *createTypeLibrary(void);
FragmentDictionary *createFragmentDictionary(void);
#endif
