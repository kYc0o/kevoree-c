#ifndef __JSONModelLoader_H
#define __JSONModelLoader_H

#include "jsonparse.h"

#define MAX_STRJSON_SIZE 100

typedef struct _ContainerRoot ContainerRoot;

void JSONKevDeserializer(struct jsonparse_state *jsonState, char _jsonType, ContainerRoot *newModel);

#endif /* __JSONModelLoader_H */
