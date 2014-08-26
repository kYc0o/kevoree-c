#include "Visitor.h"

char* buffer = NULL;

void actionprintf(char *path, Type type, void* value)
{
	switch(type)
	{
		case STRING:
			printf("path = %s  value = %s\n", path, (char*)value);
			break;

		case BOOL:
			printf("path = %s  value = %d\n", path, (int)value);
			break;
	}
}

/*void actionPrintJSON(char *_path, Type type, void *value, int endStart)
{
	char* path = strdup(_path);

	path = strtok(_path, "\\");

	if(endStart == 1)
	{
		buffer = malloc(sizeof(char) * 3);

		if(buffer != NULL)
		{
			sprintf(buffer, "{\n");
		}
	}

	switch(type)
	{
		case STRING:
			buffer = realloc(buffer, sizeof(buffer) + sizeof(path));
			sprintf(buffer, "",path,(char*)value);
			break;

		case BOOL:
			printf("path = %s  value = %d\n", path, (int)value);
			break;
	}
}
*/
