#ifndef H_Visitor
#define H_Visitor

/*#include "kevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "KMF4C.h"
#include "list.h"
/*#include "ModelAttributeVisitor.h"
#include "ModelVisitor.h"*/
/*#include "ContainerRoot.h"*/

typedef struct _ContainerRoot ContainerRoot;
typedef struct _Visitor Visitor;
typedef enum Type Type;

typedef void (*fptrVisit)(char*, Type, void*);
typedef void (*fptrDiff)(Visitor*, char*, Type, void*);

enum Type
{
	INTEGER,
	STRING,
	BOOL,
	BRACKET,
	CLOSEBRACKET,
	SQBRACKET,
	CLOSESQBRACKET,
	CLOSEBRACKETCOLON,
	CLOSESQBRACKETCOLON,
	COLON,
	STRREF,
	RETURN,
	REFERENCE
};

typedef struct _Visitor {
	ContainerRoot *new_model;
	ContainerRoot *current_model;
	/*LIST(visit_list);*/
	void *visit_list_list;
	list_t visit_list;
	fptrVisit store;
	fptrVisit printPaths;
	fptrVisit print;
	fptrDiff diff;
	void (*action)(char *path, Type type, void *value);
	bool (*secondAction)(char *path, char *value);
	fptrDelete delete;
} Visitor;

Visitor *new_Visitor(ContainerRoot *new_model, ContainerRoot *current_model);
void delete_Visitor(void *const this);
void Visitor_store(char *path, Type type, void *value);
void Visitor_printPaths(char *path, Type type, void *value);
void Visitor_print(char *path, Type type, void *value);
void Visitor_diff(Visitor *const this, char *path, Type type, void *value);


/*void actionprintf(char *path, Type type, void* value);*/
#endif /* H_VISITOR */
