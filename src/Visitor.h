#ifndef H_Visitor
#define H_Visitor

/*#include "kevoree.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*#include "ModelAttributeVisitor.h"
#include "ModelVisitor.h"*/
/*#include "ContainerRoot.h"*/

typedef enum Type Type;
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
	RETURN
};

typedef struct _Visitor {
	void (*action)(char* path, Type type, void* value);
} Visitor;

void actionprintf(char *path, Type type, void* value);
#endif /* H_VISITOR */
