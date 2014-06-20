/*#include "Comparekevoree.h"

int compareContainerRoot(ContainerRoot *s, ContainerRoot *t)
{
	if(s == NULL || t == NULL)
	{
		return 0;
	}

	int i, j;

	for(i = 0; i < s->count_groups; i++)
	{
		for(j = 0; j < t->count_groups; j++)
		{
			compareGroup(s->groups[i], t->groups[j]);
		}
	}

	for(i = 0; i < s->count_nodes; i++)
	{
		for(j = 0;j < t->count_nodes; j++)
		{
			compareContainerNode(s->nodes[i], t->nodes[j]);
		}
	}

	for(i = 0;i < s->count_nodeNetworks; i++)
	{
		for(j = 0;j < t->count_nodeNetworks; j++)
		{
			compareNodeNetwork(s->nodeNetworks[i], t->nodeNetworks[j]);
		}
	}

	for(i = 0; i < s->count_typedefintions; i++)
	{
		for(j=0; j<t->count_typedefintions; j++)
		{
			compareTypeDefinition(s->typedefintions[i], t->typedefintions[j]);
		}
	}
}

int compareContainerNode(ContainerNode *s, ContainerNode *t)
{
	if(s == NULL || t == NULL)
	{
		return 0;
	}

	int i, j;

	if(strcmp(s->name,t->name))
	{
		printf("TRACE name %s ", t->name);
	}

	if(s->started != t->started)
	{
	}

	for(i = 0; i < s->count_components; i++)
	{
		for(j = 0; j<t->count_components; j++)
		{
			compareComponentInstance(s->components[i], t->components[j]);
		}
	}

	compareTypeDefinition(s->typedefintion, t->typedefintion);

	for(i = 0; i < s->count_nodeNetworks; i++)
	{
		for(j = 0; j < t->count_nodeNetworks; j++)
		{
			compareNodeNetwork(s->nodeNetworks[i], t->nodeNetworks[j]);
		}
	}
}

int compareComponentInstance(ComponentInstance *s, ComponentInstance *t)
{
	if(s == NULL || t == NULL)
	{
		return 0;
	}

	int i, j;

	if(strcmp(s->name, t->name))
	{
		printf("TRACE name %s ", t->name);
	}

	compareTypeDefinition(s->typedefinition, t->typedefinition);
}

int compareGroup(Group *s, Group *t)
{
	if(s == NULL || t == NULL)
	{
		return 0;
	}

	int i, j;

	for(i = 0; i < s->count_subNodes; i++)
	{
		for(j = 0; j < t->count_subNodes; j++)
		{
			compareContainerNode(s->subNodes[i], t->subNodes[j]);
		}
	}
}

int compareTypeDefinition(TypeDefinition *s, TypeDefinition *t)
{
	if(s == NULL || t == NULL)
	{
		return 0;
	}

	int i, j;

	if(strcmp(s->query, t->query))
	{
		printf("TRACE query %s ", t->query);
	}
}

int compareNodeNetwork(NodeNetwork *s, NodeNetwork *t)
{
	if(s == NULL || t == NULL)
	{
		return 0;
	}

	int i, j;

	if(strcmp(s->networkType, t->networkType))
	{
		printf("TRACE networkType %s ", t->networkType);
	}

	if(strcmp(s->value, t->value))
	{
		printf("TRACE value %s ", t->value);
	}
}*/
