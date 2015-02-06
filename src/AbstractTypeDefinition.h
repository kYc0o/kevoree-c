#ifndef __AbstractTypeDefinition_H
#define __AbstractTypeDefinition_H

/*#include "KevoreeModelHandlerService.h"*/
#include "hashmap.h"

typedef struct _AbstractTypeDefinition AbstractTypeDefinition;
typedef struct _KevoreeModelHandlerService KevoreeModelHandlerService;
typedef struct _Bootstraper Bootstraper;
typedef struct _KMFContainer KMFContainer;

typedef void (*fptrStart)(AbstractTypeDefinition*);
typedef void (*fptrStop)(AbstractTypeDefinition*);
typedef void (*fptrUpdate)(AbstractTypeDefinition*, int);
typedef void (*fptrSetModelService)(AbstractTypeDefinition*, KevoreeModelHandlerService*);
typedef KevoreeModelHandlerService *(*fptrGetModelService)(AbstractTypeDefinition*);
typedef void (*fptrSetBootStrapperService)(AbstractTypeDefinition*, Bootstraper*);
typedef Bootstraper *(*fptrGetBootStrapperService)(AbstractTypeDefinition*);
typedef void (*fptrSetPath)(AbstractTypeDefinition*, char*);
typedef void *(*fptrGetModelElement)(AbstractTypeDefinition*);
typedef void (*fptrUpdateParam)(AbstractTypeDefinition*, char*, char*);
typedef void (*fptrATDDelete)(AbstractTypeDefinition*);

typedef struct _AbstractTypeDefinition {
	void *pDerivedObj;
	KevoreeModelHandlerService *service;
	Bootstraper *bootstrapService;
	char *path;
	map_t params;
	fptrStart start;
	fptrStop stop;
	fptrUpdate update;
	fptrSetModelService setModelService;
	fptrGetModelService getModelService;
	fptrSetBootStrapperService setBootStrapperService;
	fptrGetBootStrapperService getBootStrapperService;
	fptrSetPath setPath;
	fptrGetModelElement getModelElement;
	fptrUpdateParam updateParam;
	fptrATDDelete delete;
} AbstractTypeDefinition;

AbstractTypeDefinition *new_AbstractTypeDefinition(void);
void delete_AbstractTypeDefinition(AbstractTypeDefinition *const this);
void AbstractTypeDefinition_start(AbstractTypeDefinition *const this);
void AbstractTypeDefinition_stop(AbstractTypeDefinition *const this);
void AbstractTypeDefinition_update(AbstractTypeDefinition *const this, int value);
void AbstractTypeDefinition_setModelService(AbstractTypeDefinition *const this, KevoreeModelHandlerService *handler);
KevoreeModelHandlerService *AbstractTypeDefinition_getModelService(AbstractTypeDefinition *const this);
void AbstractTypeDefinition_setBootStrapperService(AbstractTypeDefinition *const this, Bootstraper *bootstrapService);
Bootstraper *AbstractTypeDefinition_getBootStrapperService(AbstractTypeDefinition *const this);
void AbstractTypeDefinition_setPath(AbstractTypeDefinition *const this, char *path);
void *AbstractTypeDefinition_getModelElement(AbstractTypeDefinition *const this);
void AbstractTypeDefinition_updateParam(AbstractTypeDefinition *const this, char *key, char *value);

#endif
