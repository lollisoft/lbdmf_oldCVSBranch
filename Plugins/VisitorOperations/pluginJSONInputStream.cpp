/*...sLicence:0:*/
/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
 The author of this work will be reached by e-Mail or paper mail.
 e-Mail: lothar.behrens@lollisoft.de
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */

/*...e*/
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/

/*...slbJSONInputStream:0:*/
/** \brief Implementation of input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbJSONInputStream : 
	public lb_I_FileOperation {
public:
	lbJSONInputStream();
	virtual ~lbJSONInputStream();
	
	DECLARE_LB_UNKNOWN()

/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_SecurityProvider*) { _CL_VERBOSE << "visit(lb_I_SecurityProvider*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_LOG << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_LOG << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_LOG << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_LOG << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_LOG << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_LOG << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_LOG << "visit(lb_I_KeyBase*)" LOG_ } 
	void LB_STDCALL visit(lb_I_String*); // { _CL_LOG << "visit(lb_I_String*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Integer*) { _CL_LOG << "visit(lb_I_Integer*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Long*) { _CL_LOG << "visit(lb_I_Long*)" LOG_ }
	void LB_STDCALL visit(lb_I_Container*) { _CL_LOG << "visit(lb_I_Container*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Database*) { _CL_LOG << "visit(lb_I_Database*)" LOG_ } 
	void LB_STDCALL visit(lb_I_ColumnBinding*) { _CL_LOG << "visit(lb_I_ColumnBinding*)" LOG_ } 
	void LB_STDCALL visit(lb_I_BoundColumn*) { _CL_LOG << "visit(lb_I_BoundColumn*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Query*) { _CL_LOG << "visit(lb_I_Query*)" LOG_ } 
	void LB_STDCALL visit(lb_I_MVC_View*) { _CL_LOG << "visit(lb_I_MVC_View*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Connection*) { _CL_LOG << "visit(lb_I_Connection*)" LOG_ } 
	void LB_STDCALL visit(lb_I_InterfaceRepository*) { _CL_LOG << "visit(lb_I_InterfaceRepository*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Element*) { _CL_LOG << "visit(lb_I_Element*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Module*) { _CL_LOG << "visit(lb_I_Module*)" LOG_ } 
	void LB_STDCALL visit(lb_I_FunctorEntity*) { _CL_LOG << "visit(lb_I_FunctorEntity*)" LOG_ }
	void LB_STDCALL visit(lb_I_InstanceReference*) { _CL_LOG << "visit(lb_I_InstanceReference*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventHandler*) { _CL_LOG << "visit(lb_I_EventHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventManager*) { _CL_LOG << "visit(lb_I_EventManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventMapper*) { _CL_LOG << "visit(lb_I_EventMapper*)" LOG_ }
	void LB_STDCALL visit(lb_I_EvHandler*) { _CL_LOG << "visit(lb_I_EvHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_Dispatcher*);// { _CL_LOG << "visit(lb_I_Dispatcher*)" LOG_ }
	void LB_STDCALL visit(lb_I_InputStream*) { _CL_LOG << "visit(lb_I_InputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_OutputStream*) { _CL_LOG << "visit(lb_I_OutputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileOperation*) { _CL_LOG << "visit(lb_I_FileOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Locale*) { _CL_LOG << "visit(lb_I_Locale*)" LOG_ }
	void LB_STDCALL visit(lb_I_Parameter*); // { _CL_LOG << "visit(lb_I_Parameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Reference*) { _CL_LOG << "visit(lb_I_Reference*)" LOG_ }
	void LB_STDCALL visit(lb_I_Log*) { _CL_LOG << "visit(lb_I_Log*)" LOG_ }
	void LB_STDCALL visit(lb_I_Plugin*) { _CL_LOG << "visit(lb_I_Plugin*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginImpl*) { _CL_LOG << "visit(lb_I_PluginImpl*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginManager*) { _CL_LOG << "visit(lb_I_PluginManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginModule*) { _CL_LOG << "visit(lb_I_PluginModule*)" LOG_ }
	void LB_STDCALL visit(lb_I_wxFrame*) { _CL_LOG << "visit(lb_I_wxFrame*)" LOG_ }
	void LB_STDCALL visit(lb_I_Window*) { _CL_LOG << "visit(lb_I_Window*)" LOG_ }
	//void LB_STDCALL visit(lb_I_Action*) { _CL_LOG << "visit(lb_I_Action*)" LOG_ }
	//void LB_STDCALL visit(lb_I_DelegatedAction*) { _CL_LOG << "visit(lb_I_DelegatedAction*)" LOG_ }
	void LB_STDCALL visit(lb_I_Form*) { _CL_LOG << "visit(lb_I_Form*)" LOG_ }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { _CL_LOG << "visit(lb_I_MasterDetailFormDefinition*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { _CL_LOG << "visit(lb_I_DatabaseReport*)" LOG_ }
	void LB_STDCALL visit(lb_I_CodeGenerator*) { _CL_LOG << "visit(lb_I_CodeGenerator*)" LOG_ }
	void LB_STDCALL visit(lb_I_Boolean*); // { _CL_LOG << "visit(lb_I_Boolean*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseOperation* pm) { _CL_LOG << "visit(lb_I_DatabaseOperation*)" LOG_ }
	//void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_LOG << "visit(lb_I_ParameterTable*)" LOG_ }
	void LB_STDCALL visit(lb_I_Socket*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer*) { _CL_LOG << "visit(lb_I_Transfer*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_Data*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_DataObject*) { _CL_LOG << "visit(lb_I_Transfer_DataObject*)" LOG_ }
	void LB_STDCALL visit(lb_I_Thread*) { _CL_LOG << "visit(lb_I_Thread*)" LOG_ }
	void LB_STDCALL visit(lb_I_Mutex*) { _CL_LOG << "visit(lb_I_Mutex*)" LOG_ }
	void LB_STDCALL visit(lb_I_CriticalSection*) { _CL_LOG << "visit(lb_I_CriticalSection*)" LOG_ }
	void LB_STDCALL visit(lb_I_Lock*) { _CL_LOG << "visit(lb_I_Lock*)" LOG_ }
		

	void LB_STDCALL visit(lb_I_ThreadImplementation*) { _CL_LOG << "visit(lb_I_ThreadImplementation*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchProtocol*) { _CL_LOG << "visit(lb_I_DispatchProtocol*)" LOG_ }
	void LB_STDCALL visit(lb_I_ProtocolTarget*) { _CL_LOG << "visit(lb_I_ProtocolTarget*)" LOG_ }
	void LB_STDCALL visit(lb_I_CallbackTarget*) { _CL_LOG << "visit(lb_I_CallbackTarget*)" LOG_ }
	void LB_STDCALL visit(lb_I_ProtocolManager*) { _CL_LOG << "visit(lb_I_ProtocolManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationServer*) { _CL_LOG << "visit(lb_I_ApplicationServer*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationServerThread*) { _CL_LOG << "visit(lb_I_ApplicationServerThread*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchFunction*) { _CL_LOG << "visit(lb_I_DispatchFunction*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationClient*) { _CL_LOG << "visit(lb_I_ApplicationClient*)" LOG_ }
	void LB_STDCALL visit(lb_I_Proxy*) { _CL_LOG << "visit(lb_I_Proxy*)" LOG_ }
	void LB_STDCALL visit(lb_I_BinaryData*) { _CL_LOG << "visit(lb_I_BinaryData*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestMethod*) { _CL_LOG << "visit(lb_I_TestMethod*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestFixture*) { _CL_LOG << "visit(lb_I_TestFixture*)" LOG_ }
	void LB_STDCALL visit(lb_I_CryptoStream*) { _CL_LOG << "visit(lb_I_CryptoStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchInterceptor*) { _CL_LOG << "visit(lb_I_DispatchInterceptor*)" LOG_ }
	void LB_STDCALL visit(lb_I_VisitableHelper*) { _CL_LOG << "visit(lb_I_VisitableHelper*)" LOG_ }
	void LB_STDCALL visit(lb_I_ExtensionObject*) { _CL_LOG << "visit(lb_I_ExtensionObject*)" LOG_ }

/*...e*/

	void LB_STDCALL visit(lb_I_Streamable* pm);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);

	void LB_STDCALL visit(lb_I_ExtensibleObject* tableModule);
	void LB_STDCALL visit(lb_I_DocumentVersion*);

	void LB_STDCALL visit(lb_I_FileLocation*);
	void LB_STDCALL visit(lb_I_DirLocation*);

	bool LB_STDCALL begin(const char* file);
	bool LB_STDCALL begin(lb_I_Stream* stream);
	void LB_STDCALL end();

	void LB_STDCALL setContextNamespace(const char* _namespace);
	lb_I_Stream* LB_STDCALL getStream();

	UAP(lb_I_InputStream, iStream)
	UAP(lb_I_String, contextNamespace)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbJSONInputStream)
	ADD_INTERFACE(lb_I_Aspect)
	ADD_INTERFACE(lb_I_FileOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbJSONInputStream, lbJSONInputStream)


/*...slbErrCodes LB_STDCALL lbJSONInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbJSONInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbJSONInputStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbJSONInputStream\58\\58\lbJSONInputStream\40\\41\:0:*/
lbJSONInputStream::lbJSONInputStream() 
{
	_CL_LOG << "lbJSONInputStream::lbJSONInputStream() called." LOG_
	REQUEST(getModuleInstance(), lb_I_String, contextNamespace)
}
/*...e*/
/*...slbJSONInputStream\58\\58\\126\lbJSONInputStream\40\\41\:0:*/
lbJSONInputStream::~lbJSONInputStream() {
	_CL_LOG << "lbJSONInputStream::~lbJSONInputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbJSONInputStream::begin(const char* file) {
	REQUEST(getModuleInstance(), lb_I_InputStream, iStream)
	
	iStream->setFileName(file);
	bool ret = iStream->open();

	if (!ret) {
		_CL_LOG << "lbJSONInputStream::begin(" << file << ") Error: Open file failed." LOG_
	}
	
	return ret;
}

bool LB_STDCALL lbJSONInputStream::begin(lb_I_Stream* stream) {
	lbErrCodes err = ERR_NONE;
	if (stream != NULL) {
		_CL_LOG << "lbJSONInputStream::begin(lb_I_Stream*): Got a stream (" << stream->getClassName() << ")." LOG_
		QI(stream, lb_I_InputStream, iStream)
		bool ret = iStream->open();

		if (!ret) {
			_CL_LOG << "lbJSONInputStream::begin(lb_I_Stream* stream) Error: Open file failed." LOG_
		}
		
		return ret;
	} else {
		_CL_LOG << "lbJSONInputStream::begin(lb_I_Stream* stream) Error: Uninitialized stream onject (NULL pointer)!" LOG_
	}
	
	return false;
}

void lbJSONInputStream::setContextNamespace(const char* _namespace) {
	_LOG << "lbJSONInputStream::setContextNamespace('" << _namespace << "') called." LOG_
	*contextNamespace = _namespace;
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_Streamable* pm) {
	if (iStream != NULL) {
		// Project manager has a private implementation. Use existing fromFile function.
		pm->load(iStream.getPtr());
	} else {
		_CL_LOG << "lbJSONInputStream::visit(lb_I_ProjectManager* pm) Error: No input stream available. Could not read from stream!" LOG_
	}
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_String* s) {
	char* buffer = NULL;

	*iStream >> buffer;
		
	*s = buffer;
	free(buffer);
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_Boolean* b) {
	bool _b = NULL;
	*iStream >> _b;
	b->setData(_b);
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_Parameter* params) {
	int count = 0;
	*iStream >> count;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, f)
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, p)

	for (int i = 0; i < count; i++) {
		char* ParameterName = NULL;
		char* ParameterClassName = NULL;

		*iStream >> ParameterName;
		*iStream >> ParameterClassName;
		
		*paramname = ParameterName;
		
		if (strcmp(ParameterClassName, p->getClassName()) == 0) {
			visit(*&p);
			params->setUAPParameter(*&paramname, *&p);
		}
		else
		if (strcmp(ParameterClassName, f->getClassName()) == 0) {
			char* _f = NULL;
			*iStream >> _f;
			f->setData(_f);
			params->setUAPFileLocation(*&paramname, *&f);
		}
		else
		if (strcmp(ParameterClassName, s->getClassName()) == 0) {
			char* _s = NULL;
			*iStream >> _s;
			*s = _s;
			params->setUAPString(*&paramname, *&s);
		}
		else
		if (strcmp(ParameterClassName, l->getClassName()) == 0) {
			long _l;
			*iStream >> _l;
			l->setData(_l);
			params->setUAPLong(*&paramname, *&l);
		}
		else
		if (strcmp(ParameterClassName, b->getClassName()) == 0) {
			bool _b;
			*iStream >> _b;
			b->setData(_b);
			params->setUAPBoolean(*&paramname, *&b);
		} else {
			_CL_LOG << "lbJSONInputStream::visit(lb_I_Parameter* params) Error: Not supported type '" << ParameterClassName << "'" LOG_
		}
	}
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_ExtensibleObject* tableModule) {
	UAP(lb_I_ExtensionObject, extension) 
	extension = tableModule->getExtension(*&contextNamespace);
	
	if (extension != NULL) {
		UAP(lb_I_Unknown, uk)
		QI(tableModule, lb_I_Unknown, uk)
		extension->setOwningObject(*&uk);

		UAP(lb_I_VisitorExtension, visitorExtension)
		QI(extension, lb_I_VisitorExtension, visitorExtension)
	
		if (visitorExtension != NULL) {
			visitorExtension->setOperator(this);
			visitorExtension->execute();
		}
	}
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_DocumentVersion*) {

}

void LB_STDCALL lbJSONInputStream::visit(lb_I_FileLocation* fileloc) {
		char*  f = NULL;
		
		*iStream >> f;
		
		fileloc->setData(f); 
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_DirLocation* fileloc) {
		char*  f = NULL;
		
		*iStream >> f;
		
		fileloc->setData(f); 
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_MetaApplication* app) {
	_CL_LOG << "lbJSONInputStream::visit(lb_I_MetaApplication* app): Read data of meta application." LOG_

	char* temp = NULL;
	bool  b;
	int   count = 0;
	
	*iStream >> b;
	app->setAutorefreshData(b);

	*iStream >> temp;
	app->setApplicationName(temp);
	
	*iStream >> temp;
	app->setUserName(temp);
	
	_LOG << "Metaapplication has got the username: '" << temp << "'." LOG_
	
	*iStream >> b;
	app->setAutoload(b);
	
	*iStream >> b;
	app->setAutoselect(b);

	*iStream >> b;
	app->setGUIMaximized(b);
	
	*iStream >> temp;
	app->setDirLocation(temp);
	
	*iStream >> b;
	if (b) app->setPropertyPaneLayoutFloating();
	
	*iStream >> b;
	if (b) app->setPropertyPaneLayoutLeft();
	
	*iStream >> b;
	if (b) app->setLoadFromDatabase(true);
	//else app->setLoadFromDatabase(false);

	*iStream >> temp;
	app->setApplicationDatabaseBackend(temp);

	*iStream >> temp;
	app->setSystemDatabaseBackend(temp);

	*iStream >> b;
	if (b) app->useApplicationDatabaseBackend(true);
	else app->useApplicationDatabaseBackend(false);

	*iStream >> b;
	if (b) app->useSystemDatabaseBackend(true);
	else app->useSystemDatabaseBackend(false);
	_CL_LOG << "lbJSONInputStream::visit(lb_I_MetaApplication* app): Read data of meta application done." LOG_
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_Dispatcher* disp) {
	_CL_LOG << "lbJSONInputStream::visit(): Read data of dispatcher." LOG_
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	char* temp = NULL;
	*iStream >> temp;
	*s = temp;
	disp->setInterceptorDefinitions(*&s);	
}

void LB_STDCALL lbJSONInputStream::visit(lb_I_Application*) {
	_CL_LOG << "lbJSONInputStream::visit(): Read data of application." LOG_
	lbErrCodes err = ERR_NONE;
	
	// Get the document via the active document from meta application.
	// This way no extra interface is needed (container with named elements)
	
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, StorageInterface)
	UAP_REQUEST(getModuleInstance(), lb_I_String, StorageNamespace)
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	
	ukDoc = meta->getActiveDocument();
	if (ukDoc == NULL) {
		_LOG << "Error: Expected a document as 'active document' here!" LOG_
		return;
	}
	
	QI(ukDoc, lb_I_Parameter, document)
	
	if (document != NULL) {
		*param = "StorageDelegateNamespace";
		document->getUAPString(*&param, *&StorageNamespace);
		
		// Get the plugin that is responsible to save the data.		
		pl = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", StorageNamespace->charrep());
		
		if (pl != NULL)	{
			ukPl = pl->getImplementation();
		} else {
			_LOG << "No 'lb_I_StandaloneStreamable' plugin with namespace '" << StorageNamespace->charrep() << "' available." LOG_	
		}
		
		UAP(lb_I_StandaloneStreamable, mystream)
	
		if (ukPl != NULL) QI(ukPl, lb_I_StandaloneStreamable, mystream)
			
		if (mystream == NULL) {
			_LOG << "Error: Found a lb_I_StandaloneStreamable plugin via PM->getFirstMatchingPlugin(...), but QI failed." LOG_
		} else {
			//isFileAvailable = fOp->begin(filename->charrep()); 
			
			mystream->setOperator(this);
			mystream->load(*&iStream);
		}
	}
}

void LB_STDCALL lbJSONInputStream::end() {

}

lb_I_Stream* LB_STDCALL lbJSONInputStream::getStream() {
	lbErrCodes err = ERR_NONE;
	
        UAP(lb_I_Stream, s)
        QI(iStream, lb_I_Stream, s)
        s++;

        return s.getPtr();
}
/*...e*/

/*...sclass lbPluginJSONInputStream implementation:0:*/
/*...slbPluginJSONInputStream:0:*/
class lbPluginJSONInputStream : public lb_I_PluginImpl {
public:
	lbPluginJSONInputStream();
	
	virtual ~lbPluginJSONInputStream();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace);
/*...e*/

	DECLARE_LB_UNKNOWN()

private:
	UAP(lb_I_Unknown, impl)
	UAP(lb_I_String, pluginNamespace)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginJSONInputStream)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginJSONInputStream, lbPluginJSONInputStream)

/*...slbErrCodes LB_STDCALL lbPluginJSONInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginJSONInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginJSONInputStream::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

void LB_STDCALL lbPluginJSONInputStream::setNamespace(const char* _namespace) {
	*pluginNamespace = _namespace;
}

lbPluginJSONInputStream::lbPluginJSONInputStream() {
	_CL_VERBOSE << "lbPluginJSONInputStream::lbPluginJSONInputStream() called.\n" LOG_
	REQUEST(getModuleInstance(), lb_I_String, pluginNamespace)
	*pluginNamespace = "Plugin namespace was not set.";
}

lbPluginJSONInputStream::~lbPluginJSONInputStream() {
	_CL_VERBOSE << "lbPluginJSONInputStream::~lbPluginJSONInputStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginJSONInputStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginJSONInputStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginJSONInputStream::initialize() {
}
	
bool LB_STDCALL lbPluginJSONInputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginJSONInputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginJSONInputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbJSONInputStream* InputStream = new lbJSONInputStream();
		
		InputStream->setContextNamespace(pluginNamespace->charrep());
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginJSONInputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginJSONInputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		lbJSONInputStream* InputStream = new lbJSONInputStream();
		
		InputStream->setContextNamespace(pluginNamespace->charrep());
	
		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginJSONInputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/
