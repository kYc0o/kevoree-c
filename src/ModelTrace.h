#ifndef MODEL_TRACE_H
#define MODEL_TRACE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ActionType.h"

/**
 * Author: fco.ja.ac@gmail.com
 * Date: 24/10/13
 * Time: 16:00
 */

/*class ModelTrace
{

  public:
    virtual ~ModelTrace(){}
	virtual string toString ()
	{
	}
  string srcPath;	
  string refName;
};*/

/*typedef struct _ModelTrace ModelTrace;*/

typedef char* (*fptrModelTraceToString)(void*);
typedef void (*fptrDeleteModelTrace)(void*);

typedef struct _ModelTrace {
	void* pDerivedObj;
	char* srcPath;
	char* refName;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelTrace;

ModelTrace* new_ModelTrace(void);
char* ModelTrace_ToString(void* const this);
void delete_ModelTrace(ModelTrace* const this);


/*class ModelAddTrace : public ModelTrace
{
	
public:
   ModelAddTrace(string _srcPath, string _refName, string _previousPath,string _typeName);
   ~ModelAddTrace();
   virtual std::string toString ();
  
  string previousPath;
  string typeName;

};*/

/*typedef _ModelAddTrace ModelAddTrace;*/

typedef struct _ModelAddTrace {
	ModelTrace* super;
	char* previousPath;
	char* typeName;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelAddTrace;

ModelAddTrace* new_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName);
ModelTrace* newPoly_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName);
char* ModelAddTrace_ToString(ModelAddTrace* const this);
void delete_ModelAddTrace(ModelAddTrace* const this);
void deletePoly_ModelAddTrace(ModelTrace* const this);

/*class ModelSetTrace:public ModelTrace
{
public: 
  ModelSetTrace (string _srcPath, string _refName, string _objPath, string _content, string _typeName);
  ~ModelSetTrace();
  virtual std::string toString ();
 
  string objPath;
  string content;
  string typeName;

};*/

/*typedef struct _ModelSetTrace ModelSetTrace;*/

typedef struct _ModelSetTrace {
	ModelTrace* super;
	char* objPath;
	char* content;
	char* typeName;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelSetTrace;

ModelTrace* newPoly_ModelSetTrace(char* _srcPath, char* _refName, char* _objPath, char* _content, char* _typeName);
ModelSetTrace* new_ModelSetTrace(char* _srcPath, char* _refName, char* _objPath, char* _content, char* _typeName);
char* ModelSetTrace_ToString(ModelSetTrace* const this);
void delete_ModelSetTrace(ModelSetTrace* const this);
void deletePoly_ModelSetTrace(ModelTrace* const this);

/*class ModelRemoveTrace:public ModelTrace
{
public:
  ModelRemoveTrace (string _srcPath, string _refName, string _objPath);
  ~ModelRemoveTrace();
  virtual std::string toString ();
  string objPath;
};*/

/*typedef _ModelRemoveTrace ModelRemoveTrace;*/

typedef struct _ModelRemoveTrace {
	ModelTrace* super;
	char* objPath;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelRemoveTrace;

ModelRemoveTrace* new_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath);
char* ModelRemoveTrace_ToString(ModelRemoveTrace* const this);
void delete_ModelRemoveTrace(ModelRemoveTrace* const this);

#endif /*MODEL_TRACE_H */