#ifndef __JSONModelLoader_H
#define __JSONModelLoader_H

#include "jsonparse.h"
#include "hashmap.h"

#define MAX_STRJSON_SIZE 100

typedef struct _ContainerRoot ContainerRoot;
typedef struct _JSONModelLoader JSONModelLoader;
typedef struct _ObjectReference ObjectReference;

typedef int (*fptrAddObject)(JSONModelLoader*, ObjectReference*);
typedef void (*fptrJSONDelete)(void*);

typedef struct _JSONModelLoader {
	map_t objects;
	fptrAddObject addObjectReference;
	fptrJSONDelete delete;
} JSONModelLoader;

typedef struct _ObjectReference {
	char *srcObjectId;
	char *refId;
	char *mapId;
	fptrJSONDelete delete;
} ObjectReference;

ContainerRoot *JSONKevDeserializer(struct jsonparse_state *jsonState, char _jsonType);
JSONModelLoader *new_JSONModelLoader(void);
ObjectReference *new_ObjectReference(char *srcObj, char *srcId);
void delete_JSONModelLoader(void *const this);
void delete_ObjectReference(void *const this);
int JSONModelLoader_AddObjectReference(JSONModelLoader *const this, ObjectReference *obj);
int resolveReferences(any_t root, any_t objRef);

#endif /* __JSONModelLoader_H */
