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

/*---------------------------------------------- SerializerAttributeVisitor ----------------------------------------*/
/*public:
	SerializerAttributeVisitor (std::string *out)
{
		this->out = out;
}*/
SerializerAttributeVisitor* new_SerializerAttributeVisitor(char* out)
{
	SerializerAttributeVisitor* pSerAttrVisitObj = NULL;

	/* Allocating memory */
	pSerAttrVisitObj = (SerializerAttributeVisitor*)malloc(sizeof(SerializerAttributeVisitor));

	if(pSerAttrVisitObj == NULL)
		return NULL;

	pSerAttrVisitObj->out = out;

	pSerAttrVisitObj->Visit = SerializerAttributeVisitor_Visit;
	pSerAttrVisitObj->Delete = delete_SerializerAttributeVisitor;

	return pSerAttrVisitObj;
}

void delete_SerializerAttributeVisitor(SerializerAttributeVisitor* const this)
{
	if(this != NULL)
	{
		free(this->out);
		free(this);
		this = NULL;
	}
}

/* void  visit(any val,string name,KMFContainer *parent) */
void SerializerAttributeVisitor_Visit(SerializerAttributeVisitor* const this, char* path, Type type, void* value)
{
	/*if(!val.empty ())*/
	if(path != NULL && value != NULL)
	{
		/*out->append(",\n\"" + name + "\":\"");*/
		sprintf(this->out, "%s,\n\"%s\":\"", this->out, path);

		char* strData = NULL;
		int iData = -1;

		/*if (!val.empty () && val.type () == typeid (string) )
		{
			data =AnyCast < string>(val);
		}else  if(!val.empty () && val.type () == typeid (int))
		{
			data =AnyCast < int>(val);;
		}else  if(!val.empty () && val.type () == typeid (short))
		{
			data =AnyCast <short>(val);;
		} else  if(!val.empty () && val.type () == typeid (bool))
		{
			if(AnyCast<bool>(val) == true)
			{
				data ="true";
			} else
			{
				data  ="false";
			}
		}
		else{
			LOGGER_WRITE(Logger::ERROR,"The SerializerAttributeVisitor::visit the type is not supported of "+name+" his parent his "+parent->path());
		}*/

		switch(type)
		{
			case STRING:
				strData = malloc(sizeof(value));
				strcpy(strData, value);
				break;

			case BOOL:
				if((int)value == 1)
				{
					strData = malloc(strlen("true") + 1);
					strcpy(strData, "true");

				}
				else
				{
					strData = malloc(strlen("false") + 1);
					strcpy(strData, "false");
				}
				break;

			case INTEGER:
				strData = malloc(sizeof value);
				sprintf(strData, "%d", (int)value);
				break;
		}

		/*out->append(data);
		out->append("\"");*/
		sprintf(this->out, "%s%s\"", this->out, strData);
		free(strData);
	}
}
/*------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------- ModelReferenceVisitor ---------------------------------------------*/
/*public:
	ModelReferenceVisitor(std::string *_out)
{
		isFirst=true;
		this->out = _out;

}*/
ModelReferenceVisitor* new_ModelReferenceVisitor(char* _out)
{
	ModelReferenceVisitor* pModRefVisit = NULL;

	pModRefVisit = (ModelReferenceVisitor*)malloc(sizeof(ModelReferenceVisitor));

	if(pModRefVisit == NULL)
		return NULL;

	pModRefVisit->out = _out;
	pModRefVisit->isFirst = 1;

	pModRefVisit->BeginVisitRef = ModelReferenceVisitor_BeginVisitRef;
	pModRefVisit->EndVisitRef = ModelReferenceVisitor_EndVisitRef;
	pModRefVisit->Visit = ModelReferenceVisitor_Visit;
	pModRefVisit->Delete = delete_ModelReferenceVisitor;

	return pModRefVisit;
}

void delete_ModelReferenceVisitor(ModelReferenceVisitor* const this)
{
	if(this != NULL)
	{
		free(this->out);
		free(this);
		this = NULL;
	}
}

/*void beginVisitRef(string refName,string refType)*/
void ModelReferenceVisitor_BeginVisitRef(ModelReferenceVisitor* const this, char* refName)
{
	/*out->append(",\n\"" + refName + "\":[");*/
	sprintf(this->out, "%s,\n\"%s\":[", this->out, refName);
	/*isFirst = true;*/
	this->isFirst = 1;
}

/*void endVisitRef(string refName)*/
void ModelReferenceVisitor_EndVisitRef(ModelReferenceVisitor* const this)
{
	/*out->append("]");*/
	sprintf(this->out, "%s]", this->out);
}

/*void visit(KMFContainer *elem,string refNameInParent, KMFContainer* parent)*/
void ModelReferenceVisitor_Visit(ModelReferenceVisitor* const this, char* path)
{
	/*if(!isFirst)*/
	if(!this->isFirst)
	{
		/*out->append(",\n");*/
		sprintf(this->out, "%s,\n", this->out);
	}
	else
	{
		/*isFirst = false;*/
		this->isFirst = 0;
	}

	/*out->append("\"" + elem->path() + "\"");*/
	sprintf(this->out, "%s\"%s\"", this->out, path);
}
/*------------------------------------------------------------------------------------------------------------------*/

/*public:
	ModelMasterVisitor(std::string *_out)
{
		isFirstInRef=true;
		out = _out;
		internalReferenceVisitor =new ModelReferenceVisitor(_out);
}*/
ModelMasterVisitor* new_ModelMasterVisitor(char* _out)
{
	ModelMasterVisitor* pModMasterVisit = NULL;

	pModMasterVisit = (ModelMasterVisitor*)malloc(sizeof(ModelMasterVisitor));

	if(pModMasterVisit == NULL)
		return NULL;

	pModMasterVisit->isFirstInRef = 1;
	pModMasterVisit->out = _out;
	pModMasterVisit->internalReferenceVisitor = new_ModelReferenceVisitor(_out);

	pModMasterVisit->PrintAtName = ModelMasterVisitor_PrintAtName;
	pModMasterVisit->BeginVisitElem = ModelMasterVisitor_BeginVisitElem;
	pModMasterVisit->EndVisitElem = ModelMasterVisitor_EndVisitElem;
	pModMasterVisit->BeginVisitRef = ModelMasterVisitor_BeginVisitRef;
	pModMasterVisit->EndVisitRef = ModelMasterVisitor_EndVisitRef;
	pModMasterVisit->Delete = delete_ModelMasterVisitor;

	return pModMasterVisit;
}

void delete_ModelMasterVisitor(ModelMasterVisitor* const this)
{
	if(this != NULL)
	{
		this->isFirstInRef = -1;
		free(this->out);
		free(this->internalReferenceVisitor);
		free(this);
		this = NULL;
	}
}

/*void printAttName(KMFContainer *elem,string *out)*/
void ModelMasterVisitor_PrintAtName(ModelMasterVisitor* const this, void* value, char* out)
{
	/*out->append("\n{\n\"eClass\":\"org.kevoree." + elem->metaClassName() + "\"");*/
	sprintf(this->out, "%s\n{\n\"eClass\":\"org.kevoree.%s\"", this->out, value->MetaClassName(value));
	/*SerializerAttributeVisitor *attributeVisitor = new SerializerAttributeVisitor(out);*/
	SerializerAttributeVisitor *attributeVisitor = new_SerializerAttributeVisitor(out);
	/*elem->visitAttributes(attributeVisitor);*/
	value->VisitAttributes(attributeVisitor);
	/*delete attributeVisitor;*/
	delete_SerializerAttributeVisitor(attributeVisitor);
}

void ModelMasterVisitor_BeginVisitElem(ModelMasterVisitor* const this, void* value);
void ModelMasterVisitor_EndVisitElem(ModelMasterVisitor* const this);
void ModelMasterVisitor_BeginVisitRef(ModelMasterVisitor* const this, char* refName);
void ModelMasterVisitor_EndVisitRef(ModelMasterVisitor* const this);

	void beginVisitElem(KMFContainer *elem)
	{
		if(!isFirstInRef)
		{
			out->append(",\n");
			isFirstInRef = false;
		}


		printAttName(elem, out);
		internalReferenceVisitor->alreadyVisited.clear();
		elem->visit(internalReferenceVisitor, false, false, true);
	}
	void endVisitElem(KMFContainer *elem)
	{
		out->append("}\n");
		isFirstInRef = false;
	}

	void beginVisitRef(string refName,string refType)
	{
		out->append(",\n\"" + refName + "\":[");
		isFirstInRef = true;
	}

	void endVisitRef(string refName)
	{
		out->append("]");
		isFirstInRef = false;
	}

	void visit(KMFContainer *elem,string refNameInParent, KMFContainer* parent)
	{

	}*/

	string JSONModelSerializer::serialize(KMFContainer *model)
	{
		std::string out="";
		ModelMasterVisitor *masterVisitor = new  ModelMasterVisitor(&out);
		model->visit(masterVisitor, true, true, false);
		delete masterVisitor;
	    return out;
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
