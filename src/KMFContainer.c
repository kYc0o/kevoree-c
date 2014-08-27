#include "KMFContainer.h"

KMFContainer* new_KMFContainer(void)
{
	KMFContainer* pKMFContObj = NULL;

	pKMFContObj = (KMFContainer*)malloc(sizeof(KMFContainer));

	if(pKMFContObj == NULL)
		return NULL;

	pKMFContObj->EContainer = KMFContainer_EContainer;
	pKMFContObj->IsReadOnly = KMFContainer_IsReadOnly;
	pKMFContObj->IsRecursiveReadOnly = KMFContainer_IsRecursiveReadOnly;
	pKMFContObj->SetInternalReadOnly = KMFContainer_SetInternalReadOnly;
	pKMFContObj->DeleteContainer = KMFContainer_deleteContainer;
	pKMFContObj->ModelEquals = KMFContainer_ModelEquals;
	pKMFContObj->DeepModelEquals = KMFContainer_DeepModelEquals;
	pKMFContObj->GetRefInParent = KMFContainer_GetRefInParent;
	pKMFContObj->FindByPath = KMFContainer_FindByPath;
	pKMFContObj->FindByID = KMFContainer_FindByID;
	pKMFContObj->Path = KMFContainer_Path;
	pKMFContObj->MetaClassName = KMFContainer_MetaClassName;
	pKMFContObj->ReflexiveMutator = KMFContainer_ReflexiveMutator;
	pKMFContObj->ToTraces = KMFContainer_ToTraces;
	pKMFContObj->InternalGetKey = KMFContainer_InternalGetKey;
	pKMFContObj->Visit = KMFContainer_Visit;
	pKMFContObj->VisitAttributes = KMFContainer_VisitAttributes;
	pKMFContObj->CreateTraces = KMFContainer_CreateTraces;
	pKMFContObj->Delete = delete_KMFContainer;

	return pKMFContObj;
}

/*virtual ~KMFContainer(){}*/
void delete_KMFContainer(void* const this)
{

}

/*virtual KMFContainer* eContainer(){return NULL;}*/
KMFContainer* KMFContainer_EContainer(void* const this)
{
	return NULL;
}

/*virtual bool isReadOnly()*/
int KMFContainer_IsReadOnly(void* const this)
{
	return 0;
}

/*virtual bool isRecursiveReadOnly()*/
int KMFContainer_IsRecursiveReadOnly(void* const this)
{
	return 0;
}

/*virtual void setInternalReadOnly()*/
void KMFContainer_SetInternalReadOnly(void* const this)
{

}

/*virtual void deleteContainer() // can't use delete reserve c++*/
void KMFContainer_deleteContainer(void* const this) // can't use delete reserve c++
{

}

/*virtual bool modelEquals(KMFContainer similarObj)*/
int KMFContainer_ModelEquals(void* const this, KMFContainer* similarObj)
{
	return 0;
}

/*virtual bool deepModelEquals(KMFContainer similarObj)*/
int KMFContainer_DeepModelEquals(void* const this, KMFContainer similarObj)
{
	return 0;
}

/*virtual string getRefInParent()*/
char* KMFContainer_GetRefInParent(void* const this)
{
	return NULL;
}

/*virtual KMFContainer* findByPath(string query)*/
KMFContainer* KMFContainer_FindByPath(void* const this, char* query)
{
	return NULL;
}

/*virtual KMFContainer* findByID(string relationName,string idP)*/
KMFContainer* KMFContainer_FindByID(void* const this, char* relationName, char* idP)
{
	return NULL;
}

/*virtual string path()*/
char* KMFContainer_Path(void* const this)
{
	return NULL;
}

/*virtual string metaClassName()*/
char* KMFContainer_MetaClassName(void* const this)
{
	return NULL;
}

/*virtual void reflexiveMutator(int mutatorType,string refName, any value, bool setOpposite,bool fireEvent )*/
void KMFContainer_ReflexiveMutator(void* const this, int mutatorType, char* refName, void* value, int setOpposite, int fireEvent)
{

}

/*virtual void addModelElementListener(ModelElementListener lst){}
virtual void removeModelElementListener(ModelElementListener lst){}
virtual void removeAllModelElementListeners(){}
virtual void addModelTreeListener(ModelElementListener lst){}
virtual void removeModelTreeListener(ModelElementListener lst){}
virtual void removeAllModelTreeListeners(){}*/

/*virtual list<ModelTrace*> * toTraces(bool attributes,bool references)*/
ModelTrace** KMFContainer_ToTraces(void* const this, int attributes, int references)
{
	return NULL;
}

/*virtual string internalGetKey()*/
char* KMFContainer_InternalGetKey(void* const this)
{
	return NULL;
}

/*virtual void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)*/
void KMFContainer_Visit(void* const this, ModelVisitor *visitor, int recursive, int containedReference, int nonContainedReference)
{

}

/*virtual void visitAttributes(ModelAttributeVisitor *visitor)*/
void KMFContainer_VisitAttributes(void* const this, ModelAttributeVisitor *visitor)
{

}

/*virtual list<ModelTrace*> *createTraces(KMFContainer *similarObj ,bool isInter ,bool isMerge ,bool onlyReferences,bool onlyAttributes)*/
ModelTrace** KMFContainer_CreateTraces(void* const this, KMFContainer *similarObj, int isInter, int isMerge, int onlyReferences, int onlyAttributes)
{
	return NULL;
}

/* TODO Code ModelVisitor and ModelAttributeVisitor */

/*virtual void clean_path_cache(){}*/
