#include "ModelTrace.h"

/**
 * Author: fco.ja.ac@gmail.com
 * Date: 21/07/2014
 * Time: 17:55
 */

ModelTrace* new_ModelTrace()
{
	ModelTrace* pObj = NULL;
	/* Allocating memory */
	pObj = (ModelTrace*)my_malloc(sizeof(ModelTrace));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;
	
	pObj->srcPath = NULL;
	pObj->refName = NULL;
	
	pObj->ToString = ModelTrace_ToString;
	pObj->Delete = delete_ModelTrace;
}

void delete_ModelTrace(void* const this)
{
	if(this != NULL)
	{
		free(((ModelTrace*)this)->srcPath);
		free(((ModelTrace*)this)->refName);
		free(this);
	}
}

char* ModelTrace_ToString(void* const this)
{
  
}

/*ModelSetTrace::ModelSetTrace (string _srcPath, string _refName, string _objPath, string _content, string _typeName)
{
	srcPath = _srcPath;
	refName = _refName;
	typeName = _typeName;
	content = _content;
	typeName = _typeName;
}*/

ModelTrace* newPoly_ModelSetTrace(char* _srcPath, char* _refName, char* _objPath, char* _content, char* _typeName)
{
	ModelSetTrace* pModSetTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModSetTraceObj = (ModelSetTrace*)my_malloc(sizeof(ModelSetTrace));

	if (pModSetTraceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pModSetTraceObj; /* Pointing to derived object */
	
	pObj->srcPath = my_malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = my_malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModSetTraceObj->objPath = my_malloc(sizeof(char)*(strlen(_objPath)+1));
	strcpy(pModSetTraceObj->objPath, _objPath);
	pModSetTraceObj->content = my_malloc(sizeof(char)*(strlen(_content)+1));
	strcpy(pModSetTraceObj->content, _content);
	pModSetTraceObj->typeName = my_malloc(sizeof(char)*(strlen(_typeName)+1));
	strcpy(pModSetTraceObj->typeName, _typeName);
	
	pModSetTraceObj->Delete = delete_ModelSetTrace;
	pModSetTraceObj->ToString = ModelSetTrace_ToString;
	pObj->ToString = ModelSetTrace_ToString;

	return pObj;
}

ModelSetTrace* new_ModelSetTrace(char* _srcPath, char* _refName, char* _objPath, char* _content, char* _typeName)
{
	ModelSetTrace* pModSetTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModSetTraceObj = (ModelSetTrace*)my_malloc(sizeof(ModelSetTrace));

	if (pModSetTraceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pModSetTraceObj->super = pObj;
	
	pObj->srcPath = my_malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = my_malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModSetTraceObj->objPath = my_malloc(sizeof(char)*(strlen(_objPath)+1));
	strcpy(pModSetTraceObj->objPath, _objPath);
	pModSetTraceObj->content = my_malloc(sizeof(char)*(strlen(_content)+1));
	strcpy(pModSetTraceObj->content, _content);
	pModSetTraceObj->typeName = my_malloc(sizeof(char)*(strlen(_typeName)+1));
	strcpy(pModSetTraceObj->typeName, _typeName);
	
	pModSetTraceObj->Delete = delete_ModelSetTrace;
	pModSetTraceObj->ToString = ModelSetTrace_ToString;
	pObj->ToString = ModelSetTrace_ToString;

	return pModSetTraceObj;
}

void deletePoly_ModelSetTrace(void* const this)
{
	ModelSetTrace* pModSetTraceObj;
	pModSetTraceObj = ((ModelTrace*)this)->pDerivedObj;
	/*destroy derived obj*/
	free(pModSetTraceObj->objPath);
	free(pModSetTraceObj->content);
	free(pModSetTraceObj->typeName);
	free(pModSetTraceObj);
	/*destroy base Obj*/
	delete_ModelTrace(this);
}

void delete_ModelSetTrace(void* const this)
{
	/* destroy base object */
	delete_ModelTrace(((ModelSetTrace*)this)->super);
	/* destroy data memebers */
	free(((ModelSetTrace*)this)->objPath);
	free(((ModelSetTrace*)this)->content);
	free(((ModelSetTrace*)this)->typeName);
	free(this);
}

/*std::string ModelSetTrace::toString ()*/
char* ModelSetTrace_ToString(void* const this)
{
	/*string buffer = "";*/
	char* buffer = NULL;
	
	/*buffer.append ("{ \"traceType\" : " + ActionType (SET) + " , \"src\" : \"" + srcPath + "\", \"refname\" : \"" + refName + "\"");*/
	sprintf(buffer, "{ \"traceType\" : %s, \"src\" : \"%s\", \"refname\" : \"%s\"", ActionType(SET), ((ModelSetTrace*)this)->super->srcPath, ((ModelSetTrace*)this)->super->refName);
	
	/*if (!objPath.empty ())*/
	if(((ModelSetTrace*)this)->objPath != NULL)
	{
		/*buffer.append (", \"objpath\" : \"" + objPath + "\"");*/
		sprintf(buffer, "%s, \"objpath\" : \"%s\"", buffer, ((ModelSetTrace*)this)->objPath);
	}
	/*if (!content.empty ())*/
	if(((ModelSetTrace*)this)->content != NULL)
	{
		/*buffer.append (", \"content\" : \"" + content + "\"");*/
		sprintf(buffer, "%s, \"content\" : \" %s \"", buffer, ((ModelSetTrace*)this)->content);
	}
	/*if (!typeName.empty ())*/
	if(((ModelSetTrace*)this)->typeName != NULL)
	{
		/*buffer.append (", \"typename\" : \"" + typeName + "\"");*/
		sprintf(buffer, "%s, \"typename\" : \"%s\"", buffer, ((ModelSetTrace*)this)->typeName);
	}
	
	/*buffer.append ("}\n");*/
	sprintf(buffer, "%s }\n", buffer);

	return buffer;
}  

/*ModelAddTrace::ModelAddTrace(string _srcPath, string _refName, string _previousPath,string _typeName)
{
	srcPath  =_srcPath;
	refName=_refName;
	previousPath =_previousPath;
	typeName=_typeName;
}*/

ModelTrace* newPoly_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName)
{
	ModelAddTrace* pModAddTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModAddTraceObj = (ModelAddTrace*)my_malloc(sizeof(ModelAddTrace));

	if (pModAddTraceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pModAddTraceObj; /* Pointing to derived object */
	
	pObj->srcPath = my_malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = my_malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModAddTraceObj->previousPath = my_malloc(sizeof(char)*(strlen(_previousPath)+1));
	strcpy(pModAddTraceObj->previousPath, _previousPath);
	pModAddTraceObj->typeName = my_malloc(sizeof(char)*(strlen(_typeName)+1));
	strcpy(pModAddTraceObj->typeName, _typeName);
	
	pModAddTraceObj->Delete = delete_ModelAddTrace;
	pModAddTraceObj->ToString = ModelAddTrace_ToString;
	pObj->ToString = ModelAddTrace_ToString;

	return pObj;
}

ModelAddTrace* new_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName)
{
	ModelAddTrace* pModAddTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModAddTraceObj = (ModelAddTrace*)my_malloc(sizeof(ModelAddTrace));

	if (pModAddTraceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pModAddTraceObj->super = pObj;
	
	pObj->srcPath = my_malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = my_malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModAddTraceObj->previousPath = my_malloc(sizeof(char)*(strlen(_previousPath)+1));
	strcpy(pModAddTraceObj->previousPath, _previousPath);
	pModAddTraceObj->typeName = my_malloc(sizeof(char)*(strlen(_typeName)+1));
	strcpy(pModAddTraceObj->typeName, _typeName);
	
	pModAddTraceObj->Delete = delete_ModelAddTrace;
	pModAddTraceObj->ToString = ModelAddTrace_ToString;
	pObj->ToString = ModelAddTrace_ToString;

	return pModAddTraceObj;
}

void deletePoly_ModelAddTrace(void* const this)
{
	ModelAddTrace* pModAddTraceObj;
	pModAddTraceObj = ((ModelTrace*)this)->pDerivedObj;
	/*destroy derived obj*/
	free(pModAddTraceObj->previousPath);
	free(pModAddTraceObj->typeName);
	/*destroy base Obj*/
	delete_ModelTrace(this);
}

void delete_ModelAddTrace(void* const this)
{
	/* destroy base object */
	delete_ModelTrace(((ModelAddTrace*)this)->super);
	/* destroy data memebers */
	free(((ModelAddTrace*)this)->previousPath);
	free(((ModelAddTrace*)this)->typeName);
	free(this);
}

/*std::string ModelAddTrace::toString ()*/
char* ModelAddTrace_ToString(void* const this)
{
	/*string buffer = "";*/
	char* buffer = NULL;

	/*buffer.append ("{ \"traceType\" : " + ActionType (ADD) + " , \"src\" : \"" + srcPath + "\", \"refname\" : \"" + refName + "\"");*/
	sprintf(buffer, "{ \"traceType\" : %s, \"src\" : \"%s\", \"refname\" : \"%s\"", ActionType(ADD), ((ModelAddTrace*)this)->super->srcPath, ((ModelAddTrace*)this)->super->refName);
	
	/*if (!previousPath.empty ())*/
	if(((ModelAddTrace*)this)->previousPath != NULL)
	{
		/*buffer.append (", \"previouspath\" : \"" + previousPath + "\"");*/
		sprintf(buffer, "%s, \"previouspath\" : \"%s\"", buffer, ((ModelAddTrace*)this)->previousPath);
	}
	/*if (!typeName.empty ())*/
	if(((ModelAddTrace*)this)->typeName != NULL)
	{
		/*buffer.append (", \"typename\" : \"" + typeName + "\"");*/
		sprintf(buffer, "%s, \"typename\" : \"%s\"", buffer, ((ModelAddTrace*)this)->typeName);
	}
	/*buffer.append ("}\n");*/
	sprintf(buffer, "%s }\n", buffer);
	return buffer;
}


/*ModelAddAllTrace::~ModelAddAllTrace(){

}

ModelAddAllTrace::ModelAddAllTrace (string _srcPath, string _refName,list < string > &_previousPath, list < string > &_typeName)
{
	srcPath = _srcPath;
	refName = _refName;
	previousPath = _previousPath;
	typeName = _typeName;

}

std::string ModelAddAllTrace::toString ()
{
	string buffer;
	buffer.append ("{ \"traceType\" : " + ActionType (ADD_ALL) +
			" , \"src\" : \"" + srcPath + "\", \"refname\" : \"" +
			refName + "\"");
	if (!previousPath.empty ())
	{
		buffer.append (", \"previouspath\" : \"" + mkString (previousPath) +
				"\"");
	}
	if (typeName.empty ())
	{
		buffer.append (", \"typename\" : \"" + mkString (typeName) + "\"");
	}
	buffer.append ("}\n");
	return buffer;
}

std::string ModelAddAllTrace::mkString (list < string > ss){

	string buffer;
	if (!ss.empty ())
	{
		return buffer;
	}
	std::list < std::string >::iterator it;
	bool isFirst = true;
	for (it = ss.begin (); it != ss.end (); ++it)
	{
		if (!isFirst)
		{
			buffer.append (",");
		}
		buffer.append (*it);
		isFirst = false;
	}
	return buffer;
}*/

/*ModelRemoveTrace::ModelRemoveTrace (string _srcPath, string _refName, string _objPath)
{
	srcPath = _srcPath;
	refName = _refName;
	objPath = _objPath;
}*/

ModelTrace* newPoly_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath)
{
	ModelRemoveTrace* pModRemTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModRemTraceObj = (ModelRemoveTrace*)my_malloc(sizeof(ModelRemoveTrace));

	if (pModRemTraceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pModRemTraceObj; /* Pointing to derived object */
	
	pObj->srcPath = my_malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = my_malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModRemTraceObj->objPath = my_malloc(sizeof(char)*(strlen(_objPath)+1));
	strcpy(pModRemTraceObj->objPath, _objPath);
	
	pModRemTraceObj->Delete = delete_ModelRemoveTrace;
	pModRemTraceObj->ToString = ModelRemoveTrace_ToString;
	pObj->ToString = ModelRemoveTrace_ToString;

	return pObj;
}

/*ModelRemoveTrace::~ModelRemoveTrace(){

}*/

void deletePoly_ModelRemoveTrace(void* const this)
{
	ModelSetTrace* pModSetTraceObj;
	pModSetTraceObj = ((ModelTrace*)this)->pDerivedObj;
	/*destroy derived obj*/
	free(pModSetTraceObj->objPath);
	/*destroy base Obj*/
	delete_ModelTrace(this);
}

void delete_ModelRemoveTrace(void* const this)
{
	/* destroy base object */
	delete_ModelTrace(((ModelRemoveTrace*)this)->super);
	/* destroy data memebers */
	free(((ModelRemoveTrace*)this)->objPath);
	free(this);
}

ModelRemoveTrace* new_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath)
{
	ModelRemoveTrace* pModRemTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	pModRemTraceObj = (ModelRemoveTrace*)my_malloc(sizeof(ModelRemoveTrace));

	if (pModRemTraceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pModRemTraceObj->super = pObj;

	pObj->srcPath = my_malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = my_malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModRemTraceObj->objPath = my_malloc(sizeof(char)*(strlen(_objPath)+1));
	strcpy(pModRemTraceObj->objPath, _objPath);

	pModRemTraceObj->Delete = delete_ModelRemoveTrace;
	pModRemTraceObj->ToString = ModelRemoveTrace_ToString;
	pObj->ToString = ModelRemoveTrace_ToString;

	return pModRemTraceObj;
}

/*std::string ModelRemoveTrace::toString ()*/
char* ModelRemoveTrace_ToString(void* const this)
{
	/*return "{ \"traceType\" : " + ActionType (REMOVE) + " , \"src\" : \"" + srcPath + "\", \"refname\" : \"" + refName + "\", \"objpath\" : \"" + objPath + "\" }\n";*/
	char* buffer = NULL;

	sprintf("{ \"traceType\" : %s , \"src\" : \" %s \", \"refname\" : \" %s \", \"objpath\" : \" %s \" }\n", ActionType(REMOVE), ((ModelRemoveTrace*)this)->super->srcPath, ((ModelRemoveTrace*)this)->super->refName, ((ModelRemoveTrace*)this)->objPath);
}
