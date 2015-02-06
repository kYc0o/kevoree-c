/*#include "DefaultFactorykevoree.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

<<<<<<< Updated upstream
int addContainerRootGroup(ContainerRoot *root, Group *val)
{
	if(root->count_groups == 0)
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
	}

	return 0;
}

int addContainerRootContainerNode(ContainerRoot *root, ContainerNode *val)
{
	if(root->count_nodes == 0)
	{
		PRINTF("DEBUG -- FIRST ADD ContainerNode -> ContainerRoot %d \n", root->count_nodes);
		root->nodes = malloc(1 * sizeof(struct ContainerNode*));
=======
/*KMFFactory *new_KMFFactory()
{
	KMFFactory *pKMFFactoryObj = NULL;

	pKMFFactoryObj = (ContainerRoot*)malloc(sizeof(KMFFactory));

	if(pKMFFactoryObj == NULL)
	{
		return NULL;
	}

	pKMFFactoryObj->createContainerNode = createContainerNode;
	pKMFFactoryObj->createComponentInstance = createComponentInstance;
	pKMFFactoryObj->createGroup = createGroup;
	pKMFFactoryObj->createTypeDefinition = createTypeDefinition;


}*/

ContainerNode *createContainerNode(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
			printf("FATAL can't allocate ContainerNode \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->metaData);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->super->started);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.ComponentInstance"))
												{
													ComponentInstance *component = createComponentInstance(jsonState, jsonType, strJson, root, obj, loader);
													if(component != NULL)
														obj->AddComponents(obj, component);
													else
														PRINTF("Component cannot be added!\n");
												}
												break;
											}
											break;
										}
									}
									else
									{
										PRINTF("Invalid object!\n");
									}
									break;
								}
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
				}
			}
			else if(!strcmp(strJson, "hosts"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							JSONKevDeserializer(jsonState, jsonType, NULL);
							break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "host"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							 * TODO add host references
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "groups"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							 * TODO add hosts references
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								Group *group = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for Group %s\n", id);

								group = root->FindGroupsByID(root, id);

								if(group != NULL)
								{
									PRINTF("Group %s found!\n", id);
									obj->AddGroups(obj, group);
								}
								else
								{
									PRINTF("Group %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("nodes[]") * strlen(obj->InternalGetKey(obj)) + 1);
									sprintf(objId, "nodes[%s]", obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "networkInformation"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.NetworkInfo"))
												{
													NetworkInfo *netInfo = createNetworkInfo(jsonState, jsonType, strJson);
													if(netInfo != NULL)
														obj->AddNetworkInformation(obj, netInfo);
													else
														PRINTF("NetworkInfo cannot be added!\n");
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
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("nodes[]") * strlen(obj->InternalGetKey(obj)) + 1);
									sprintf(objId, "nodes[%s]", obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.Dictionary"))
												{
													Dictionary *dic = createDictionary(jsonState, jsonType, strJson);
													obj->super->AddDictionary(obj->super, dic);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;

								case JSON_TYPE_STRING:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_INT:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_NUMBER:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson);
													if(fragdic != NULL)
													{
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													}
													else
													{
														PRINTF("DictionaryValue cannot be created!\n");
													}
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
>>>>>>> Stashed changes
		}

		root->nodes[root->count_nodes] = (struct ContainerNode*)val;
		root->count_nodes++;
	}
<<<<<<< Updated upstream

	return 0;
=======
	PRINTF("\t}\n");
	return obj;
>>>>>>> Stashed changes
}

int addContainerRootNodeNetwork(ContainerRoot *root, NodeNetwork *val)
{
<<<<<<< Updated upstream
	if(root->count_nodeNetworks == 0)
	{
		PRINTF("DEBUG -- FIRST ADD NodeNetwork -> ContainerRoot %d \n", root->count_nodeNetworks);
		root->nodeNetworks = malloc(1 * sizeof(struct NodeNetwork*));
=======
	PRINTF("%s\n", strJson);
	NetworkInfo *obj = new_NetworkInfo();
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.NetworkProperty"))
												{
													NetworkProperty *netprop = createNetworkProperty(jsonState, jsonType, strJson);
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
>>>>>>> Stashed changes
		}

		root->nodeNetworks[root->count_nodeNetworks] = (struct NodeNetwork*)val;
		root->count_nodeNetworks++;
	}
<<<<<<< Updated upstream

	return 0;
=======
	PRINTF("\t}\n");
	return obj;
>>>>>>> Stashed changes
}

int addContainerRootTypeDefinition(ContainerRoot *root, TypeDefinition *val)
{
<<<<<<< Updated upstream
	if(root->count_typedefintions == 0)
	{
		PRINTF("DEBUG -- FIRST ADD TypeDefinition -> ContainerRoot %d \n",root->count_typedefintions);
		root->typedefintions = malloc(1 * sizeof(struct TypeDefinition*));
=======
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
			printf("FATAL can't allocate TypeDefinition \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "value"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->value = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->value, strJson);
						PRINTF("%s -> %s\n", strJson, obj->value);
						break;
					}
					break;
				}
			}
			break;
>>>>>>> Stashed changes
		}

		root->typedefintions[root->count_typedefintions] =(struct TypeDefinition*)val;
		root->count_typedefintions++;
	}
<<<<<<< Updated upstream

	return 0;
}

int addContainerRootDeployUnit(ContainerRoot *root, DeployUnit *val)
{
	if(root->count_deployUnits == 0)
	{
		PRINTF("DEBUG -- FIRST ADD DeployUnit -> ContainerRoot %d \n",root->count_deployUnits);
		root->deployUnits = malloc(1 * sizeof(struct DeployUnit*));
=======
	PRINTF("\t}\n");
	return obj;
}

ComponentInstance *createComponentInstance(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, ContainerNode *node, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
			printf("FATAL can't allocate DeployUnit \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->metaData);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->super->started);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("nodes[]/components[]") * strlen(obj->InternalGetKey(obj)) * strlen(node->InternalGetKey(node)) + 1);
									sprintf(objId, "nodes[%s]/components[%s]", node->InternalGetKey(node), obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.Dictionary"))
												{
													Dictionary *dic = createDictionary(jsonState, jsonType, strJson);
													obj->super->AddDictionary(obj->super, dic);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;

								case JSON_TYPE_STRING:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_INT:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_NUMBER:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson);
													if(fragdic != NULL)
													{
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													}
													else
													{
														PRINTF("DictionaryValue cannot be created!\n");
													}
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
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
>>>>>>> Stashed changes
		}

		root->count_deployUnits[root->count_deployUnits] =(struct DeployUnit*)val;
		root->count_deployUnits++;
	}
<<<<<<< Updated upstream

	return 0;
}

int addContainerNodeComponentInstance(ContainerNode *node, ComponentInstance *val)
{
	if(node->count_components== 0)
	{
		PRINTF("DEBUG -- FIRST ADD ComponentInstance -> ContainerNode %d \n", node->count_components);
		node->components = malloc(1 * sizeof(struct ComponentInstance*));
=======
	PRINTF("\t}\n");
	return obj;
}

Dictionary *createDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	PRINTF("%s\n", strJson);

	Dictionary *obj = new_Dictionary();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->generated_KMF_ID, strJson);
						PRINTF("%s -> %s\n", strJson, obj->generated_KMF_ID);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryType"))
												{
													DictionaryValue *dicval = createDictionaryValue(jsonState, jsonType, strJson);
													obj->AddValues(obj, dicval);
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

Group *createGroup(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
			printf("FATAL can't allocate ComponentInstance \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->metaData);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->super->started);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("groups[]") * strlen(obj->InternalGetKey(obj)) + 1);
									sprintf(objId, "groups[%s]", obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "subNodes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																					JSONKevDeserializer(jsonState, jsonType, NULL);
																					break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								ContainerNode *node = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for SubNode %s\n", id);

								node = root->FindNodesByID(root, id);

								if(node != NULL)
								{
									PRINTF("SubNode %s found!\n", id);
									obj->AddSubNodes(obj, node);
								}
								else
								{
									PRINTF("Node %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("groups[]") * strlen(obj->InternalGetKey(obj)) + 1);
									sprintf(objId, "groups[%s]", obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
									/*node = new_ContainerNode();
									if(node != NULL)
									{
										node->super->super->name = malloc(sizeof(char) * strlen(id) + 1);
										strcpy(node->super->super->name, id);

										PRINTF("Node created with id: %d", node->super->super->name)
										obj->AddSubNodes(obj, node);
									}
									else
									{
										PRINTF("Cannot create SubNode reference\n");
									}*/
								}
								/*PRINTF("SubNode cannot be found!\n");*/
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
															JSONKevDeserializer(jsonState, jsonType, NULL);
															break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson);
													if(fragdic != NULL)
													{
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													}
													else
													{
														PRINTF("DictionaryValue cannot be created!\n");
													}
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
>>>>>>> Stashed changes
		}

		node->components[node->count_components] =(struct ComponentInstance*)val;
		node->count_components++;
	}
<<<<<<< Updated upstream

	return 0;
=======
	PRINTF("\t}\n");
	return obj;
>>>>>>> Stashed changes
}

int addContainerNodeNodeNetwork(ContainerNode *node, NodeNetwork *val)
{
<<<<<<< Updated upstream
	if(node->count_nodeNetworks == 0)
	{
		PRINTF("DEBUG -- FIRST ADD NodeNetwork -> ContainerNode %d \n",node->count_nodeNetworks);
		node->nodeNetworks = malloc(1 * sizeof(struct NodeNetwork*));

		if(node->nodeNetworks == NULL)
		{
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
		}
=======
	PRINTF("%s\n", strJson);
	FragmentDictionary *obj = new_FragmentDictionary();
>>>>>>> Stashed changes

		node->nodeNetworks[node->count_nodeNetworks] = (struct NodeNetwork*)val;
		node->count_nodeNetworks++;
	}
	else
	{
		node->nodeNetworks = realloc(node->nodeNetworks,(node->count_nodeNetworks+1)*sizeof(struct NodeNetwork*));

		if(node->nodeNetworks == NULL)
		{
<<<<<<< Updated upstream
			printf("FATAL can't allocate NodeNetwork \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->super->generated_KMF_ID, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->generated_KMF_ID);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->name);
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryValue"))
												{
													DictionaryValue *dicval = createDictionaryValue(jsonState, jsonType, strJson);
													if(dicval != NULL)
													{
														Dictionary *dico = obj->super;
														dico->AddValues(dico, dicval);
													}
													else
													{
														PRINTF("DictionaryValue cannot be created!\n");
													}
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
>>>>>>> Stashed changes
		}

		node->nodeNetworks[node->count_nodeNetworks] =(struct NodeNetwork*)val;
		node->count_nodeNetworks++;
	}
<<<<<<< Updated upstream

	return 0;
=======
	PRINTF("\t}\n");
	return obj;
>>>>>>> Stashed changes
}

int addGroupContainerNode(Group *group, ContainerNode *val)
{
<<<<<<< Updated upstream
	if(group->count_subNodes == 0)
	{
		PRINTF("DEBUG -- FIRST ADD ContainerNode -> Group %d \n",group->count_subNodes);
		group->subNodes = malloc(1*sizeof(struct ContainerNode*));
=======
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
			printf("FATAL can't allocate ContainerNode \n");
			return -1;
=======
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "value"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->value = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->value, strJson);
						PRINTF("%s -> %s\n", strJson, obj->value);
						break;
					}
					break;
				}
			}
			break;
>>>>>>> Stashed changes
		}

		group->subNodes[group->count_subNodes] = (struct ContainerNode*)val;
		group->count_subNodes++;
	}
<<<<<<< Updated upstream

	return 0;
}

ContainerRoot *createContainerRoot(void)
{
	ContainerRoot *ptr = (ContainerRoot*)malloc(sizeof(ContainerRoot));

	if(ptr == NULL)
=======
	PRINTF("\t}\n");
	return obj;
}

TypeDefinition *createTypeDefinition(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);

	TypeDefinition *obj = NULL;

	if(!strcmp(strJson, "org.kevoree.NodeType"))
>>>>>>> Stashed changes
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
	}

	return ptr;
}

ContainerNode * createContainerNode(void)
{
	ContainerNode *ptr = (ContainerNode*)malloc(sizeof(ContainerNode));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate ContainerNode \n");
		return NULL;
	}
	else
	{
<<<<<<< Updated upstream
		ptr->accept = _acceptContainerNode;
		ptr->started = 0;
		ptr->count_components = 0;
		ptr->components = NULL;
		ptr->typedefintion = NULL;
		ptr->count_nodeNetworks = 0;
		ptr->nodeNetworks = NULL;
	}

	return ptr;
}

ComponentInstance * createComponentInstance(void)
{
	ComponentInstance *ptr = (ComponentInstance*)malloc(sizeof(ComponentInstance));

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

	return ptr;
=======
		PRINTF("TypeDefinition %s not supported!\n", strJson);
		return NULL;
	}

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "version"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->version = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->version, strJson);
						PRINTF("%s -> %s\n", strJson, obj->version);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "factoryBean"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->factoryBean = malloc(sizeof(char) * strlen(strJson) + 1); /*atoi(strJson);*/
						strcpy(obj->factoryBean, strJson);
						PRINTF("%s -> %s\n", strJson, obj->factoryBean);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "bean"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->bean = malloc(sizeof(char) * strlen(strJson) + 1); /*atoi(strJson);*/
						strcpy(obj->bean, strJson);
						PRINTF("%s -> %s\n", strJson, obj->bean);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "abstract"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->abstract = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->abstract);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "deployUnit"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								DeployUnit *du = NULL;
								char id[100];
								memset(&id[0], 0, sizeof(id));
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for DeployUnit %s\n", id);

								du = root->FindDeployUnitsByID(root, id);

								if(du != NULL)
								{
									PRINTF("DeployUnit %s found!\n", id);
									obj->AddDeployUnit(obj, du);
								}
								else
								{
									PRINTF("DeployUnit %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("typeDefinitions[]") * strlen(obj->InternalGetKey(obj)) + 1);
									sprintf(objId, "typeDefinitions[%s]", obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
								/*case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;*/

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "superTypes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionaryType"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryType"))
												{
													DictionaryType *dictype = createDictionaryType(jsonState, jsonType, strJson);
													if(dictype != NULL)
														obj->AddDictionaryType(obj, dictype);
													else
														return NULL;
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
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
>>>>>>> Stashed changes
}

Group * createGroup(void)
{
<<<<<<< Updated upstream
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

=======
	PRINTF("%s\n", strJson);

	DictionaryType *obj = new_DictionaryType();

	if(obj == NULL)
		return NULL;

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		PRINTF("jsonType: %c\n", jsonType);
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->generated_KMF_ID, strJson);
						PRINTF("%s -> %s\n", strJson, obj->generated_KMF_ID);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "attributes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryAttribute"))
												{
													DictionaryAttribute *dicattr = createDictionaryAttribute(jsonState, jsonType, strJson);
													obj->AddAttributes(obj, dicattr);
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

DictionaryAttribute *createDictionaryAttribute(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes


TypeDefinition* createTypeDefinition(void)
{
	TypeDefinition *ptr = (TypeDefinition*)malloc(sizeof(TypeDefinition));

	if(ptr == NULL)
	{
<<<<<<< Updated upstream
		printf("FATAL can't allocate TypeDefinition \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptTypeDefinition;
	}

	return ptr;
=======
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "optional"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->optional = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->optional);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "state"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->state = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->state);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "datatype"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->datatype = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->datatype, strJson);
						PRINTF("%s -> %s\n", strJson, obj->datatype);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDependant"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->fragmentDependant = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->fragmentDependant);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "defaultValue"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->defaultValue = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->defaultValue, strJson);
						PRINTF("%s -> %s\n", strJson, obj->defaultValue);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
>>>>>>> Stashed changes
}



NodeNetwork* createNodeNetwork(void)
{
	NodeNetwork *ptr = (NodeNetwork*)malloc(sizeof(NodeNetwork));

	if(ptr == NULL)
	{
		PRINTF("FATAL can't allocate NodeNetwork \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptNodeNetwork;
	}

	return ptr;
}

<<<<<<< Updated upstream
DeployUnit * createDeployUnit(void)
{
	DeployUnit *ptr = (DeployUnit*)malloc(sizeof(DeployUnit));
=======
TypeLibrary *createTypeLibrary(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);
>>>>>>> Stashed changes

	if(ptr == NULL)
	{
<<<<<<< Updated upstream
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
}*/
=======
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "subTypes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																					JSONKevDeserializer(jsonState, jsonType, NULL);
																					break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->AddSubTypes(obj, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("libraries[]") * strlen(obj->InternalGetKey(obj)) + 1);
									sprintf(objId, "libraries[%s]", obj->InternalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
									/*typdef = new_TypeDefinition();
									if(typdef != NULL)
									{
										char *nextToken;
										nextToken = strtok(id, "/");

										typdef->super->name = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->super->name, nextToken);

										nextToken = strtok(NULL, "/");

										typdef->version = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->version, nextToken);

										obj->AddSubTypes(obj, typdef);
									}
									else
									{
										PRINTF("Cannot create TypeDefinition reference\n");
									}*/
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

DeployUnit * createDeployUnit(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	PRINTF("%s\n", strJson);

	DeployUnit *obj = new_DeployUnit();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "groupName"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->groupName = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->groupName, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "version"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						/*obj->state = atoi(strJson);*/
						obj->version = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->version, strJson);
						PRINTF("%s -> %s\n", strJson, obj->version);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "url"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->url = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->url, strJson);
						PRINTF("%s -> %s\n", strJson, obj->url);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "hashcode"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->hashcode = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->hashcode, strJson);
						PRINTF("%s -> %s\n", strJson, obj->hashcode);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "type"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->type = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->type, strJson);
						PRINTF("%s -> %s\n", strJson, obj->type);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}
>>>>>>> Stashed changes
