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
#ifndef DEBUG_MALLOC
#include <malloc.h>
#endif
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
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "plugin.cpp"
#pragma interface "plugin.cpp"
#endif

/*...e*/

/*...sclass lbPluginModuleDMFBasicActionStepsTest:0:*/
class lbPluginModuleDMFBasicActionSteps : public lb_I_PluginModule {
public:

	lbPluginModuleDMFBasicActionSteps();
	virtual ~lbPluginModuleDMFBasicActionSteps();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL install();

	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleDMFBasicActionStepsTest implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleDMFBasicActionSteps)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleDMFBasicActionSteps)

BEGIN_PLUGINS(lbPluginModuleDMFBasicActionSteps)
	ADD_PLUGIN(lbPluginDMFIdForFormValue, BasicActionSteps)
	ADD_PLUGIN(lbPluginCallActivityHandler, BasicActionSteps)
END_PLUGINS()

lbPluginModuleDMFBasicActionSteps::lbPluginModuleDMFBasicActionSteps() {
	_LOGVERBOSE << "lbPluginModuleDMFBasicActionSteps::lbPluginModuleDMFBasicActionSteps() lbPluginDMFIdForFormValue with namespace BasicActionSteps called." LOG_
}

lbPluginModuleDMFBasicActionSteps::~lbPluginModuleDMFBasicActionSteps() {
	_LOGVERBOSE << "lbPluginModuleDMFBasicActionSteps::~lbPluginModuleDMFBasicActionSteps() lbPluginDMFIdForFormValue with namespace BasicActionSteps called." LOG_
}

// The failure code is not late binding the columns, thus a primary key
// later on seems not to get handled proper when I try to set it readonly.
//#define FAILURE_CODE

// The query does not cause the stack corrupption either failure or not
//#define FAILURE_QUERY

void LB_STDCALL lbPluginModuleDMFBasicActionSteps::initialize() {
	lbErrCodes err = ERR_NONE;
	
	_LOGVERBOSE << "lbPluginModuleDMFBasicActionSteps::initialize() lbPluginDMFIdForFormValue called." LOG_
	enumPlugins();
}

void LB_STDCALL lbPluginModuleDMFBasicActionSteps::install() {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	char* dbbackend = meta->getSystemDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOGVERBOSE << "Using plugin database backend for lbPluginModuleDMFBasicActionSteps::initialize() operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		
		if (database == NULL) {
			_LOG << "Error: Database couldn't loaded. Maybe ODBC components are not installed." LOG_
			return;
		}
		
		_LOGVERBOSE << "Using built in database backend for lbPluginModuleDMFBasicActionSteps::initialize() operation..." LOG_
	}

	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->init();
	if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
		_LOG << "Error: Could not connect to given database: '" << "lbDMF" << "'" LOG_

		return;
	}

	UAP(lb_I_Query, q)
	UAP(lb_I_Query, query_actions)
	UAP(lb_I_Query, query_action_steps)
	UAP(lb_I_Query, formularquery)
	UAP(lb_I_Query, formularactions)
	UAP(lb_I_Query, applicationparameterquery)
	UAP(lb_I_Query, applicationquery)
	UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
	q = database->getQuery("lbDMF", 0);
	query_actions = database->getQuery("lbDMF", 0);
	query_action_steps = database->getQuery("lbDMF", 0);
	formularquery = database->getQuery("lbDMF", 0);
	formularactions = database->getQuery("lbDMF", 0);
	applicationparameterquery = database->getQuery("lbDMF", 0);
	applicationquery = database->getQuery("lbDMF", 0);

#ifdef FAILURE_QUERY
	*sql = "select id, bezeichnung, action_handler, module from action_types where module = 'lbDMFXslt' and action_handler = 'instanceOflbDMFXslt'";
#endif
#ifndef FAILURE_QUERY
	*sql = "select id, action_handler, module, bezeichnung from action_types where module = 'lbDMFXslt' and action_handler = 'instanceOflbDMFXslt'";
#endif

	q->skipFKCollecting();
	query_actions->skipFKCollecting();
	query_action_steps->skipFKCollecting();
	formularquery->skipFKCollecting();
	formularactions->skipFKCollecting();
	applicationquery->skipFKCollecting();

#ifdef FAILURE_CODE
	err = q->query(sql->charrep());
#endif
#ifndef FAILURE_CODE
	err = q->query(sql->charrep(), false);
	q->setReadonly("id");
    q->bind();
#endif

	if (err == ERR_NONE) {
		err = q->first();
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			_LOGVERBOSE << "Plugin lbPluginDMFIdForFormValue with BasicActionSteps already installed." LOG_
		} else {
			if (meta->askYesNo("Plugin for XSLT transformation actions available.\n\nWould you enable that plugin ?")) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, columnname)
				UAP_REQUEST(getModuleInstance(), lb_I_String, module)
				UAP_REQUEST(getModuleInstance(), lb_I_String, action_handler)
				UAP_REQUEST(getModuleInstance(), lb_I_String, bezeichnung)
				UAP_REQUEST(getModuleInstance(), lb_I_String, id)
				UAP_REQUEST(getModuleInstance(), lb_I_Long, action_type_id)

				// If loading is set to file, overwrite.
				meta->setLoadFromDatabase(true);

				*module = "lbDMFXslt";
				*action_handler = "instanceOflbDMFXslt";
				*bezeichnung = "Perform XSLT transformation";
				*id = "1";

				*columnname = "module";
				q->setString(*&columnname, *&module);
				*columnname = "id";
				q->setString(*&columnname, *&id);
				*columnname = "action_handler";
				q->setString(*&columnname, *&action_handler);
				*columnname = "bezeichnung";
				q->setString(*&columnname, *&bezeichnung);

				q->add();
				*columnname = "id";
				q->setString(*&columnname, *&id);
				*columnname = "module";
				q->setString(*&columnname, *&module);
				*columnname = "action_handler";
				q->setString(*&columnname, *&action_handler);
				*columnname = "bezeichnung";
				q->setString(*&columnname, *&bezeichnung);

#ifdef FAILURE_CODE
                q->setReadonly("id");
#endif
				q->update();

				q->last();
				action_type_id = q->getAsLong(1);

				// Action to generate code at the level of Application
				{
					query_actions->query("insert into actions (name, typ, source, target) values('Code generieren', 1, 'name', 0)");
                    _LOG << "Initialize lbDMFXSLT module. Step 4" LOG_

					UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
					UAP(lb_I_Long, actionid)

					if (query_actions->query("select id from actions where name = 'Code generieren'") == ERR_NONE) {
						err = query_actions->first();
						if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
							actionid = query_actions->getAsLong(1);

							*sql = "insert into action_steps (actionid, type, bezeichnung, a_order_nr) values (";
							*sql += actionid->charrep();
							*sql += ", ";
							*sql += action_type_id->charrep();
							*sql += ", 'Translate XML file with XSLT template', 1)";
							query_action_steps->query(sql->charrep());

							*sql = "select id from formulare where name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager')";

							if (formularquery->query(sql->charrep()) == ERR_NONE) {
								err = formularquery->first();
								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									UAP(lb_I_String, formid)

									formid = formularquery->getAsString(1);

									*sql = "insert into formular_actions (formular, action, event) values (";
									*sql += formid->charrep();
									*sql += ", ";
									*sql += actionid->charrep();
									*sql += ", 'evtGenerateCode')";

									formularactions->query(sql->charrep());
								}
							}
						}
					}
				}
				// Action to generate XSLT template at the level of Templates
#ifdef bla
				{
					query_actions->query("insert into actions (name, typ, source, target) values('generate XSLT template', 1, 'name', 0)");

					UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
					UAP(lb_I_Long, actionid)

					if (query_actions->query("select id from actions where name = 'generate XSLT template'") == ERR_NONE) {
						err = query_actions->first();
						if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
							actionid = query_actions->getAsLong(1);

							*sql = "insert into action_steps (actionid, type, bezeichnung, a_order_nr) values (";
							*sql += actionid->charrep();
							*sql += ", ";
							*sql += action_type_id->charrep();
							*sql += ", 'Create  XSLT template file set based on template definition', 1)";
							query_action_steps->query(sql->charrep());

							*sql = "select id from formulare where name = 'Templates' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager')";

							if (formularquery->query(sql->charrep()) == ERR_NONE) {
								err = formularquery->first();
								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									UAP(lb_I_String, formid)

									formid = formularquery->getAsString(1);

									*sql = "insert into formular_actions (formular, action, event) values (";
									*sql += formid->charrep();
									*sql += ", ";
									*sql += actionid->charrep();
									*sql += ", 'evtGenerateXSLTTemplate')";

									formularactions->query(sql->charrep());
								}
							}
						}
					}
				}
#endif
			}
		}
	}
}

lbErrCodes LB_STDCALL lbPluginModuleDMFBasicActionSteps::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleDMFBasicActionStepsTest::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
