#ifndef H_Visitor
#define H_Visitor

/*#include "kevoree.h"*/
#include <stdlib.h>
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
/*void visitContainerRoot(ContainerRoot *origin, Visitor* visitor);
void visitContainerNode(ContainerNode *origin, char *parent, Visitor* visitor);
void visitComponentInstance(ComponentInstance *origin, char *parent, Visitor* visitor);*/

#endif /* H_VISITOR */
