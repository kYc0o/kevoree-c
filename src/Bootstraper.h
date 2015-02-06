/*
 * Bootstraper.h
 *
 *  Created on: Jan 28, 2015 1:18:54 PM
 *      Author: facosta
 */

#ifndef APPS_KEVOREE_BOOTSTRAPER_H_
#define APPS_KEVOREE_BOOTSTRAPER_H_

typedef struct _Bootstraper Bootstraper;
typedef struct _AbstractNodeType AbstractNodeType;
typedef struct _KevoreeModelHandlerService KevoreeModelHandlerService;
typedef struct _IDynamicLoader IDynamicLoader;

typedef struct _DeployUnit DeployUnit;
typedef struct _ContainerRoot ContainerRoot;

typedef AbstractNodeType *(*fptrBootstrNodeTyp)(Bootstraper*, char*, KevoreeModelHandlerService*);
typedef char *(*fptrRslvDepUnit)(Bootstraper*, DeployUnit*);
typedef IDynamicLoader *(*fptrGetDynLoader)(Bootstraper*);
typedef void (*fptrSetPropNewModel)(Bootstraper*, ContainerRoot*);
typedef void (*fptrBDelete)(Bootstraper*);

typedef struct _Bootstraper {
	void *pDerivedObj;
	fptrBootstrNodeTyp bootstrapNodeType;
	fptrRslvDepUnit resolveDeployUnit;
	fptrGetDynLoader getDynamicLoader;
	fptrSetPropNewModel setProposedNewModel;
	fptrBDelete delete;
} Bootstraper;

Bootstraper *new_Bootstraper(void);
void delete_Bootstraper(Bootstraper* const this);

/*
 * Only prototypes are provided since all functions are virtual
 */
AbstractNodeType *Bootstraper_bootsraperNodeType(Bootstraper * const this, char *destNodeName, KevoreeModelHandlerService *mservice);
char *Bootstraper_resolveDeployUnit(Bootstraper * const this, DeployUnit *du);
IDynamicLoader *Bootstraper_getDynamicLoader(Bootstraper * const this);
void Bootstraper_setProposedNewModel(Bootstraper * const this, ContainerRoot *root);

#endif /* APPS_KEVOREE_BOOTSTRAPER_H_ */
