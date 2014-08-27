#ifndef KMFContainer_H
#define KMFContainer_H
/**
 * Author: fco.ja.ac@gmail.com
 * Date: 27/08/14
 * Time: 18:13
 */

/*#include <microframework/api/trace/ModelTrace.h>*/
#include "ModelTrace.h"
/*#include <microframework/api/utils/ModelVisitor.h>*/
/*#include "ModelVisitor.h"*/
/*#include <microframework/api/utils/ModelAttributeVisitor.h>*/
#include "Visitor.h"
#include <string.h>
#include <stdlib.h>

typedef struct _KMFContainer KMFContainer;

typedef void (*fptrEContainer)(void*);
typedef int (*fptrIsReadOnly)(void*);
typedef int (*fptrIsRecursiveReadOnly)(void*);
typedef void (*fptrSetInternalReadOnly)(void*);
typedef void (*fptrDeleteContainer)(void*);
typedef int (*fptrModelEquals)(void*, KMFContainer*);
typedef int (*fptrDeepModelEquals)(void*, KMFContainer*);
typedef char* (*fptrGetRefInParent)(void*);
typedef KMFContainer* (*fptrKMFContFindByPath)(KMFContainer*, char*);
typedef KMFContainer* (*fptrKMFContFindByID)(KMFContainer*, char*, char*);
typedef char* (*fptrPath)(void*);
typedef char* (*fptrMetaClassName)(void*);
typedef void (*fptrReflexiveMutator)(void*, int, char*, void*, int, int);
/*
 * virtual void addModelElementListener(ModelElementListener lst){}
    virtual void removeModelElementListener(ModelElementListener lst){}
    virtual void removeAllModelElementListeners(){}
    virtual void addModelTreeListener(ModelElementListener lst){}
    virtual void removeModelTreeListener(ModelElementListener lst){}
    virtual void removeAllModelTreeListeners(){}
    virtual list<ModelTrace*> * toTraces(bool attributes,bool references){return NULL;}
    template <class A> // http://www.cplusplus.com/doc/tutorial/templates
	A* findByPath(string query,A clazz);
 */
typedef ModelTrace** (*fptrToTraces)(void*, int, int);
typedef char* (*fptrInternalGetKey)(void*);
typedef void (*fptrVisit)(void*, ModelVisitor*, int, int, int);
typedef void (*fptrVisitAttributes)(void*, ModelAttributeVisitor*);
typedef ModelTrace** (*fptrCreateTraces)(void*, KMFContainer*, int, int, int, int);
/*virtual void clean_path_cache(){}*/
typedef void (*fptrDelete)(void*);

/*class KMFContainer*/
typedef struct _KMFContainer {
	fptrEContainer EContainer;
	fptrIsReadOnly IsReadOnly;
	fptrIsRecursiveReadOnly IsRecursiveReadOnly;
	fptrSetInternalReadOnly SetInternalReadOnly;
	fptrDeleteContainer DeleteContainer;
	fptrModelEquals ModelEquals;
	fptrDeepModelEquals DeepModelEquals;
	fptrGetRefInParent GetRefInParent;
	fptrKMFContFindByPath FindByPath;
	fptrKMFContFindByID FindByID;
	fptrPath Path;
	fptrMetaClassName MetaClassName;
	fptrReflexiveMutator ReflexiveMutator;
	fptrInternalGetKey InternalGetKey;
	fptrToTraces ToTraces;
	fptrVisit Visit;
	fptrVisitAttributes VisitAttributes;
	fptrCreateTraces CreateTraces;
	fptrDelete Delete;
} KMFContainer;

KMFContainer* new_KMFContainer(void);
void delete_KMFContainer(void* const this);
KMFContainer* KMFContainer_EContainer(void* const this);
int KMFContainer_IsReadOnly(void* const this);
int KMFContainer_IsRecursiveReadOnly(void* const this);
void KMFContainer_SetInternalReadOnly(void* const this);
void KMFContainer_deleteContainer(void* const this); // can't use delete reserve c++
int KMFContainer_ModelEquals(void* const this, KMFContainer* similarObj);
int KMFContainer_DeepModelEquals(void* const this, KMFContainer similarObj);
char* KMFContainer_GetRefInParent(void* const this);
KMFContainer* KMFContainer_FindByPath(void* const this, char* query);
KMFContainer* KMFContainer_FindByID(void* const this, char* relationName, char* idP);
char* KMFContainer_Path(void* const this);
char* KMFContainer_MetaClassName(void* const this);
void KMFContainer_ReflexiveMutator(void* const this, int mutatorType, char* refName, void* value, int setOpposite, int fireEvent);
/*virtual void addModelElementListener(ModelElementListener lst){}
virtual void removeModelElementListener(ModelElementListener lst){}
virtual void removeAllModelElementListeners(){}
virtual void addModelTreeListener(ModelElementListener lst){}
virtual void removeModelTreeListener(ModelElementListener lst){}
virtual void removeAllModelTreeListeners(){}*/
ModelTrace** KMFContainer_ToTraces(void* const this, int attributes, int references);
/*template <class A> // http://www.cplusplus.com/doc/tutorial/templates
A* findByPath(string query,A clazz);*/
char* KMFContainer_InternalGetKey(void* const this);
void KMFContainer_Visit(void* const this, ModelVisitor *visitor, int recursive, int containedReference, int nonContainedReference);
void KMFContainer_VisitAttributes(void* const this, ModelAttributeVisitor *visitor);
ModelTrace** KMFContainer_CreateTraces(void* const this, KMFContainer *similarObj, int isInter, int isMerge, int onlyReferences, int onlyAttributes);

#endif /* KMFContainer_H */
