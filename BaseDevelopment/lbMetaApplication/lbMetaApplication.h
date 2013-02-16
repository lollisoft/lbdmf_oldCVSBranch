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
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.79 $
 * $Name:  $
 * $Id: lbMetaApplication.h,v 1.79 2013/02/16 10:36:25 lollisoft Exp $
 *
 * $Log: lbMetaApplication.h,v $
 * Revision 1.79  2013/02/16 10:36:25  lollisoft
 * Merged Release_1_0_4_stable_rc1_branch but doesn't yet compile.
 * Several files were conflicting and resolved in this checkin.
 *
 * Revision 1.78  2011/10/29 06:03:58  lollisoft
 * Refactored application model (and it's model classes) into separate files to enable code generation.
 * The code generation is planned for the model classes and the composite container for the model.
 * Refactored out the login and user management from meta application due to the fact that it is a
 * distinct feature the meta application should not provide. The code has been moved to a security
 * provider API based plugin that should be loaded as a plugin. Currently this fails and thus login is not
 * available.
 *
 * Revision 1.77.2.2  2012/11/18 08:38:19  lollisoft
 * Many changes that help improving unit tests. They mainly include application
 * reload capabilities, but that didn't yet work in GUI. Some menu entries are
 * doubled, data isn't valid (NULL pointer).
 *
 * Revision 1.77.2.1  2012/11/11 08:25:42  lollisoft
 * Added new function to unregister an event.
 *
 * Revision 1.77  2011/09/27 06:29:42  lollisoft
 * Fixed some issues reported by CppCheck.
 *
 * Revision 1.76  2011/06/18 17:29:55  lollisoft
 * Changed all char* to const char* where a corresponding warning was generated.
 *
 * Revision 1.75  2010/10/12 07:04:22  lollisoft
 * Completed implementation to write to json file from within an interceptor for events.
 *
 * Sample code of interceptor has to be extracted, published  and documented.
 *
 * Revision 1.74  2010/06/30 06:05:57  lollisoft
 * Added code to support unloading application module (detachInterface) and changed code to try correctly unloading modules.
 *
 * Revision 1.73  2010/05/17 05:44:43  lollisoft
 * Many changes related to support mixing MinGW with Open Watcom.
 *
 * Revision 1.72  2010/04/25 21:37:09  lollisoft
 * Successfully ported lbHook to MINGW compiler. There were only two issues
 * I have identified: The enum problem as reported from Michal Necasek having
 * different sizes and the interface ordering to be equal to implementing class
 * declaration. But this only belongs to my UnitTest code yet.
 *
 * Aim of this is the ability to mix in MINGW modules for features Open Watcom
 * didn't support yet and let me do this with minimal effort.
 *
 * Revision 1.71  2010/02/17 13:47:26  lollisoft
 * Added default parameter to enable skipping yielding.
 *
 * Revision 1.70  2010/01/16 16:22:41  lollisoft
 * Added methods to cleanup intercepted instances that otherwise will crash the application due to dangling pointers.
 *
 * Revision 1.69  2010/01/14 17:31:25  lollisoft
 * More changes for interceptor functionality, but crashes on Mac OS X (PPC).
 *
 * Revision 1.68  2010/01/12 19:45:41  lollisoft
 * Mostly completed plugin based interceptor functionality for events.
 *
 * Revision 1.67  2010/01/10 10:17:06  lollisoft
 * Added code for interceptor functionality.
 *
 * Revision 1.66  2009/09/03 17:32:43  lollisoft
 * Corrected exit behaviour when clicking on window close button.
 *
 * Revision 1.65  2009/07/19 22:40:20  lollisoft
 * Moved the installation step of an initial database to the new plugin install method.
 *
 * Revision 1.64  2009/06/10 11:56:51  lollisoft
 * Added functions to help passing application process name.
 *
 * Revision 1.63  2009/02/11 18:39:58  lollisoft
 * Added functions to provide property changing by code.
 * Also added an uninitialisation function to ensure correct
 * cleanup. Also added a simple fireEvent function.
 *
 * Revision 1.62  2009/02/08 15:01:05  lollisoft
 * Minor documentation.
 *
 * Revision 1.61  2009/02/04 11:34:04  lollisoft
 * Added but partly deactivated new hooks stuff.
 *
 * Revision 1.60  2008/05/21 22:25:10  lollisoft
 * Some improvements for working with Sqlite database.
 *
 * Revision 1.59  2008/05/19 06:42:31  lollisoft
 * Added code to check for availability of any database. Corrected splash screen and modal dialog problems.
 *
 * Revision 1.58  2008/05/16 06:39:19  lollisoft
 * Added switches to disable database backend settings.
 *
 * Revision 1.57  2008/04/18 05:58:30  lollisoft
 * Added new methods to get ans set application and system database backend (the namespace of a plugin).
 *
 * Revision 1.56  2008/04/14 06:05:33  lollisoft
 * Added database backend configuration for near pluggable database support. Corrected property panel displaying at startup.
 *
 * Revision 1.55  2008/02/23 18:25:11  lollisoft
 * Added an optional boolean parameter that additionally
 * triggers change events of the properties in parameter 1.
 *
 * Revision 1.54  2008/02/18 20:02:52  lollisoft
 * Added function to get a directory from the user.
 *
 * Revision 1.53  2008/02/12 21:36:27  lollisoft
 * Added code that allows to store parameter sets into the meta application file.
 *
 * Revision 1.52  2007/10/11 13:38:40  lollisoft
 * Propably completed offline capability from system database.
 *
 * Revision 1.51  2007/08/02 07:01:57  lollisoft
 * Added member function to remove a toolbar.
 *
 * Revision 1.50  2007/07/11 14:49:14  lollisoft
 * Added flag to force database usage and changed code to
 * support the flag.
 *
 * Revision 1.49  2007/05/14 19:19:14  lollisoft
 * Unfinished changes. Go to Linux.
 *
 * Revision 1.48  2007/05/11 21:21:02  lollisoft
 * Linux compiler is more restrictive with const char*
 *
 * Revision 1.47  2007/05/01 08:39:21  lollisoft
 * Added more propertypanel functionality.
 *
 * Revision 1.46  2007/02/09 21:35:51  lollisoft
 * Implemented remaining stuff for basic toolbar support.
 * But these seems not to show the bitmap on Mac OS X.
 *
 * Revision 1.45  2007/02/08 22:36:05  lollisoft
 * Partial toolbar implementation
 *
 * Revision 1.44  2007/02/03 11:04:36  lollisoft
 * Implemented directory location property handler. This is used in lbMetaApplication.
 *
 * Revision 1.43  2007/01/29 20:12:59  lollisoft
 * Checkin for Linux.
 *
 * Revision 1.42  2007/01/14 15:06:15  lollisoft
 * Added a new function to show a simple message box.
 *
 * Revision 1.41  2006/07/17 17:37:45  lollisoft
 * Changes dueto bugfix in plugin manager. Repeadable iterator problem.
 * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
 * be found any more after first query.
 *
 * Code works well with improved trmem library, but there is still a crash in
 * database classes (pgODBC library).
 *
 * Revision 1.40  2006/07/02 13:25:57  lollisoft
 * Added active document support.
 *
 * Revision 1.39  2006/06/24 06:19:54  lollisoft
 * Commit due to travel to Duesseldorf.
 *
 * Revision 1.38  2006/06/15 18:36:28  lollisoft
 * Partly implemented load of lbDMF database contents into file. (Login and application list)
 *
 * Revision 1.37  2006/06/10 09:51:51  lollisoft
 * Implemented new load and save method for meta application.
 *
 * Revision 1.36  2006/06/09 16:03:33  lollisoft
 * Changes on Mac OS X before weekend.
 *
 * Revision 1.35  2006/06/03 06:16:57  lollisoft
 * Changes against new Datamodel classes.
 * These are used instead spread SQL commands.
 *
 * Currently, the SQL commands are for fallback issues,
 * if there is no data in the config files.
 *
 * Later the planned fallback SQL commands are replaced by
 * a controlled visitor operation.
 *
 * Work is in process.
 *
 * Revision 1.34  2006/03/28 11:34:04  lollisoft
 * Renamed Initialize to initialize and added unloadApplication for better unloading of the application.
 *
 * Revision 1.33  2006/03/24 17:12:22  lollisoft
 * Added GUI state for maximized or not.
 *
 * Revision 1.32  2006/03/16 08:01:04  lollisoft
 * Added set and getAutorefreshData members to the  lb_I_MetaApplication implementation. Also included that flags in the property panel.
 *
 * Revision 1.31  2006/02/22 11:49:57  lollisoft
 * Moved the general part to meta application. wxWrapper does ask for it when left panel will be shown.
 *
 * Revision 1.30  2006/02/21 19:35:50  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.29  2006/02/19 18:41:35  lollisoft
 * Feedback of properties works good. I am use the
 * dispatcher mechanism to forward the change events
 * on per lb_I_Parameter instance and the category name
 * to a registered handler.
 *
 * So one handler must be capable to recieve values for all
 * elements of one lb_I_Parameter instance.
 *
 * Revision 1.28  2006/02/17 23:57:16  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.27  2006/01/30 15:54:14  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.26  2006/01/26 14:03:23  lollisoft
 * Added event en/disable and toggle functions. Also added
 * askYesNo function.
 *
 * Revision 1.25  2006/01/21 23:48:14  lollisoft
 * Added new member to ask the user for a file.
 *
 * Revision 1.24  2005/11/18 23:41:31  lollisoft
 * More memory leaks have been fixed. There are currently less than 200
 * chunks unfreed, wich may be located in the plugin mechanism.
 *
 * Revision 1.23  2005/11/16 13:17:03  lollisoft
 * Added Memtrack breakpoint counter.
 *
 * Corrected reference count bug by using UAP for 'a' and using preload to
 * delegate unloading of shared library, loaded by loadApplication into
 * destructor.
 *
 * Revision 1.22  2005/06/20 11:18:46  lollisoft
 * Added interface set/get User and ApplicationName
 *
 * Revision 1.21  2005/06/01 10:57:22  lollisoft
 * Replaced DEBUG_UAP with UAP
 *
 * Revision 1.20  2005/03/31 08:59:34  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.19  2005/01/05 13:41:36  lollisoft
 * New dynamic application implementation works
 *
 * Revision 1.18  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.17  2004/07/16 20:24:41  lollisoft
 * Added handler to enter into the debugger
 *
 * Revision 1.16  2004/01/24 16:17:29  lollisoft
 * Added support for loading application
 *
 * Revision 1.15  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.14  2003/08/22 17:38:35  lollisoft
 * Implemented a handler for a button press event and code to demonstrate
 *
 * Revision 1.13  2003/08/16 18:03:53  lollisoft
 * Added my new address due to move
 *
 * Revision 1.12  2003/03/14 16:00:38  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.11  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.10  2002/10/08 16:33:38  lothar
 * Missing LB_STDCALL
 *
 * Revision 1.9  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.8  2002/09/12 18:32:59  lothar
 * Added some UI wrapper and sub module creation
 *
 * Revision 1.7  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.6  2002/09/04 17:52:12  lothar
 * Problems with stack cleanup
 *
 * Revision 1.5  2002/08/21 18:00:28  lothar
 * Added UAP variables
 *
 * Revision 1.4  2002/08/06 05:41:39  lothar
 * More special Dispatcher and EventManager interface.
 * Empty bodies compiling
 *
 * Revision 1.3  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/

#ifndef _LB_METAAPP_
#define _LB_METAAPP_

#include <stdio.h>
#include <lbInterfaces.h>


/*...sclass lb_MetaApplication:0:*/
/** \brief Implementation of lb_I_MetaApplication
 * Main application interface to the programmer.
 */
class lb_MetaApplication : 
public lb_I_MetaApplication,
public lb_I_EventHandler
{
public:
	lbErrCodes 				LB_STDCALL save();
	lbErrCodes 				LB_STDCALL load();
	lbErrCodes 				LB_STDCALL setGUI(lb_I_GUI* _gui);
	lbErrCodes 				LB_STDCALL setUserName(const char* user);
	lbErrCodes 				LB_STDCALL setApplicationName(const char* app);
	void	   				LB_STDCALL setAutorefreshData(bool b);
	void	   				LB_STDCALL setGUIMaximized(bool b);
	bool	   				LB_STDCALL getGUIMaximized();
	void	   				LB_STDCALL setAutoload(bool b);
	void	  				LB_STDCALL setAutoselect(bool b);
	bool	   				LB_STDCALL getAutorefreshData();
	bool	   				LB_STDCALL getAutoload();
	bool	   				LB_STDCALL getAutoselect();
	char*	   				LB_STDCALL getDirLocation();
	void	   				LB_STDCALL setDirLocation(const char* dirloc);
	/**
	 * Let the implementation register it's symbolic events.
	 * For each event, it gets an numeric identifer so it may
	 * be able to dispatch that events.
	 */
	lbErrCodes 				LB_STDCALL initialize(const char* user = NULL, const char* app = NULL);
	lbErrCodes 				LB_STDCALL uninitialize();
	lbErrCodes 				LB_STDCALL run();
	lbErrCodes 				LB_STDCALL getGUI(lb_I_GUI** _gui);
	lbErrCodes 				LB_STDCALL getUserName(lb_I_String** user);
	lbErrCodes 				LB_STDCALL getApplicationName(lb_I_String** app);
	lb_I_EventManager*		getEVManager( void );
	/**
	 * Load the real application.
	 */
	lbErrCodes 				LB_STDCALL loadApplication(const char* user, const char* app);
	lbErrCodes 				LB_STDCALL unloadApplication();
	lbErrCodes 				LB_STDCALL addToolBar(const char* toolbarName);
	lbErrCodes 				LB_STDCALL removeToolBar(const char* toolbarName);
	lbErrCodes 				LB_STDCALL addToolBarButton(const char* toolbarName, const char* entry, const char* evHandler, const char* toolbarimage, const char* afterentry = NULL);
	lbErrCodes 				LB_STDCALL removeToolBarButton(const char* toolbarName, const char* entry);
	lbErrCodes 				LB_STDCALL toggleToolBarButton(const char* toolbarName, const char* entry);
	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	lbErrCodes 				LB_STDCALL addMenuBar(const char* name, const char* after = NULL);
	/**
	 * Add a menu behind the last.
	 */
	lbErrCodes 				LB_STDCALL addMenu(const char* name);
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	lbErrCodes 				LB_STDCALL addMenuEntry(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry = NULL);
	lbErrCodes 				LB_STDCALL addMenuEntryCheckable(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry = NULL);
	lbErrCodes 				LB_STDCALL removeMenuBar(const char* name);
	lbErrCodes 				LB_STDCALL removeMenuEntry(const char* in_menu, const char* entry);
	lbErrCodes 				LB_STDCALL enableEvent(const char* name);
	lbErrCodes 				LB_STDCALL disableEvent(const char* name);
	lbErrCodes 				LB_STDCALL toggleEvent(const char* name);
	lbErrCodes 				LB_STDCALL addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h);
	lbErrCodes 				LB_STDCALL addLabel(const char* text, int x, int y, int w, int h);
	lbErrCodes 				LB_STDCALL addTextField(const char* name, int x, int y, int w, int h);
	lb_I_InputStream*		LB_STDCALL askOpenFileReadStream(const char* extentions);
	bool					LB_STDCALL askYesNo(const char* msg);
	void					LB_STDCALL msgBox(const char* title, const char* msg);
	void 					LB_STDCALL addStatusBar();
	void 					LB_STDCALL addStatusBar_TextArea(const char* name);
	void 					LB_STDCALL setStatusText(const char* name, const char* value, bool call_yield = true);
	void 					LB_STDCALL disableStatusbar();
	/** \brief Let the GUI show the given parameters in a property panel.
	 *
	 */
	lbErrCodes 				LB_STDCALL showPropertyPanel(lb_I_Parameter* params, bool update = false);
	lbErrCodes 				LB_STDCALL registerPropertyChangeEventGroup(const char* name, lb_I_Parameter* params, lb_I_EventHandler* target, lbEvHandler handler);
	lb_I_Parameter* 		LB_STDCALL getParameter();
	void					LB_STDCALL setActiveApplication(const char* name);
	lb_I_Unknown*			LB_STDCALL getActiveDocument();
	void					LB_STDCALL setActiveDocument(lb_I_Unknown* doc);
	void                    LB_STDCALL setPropertyPaneLayoutFloating();
	void                    LB_STDCALL setPropertyPaneLayoutLeft();
	void                    LB_STDCALL showPropertyPanel();
	void                    LB_STDCALL setLoadFromDatabase(bool b);
	bool                    LB_STDCALL getLoadFromDatabase();
	void					LB_STDCALL addPropertySet(lb_I_Parameter* properties, const char* setname);
	void					LB_STDCALL delPropertySet(const char* setname);
	lb_I_Parameter*			LB_STDCALL getPropertySet(const char* setname, bool copy = false);
	bool					LB_STDCALL askForDirectory(lb_I_DirLocation* loc);
	char*					LB_STDCALL getSystemDatabaseBackend();
	char*					LB_STDCALL getApplicationDatabaseBackend();
	void					LB_STDCALL setSystemDatabaseBackend(const char* backend);
	void					LB_STDCALL setApplicationDatabaseBackend(const char* backend);
	void					LB_STDCALL useSystemDatabaseBackend(bool backend);
	void					LB_STDCALL useApplicationDatabaseBackend(bool backend);
	bool					LB_STDCALL usingSystemDatabaseBackend();
	bool					LB_STDCALL usingApplicationDatabaseBackend();
	void					LB_STDCALL firePropertyChangeEvent(const char* name, const char* value);
	void					LB_STDCALL fireEvent(const char* name);
	void					LB_STDCALL setProcessName(const char* name);
	lb_I_String*			LB_STDCALL getProcessName();

	lbErrCodes 				LB_STDCALL addToolBarTool(const char* toolbarName, const char* tooltype, const char* entry, const char* evHandler, const char* toolbarimage, const char* afterentry);
	

	lb_I_Unknown* 			LB_STDCALL getUnknown();
	lbErrCodes 				LB_STDCALL loadSubModules();

/*...sWrapper for some usual GUI functions:8:*/
/*...e*/

	lbErrCodes				LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	

	/* \brief Wrapper for FileExists function in lbHook.
	 * This function enables UML models (activitie) to make decisions based on files.
	 */
	lbErrCodes				LB_STDCALL isFileAvailable(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL enterDebugger(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL getLoginData(lb_I_Unknown* uk);
	
	lbErrCodes				LB_STDCALL lbEvHandler1(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL lbEvHandler2(lb_I_Unknown* uk);
	void					LB_STDCALL getBasicApplicationInfo(lb_I_Unknown** info);
	lbErrCodes				LB_STDCALL lbButtonTestHandler(lb_I_Unknown* uk);	
	
	/// \brief My handler for changed properties.
	lbErrCodes				LB_STDCALL propertyChanged(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL doAutoload(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL doLog(lb_I_Unknown* uk);
	
	bool                    LB_STDCALL isPropertyPaneLayoutFloating();
	bool                    LB_STDCALL isPropertyPaneLayoutLeft();
	void					LB_STDCALL updatePropertyGroup(lb_I_Container* properties, const char* prefix);

	//lb_I_Applications*		LB_STDCALL getApplicationModel();
	//bool 					LB_STDCALL login(const char* user, const char* pass);

	void					LB_STDCALL initApplicationSwitcher();
	void					LB_STDCALL deinitApplicationSwitcher();
	lbErrCodes				LB_STDCALL switchApplication(lb_I_Unknown* uk);

public:
	lb_MetaApplication();
	virtual ~lb_MetaApplication();

	DECLARE_LB_UNKNOWN()

protected:
#ifdef OLD_TIGHT_DEPENDENCY	
	/// \brief Applications stored in file or database.
	UAP(lb_I_Applications, Applications)
	/// \brief Users stored in file or database.
	UAP(lb_I_UserAccounts, Users)
	/// \brief Users to Applications mapping stored in file or database.
	UAP(lb_I_User_Applications, User_Applications)
	//	UAP(lb_I_Applications_Formulars, ApplicationFormulars)
#endif

	lb_I_GUI* gui;
	
	char* moduleName;
	
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_Application, app)
	UAP(lb_I_String, ProcessName)
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)
	
	/// \brief Active document per LogonApplication
	UAP(lb_I_Container, activeDocuments)
	
	UAP(lb_I_Parameter, myProperties)
	
	// To store propertysets
	UAP(lb_I_Parameter, propertySets)

	/// Types of databases available.
	UAP(lb_I_Container, availableDatabaseTypes)
	
	bool isPropertyPanelFloating;
	bool isPropertyPanelLeft;
	
	bool isStatusbarActive;

	// Internal (ODBC) is an empty string. Not empty is a plugin namespace.
	bool _use_system_database_backend;
	bool _use_application_database_backend;
	char* _system_database_backend;
	char* _application_database_backend;
	//char* _system_database_backend_temp;
	//char* _application_database_backend_temp;
	char* _dirloc;
	bool _force_use_database;
	bool _autoload;
	bool _autorefresh;
	bool _autoselect;
	bool _GUIMaximized;
	bool _logged_in;
	bool _loading_object_data;
	
	
	bool _loaded;
};
/*...e*/
/*...sclass lb_EventMapper:0:*/
class lb_EventMapper :
public lb_I_EventMapper
{
public:
        /**
         * If handler is NULL, then the event manager knows, that the requesting
         * instance has a dispatcher and therefore handles it self. You must register
         * the dispatcher after all requested id's for your events.
         */
        virtual lbErrCodes LB_STDCALL setEvent(const char* name, lbEvHandler handler = NULL);
        /**
         * Get the id back.
         */
        virtual int LB_STDCALL getID();	
        
public:
        lb_EventMapper();
        virtual ~lb_EventMapper();

        DECLARE_LB_UNKNOWN()

protected:
	virtual char* LB_STDCALL getName();
        virtual void LB_STDCALL setID(int id);

	friend class lb_I_EventManager;
        
	char* _name;
	int _id;
};
/*...e*/

/*...sclass lb_Dispatcher:0:*/
class lb_Dispatcher : public lb_I_Dispatcher {
public:
	virtual lbErrCodes LB_STDCALL setEventManager(lb_I_EventManager* EvManager);
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName);
	virtual lbErrCodes LB_STDCALL delEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName);
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr);

	virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp);
	virtual lbErrCodes LB_STDCALL delDispatcher(lb_I_Dispatcher* disp);
	
	/**
	 * ID variant
	 */
	virtual lbErrCodes LB_STDCALL dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult);
	/**
	 * Name variant
	 *
	 * This variant let's the programmer issue any events from his or her module.
	 * As a sample, it must be possible to query from an event name an id.
	 * Also it must be possible to call this function to announce a handler.
	 * 
	 * This may be solved this way:
	 * EvName = "AnnounceHandler"
	 * EvData = lb_I_HandlerAddress
	 */
	virtual lbErrCodes LB_STDCALL dispatch(const char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult);
	
	virtual lb_I_DispatchResponse* LB_STDCALL dispatch(lb_I_DispatchRequest* req);

#ifdef IMPLEMENT_NEWSTUFF
	/**
	 * Using the interceptor pattern at this place as it is simple to intercept all dynamic fnctionality.
	 * The interceptor to add should be put into a queue, if there is no event handler registered. Then
	 * it will be possible to add interceptors as early as possible.
	 */
	lbErrCodes LB_STDCALL setInterceptor(lb_I_DispatchInterceptor* evHandlerInstance, lbInterceptor evHandler_Before, lbInterceptor evHandler_After, const char* EvName);
	lbErrCodes LB_STDCALL delInterceptor(const char* EvName);
	lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_String* EvName, lb_I_Unknown* interceptedInstance);

	lb_I_String* LB_STDCALL getInterceptorDefinitions();
	lbErrCodes LB_STDCALL setInterceptorDefinitions(lb_I_String* s);
	
	lb_I_EvHandler* LB_STDCALL hasDefinedInterceptor(lb_I_String* event);
	lbErrCodes LB_STDCALL activateInterceptor(lb_I_String* EvName, lb_I_EvHandler* ev);
	
#endif
	
	void LB_STDCALL detachInstance(lb_I_EventHandler* evHandlerInstance);
	
public:
	lb_Dispatcher();
	virtual ~lb_Dispatcher();

	DECLARE_LB_UNKNOWN()


	/// \brief The events that must be intercepted.
	UAP(lb_I_Container, interceptorevents)
	UAP(lb_I_Container, dispatcher)
	UAP(lb_I_EventManager, evManager)
};
/*...e*/
/*...sclass lb_EventManager:0:*/
class lb_EventManager : public lb_I_EventManager {
public:
	virtual lbErrCodes LB_STDCALL registerEvent(const char* EvName, int & EvNr);
	virtual lbErrCodes LB_STDCALL resolveEvent(const char* EvName, int & evNr);
	virtual char* LB_STDCALL reverseEvent(int evNr);
	virtual lbErrCodes LB_STDCALL unregisterEvent(const char* EvName);
public:
	lb_EventManager();
	virtual ~lb_EventManager();
	
	DECLARE_LB_UNKNOWN()
	
protected:


	friend class lb_I_Dispatcher;

	// Maps id to event name	
	UAP(lb_I_Container, events)
	
	// Holds free id
	UAP(lb_I_Container, freeIds)
	
	// Reverse mapping name -> id
	UAP(lb_I_Container, reverse_events)
	
	int maxEvId;
};
/*...e*/

/*...sclass lb_EvHandler:0:*/
class lb_EvHandler : public lb_I_EvHandler {
public:        
	virtual lbErrCodes LB_STDCALL setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler);
	virtual lbEvHandler LB_STDCALL getHandler();
	virtual lb_I_EventHandler* LB_STDCALL getHandlerInstance();

	virtual lbErrCodes LB_STDCALL call(lb_I_Unknown* evData, lb_I_Unknown** evResult, bool hasDefinedInterceptor = false);

#ifdef IMPLEMENT_NEWSTUFF
	
	virtual lb_I_DispatchInterceptor* getInterceptor();
	virtual lbInterceptor LB_STDCALL getBeforeInterceptor();
	virtual lbInterceptor LB_STDCALL getAfterInterceptor();
	// Forwarded functions.
	virtual lbErrCodes LB_STDCALL setInterceptor(lb_I_DispatchInterceptor* evHandlerInstance, lbInterceptor evHandler_Before, lbInterceptor evHandler_After);
	virtual lbErrCodes LB_STDCALL delInterceptor();
	
	virtual lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_Unknown* interceptedInstance);

	/** \brief Implements execution of hook functions.
	 *
	 * Hooks, that are executed before could cancel the call to the dispatched function.
	 * The following error codes should be implemented:
	 * 
	 * ERR_HOOK_BEFORE_CANCEL			Cancel the dispatch call and return.
	 * ERR_HOOK_BEFORE_FAILURENOTICE	Returns a value in the result parameters with name 'failurenotice' and a value with name 'failurecode'.
	 */
	virtual lbErrCodes LB_STDCALL executeInterceptorBefore(lb_I_Unknown* EvData, lb_I_Unknown** EvResult);

	/** \brief Implements execution of hook functions.
	 *
	 * Hooks, that are executed before could cancel the call to the dispatched function.
	 * The following error codes should be implemented:
	 * 
	 * ERR_HOOK_BEFORE_FAILURENOTICE	Returns a value in the result parameters with name 'failurenotice' and a value with name 'failurecode'.
	 */
	virtual lbErrCodes LB_STDCALL executeInterceptorAfter(lb_I_Unknown* EvData, lb_I_Unknown** EvResult);

	/** \brief The handler may require an interceptor.
	 * Use this function to define if the handler needs an interceptor.
	 */
	virtual void LB_STDCALL setInterceptorRequired(bool _required);

	/** \brief Check if this handler needs an interceptor.
	 * This is used to auto cancel events that have a defined interceptor, but the interceptor plugin is missing.
	 * The check would enable determining missing plugins and thus tricking out permissions will fail this way.
	 */
	virtual bool LB_STDCALL getInterceptorRequired();
	


	
#endif	
	
public:
	lb_EvHandler();
	virtual ~lb_EvHandler();

	DECLARE_LB_UNKNOWN()

	bool interceptorRequired;
	
	lb_I_DispatchInterceptor* _evHandlerInstance_interceptor;
	lbInterceptor ev_interceptor_Before;
	lbInterceptor ev_interceptor_After;

	lb_I_EventHandler* _evHandlerInstance;
	lbEvHandler ev;
};
/*...e*/

/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_FUNCTOR(instanceOfEventMapper)
DECLARE_FUNCTOR(instanceOfEvHandler)

DECLARE_SINGLETON_FUNCTOR(instanceOfDispatcher)
DECLARE_SINGLETON_FUNCTOR(instanceOfEventManager)
DECLARE_SINGLETON_FUNCTOR(instanceOfMetaApplication)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif //LB_OBJECT
