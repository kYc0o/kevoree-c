#ifndef MODEL_TRACE_H
#define MODEL_TRACE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Author: fco.ja.ac@gmail.com
 * Date: 24/10/13
 * Time: 16:00
 */

typedef struct _ModelTrace ModelTrace;

typedef char *(*fptrModelTraceToString)(void*);
typedef void (*fptrDeleteModelTrace)(void*);

typedef struct _ModelTrace {
	ModelTrace *next;
	void *pDerivedObj;
	char *srcPath;
	char *refName;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelTrace;

ModelTrace *new_ModelTrace(void);
char *ModelTrace_ToString(void * const this);
void delete_ModelTrace(void * const this);

typedef struct _ModelAddTrace {
	ModelTrace *super;
	char *previousPath;
	char *typeName;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelAddTrace;

ModelAddTrace *new_ModelAddTrace(char *_srcPath, char *_refName, char *_previousPath, char *_typeName);
ModelTrace *newPoly_ModelAddTrace(char* _srcPath, char *_refName, char *_previousPath, char *_typeName);
char* ModelAddTrace_ToString(void* const this);
void delete_ModelAddTrace(void* const this);
void deletePoly_ModelAddTrace(void* const this);

typedef struct _ModelSetTrace {
	ModelTrace *super;
	/*char* objPath;*/
	char *content;
	/*char* typeName;*/
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelSetTrace;

ModelTrace* newPoly_ModelSetTrace(char *_srcPath, char *_refName, /*char* _objPath,*/ char *_content/*, char* _typeName*/);
ModelSetTrace* new_ModelSetTrace(char *_srcPath, char *_refName, /*char *_objPath,*/ char *_content/*, char* _typeName*/);
char *ModelSetTrace_ToString(void *const this);
void delete_ModelSetTrace(void *const this);
void deletePoly_ModelSetTrace(void *const this);

typedef struct _ModelRemoveTrace {
	ModelTrace* super;
	char* objPath;
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelRemoveTrace;

ModelRemoveTrace* new_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath);
ModelTrace *newPoly_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath);
char* ModelRemoveTrace_ToString(void* const this);
void delete_ModelRemoveTrace(void* const this);
void deletePoly_ModelRemoveTrace(void* const this);

#endif /*MODEL_TRACE_H */
