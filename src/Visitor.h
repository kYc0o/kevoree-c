#ifndef H_Visitor
#define H_Visitor

/*#include "kevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*#include "ContainerRoot.h"*/

typedef enum Type Type;
enum Type
{
	INTEGER,
	STRING,
	BOOL
};

typedef struct _Visitor {
	void (*action)(char* path, Type type, void* value);
} Visitor;

void actionprintf(char *path, Type type, void* value);
/*---------------------------------------------- SerializerAttributeVisitor ----------------------------------------*/

typedef struct _SerializerAttributeVisitor SerializerAttributeVisitor;

typedef void (*fptrSerializerVisit)(SerializerAttributeVisitor*, char*, Type, void*);
typedef void (*fptrSerializerDelete)(SerializerAttributeVisitor*);

/*class SerializerAttributeVisitor:public ModelAttributeVisitor*/
typedef struct _SerializerAttributeVisitor {
	/*std::string *out;*/
	char* out;
	fptrSerializerVisit Visit;
	fptrSerializerDelete Delete;
} SerializerAttributeVisitor;

SerializerAttributeVisitor* new_SerializerAttributeVisitor(char* out);
void delete_SerializerAttributeVisitor(SerializerAttributeVisitor* const this);
void SerializerAttributeVisitor_Visit(SerializerAttributeVisitor* const this, char* path, Type type, void* value);

/*------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------- ModelReferenceVisitor ---------------------------------------------*/

typedef struct _ModelReferenceVisitor ModelReferenceVisitor;

typedef void (*fptrModelRefBeginVisitRef)(ModelReferenceVisitor*, char*);
typedef void (*fptrModelRefEndVisitRef)(ModelReferenceVisitor*);
typedef void (*fptrModelRefVisit)(ModelReferenceVisitor*, char* path);
typedef void (*fptrModelRefDelete)(ModelReferenceVisitor*);

/*class ModelReferenceVisitor :public ModelVisitor*/
typedef struct _ModelReferenceVisitor {
/*private:
	bool isFirst;
	std::string *out;*/
	int isFirst;
	char* out;
	fptrModelRefBeginVisitRef BeginVisitRef;
	fptrModelRefEndVisitRef EndVisitRef;
	fptrModelRefVisit Visit;
	fptrModelRefDelete Delete;
} ModelReferenceVisitor;

ModelReferenceVisitor* new_ModelReferenceVisitor(char* _out);
void delete_ModelReferenceVisitor(ModelReferenceVisitor* const this);
void ModelReferenceVisitor_BeginVisitRef(ModelReferenceVisitor*, char* refName);
void ModelReferenceVisitor_EndVisitRef(ModelReferenceVisitor*);
void ModelReferenceVisitor_Visit(ModelReferenceVisitor*, char* path);
/*------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- ModelMasterVisitor --------------------------------------------------*/

typedef struct _ModelMasterVisitor ModelMasterVisitor;

typedef void (*fptrModelMasterPrintAtName)(ModelMasterVisitor*, void*, char*);
typedef void (*fptrModelMasterBeginVisitElem)(ModelMasterVisitor*, void*);
typedef void (*fptrModelMasterEndVisitElem)(ModelMasterVisitor*);
typedef void (*fptrModelMasterBeginVisitRef)(ModelMasterVisitor*, char*);
typedef void (*fptrModelMasterEndVisitRef)(ModelMasterVisitor*);
typedef void (*fptrModelMasterDelete)(ModelMasterVisitor*);

/*class ModelMasterVisitor :public ModelVisitor*/
typedef struct _ModelMasterVisitor {
/*private:
	bool isFirstInRef;
	std::string *out;
	ModelReferenceVisitor *internalReferenceVisitor;*/
	int isFirstInRef;
	char* out;
	ModelReferenceVisitor *internalReferenceVisitor;
	fptrModelMasterPrintAtName PrintAtName;
	fptrModelMasterBeginVisitElem BeginVisitElem;
	fptrModelMasterEndVisitElem EndVisitElem;
	fptrModelMasterBeginVisitRef BeginVisitRef;
	fptrModelMasterEndVisitRef EndVisitRef;
	fptrModelMasterDelete Delete;
} ModelMasterVisitor;

ModelMasterVisitor* new_ModelMasterVisitor(char* out);
void delete_ModelMasterVisitor(ModelMasterVisitor* const this);
void ModelMasterVisitor_PrintAtName(ModelMasterVisitor* const this, void* value, char* out);
void ModelMasterVisitor_BeginVisitElem(ModelMasterVisitor* const this, void* value);
void ModelMasterVisitor_EndVisitElem(ModelMasterVisitor* const this);
void ModelMasterVisitor_BeginVisitRef(ModelMasterVisitor* const this, char* refName);
void ModelMasterVisitor_EndVisitRef(ModelMasterVisitor* const this);
/*------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------- JSONModelSerializer ------------------------------------------------*/

typedef struct _JSONModelSerializer JSONModelSerializer;

typedef void (*fptrJSONModelSerializeToStrem)(JSONModelSerializer*, void*, void*);
typedef void (*fptrJSONModelSerialize)(JSONModelSerializer*, void*, char*);
typedef void (*fptrJSONModelDelete)(JSONModelSerializer*);

/*class JSONModelSerializer : public ModelSerializer*/
typedef struct _JSONModelSerializer {
/*public:
	void serializeToStream(KMFContainer *model, iostream  raw);
	string serialize(KMFContainer *model);*/
	fptrJSONModelSerializeToStrem SerializeToStream;
	fptrJSONModelSerialize Serialize;
} JSONModelSerializer;

JSONModelSerializer* new_JSONModelSerializer(void);
void delete_JSONModelSerializer(JSONModelSerializer* const this);
void JSONModelSerializer_SerializeToStream(JSONModelSerializer* const this, void* value, void* stream);
void JSONModelSerializer_Serialize(JSONModelSerializer* const this, void* value, char* buffer);
/*------------------------------------------------------------------------------------------------------------------*/


/*void visitContainerRoot(ContainerRoot *origin, Visitor* visitor);
void visitContainerNode(ContainerNode *origin, char *parent, Visitor* visitor);
void visitComponentInstance(ComponentInstance *origin, char *parent, Visitor* visitor);*/

#endif /* H_VISITOR */
