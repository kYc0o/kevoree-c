#ifndef H_Visitor
#define H_Visitor

/*#include "kevoree.h"*/

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

/*void visitContainerRoot(ContainerRoot *origin, Visitor* visitor);
void visitContainerNode(ContainerNode *origin, char *parent, Visitor* visitor);
void visitComponentInstance(ComponentInstance *origin, char *parent, Visitor* visitor);*/

#endif /* H_VISITOR */