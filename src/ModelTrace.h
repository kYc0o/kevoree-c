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

typedef char *(*fptrModelTraceToString)(void*);
typedef void (*fptrDeleteModelTrace)(void*);

typedef struct {
	fptrModelTraceToString ToString;
	fptrDeleteModelTrace Delete;
} ModelTrace_VT;

// abstract
typedef struct {
	void *next;
	const ModelTrace_VT* vt;
	char *srcPath;
	char *refName;
} ModelTrace;

typedef struct {
	ModelTrace *next;
	const ModelTrace_VT* vt;
	char *srcPath;
	char *refName;
	char *previousPath;
	char *typeName;
} ModelAddTrace;

ModelTrace *newPoly_ModelAddTrace(char* _srcPath, char *_refName, char *_previousPath, char *_typeName);

typedef struct {
	ModelTrace *next;
	const ModelTrace_VT* vt;
	char *srcPath;
	char *refName;
	/*char* objPath;*/
	char *content;
	/*char* typeName;*/
} ModelSetTrace;

ModelTrace *newPoly_ModelSetTrace(char *_srcPath, char *_refName, /*char* _objPath,*/ char *_content/*, char* _typeName*/);

typedef struct {
	ModelTrace *next;
	const ModelTrace_VT* vt;
	char *srcPath;
	char *refName;
	char* objPath;
} ModelRemoveTrace;

ModelTrace *newPoly_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath);

#endif /*MODEL_TRACE_H */
