#include "DefaultFactorykevoree.h"
#include "kevoree.h"
#include "JSONModelLoader.h"
#include "json.h"
#include "jsonparse.h"

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

int addContainerRootGroup(ContainerRoot *root, Group *val)
{
	root->AddGroups(root, val);

	/*if(root->groups == NULL)
	{
		PRINTF("DEBUG -- FIRST ADD Group -> ContainerRoot %d \n", root->count_groups);
		root->groups = malloc(1 * sizeof(struct Group*));

		if(root->groups == NULL)
		{
			printf("FATAL can't allocate Group \n");
			return -1;
		}

		root->groups[root->count_groups] = (struct Group*)val;
        	root->count_groups++;
	}
	else
	{
		root->groups = realloc(root->groups, (root->count_groups+1) * sizeof(struct Group*));

		if(root->groups == NULL)
		{
			printf("FATAL can't allocate Group \n");
			return -1;
		}

		root->groups[root->count_groups] = (struct Group*)val;
		root->count_groups++;
	}*/

	return 0;
}

int addContainerRootContainerNode(ContainerRoot *root, ContainerNode *val)
{
	root->AddNodes(root, val);

	/*if(root->count_nodes == 0)
	{
		PRINTF("DEBUG -- FIRST ADD ContainerNode -> ContainerRoot %d \n", root->count_nodes);
		root->nodes = malloc(1 * sizeof(struct ContainerNode*));

		if(root->nodes == NULL)
		{
			printf("FATAL can't allocate ContainerNode \n");
			return -1;
		}

		root->nodes[root->count_nodes] = (struct ContainerNode*)val;
		root->count_nodes++;
	}
	else
	{
		root->nodes = realloc(root->nodes, (root->count_nodes+1) * sizeof(struct ContainerNode*));

		if(root->nodes == NULL)
		{
			printf("FATAL can't allocate ContainerNode \n");
			return -1;
		}

		root->nodes[root->count_nodes] = (struct ContainerNode*)val;
		root->count_nodes++;
	}*/

	return 0;
}

/*int addContainerRootNodeNetwork(ContainerRoot *root, NodeNetwork *val)
{
	if(root->count_nodeNetworks == 0)
	{
		PRINTF("DEBUG -- FIRST ADD NodeNetwork -> ContainerRoot %d \n", root->count_nodeNetworks);
		root->nodeNetworks = malloc(1 * sizeof(struct NodeNetwork*));

		if(root->nodeNetworks == NULL)
		{
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
		}

		root->nodeNetworks[root->count_nodeNetworks] = (struct NodeNetwork*)val;
		root->count_nodeNetworks++;
	}
	else
	{
		root->nodeNetworks = realloc(root->nodeNetworks, (root->count_nodeNetworks + 1) * sizeof(struct NodeNetwork*));

		if(root->nodeNetworks == NULL)
		{
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
		}

		root->nodeNetworks[root->count_nodeNetworks] = (struct NodeNetwork*)val;
		root->count_nodeNetworks++;
	}

	return 0;
}*/

int addContainerRootTypeDefinition(ContainerRoot *root, TypeDefinition *val)
{
	root->AddTypeDefinitions(root, val);

	/*if(root->count_typedefintions == 0)
	{
		PRINTF("DEBUG -- FIRST ADD TypeDefinition -> ContainerRoot %d \n",root->count_typedefintions);
		root->typedefintions = malloc(1 * sizeof(struct TypeDefinition*));

		if(root->typedefintions == NULL)
		{
			printf("FATAL can't allocate TypeDefinition \n");
			return -1;
		}

		root->typedefintions[root->count_typedefintions] =(struct TypeDefinition*)val;
		root->count_typedefintions++;
	}
	else
	{
		root->typedefintions = realloc(root->typedefintions, (root->count_typedefintions + 1) * sizeof(struct TypeDefinition*));

		if(root->typedefintions == NULL)
		{
			printf("FATAL can't allocate TypeDefinition \n");
			return -1;
		}

		root->typedefintions[root->count_typedefintions] =(struct TypeDefinition*)val;
		root->count_typedefintions++;
	}*/

	return 0;
}

int addContainerRootDeployUnit(ContainerRoot *root, DeployUnit *val)
{
	root->AddDeployUnits(root, val);

	/*if(root->count_deployUnits == 0)
	{
		PRINTF("DEBUG -- FIRST ADD DeployUnit -> ContainerRoot %d \n",root->count_deployUnits);
		root->deployUnits = malloc(1 * sizeof(struct DeployUnit*));

		if(root->deployUnits == NULL)
		{
			printf("FATAL can't allocate DeployUnit \n");
			return -1;
		}

		root->deployUnits[root->count_deployUnits] =(struct DeployUnit*)val;
		root->count_deployUnits++;
	}
	else
	{
		root->deployUnits = realloc(root->deployUnits, (root->count_deployUnits + 1) * sizeof(struct DeployUnit*));

		if(root->deployUnits == NULL)
		{
			printf("FATAL can't allocate DeployUnit \n");
			return -1;
		}

		root->count_deployUnits[root->count_deployUnits] =(struct DeployUnit*)val;
		root->count_deployUnits++;
	}*/

	return 0;
}

int addContainerNodeComponentInstance(ContainerNode *node, ComponentInstance *val)
{
	node->AddComponents(node, val);

	/*if(node->count_components== 0)
	{
		PRINTF("DEBUG -- FIRST ADD ComponentInstance -> ContainerNode %d \n", node->count_components);
		node->components = malloc(1 * sizeof(struct ComponentInstance*));

		if(node->components == NULL)
		{
			printf("FATAL can't allocate ComponentInstance \n");
			return -1;
		}

		node->components[node->count_components] = (struct ComponentInstance*)val;
		node->count_components++;
	}
	else
	{
		node->components = realloc(node->components, (node->count_components + 1) * sizeof(struct ComponentInstance*));

		if(node->components == NULL)
		{
			printf("FATAL can't allocate ComponentInstance \n");
			return -1;
		}

		node->components[node->count_components] =(struct ComponentInstance*)val;
		node->count_components++;
	}*/

	return 0;
}

/*int addContainerNodeNodeNetwork(ContainerNode *node, NodeNetwork *val)
{
	if(node->count_nodeNetworks == 0)
	{
		PRINTF("DEBUG -- FIRST ADD NodeNetwork -> ContainerNode %d \n",node->count_nodeNetworks);
		node->nodeNetworks = malloc(1 * sizeof(struct NodeNetwork*));

		if(node->nodeNetworks == NULL)
		{
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
		}

		node->nodeNetworks[node->count_nodeNetworks] = (struct NodeNetwork*)val;
		node->count_nodeNetworks++;
	}
	else
	{
		node->nodeNetworks = realloc(node->nodeNetworks,(node->count_nodeNetworks+1)*sizeof(struct NodeNetwork*));

		if(node->nodeNetworks == NULL)
		{
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
		}

		node->nodeNetworks[node->count_nodeNetworks] =(struct NodeNetwork*)val;
		node->count_nodeNetworks++;
	}

	return 0;
}*/

int addGroupContainerNode(Group *group, ContainerNode *val)
{
	group->AddSubNodes(group, val);

	/*if(group->count_subNodes == 0)
	{
		PRINTF("DEBUG -- FIRST ADD ContainerNode -> Group %d \n",group->count_subNodes);
		group->subNodes = malloc(1*sizeof(struct ContainerNode*));

		if(group->subNodes == NULL)
		{
			printf("FATAL can't allocate ContainerNode \n");
			return -1;
		}

		group->subNodes[group->count_subNodes] = (struct ContainerNode*)val;
		group->count_subNodes++;
	}
	else
	{
		group->subNodes = realloc(group->subNodes, (group->count_subNodes + 1) * sizeof(struct ContainerNode*));

		if(group->subNodes == NULL)
		{
			printf("FATAL can't allocate ContainerNode \n");
			return -1;
		}

		group->subNodes[group->count_subNodes] = (struct ContainerNode*)val;
		group->count_subNodes++;
	}*/

	return 0;
}

ContainerRoot *createContainerRoot(struct jsonparse_state *jsonState, char jsonType)
{
	ContainerRoot *obj = new_ContainerRoot();

	while((jsonType = jsonparse_next(jsonState)) != JSON_TYPE_OBJECT)
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->generated_KMF_ID = strJson;
						break;
					}
					break;
				}
			}
			break;
		}
	}

	return obj;

	/*ContainerRoot *ptr = (ContainerRoot*)malloc(sizeof(ContainerRoot));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate ContainerRoot \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptContainerRoot;
		ptr->count_groups = 0;
		ptr->groups = NULL;
		ptr->count_nodes = 0;
		ptr->nodes = NULL;
		ptr->count_nodeNetworks = 0;
		ptr->nodeNetworks = NULL;
		ptr->count_typedefintions = 0;
		ptr->typedefintions = NULL;
		ptr->count_deployUnits = 0;
		ptr->deployUnits = NULL;
	}*/
}

ContainerNode * createContainerNode(struct jsonparse_state *jsonState, char jsonType, ContainerRoot *root)
{
	ContainerNode *obj = new_ContainerNode();

	while((jsonType = jsonparse_next(jsonState)) != JSON_TYPE_OBJECT)
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "metaData"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "started"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->started = atoi(strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "components"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, sizeof strJson);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, sizeof strJson);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, sizeof strJson);
												if(!strcmp(strJson, "org.kevoree.ComponentInstance"))
												{
													ComponentInstance *component = createComponentInstance(jsonState, jsonType, root);
													obj->AddComponents(obj, component);
												}
												break;
											}
											break;
										}
									}
									else
									{
										printf("Invalid object!\n");
									}
									break;
								}
								/*JSONKevDeserializer(jsonState, jsonType, NULL);*/
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
			}
			else if(!strcmp(strJson, "hosts"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							JSONKevDeserializer(jsonState, jsonType, NULL);
							break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
				break;
			}
			else if(!strcmp(strJson, "host"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
										JSONKevDeserializer(jsonState, jsonType, NULL);
										break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
				break;
			}
			else if(!strcmp(strJson, "groups"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
										JSONKevDeserializer(jsonState, jsonType, NULL);
										break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
				break;
			}
			else if(!strcmp(strJson, "networkInformation"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, sizeof strJson);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, sizeof strJson);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, sizeof strJson);
												if(!strcmp(strJson, "org.kevoree.NetworkInfo"))
												{
													NetworkInfo *netInfo = createNetworkInfo(jsonState, jsonType, root);
													obj->AddNetworkInformation(obj, netInfo);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "typeDefinition"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}
	return obj;

	/*ContainerNode *ptr = (ContainerNode*)malloc(sizeof(ContainerNode));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate ContainerNode \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptContainerNode;
		ptr->started = 0;
		ptr->count_components = 0;
		ptr->components = NULL;
		ptr->typedefintion = NULL;
		ptr->count_nodeNetworks = 0;
		ptr->nodeNetworks = NULL;
	}

	return ptr;*/
}

NetworkInfo *createNetworkInfo(struct jsonparse_state *jsonState, char jsonType, ContainerRoot *root)
{
	printf("%s\n", strJson);
	NetworkInfo *obj = new_NetworkInfo();

	while((jsonType = jsonparse_next(jsonState)) != JSON_TYPE_OBJECT)
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "values"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, sizeof strJson);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, sizeof strJson);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, sizeof strJson);
												if(!strcmp(strJson, "org.kevoree.NetworkProperty"))
												{
													NetworkProperty *netprop = createNetworkProperty(jsonState, jsonType, root);
													obj->AddValues(obj, netprop);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}
}

NetworkProperty *createNetworkProperty(struct jsonparse_state *jsonState, char jsonType, ContainerRoot *root)
{
	printf("%s\n", strJson);

	NetworkProperty *obj = new_NetworkProperty();

	while((jsonType = jsonparse_next(jsonState)) != JSON_TYPE_OBJECT)
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			break;
		}
	}

}

ComponentInstance * createComponentInstance(struct jsonparse_state *jsonState, char jsonType, ContainerRoot *root)
{
	printf("%s\n", strJson);

	ComponentInstance *obj = new_ComponentInstance();

	while((jsonType = jsonparse_next(jsonState)) != JSON_TYPE_OBJECT)
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "metaData"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "started"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						obj->super->started = atoi(strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "provided"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "required"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, sizeof strJson);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, sizeof strJson);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}

	return obj;

	/*ComponentInstance *ptr = (ComponentInstance*)malloc(sizeof(ComponentInstance));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate ComponentInstance \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptComponentInstance;
		ptr->typedefinition = NULL;

	}

	return ptr;*/
}

Group * createGroup(void)
{
	Group *ptr = (Group*)malloc(sizeof(Group));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate Group \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptGroup;
		ptr->count_subNodes = 0;
		ptr->subNodes = NULL;
	}

	return ptr;
}



TypeDefinition* createTypeDefinition(void)
{
	TypeDefinition *ptr = (TypeDefinition*)malloc(sizeof(TypeDefinition));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate TypeDefinition \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptTypeDefinition;
	}

	return ptr;
}



NodeNetwork* createNodeNetwork(void)
{
	NodeNetwork *ptr = (NodeNetwork*)malloc(sizeof(NodeNetwork));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate NodeNetwork \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptNodeNetwork;
	}

	return ptr;
}

DeployUnit * createDeployUnit(void)
{
	DeployUnit *ptr = (DeployUnit*)malloc(sizeof(DeployUnit));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate DeployUnit \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptDeployUnit;
		ptr->name = NULL;
		ptr->groupName = NULL;
		ptr->version = NULL;
		ptr->type = NULL;
	}

	return ptr;
}
