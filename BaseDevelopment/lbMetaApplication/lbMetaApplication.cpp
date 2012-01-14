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
    p-Mail: Lothar Behrens
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.192 $
 * $Name:  $
 * $Id: lbMetaApplication.cpp,v 1.192 2012/01/14 22:56:26 lollisoft Exp $
 *
 * $Log: lbMetaApplication.cpp,v $
 * Revision 1.192  2012/01/14 22:56:26  lollisoft
 * Fixed a code generator bug that let the application fail to load from local file.
 *
 * Revision 1.191  2012/01/14 19:54:13  lollisoft
 * Generated code works with written code and application fully initializes.
 * Also it can exit without errors. Maybe the XSLT templates will not work yet.
 * This is due to small changes in the naming (plural vs singular).
 *
 * Revision 1.190  2012/01/09 07:37:51  lollisoft
 * Fixed some functor naming problems in code generator
 * and changed some log messages to be verbose only.
 *
 * Revision 1.189  2011/10/29 06:03:58  lollisoft
 * Refactored application model (and it's model classes) into separate files to enable code generation.
 * The code generation is planned for the model classes and the composite container for the model.
 * Refactored out the login and user management from meta application due to the fact that it is a
 * distinct feature the meta application should not provide. The code has been moved to a security
 * provider API based plugin that should be loaded as a plugin. Currently this fails and thus login is not
 * available.
 *
 * Revision 1.188  2011/10/15 16:33:26  lollisoft
 * Removed some unused code and no more required code. Current version does not compile at all.
 *
 * Revision 1.187  2011/10/15 13:14:04  lollisoft
 * Decided to make a hash cut and removed stuff that everywhere was the cause for crashes on Mac.
 * Currently the code crashes on windows, but lets see how it is working on Mac.
 *
 * Revision 1.186  2011/10/03 04:43:07  lollisoft
 * Fixes to try cope with rare application crash.
 *
 * Revision 1.185  2011/09/27 06:29:42  lollisoft
 * Fixed some issues reported by CppCheck.
 *
 * Revision 1.184  2011/07/10 06:17:06  lollisoft
 * Changed some logging messages to be verbose only.
 *
 * Revision 1.183  2011/06/18 17:29:55  lollisoft
 * Changed all char* to const char* where a corresponding warning was generated.
 *
 * Revision 1.182  2011/04/03 19:31:42  lollisoft
 * Minor changes in console mode.
 *
 * Revision 1.181  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.180  2010/08/29 21:09:30  lollisoft
 * Changes to get more modules compiled with MinGW.
 * Also changed my adress in some files as I have a new
 * home. Others will follow.
 *
 * Revision 1.179  2010/06/30 06:05:57  lollisoft
 * Added code to support unloading application module (detachInterface) and changed code to try correctly unloading modules.
 *
 * Revision 1.178  2010/05/30 08:28:26  lollisoft
 * Fixed crashes on Mac OS X while running unit tests.
 *
 * Revision 1.177  2010/05/29 18:07:18  lollisoft
 * Changes to compile code with MinGW.
 *
 * Revision 1.176  2010/05/29 07:45:24  lollisoft
 * Some trouble when other modules compiled with mingw. Fixed.
 * Bug in resolveEvent fixed. Used a container without checking against NULL.
 *
 * Revision 1.175  2010/05/17 05:44:40  lollisoft
 * Many changes related to support mixing MinGW with Open Watcom.
 *
 * Revision 1.174  2010/04/25 21:37:09  lollisoft
 * Successfully ported lbHook to MINGW compiler. There were only two issues
 * I have identified: The enum problem as reported from Michal Necasek having
 * different sizes and the interface ordering to be equal to implementing class
 * declaration. But this only belongs to my UnitTest code yet.
 *
 * Aim of this is the ability to mix in MINGW modules for features Open Watcom
 * didn't support yet and let me do this with minimal effort.
 *
 * Revision 1.173  2010/02/22 09:28:22  lollisoft
 * Missing return value.
 *
 * Revision 1.172  2010/02/17 13:47:26  lollisoft
 * Added default parameter to enable skipping yielding.
 *
 * Revision 1.171  2010/01/24 22:54:27  lollisoft
 * Removed two log messages that makes problems when timer event works in one second interval.
 *
 * Revision 1.170  2010/01/22 12:24:52  lollisoft
 * Bugfix for a null pointer crash.
 *
 * Revision 1.169  2010/01/16 16:22:41  lollisoft
 * Added methods to cleanup intercepted instances that otherwise will crash the application due to dangling pointers.
 *
 * Revision 1.168  2010/01/15 18:48:48  lollisoft
 * Interceptor logic works as long as one database form is
 * not closed when another is opened and then the
 * interceptor walks through the list of intercepted event
 * handlers.
 *
 * This is due to the fact that wxWidgets deletes the instance, but the container with a reference is not notified to remove the instance (without deletion).
 *
 * This is tricky.
 *
 * Revision 1.167  2010/01/14 17:31:25  lollisoft
 * More changes for interceptor functionality, but crashes on Mac OS X (PPC).
 *
 * Revision 1.166  2010/01/12 19:45:41  lollisoft
 * Mostly completed plugin based interceptor functionality for events.
 *
 * Revision 1.165  2010/01/10 10:17:06  lollisoft
 * Added code for interceptor functionality.
 *
 * Revision 1.164  2009/12/11 18:55:15  lollisoft
 * Bugfix when no application module is loaded, the name is also not available.
 *
 * Revision 1.163  2009/12/06 19:20:16  lollisoft
 * Modified build process to use precompiled files.
 * Corrected the long build time problem. It is located in the _LOG macro.
 * Updated wxPropgrid to 1.4.9.1 and updated building against wxMSW 2.8.10.
 *
 * Build works, but running the application fails with not properly initialized error.
 * (0xc0000005)
 *
 * Also updated the iss files for the new planned release.
 *
 * Revision 1.162  2009/09/26 18:57:14  lollisoft
 * Bugfix for a crash when the application was set to use ODBC, but that was not available when restarted.
 *
 * Revision 1.161  2009/09/03 17:32:43  lollisoft
 * Corrected exit behaviour when clicking on window close button.
 *
 * Revision 1.160  2009/07/19 22:40:20  lollisoft
 * Moved the installation step of an initial database to the new plugin install method.
 *
 * Revision 1.159  2009/07/11 19:47:20  lollisoft
 * Corrected behaviour when ODBC database is available, but installation fails.
 * Added a question in case to switch to local Sqlite database.
 *
 * Revision 1.158  2009/07/05 00:46:50  lollisoft
 * Return prior registered event ID for the name.
 *
 * Revision 1.157  2009/06/29 10:31:00  lollisoft
 * Renamed a dispatch parameter.
 *
 * Revision 1.156  2009/06/10 11:56:51  lollisoft
 * Added functions to help passing application process name.
 *
 * Revision 1.155  2009/06/02 18:11:31  lollisoft
 * Added search path for ../Database in case if initial SQL scripts are only located in development directory.
 *
 * Revision 1.154  2009/03/14 22:12:12  lollisoft
 * Corrected linux part of initial SQL file lookup.
 *
 * Revision 1.153  2009/03/14 11:11:57  lollisoft
 * Fixed lookup of SQL files under Solaris.
 *
 * Revision 1.152  2009/03/13 20:53:15  lollisoft
 * Corrected lookup problem of SQL scripts under Windows.
 *
 * Revision 1.151  2009/03/12 19:08:41  lollisoft
 * Changed database bootstrapping code (location of SQL files) according to better fit into OS type.
 *
 * Revision 1.150  2009/02/12 11:31:11  lollisoft
 * Added missing return.
 *
 * Revision 1.149  2009/02/11 18:39:57  lollisoft
 * Added functions to provide property changing by code.
 * Also added an uninitialisation function to ensure correct
 * cleanup. Also added a simple fireEvent function.
 *
 * Revision 1.148  2008/10/27 18:59:34  lollisoft
 * Moved uninitialize call before deletion of active document.
 *
 * Revision 1.147  2008/10/19 17:04:13  lollisoft
 * Using system account on internal database in installDatabase(). Changed logging function name in getApplications().
 *
 * Revision 1.146  2008/09/26 10:43:20  lollisoft
 * Removed shortcut.
 *
 * Revision 1.145  2008/08/30 09:23:37  lollisoft
 * Initial setup works and also the autoload of 'lbDMF Manager'.
 *
 * Revision 1.144  2008/08/30 06:59:44  lollisoft
 * Added a comment to restart the application after initial installation.
 *
 * Revision 1.143  2008/08/25 14:54:32  lollisoft
 * Added fix for WIndows based installation path.
 *
 * Revision 1.142  2008/08/18 06:11:58  lollisoft
 * Fix for OS X.
 *
 * Revision 1.141  2008/08/08 11:30:30  lollisoft
 * Tries on Linux
 *
 * Revision 1.140  2008/08/07 17:25:44  lollisoft
 * Using different path per platform.
 *
 * Revision 1.139  2008/08/03 09:14:42  lollisoft
 * Implemented automatic installation of an initial database.
 *
 * Revision 1.138  2008/08/02 07:24:48  lollisoft
 * Activated database checks.
 *
 * Revision 1.137  2008/05/23 23:32:35  lollisoft
 * Fixed missing returns.
 *
 * Revision 1.136  2008/05/21 22:25:10  lollisoft
 * Some improvements for working with Sqlite database.
 *
 * Revision 1.135  2008/05/19 06:42:30  lollisoft
 * Added code to check for availability of any database. Corrected splash screen and modal dialog problems.
 *
 * Revision 1.134  2008/05/16 06:39:19  lollisoft
 * Added switches to disable database backend settings.
 *
 * Revision 1.133  2008/05/12 21:46:47  lollisoft
 * Trim the database namespaces.
 *
 * Revision 1.132  2008/05/11 22:33:03  lollisoft
 * Bugfixes and propably some log messages changed / added.
 *
 * Revision 1.131  2008/04/18 05:58:30  lollisoft
 * Added new methods to get ans set application and system database backend (the namespace of a plugin).
 *
 * Revision 1.130  2008/04/14 06:05:33  lollisoft
 * Added database backend configuration for near pluggable database support. Corrected property panel displaying at startup.
 *
 * Revision 1.129  2008/02/23 18:25:11  lollisoft
 * Added an optional boolean parameter that additionally
 * triggers change events of the properties in parameter 1.
 *
 * Revision 1.128  2008/02/18 20:02:51  lollisoft
 * Added function to get a directory from the user.
 *
 * Revision 1.127  2008/02/12 21:36:27  lollisoft
 * Added code that allows to store parameter sets into the meta application file.
 *
 * Revision 1.126  2007/11/22 16:08:10  lollisoft
 * Other starting ID.
 *
 * Revision 1.125  2007/11/19 11:16:11  lollisoft
 * These chanes do not really help, but some unused code has been removed. Check codegeneration on Windows.
 *
 * Revision 1.124  2007/10/11 13:38:39  lollisoft
 * Propably completed offline capability from system database.
 *
 * Revision 1.123  2007/09/04 11:41:46  lollisoft
 * Some corrections in setting correct application name.
 *
 * Revision 1.122  2007/08/31 16:49:50  lollisoft
 * This should fix loaded application name overwrite bug.
 *
 * Revision 1.121  2007/08/31 16:06:07  lollisoft
 * Removed last application property. Not required to edit.
 *
 * Revision 1.120  2007/08/16 09:44:59  lollisoft
 * Changes in propgrid and related stuff that let the application correctly change boolean properties.
 *
 * Revision 1.119  2007/08/02 07:06:06  lollisoft
 * Added member function to remove a toolbar.
 *
 * Revision 1.118  2007/07/14 08:50:26  lollisoft
 * Hopefully the last changes for 1.0rc1 release.
 *
 * Revision 1.117  2007/07/13 12:28:36  lollisoft
 * Remaining code changes done and fixed database login bug.
 *
 * Revision 1.116  2007/07/12 11:02:32  lollisoft
 * Important bugfix in database classes. Connetcion problems should be fixed.
 *
 * Revision 1.115  2007/07/11 14:49:14  lollisoft
 * Added flag to force database usage and changed code to
 * support the flag.
 *
 * Revision 1.114  2007/07/09 20:14:10  lollisoft
 * Moved loading application database schema to that
 * point, when exporting application to XML. This way
 * loading the application is a bit faster.
 *
 * Revision 1.113  2007/07/04 16:09:30  lollisoft
 * Some console messages or errors have been changed.
 *
 * Revision 1.112  2007/06/16 10:26:51  lollisoft
 * This changes let the application successfully run under Solaris. Also a bug is fixed that caused a crash at application exit.
 *
 * Revision 1.111  2007/06/06 21:33:23  lollisoft
 * Made bugfixes and enhancements that were required.
 *
 * Revision 1.110  2007/05/14 19:19:14  lollisoft
 * Unfinished changes. Go to Linux.
 *
 * Revision 1.109  2007/05/11 21:21:01  lollisoft
 * Linux compiler is more restrictive with const char*
 *
 * Revision 1.108  2007/05/01 08:39:21  lollisoft
 * Added more propertypanel functionality.
 *
 * Revision 1.107  2007/04/22 13:48:22  lollisoft
 * Bugfix if application would be loaded by environment.
 * Added 'Main Toolbar' initialisation to here.
 *
 * Revision 1.106  2007/02/09 21:35:51  lollisoft
 * Implemented remaining stuff for basic toolbar support.
 * But these seems not to show the bitmap on Mac OS X.
 *
 * Revision 1.105  2007/02/08 22:36:05  lollisoft
 * Partial toolbar implementation
 *
 * Revision 1.104  2007/02/03 11:04:36  lollisoft
 * Implemented directory location property handler. This is used in lbMetaApplication.
 *
 * Revision 1.103  2007/01/29 20:12:59  lollisoft
 * Checkin for Linux.
 *
 * Revision 1.102  2007/01/14 15:06:15  lollisoft
 * Added a new function to show a simple message box.
 *
 * Revision 1.101  2007/01/03 17:08:39  lollisoft
 * Activated more logging and added more error messages.
 *
 * Revision 1.100  2006/12/23 15:42:42  lollisoft
 * Many changes to get a more stable release. Still having problems with database updates on foreign keys.
 *
 * Revision 1.99  2006/12/10 17:03:21  lollisoft
 * Log, don't write to console.
 *
 * Revision 1.98  2006/10/23 21:20:48  lollisoft
 * Small changes to compile under Linux again
 *
 * Revision 1.97  2006/10/22 18:34:36  lollisoft
 * Many memory leaks resolved, but they were caused by small errors :-(
 * This is also a sync.
 *
 * Revision 1.96  2006/07/20 17:41:15  lollisoft
 * Bugfix for stack overflow. Too many char[] arrays on the stack.
 * Corrected missing entries in Applications list. It wasn't correctly
 * setup while manual login. Thus, later not stored.
 *
 * Revision 1.95  2006/07/17 17:37:45  lollisoft
 * Changes dueto bugfix in plugin manager. Repeadable iterator problem.
 * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
 * be found any more after first query.
 *
 * Code works well with improved trmem library, but there is still a crash in
 * database classes (pgODBC library).
 *
 * Revision 1.94  2006/07/02 13:25:57  lollisoft
 * Added active document support.
 *
 * Revision 1.93  2006/06/24 06:19:54  lollisoft
 * Commit due to travel to Duesseldorf.
 *
 * Revision 1.92  2006/06/15 18:36:28  lollisoft
 * Partly implemented load of lbDMF database contents into file. (Login and application list)
 *
 * Revision 1.91  2006/06/10 09:51:51  lollisoft
 * Implemented new load and save method for meta application.
 *
 * Revision 1.90  2006/06/09 16:03:33  lollisoft
 * Changes on Mac OS X before weekend.
 *
 * Revision 1.89  2006/06/03 06:16:57  lollisoft
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
 * Revision 1.88  2006/05/07 07:07:57  lollisoft
 * Corrected file dialog cancel handling.
 *
 * Revision 1.87  2006/03/28 11:34:04  lollisoft
 * Renamed Initialize to initialize and added unloadApplication for better unloading of the application.
 *
 * Revision 1.86  2006/03/24 17:12:22  lollisoft
 * Added GUI state for maximized or not.
 *
 * Revision 1.85  2006/03/16 08:01:04  lollisoft
 * Added set and getAutorefreshData members to the  lb_I_MetaApplication implementation. Also included that flags in the property panel.
 *
 * Revision 1.84  2006/03/09 09:29:11  lollisoft
 * Catch plugin failure while loading application settings and
 * database connection failure.
 *
 * Revision 1.83  2006/02/22 11:49:57  lollisoft
 * Moved the general part to meta application. wxWrapper does ask for it when left panel will be shown.
 *
 * Revision 1.82  2006/02/21 20:56:30  lollisoft
 * Wrong menu updating.
 *
 * Revision 1.81  2006/02/21 19:35:50  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.80  2006/02/19 18:41:35  lollisoft
 * Feedback of properties works good. I am use the
 * dispatcher mechanism to forward the change events
 * on per lb_I_Parameter instance and the category name
 * to a registered handler.
 *
 * So one handler must be capable to recieve values for all
 * elements of one lb_I_Parameter instance.
 *
 * Revision 1.79  2006/02/17 23:57:13  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.78  2006/01/30 15:54:14  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.77  2006/01/26 14:03:23  lollisoft
 * Added event en/disable and toggle functions. Also added
 * askYesNo function.
 *
 * Revision 1.76  2006/01/22 13:36:51  lollisoft
 * Reading back an added parameter (result) works.
 *
 * Revision 1.75  2006/01/21 23:48:14  lollisoft
 * Added new member to ask the user for a file.
 *
 * Revision 1.74  2006/01/20 21:30:39  lollisoft
 * Used base class in loadApplication changed to lb_I_Application.
 *
 * Revision 1.73  2005/12/11 19:15:49  lollisoft
 * Release changes for 0.6.0. Added todo entries, removed unused code.
 *
 * Revision 1.72  2005/11/26 18:59:11  lollisoft
 * Minor changes to compile and run under Linux
 *
 * Revision 1.71  2005/11/20 13:39:52  lollisoft
 * Wrong variable name
 *
 * Revision 1.70  2005/11/18 23:41:31  lollisoft
 * More memory leaks have been fixed. There are currently less than 200
 * chunks unfreed, wich may be located in the plugin mechanism.
 *
 * Revision 1.69  2005/11/16 13:17:03  lollisoft
 * Added Memtrack breakpoint counter.
 *
 * Corrected reference count bug by using UAP for 'a' and using preload to
 * delegate unloading of shared library, loaded by loadApplication into
 * destructor.
 *
 * Revision 1.68  2005/11/11 22:51:30  lollisoft
 * Memory leaks removed. There are currently only 4 chunks leaky.
 * These may be false positives, because one of them is an allocated
 * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
 * wxMenuBar gets an owner (see wxWidgets documentation).
 *
 * Revision 1.67  2005/11/06 19:25:33  lollisoft
 * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
 *
 * Revision 1.66  2005/11/02 16:24:28  lollisoft
 * Bug for the program ending crash and the cout crash found. See history in
 * lbDB.cpp.
 *
 * Revision 1.65  2005/10/31 19:37:55  lollisoft
 * This version compiles and ends without a crash at exit. I have added a simple
 * string class to store places of queryInterface calls and setModuleManager calls.
 * This may change the layout to let the application not crash at exit.
 *
 * Revision 1.64  2005/10/31 15:02:04  lollisoft
 * Singleton mismatched to their declaration. Small correction in DllMain.
 *
 * Revision 1.63  2005/06/27 10:32:08  lollisoft
 * Mostly changes to conio.h conflicts while XCode build
 *
 * Revision 1.62  2005/06/20 11:18:46  lollisoft
 * Added interface set/get User and ApplicationName
 *
 * Revision 1.61  2005/05/04 22:09:38  lollisoft
 * Many memory leaks fixed. Changed _CL_LOG to _CL_VERBOSE.
 *
 * Revision 1.60  2005/05/03 21:15:49  lollisoft
 * Better memtrack support
 *
 * Revision 1.59  2005/05/01 21:26:15  lollisoft
 * Added informative filename to show when printing memory leaks.
 *
 * Thanks to the trmem code from Open Watcom.
 *
 * Revision 1.58  2005/05/01 01:12:35  lollisoft
 * Found a really big memory leak. It happens due to missing setup of ref variable
 * in lbFunctorEntity class of lbModule.cpp.
 *
 * Due to the fact, that I use this class for each instance retrival, it wasted
 * much memory. More: See documentation in that class.
 *
 * Revision 1.57  2005/04/18 19:04:22  lollisoft
 * Returning proper error code.
 *
 * Revision 1.56  2005/04/02 09:52:37  lollisoft
 * Put optional parameter into paramater list.
 *
 * Revision 1.55  2005/03/31 08:59:34  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.54  2005/03/19 16:40:59  lollisoft
 * Implemented i18n.
 *
 * Revision 1.53  2005/02/20 18:01:23  lollisoft
 * Bugfix due to buffer overflow affecting GUI sample under Linux
 *
 * Revision 1.52  2005/02/20 09:39:33  lollisoft
 * Deactivated unneeded menu entries.
 *
 * Revision 1.51  2005/02/14 16:37:14  lollisoft
 * Much tries to get foreign key handling work under linux. But there might be some magic bugs, that don't let them use
 *
 * Revision 1.50  2005/02/13 09:13:16  lollisoft
 * Using applicationName to load not a hardcoded application
 *
 * Revision 1.49  2005/02/12 15:46:32  lollisoft
 * Changed SQL queries, enabled optional user and password settings via
 * environment.
 *
 * Revision 1.48  2005/02/10 17:02:26  lollisoft
 * Changes for Mac OS X
 *
 * Revision 1.47  2005/02/02 13:30:29  lollisoft
 * Latest changes for version 0.4.1
 *
 * Revision 1.46  2005/01/27 12:53:27  lollisoft
 * Changed SQL query not to use " in it
 *
 * Revision 1.45  2005/01/25 12:54:41  lollisoft
 * Verbose message added
 *
 * Revision 1.44  2005/01/23 13:43:04  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.43  2005/01/23 11:29:27  lollisoft
 * Now the code compiles under SuSE Linux 9.1
 *
 * Revision 1.42  2005/01/21 14:58:47  lollisoft
 * Removed some unused log messages, changed SQL case to lower
 *
 * Revision 1.41  2005/01/05 13:41:36  lollisoft
 * New dynamic application implementation works
 *
 * Revision 1.40  2004/10/09 16:55:07  lollisoft
 * Bugfix for call of pure virtual function. Don't know where it comes from ??
 *
 * Revision 1.39  2004/08/10 18:25:26  lollisoft
 * Lesser logging messages.
 *
 * Revision 1.38  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.37  2004/07/18 07:28:25  lollisoft
 * Now the database sample works also under linux. Some bugs solved and minor changes
 *
 * Revision 1.36  2004/07/17 08:47:57  lollisoft
 * Bugfix for MSVC
 *
 * Revision 1.35  2004/07/16 20:24:41  lollisoft
 * Added handler to enter into the debugger
 *
 * Revision 1.34  2004/06/29 16:35:50  lollisoft
 * Removed some log messages
 *
 * Revision 1.33  2004/04/10 17:54:23  lollisoft
 * Current version runs on linux again. There was a bug in additional linux code to strcat to a variable. This variable was given as a parameter and therefore I cannot assume, that I am able to have a big enough buffer for that action. Electric Fence gave me the hint for that bug.
 *
 * Revision 1.32  2004/02/02 23:24:39  lollisoft
 * New label and text field handlers works
 *
 * Revision 1.31  2004/01/24 16:16:57  lollisoft
 * Added support for loading application
 *
 * Revision 1.30  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.29  2003/08/22 17:38:35  lollisoft
 * Implemented a handler for a button press event and code to demonstrate
 *
 * Revision 1.28  2003/08/16 18:03:25  lollisoft
 * Added my new address due to move
 *
 * Revision 1.27  2003/07/15 22:18:05  lollisoft
 * Removed debug messages, implemented numeric dispatcher and much more
 *
 * Revision 1.26  2003/07/10 21:13:06  lollisoft
 * Adding menu entry implemented
 *
 * Revision 1.25  2003/03/14 16:00:36  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.24  2003/02/17 21:34:34  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.23  2003/02/09 13:22:50  lothar
 * Different log usage
 *
 * Revision 1.22  2003/01/27 21:18:04  lothar
 * Missed STARTREF setup
 *
 * Revision 1.21  2003/01/19 17:31:31  lothar
 * Runs now with MSC
 *
 * Revision 1.20  2003/01/15 22:42:20  lothar
 * Compiles with MSC
 *
 * Revision 1.19  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.18  2002/12/12 20:59:38  lothar
 * Now it runs under Linux again
 *
 * Revision 1.17  2002/12/08 17:07:23  lothar
 * More tries to run under linux
 *
 * Revision 1.16  2002/11/29 19:50:26  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.15  2002/11/08 18:53:25  lothar
 * Compiles now (-d1)
 *
 * Revision 1.13  2002/10/04 16:53:11  lothar
 * Replaced old LOG macro with the new
 * _LOG << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.12  2002/10/01 19:22:59  lothar
 * Broken
 *
 * Revision 1.11  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.10  2002/09/17 04:26:36  lothar
 * First API-Callback works
 *
 * Revision 1.9  2002/09/12 18:34:02  lothar
 * Added some UI wrapper and sub module creation. Cleanup
 *
 * Revision 1.8  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.7  2002/09/04 17:52:12  lothar
 * Problems with stack cleanup
 *
 * Revision 1.6  2002/08/21 17:59:42  lothar
 * More functions implemented
 *
 * Revision 1.5  2002/08/06 05:41:39  lothar
 * More special Dispatcher and EventManager interface.
 * Empty bodies compiling
 *
 * Revision 1.4  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.3  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/
#define LB_METAAPP_DLL

#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif

/*...sincludes:0:*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __cplusplus
}
#endif

#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <lbInterfaces-sub-security.h>
#include <lbmetaapp-module.h>
#include <lbMetaApplication.h>
/*...e*/

/*...sFunctors:0:*/
IMPLEMENT_FUNCTOR(instanceOfEventMapper, lb_EventMapper)
IMPLEMENT_FUNCTOR(instanceOfEvHandler, lb_EvHandler)

/// \todo Check if these OS differences are really needed.

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfEventManager, lb_EventManager)
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfDispatcher, lb_Dispatcher)
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfMetaApplication, lb_MetaApplication)

/*...e*/

/*...slb_MetaApplication:0:*/
/*...sctors\47\dtors:0:*/
lb_MetaApplication::lb_MetaApplication() {
	
	gui = NULL;
	moduleName = NULL;

	_GUIMaximized = true;
	_loaded = false;

	_autoload = true;
	_autoselect = false;
	_autorefresh = false;
	_logged_in = false;
	_force_use_database = false;

	isPropertyPanelFloating = false;
	isPropertyPanelLeft = true;

	isStatusbarActive = true;

	_use_application_database_backend = false;
	_use_system_database_backend = false;
	_application_database_backend = strdup("");
	_system_database_backend = strdup("");
	_dirloc = strdup(".");
	_loading_object_data = false;

	REQUEST(getModuleInstance(), lb_I_Container, activeDocuments)

	activeDocuments->setCloning(false);

	REQUEST(getModuleInstance(), lb_I_String, ProcessName)

	REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());

	_CL_VERBOSE << "lb_MetaApplication::lb_MetaApplication() called." LOG_
}

void LB_STDCALL lb_MetaApplication::disableStatusbar() {
	isStatusbarActive = false;
}

lb_MetaApplication::~lb_MetaApplication() {
	_CL_VERBOSE << "lb_MetaApplication::~lb_MetaApplication() called." LOG_

	lbErrCodes err = ERR_NONE;

	/*
	 * There must be an unload process of the loaded application's, so that it
	 * will not unloaded in the wrong order when unHookAll is called.
	 *
	 *
	 * Destroy loaded object and manually unload the corresponding module.
	 */

	if (app != NULL) {
		app--;
		app.resetPtr();
	}

	if (moduleName) {
		_CL_VERBOSE << "Unload module " << moduleName << "." LOG_
		lbUnloadModule(moduleName);
		_CL_VERBOSE << "Unloaded module." LOG_

		free(moduleName);
	}


	if (_dirloc != NULL) free(_dirloc);
}
/*...e*/


void			LB_STDCALL lb_MetaApplication::setProcessName(const char* name) {
	*ProcessName = name;
}

lb_I_String*	LB_STDCALL lb_MetaApplication::getProcessName() {
	ProcessName++;
	return ProcessName.getPtr();
}

lbErrCodes LB_STDCALL lb_MetaApplication::uninitialize() {
#ifdef OLD_TIGHT_DEPENDENCY	
	if (User_Applications != NULL) User_Applications--;
	if (Users != NULL) Users--;
	if (Applications != NULL) Applications--;
#endif
	if (LogonApplication != NULL) LogonApplication--;
	if (activeDocuments != NULL) activeDocuments--;
	if (app != NULL) {
		app--;
		app.resetPtr();
	}

	REQUEST(getModuleInstance(), lb_I_Container, activeDocuments)

	return ERR_NONE;
}

lb_I_Unknown* LB_STDCALL lb_MetaApplication::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
	uk++;
	return uk.getPtr();
}

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::doAutoload, "doAutoload");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::doLog, "doLog");

	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::enterDebugger, "enterDebugger");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbEvHandler1, "getBasicApplicationInfo");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbEvHandler2, "getMainModuleInfo");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbButtonTestHandler, "Button Test pressed");

	// Register a general login functionality
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::getLoginData, "getLoginData");

	return ERR_NONE;
}
/*...e*/

/*...sevent handlers\44\ that can be registered:0:*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\enterDebugger\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::enterDebugger(lb_I_Unknown* uk) {
#ifdef WINDOWS
	DebugBreak();
#endif
#ifdef LINUX
	// How do I this under linux ??
#endif
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbEvHandler1\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler1(lb_I_Unknown* uk) {
	_CL_LOG << "lb_MetaApplication::lbEvHandler1() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbEvHandler2\40\lb_I_Unknown\42\ uk\41\ \47\\47\ Show a simple message box:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler2(lb_I_Unknown* uk) {

	if (gui != NULL) {
	        gui->msgBox("Information", "The main module of this application is a DLL and creates a basic functionality.\nThe real application will be loaded from configuraton and then the control\nwill be delegated to it.");
	} else {
	        COUT << "Information: The main module of this application is a DLL and creates a basic functionality.\nThe real application will be loaded from configuraton and then the control\nwill be delegated to it.\n" << ENDL;
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbButtonTestHandler\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbButtonTestHandler(lb_I_Unknown* uk) {

        if (gui != NULL) {
                gui->msgBox("Information", "Test button has been pressed");
        } else {
                COUT << "lb_MetaApplication::lbButtonTestHandler() called in console mode" << ENDL;
        }

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getLoginData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getLoginData(lb_I_Unknown* uk) {

        if (gui != NULL) {
                UAP(lb_I_Form, loginForm)

                loginForm = gui->createLoginForm();
        } else {
                COUT << "Login form on console not supported" << ENDL;
        }

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::doAutoload(lb_I_Unknown* uk) {
	_autoload = !_autoload;

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::doLog(lb_I_Unknown* uk) {
	setLogActivated(!isLogActivated());

	return ERR_NONE;
}
/*...e*/


BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lb_MetaApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
	ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\save\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::save() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP(lb_I_Plugin, pl1)
	UAP(lb_I_Unknown, ukPl1)
	pl1 = PM->getFirstMatchingPlugin("lb_I_FileOperation", "OutputStreamVisitor");

	if (pl1 == NULL) {
		_LOG << "Error: Need a plugin with an implementation of interface lb_I_FileOperation in namespace OutputStreamVisitor. Cannot save meta application data." LOG_
			return ERR_FILE_WRITE_DEFAULT;
	}

	ukPl1 = pl1->getImplementation();
	UAP(lb_I_FileOperation, fOp1)
	QI(ukPl1, lb_I_FileOperation, fOp1)

#ifdef OSX
	lb_I_GUI* g = NULL;
	getGUI(&g);
	if (g) {
		if (!fOp1->begin("./wxWrapper.app/Contents/Resources/MetaApp.mad")) {
			// Fallback
			if (!fOp1->begin("MetaApp.mad")) {
				_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

				return ERR_FILE_WRITE_DEFAULT;
			}
		}
	} else if (!fOp1->begin("MetaApp.mad")) {
		_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

		return ERR_FILE_WRITE_DEFAULT;
	}
#endif
#ifndef OSX
	if (!fOp1->begin("MetaApp.mad")) {
		_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

		return ERR_FILE_WRITE_DEFAULT;
	}
#endif

	UAP(lb_I_Unknown, ukAcceptor1)
	QI(this, lb_I_Unknown, ukAcceptor1)
	ukAcceptor1->accept(*&fOp1);

	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
	disp->accept(*&fOp1);


	if (propertySets != NULL) {
		_LOG << "Save property sets..." LOG_
		propertySets->accept(*&fOp1);
		_LOG << "Saved property sets." LOG_
	} else {
		_LOG << "Don't save property sets. Not initialized." LOG_
	}

	// Save a Users list

#ifdef OLD_TIGHT_DEPENDENCY	
	if (Users == NULL) {
			UAP(lb_I_Plugin, pl2)
			UAP(lb_I_Unknown, ukPl2)
			pl2 = PM->getFirstMatchingPlugin("lb_I_UserAccounts", "Model");
			ukPl2 = pl2->getImplementation();
			QI(ukPl2, lb_I_UserAccounts, Users)

			_LOG << "Save default user data ..." LOG_
	}

	if (Users != NULL) {
		_LOG << "lb_MetaApplication::save(): Save Users list." LOG_
		Users->accept(*&fOp1);
	}

	if (Applications == NULL) {
			UAP(lb_I_Plugin, pl3)
			UAP(lb_I_Unknown, ukPl3)
			pl3 = PM->getFirstMatchingPlugin("lb_I_Applications", "Model");
			ukPl3 = pl3->getImplementation();
			QI(ukPl3, lb_I_Applications, Applications)

			_LOG << "Save default application data ..." LOG_
	}

	if (Applications != NULL) {
		_LOG << "lb_MetaApplication::save(): Save Applications list." LOG_
		Applications->accept(*&fOp1);
	}

	if (User_Applications == NULL) {
			UAP(lb_I_Plugin, pl4)
			UAP(lb_I_Unknown, ukPl4)
			pl4 = PM->getFirstMatchingPlugin("lb_I_User_Applications", "Model");
			ukPl4 = pl4->getImplementation();
			QI(ukPl4, lb_I_User_Applications, User_Applications)

			_LOG << "Save default user - application data ..." LOG_
	}

	if (User_Applications != NULL) {
		_LOG << "lb_MetaApplication::save(): Save User_Applications list." LOG_
		User_Applications->accept(*&fOp1);
	}
#endif

	fOp1->end();

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\load\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::load() {
	lbErrCodes err = ERR_NONE;

	_loading_object_data = true;

	// Get the plugin to read a standard stream based file

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");

	if (pl != NULL) {
		ukPl = pl->getImplementation();

		if (ukPl != NULL) {
			UAP(lb_I_FileOperation, fOp)
			QI(ukPl, lb_I_FileOperation, fOp)

#ifdef OSX
			lb_I_GUI* g = NULL;
			getGUI(&g);
			if (g) {
				if (!fOp->begin("./wxWrapper.app/Contents/Resources/MetaApp.mad")) {
					// Fallback
					if (!fOp->begin("MetaApp.mad")) {
						_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

						return ERR_FILE_READ;
					}
				}
			} else if (!fOp->begin("MetaApp.mad")) {
				_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

				return ERR_FILE_READ;
			}
#endif
#ifndef OSX
			if (!fOp->begin("MetaApp.mad")) {
				_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

				return ERR_FILE_READ;
			}
#endif

			// Read my data
			UAP(lb_I_Unknown, ukAcceptor)
			QI(this, lb_I_Unknown, ukAcceptor)
			ukAcceptor->accept(*&fOp);

#ifdef IMPLEMENT_NEWSTUFF
			/* Here it seems the best and earliest place to load interceptor configuration.
			 * Before any user could login (except applications without login required), the
			 * interceptors were setup. The interceptors may be registered before the intented
			 * event handler will be registered and thus the interceptor must be stored until
			 * it could be activated.
			 *
			 * A stored interceptor not only needs the name of the event to intercept, but also
			 * the class and the pointer to the methods to be used for interception. Currently I
			 * do not know  how to store the pointer to the method, as I assume it will change on
			 * each application start.
			 *
			 * A plugin must register the interceptors of interest to activate the interception
			 * functionality. The dispatcher should cancel all dispatching calls who have a registered
			 * interceptor that is not fully loaded.
			 */

			UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
			disp->accept(*&fOp);
#endif

			_LOG << "Read property sets from metaapp file..." LOG_
			REQUEST(getModuleInstance(), lb_I_Parameter, propertySets)
			propertySets->accept(*&fOp);
			_LOG << "Done reading property sets. Having " << propertySets->Count() << " sets." LOG_


#ifdef OLD_TIGHT_DEPENDENCY	
			UAP(lb_I_Plugin, pl2)
			UAP(lb_I_Unknown, ukPl2)
			pl2 = PM->getFirstMatchingPlugin("lb_I_UserAccounts", "Model");
			ukPl2 = pl2->getImplementation();

			UAP(lb_I_Plugin, pl3)
			UAP(lb_I_Unknown, ukPl3)
			pl3 = PM->getFirstMatchingPlugin("lb_I_Applications", "Model");
			ukPl3 = pl3->getImplementation();

			UAP(lb_I_Plugin, pl4)
			UAP(lb_I_Unknown, ukPl4)
			pl4 = PM->getFirstMatchingPlugin("lb_I_User_Applications", "Model");
			ukPl4 = pl4->getImplementation();

/* Meta application could not know details of the application. Has it forms ?
			UAP(lb_I_Plugin, pl5)
			UAP(lb_I_Unknown, ukPl5)
			pl5 = PM->getFirstMatchingPlugin("lb_I_Applications_Formulars", "Model");
			ukPl5 = pl5->getImplementation();
*/





			QI(ukPl2, lb_I_UserAccounts, Users)
			QI(ukPl3, lb_I_Applications, Applications)
			QI(ukPl4, lb_I_User_Applications, User_Applications)
//			QI(ukPl5, lb_I_Applications_Formulars, ApplicationFormulars)

			// Database read will be forced by login.
			if (!_force_use_database) {
				_LOG << "Read users, applications and user associations from file." LOG_
				// Read an Users list
				ukPl2->accept(*&fOp);
				// Read an Applications list
				ukPl3->accept(*&fOp);
				// Read users applications
				ukPl4->accept(*&fOp);
				// Read applications to formular assoc
//				ukPl5->accept(*&fOp);

				if (Users->getUserCount() == 0) {
					_LOG << "Warning: Users list from file does not contain any data." LOG_
				}
			} else {
				UAP(lb_I_Container, apps)
				apps = getApplications();
			}
/*
			UAP_REQUEST(getModuleInstance(), lb_I_String, backend)
			UAP_REQUEST(getModuleInstance(), lb_I_Boolean, usebackend)

			backend->accept(*&fOp);
			if (_application_database_backend != NULL) free(_application_database_backend);
			_application_database_backend = strdup(backend->charrep());

			backend->accept(*&fOp);
			if (_system_database_backend != NULL) free(_system_database_backend);
			_system_database_backend = strdup(backend->charrep());

			_LOG << "Load application database backend: '" << _application_database_backend << "'" LOG_
			_LOG << "Load system database backend: '" << _system_database_backend << "'" LOG_

			usebackend->accept(*&fOp);
			_LOG << "Load system database backend flag: '" << usebackend->charrep() << "'" LOG_
			_use_application_database_backend = usebackend->getData();
			usebackend->accept(*&fOp);
			_LOG << "Load application database backend flag: '" << usebackend->charrep() << "'" LOG_
			_use_system_database_backend = usebackend->getData();
*/
#endif //OLD_TIGHT_DEPENDENCY	

			fOp->end();

			_loaded = true;

			return ERR_NONE;
		} else {
			_LOG << "lb_MetaApplication::load() Error: Could not get lb_I_FileOperation plugin !" LOG_
		}
	} else {
		_LOGERROR << "Error: Could not load stream operator classes!" LOG_
	}
	return ERR_FILE_READ;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_MetaApplication::setData() has not been implemented" LOG_

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getUserName\40\lb_I_String\42\\42\ user\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getUserName(lb_I_String** user) {
	if (LogonUser == NULL) (*user)->setData("");
	else (*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getApplicationName\40\lb_I_String\42\\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getApplicationName(lb_I_String** app) {
	if (LogonApplication == NULL) (*app)->setData("");
	else (*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setUserName\40\char\42\ user\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setUserName(const char* user) {
	if (!_loading_object_data)
		if (!_logged_in) {
			_LOG << "Error: Not logged in. Function call not allowed." LOG_
			return ERR_NONE;
		}

	if ((user == NULL) || strcmp(user, "") == 0) {
		_LOG << "Error: Setting empty user name not allowed." LOG_
		return ERR_NONE;
	}

	if (LogonUser == NULL) {
        	REQUEST(getModuleInstance(), lb_I_String, LogonUser)
	}

	LogonUser->setData(user);
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setApplicationName\40\char\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setApplicationName(const char* app) {
	if ((app == NULL) || strcmp(app, "") == 0) return ERR_NONE;

	if (LogonApplication == NULL) {
        	REQUEST(getModuleInstance(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager \42\ lb_MetaApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager * lb_MetaApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\Initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
/// \todo Implement autologon settings for last user.
lbErrCodes LB_STDCALL lb_MetaApplication::initialize(const char* user, const char* appName) {
	lbErrCodes err = ERR_NONE;
/*...sdoc:8:*/
	/**
	* At this point should be found the real application. The real one
	 * may be defined by an environment variable, that is defined out of
	 * a batch file.
	 * The variable contains the name of the application, where a xml tag
	 * resolves the functor for this application.
	 */
/*...e*/

	if (user == NULL) {
		_CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL && _logged_in) {
			REQUEST(getModuleInstance(), lb_I_String, LogonUser)
			LogonUser->setData(user);
		}

	if (appName == NULL) {
		_CL_LOG << "lb_MetaApplication::Initialize() appName is NULL" LOG_
	} else
		if (LogonApplication == NULL) {
			REQUEST(getModuleInstance(), lb_I_String, LogonApplication)
			LogonApplication->setData(appName);
		}


/*...sdispatch integer values:8:*/
	/*
	 * This variable is needed, if this instance also implements a little dispatcher.
	 * It should moved into the class declatation and used in the dispatch functions.
	 */
	int getBasicApplicationInfo;
	int getMainModuleInfo;
	int testPressed;
	int enterDebugger;
	int _getLoginData;
	int doAutoload;
	int doLog;
/*...e*/

/*...sget the event manager:8:*/
	/**
		* Registrieren eines Events, der auch auf der GUI Seite bekannt ist.
	 */

/*...e*/

/*...sregister some basic events \40\getBasicApplicationInfo\46\\46\\46\\41\ by the event manager:8:*/
	eman->registerEvent("doAutoload", doAutoload);
	eman->registerEvent("doLog", doLog);
	eman->registerEvent("enterDebugger", enterDebugger);
	eman->registerEvent("getBasicApplicationInfo", getBasicApplicationInfo);
	eman->registerEvent("getMainModuleInfo", getMainModuleInfo);
	eman->registerEvent("Button Test pressed", testPressed);

	if (getenv("TARGET_APPLICATION") == NULL) {
		// Need a database configuration based authentication
		eman->registerEvent("getLoginData", _getLoginData);
	}
/*...e*/

	registerEventHandler(dispatcher.getPtr());

	// Step 3 (Load sub components, handling menus and else needed for an UI)
	loadSubModules();

/*...ssome docs:8:*/
	/**
		* After initializion of all event handlers, we need to get up all
	 * GUI accessible handlers - like menus or else.
	 * This class, as an example, provides two handlers
	 * getBasicApplicationInfo and getMainModuleInfo
	 *
	 * The handler depends on some capabilities:
	 *
	 * 	1. A basic dialog to show text
	 *		This may be a container of capabilities
	 *		 must:SimpleTextDialog
	 *		 optional:PictureElements
	 *
	 * It provides these capabilities:
	 *
	 *	1. An information about menu creation
	 *		This may be a simple string - lb_I_String
	 */


	/**
		* Init the application (menu, toolbar, accelerators)
	 *
	 * This will be done by the loaded application from the
	 * environment variable (TARGET_APPLICATION)
	 */
/*...e*/

	addMenuBar(_trans("&Edit"));

	UAP_REQUEST(getModuleInstance(), lb_I_String, translated)

	*translated = _trans("&Autoload application");
	addMenuEntryCheckable(_trans("&Edit"), translated->charrep(), "doAutoload", "");
	*translated = _trans("Log to logfile");
	addMenuEntryCheckable(_trans("&File"), translated->charrep(), "doLog", "");

	if (getenv("TARGET_APPLICATION") != NULL) {
		loadApplication("", "");
	}

	addMenuBar(_trans("&Help"));

	if (getenv("TARGET_APPLICATION") == NULL) {
		const char* temp = _trans("&Login\tCtrl-L");
		char* login = (char*) malloc(strlen(temp)+1);
		login[0] = 0;
		strcpy(login, temp);

		addMenuEntry(_trans("&File"), login, "getLoginData", "");
		free(login);
	}

	const char* temp = _trans("MainModule&Info\tCtrl-I");

	char* mm = (char*) malloc(strlen(temp)+1);
	mm[0] = 0;
	strcpy(mm, temp);

	addMenuEntry(_trans("&Help"), mm, "getMainModuleInfo", "");
	free(mm);

	_CL_LOG << "Load properties from file..." LOG_

	REQUEST(getModuleInstance(), lb_I_Parameter, myProperties)


	if (!_loaded) {
		if (load() != ERR_NONE) {
			_LOG << "ERROR: Could not load file for MetaApplication data. Save a default file !" LOG_
			if (save() != ERR_NONE) {
				_LOG << "ERROR: Could not save a default file for MetaApplication data!" LOG_
			}
		}
	}

	addToolBar("Main Toolbar");

	addStatusBar();
	addStatusBar_TextArea("Info");

	/*

	   Here it would be the best to get user accounts into the new account list.
	   Having no database and no previously retrieved data from file would lead
	   into not loading the last application for the last user.

	   Really, it then would be invalid data in the last logged in user.

	   Changed user data leads to a reread from the database for these user accounts.
	   Thus, the database has higher priority. This is because other users may have
	   changed their passwords.

	   Changing the data for the logged in user is a special case, where the changed
	   data must be written back to the database.
	*/

	if (getAutoload() && (LogonUser != NULL) && (LogonApplication != NULL)) {
		if ((strcmp(LogonUser->charrep(), "") != 0) && (strcmp(LogonApplication->charrep(), "") != 0)) {
			_CL_LOG << "Autoload is active and have " << LogonApplication->charrep() <<
			" and " << LogonUser->charrep() << ". Loading..." LOG_

			/* loadApplication() does not know, that the parameters are from it self.
			Thus LogonApplication->setData(...) and LogonUser->setData(...) would
			delete it's content.

			This is tricky.
			*/

			char* a = strdup(LogonApplication->charrep());
			char* u = strdup(LogonUser->charrep());

			_logged_in = true;

			setStatusText("Info", "Loading application ...");

			_LOG << "Using database backend name '" << getSystemDatabaseBackend() << "'." LOG_

			//loadApplication(u, a);
			getLoginData(NULL);

			_LOG << "Used database backend name '" << getSystemDatabaseBackend() << "'." LOG_

			setStatusText("Info", "Loading application done.");

			free(a);
			free(u);

		} else {
			UAP(lb_I_Parameter, params)
			params = getParameter();
			showPropertyPanel(*&params);
		}
	}

	if (!getAutoload()) {
		UAP(lb_I_Parameter, params)
		params = getParameter();
		showPropertyPanel(*&params);
	}

	addToolBarButton("Main Toolbar", "Properties", "ShowPropertyPanel", "configure.png");


	if (getAutoload())
		toggleEvent("doAutoload");

	if (isLogActivated())
		toggleEvent("doLog");

	_loading_object_data = false;

	_CL_LOG << "Loaded properties from file." LOG_

	return ERR_NONE;
}
/*...e*/

void                    LB_STDCALL lb_MetaApplication::setPropertyPaneLayoutFloating() {

}

void                    LB_STDCALL lb_MetaApplication::setPropertyPaneLayoutLeft() {

}

bool                    LB_STDCALL lb_MetaApplication::isPropertyPaneLayoutFloating() {
	return isPropertyPanelFloating;
}

bool                    LB_STDCALL lb_MetaApplication::isPropertyPaneLayoutLeft() {
	return isPropertyPanelLeft;
}

void                    LB_STDCALL lb_MetaApplication::showPropertyPanel() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, s)


	UAP(lb_I_Unknown, uk)
	QI(s, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("ShowPropertyPanel", uk.getPtr(), &uk_result);
}

void	   LB_STDCALL lb_MetaApplication::setGUIMaximized(bool b) {
	_GUIMaximized = b;
}

bool	   LB_STDCALL lb_MetaApplication::getGUIMaximized() {
	return _GUIMaximized;
}

void       LB_STDCALL lb_MetaApplication::setAutoload(bool b) {
	_autoload = b;
}

void       LB_STDCALL lb_MetaApplication::setDirLocation(const char* dirloc) {
	if (_dirloc != NULL) free(_dirloc);
	_dirloc = strdup(dirloc);
}

void       LB_STDCALL lb_MetaApplication::setAutorefreshData(bool b) {
	_autorefresh = b;
}


void       LB_STDCALL lb_MetaApplication::setAutoselect(bool b) {
	_autoselect = b;
}

void       LB_STDCALL lb_MetaApplication::setLoadFromDatabase(bool b) {
	_force_use_database = b;
}

bool       LB_STDCALL lb_MetaApplication::getLoadFromDatabase() {
	return _force_use_database;
}

bool       LB_STDCALL lb_MetaApplication::getAutoload() {
	return _autoload;
}

char*       LB_STDCALL lb_MetaApplication::getDirLocation() {
	return _dirloc;
}

bool       LB_STDCALL lb_MetaApplication::getAutorefreshData() {
	return _autorefresh;
}

bool       LB_STDCALL lb_MetaApplication::getAutoselect() {
	return _autoselect;
}

char*		LB_STDCALL lb_MetaApplication::getSystemDatabaseBackend() {
	UAP_REQUEST(getModuleInstance(), lb_I_String, Backend)
	*Backend = _system_database_backend;
	Backend->trim(); // Always trim spaces.
	setSystemDatabaseBackend(Backend->charrep());
	if (_use_system_database_backend) return _system_database_backend;
	return (char*) "";
}

char*		LB_STDCALL lb_MetaApplication::getApplicationDatabaseBackend() {
	UAP_REQUEST(getModuleInstance(), lb_I_String, Backend)
	*Backend = _application_database_backend;
	Backend->trim(); // Always trim spaces.
	setApplicationDatabaseBackend(Backend->charrep());

	if (_use_application_database_backend) return _application_database_backend;
	return (char*) "";
}

void		LB_STDCALL lb_MetaApplication::setSystemDatabaseBackend(const char* backend) {
	if (_system_database_backend) free(_system_database_backend);
	UAP_REQUEST(getModuleInstance(), lb_I_String, Backend)
	*Backend = backend;
	Backend->trim();
	_system_database_backend = strdup(Backend->charrep());
}

void		LB_STDCALL lb_MetaApplication::setApplicationDatabaseBackend(const char* backend) {
	if (_application_database_backend) free(_application_database_backend);
	UAP_REQUEST(getModuleInstance(), lb_I_String, Backend)
	*Backend = backend;
	Backend->trim();
 	_application_database_backend = strdup(Backend->charrep());
}

void LB_STDCALL lb_MetaApplication::useSystemDatabaseBackend(bool backend) {
	_use_system_database_backend = backend;
}

void LB_STDCALL lb_MetaApplication::useApplicationDatabaseBackend(bool backend) {
	_use_application_database_backend = backend;
}

bool LB_STDCALL lb_MetaApplication::usingSystemDatabaseBackend() {
	return _use_system_database_backend;
}

bool LB_STDCALL lb_MetaApplication::usingApplicationDatabaseBackend() {
	return _use_application_database_backend;
}


/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\propertyChanged\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::propertyChanged(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)

	if (param != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, parameterName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)

		UAP(lb_I_KeyBase, key)

		name->setData("name");
		param->getUAPString(*&name, *&parameterName);

		name->setData("value");
		param->getUAPString(*&name, *&value);

		QI(parameterName, lb_I_KeyBase, key)

		if (strcmp(key->charrep(), "GeneralBase directory") == 0) {
					setDirLocation(value->charrep());
		}

		if (strcmp(key->charrep(), "GeneralSystem Database backend") == 0) {
					if (_system_database_backend != NULL) free(_system_database_backend);
					_system_database_backend = strdup(value->charrep());
		}


		if (strcmp(key->charrep(), "GeneralApplication Database backend") == 0) {
					if (_application_database_backend != NULL) free(_application_database_backend);
					_application_database_backend = strdup(value->charrep());
		}

		if (strcmp(key->charrep(), "GeneralAutorefresh updated data") == 0) {
				value->toLower();
				if (strcmp(value->charrep(), "true") == 0) {
					setAutorefreshData(true);
				} else {
					setAutorefreshData(false);
				}
		}

		if (strcmp(key->charrep(), "GeneralAutoopen last application") == 0) {
				value->toLower();
				if (strcmp(value->charrep(), "true") == 0) {
					setAutoload(true);
				} else {
					setAutoload(false);
				}
				toggleEvent("doAutoload");
		}

		if (strcmp(key->charrep(), "GeneralUse system Database backend") == 0) {
				value->toLower();
				if (strcmp(value->charrep(), "true") == 0) {
					_use_system_database_backend = true;
				} else {
					_use_system_database_backend = false;
				}
		}

		if (strcmp(key->charrep(), "GeneralUse application Database backend") == 0) {
				value->toLower();
				if (strcmp(value->charrep(), "true") == 0) {
					_use_application_database_backend = true;
				} else {
					_use_application_database_backend = false;
				}
		}

		if (strcmp(key->charrep(), "GeneralPrefer database configuration") == 0) {
				value->toLower();
				if (strcmp(value->charrep(), "true") == 0) {
					_force_use_database = true;
				} else {
					_force_use_database = false;
				}
		}

		if (strcmp(key->charrep(), "GeneralLast application") == 0) {
			setApplicationName(value->charrep());
		}

		_LOG << "User has changed a property for meta application: " << key->charrep() << " = " << value->charrep() LOG_
	} else {
		_LOG << "ERROR: Could not decode parameter structure!" LOG_
	}

	return err;
}
/*...e*/

/*...slb_I_Parameter\42\ LB_STDCALL lb_MetaApplication\58\\58\getParameter\40\\41\:0:*/
lb_I_Parameter* LB_STDCALL lb_MetaApplication::getParameter() {
	// Build up a preferences object and pass it to the property view
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)

	// General parameters for this application
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramGeneral)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameterGeneral)
	UAP_REQUEST(getModuleInstance(), lb_I_String, valueGeneral)

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dirloc)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)


	parameter->setData("General");
	//--------------------------------------------------------
	parameterGeneral->setData("Base directory");
	dirloc->setData(_dirloc);
	paramGeneral->setUAPDirLocation(*&parameterGeneral, *&dirloc);

	parameterGeneral->setData("Autoselect last application");
	b->setData(_autoselect);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	parameterGeneral->setData("Autorefresh updated data");
	b->setData(_autorefresh);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	parameterGeneral->setData("Autoopen last application");
	b->setData(_autoload);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	parameterGeneral->setData("Prefer database configuration");
	b->setData(_force_use_database);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	parameterGeneral->setData("Application Database backend");
	*value = _application_database_backend;
	paramGeneral->setUAPString(*&parameterGeneral, *&value);

	parameterGeneral->setData("System Database backend");
	*value = _system_database_backend;
	paramGeneral->setUAPString(*&parameterGeneral, *&value);

	parameterGeneral->setData("Use application Database backend");
	b->setData(_use_application_database_backend);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	parameterGeneral->setData("Use system Database backend");
	b->setData(_use_system_database_backend);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	_LOG << "lb_MetaApplication::getParameter() returns as Application Database backend: " << _application_database_backend LOG_
	_LOG << "lb_MetaApplication::getParameter() returns as System Database backend: " << _system_database_backend LOG_

	registerPropertyChangeEventGroup(parameter->charrep(), *&paramGeneral, this, (lbEvHandler) &lb_MetaApplication::propertyChanged);

	param->setUAPParameter(*&parameter, *&paramGeneral);
	//--------------------------------------------------------
	param++;

	return param.getPtr();
}
/*...e*/

// This starts the main application

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);
#endif
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::loadSubModules() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::unloadApplication() {
#ifdef OLD_TIGHT_DEPENDENCY	
	if (User_Applications != NULL) {
			_LOG << "lb_MetaApplication::unloadApplication() with " << User_Applications->getRefCount() << " instances." LOG_
	}
#endif

	if (app != NULL) {
		app->uninitialize(); // Internally saves the active document. Thus do not move this behind the following if block.

		if (activeDocuments != NULL) {
			_LOG << "Manually delete all active documents." LOG_
			activeDocuments->deleteAll();
			_LOG << "Deleted all active documents." LOG_
		}

		app--;
		app.resetPtr();
	}

	uninitLocale();
	_CL_LOG << "lb_MetaApplication::unloadApplication() ready." LOG_
	return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\loadApplication\40\char\42\ user\44\ char\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::loadApplication(const char* user, const char* application) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	
	_LOG << "lb_MetaApplication::loadApplication('" << ((user == NULL) ? "NULL" : user) << "', '" << ((application == NULL) ? "NULL" : application) << "') called" LOG_
	
#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif

	if (user == NULL) {
		_CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL) {
			REQUEST(getModuleInstance(), lb_I_String, LogonUser)
		}

	LogonUser->setData(user);

	if (application == NULL) {
		_CL_LOG << "lb_MetaApplication::Initialize() app is NULL" LOG_
	} else
        if (LogonApplication == NULL) {
			REQUEST(getModuleInstance(), lb_I_String, LogonApplication)
        }

	LogonApplication->setData(application);

	char* applicationName = getenv("TARGET_APPLICATION");

	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	if (applicationName == NULL) {
		/*
		 * No predefined application without authentication.
		 * Read the configuration from a database.
		 */
		_LOG << "lb_MetaApplication::loadApplication() loads an application over parameters: " << ((application == NULL) ? "NULL" : application) LOG_

			// Also the application requires an authenticated user
		UAP(lb_I_SecurityProvider, securityManager)
		AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")
		
		UAP(lb_I_String, ModuleName)
		UAP(lb_I_String, Functor)
		
		UAP(lb_I_Container, apps)
		apps = securityManager->getApplications();
		
		apps->finishIteration();
		while (apps->hasMoreElements() == 1)
		{
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_String, appName)
			uk = apps->nextElement();
			QI(uk, lb_I_String, appName)
			if (*appName == application)
			{
				UAP(lb_I_Long, id)
				UAP(lb_I_KeyBase, key)
				key = apps->currentKey();
				QI(key, lb_I_Long, id)
				securityManager->setCurrentApplicationId(id->getData());
				break;
			}
		}
		
		ModuleName = securityManager->getApplicationModule();
		Functor = securityManager->getApplicationFunctor();

		applicationName = (char*) malloc(strlen(ModuleName->charrep())+1);
		applicationName[0] = 0;
		strcpy(applicationName, ModuleName->charrep());

		char f[100] = "";
		char appl[100] = "";
		UAP(lb_I_Unknown, a)

		strcpy(f, PREFIX);
		strcat(f, Functor->charrep());
		strcpy(appl, applicationName);


#ifdef WINDOWS
		getModuleInstance()->preload(appl);
		getModuleInstance()->makeInstance(f, appl, &a);
#endif
#ifdef LINUX
		strcat(appl, ".so");
		getModuleInstance()->preload(appl);
		getModuleInstance()->makeInstance(f, appl, &a);
#endif

		if (a == NULL) {
			_CL_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
			return ERR_NONE;
		}

		if (moduleName == NULL) {
			moduleName = (char*) malloc(strlen(appl)+1);
			moduleName[0] = 0;
			strcpy(moduleName, appl);
		} else {
			_CL_LOG << "ERROR: Multiple applications not yet supported." LOG_
		}

		QI(a, lb_I_Application, app)

			//if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

		app->setGUI(gui);
		app->initialize(user, application);

		// Setting currently loaded application here, because it may be overwritten by app->initialize() when set prior that call.
		LogonApplication->setData(application);
		free(applicationName);
		
#ifdef OLD_TIGHT_DEPENDENCY	
		if (Applications->getApplicationCount() != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, ModuleName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, Functor)

			Users->selectAccount(LogonUser->charrep());
			Applications->selectApplication(LogonApplication->charrep());

			long uid = Users->getUserID();
			long aid = Applications->getApplicationID();

			User_Applications->finishRelationIteration();
			while (User_Applications->hasMoreRelations()) {
				User_Applications->setNextRelation();

				if ((User_Applications->getUserID() == uid) && (User_Applications->getApplicationID() == aid)) {
					break;
				}
			}
			User_Applications->finishRelationIteration();
			Applications->finishApplicationIteration();
			Users->finishUserIteration();

					*ModuleName = Applications->getApplicationModule();
					*Functor = Applications->getApplicationFunctor();

					applicationName = (char*) malloc(strlen(ModuleName->charrep())+1);
					applicationName[0] = 0;
					strcpy(applicationName, ModuleName->charrep());

					char f[100] = "";
					char appl[100] = "";
					UAP(lb_I_Unknown, a)

						strcpy(f, PREFIX);
					strcat(f, Functor->charrep());
					strcpy(appl, applicationName);


#ifdef WINDOWS
					getModuleInstance()->preload(appl);
					getModuleInstance()->makeInstance(f, appl, &a);
#endif
#ifdef LINUX
					strcat(appl, ".so");
					getModuleInstance()->preload(appl);
					getModuleInstance()->makeInstance(f, appl, &a);
#endif

					if (a == NULL) {
						_CL_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
						return ERR_NONE;
					}

					if (moduleName == NULL) {
						moduleName = (char*) malloc(strlen(appl)+1);
						moduleName[0] = 0;
						strcpy(moduleName, appl);
					} else {
						_CL_LOG << "ERROR: Multiple applications not yet supported." LOG_
					}

					QI(a, lb_I_Application, app)

						//if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

					app->setGUI(gui);
					app->initialize(user, application);

					// Setting currently loaded application here, because it may be overwritten by app->initialize() when set prior that call.
					LogonApplication->setData(application);
					free(applicationName);

		} else {
			UAP(lb_I_Database, database)

			char* dbbackend = getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "lb_MetaApplication::isAnyDatabaseAvailable() Using plugin database backend for system database setup test..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "lb_MetaApplication::isAnyDatabaseAvailable() Using built in database backend for system database setup test..." LOG_
			}

			UAP(lb_I_Query, sampleQuery)

			database->init();

			if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
				_LOG << "Error: Connection to database failed." LOG_
				UAP(lb_I_Parameter, params)
				params = getParameter();
				showPropertyPanel(*&params);
				// Mac OS X hangs because wxWidgets manin frame isn't initialized yet.
				//msgBox("Error", _trans("Could not login to system database."));
				return ERR_NONE;
			} else {

				sampleQuery = database->getQuery("lbDMF", 0);

				char* buffer = (char*) malloc(1000);
				buffer[0] = 0;

				sprintf(buffer,
						"select Anwendungen.modulename, Anwendungen.functor, Anwendungen.interface from Anwendungen inner join User_Anwendungen on "
						"Anwendungen.id = User_Anwendungen.anwendungenid "
						"inner join Users on User_Anwendungen.userid = Users.id where "
						"Users.userid = '%s' and Anwendungen.name = '%s'"
						, LogonUser->charrep(), LogonApplication->charrep());

				printf("%s\n", buffer);

				/*
				 * Decide upon the interface, if this code is capable to handle this application.
				 * First, only handle lb_I_MetaApplication types.
				 */

				sampleQuery->skipFKCollecting();
				sampleQuery->query(buffer);
				sampleQuery->enableFKCollecting();


				// Fill up the available applications for that user.
				UAP_REQUEST(getModuleInstance(), lb_I_String, ModuleName)
				UAP_REQUEST(getModuleInstance(), lb_I_String, Functor)

					lbErrCodes DBerr = sampleQuery->first();

				if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
					ModuleName = sampleQuery->getAsString(1);
					Functor = sampleQuery->getAsString(2);

					applicationName = (char*) malloc(strlen(ModuleName->charrep())+1);
					applicationName[0] = 0;
					strcpy(applicationName, ModuleName->charrep());

#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif

					char f[100] = "";
					char appl[100] = "";
					UAP(lb_I_Unknown, a)

						strcpy(f, PREFIX);
					strcat(f, Functor->charrep());
					strcpy(appl, applicationName);


#ifdef WINDOWS
					getModuleInstance()->preload(appl);
					getModuleInstance()->makeInstance(f, appl, &a);
#endif
#ifdef LINUX
					strcat(appl, ".so");
					getModuleInstance()->preload(appl);
					getModuleInstance()->makeInstance(f, appl, &a);
#endif

					if (a == NULL) {
						_CL_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
						return ERR_NONE;
					}

					if (moduleName == NULL) {
						moduleName = (char*) malloc(strlen(appl)+1);
						moduleName[0] = 0;
						strcpy(moduleName, appl);
					} else {
						_CL_LOG << "ERROR: Multiple applications not yet supported." LOG_
					}

					QI(a, lb_I_Application, app)

						//if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

						app->setGUI(gui);
					app->initialize(user, application);

					// Setting currently loaded application here, because it may be overwritten by app->initialize() when set prior that call.
					LogonApplication->setData(application);
					free(applicationName);
				} else {
					_LOG << "Error: Query to get application data failed. '" << buffer << "'" LOG_
				}
				free(buffer);
			}
		}
		//if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher has been set to NULL" LOG_
#endif		
	} else {
		_LOG << "lb_MetaApplication::loadApplication() loads an application over the environmemt: " << applicationName LOG_

		UAP(lb_I_Unknown, a)

#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif


#ifdef WINDOWS
		getModuleInstance()->preload(applicationName);
		getModuleInstance()->makeInstance(PREFIX "instanceOfApplication", applicationName, &a);
#endif
#ifdef LINUX
		char name[80] = "";
		strcpy(name, applicationName);
		strcat(name, ".so");
		getModuleInstance()->preload(name);
		getModuleInstance()->makeInstance(PREFIX "instanceOfApplication", name, &a);
#endif
		if (a == NULL) {
			_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
			return ERR_NONE;
		}

		QI(a, lb_I_Application, app)

		if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

		app->setGUI(gui);
		app->initialize();
		// Setting currently loaded application here, because it may be overwritten by app->initialize() when set prior that call.
		LogonApplication->setData(application);

		_CL_LOG << "Meta application has " << app->getRefCount() << " references." LOG_

		if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher has been set to NULL" LOG_
	}

        return ERR_NONE;
}
/*...e*/

/*...sBasic functions to be used for a UI application:0:*/

lbErrCodes LB_STDCALL lb_MetaApplication::removeToolBar(const char* toolbarName)	{
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	parameter->setData("toolbarName");
	value->setData(toolbarName);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("removeToolBar", uk.getPtr(), &uk_result);

	return err;
}

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addToolBar\40\char\42\ toolbarName\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addToolBar(const char* toolbarName)	{
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	parameter->setData("toolbarName");
	value->setData(toolbarName);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("addToolBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::addToolBarButton(const char* toolbarName, const char* entry, const char* evHandler, const char* toolbarimage, const char* afterentry) {
	return addToolBarTool(toolbarName, "Button", entry, evHandler, toolbarimage, afterentry);
}

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addToolBarTool\40\char\42\ toolbarName\44\ char\42\ tooltype\44\ char\42\ entry\44\ char\42\ evHandler\44\ char\42\ toolbarimage\44\ char\42\ afterentry\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addToolBarTool(const char* toolbarName, const char* tooltype, const char* entry, const char* evHandler, const char* toolbarimage, const char* afterentry) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	parameter->setData("toolbarName");
	value->setData(toolbarName);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("tooltype");
	value->setData(tooltype);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("entry");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("evHandler");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("toolbarimage");
	value->setData(toolbarimage);
	param->setUAPString(*&parameter, *&value);

	if (afterentry != NULL) {
		parameter->setData("afterentry");
		value->setData(afterentry);
		param->setUAPString(*&parameter, *&value);
	}

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("addTool_To_ToolBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\removeToolBarButton\40\char\42\ toolbarName\44\ char\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::removeToolBarButton(const char* toolbarName, const char* entry) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	parameter->setData("toolbarName");
	value->setData(toolbarName);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("entry");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("removeTool_From_ToolBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\toggleToolBarButton\40\char\42\ toolbarName\44\ char\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::toggleToolBarButton(const char* toolbarName, const char* entry) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	parameter->setData("toolbarName");
	value->setData(toolbarName);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("entry");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("toggleTool_From_ToolBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addMenuBar\40\char\42\ name\44\ char\42\ after\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuBar(const char* name, const char* after) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	parameter->setData("name");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	if (after != NULL) {
		parameter->setData("after");
		value->setData(after);
		param->setUAPString(*&parameter, *&value);

	}


	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddMenuBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addMenu\40\char\42\ name\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenu(const char* name) {
	return ERR_NONE;
}
/*...e*/
/*...slb_MetaApplication\58\\58\addTextField\40\char\42\ name\44\ int x\44\ int y\44\ int w\44\ int h\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addTextField(const char* name, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

        parameter->setData("text");
        value->setData(name);
        param->setUAPString(*&parameter, *&value);

        parameter->setData("x");
        i->setData(x);
        param->setUAPInteger(*&parameter, *&i);

        parameter->setData("y");
        i->setData(y);
        param->setUAPInteger(*&parameter, *&i);

        parameter->setData("w");
        i->setData(w);
        param->setUAPInteger(*&parameter, *&i);

        parameter->setData("h");
        i->setData(h);
        param->setUAPInteger(*&parameter, *&i);

        UAP(lb_I_Unknown, uk)
        QI(param, lb_I_Unknown, uk)

        UAP_REQUEST(getModuleInstance(), lb_I_String, result)
        UAP(lb_I_Unknown, uk_result)
        QI(result, lb_I_Unknown, uk_result)

        dispatcher->dispatch("AddTextField", uk.getPtr(), &uk_result);

        return err;
}
/*...e*/
/*...sbool LB_STDCALL lb_MetaApplication\58\\58\askYesNo\40\char\42\ msg\41\:0:*/
bool LB_STDCALL lb_MetaApplication::askYesNo(const char* msg) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)


	parameter->setData("msg");
	value->setData(msg);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	if (dispatcher == NULL) {
		REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		dispatcher->setEventManager(eman.getPtr());
	}

	printf("AskYesNo gets called. Handler data is: %p\n", uk.getPtr());

	dispatcher->dispatch("askYesNo", uk.getPtr(), &uk_result);

	// Got a name of the file. Create an input stream.

	parameter->setData("result");
	param->getUAPString(*&parameter, *&value);

	if (strcmp(value->charrep(), "yes") == 0) return true;
	return false;
}
/*...e*/

/*...svoid LB_STDCALL lb_MetaApplication\58\\58\addStatusBar\40\\41\:0:*/
void LB_STDCALL lb_MetaApplication::addStatusBar() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("addStatusBar", uk.getPtr(), &uk_result);
}
/*...e*/
/*...svoid LB_STDCALL lb_MetaApplication\58\\58\addStatusBar_TextArea\40\char\42\ name\41\:0:*/
void LB_STDCALL lb_MetaApplication::addStatusBar_TextArea(const char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Value)

	*parameter = "Name";
	*Value = name;
	param->setUAPString(*&parameter, *&Value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("addStatusBar_TextArea", uk.getPtr(), &uk_result);
}
/*...e*/
/*...svoid LB_STDCALL lb_MetaApplication\58\\58\setStatusText\40\char\42\ name\44\ char\42\ value\41\:0:*/
void LB_STDCALL lb_MetaApplication::setStatusText(const char* name, const char* value, bool call_yield) {
	lbErrCodes err = ERR_NONE;

	if (!isStatusbarActive) return;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Value)

	*parameter = "Name";
	*Value = name;
	param->setUAPString(*&parameter, *&Value);
	*parameter = "Value";
	*Value = value;
	param->setUAPString(*&parameter, *&Value);
	*parameter = "CallYield";
	*Value = (call_yield) ? "true" : "false";
	param->setUAPString(*&parameter, *&Value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	if (dispatcher != NULL) dispatcher->dispatch("setStatusText", uk.getPtr(), &uk_result);
}
/*...e*/

/*...svoid LB_STDCALL lb_MetaApplication\58\\58\msgBox\40\char\42\ title\44\ char\42\ msg\41\:0:*/
void LB_STDCALL lb_MetaApplication::msgBox(const char* title, const char* msg) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

	parameter->setData("msg");
	value->setData(msg);
	param->setUAPString(*&parameter, *&value);
	parameter->setData("title");
	value->setData(title);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("showMsgBox", uk.getPtr(), &uk_result);
}
/*...e*/

/*...slb_I_InputStream\42\ LB_STDCALL lb_MetaApplication\58\\58\askOpenFileReadStream\40\char\42\ extensions\41\:0:*/
lb_I_InputStream* LB_STDCALL lb_MetaApplication::askOpenFileReadStream(const char* extensions) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

	parameter->setData("extension");
	value->setData(extensions);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("askOpenFileReadStream", uk.getPtr(), &uk_result);

	// Got a name of the file. Create an input stream.

	parameter->setData("result");
	param->getUAPString(*&parameter, *&value);

	if (strcmp(value->charrep(), "") == 0) return NULL;

	_LOG << "Got a file name: " << value->charrep() << "." LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_InputStream, s)
	s++;
	s->setFileName(value->charrep());

	return s.getPtr();
}
/*...e*/


/*...slb_MetaApplication\58\\58\addLabel\40\char\42\ text\44\ int x\44\ int y\44\ int w\44\ int h\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addLabel(const char* text, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)


	parameter->setData("labeltext");
	value->setData(text);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("x");
	i->setData(x);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("y");
	i->setData(y);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("w");
	i->setData(w);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("h");
	i->setData(h);
	param->setUAPInteger(*&parameter, *&i);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddLabel", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

/*...slb_MetaApplication\58\\58\addButton\40\char\42\ buttonText\44\ char\42\ evHandler\44\ int x\44\ int y\44\ int w\44\ int h\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)


	parameter->setData("buttontext");
	value->setData(buttonText);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("handlername");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("x");
	i->setData(x);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("y");
	i->setData(y);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("w");
	i->setData(w);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("h");
	i->setData(h);
	param->setUAPInteger(*&parameter, *&i);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddButton", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\enableEvent\40\char\42\ name\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::enableEvent(const char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)


	parameter->setData("handlername");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("enableEvent", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\disableEvent\40\char\42\ name\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::disableEvent(const char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)


	parameter->setData("handlername");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("disableEvent", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\toggleEvent\40\char\42\ name\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::toggleEvent(const char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)


	parameter->setData("handlername");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("toggleEvent", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

void LB_STDCALL lb_MetaApplication::fireEvent(const char* name) {
	lbErrCodes err = ERR_NONE;
	int eventID = -1;
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, param)
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

	eman->resolveEvent((const char*) name, eventID);
	dispatcher->setEventManager(eman.getPtr());

	param->setData(eventID);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch(eventID, uk.getPtr(), &uk_result);
}

void LB_STDCALL lb_MetaApplication::firePropertyChangeEvent(const char* name, const char* value) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, evId)

	int PropertyEvent;

	if (eman == NULL) {
		REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	}

	eman->resolveEvent((const char*) name, PropertyEvent);

	Name->setData("eventId");
	evId->setData(PropertyEvent);
	param->setUAPInteger(*&Name, *&evId);

	Name->setData("value");
	Value->setData((const char*) value);
	param->setUAPString(*&Name, *&Value);

	Name->setData("name");
	Value->setData((const char*) name);
	param->setUAPString(*&Name, *&Value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	if (dispatcher == NULL) {
		REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		dispatcher->setEventManager(eman.getPtr());
	}

	dispatcher->dispatch(PropertyEvent, uk.getPtr(), &uk_result);
}

void LB_STDCALL lb_MetaApplication::updatePropertyGroup(lb_I_Container* properties, const char* prefix) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fl)
	UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dl)
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, I)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)


	for (int i = 1; i <= properties->Count(); i++) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)

		uk = properties->getElementAt(i);
		key = properties->getKeyAt(i);

		bool found = false;

		if (prefix && prefix[0] != 0)
			*name = prefix;
		else
			*name = "";


		*name += key->charrep();

		if (strcmp(uk->getClassName(), "lbString") == 0) {
			s->setData(*&uk);
			firePropertyChangeEvent(name->charrep(), s->charrep());
		}
		if (strcmp(uk->getClassName(), "lbDirLocation") == 0) {
			dl->setData(*&uk);
			firePropertyChangeEvent(name->charrep(), dl->charrep());
		}
		if (strcmp(uk->getClassName(), "lbFileLocation") == 0) {
			fl->setData(*&uk);
			firePropertyChangeEvent(name->charrep(), fl->charrep());
		}
		if (strcmp(uk->getClassName(), "lbInteger") == 0) {
			I->setData(*&uk);
			firePropertyChangeEvent(name->charrep(), I->charrep());
		}
		if (strcmp(uk->getClassName(), "lbBoolean") == 0) {
			b->setData(*&uk);
			firePropertyChangeEvent(name->charrep(), b->charrep());
		}
		if (strcmp(uk->getClassName(), "lbParameter") == 0) {
			UAP(lb_I_Container, props)
			UAP(lb_I_Parameter, param)
			QI(uk, lb_I_Parameter, param)

			props = param->getParameterList();

			updatePropertyGroup(*&props, key->charrep());
		}

		if (found == false) {
			_LOG << "No handler for parameter of type " << uk->getClassName() << " found." LOG_
		}
	}
}

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\showPropertyPanel\40\lb_I_Parameter\42\ params\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::showPropertyPanel(lb_I_Parameter* params, bool update) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Unknown, uk)
	QI(params, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("ShowPropertyPanel", uk.getPtr(), &uk_result);

	if (update) {
		// Walk to the properties and fire the change event
		UAP(lb_I_Container, props)
		props = params->getParameterList();

		if (props != NULL) updatePropertyGroup(*&props, "");
	}

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\registerPropertyChangeEventGroup\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::registerPropertyChangeEventGroup(const char* name, lb_I_Parameter* params, lb_I_EventHandler* target, lbEvHandler handler) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Container, properties)

	properties = params->getParameterList();

	int temp;

	for (int i = 1; i <= properties->Count(); i++) {
		UAP(lb_I_KeyBase, key)
		UAP_REQUEST(getModuleInstance(), lb_I_String, eventName)

		key = properties->getKeyAt(i);

		*eventName = name;
		*eventName += key->charrep();

		eman->registerEvent(eventName->charrep(), temp);
		dispatcher->addEventHandlerFn(target, handler, eventName->charrep());
	}

	return err;
}
/*...e*/


/*...slb_MetaApplication\58\\58\addMenuEntry\40\char\42\ in_menu\44\ char\42\ entry\44\ char\42\ evHandler\44\ char\42\ afterentry\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuEntry(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)


	parameter->setData("menubar");
	value->setData(in_menu);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("menuname");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("handlername");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);

	if (afterentry && (strcmp(afterentry, "") != 0)) {
		parameter->setData("after");
		value->setData(afterentry);
		param->setUAPString(*&parameter, *&value);
	}

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddMenuEntry", uk.getPtr(), &uk_result);


	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addMenuEntryCheckable\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuEntryCheckable(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)


	parameter->setData("menubar");
	value->setData(in_menu);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("menuname");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("handlername");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("checkable");
	value->setData("yes");
	param->setUAPString(*&parameter, *&value);

	if (afterentry && (strcmp(afterentry, "") != 0)) {
		parameter->setData("after");
		value->setData(afterentry);
		param->setUAPString(*&parameter, *&value);
	}

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddMenuEntry", uk.getPtr(), &uk_result);

	return ERR_NONE;
}
/*...e*/
/*...e*/

#ifdef OLD_TIGHT_DEPENDENCY	
long LB_STDCALL lb_MetaApplication::getApplicationID() {
//\todo Implement using new security provider interface.
	if ((_logged_in) && (Applications->getApplicationCount() > 0)) {
		Applications->selectApplication(LogonApplication->charrep());

		return Applications->getApplicationID();
	} else {
		if (!_logged_in) {
			_LOG << "Error: lb_MetaApplication::getApplicationID() returns 0, because user is not logged in." LOG_
		}
		if (Applications->getApplicationCount() <= 0) {
			_LOG << "Error: lb_MetaApplication::getApplicationID() returns 0, because the application count of Applications is 0." LOG_
		}
		return 0;
	}
	_LOGERROR << "Error: lb_MetaApplication::getApplicationID() returns 0, because no security provider was available." LOG_
	return 0;
}
#endif

void			LB_STDCALL lb_MetaApplication::setActiveApplication(const char* name) {

}

lb_I_Unknown*	LB_STDCALL lb_MetaApplication::getActiveDocument() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_KeyBase, key)

	if (LogonApplication == NULL) return NULL;

	QI(LogonApplication, lb_I_KeyBase, key)

	lb_I_Unknown* ukDoc = activeDocuments->getElement(&key);
	if (ukDoc == NULL) _LOG << "Active document for '" << LogonApplication->charrep() << "' not found!" LOG_
	return ukDoc;
}

void			LB_STDCALL lb_MetaApplication::setActiveDocument(lb_I_Unknown* doc) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukDoc)

	ukDoc = doc;

	QI(LogonApplication, lb_I_KeyBase, key)

	if (activeDocuments->exists(&key)) {
		activeDocuments->remove(&key);
	}

	_LOG << "Insert active document for application '" << LogonApplication->charrep() << "'" LOG_

	activeDocuments->insert(&ukDoc, &key);

	_CL_LOG << "Inserted document has " << ukDoc->getRefCount() << " references." LOG_
}

/*...slb_I_Container\42\ LB_STDCALL lb_MetaApplication\58\\58\getApplications\40\\41\:0:*/
#ifdef OLD_TIGHT_DEPENDENCY
lb_I_Container* LB_STDCALL lb_MetaApplication::getApplications() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Container, apps)
	if (Applications->getApplicationCount() == 0) {
		// Maybe no data collected in the file yet
		// Fallback to manually read out the applications

		_LOG << "Info: Have no applications in '" << Applications->getClassName() << "'. Create the list from database." LOG_

		UAP(lb_I_Database, database)

		char* dbbackend = getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "lb_MetaApplication::getApplications() Using plugin database backend for system database setup test..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)

			if (database == NULL) {
				setSystemDatabaseBackend("DatabaseLayerGateway");
				setApplicationDatabaseBackend("DatabaseLayerGateway");
				useSystemDatabaseBackend(true);
				useApplicationDatabaseBackend(true);

				// A second try here
				char* dbbackend = getSystemDatabaseBackend();
				if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
					UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
					AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
					_LOG << "lb_MetaApplication::getApplications() Using plugin database backend for system database setup test..." LOG_
				}
				if (database == NULL) {
					msgBox("Error", "Getting application list failed. Even local database backend failed to load.");
					apps++;
					return apps.getPtr();
				}
			}

			_LOG << "lb_MetaApplication::getApplications() Using built in database backend for system database setup test..." LOG_
		}

		UAP(lb_I_Query, sampleQuery)
		database->init();

		const char* lbDMFPasswd = getenv("lbDMFPasswd");
		const char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		if (err != ERR_NONE) {
			_LOG << "Error: No database connection built up. Could not use database logins." LOG_
			apps++;
			return apps.getPtr();
		}

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)

		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");

		bool hasDBLoaded = false;

		if (pl != NULL) {
			ukPl = pl->getImplementation();

			if (ukPl != NULL) {
				UAP(lb_I_DatabaseOperation, fOp)
				QI(ukPl, lb_I_DatabaseOperation, fOp)

				if (!fOp->begin("lbDMF", database.getPtr())) {
					_LOG << "FATAL: Failed to start reading application list from database!" LOG_
					apps++;
					return apps.getPtr();
				}

				Applications->accept(*&fOp);

				Users->accept(*&fOp);

				User_Applications->accept(*&fOp);

				fOp->end();

				/// \todo Save on demand or at application end.
				// => Save menu entry, or on property changes.
				//save(); // Late save

				while (Applications->hasMoreApplications()) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, name)
					UAP(lb_I_KeyBase, key)
					UAP(lb_I_Unknown, ukName)

					Applications->setNextApplication();

					*name = Applications->getApplicationName();

					QI(name, lb_I_KeyBase, key)
					QI(name, lb_I_Unknown, ukName)

					apps->insert(&ukName, &key);
				}

				Applications->finishApplicationIteration();
				hasDBLoaded = true;
			} else {
				_LOG << "Error: Could not load database stream operator classes!" LOG_
			}
		} else {
			_LOG << "Error: No database stream operation found.!" LOG_
		}

		// A first preload of the applications is ignored yet.

/*...sLoad by direct SQL queries\44\ if all above fails:16:*/
		if (!hasDBLoaded) {
			_LOG << "Info: All streaming operations have been failed. Use database API directly." LOG_
			sampleQuery = database->getQuery("lbDMF", 0);

			char* buffer = (char*) malloc(1000);
			buffer[0] = 0;

			sprintf(buffer,
				"select Anwendungen.name from Anwendungen inner join User_Anwendungen on "
				"Anwendungen.id = User_Anwendungen.anwendungenid "
				"inner join Users on User_Anwendungen.userid = Users.id where "
				"Users.userid = '%s'"
					, LogonUser->charrep());


			sampleQuery->skipFKCollecting();
			sampleQuery->query(buffer);
			sampleQuery->enableFKCollecting();

			free(buffer);

			lbErrCodes err = sampleQuery->first();

/*...sLoop through:40:*/
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

				UAP_REQUEST(getModuleInstance(), lb_I_String, S1)
				UAP(lb_I_KeyBase, key)
				UAP(lb_I_Unknown, uk_S1)

				S1 = sampleQuery->getAsString(1);
				QI(S1, lb_I_KeyBase, key)
				QI(S1, lb_I_Unknown, uk_S1)

				apps->insert(&uk_S1, &key);

				while (err == ERR_NONE) {
					lbErrCodes err = sampleQuery->next();

					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						S1 = sampleQuery->getAsString(1);
						QI(S1, lb_I_KeyBase, key)
						QI(S1, lb_I_Unknown, uk_S1)

						apps->insert(&uk_S1, &key);

						if (err == WARN_DB_NODATA) {
							break;
						}
					}

					if (err == ERR_DB_NODATA) {
					        //box->SetSelection(0);
					        break;
					}
				}

			}
/*...e*/
		}
/*...e*/
	} else {
		if (Users->selectAccount(LogonUser->charrep())) {
			long UID = Users->getUserID();

			User_Applications->finishRelationIteration();

			while (User_Applications->hasMoreRelations()) {
				User_Applications->setNextRelation();
				Applications->selectApplication(User_Applications->getApplicationID());

				_LOG <<	"Check if user '" << Users->getUserName() <<
							"' has rights on application '" << Applications->getApplicationName() << "'. (" << User_Applications->getApplicationID() << ") " <<
							UID << " = " << User_Applications->getUserID() LOG_

				if (User_Applications->getUserID() == UID) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, S1)
					UAP(lb_I_KeyBase, key)
					UAP(lb_I_Unknown, uk_S1)

					*S1 = Applications->getApplicationName();

					QI(S1, lb_I_KeyBase, key)
					QI(S1, lb_I_Unknown, uk_S1)

					apps->insert(&uk_S1, &key);
				}
			}
		} else {
			_LOG << "Error: Logged in user account is not in data model!" LOG_
		}
	}
	apps++;
	return apps.getPtr();
}
#endif
/*...e*/

#ifdef OLD_TIGHT_DEPENDENCY
lb_I_Applications* LB_STDCALL lb_MetaApplication::getApplicationModel() {
	if (Applications == NULL) {
		REQUEST(getModuleInstance(), lb_I_Applications, Applications)
	}

	Applications++;

	return Applications.getPtr();
}
#endif

void LB_STDCALL lb_MetaApplication::delPropertySet(const char* setname) {
	if (propertySets != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, set)
		*set = setname;
		propertySets->delParameter(*&set);
	}
}

void LB_STDCALL lb_MetaApplication::addPropertySet(lb_I_Parameter* properties, const char* setname) {
	if (propertySets == NULL) {
		REQUEST(getModuleInstance(), lb_I_Parameter, propertySets)
	}
	UAP_REQUEST(getModuleInstance(), lb_I_String, set)
	*set = setname;

	propertySets->delParameter(*&set);
	propertySets->setUAPParameter(*&set, properties);
}

lb_I_Parameter*	LB_STDCALL lb_MetaApplication::getPropertySet(const char* setname, bool copy) {
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, p)
		UAP_REQUEST(getModuleInstance(), lb_I_String, set)
		*set = setname;

		if (copy == false) {
			p->setCloning(false);
		}

		if (propertySets != NULL) {
			propertySets->getUAPParameter(*&set, *&p);
			p++;
			return p.getPtr();
		} else {
			return NULL;
		}
}

bool LB_STDCALL lb_MetaApplication::askForDirectory(lb_I_DirLocation* loc) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("askForDirectory", uk.getPtr(), &uk_result);

	// Got a name of the file. Create an input stream.

	parameter->setData("result");
	param->getUAPString(*&parameter, *&value);

	if (strcmp(value->charrep(), "") == 0) return false;

	_LOG << "Got a directory name: " << value->charrep() << "." LOG_

	loc->setData(value->charrep());

	return true;
}

#ifdef OLD_TIGHT_DEPENDENCY
/*...sbool LB_STDCALL lb_MetaApplication\58\\58\login\40\const char\42\ user\44\ const char\42\ pass\41\:0:*/
bool LB_STDCALL lb_MetaApplication::login(const char* user, const char* pass) {
	lbErrCodes err = ERR_NONE;

	if (Users == NULL) {
		_LOG << "Error: Can not login. Have no Users list. Probably first call initialize();" LOG_
		return false;
	}

	if (Users->getUserCount() == 0) {
		// Fallback to database use. This should be moved to a 'service', that would
		// Read out the content's of the database. So the best would be using visitor
		// pattern for this to do.

		UAP(lb_I_Database, database)

		char* dbbackend = getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "lb_MetaApplication::isAnyDatabaseAvailable() Using plugin database backend for system database setup test..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "lb_MetaApplication::isAnyDatabaseAvailable() Using built in database backend for system database setup test..." LOG_
		}

		database->init();

		const char* lbDMFPasswd = getenv("lbDMFPasswd");
		const char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		err = database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		if (err != ERR_NONE) {
			_LOG << "Error: No database connection built up. Could not use database logins." LOG_
			return FALSE;
		}

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)

		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");

		if (pl != NULL) {
			ukPl = pl->getImplementation();

			if (ukPl != NULL) {
				UAP(lb_I_DatabaseOperation, fOp)
				QI(ukPl, lb_I_DatabaseOperation, fOp)

				if (!fOp->begin("lbDMF", database.getPtr())) {
					return false;
				}

				Users->accept(*&fOp);

				fOp->end();
			} else {
				_CL_LOG << "Error: Could not load database stream operator classes!" LOG_
			}
		} else {
			_CL_LOG << "Error: Could not load database stream operator classes!" LOG_
		}

		// A first preload of the user accounts is ignored yet.
		_CL_LOG << "Try selective database login check." LOG_


		UAP(lb_I_Query, sampleQuery)

		sampleQuery = database->getQuery("lbDMF", 0);

		char* buffer = (char*) malloc(1000);
		buffer[0] = 0;

		sampleQuery->skipFKCollecting();
		sprintf(buffer, "select userid, passwort from Users where userid = '%s' and passwort = '%s'",
               	user, pass);

		_CL_VERBOSE << "Query for user " << user LOG_

		if (sampleQuery->query(buffer) != ERR_NONE) {
			sampleQuery->enableFKCollecting();
			free(buffer);
			return FALSE;
		}

		free(buffer);

		sampleQuery->enableFKCollecting();

		err = sampleQuery->first();

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			_logged_in = true;
			return true;
		} else {
			return false;
		}
	} else {
		// We have got users from file

		Users->finishUserIteration();
		while (Users->hasMoreUsers()) {
			Users->setNextUser();

			if ((strcmp(Users->getUserName(), user) == 0) && (strcmp(Users->getUserPassword(), pass) == 0)) {
				_logged_in = true;
				Users->finishUserIteration();
				return true;
			}
		}

		// There may be more users in the database, so try to fetch them and make one retry

		return false;
	}
}
/*...e*/
#endif
/*...e*/
/*...slb_EventMapper:0:*/
lb_EventMapper::lb_EventMapper() {
	
	_CL_LOG << "Instance of lb_I_EventMapper created" LOG_
	_name = NULL;
	_id = 0;
}

lb_EventMapper::~lb_EventMapper() {
	if (_name) free(_name);
}




BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventMapper)
	ADD_INTERFACE(lb_I_EventMapper)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_EventMapper::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_EventMapper::setData() has not been implemented" LOG_

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EventMapper::setEvent(const char* name, lbEvHandler handler) {
	_name = strdup(name);
	return ERR_NONE;
}

char* LB_STDCALL lb_EventMapper::getName() {
	if (_name != NULL) return _name;
	return NULL;
}

int LB_STDCALL lb_EventMapper::getID() {
	return _id;
}

void LB_STDCALL lb_EventMapper::setID(int id) {
	_id = id;
}

/*...e*/

/*...slb_EventManager:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lb_EventManager)
	ADD_INTERFACE(lb_I_EventManager)
END_IMPLEMENT_LB_UNKNOWN()

lb_EventManager::lb_EventManager() {
	maxEvId = 12000;
}

lb_EventManager::~lb_EventManager() {
	_CL_VERBOSE << "lb_EventManager::~lb_EventManager() called." LOG_
}

lbErrCodes LB_STDCALL lb_EventManager::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_EventManager::setData() has not been implemented" LOG_

	return ERR_NONE;
}

/*...slb_EventManager\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_EventManager::registerEvent(const char* EvName, int & EvNr) {
	lbErrCodes err = ERR_NONE;
	int newId = maxEvId + 1;

/*...sInit containers:8:*/
	if (events == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(getModuleInstance(), lb_I_Container, events)

		// For housekeeping
		REQUEST(getModuleInstance(), lb_I_Container, freeIds)

		// The reverse
		REQUEST(getModuleInstance(), lb_I_Container, reverse_events)
	}
/*...e*/

/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(getModuleInstance(), lb_I_String, stringData)
	stringData->setData(EvName);

	UAP(lb_I_KeyBase, sk)
	QI(stringData, lb_I_Unknown, sk)
/*...e*/

/*...sError handling:8:*/
	if (events == NULL) _CL_LOG << "Nullpointer detected (events)!" LOG_
	if (*&sk == NULL) _CL_LOG << "Nullpointer detected (sk)!" LOG_
	if (events->exists(&sk) == 1) {
		_CL_LOG << "lb_EventManager::registerEvent(): Error: Event schon registriert" LOG_
		resolveEvent(EvName, EvNr);
		return ERR_EVENT_EXISTS;
	}
/*...e*/
/*...sdetermine id:8:*/
	if (freeIds->Count() == 0) {
		maxEvId++;
	} else {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)

		key = freeIds->getKeyAt(freeIds->Count());
		uk = freeIds->getElementAt(freeIds->Count());

		freeIds->remove(&key);

		UAP(lb_I_Integer, i)
		QI(uk, lb_I_Integer, i)

		newId = i->getData();
	}
/*...e*/
/*...sinsert new event:8:*/
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, integerData)
	integerData->setData(maxEvId);

	UAP(lb_I_Unknown, idata)
	QI(integerData, lb_I_Unknown, idata)

	events->insert(&idata, &sk);

	UAP(lb_I_KeyBase, ik)
	QI(integerData, lb_I_Unknown, ik)

	UAP(lb_I_Unknown, sdata)
	QI(stringData, lb_I_Unknown, sdata)

	reverse_events->insert(&sdata, &ik);

	EvNr = maxEvId;
/*...e*/

	if (events->exists(&sk) != 1) {
		_CL_LOG << "lb_EventManager::registerEvent(): Error: Event could not be registered" LOG_
		return ERR_EVENT_NOTREGISTERED;
	}

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_EventManager::resolveEvent(const char* EvName, int & evNr) {
	lbErrCodes err = ERR_NONE;

/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(getModuleInstance(), lb_I_String, stringKey)
	stringKey->setData(EvName);

	UAP(lb_I_KeyBase, kk)
	QI(stringKey, lb_I_Unknown, kk)
/*...e*/

	if (events == NULL) {
		_CL_VERBOSE << "Error: No events registered yet, thus event name not found: " << EvName LOG_
		return ERR_EVENT_NOTREGISTERED;
	}

/*...sresolve event:8:*/
	if (events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object)
		UAP(lb_I_Integer, i)

		object = events->getElement(&kk);
		QI(object, lb_I_Integer, i)
		evNr = i->getData();
	} else {
		_CL_VERBOSE << "Error: Event name not registered: " << EvName LOG_
		return ERR_EVENT_NOTREGISTERED;
	}
/*...e*/

	return ERR_NONE;
}

char* LB_STDCALL lb_EventManager::reverseEvent(int evNr) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Integer, ID)
	ID->setData(evNr);

	UAP(lb_I_KeyBase, kk)
	QI(ID, lb_I_Unknown, kk)

	if (reverse_events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object)
		UAP(lb_I_String, str)

		object = reverse_events->getElement(&kk);
		QI(object, lb_I_String, str)
		/// \todo Change to a dynamically allocated version that can grow on demand.
		static char result[100] = "";
		strcpy(result, str->getData());

		return result;
	} else {
		_CL_LOG << "Error: Event id not registered: " << evNr LOG_
		return (char*) "";
	}
}
/*...e*/
/*...slb_Dispatcher:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lb_Dispatcher)
	ADD_INTERFACE(lb_I_Dispatcher)
END_IMPLEMENT_LB_UNKNOWN()

lb_Dispatcher::lb_Dispatcher() {
	
	REQUEST(getModuleInstance(), lb_I_Container, interceptorevents)
}

lb_Dispatcher::~lb_Dispatcher() {
	_CL_VERBOSE << "lb_Dispatcher::~lb_Dispatcher() called." LOG_

	if (evManager != NULL) _CL_VERBOSE << "Event manager in dispatcher has " << evManager->getRefCount() << " references." LOG_
	if (dispatcher != NULL) _CL_VERBOSE << "Dispatcher list has " << dispatcher->getRefCount() << " references." LOG_
}

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_Dispatcher::setData() has not been implemented" LOG_

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setEventManager\40\lb_I_EventManager\42\ EvManager\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setEventManager(lb_I_EventManager* EvManager) {
	evManager = EvManager;
	evManager++;

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ char\42\ EvName\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName) {
	/*
	 * Create an instance of a function pointer object
	 */

	int id = 0;
	_CL_LOG << "lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName) called with " << EvName LOG_
	evManager->resolveEvent(EvName, id);
	addEventHandlerFn(evHandlerInstance, evHandler, id);
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\delEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ char\42\ EvName\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::delEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName) {
	/*
	 * Create an instance of a function pointer object
	 */

	int id = 0;
	evManager->resolveEvent(EvName, id);
	//addEventHandlerFn(evHandlerInstance, evHandler, id);
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ int EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_EvHandler, evH)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
	UAP(lb_I_KeyBase, k)
	UAP(lb_I_Unknown, e)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_EvHandler, ev)
	_CL_LOG << "lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) called with " << EvNr LOG_


	if (dispatcher == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(getModuleInstance(), lb_I_Container, dispatcher)
	}

	evH->setHandler(evHandlerInstance, evHandler);
	i->setData(EvNr);
	QI(i, lb_I_KeyBase, k)
	QI(evH, lb_I_Unknown, e)

	if (dispatcher->exists(&k) == 1) {
        	dispatcher->remove(&k);
	}

	if ((err = dispatcher->insert(&e, &k)) != ERR_NONE) _CL_LOG << "Error: Inserting new container element failed" LOG_

	uk = dispatcher->getElement(&k);

	if (uk == NULL) {
		_LOG << "Error: Could not add an interceptor." LOG_
		return ERR_REGISTER_HANDLER;
	}

	QI(uk, lb_I_EvHandler, ev)

	// Prepare the event name and eventually strip off the instance pointer part.
	char* reversed = evManager->reverseEvent(EvNr);
	char ptr[20] = "";
	sprintf(ptr, "%p", (void*) evHandlerInstance);
	UAP_REQUEST(getModuleInstance(), lb_I_String, Reversed)
	*Reversed = reversed;
	Reversed->replace(ptr, "");
	_LOGVERBOSE << "Adding an interceptor '" << Reversed->charrep() << "' for event '" << reversed << "'. Replace pattern '" << ptr << "'" LOG_
	activateInterceptor(*&Reversed, *&ev);

	return ERR_NONE;
}
/*...e*/

void LB_STDCALL lb_Dispatcher::detachInstance(lb_I_EventHandler* evHandlerInstance) {
	lbErrCodes err = ERR_NONE;
	if (dispatcher != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_Container, handlersToDelete)

		dispatcher->finishIteration();
		while (dispatcher->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			uk = dispatcher->nextElement();
			UAP(lb_I_EvHandler, ev)
			QI(uk, lb_I_EvHandler, ev)
			if (ev != NULL) {
				lb_I_EventHandler* evH = ev->getHandlerInstance();
				if (evH == evHandlerInstance) {
					UAP(lb_I_KeyBase, key)
					key = dispatcher->currentKey();

					handlersToDelete->insert(&uk, &key);
				}
			}
		}

		while (handlersToDelete->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_KeyBase, key)

			uk = handlersToDelete->nextElement();
			key = handlersToDelete->currentKey();

			dispatcher->finishIteration();
			dispatcher->remove(&key);
		}
	}
}

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addDispatcher(lb_I_Dispatcher* disp) {
	_CL_LOG << "lb_Dispatcher::addDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\delDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::delDispatcher(lb_I_Dispatcher* disp) {
	_CL_LOG << "lb_Dispatcher::delDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slb_I_DispatchResponce\42\ lb_Dispatcher\58\\58\dispatch\40\lb_I_DispatchRequest\42\ req\41\:0:*/
lb_I_DispatchResponse* lb_Dispatcher::dispatch(lb_I_DispatchRequest* req) {
	_CL_LOG << "lb_Dispatcher::dispatch() called" LOG_
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\int EvNr\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
	i->setData(EvNr);

	UAP(lb_I_KeyBase, ik)
	QI(i, lb_I_KeyBase, ik)


	UAP(lb_I_Unknown, uk)
	UAP(lb_I_EvHandler, ev)

	if (dispatcher == NULL) {
		_CL_LOG << "Error: Have no dispatcher" LOG_
	} else {

		uk = dispatcher->getElement(&ik);

		if (uk == NULL) {
			_CL_LOG << "Error: Could not get the handler from the id" LOG_
			return ERR_DISPATCH_FAILS;
		}

		QI(uk, lb_I_EvHandler, ev)

		// Prepare the event name and eventually strip off the instance pointer part.
		char* reversed = evManager->reverseEvent(EvNr);
		char ptr[20] = "";
		sprintf(ptr, "%p", (void*) ev->getHandlerInstance());
		UAP_REQUEST(getModuleInstance(), lb_I_String, Reversed)
		*Reversed = reversed;
		Reversed->replace(ptr, "", true);

		UAP(lb_I_EvHandler, evH)
		evH = hasDefinedInterceptor(*&Reversed);

		ev->setInterceptorRequired(evH != NULL);
		ev->call(EvData, EvResult);
	}
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\char\42\ EvName\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(const char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {

	int id = 0;
	lbErrCodes err = ERR_NONE;

	evManager->resolveEvent(EvName, id);

	return dispatch(id, EvData, EvResult);
}
/*...e*/

#ifdef IMPLEMENT_NEWSTUFF

lb_I_EvHandler* LB_STDCALL lb_Dispatcher::hasDefinedInterceptor(lb_I_String* event) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_KeyBase, key)
	QI(event, lb_I_KeyBase, key)

	if (interceptorevents->exists(&key) != 0) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_EvHandler, ev)
		uk = interceptorevents->getElement(&key);
		QI(uk, lb_I_EvHandler, ev)
		ev++;
		return ev.getPtr();
	}

	return NULL;
}

lbErrCodes LB_STDCALL lb_Dispatcher::activateInterceptor(lb_I_String* EvName, lb_I_EvHandler* ev) {
	UAP(lb_I_EvHandler, evInterceptor)
	evInterceptor = hasDefinedInterceptor(*&EvName);
	if (evInterceptor != NULL) {
		_LOG << "lb_Dispatcher::activateInterceptor() activates interceptor '" << EvName->charrep() << "'" LOG_
		ev->setInterceptor(evInterceptor->getInterceptor(), evInterceptor->getBeforeInterceptor(), evInterceptor->getAfterInterceptor());
	}
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::setInterceptor(lb_I_DispatchInterceptor* evHandlerInstance, lbInterceptor evHandler_Before, lbInterceptor evHandler_After, const char* EvName) {
	int id = 0;
	lbErrCodes err = ERR_NONE;
	bool foundRegistered = false;

	_LOG << "lb_Dispatcher::setInterceptor() for event name '" << EvName << "' called." LOG_

	UAP(lb_I_EvHandler, evH)
	UAP(lb_I_Unknown, uk)
	UAP_REQUEST(getModuleInstance(), lb_I_String, new_interceptor)
	UAP(lb_I_KeyBase, key)
	*new_interceptor = EvName;
	QI(new_interceptor, lb_I_KeyBase, key)

	if (interceptorevents->exists(&key) != 0) {
		// Replace existing
		_LOG << "Replacing an existing interceptor." LOG_
		uk = interceptorevents->getElement(&key);
		QI(uk, lb_I_EvHandler, evH)
	} else {
		_LOG << "Adding a new interceptor." LOG_
		REQUEST(getModuleInstance(), lb_I_EvHandler, evH)
		QI(evH, lb_I_Unknown, uk)
		interceptorevents->insert(&uk, &key);
		uk = interceptorevents->getElement(&key);
		QI(uk, lb_I_EvHandler, evH)
	}

	evH->setInterceptor(evHandlerInstance, evHandler_Before, evHandler_After);

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::delInterceptor(const char* EvName) {
	int id = 0;
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
	evManager->resolveEvent(EvName, id);
	i->setData(id);

	UAP(lb_I_KeyBase, ik)
	QI(i, lb_I_KeyBase, ik)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_EvHandler, ev)

	if (dispatcher == NULL) {
		_LOG << "Error: Have no dispatcher" LOG_
		return ERR_DELETE_INTERCEPTOR_FAILS;
	} else {
		uk = dispatcher->getElement(&ik);

		if (uk == NULL) {
			_LOG << "Error: Could not delete an interceptor." LOG_
			return ERR_DELETE_INTERCEPTOR_FAILS;
		}

		QI(uk, lb_I_EvHandler, ev)

		ev->delInterceptor();
	}
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::removeInterceptedInstance(lb_I_String* EvName, lb_I_Unknown* interceptedInstance) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_EvHandler, evInterceptor)
	evInterceptor = hasDefinedInterceptor(*&EvName);

	if (evInterceptor != NULL) evInterceptor->removeInterceptedInstance(interceptedInstance);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::setInterceptorDefinitions(lb_I_String* s) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	pl = PM->getFirstMatchingPlugin("lb_I_CryptoStream", "cryptostream");
	if (pl != NULL) {
		ukPl = pl->getImplementation();

		if (ukPl != NULL) {
			UAP(lb_I_CryptoStream, cs)
			QI(ukPl, lb_I_CryptoStream, cs)

			if (cs != NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, decryptedString)
				*decryptedString = "";
				cs->setAlgorythm(""); // No encryption
				*cs << s;
				cs->setAlgorythm("TripleDES");
				*cs >> *&decryptedString; // Decrypt with TripleDES
				/// \todo This breaks the container anyhow.
				// Why does it compile?
				//interceptorevents = decryptedString->split(',');
				return err;
			}
		}
	}

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	meta->msgBox("Error", "The crypto plugin can't be used!\n\n Work without encryption.");
	//interceptorevents = s->split(',');

	return err;
}

lb_I_String* LB_STDCALL lb_Dispatcher::getInterceptorDefinitions() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	*s = "";

	interceptorevents->finishIteration();
	while (interceptorevents->hasMoreElements() != 0) {
		UAP(lb_I_String, part)
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		uk = interceptorevents->nextElement();
		key = interceptorevents->currentKey();

		if (*s == "") {
			*s = key->charrep();
		} else {
			*s += ",";
			*s += key->charrep();
		}
	}

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	pl = PM->getFirstMatchingPlugin("lb_I_CryptoStream", "cryptostream");
	if (pl != NULL) {
		ukPl = pl->getImplementation();

		if (ukPl != NULL) {
			UAP(lb_I_CryptoStream, cs)
			QI(ukPl, lb_I_CryptoStream, cs)

			if (cs != NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, encryptedString)
				*encryptedString = "";
				cs->setAlgorythm("TripleDES"); // Encrypt with TripleDES
				*cs << *&s;
				cs->setAlgorythm("");
				*cs >> *&encryptedString; // No decryption

				encryptedString++;
				return encryptedString.getPtr();
			}
		}
	}
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	meta->msgBox("Error", "The crypto plugin can't be used!\n\n Work without encryption.");
	s++;
	return s.getPtr();
}

#endif

/*...e*/

/*...slb_EvHandler:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EvHandler)
	ADD_INTERFACE(lb_I_EvHandler)
END_IMPLEMENT_LB_UNKNOWN()

lb_EvHandler::lb_EvHandler() {
	_evHandlerInstance = NULL;
	ev = NULL;
	_evHandlerInstance_interceptor = NULL;
	ev_interceptor_Before = NULL;
	ev_interceptor_After = NULL;
	interceptorRequired = false;
}

lb_EvHandler::~lb_EvHandler() {
}

lbEvHandler LB_STDCALL lb_EvHandler::getHandler() {
	return ev;
}

lbErrCodes LB_STDCALL lb_EvHandler::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_EvHandler, eh)
	QI(uk, lb_I_EvHandler, eh)

	setHandler(eh->getHandlerInstance(), eh->getHandler());

	return ERR_NONE;
}

lb_I_EventHandler* LB_STDCALL lb_EvHandler::getHandlerInstance() {
	return _evHandlerInstance;
}

lbErrCodes LB_STDCALL lb_EvHandler::setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler) {
	_evHandlerInstance = evHandlerInstance;
	ev = evHandler;
	return ERR_NONE;
}

#ifdef IMPLEMENT_NEWSTUFF

void LB_STDCALL lb_EvHandler::setInterceptorRequired(bool _required) {
	interceptorRequired = _required;
}

bool LB_STDCALL lb_EvHandler::getInterceptorRequired() {
	return interceptorRequired;
}

lb_I_DispatchInterceptor* lb_EvHandler::getInterceptor() {
	return _evHandlerInstance_interceptor;
}

lbInterceptor LB_STDCALL lb_EvHandler::getBeforeInterceptor() {
	return ev_interceptor_Before;
}

lbInterceptor LB_STDCALL lb_EvHandler::getAfterInterceptor() {
	return ev_interceptor_After;
}

lbErrCodes LB_STDCALL lb_EvHandler::removeInterceptedInstance(lb_I_Unknown* interceptedInstance) {
	if (_evHandlerInstance_interceptor != NULL) {
		_evHandlerInstance_interceptor->removeInterceptedInstance(interceptedInstance);
	}
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EvHandler::setInterceptor(lb_I_DispatchInterceptor* evHandlerInstance, lbInterceptor evHandler_Before, lbInterceptor evHandler_After) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lb_EvHandler::setInterceptor() called." LOG_
	_evHandlerInstance_interceptor = evHandlerInstance;
	ev_interceptor_Before = evHandler_Before;
	ev_interceptor_After = evHandler_After;

	if (_evHandlerInstance_interceptor != NULL) {
		if (_evHandlerInstance != NULL) {
			char ptr[100] = "";
			sprintf(ptr, "%p", _evHandlerInstance);
			_LOG << "lb_EvHandler::setInterceptor(): Pass intercepted handler " << ptr << " to interceptor." LOG_
			UAP(lb_I_Unknown, uk)

			uk = _evHandlerInstance->getUnknown();
			_evHandlerInstance_interceptor->addInterceptedInstance(*&uk);
		} else {
			_LOG << "Error: Could not add intercepted instance to interceptor. Handler must be passed first by setHandler method." LOG_
		}
	}
	_LOG << "lb_EvHandler::setInterceptor() leaving." LOG_
	return err;
}

lbErrCodes LB_STDCALL lb_EvHandler::delInterceptor() {
	lbErrCodes err = ERR_NONE;

	_evHandlerInstance_interceptor = NULL;
	ev_interceptor_Before = NULL;
	ev_interceptor_After = NULL;

	return err;
}

lbErrCodes LB_STDCALL lb_EvHandler::executeInterceptorBefore(lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	lbErrCodes err = ERR_NONE;

	// Check if the interceptor is required and not initialized (no plugin found with that interceptor).
	if (interceptorRequired && !_evHandlerInstance_interceptor && !ev_interceptor_Before) return ERR_INTERCEPTOR_MISSING;

	if (_evHandlerInstance_interceptor && ev_interceptor_Before) {
			err = (_evHandlerInstance_interceptor->*(lbInterceptor) ev_interceptor_Before) (EvData);
	}

	return err;
}

lbErrCodes LB_STDCALL lb_EvHandler::executeInterceptorAfter(lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	lbErrCodes err = ERR_NONE;

	if (_evHandlerInstance_interceptor && ev_interceptor_After) {
		err = (_evHandlerInstance_interceptor->*(lbInterceptor) ev_interceptor_After) (EvData);
	}

	return err;
}

#endif

lbErrCodes LB_STDCALL lb_EvHandler::call(lb_I_Unknown* evData, lb_I_Unknown** evResult, bool hasDefinedInterceptor) {

	// Assume the interceptor makes only sense if the real function is callable. Thus interceptor is here
#ifdef IMPLEMENT_NEWSTUFF
	lbErrCodes err_interceptor_Before = executeInterceptorBefore(evData, evResult);

	if (err_interceptor_Before == ERR_INTERCEPTOR_MISSING) {
		_LOG << "Error: Interceptor defined, but is missing." LOG_
		return ERR_INTERCEPTOR_MISSING;
	}

	if (err_interceptor_Before == ERR_INTERCEPTOR_BEFORE_CANCEL) {
		_LOG << "Error: Interceptor has cancelled operation." LOG_
		return ERR_INTERCEPTOR_BEFORE_CANCEL;
	}
#endif
	(_evHandlerInstance->*(lbEvHandler) ev) (evData);

#ifdef IMPLEMENT_NEWSTUFF
	lbErrCodes err_interceptor_After = executeInterceptorAfter(evData, evResult);
#endif

	return ERR_NONE;
}
/*...e*/

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();

                	if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);

                	TRMemSetModuleName(__FILE__);

                	if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:
                       	_CL_LOG << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
                        if (situation) _CL_VERBOSE << "DLL released by system." LOG_
                        else           _CL_VERBOSE << "DLL released by program.\n" LOG_
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }

        return TRUE;
}
/*...e*/
#endif
