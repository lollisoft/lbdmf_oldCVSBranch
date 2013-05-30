/*...sLicense:0:*/
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

/**
 *  \file lbInterfaces.h
 *  Main include file for all interfaces.
 *
 *  lbConfigHook.h includes this file for you.
 */

/*...sMain page documentation:0:*/
/** \mainpage Distributed Multiplatform Framework (1.0.4-final)
 * \section intro_sec Introduction to DMF - Distributed Multiplatform Framework
 *
 * This is the introduction for the users of DMF after the first installation.
 * Here the post installation will be explained in short and other important things,
 * that have to do with installation and different usage as of databases.
 *
 * To start programming, you could start \ref Quickstart "here".
 *
 * The main sample application and it's documentation will be found \ref PrototypeGUI "here".
 *
 * Prerequirements:
 *
 * My latest version of binary build tools. <a href="http://sourceforge.net/projects/lbdmf/files/lbdmf/lbDMF-1.0.4-stable-rc3/lbDMF-BinbuildTools-1.0.4-stable-rc3.exe/download">Binary Build Tools</a>
 *
 * Latest MinGW compiler (tested version as of release day). <a href="http://www.mingw.org">MinGW</a>
 *
 * The wxWidgets source code. Latest version tested is 2.8.11 <a href="http://www.wxwidgets.org">wxWidgets</a>. <b>Note: Additionally to the build instructions for wxWidgets, use mingw32-make instead of make.</b>
 *
 * Supported databases: <a href="http://www.postgresql.org">PostgreSQL</a> or <a href="http://www.sqlite.org">Sqlite</a>.
 * Other databases may be possible, but there is not yet a SQL script to setup the database. The Sqlite database is included in the source tree.
 *
 * \note To get ODBC stuff work properly under Linux you should at least on SuSE Linux 9.1 download unixODBC version 2.2.11,
 * compile and install it. After that, reinstall ODBC driver version 07.03.0200 for UPDATEABLE CURSORS.
 *
 * \ref Postsetup "Post setup instructions."
 *
 * A new feature that has been documented in the pdf documentation but not here:
 *
 * Actions
 *
 * Actions are a mechanism to configure user interaction in a dynamic fashion. Basically the database forms have prebuild actions
 * such as First, Previous, Next, Last, Add, Delete, Refresh. Also there are actions that will be created by the model, if you add
 * a stereotype of masterdetail_action or detailmaster_action what results into 'jump into the details form' or 'jump into the master form'.
 *
 * But there are many other possible actions that could be triggered not only by code. Here I will start listing these actions for a reference.
 *
 * \ref Actionreference "Actions reference page."
 */
/*...e*/

/*...sActions reference page.:0:*/
/** \page Actionreference Actions reference page.
 *
 * \section Introduction
 * Users interact with software in general. Each interaction can be understood as such and I'll name them actions.
 * The main application - wxWrapper - for sample, predefines a set of actions that are to be used by the application ligic.
 * Other actions are provided by other modules if They are loaded. I mean plugins.
 *
 * \section Dive Dive into
 * Most of these actions are defined to get the ability of loose coupling. If an action is called (by name), but does not exist,
 * nothing happens. The software functionality in general will not be affected. Also most of these actions were used from withing
 * hard coded functionality. That's what I will change in the future and have begun to understand it's importance for a prototype.
 *
 * Therefore this sections are for.
 *
 * \section Actions1 Actions in the meta application
 *
 * Registered handlers in lb_MetaApplication::registerEventHandler:
 *
 * \b doAutoload Activates or deactivates autoloading the last logged in application. No parameters are required.
 *
 * \b doLog Activates or deactivates logging. Logging to file and console are affected by this function.
 *
 * \b enterDebugger Breaks into the debugger. It was used earlyer, but not recently.
 *
 * \b getBasicApplicationInfo Nope, it does nothing more than creating a console message for now. To be filled with useful code.
 *
 * \b getMainModuleInfo If the meta application has an associated GUI, it displays the information about it self in a dialog. If not it prints it to the console.
 *
 * '<b>Button Test pressed</b>' Was for first trials of these dispatched event handlers or actions.
 *
 * \b getLoginData Used to open a login form. Not supported yet on console.
 *
 * Properties could change and thus one may be interested in that event. The meta application uses the following function to register a group of propertie's change events
 * handled by a function: registerPropertyChangeEventGroup. The following parameters are registered and thus could also triggered from anywhere.
 *
 * Group of properties 'General' (prefix in the handler name):
 *
 * '<b>Base directory</b>' sets a new base directory where the application operates, but does not chdir to.
 *
 * '<b>Autoselect last application</b>' Activates a small helper to ease the login procedure. Not yet implemented.
 *
 * '<b>Autorefresh updated data</b>' Sets autorefresh in database forms to not work on invalid (old) data.
 *
 * '<b>Autoopen last application</b>' Same as the event handler doAutoload.
 *
 * '<b>Prefer database configuration</b>' Prefer using the database contents instead local cache in file.
 *
 * '<b>Application Database backend</b>' The database backend namespace for the application. Used to lookup different database implementations.
 *
 * '<b>System Database backend</b>' The database backend namespace for the system. The system database stores the configuration of an application.
 *
 * '<b>Use application Database backend</b>' Use the backend database by namespace. If not, an ODBC backend is used.
 *
 * '<b>Use system Database backend</b>' Same for the system database, thus one can use different database systems for configuration and application.
 *
 * \section Actions2 Actions in the wxWrapperDLL module
 *
 * Registered handler in lb_wxFrame::registerEventHandler:
 *
 * \b ShowPropertyPanel
 *
 * \b switchPanelUse
 *
 * \b switchTableUse
 *
 * \b setPreferredPropertyPanelByNamespace
 *
 * \b showMsgBox
 *
 * \b addStatusBar
 *
 * \b addStatusBar_TextArea
 *
 * \b setStatusText
 *
 * \b addToolBar
 *
 * \b removeToolBar
 *
 * \b addTool_To_ToolBar
 *
 * \b removeTool_From_ToolBar
 *
 * \b toggleTool_From_ToolBar
 *
 * \b showLeftTreeView
 *
 * \section Actions3 Actions in the wxWrapper (dynamic.cpp) module
 *
 * \b AddMenu
 *
 * \b AddMenuBar
 *
 * \b AddMenuEntry
 *
 * \b AddButton
 *
 * \b AddLabel
 *
 * \b AddTextField
 *
 * \b askOpenFileReadStream
 *
 * \b askYesNo
 *
 * \b enableEvent
 *
 * \b disableEvent
 *
 * \b toggleEvent
 *
 * \b setXRCFile
 *
 * \b askForDirectory
 *
 * \section Actions4 Actions in the lbLoginWizard.cpp module
 * Also Plugins can register dispatch handlers. Thus the software has a very simple extension mechanism.
 *
 * \b RunLogin
 *
 * \section Actions5 Actions in the lbDynamicApplication module when the app is loaded (what makes the main database application functionality possible)
 *
 * If the application loaded is 'lbDMF Manager'
 *
 * \b evtExportApplicationToXML Save the application model (in database) to XML format.
 *
 * \b exportApplicationToXMLBuffer Save the application model (in database) to XML formatted string.
 *
 * \b exportApplicationConfigurationToUMLXMIDoc Saves the application model (in database) to XMI formatted UML representation.
 *
 * \b importUMLXMIDocIntoApplication Imports an XMI UML representation from file.
 *
 * \b editProperties Opens the properties panel.
 *
 * If the application loaded is not 'lbDMF Manager'
 *
 * \b exportApplicationToXMLBuffer
 *
 * \b exportApplicationConfigurationToUMLXMIDoc
 *
 * \section Actions6 Actions in the lbDynamicApplication module when the lb_I_Application implementation is initialized
 *
 * \b resetCustomDBFormsToDynamic
 *
 * \b executeQueryFromFile
 *
 * \b overwriteDatabase
 * 
 * \section Actions7 Actions in lbDynamicApplication::activateDBForms when the forms per application are initialized
 *
 * For each form in the formulare table, eventname is used to register an 'open form' action for the configured form.
 *
 * \section Actions8 Actions in the plugin manager
 *
 * The plugin manager yet only registers runUnitTests as action.
 *
 * \section Actions9 Actions in the foreign key primary key selection dialog
 *
 * There will be registered one event handler to select a column. I currently don't know what is it for.
 *
 * \section Actions10 Actions that are registered per database dialog
 *
 * Each handler has prefixed the string value of the instance pointer (0xaf56bc78).
 *
 * \b DatabaseFirst
 *
 * \b DatabaseNext
 *
 * \b DatabasePrev
 *
 * \b DatabaseLast
 *
 * \b DatabaseAdd
 *
 * \b DatabaseDelete
 *
 * \section Actions11 Actions that are registered per database panel
 *
 * Each handler has prefixed the string value of the instance pointer (0xaf56bc78).
 *
 * \b DatabaseFirst
 *
 * \b DatabaseNext
 *
 * \b DatabasePrev
 *
 * \b DatabaseLast
 *
 * \b DatabaseAdd
 *
 * \b DatabaseDelete
 *
 * \b DatabaseRefresh
 *
 * \b DBFormInitialized
 * 
 * \section Actions12 Actions that are registered per database table view dialog
 *
 * Each handler has prefixed the string value of the instance pointer (0xaf56bc78).
 *
 * \b DatabaseFirst
 *
 * \b DatabaseNext
 *
 * \b DatabasePrev
 *
 * \b DatabaseLast
 *
 * \b DatabaseAdd
 *
 * \b DatabaseDelete
 * 
 * \section Actions13 Actions that are registered per database table view panel
 *
 * Each handler has prefixed the string value of the instance pointer (0xaf56bc78).
 *
 * \b DatabaseFirst
 *
 * \b DatabaseNext
 *
 * \b DatabasePrev
 *
 * \b DatabaseLast
 *
 * \b DatabaseAdd
 *
 * \b DatabaseDelete
 *
 * \b DatabaseRefresh
 * 
 * \section Actions14 Actions registered per database form actions configuration
 *
 * Each action is registered in the following schema: '<instance pointer string>(<action name>)'.
 *
 * \section Actions15 Action handlers in Unit Tests
 * The Unit Tests demonstrate the ability to simulate user interaction such as askYesNo. It registers this handler to react
 * upon application logic with user interaction. See UIWrapper::registerEventHandler in testUMLImport.cpp or Actions.cpp in
 * the UnitTests sub directories Actions/BaseDebelopment or RegressionTests sub directory TestUMLImport.
 * 
 */
/*...e*/

/*...sQuickstart page documentation:0:*/
/** \page Quickstart Beginning programming in DMF environment.
 *
 * \section Introduction
 * Here we will learn to create simple console applications.
 *
 * \section HelloWorld A simple application like the famous Hello world application.
 * As the most programming environments, showing a first sample application, I will do the same.
 * We will start to create a new simple Hello world application, showing a 'Hello world' text.
 * But we do not use prinf's or cout's.
 *
 * We would use the console logging feature of DMF and a string class that will be loaded from
 * anywhere else using an interface.
 *
 * At first, you will see the code:
 * \ref FirstSample "Hello world."
 *
 */
/*...e*/

/*...sPost setup documentation:0:*/
/** \page Postsetup Post setup instructions.
 *
 * \section Introduction
 * You do need to post setup your installation. These includes minimal changes in files, installing
 * software, databases, ODBC drivers and setup ODBC configurations.
 *
 * \section PSetup1 Post setup
 *
 *	The post setup uses a scenary of an installation to drive D: where afterwards a directory lbDMF exists.
 *
 * \section PSetup2 lbDMF Develop link
 *
 *	If you start the lbDMF Develop link on the desktop, you get opened a text file with
 *	a hint text. It explains once to read these instructions for post installation.
 *
 *	If you don't have downloaded the source distribution yet, do this before continuing.
 *
 * \section PSetup3 Drive letter
 *
 *	If you have installed lbDMF to C:\\lbDMF, you can skip this step.
 *
 *	Right click on lbDMF Develop symbol to edit it. Change the drive letter, pointing to
 *	your actual installation. Sample here would drive D: and not the standard C: drive letter.
 *	In this sample installation scenario, simply change the lines set DEVLW=<driveletter> to DEVLW=D:
 *
 *	Note: There are two locations of setting DEVLW. Change the line after :DISTMODE
 *
 * \section PSetup4 Setup wxWidgets
 *
 *	Install the wxWidgets distribution into [C/D]:\\lbDMF\\Develop\\wxwin\\wx.
 *
 *	After installation: Check, if inside exists a src directory and all else of the distribution.
 *
 * \section PSetup5 Setup Open Watcom
 *
 *	Install the Open Watcom distribution into [C/D]:\\lbDMF\\Develop\\tools\\watcom.
 *
 *	After installation: Check, if inside exists a src directory and all else of the distribution.
 *
 * \section PSetup6 Make wxWidgets (2.4.x) source tree
 *
 *	If you like to have a static library, skip that lines, that copy makefile.env and makefile.wat.
 *
 *	Start a normal MSDOS console (cmd) and type these lines (C:):
 *
 *	\code
 *	set DRIVE=C:
 *	set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXDIR%\src\msw
 *	copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx
 *	copy /Y %WXDIR%\..\..\Projects\CPP\makewat.env %WXDIR%\src
 *	copy /Y %WXDIR%\..\..\Projects\CPP\makefile.wat %WXDIR%\src\msw
 *	wmake -f makefile.wat all
 *	\endcode
 *
 *	or
 *
 *	Start a normal MSDOS console (cmd) and type these lines (D:):
 *
 *	\code
 *	set DRIVE=D:
 *	set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXDIR%\src\msw
 *	copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx
 *	copy /Y %WXDIR%\..\..\Projects\CPP\makewat.env %WXDIR%\src
 *	copy /Y %WXDIR%\..\..\Projects\CPP\makefile.wat %WXDIR%\src\msw
 *	wmake -f makefile.wat all
 *	\endcode
 *
* \section PSetup61 Make wxWidgets (2.6.x) source tree
	*
	 *	Bevore you build the library, decide to build a static library or a shared library (DLL).
		*	If you like to have a DLL, modify the following file: config.wat in the build/msw directory.
			*
			 *	# What type of library to build? [0,1]
			 *	SHARED = 1
			 *
			 *	There is also a switch for debug or release builds:
			 *
			 *	# Type of compiled binaries [debug,release]
			 *	BUILD = release
			 *
			 *	Start a normal MSDOS console (cmd) and type these lines (C:):
			 *
			 *	\code
			 *	set DRIVE=C:
			 *	set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx
			 *	%DRIVE%
			 *	cd %WXDIR%\build\msw
			 *	copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx
			 *	wmake -f makefile.wat all
			 *	\endcode
			 *
			 *	or
			 *
			 *	Start a normal MSDOS console (cmd) and type these lines (D:):
			 *
			 *	\code
			 *	set DRIVE=D:
			 *	set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx
			 *	%DRIVE%
			 *	cd %WXDIR%\build\msw
			 *	copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx
			 *	wmake -f makefile.wat all
			 *	\endcode
			 *
			 *	This should start compiling the wxWidgets code.
			 *
			 *	After you have built wxWitgets, you must copy the created DLL to the place where it should be
			 *	installed:
			 *
			 * \section PSetup62 Copy DLL/library for wxWidgets 2.4.x/2.6.x:
			 *
			 *	From drive C:
			 *
			 *	\code
			 *	set DRIVE=C:
			 *	set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx
			 *	%DRIVE%
			 *	cd %WXDIR%\src\msw
			 *	mkdir %WXDIR%\..\..\Projects\dll\libs
			 *	copy /Y %WXDIR%\lib\wat_dll\wxmsw*.dll %WXDIR%\..\..\Projects\dll
			 *	copy /Y %WXDIR%\lib\wat_dll\wxmsw*.lib %WXDIR%\..\..\Projects\dll\libs
			 *	copy /Y %WXDIR%\lib\wxmsw*.dll %WXDIR%\..\..\Projects\dll
			 *	copy /Y %WXDIR%\lib\wxmsw*.lib %WXDIR%\..\..\Projects\dll\libs
			 *	\endcode
			 *
			 *	From Drive D:
			 *
			 *	\code
			 *	set DRIVE=D:
			 *	set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx
			 *	%DRIVE%
			 *	cd %WXDIR%\src\msw
			 *	mkdir %WXDIR%\..\..\Projects\dll\libs
			 *	copy /Y %WXDIR%\lib\wat_dll\wxmsw*.dll %WXDIR%\..\..\Projects\dll
			 *	copy /Y %WXDIR%\lib\wat_dll\wxmsw*.lib %WXDIR%\..\..\Projects\dll\libs
			 *	copy /Y %WXDIR%\lib\wxmsw*.dll %WXDIR%\..\..\Projects\dll
			 *	copy /Y %WXDIR%\lib\wxmsw*.lib %WXDIR%\..\..\Projects\dll\libs
			 *	\endcode
			 *
			 * \section PSetup7 Start compiling lbDMF source tree
			 *
			 *	If you have done this, you can restart the lbDMF Develop link and a simple console window
			 *	starts.
			 *
			 *	Type make
			 *
			 * \section PSetup8 Database setup
			 *
			 *	To be able to run the sample applications, you need to create at least one database.
			 *	Do this with the tools, provided from the database vendors.
			 *
			 *	The first database, needed should be named lbdmf and a correct ODBC configuration should
			 *	be set up. See below.
			 *
			 *	The database scripts are located in [C/D]:\\lbDMF\\Develop\\Projects\\CPP\\Database.
			 *
			 *	Create at least an user to have rights to change data. For the PostgreSQL database, create
			 *	the user and create the tables with that user logged on. If you set up the tables with the
			 *	database system user, your user has not the correct rigths.
			 *
			 *	Currently, I maintain MySQL and Sybase and PostgreSQL database scripts, but I prefer to use PostgreSQL.
			 *
			 *	Set the environment variables to connect with the correct user and password. If not, default values from
			 *	my private database are used:
			 *
			 *	set lbDMFUser=<User>
			 *
			 *	set lbDMFpasswd=<Password>
			 *
			 * \section PSetup9 ODBC Setup
			 *
			 *	The setup must activate any updateable cursor switches, don't convert bools as char. As a sample, here are
			 *	the nessesary registry files (their content) to setup a configuration to a local PostgreSQL installation
			 *	(as administrator):
			 *
			 *	\note The samples here are for drive C: installation only.
			 *
			 *	The database ODBC setup:
			 *
			 *	\code
			 *	Windows Registry Editor Version 5.00
			 *
			 *	[HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBC.INI\ODBC Data Sources]
			 *	"lbDMF"="PostgreSQL"
			 *
			 *	[HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBC.INI\lbDMF]
			 *	"Driver"="C:\\lbDMF\\develop\\Projects\\dll\\psqlodbc.dll"
			 *	"Fetch"="100"
			 *	"CommLog"="0"
			 *	"Debug"="0"
			 *	"Optimizer"="1"
			 *	"Ksqo"="1"
			 *	"UniqueIndex"="1"
			 *	"UseDeclareFetch"="0"
			 *	"UnknownSizes"="0"
			 *	"TextAsLongVarchar"="1"
			 *	"UnknownsAsLongVarchar"="0"
			 *	"BoolsAsChar"="0"
			 *	"Parse"="0"
			 *	"CancelAsFreeStmt"="0"
			 *	"MaxVarcharSize"="254"
			 *	"MaxLongVarcharSize"="8190"
			 *	"ExtraSysTablePrefixes"="dd_;"
			 *	"Description"=""
			 *	"Database"="lbdmf"
			 *	"Servername"="localhost"
			 *	"Port"="5432"
			 *	"SSLmode"="prefer"
			 *	"Username"="dba"
			 *	"Password"="trainres"
			 *	"ReadOnly"="0"
			 *	"ShowOidColumn"="0"
			 *	"FakeOidIndex"="0"
			 *	"RowVersioning"="0"
			 *	"ShowSystemTables"="1"
			 *	"Protocol"="6.4"
			 *	"ConnSettings"=""
			 *	"DisallowPremature"="0"
			 *	"UpdatableCursors"="1"
			 *	"LFConversion"="1"
			 *	"TrueIsMinus1"="0"
			 *	"BI"="0"
			 *	"ByteaAsLongVarBinary"="0"
			 *	"UseServerSidePrepare"="0"
			 *	"LowerCaseIdentifier"="0"
			 *	\endcode
			 *
			 *	The database ODBC driver setup:
			 *
			 *	\code
			 *	Windows Registry Editor Version 5.00
			 *
			 *	[HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBCINST.INI\PostgreSQL]
			 *	"UsageCount"=dword:00000001
			 *	"Driver"="C:\\lbDMF\\develop\\Projects\\dll\\psqlodbc.dll"
			 *	"Setup"="C:\\lbDMF\\develop\\Projects\\dll\\psqlodbc.dll"
			 *	"APILevel"="1"
			 *	"SQLLevel"="1"
			 *	"DriverODBCVer"="03.00"
			 *	"FileUsage"="0"
			 *	"ConnectFunctions"="YYN"
			 *	"Fetch"="100"
			 *	"CommLog"="0"
			 *	"Debug"="0"
			 *	"Optimizer"="1"
			 *	"Ksqo"="1"
			 *	"UniqueIndex"="1"
			 *	"ReadOnly"="0"
			 *	"UseDeclareFetch"="0"
			 *	"UnknownSizes"="0"
			 *	"TextAsLongVarchar"="1"
			 *	"UnknownsAsLongVarchar"="0"
			 *	"BoolsAsChar"="0"
			 *	"Parse"="0"
			 *	"CancelAsFreeStmt"="0"
			 *	"MaxVarcharSize"="254"
			 *	"MaxLongVarcharSize"="8190"
			 *	"ExtraSysTablePrefixes"="dd_;"
			 *	"CPTimeout"="<not pooled>"
			 *	"ConnSettings"=""
			 *	\endcode
			 *
			 * \section PSetup10 Run the sample GUI application
			 *
			 *	Simply after compiling the sources, let the build window open and type wxwrapper. Go to menu
			 *	File->Login and login as behrens over the wizard and use password as the password.
			 *
			 *	After successfull login you should be able to select an application. Choose lbDMF Manager.
			 *
			 */
			 /*...e*/

			 /*...sDatabase Prototype GUI:0:*/
			 /** \page PrototypeGUI Database prototype GUI documentation
			  *
			  * \section Introduction
			  *
			  * The main sample application, distributed also as binary sample, is aimed to be a prototype
			  * for any kind of database applications. You could define forms and related information in a
			  * configuration database.
			  *
			  * If you have a target database model for a specific application, then it is easy to build up
			  * a prototype for it in minutes. Here you could see it in action on <a href="../../screens-sample-all.html">all platforms</a>
			  *
			  * \section Prepare1 Prepare for first run
			  *
			  * Before you could run the sample application, you need a proper set up database. As I most time
			  * test and use <a href="http://www.postgresql.org">PostgreSQL</a>, you should have installed this
			  * database engine. Also you should have set up an ODBC driver for that database. See \ref PSetup9 "ODBC Setup".
			  *
			  * \note The binary sample package contains an ODBC setup routine for a PostgreSQL database installed on your machine.
			  *
			  * After database installation (see \ref PSetup8 "Database setup") you need to run the script for that database.
			  *
			  * Source package:
			  *
			  * \li PostgreSQL: /lbDMF/develop/Projects/CPP/Database/lbDMF-PostgreSQL.sql
			  * \li MySQL: /lbDMF/develop/Projects/CPP/Database/lbDMF-MySQL.sql
			  * \li Sybase: /lbDMF/develop/Projects/CPP/Database/lbDMF-Sybase.sql
			  *
			  * Binary sample package:
			  *
			  * \li PostgreSQL: /lbDMF/Database/lbDMF-PostgreSQL.sql
			  * \li MySQL: /lbDMF/Database/lbDMF-MySQL.sql
			  * \li Sybase: /lbDMF/Database/lbDMF-Sybase.sql
			  *
			  * \section Application1 The application
			  *
			  * Let us start with an application - say - we have a small CD collection database.
			  *
			  * \section DatabaseSetup1 Database Setup
			  *
			  * The CD collection database will consist interpret, album and and title tables. To create
			  * the database, please copy the SQL code below to your database query editor of your newly created database instance.
			  *
			  * \note You must declare a primary key for each table. If you don't do it, the GUI would not work properly.
			  *
			  * \code
			  -- Force to use this user. Rename it accordingly.
			  SET SESSION AUTHORIZATION 'dba';

			  CREATE TABLE interpret (
			  id SERIAL,
			  name CHAR(50),
			  country CHAR(3),
			  PRIMARY KEY (id)
			  );

			  CREATE TABLE album (
			  id SERIAL,
			  interpretid INT,
			  name CHAR(50),
			  go_public_date DATE,
			  PRIMARY KEY (id),
			  CONSTRAINT cst_album_interpret_interpretid FOREIGN KEY (interpretid)
			  REFERENCES interpret (id) ON UPDATE NO ACTION ON DELETE NO ACTION
			  );

			  CREATE TABLE title (
			  id SERIAL,
			  albumid INT,
			  songid INT,
			  name CHAR(50),
			  time TIME,
PRIMARY KEY (id),
	CONSTRAINT cst_title_album_albumid FOREIGN KEY (albumid)
	REFERENCES album (id) ON UPDATE NO ACTION ON DELETE NO ACTION

	);
	* \endcode
	*
	* \section lbDMFDatabaseSetup1 Setup the configuration in the main config database
	*
	* To be able to run the application with forms against that tables, we need to setup some configuration for it.
	* Start the GUI and login with the default user 'user' and password 'TestUser'. Select the application 'lbDMF Manager'.
	* A menu would be created with some entries.
	*
	* \note You get a tabbed view per default. If you like to view more than one form in parallel, select 'File->switch panel usage'.
	*
	* Select menuentry 'Benutzer verwalten' in menu 'lbDMF Manager' to manage users.
	* There, add a new entry with 'Add' and then set up the users data correctly.
	*
	* \note If you add the first entry in the form, you should again press the add button and then delete one of the two created entries with delete. Say, this is still a little bad 'feature' and behaves in all forms.
	*
	* \section AddApplication1 Create a new application
	*
	* After you have created a new user, you must create a new application. This would <b>not</b> be done, if you press the button 'Anwendungen'.
	* You first must open a new form.
	*
	* Go to menu 'lbDMF Manager' and open 'Anwendungen' from <b>there</b>. The difference is, that you get opened the form 'Anwendungen',
	* whereas you open the 'User to application' mapping from the users form. This is because you could map multiple users to multiple
	* applications. (It is a N to N relation).
	*
	* \section ApplicationDataEntry1 Entries for the new application
	*
	* Enter the data for your new application as follows:
	*
	* \verbatim
	Application name  = 'Music database'
	Application title = 'Music database'
	Module name       = 'lbDynApp'
	Functor           = 'instanceOfApplication'
	Interface         = 'lb_I_Application' \endverbatim
	*
	* If you have entered all data, again press add (remember deletion of temprary added data) <b>or</b>
	* press a navigation button to save the data.
	*
	* \section GotoDetail1 Connect the user with the application
	*
	* Go to tab 'Benutzer' and press 'Anwendungen' to connect the user to the newly created application. Create a new entry
	* by pressing 'Add' and select your new application from the drop down list. After this, you have to either save the data
	* or again press 'Add' and delete the secondly added entry again.
	*
	* \section SetFormular1 Setup database formulars
	*
	* For each table in the sample, you need to create a database formular configuration. To do this, you go to tab 'Anwendungen' and press
	* the button 'Formulare'. You will open a detail form, that will only show forms for your currently selected application in tab 'Anwendungen'
	*
	* From there you must use 'Add' to create new entries in that form. Press twice and let the second one alive - do not delete it again.
	* Setup formular name and all data as follows:
	*
	* \verbatim
	name        = '<formname>'
	menuname    = '<name in menu>'
	eventname   = 'manage<formularname>'
	menuhilfe   = '<menu help text>'
	anwendungid = '<select your application>'
	typ         = '<select Dynamisch aufgebautes Datenbankformular>' \endverbatim
	*
	* The event name must be unique per application. Double entries would be used once and the first entry retrieved from the database query wins.
	*
	* Each form could be of a dynamic type or a hard coded variant. Hardcoded is not implemented yet. The menu help 'menuhilfe' also is not implemented yet.
	*
	* Repeat this step for all your forms.
	*
	* \section SetQuery1 Setup SQL query parameter
	*
	* After you have created an application, connected the newly created user to that application and have created the forms, you need
	* to setup a SQL query for each form. Do this from the current tab by pressing the button 'Parameter'.
	*
	* Each form currently needs only one parameter - the query parameter. Add a new entry and setup as follows:
	* \verbatim
	parametername  = 'query'
	parametervalue = '<SQL query for that form>' \endverbatim
	*
	* Repeat this step by changing to tab 'Formulare', select the other forms and press 'Parameter' for each form.
	*
	* \section RestartAndTry Restart and try your application
	*
	* You could directly login to your new application, but this may buggy. Restart and try then.
	*/
	/*...e*/

#ifdef _MSC_VER

#pragma warning( disable: 4275 )
#pragma warning( disable: 4101 )
#pragma warning( disable: 4102 )
#pragma warning( disable: 4172 )
#pragma warning( disable: 4251 )

#endif

#ifdef __WATCOMC__
#pragma warning 14 9;
#endif

	/*...sdocu:0:*/
	/**
	 * For all Interfaces are factories needed. How should I design these
	 * factories ?
	 */

	/*...e*/

	/*...sbasics:0:*/
	/*...sincludes and definitions:0:*/
	/**
	 * All classes, that anounce callbacks, must implement the interface for
	 * lb_I_CallbackManager. The callback manager did not need to handle its
	 * own table, more it may delegate this to the static (singleton) handler.
	 */


#ifndef __LB_INTERFACES__
#define __LB_INTERFACES__

	// If NULL is undefined, let it define by stddef.h
#ifndef NULL
#include <stddef.h>
#endif

#include <lbErrcodes.h>

	//#define LB_STDCALL

#ifndef FALSE
#define FALSE false
#endif

/** \todo Put each definition in a separate block.
 *
 */
	// KDevelop: Problems to set these variable :-)
#ifdef TVISION
#ifndef LB_STDCALL
#ifdef WINDOWS
#define LB_STDCALL __stdcall
#define LB_CDECL __cdecl
	//__attribute__((cdecl))
#endif
#ifndef WINDOWS
#define LB_STDCALL
#define LB_CDECL
#endif
#endif
#endif

#ifndef _MSC_VER
 #ifndef LB_STDCALL
  #ifdef WINDOWS
   // LB_STDCALL should be used for all member functions
   #define LB_STDCALL __stdcall
   // LB_CDECL should be used for all functions
   #define LB_CDECL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_STDCALL
   #define LB_CDECL
  #endif
 #endif
#endif

#ifndef LB_FUNCTORCALL
 #ifdef WINDOWS
  // As LB_CDECL for functions, this should also __cdecl
  #define LB_FUNCTORCALL __cdecl
 #endif
 #ifndef WINDOWS
  #define LB_FUNCTORCALL
 #endif
#endif


#ifdef _MSC_VER
#ifndef LB_STDCALL
#ifdef WINDOWS
#define LB_STDCALL __stdcall
#define LB_CDECL __cdecl
#endif
#ifndef WINDOWS
#define LB_STDCALL
#define LB_CDECL
#endif
#endif

#ifndef LB_FUNCTORCALL
#ifdef WINDOWS
#define LB_FUNCTORCALL __stdcall
#endif
#ifndef WINDOWS
#define LB_FUNCTORCALL
#endif
#endif
#endif

#ifdef WINDOWS
#define LB_DLLEXPORT __declspec(dllexport)
#define LB_DLLIMPORT __declspec(dllimport)
#endif

#ifndef DLLEXPORT
	// Default to import. Modules redefine this in general.
#ifdef WINDOWS
#define DLLEXPORT LB_DLLIMPORT
#endif
#ifdef LB_DMF_POWER
#define DLLEXPORT LB_DLLIMPORT
#endif
#ifdef LINUX
#define DLLEXPORT
#endif
#endif

#if !defined(LB_CDECL)
#error LB_CDECL is not defined !
#endif


#ifndef __BASE_TYPES_DEFINED__
#define __BASE_TYPES_DEFINED__
	/*...sbase types:0:*/
#ifndef __WATCOMC__
#ifndef _MSC_VER
#ifndef TVISION
#ifndef __MINGW32__
	typedef unsigned char byte;
	typedef unsigned short u_short;
#endif
#endif
#endif
#endif
#ifdef __POWERPP
	typedef unsigned short byte;
	typedef unsigned short u_short;
#endif
#ifdef OSX
#if (OSNAME == Panther)
	typedef unsigned long DWORD;
#endif
#if (OSTYPE == Leopard)
	//typedef unsigned int DWORD; // Leopard with IODBC
	typedef unsigned long DWORD;
#endif
#endif
#ifndef OSX
	typedef unsigned long DWORD;
#endif
	typedef unsigned short LB_DATA;
	//typedef unsigned short u_short;
	/*...e*/
#endif // __BASE_TYPES_DEFINED__

	class lb_I_CallbackTarget;
	class lb_I_ProtocolTarget;

	//#include <lbInterfaces-sub-transfer.h>
	/*...e*/

	/*...sforward class decl\39\s:0:*/
	/**
	 * The base interface, that currently implements only release.
	 * A query interface should be added. But is M$'s solution usable ?
	 */

	class lb_I_String;

	class lb_I_gcManager;
	class lb_I_Unknown;
	class lb_I_Module;

	class lb_I_Event;
	class lb_I_EventSink;

	class lb_I_Dispatcher;
	class lb_I_EventManager;
	class lb_I_EventHandler;

	class lb_I_ConfigObject;

	class lb_I_Frame;
	class lb_I_Transfer_Data;

	// Base interface for visitors
	class lb_I_Aspect;

	class lb_I_VisitableHelper;
	class lb_I_Streamable;
	class lb_I_Integer;
	class lb_I_Long;
	class lb_I_Container;
	class lb_I_Database;
	class lb_I_Connection;
	class lb_I_ColumnBinding;
	class lb_I_BoundColumn;
	class lb_I_KeyBase;
	class lb_I_Query;
	class lb_I_MVC_View;
	class lb_I_InterfaceRepository;
	class lb_I_Element;
	class lb_I_FunctorEntity;
	class lb_I_InstanceReference;
	class lb_I_FileOperation;
	class lb_I_OutputStream;
	class lb_I_Locale;
	class lb_I_Parameter;
	class lb_I_Log;
	class lb_I_Window;
	class lb_I_wxFrame;
	class lb_I_MasterDetailFormDefinition;
	class lb_I_DatabaseReport;
	class lb_I_Project;
	class lb_I_Stream;
	class lb_I_CodeGenerator;
	class lb_I_ProjectManager;
	class lb_I_GUIApp;
	class lb_I_LogonPage;
	class lb_I_AppSelectPage;
	class lb_I_LogonHandler;
	class lb_I_DatabaseOperation;
	class lb_I_Document;
	class lb_I_Socket;
	class lb_I_Transfer_DataObject;
	class lb_I_Transfer;
	class lb_I_ThreadImplementation;
	class lb_I_Column_Types;
	class lb_I_Formular_Fields;
	class lb_I_FixedDatabaseForm;
	class lb_I_DBReportTextblock;
	class lb_I_DBReportProperties;
	class lb_I_DirLocation;
	class lb_I_Action_Parameters;
	class lb_I_ActionStep_Parameters;
	class lb_I_TestFixture;
	class lb_I_TestMethod;
	class lb_I_CryptoStream;
	class lb_I_DispatchInterceptor;
	class lb_I_ChainingDispatchInterceptor;
	class lb_I_InputStream;
	class lb_I_Applications;
	class lb_I_PluginManager;
	class lb_I_Plugin;

	/*...e*/

	/*...scallback \47\ handler typedefs:0:*/
	/**
	 * This is a base class for all callback able objects
	 */
	///////////////////////////////////////////////////////////////
	// Type for lb protocol callback functions. This should be an interface.
	typedef lbErrCodes (LB_STDCALL lb_I_ProtocolTarget::*lbProtocolCallback)(lb_I_Transfer_Data* , lb_I_Transfer_Data*);
	typedef lbErrCodes (LB_STDCALL lb_I_CallbackTarget::*lbMemberCallback)( const char* handlername, lb_I_Transfer_Data*);



	typedef lbErrCodes (LB_STDCALL lb_I_EventSink::*lb_I_EventCallback)(lb_I_Unknown* question, lb_I_Unknown* answer);


#ifndef TVISION
typedef lbErrCodes (LB_STDCALL lb_I_EventHandler::*lbEvHandler)(lb_I_Unknown* uk);
#endif
#ifdef TVISION
typedef lbErrCodes ( lb_I_EventHandler::*lbEvHandler)(lb_I_Unknown* uk);
#endif

#ifndef TVISION
typedef lbErrCodes (LB_STDCALL lb_I_DispatchInterceptor::*lbInterceptor)(lb_I_Unknown* uk);
#endif
#ifdef TVISION
typedef lbErrCodes ( lb_I_DispatchInterceptor::*lbInterceptor)(lb_I_Unknown* uk);
#endif

	typedef void (LB_STDCALL lb_I_TestFixture::*TestMethod)();

	/*...e*/

	/*
	   CL_LOG("Releasing instance");
	 */
	/*...sdefine RELEASE\40\instance\41\:0:*/
#define RELEASE(instance) \
{ lbErrCodes err; \
	if ((err = instance->release(__FILE__, __LINE__)) != ERR_NONE) { \
		if (err == ERR_REFERENCE_COUNTING ) { \
			_CL_LOG << "RELEASE(...) Reference count mismatch at " << __LINE__ << " in " << __FILE__ LOG_ \
		} else { \
		} \
	} else { \
		instance = NULL; \
	} \
}

	/*...e*/
	/*...sdefine QI\40\source\44\ interface\44\ target\41\:0:*/
#define QI(source, interface, target) \
{ \
	target.setFile(__FILE__); \
	target.setLine(__LINE__); \
	if (source->queryInterface(#interface, (void**) &target, __FILE__, __LINE__) != ERR_NONE) \
	{ \
		_LOGERROR << "QI: Failed to get interface without errors (" << #interface << ")" LOG_ \
	} \
	if (target == NULL) \
	{ \
		_LOGERROR << "QI: Failed to get instance of interface (" << #interface << ")" LOG_ \
	} \
}
	/*...e*/
	/*...e*/

	// UNKNOWN_AUTO_PTR was tested, use it.

#define USE_UAP

	/*...sclass miniLong:0:*/
	class miniLong {
		public:
			miniLong() {
				l = 0;
			}

		miniLong(long _l) {
			l = _l;
		}

		miniLong(const miniLong& _l) {
				l = _l.l;
			}

		virtual ~miniLong() {
		}

		operator long() { return l; }

		miniLong& LB_STDCALL operator = (const long _l) {
			l = _l;
			return *this;
		}

		miniLong& LB_STDCALL operator = (const int _l) {
			l = (long)_l;
			return *this;
		}
		
		miniLong& LB_STDCALL operator ++ () {
			l++;
			return *this;
		}
		
		miniLong& LB_STDCALL operator -- () {
			l--;
			return *this;
		}
		
		miniLong& LB_STDCALL operator ++ (int) {
			l++;
			return *this;
		}
		
		miniLong& LB_STDCALL operator -- (int) {
			l--;
			return *this;
		}
		
		bool LB_STDCALL operator == (const miniLong& _l) const {
			return l == _l.get();
		}

		bool LB_STDCALL operator == (const int _l) const {
			return l == (long)_l;
		}

		bool LB_STDCALL operator == (const long _l) const {
			return l == _l;
		}

		bool LB_STDCALL operator >= (const miniLong& _l) const {
			return l >= _l.get();
		}

		bool LB_STDCALL operator >= (const int _l) const {
			return l >= (long)_l;
		}

		bool LB_STDCALL operator >= (const long _l) const {
			return l >= _l;
		}

		long get() const { return l; }
			void set(long _l) { l = _l; }
			long l;
	};
/*...e*/

/*...sclass miniString:0:*/
class miniString {
	public:
		miniString() {
			ptr = (char*) malloc(1);
			ptr[0] = 0;
		}

		virtual ~miniString() {
			if (ptr) free(ptr);
		}

		char* get() {
			return ptr;
		}

		void set(char const* p) {
			if (p) {
				if (ptr) free(ptr);

				ptr = (char*) malloc(strlen(p)+1);
				ptr[0] = 0;
				strcpy(ptr, p);
			}
		}

	protected:
		char* ptr;
};
/*...e*/

/* setData must check the type of this ! */
/* = may also be possible */
/*...sclass lb_I_Unknown:0:*/


/*...sclass lb_I_Unknown:0:*/
/**
 * \brief Similar to IUnknown aka Microsoft COM.
 *
 * lb_I_Unknown is the base class for all other classes, that are used in the framework.
 * All classes, that needs to be loaded dynamically, must inherid from this class.
 */
class lb_I_Unknown {

public:
	/**
	 * Call this, when you no longer use an instance of any classes, that have
	 * this as a base class.
	 *
	 * This decrements the internal reference counter and if zero, it destroys
	 * it self. The pointer, you have in use, is undefined afterwards. You should set
	 * it to NULL.
	 */
	virtual lbErrCodes LB_STDCALL release(const char* file, int line) = 0;

	/**
	 * This function returns it's location of creation. The creation of this instance
	 * would be set with setModuleManager.
	 */
	virtual char* LB_STDCALL getCreationLoc() const = 0;

	/**
	 * Indicator, to determine, if the instance has no more references.
	 * The instance would be deleted at next release.
	 */
	virtual int LB_STDCALL deleteState() = 0;

	/**
	 * Activate or deactivate debug informations.
	 */
	virtual void LB_STDCALL setDebug(long i) = 0;

	/**
	 * Returns the number of references to this instance.
	 */
	virtual int LB_STDCALL getRefCount() = 0;

	/**
	 * Returns the classname of this instance. It should be a hint to determine
	 * the real type of this instance. This is not a way to determine the interface
	 * of this class. The class in use can provide more than one interface to be used.
	 *
	 * It is not clear, how to implement that.
	 */
	virtual char const* LB_STDCALL getClassName() = 0;

	/**
	 * Query this instance for any interfaces it may support. A real implementation, derived
	 * from this, has a supported interface.
	 *
	 * There is a list interface functionality missing. I do not know, how to implement
	 * this in the macros.
	 *
	 * An idea may be a dummy call to it at any point after instantiation and include code
	 * to register all defined interfaces one per livetime.
	 */
	virtual lbErrCodes LB_STDCALL queryInterface(const char* name, void** unknown, const char* file, int line) const = 0;

	/**
	 * This is an attempt to resolve any dangling references. As yet tried, a release on another
	 * place don't help, because the reference ID would include the place of creation.
	 *
	 * (__FILE__, __LINE__)
	 *
	 * With the help of UAP, it may be possible, because it can hold such an ID for each reference.
	 */
	virtual char const* LB_STDCALL _queryInterface(const char* name, void** unknown, const char* file, int line) = 0;

        /**
         * This was used yet for put an object in a container. After inserting the object
         * into the container, there are two instances (not two references).
         * So the cloning is generaly a good way to make copies of an object.
         *
         * But remark:	The cloned object returned is not the instance in general.
         *		It is the *FIRST* lb_I_Unknown* reference to it.
         *		Putting an object in a container, you have your instance
         *		with the same reference count as before.
         *
         *		The clone() method does not and is not able to make deep clones.
         *		It does not know how !
         *
         *		It creates a new instance with the normal constructor. But it calls
         *		the method setData with the this pointer.
         *		You must provide this method to be able to make a copy of your data.
		 *
         *
         *		return uk;
         */
        virtual lb_I_Unknown* LB_STDCALL clone(const char* file, int line) const = 0;

        /**
         * This member must be implemented by the programmer of each class. setData is called
         * from the clone member to get a correct copy of the cloned instance.
         */
        virtual lbErrCodes LB_STDCALL setData(lb_I_Unknown* u) = 0;

		virtual void LB_STDCALL accept(lb_I_Aspect* v) = 0;//{ v->visit(this); }
	
	virtual void LB_STDCALL traceObject(const char* why, const char* file, int line) const = 0;
};
/*...e*/

class lb_I_TestMethod : public lb_I_Unknown {
public:
	virtual void LB_STDCALL setMethod(lb_I_TestFixture* TestMethodInstance, TestMethod methodFn) = 0;
	virtual void LB_STDCALL call() = 0;
	virtual TestMethod LB_STDCALL getMethod() = 0;
	virtual lb_I_TestFixture* getTestInstance() = 0;

};

/*...sclass lb_I_Requestable:0:*/
/*...sdocu  lb_I_Requestable:0:*/
/**
 * \deprecated Have lb_I_EventHandler for this.
 *
 * lb_I_Requestable is intented to implement a class that can be called
 * for any requests. This may be the 'Meta' Application.
 * The Meta Application did not need to provide an interface for dispatching.
 * This is because, the client of Meta *must* not call any dispatchning -
 * members.
 */
/*...e*/
class lb_I_Requestable {
public:
	virtual lbErrCodes LB_STDCALL initialize() = 0;
	virtual lbErrCodes LB_STDCALL request(const char* request, lb_I_Unknown** result) = 0;
	virtual lbErrCodes LB_STDCALL uninitialize() = 0;
};
/*...e*/

/*...sclass lb_I_Module:0:*/
class lb_I_Module : 
                public lb_I_Unknown,
                public lb_I_Requestable 
{
public:

	virtual char* LB_STDCALL getCreationLoc(const char* addr) = 0;
    virtual void LB_STDCALL notify_create(lb_I_Unknown* that, const char* implName, const char* file = "", int line = 0) = 0;
    virtual void LB_STDCALL notify_add(lb_I_Unknown* that, const char* implName, const char* file, int line) = 0;
    virtual void LB_STDCALL notify_release(lb_I_Unknown* that, const char* implName, const char* file, int line) = 0;
    virtual void LB_STDCALL notify_destroy(lb_I_Unknown* that, const char* implName, const char* file, int line) = 0;

    virtual int  LB_STDCALL can_delete(lb_I_Unknown* that, const char* implName, const char* file = "", int line = 0) = 0;

        /**
         * This function loads a module and stores the modulehandle in an array
         * or a list. If the object is destroyed, the loaded modules are
         * automatically unloaded (the array/list).
         */
        virtual lbErrCodes LB_STDCALL load(const char* name) = 0;

	virtual lbErrCodes LB_STDCALL preload(const char* name) = 0;

	virtual void LB_STDCALL printReferences(const char* addr) = 0;        
        
        /**
         * The module getModuleInstance() is responsible for creating any instances, that are
         * available. This implementation knows that the directory of functors
         * for instances are stored in an XML file (DTD file v1.3).
         *
         * The current implementation for this in the function request is not the
         * intention for the interface lb_I_Requestable.
         *
         * The new function for this may be:
         */


        /**
         * get back a lb_I_String for a functor or a lb_I_Container for a list of
         * them. The errcode helps to decide.
         */
        virtual lbErrCodes LB_STDCALL getFunctors(const char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk) = 0;
        virtual lbErrCodes LB_STDCALL getInstance(const char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk) = 0;
        
        /**
         *
         */
        
        //virtual lbErrCodes getObjectInstance(char* name, lb_I_Requestable*& inst) = 0; 
        virtual lbErrCodes LB_STDCALL getObjectInstance(const char* name, lb_I_Container*& inst) = 0;
        
        virtual lbErrCodes LB_STDCALL makeInstance(const char* functor, const char* module, lb_I_Unknown** instance) = 0;
        
        virtual char* LB_STDCALL getCreationLoc() const = 0;
};
/*...e*/


/*...sAutoPointer:0:*/
/** \def UAP(interface, Unknown_Reference, file, line)
 *  \brief An automatic pointer implementation via macro.
 */

#ifdef MEMTRACK

#define UAP_CHECKPOINTER_INVALID(ptr, msg) \
	if (!_TRMemValidate(ptr)) { \
		char buf[20] = ""; \
		sprintf(buf, "%p", ptr); \
		_LOG << msg << " ( " << buf << ")." LOG_ \
	}
#endif

#ifndef MEMTRACK
#define UAP_CHECKPOINTER_INVALID(ptr, msg)
#endif


#ifdef MEMTRACK
#define UAP_CHECKPOINTER(ptr, msg) \
	if (_TRMemValidate(ptr)) { \
		char buf[20] = ""; \
		sprintf(buf, "%p", ptr); \
		_LOG << msg << " ( " << buf << ")." LOG_ \
	}
#endif

#ifndef MEMTRACK
#define UAP_CHECKPOINTER(ptr, msg)
#endif

#ifndef USE_OLD_UAP

template <typename iface>
class UAPTempl {

		public:
	        UAPTempl() {
	        	_autoPtr = NULL;
	        	_line = __LINE__;
	        	_file = strdup(__FILE__);
	        	attachedClassName = NULL;
	        	allowDelete = 1;
				locked = false;
	        	initialized = false;
		}

		UAPTempl(const UAPTempl& _ref) {
			char const* empty = "";
			attachedClassName = NULL;
			initialized = false;
        	allowDelete = 1;
			locked = false;
			if ((_ref != NULL) && (_ref->getClassName() != NULL))
				attachedClassName = strdup(_ref->getClassName());
			else
				attachedClassName = strdup(empty);
			if (_file != NULL) free(_file);
			_file = NULL;
			if (_ref._file != NULL) {
				_file = (char*) strdup(_ref._file);
			}
			_line = _ref._line;
			_autoPtr = NULL;
		}
		UAPTempl& operator=(const UAPTempl& _ref) {
			if (this == &_ref) return *this;
        	allowDelete = 1;
			locked = false;
			char const* empty = "";
			if (_file != NULL) free(_file);
			_file = NULL;
			if (_ref._file != NULL) {
				_file = (char*) strdup(_ref._file);
			}
			if (attachedClassName) {
				free(attachedClassName);
			}
			initialized = false;
			if ((_ref != NULL) && (_ref->getClassName() != NULL))
			        attachedClassName = strdup(_ref->getClassName());
		        else
	                attachedClassName = strdup(empty);
			_line = _ref._line;
			_autoPtr = _ref._autoPtr;
			return *this;
		}

		virtual ~UAPTempl() {
			if (_autoPtr != NULL) {
				UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Destruct on invalid object pointer")
				if (allowDelete != 1) {
					if (_autoPtr->deleteState() == 1) {
//\todo Report otherwise.
						//if (isLogActivated()) printf("Error: Instance would be deleted, but it's not allowed !!\n");
					}
				}
				if (_line == -1) {
				}
				_autoPtr->release(_file, _line);
				_autoPtr = NULL;
			}
			if (attachedClassName != NULL) free(attachedClassName);
			if (_file) free(_file);
		}
		void LB_STDCALL setFile(char const* __file) {
			if (_file != NULL) {
				free(_file);
			}
			if (__file != NULL) {
				_file = (char*) strdup(__file);
			} else {
//\todo Report otherwise.
//				_CL_LOG << "Error: Setting file parameter is empty! (macro is " << __FILE__ << ", " << __LINE__ LOG_
				_file = strdup(__FILE__);
			}
		}
		void LB_STDCALL setLine(int __line) {
			if (__line == -1) {
//\todo Report otherwise.
//				_CL_LOG << "Error: Setting line parameter is empty! (macro is " << __FILE__ << ", " << __LINE__ LOG_
				_line = __LINE__;
			} else {
				_line = __line;
			}
		}

		iface* LB_STDCALL getPtr() const {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: getPtr() on invalid object pointer")
			return _autoPtr;
		}
		void LB_STDCALL lock() {
			locked = true;
		}
		void LB_STDCALL resetPtr() {
			_autoPtr = NULL;
		}
		void LB_STDCALL setPtr(iface*& source) {
			if (locked) return;
			if (_autoPtr != NULL) {
//\todo Report otherwise.
//				_CL_LOG << "Error: UAP object still initialized!" LOG_
			}
			_autoPtr = source;
		}

		iface& LB_STDCALL operator * () {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator * () on invalid object pointer")
			return *_autoPtr;
		}
		iface* LB_STDCALL operator -> () const {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Operate on invalid object pointer")
			if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) {
					char const* className = _autoPtr->getClassName();
					int len = strlen(className)+1;
					initialized = true;
					if (attachedClassName != NULL) free(attachedClassName);
					attachedClassName = (char*) malloc(len);
					attachedClassName[0] = 0;
				        strcpy(attachedClassName, className);
			}
			return _autoPtr;
		}
		iface* LB_STDCALL operator -> () {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Operate on invalid object pointer")
			if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) {
					char const* className = _autoPtr->getClassName();
					int len = strlen(className)+1;
					initialized = true;
					if (attachedClassName != NULL) free(attachedClassName);
					attachedClassName = (char*) malloc(len);
					attachedClassName[0] = 0;
				        strcpy(attachedClassName, className);
			}
			return _autoPtr;
		}
		UAPTempl& LB_STDCALL operator++(int) {
			lb_I_Unknown* temp = NULL;
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator++ on invalid object pointer")
			_autoPtr->queryInterface((char*) "lb_I_Unknown", (void**) &temp, (char*) __FILE__, __LINE__);
			return *this;
		}
		UAPTempl& LB_STDCALL operator--(int) {
			iface* temp = NULL;
			if (_autoPtr == NULL) return *this;
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator-- on invalid object pointer")
			if (_autoPtr->release((char*) __FILE__, __LINE__) == ERR_RELEASED) _autoPtr = NULL;
			return *this;
		}

		iface ** LB_STDCALL operator & () {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator& on invalid object pointer")
			return &_autoPtr;
		}

		iface* LB_STDCALL operator = (iface* autoPtr) {
			if (*this == autoPtr) return this->_autoPtr;
			if (locked) return this->_autoPtr;
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator = on invalid old object pointer")
			if (_autoPtr != NULL) {
				_autoPtr->release(__FILE__, __LINE__);
			}
			_autoPtr = autoPtr;
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator = on invalid new object pointer")
			if (attachedClassName) {
				free(attachedClassName);
			}
			if ((autoPtr != NULL) && (autoPtr->getClassName() != NULL))
				attachedClassName = strdup(autoPtr->getClassName());
			else
				attachedClassName = strdup("");
			return this->_autoPtr;
		}
		int LB_STDCALL operator == (const iface* b) const {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator == on invalid object pointer")
			return _autoPtr == b;
		}
		int LB_STDCALL operator == (const UAPTempl& b) const {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator == on invalid object pointer")
			return *this == b;
		}
		int LB_STDCALL operator != (const iface* b) const {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator != on invalid object pointer")
			return _autoPtr != b;
		}
		void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; }
		
		protected:
	        iface* _autoPtr;
	        mutable int _line;
	        mutable char* _file;
	        mutable int allowDelete;
	        mutable bool initialized;
		mutable bool locked;
	        mutable char* attachedClassName;
		};

#define UAPDECL(classname) \
typedef UAPTempl<classname> UAP##classname;

UAPDECL(lb_I_Unknown)
UAPDECL(lb_I_CallbackTarget)
UAPDECL(lb_I_ProtocolTarget)

UAPDECL(lb_I_String)

UAPDECL(lb_I_gcManager)
UAPDECL(lb_I_Unknown)
UAPDECL(lb_I_Module)

UAPDECL(lb_I_Event)
UAPDECL(lb_I_EventSink)

UAPDECL(lb_I_Dispatcher)
UAPDECL(lb_I_EventManager)
UAPDECL(lb_I_EventHandler)

UAPDECL(lb_I_ConfigObject)

UAPDECL(lb_I_Frame)
UAPDECL(lb_I_Transfer_Data)

	// Base interface for visitors
UAPDECL(lb_I_Aspect)

UAPDECL(lb_I_VisitableHelper)
UAPDECL(lb_I_Streamable)
UAPDECL(lb_I_Integer)
UAPDECL(lb_I_Long)
UAPDECL(lb_I_Container)
UAPDECL(lb_I_Database)
UAPDECL(lb_I_Connection)
UAPDECL(lb_I_ColumnBinding)
UAPDECL(lb_I_BoundColumn)
UAPDECL(lb_I_KeyBase)
UAPDECL(lb_I_Query)
UAPDECL(lb_I_MVC_View)
UAPDECL(lb_I_InterfaceRepository)
UAPDECL(lb_I_Element)
UAPDECL(lb_I_FunctorEntity)
UAPDECL(lb_I_InstanceReference)
UAPDECL(lb_I_FileOperation)
UAPDECL(lb_I_OutputStream)
UAPDECL(lb_I_Locale)
UAPDECL(lb_I_Parameter)
UAPDECL(lb_I_Log)
UAPDECL(lb_I_Window)
UAPDECL(lb_I_wxFrame)
UAPDECL(lb_I_MasterDetailFormDefinition)
UAPDECL(lb_I_DatabaseReport)
UAPDECL(lb_I_Project)
UAPDECL(lb_I_Stream)
UAPDECL(lb_I_CodeGenerator)
UAPDECL(lb_I_ProjectManager)
UAPDECL(lb_I_GUIApp)
UAPDECL(lb_I_LogonPage)
UAPDECL(lb_I_AppSelectPage)
UAPDECL(lb_I_LogonHandler)
UAPDECL(lb_I_DatabaseOperation)
UAPDECL(lb_I_Document)
UAPDECL(lb_I_Socket)
UAPDECL(lb_I_Transfer_DataObject)
UAPDECL(lb_I_Transfer)
UAPDECL(lb_I_ThreadImplementation)
UAPDECL(lb_I_Column_Types)
UAPDECL(lb_I_Formular_Fields)
UAPDECL(lb_I_FixedDatabaseForm)
UAPDECL(lb_I_DBReportTextblock)
UAPDECL(lb_I_DBReportProperties)
UAPDECL(lb_I_DirLocation)
UAPDECL(lb_I_Action_Parameters)
UAPDECL(lb_I_ActionStep_Parameters)
UAPDECL(lb_I_TestFixture)
UAPDECL(lb_I_TestMethod)
UAPDECL(lb_I_CryptoStream)
UAPDECL(lb_I_DispatchInterceptor)
UAPDECL(lb_I_ChainingDispatchInterceptor)
UAPDECL(lb_I_InputStream)
UAPDECL(lb_I_Applications)
UAPDECL(lb_I_PluginManager)
UAPDECL(lb_I_Plugin)

		
#define UAP(classname, variable) \
	UAP##classname variable;

#endif

#ifdef USE_OLD_UAP

#define UAP(interface, Unknown_Reference) \
		class UAP##Unknown_Reference { \
\
		public: \
	        UAP##Unknown_Reference() { \
	        	_autoPtr = NULL; \
	        	_line = __LINE__; \
	        	_file = strdup(__FILE__); \
	        	attachedClassName = NULL; \
	        	allowDelete = 1; \
				locked = false; \
	        	initialized = false; \
		} \
		\
		UAP##Unknown_Reference(const UAP##Unknown_Reference& _ref) { \
			char const* empty = ""; \
			attachedClassName = NULL; \
			initialized = false; \
        	allowDelete = 1; \
			locked = false; \
			if ((_ref != NULL) && (_ref->getClassName() != NULL)) \
				attachedClassName = strdup(_ref->getClassName()); \
			else \
				attachedClassName = strdup(empty); \
			if (_file != NULL) free(_file); \
			_file = NULL; \
			if (_ref._file != NULL) { \
				_file = (char*) strdup(_ref._file); \
			} \
			_line = _ref._line; \
			_autoPtr = NULL; \
		} \
		UAP##Unknown_Reference& operator=(const UAP##Unknown_Reference& _ref) { \
			if (this == &_ref) return *this; \
        	allowDelete = 1; \
			locked = false; \
			char const* empty = ""; \
			if (_file != NULL) free(_file); \
			_file = NULL; \
			if (_ref._file != NULL) { \
				_file = (char*) strdup(_ref._file); \
			} \
			if (attachedClassName) { \
				free(attachedClassName); \
			} \
			initialized = false; \
			if ((_ref != NULL) && (_ref->getClassName() != NULL)) \
			        attachedClassName = strdup(_ref->getClassName()); \
		        else \
	                attachedClassName = strdup(empty); \
			_line = _ref._line; \
			_autoPtr = _ref._autoPtr; \
			return *this; \
		} \
		\
		virtual ~UAP##Unknown_Reference() { \
			if (_autoPtr != NULL) { \
				UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Destruct on invalid object pointer") \
				if (allowDelete != 1) { \
					if (_autoPtr->deleteState() == 1) { \
						if (isLogActivated()) printf("Error: Instance would be deleted, but it's not allowed !!\n"); \
					} \
				} \
				if (_line == -1) { \
				} \
				_autoPtr->release(_file, _line); \
				_autoPtr = NULL; \
			} \
			if (attachedClassName != NULL) free(attachedClassName); \
			if (_file) free(_file); \
		} \
		void LB_STDCALL setFile(char const* __file) { \
			if (_file != NULL) { \
				free(_file); \
			} \
			if (__file != NULL) { \
				_file = (char*) strdup(__file); \
			} else { \
				_CL_LOG << "Error: Setting file parameter is empty! (macro is " << __FILE__ << ", " << __LINE__ LOG_ \
				_file = strdup(__FILE__); \
			} \
		} \
		void LB_STDCALL setLine(int __line) { \
			if (__line == -1) { \
				_CL_LOG << "Error: Setting line parameter is empty! (macro is " << __FILE__ << ", " << __LINE__ LOG_ \
				_line = __LINE__; \
			} else { \
				_line = __line; \
			} \
		} \
		\
		interface* LB_STDCALL getPtr() const { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: getPtr() on invalid object pointer") \
			return _autoPtr; \
		} \
		void LB_STDCALL lock() { \
			locked = true; \
		} \
		void LB_STDCALL resetPtr() { \
			_autoPtr = NULL; \
		} \
		void LB_STDCALL setPtr(interface*& source) { \
			if (locked) return; \
			if (_autoPtr != NULL) { \
				_CL_LOG << "Error: UAP object still initialized!" LOG_ \
			} \
			_autoPtr = source; \
		} \
		\
		interface& LB_STDCALL operator * () { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator * () on invalid object pointer") \
			return *_autoPtr; \
		} \
		interface* LB_STDCALL operator -> () const { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Operate on invalid object pointer") \
			if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) { \
					char const* className = _autoPtr->getClassName(); \
					int len = strlen(className)+1; \
					initialized = true; \
					if (attachedClassName != NULL) free(attachedClassName); \
					attachedClassName = (char*) malloc(len); \
					attachedClassName[0] = 0; \
				        strcpy(attachedClassName, className); \
			} \
			return _autoPtr; \
		} \
		interface* LB_STDCALL operator -> () { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Operate on invalid object pointer") \
			if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) { \
					char const* className = _autoPtr->getClassName(); \
					int len = strlen(className)+1; \
					initialized = true; \
					if (attachedClassName != NULL) free(attachedClassName); \
					attachedClassName = (char*) malloc(len); \
					attachedClassName[0] = 0; \
				        strcpy(attachedClassName, className); \
			} \
			return _autoPtr; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator++(int) { \
			interface* temp = NULL; \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator++ on invalid object pointer") \
			_autoPtr->queryInterface((char*) #interface, (void**) &temp, (char*) __FILE__, __LINE__); \
			return *this; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator--(int) { \
			interface* temp = NULL; \
			if (_autoPtr == NULL) return *this; \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator-- on invalid object pointer") \
			if (_autoPtr->release((char*) __FILE__, __LINE__) == ERR_RELEASED) _autoPtr = NULL; \
			return *this; \
		} \
		interface ** LB_STDCALL operator & () { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator& on invalid object pointer") \
			return &_autoPtr; \
		} \
		\
		interface* LB_STDCALL operator = (interface* autoPtr) { \
			if (*this == autoPtr) return this->_autoPtr; \
			if (locked) return this->_autoPtr; \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator = on invalid old object pointer") \
			if (_autoPtr != NULL) { \
				_autoPtr->release(__FILE__, __LINE__); \
			} \
			_autoPtr = autoPtr; \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator = on invalid new object pointer") \
			if (attachedClassName) { \
				free(attachedClassName); \
			} \
			if ((autoPtr != NULL) && (autoPtr->getClassName() != NULL)) \
				attachedClassName = strdup(autoPtr->getClassName()); \
			else \
				attachedClassName = strdup(""); \
			return this->_autoPtr; \
		} \
		int LB_STDCALL operator == (const interface* b) const { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator == on invalid object pointer") \
			return _autoPtr == b; \
		} \
		int LB_STDCALL operator == (const UAP##Unknown_Reference& b) const { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator == on invalid object pointer") \
			return *this == b; \
		} \
		int LB_STDCALL operator != (const interface* b) const { \
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator != on invalid object pointer") \
			return _autoPtr != b; \
		} \
		void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; } \
		\
		protected: \
	        interface* _autoPtr; \
	        mutable int _line; \
	        mutable char* _file; \
	        mutable int allowDelete; \
	        mutable bool initialized; \
		mutable bool locked; \
	        mutable char* attachedClassName; \
		}; \
	\
        UAP##Unknown_Reference Unknown_Reference;

#endif
		
// Probably unused.
//interface* _UAP##Unknown_Reference;


/*...sbla \40\geht nicht\41\:0:*/
#ifdef bla
#define UNKNOWN_AUTO_PTR(interface, Unknown_Referene) \
	interface* Unknown_Referene = NULL; \
	UAP UAP##Unknown_Referene((lb_I_Unknown**) &Unknown_Referene);
#endif
/*...e*/
/*...e*/

/*...sREQUEST Use this for a predefined UAP\46\:0:*/
// Use this for a predefined UAP. It will automatically deleted, if scope is gone.

/** \def REQUEST(mm, interface, variable)
 *  \brief Requester macro for getting an instance of given interface.
 *
 *  Makes it simpler to instantiate any kint of object.
 */

#define REQUEST(mm, interface, variable) \
	requestHelper(mm, #interface, (void**)&variable, __FILE__, __LINE__);
/*
  	UAP(lb_I_Unknown, uk##variable) \
  	mm->request(#interface, &uk##variable); \
  	if (uk##variable != NULL) { \
	  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
		uk##variable.setFile(__FILE__); \
		uk##variable.setLine(__LINE__); \
	} else { \
	_LOG << "Error: REQUEST macro failure!" LOG_ \
	} \

*/	
	
/** \def DEBUG_REQUEST(mm, interface, variable)
 *  \brief Requester macro for getting an instance of given interface.
 *  Makes it simpler to instantiate any kint of object. Debug version.
 */

#define DEBUG_REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable) \
	printf("Step 1\n"); \
  	mm->request(#interface, &uk##variable); \
	printf("Step 2\n"); \
	printf("Step 3\n"); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
	printf("Step 4\n"); \
	uk##variable.setFile(__FILE__); \
	printf("Step 5\n"); \
	uk##variable.setLine(__LINE__);

/*...e*/

/*...sUAP_REQUEST Use this for an stack like environment\46\:0:*/
// Use this for an stack like environment. It will automatically deleted, if scope is gone.

/** \def UAP_REQUEST(mm, interface, variable)
 *  \brief Variable and instantiation of any interface.
 *  This is usefull in functions, if the object should automatically
 *  destroyed, if the scope is left.
 */

#define UAP_REQUEST(mm, interface, variable) \
		lbErrCodes err##variable = ERR_NONE; \
		UAP(lb_I_Unknown, uk##variable) \
		UAP(interface, variable) \
		err##variable = mm->request(#interface, &uk##variable); \
		if (err##variable == ERR_MODULE_NO_INTERFACE) { \
			_CL_LOG << "Error: Interface '" << #interface << "' not defined. Check if this is an implementation error or wrong module version." LOG_ \
		} else if (err##variable == ERR_MODULE_NOT_FOUND) { \
			_CL_LOG << "Error: Module for interface '" << #interface << "' could not be loaded or was not found." LOG_ \
		} else { \
			uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
		}

/*...e*/

/*...sSTATIC_REQUEST\40\mm\44\ interface\44\ variable\41\:0:*/
/** \def STATIC_REQUEST(mm, interface, variable)
 *  \brief Non automatic destroying variant of UAP_REQUEST. This could be used to return the created instance over their interface.
 */
#define STATIC_REQUEST(mm, interface, variable) \
  	lb_I_Unknown* uk##variable; \
  	mm->request(#interface, &uk##variable); \
  	_CL_LOG << "STATIC_REQUEST: Have an instance" LOG_ \
  	interface* variable; \
  	_CL_LOG << "STATIC_REQUEST: Set module manager" LOG_ \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__);

/*...e*/

/*...sDECLARE_LB_UNKNOWN\40\\41\:0:*/
/** \def DECLARE_LB_UNKNOWN() To be used in any interface implementation.
 *  This has to be used for each class definition, when deriving from lb_I_Unknown.
 */
#define DECLARE_LB_UNKNOWN() \
public: \
	lbErrCodes 	LB_STDCALL release(const char* file, int line); \
	char*           LB_STDCALL getCreationLoc() const; \
	int 		LB_STDCALL deleteState(); \
	void 		LB_STDCALL setDebug(long i) { debug_macro = i; } \
	int 		LB_STDCALL getRefCount() { return ref; } \
	char const*	LB_STDCALL getClassName(); \
	lbErrCodes 	LB_STDCALL queryInterface(const char* name, void** unknown, const char* file, int line) const; \
	char const*	LB_STDCALL _queryInterface(const char* name, void** unknown, const char* file, int line); \
	lb_I_Unknown* 	LB_STDCALL clone(const char* file, int line) const; \
	lbErrCodes 	LB_STDCALL setData(lb_I_Unknown* u); \
	void		LB_STDCALL accept(lb_I_Aspect* v) { \
	    if (v == NULL) {\
			_LOG << "Error: Accept method couldn't forward with a NULL pointer." LOG_\
	    } else { \
		    v->visit(this);\
		} \
	} \
	void 		LB_STDCALL resetRefcount(); \
	void		LB_STDCALL traceObject(const char* why, const char* file, int line) const; \
protected: \
	mutable miniLong	ref; \
	mutable miniLong	debug_macro; \
	mutable miniLong	instance_counted; \
	mutable miniString	lastQIFile; \
	mutable miniLong	lastQILine; \
	mutable miniString	lastSMFile; \
	mutable miniLong	lastSMLine; \
public:

/*...e*/

/*...sBEGIN_IMPLEMENT_LB_UNKNOWN:0:*/
/** \def BEGIN_IMPLEMENT_LB_UNKNOWN Implements the memberfunctions of lb_I_Unknown.
 *  This must be used to begin the interface declaration of your class.
 *  It implements the mechanisms of the component system.
 */

#define BEGIN_IMPLEMENT_LB_UNKNOWN(classname) \
char const* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
void LB_STDCALL classname::traceObject(const char* why, const char* file, int line) const { \
\
_LOGALWAYS << #classname << "::traceObject(" << why << ", " << file << ", " << line << ") called: References = " << ref LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastQIFile = " << lastQIFile.get() LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastQILine = " << lastQILine.get() LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastSMFile = " << lastQIFile.get() LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastSMLine = " << lastQILine.get() LOG_ \
\
} \
char const* LB_STDCALL classname::_queryInterface(const char* name, void** unknown, const char* file, int line) { \
	char* ID = (char*) malloc(strlen(name)+strlen(#classname)+strlen(file)+1); \
	ID[0] = 0; \
	strcat(ID, name); \
	strcat(ID, #classname); \
	strcat(ID, file); \
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		_CL_LOG <<"Error: queryInterface failed (in _queryInterface)!" LOG_ \
		free(ID); \
		return ""; \
	} \
	\
	return ID; \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = 0; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == 0) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	return strdup("getCreationLoc not supported."); \
} \
lbErrCodes LB_STDCALL classname::release(const char* file, int line) { \
	char ptr[20] = ""; \
	sprintf(ptr, "%p", this); \
	if (_TRMemValidate(this)) { \
		if (debug_macro == 1) { \
			_LOG << #classname << "::release(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
		} else {\
			_CL_VERBOSE << #classname << "::release(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
		} \
		ref--; \
		if (ref == 0) { \
			_CL_VERBOSE << "Info: Instance released: " << #classname << "(" << ptr << "). Instances: " << ref.get() LOG_ \
			_CL_VERBOSE << "Delete instance '" << #classname << "'" LOG_ \
			delete this; \
			_CL_VERBOSE << "Deleted" LOG_ \
			return ERR_RELEASED; \
		} \
		else { \
			if (ref > 0) { \
				_CL_VERBOSE << "Info: Instance released: " << #classname << "(" << ptr << "). Instances: " << ref.get() LOG_ \
			} else { \
				if (isLogActivated()) printf("Error: Instance %s has been deleted prior!\n", #classname); \
				_CL_LOG << "Error: Instance has been deleted prior: " << #classname LOG_ \
			} \
		} \
		return ERR_NONE; \
	} \
	if (ref < 0) { \
		_CL_LOG << "Error: Reference count of instance " << ptr << " in last query interface " << \
		lastQIFile.get() << " at " << lastQILine << \
		" of object type " << #classname << " is less than " << 0 << " (" << ref << ") !!!" LOG_ \
		return ERR_REFERENCE_COUNTING; \
	} else { \
		char buf[20] = ""; \
		sprintf(buf, "%p", this); \
		_LOG << "Error: Instance " << buf << " of object type " << #classname << " was deleted prior (At: " << file << ":" << line << ") !!!" LOG_ \
	} \
	return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(const char* file, int line) const { \
\
	if (debug_macro == 1) { \
		_LOG << #classname << "::clone(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
	} else { \
		_CL_VERBOSE << #classname << "::clone(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
	} \
	classname* cloned = new classname(); \
	cloned->setDebug(debug_macro); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting interface" LOG_ \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting unknown interface of cloned object" LOG_ \
	} \
\
	if (uk->getRefCount() > 1) { \
		if (debug_macro == 1) { \
			_LOG << "Cloned object of type " << uk->getClassName() << " has " << uk->getRefCount() << " references" LOG_ \
		} else { \
			_CL_LOG << "Cloned object of type " << uk->getClassName() << " has " << uk->getRefCount() << " references" LOG_ \
		} \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(const char* name, void** unknown, const char* file, int line) const { \
	char _classname[100] = #classname; \
	lastQIFile.set(file); \
	lastQILine = line; \
	if (debug_macro == 1) { \
		_LOG << #classname << "::queryInterface(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
	} else { \
		_CL_VERBOSE << #classname << "::queryInterface(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
	} \
	\
	if (instance_counted.get() != 112233) { \
		instance_counted.set(112233); \
		InstanceCount(1); \
	} \
	if (unknown == NULL) { \
		_CL_LOG << "Error: Got NULL pointer reference while queryInterface() called for " << \
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_ \
	} \
\
	if (strcmp(name, "lb_I_Unknown") == 0) { \
		if (ref < 0) { \
			_CL_LOG << "Reference count error in queryInterface (" #classname ")" LOG_ \
		} \
		ref++; \
		*unknown = (lb_I_Unknown*) this; \
\
		if (*unknown != (void*) this) { \
			TRMemSetPointerValid(*unknown, (void*) this); \
		} \
		return ERR_NONE; \
	}

/*...e*/
/*...sBEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN:0:*/
/** \def BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN Implements the memberfunctions of lb_I_Unknown.
 *  This must be used to begin the interface declaration of your class.
 *  It implements the mechanisms of the component system.
 *
 *  This could be used, if only one instance should be used per process.
 */

#define BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(classname) \
char const* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
void LB_STDCALL classname::traceObject(const char* why, const char* file, int line) const { \
\
_LOGALWAYS << #classname << "::traceObject(" << why << ", " << file << ", " << line << ") called: References = " << ref LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastQIFile = " << lastQIFile.get() LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastQILine = " << lastQILine.get() LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastSMFile = " << lastQIFile.get() LOG_ \
_LOGALWAYS << #classname << "::traceObject(): lastSMLine = " << lastQILine.get() LOG_ \
\
} \
char const* LB_STDCALL classname::_queryInterface(char const* name, void** unknown, char const* file, int line) { \
	char* ID = (char*) malloc(strlen(name)+strlen(#classname)+strlen(file)+1); \
	ID[0] = 0; \
	strcat(ID, name); \
	strcat(ID, #classname); \
	strcat(ID, file); \
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		_CL_LOG <<"Error: queryInterface failed (in _queryInterface)!" LOG_ \
		free(ID); \
		return ""; \
	} \
	\
	return ID; \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = 0; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == 0) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	sprintf(buf, "%p", (void*) this); \
	return strdup("getCreationLoc() not supported."); \
} \
lbErrCodes LB_STDCALL classname::release(char const* file, int line) { \
	if (_TRMemValidate(this)) { \
        ref--; \
		char ptr[20] = ""; \
		sprintf(ptr, "%p", this); \
	\
        if (ref == 0) { \
			ref++; \
        	return ERR_NONE; \
        } \
        if (ref < 0) { \
        	if (isLogActivated()) printf("Error: Reference count of instance %p of object type %s is less than %d (%d) !!!", ptr, #classname, 0, ref.get()); \
        	return ERR_REFERENCE_COUNTING; \
        } \
        } else { \
        	if (isLogActivated()) printf("Error: Instance %p of object type %s was deleted prior !!!", this, #classname); \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(const char* file, int line) const { \
\
	classname* cloned = new classname(); \
	cloned->setDebug(debug_macro); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting interface" LOG_ \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting unknown interface of cloned object" LOG_ \
	} \
\
	if (uk->getRefCount() > 1) { \
		_CL_LOG << "Cloned object has %d references" << uk->getRefCount() LOG_ \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char const* name, void** unknown, char const* file, int line) const { \
	char _classname[100] = #classname; \
	if (unknown == NULL) { \
		_CL_LOG << "Error: Got NULL pointer reference while queryInterface() called for " << \
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_ \
	} \
\
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < 0) { \
        		_CL_LOG << "Reference count error in queryInterface (" #classname ")" LOG_ \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (*unknown != (void*) this) { \
                        TRMemSetPointerValid(*unknown, (void*) this); \
                } \
                return ERR_NONE; \
        }

/*...e*/

/** \def ADD_INTERFACE Adds support for a specific interface.
 *  This could be used multiple times for having more than one interface.
 */
#define ADD_INTERFACE(interfaceName) \
        if (strcmp(name, #interfaceName) == 0) { \
                ref++; \
                *unknown = (interfaceName*) this; \
                if (*unknown != (void*) this) { \
                        TRMemSetPointerValid(*unknown, (void*) this); \
                } \
                return ERR_NONE; \
        }

#define END_IMPLEMENT_LB_UNKNOWN() \
	_CL_VERBOSE << "Error: Requested interface '" << name << "' not found! File: " << file << " Line: " << line LOG_ \
	return ERR_NO_INTERFACE; \
}

/*...e*/

/*...sstandard functor:0:*/
/**
 * Base of all instances - the functor
 */

extern "C" {
typedef lbErrCodes (LB_FUNCTORCALL *T_pLB_GET_UNKNOWN_INSTANCE) (lb_I_Unknown**, lb_I_Module* m, const char* file, int line);
}

/** \def DECLARE_FUNCTOR Declares a functor in a header file.
 * This must be used once per class.
 *
 * Idea: To ensure, that the object gets the module manager, it is locked until
 * setModuleManager is called with a correct value.
 * queryInterface can at first time do it's work, store the data, that has to
 * be stored in module manager and lock the instance for further use.
 */

#define DECLARE_FUNCTOR(name) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, const char* file, int line); \
}

/** \def IMPLEMENT_FUNCTOR Implements the functor in a cpp file.
 * Use this once per class.
 */
#define IMPLEMENT_FUNCTOR(name, clsname) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, const char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
	clsname* instance = new clsname(); \
	if (!_TRMemValidate(instance)) { \
		_LOG << "Error: Functor " << #name << " doesn't use TRMem's operator new !" LOG_ \
	} \
        *uk = NULL; \
        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
                _CL_LOG << "Failed to create unknown reference to instance of " << \
                #clsname << ". Errcode is " << err LOG_ \
                if (err == ERR_STATE_FURTHER_LOCK) { \
                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
                	return err; \
                } \
                return ERR_FUNCTOR; \
        } \
\
        return ERR_NONE; \
} \
}

/** \def DECLARE_SINGLETON_FUNCTOR Declares a singleton functor in a header file.
 * This must be used once per class.
 */
#define DECLARE_SINGLETON_FUNCTOR(name) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, const char* file, int line); \
}

/** \def IMPLEMENT_SINGLETON_FUNCTOR Implements the singleton functor in a cpp file.
 * Use this once per class.
 */
#define IMPLEMENT_SINGLETON_FUNCTOR_BASE(name, clsname) \
class singletonHolder_##name { \
public: \
	singletonHolder_##name() { \
		_CL_VERBOSE << "singletonHolder_" << #name << "() called." LOG_ \
		singleton = NULL; \
	} \
	virtual ~singletonHolder_##name() { \
		_CL_VERBOSE << "~singletonHolder_" << #name << "() called." LOG_ \
		destroy(); \
		_CL_VERBOSE << "~singletonHolder_" << #name << "() leaving." LOG_ \
	} \
	void destroy() { \
		if (singleton != NULL) { \
			if (_TRMemValidate(singleton)) { \
				printf("Information: singletonHolder_" #name " will be destroyed now.\n"); \
				delete singleton; \
				singleton = NULL; \
				printf("Information: singletonHolder_" #name " is destroyed now.\n"); \
			} \
			else \
				/*if (isLogActivated())*/ printf("ERROR: Sinleton object has been deleted prior!\n"); \
		} else { \
			/*if (isLogActivated())*/ printf("Warning: singletonHolder_" #name " was not used yet.\n"); \
		} \
	} \
	void set(clsname* _singleton) { \
		lb_I_Unknown* temp; \
		lbErrCodes err = ERR_NONE; \
		err = _singleton->queryInterface("lb_I_Unknown", (void**) &temp, __FILE__, __LINE__); \
		singleton = _singleton; \
	} \
	\
	clsname* get() { \
		return singleton; \
	} \
	\
	clsname* singleton; \
}; \
\
singletonHolder_##name singleton_##name; \
\
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, const char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
	if (singleton_##name.get() == NULL) { \
	        clsname* instance = new clsname(); \
			if (!_TRMemValidate(instance)) { \
				_LOG << "Error: Singleton functor " << #name << " doesn't use TRMem's operator new !" LOG_ \
			} \
	        *uk = NULL; \
	        char buf[100] = ""; \
	        track_Object(instance, "IMPLEMENT_SINGLETON_FUNCTOR - Instantiating"); \
	        \
	        singleton_##name.set(instance); \
	        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
	                _CL_LOG << "Failed to create unknown reference to singleton instance of " << \
	                #clsname << ". Errcode is " << err LOG_ \
	                if (err == ERR_STATE_FURTHER_LOCK) { \
	                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
	                	return err; \
	                } \
	                return ERR_FUNCTOR; \
	        } \
        } else { \
	        track_Object(singleton_##name.get(), "IMPLEMENT_SINGLETON_FUNCTOR - queryInterface()"); \
	        if ((err = singleton_##name.get()->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
	                _CL_LOG << "Failed to create unknown reference to singleton instance of " << \
	                #clsname << ". Errcode is " << err LOG_ \
	                if (err == ERR_STATE_FURTHER_LOCK) { \
	                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
	                	return err; \
	                } \
	                return ERR_FUNCTOR; \
	        } \
        } \
\
        return ERR_NONE; \
} \
}

#ifdef LINUX
#define IMPLEMENT_SINGLETON_FUNCTOR(name, clsname) \
IMPLEMENT_SINGLETON_FUNCTOR_BASE(name, clsname) \
extern "C" { \
__attribute__((constructor)) \
static void constructor_##name() { \
	printf("Constructor for singleton object 'singleton_%s' called.\n", #name); \
} \
__attribute__((destructor)) \
static void destructor_##name() { \
	printf("Destructor for singleton object 'singleton_%s' called.\n", #name); \
	if (singleton_##name.get() != NULL) { \
		printf("Destruct instance 'singleton_%s'.\n", #name); \
		singleton_##name.destroy(); \
	} \
} \
}
#endif
#ifndef LINUX
#define IMPLEMENT_SINGLETON_FUNCTOR(name, clsname) \
IMPLEMENT_SINGLETON_FUNCTOR_BASE(name, clsname)
#endif

/*...e*/


#define DECLARE_TESTFIXTURE() \
void LB_STDCALL addTestMethod(TestMethod methodFn, const char* _testname); \
void LB_STDCALL registerTests(); \
void LB_STDCALL setUp(); \
void LB_STDCALL tearDown(); \
void LB_STDCALL runTest(); \
private: \
UAP(lb_I_Container, TestMethods)

#define BEGIN_IMPLEMENT_TESTFIXTURE(TF) \
class TestMethod##TF : public lb_I_TestMethod { \
public: \
	TestMethod##TF(); \
	virtual ~TestMethod##TF(); \
	void LB_STDCALL setMethod(lb_I_TestFixture* TestMethodInstance, TestMethod methodFn); \
	TestMethod LB_STDCALL getMethod(); \
	lb_I_TestFixture* getTestInstance(); \
	void LB_STDCALL call(); \
\
	DECLARE_LB_UNKNOWN() \
\
protected: \
	lb_I_TestFixture* instance; \
	TestMethod m_testmethod; \
}; \
\
BEGIN_IMPLEMENT_LB_UNKNOWN(TestMethod##TF) \
	ADD_INTERFACE(lb_I_TestMethod) \
END_IMPLEMENT_LB_UNKNOWN() \
lbErrCodes LB_STDCALL TestMethod##TF::setData(lb_I_Unknown* uk) { \
	lbErrCodes err = ERR_NONE; \
	UAP(lb_I_TestMethod, test) \
	QI(uk, lb_I_TestMethod, test) \
	if (test != NULL) { \
		m_testmethod = test->getMethod(); \
		instance = test->getTestInstance(); \
	} \
	return ERR_NOT_IMPLEMENTED; \
} \
TestMethod##TF::TestMethod##TF() { \
	instance = NULL; \
	ref = 0; \
} \
TestMethod##TF::~TestMethod##TF() { \
\
} \
TestMethod LB_STDCALL TestMethod##TF::getMethod() { \
	return m_testmethod; \
} \
lb_I_TestFixture* TestMethod##TF::getTestInstance() { \
	return instance; \
} \
void TestMethod##TF::setMethod(lb_I_TestFixture* TestMethodInstance, TestMethod methodFn) { \
	instance = TestMethodInstance; \
	m_testmethod = methodFn; \
} \
void TestMethod##TF::call() { \
	if (instance) (instance->*(TestMethod) m_testmethod) (); \
} \
\
void LB_STDCALL TF::addTestMethod(TestMethod methodFn, const char* _testname) { \
	lbErrCodes err = ERR_NONE; \
	UAP_REQUEST(getModuleInstance(), lb_I_String, testname) \
	UAP(lb_I_KeyBase, tmkey) \
	UAP(lb_I_Unknown, ukMethod) \
	*testname = _testname; \
	QI(testname, lb_I_KeyBase, tmkey) \
	UAP(lb_I_TestMethod, m) \
	TestMethod##TF* method = new TestMethod##TF(); \
	QI(method, lb_I_TestMethod, m) \
	m->setMethod(this, methodFn); \
	QI(m, lb_I_Unknown, ukMethod) \
	TestMethods->insert(&ukMethod, &tmkey); \
} \
void LB_STDCALL TF::runTest() { \
	lbErrCodes err = ERR_NONE; \
	TestMethods->finishIteration(); \
	while (TestMethods->hasMoreElements() == 1) { \
		UAP(lb_I_TestMethod, m) \
		UAP(lb_I_Unknown, uk) \
		uk = TestMethods->nextElement(); \
		QI(uk, lb_I_TestMethod, m) \
		if (m != NULL) { \
			m->call(); \
		} \
	} \
} \
void LB_STDCALL TF::registerTests() { \
	if (TestMethods == NULL) { \
		REQUEST(getModuleInstance(), lb_I_Container, TestMethods) \
	} else { \
		TestMethods--; \
		TestMethods.resetPtr(); \
		REQUEST(getModuleInstance(), lb_I_Container, TestMethods) \
	}



#define END_IMPLEMENT_TESTFIXTURE() }

#define ADD_TEST(TestName) addTestMethod((TestMethod) &lbTest::TestName, #TestName);
// Hack to avoid mixing two test implementations
#ifndef TEST_FIXTURE
#define TEST_CASE(testcase) void LB_STDCALL testcase();
#endif

/*...sclass lb_I_Reference:0:*/
/**
 * \brief This should be a class to be used as a 'smart' pointer.
 *
 * Currently I use the UAP macros as smart pointer implementations.
 * The UAP solution has no base class. This would be one, but it would
 * bite it self indirectly into the whife.
 *
 * This is because UAP is a 'normal' class. It can't and shouldn't be created by the lbDMF system.
 *
 * If it could be created by REQUEST, the UAP_REQUEST macro - requesting an instance for a particular
 * interface - must also request the base class of it self to have the UAP class.
 */
#ifndef _MSC_VER
class lb_I_Reference : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL set(lb_I_Unknown* r) = 0;
	virtual lbErrCodes LB_STDCALL get(lb_I_Unknown*& r) = 0;
};
#endif
/*...e*/

/*...sclass lb_I_gcManager:0:*/
/**
 * \brief An attempt to create garbage collection classes.
 */
class lb_I_gcManager {
protected:
	lb_I_gcManager() {}
	virtual ~lb_I_gcManager() {}

public:
	virtual lbErrCodes toTrash(lb_I_Unknown * inst) = 0;
};
/*...e*/

// What about exceptions ?

/*...sclass lb_I_Exception:0:*/
/**
 * \brief An attempt for exceptions.
 */
class lb_I_Exception {
public:
	virtual lbErrCodes getMessage(char*& msg) = 0;
};
/*...e*/
/*...sclass lb_I_ErrorDescription:0:*/
/**
 * \brief An attempt for error descriptions.
 */
class lb_I_ErrorDescription {// Every interface may produce errors
public:
	virtual lbErrCodes getLastError(char* description, int len) = 0;
};
/*...e*/

class lb_I_DispatchFunction : public lb_I_Unknown {
public:

	/// Store the function handler.
	virtual lbErrCodes LB_STDCALL setFunction(const char* service, lb_I_CallbackTarget* handlerInstance, lbMemberCallback fn) = 0;

	/// Get the protocol callback function.
	virtual lbMemberCallback LB_STDCALL getFunction() = 0;

	/// Get the protocol handler instance.
	virtual lb_I_CallbackTarget* LB_STDCALL getHandlerInstance() = 0;
};

/*...sclass lb_I_CallbackManager:0:*/
/** \brief An attempt for registering callbacks.
 */
class lb_I_CallbackManager {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in your class implementing callback handling
	 */


/*...e*/
	virtual lbErrCodes LB_STDCALL addCallbackHandler(const char* handlername, lbMemberCallback cbFn) = 0;
	virtual lbErrCodes LB_STDCALL delCallbackHandler(const char* handlername) = 0;
};
/*...e*/
/*...sclass lb_I_CallbackDispatcher dispatches over names:0:*/
/** \brief An attempt to dispatch a request.
 */
class lb_I_CallbackDispatcher {
public:
	virtual lbErrCodes LB_STDCALL dispatch(const char* request, lb_I_Transfer_Data* result) = 0;
};
/*...e*/
/*...sclass lb_I_CallbackTarget:0:*/
/** \brief An attempt to let classes register their callbacks.
 */
class lb_I_CallbackTarget : public lb_I_Unknown {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in the derived class for your functions
	 * to be called back.
	 */

/*...e*/
	virtual lbErrCodes LB_STDCALL registerCallbacks() = 0;
};
/*...e*/

/*...sclass lb_I_DispatchProtocol:0:*/
/** \brief Class to hold a protocol based handler.
 */
class lb_I_DispatchProtocol : public lb_I_Unknown {
public:

	/// Store the protocol handler.
	virtual lbErrCodes LB_STDCALL setProto(const char* service, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback fn) = 0;

	virtual char* LB_STDCALL getServiceName() = 0;
	
	/// Get the protocol callback function.
	virtual lbProtocolCallback LB_STDCALL getProto() = 0;

	/// Get the protocol handler instance.
	virtual lb_I_ProtocolTarget* LB_STDCALL getProtocolHandlerInstance() = 0;
};
/*...e*/

/*...sdocu:0:*/
/**
 * This interface must be used to register or deregister
 * protocol callbacks, if an implementation is a callback target.
 */

/*...e*/
/*...sclass lb_I_ProtocolManager:0:*/
/** \brief An attempt for a protocol based callback manager.
 */
class lb_I_ProtocolManager {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in your class implementing callback handling
	 */


/*...e*/
	virtual lbErrCodes LB_STDCALL addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback cbFn) = 0;
	virtual lbErrCodes LB_STDCALL delProtocolHandler(const char* handlername) = 0;
};
/*...e*/
/*...sclass lb_I_ProtocolDispatcher dispatches over protocol haeder:0:*/
/** \brief An attempt for a protocol based dispatcher.
 */
class lb_I_ProtocolDispatcher {
public:
	virtual lbErrCodes LB_STDCALL dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) = 0;
};
/*...e*/
/*...sdocu:0:*/
/**
 * This is used by a server instance, that implements some protocols.
 */
/*...e*/
/*...sclass lb_I_ProtocolTarget:0:*/
/** \brief An attempt for a protocol based callback handler.
 */
class lb_I_ProtocolTarget : public lb_I_Unknown {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in the derived class for your functions
	 * to be called back.
	 */

/*...e*/
	/** \brief The service for these protocols.
	 * Each protocol target class could define the service name, under which
	 * they should be reachable.
	 *
	 * The service name could be overwritten to use another service.
	 */
	virtual char* LB_STDCALL getServiceName() = 0;
	virtual lbErrCodes LB_STDCALL registerProtocols(lb_I_ProtocolManager* protoMgr, const char* serverInstance) = 0;
};
/*...e*/

class lb_I_ApplicationServer :
	public lb_I_ProtocolManager,
	public lb_I_ProtocolDispatcher,
	public lb_I_ProtocolTarget {
public:
	virtual bool LB_STDCALL isConnected(lb_I_Transfer_Data* request) = 0;
	virtual lbErrCodes LB_STDCALL waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* request) = 0;
	virtual lbErrCodes LB_STDCALL answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result) = 0;

	virtual void LB_STDCALL autostartServerPlugins(bool start) = 0;
	virtual lbErrCodes LB_STDCALL activateServerPlugin(const char* name) = 0;
	virtual void LB_STDCALL run() = 0;
};

class lb_I_ApplicationClient :
	public lb_I_Unknown,
	//public lb_I_Requestable,
	public lb_I_CallbackManager,
	public lb_I_CallbackDispatcher {


};
/*...sclass lb_I_EventConnector:0:*/
/** \brief ???
 */
class lb_I_EventConnector {
public:
	virtual lbErrCodes LB_STDCALL getConnectorEventList(lb_I_Container* c) = 0;
};
/*...e*/
/*...sclass lb_I_EventSource:0:*/
/// A Menu ??
class lb_I_EventSource {
public:
	virtual lbErrCodes LB_STDCALL getSourceEventList(lb_I_Container* c) = 0;
};
/*...e*/
/*...sclass lb_I_EventSink:0:*/
/// A Frame ??
class lb_I_EventSink {
public:
	virtual lb_I_EventCallback LB_STDCALL getEventFunction(const char* name) = 0;
	virtual lbErrCodes LB_STDCALL Connect(const char* evName, lb_I_EventCallback evFn) = 0;
	virtual lbErrCodes LB_STDCALL getSinkEventList(lb_I_Container* c) = 0;

	/**
	 * The events are compareable, that is, the connector says the same events
	 * than the sink. If that is so, then the registration will succeed.
	 *
	 * But what is about the event source. When and where are these created ?
	 */
	virtual lbErrCodes LB_STDCALL registerEvents(lb_I_EventConnector* object) = 0;

	/**
	 * This function will be called in the scope of application initializion.
	 * That is in an instance of lb_I_EventConnector. This instance says wich
	 * events should be implemented. This events are registered before and then
	 * the event source can be made.
	 */
	virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object) = 0;
	virtual lb_I_Unknown* LB_STDCALL getEventsource(lb_I_EventConnector* object) = 0;

};
/*...e*/

/*...sclass lb_I_EventMapper:0:*/
/// ???
class lb_I_EventMapper : public lb_I_Unknown {
public:
	/**
	 * If handler is NULL, then the event manager knows, that the requesting
	 * instance has a dispatcher and therefore handles it self. You must register
	 * the dispatcher after all requested id's for your events.
	 */
	virtual lbErrCodes LB_STDCALL setEvent(const char* name, lbEvHandler handler = NULL) = 0;
	/**
	 * Get the id back.
	 */
	virtual int LB_STDCALL getID() = 0;

protected:
	virtual char* LB_STDCALL getName() = 0;
	virtual void LB_STDCALL setID(int id) = 0;

	friend class lb_I_EventManager;
};
/*...e*/

//	virtual lbErrCodes LB_STDCALL setDiapatcher(lb_I_Dispatcher* disp) = 0;
//	virtual lb_I_Dispatcher* LB_STDCALL getDispatcher() = 0;

/*...sclass lb_I_EventManager:0:*/
/**
 * \brief An event ID manager. It reserves ID's for symbolic event names.
 *
 * This is used to create event ID numbers, that - for sample - are used in my
 * GUI sample application. wxWidgets usually defines those ID's per define. Here,
 * I am capable to manage those ID's dynamically.
 *
 * You are able to write a plugin module and insert menu entries dynamically to
 * the wx application and let the app resolve that event ID correctly to the module
 * by forwarding all those events to a OnDispatch handler. This handler forwards
 * the event to my own event handling mechanism.
 *
 * This does not interfer the two different mechanisms of wx and my own.
 *
 * \note A class of this interface must be singleton.
 */
class lb_I_EventManager : public lb_I_Unknown {
public:

	/**
	 * Register a symbolic event name and get back their ID.
	 * \param EvName The symbolic name of the event. This could be a #define EVENTXY "eventXY".
	 * \param EvNr The ID, generated inside of this implementation.
	 */
	virtual lbErrCodes LB_STDCALL registerEvent(const char* EvName, int & EvNr) = 0;

	/**
	 * Get the ID of a registered symbolic event name. Parameters as above described.
	 */
	virtual lbErrCodes LB_STDCALL resolveEvent(const char* EvName, int & evNr) = 0;

	virtual char* LB_STDCALL reverseEvent(int evNr) = 0;
	
	/**\brief Used by the dispatcher in detachInstance
	 */
	virtual lbErrCodes LB_STDCALL unregisterEvent(const char* EvName) = 0;

protected:

	friend class lb_I_Dispatcher;
};
/*...e*/

// Activate interceptor code
#define IMPLEMENT_NEWSTUFF

/*...sclass lb_I_EvHandler:0:*/
/**
 * \brief An event handler entity.
 *
 * An event handler entity is an instance for a class, that has one or more event handlers.
 */
class lb_I_EvHandler : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler) = 0;
	virtual lbEvHandler LB_STDCALL getHandler() = 0;
	virtual lb_I_EventHandler* LB_STDCALL getHandlerInstance() = 0;

	/** \brief Call the registered handler.
	 * If the boolean flag hasDefinedInterceptor is true, the call will fail if no interceptor is registered.
	 */
	virtual lbErrCodes LB_STDCALL call(lb_I_Unknown* evData, lb_I_Unknown** evResult, bool hasDefinedInterceptor = false) = 0;

#ifdef IMPLEMENT_NEWSTUFF
	virtual lb_I_DispatchInterceptor* getInterceptor() = 0;
	virtual lbInterceptor LB_STDCALL getBeforeInterceptor() = 0;
	virtual lbInterceptor LB_STDCALL getAfterInterceptor() = 0;

	// Forwarded functions.
	virtual lbErrCodes LB_STDCALL setInterceptor(lb_I_DispatchInterceptor* evHandlerInstance, lbInterceptor evHandler_Before, lbInterceptor evHandler_After) = 0;
	virtual lbErrCodes LB_STDCALL delInterceptor() = 0;

	virtual lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_Unknown* interceptedInstance) = 0;

	/** \brief Implements execution of hook functions.
	 *
	 * Hooks, that are executed before could cancel the call to the dispatched function.
	 * The following error codes should be implemented:
	 *
	 * ERR_HOOK_BEFORE_CANCEL			Cancel the dispatch call and return.
	 * ERR_HOOK_BEFORE_FAILURENOTICE	Returns a value in the result parameters with name 'failurenotice' and a value with name 'failurecode'.
	 */
	virtual lbErrCodes LB_STDCALL executeInterceptorBefore(lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;

	/** \brief Implements execution of hook functions.
	 *
	 * Hooks, that are executed before could cancel the call to the dispatched function.
	 * The following error codes should be implemented:
	 *
	 * ERR_HOOK_BEFORE_FAILURENOTICE	Returns a value in the result parameters with name 'failurenotice' and a value with name 'failurecode'.
	 */
	virtual lbErrCodes LB_STDCALL executeInterceptorAfter(lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;

	virtual void LB_STDCALL setInterceptorRequired(bool _required) = 0;
#endif


};
/*...e*/
/*...sclass lb_I_EventHandler:0:*/
/**
 * \brief An event handler class. It handles one or more events.
 *
 * The event handler registers all it's handlers by get a call of registerEventHandler.
 * It get's an external dispatcher, to don't need to provide it's own dispatcher.
 */
class lb_I_EventHandler {
public:
	/**
	 * Register all the handlers by this class to the given dispatcher.
	 */
	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp) = 0;
	/**
	 * This function is added to avoid diamond shaped class hirachies.
	 */

	virtual lb_I_Unknown* LB_STDCALL getUnknown() = 0;
};
/*...e*/

/** \brief Helper interface that makes non visitable classes visitable.
 * A non visitable class is for sample a pure event handler, that forwards
 * the events to other instances of other classes.
 *
 * The interface has no other usage than to have a name in the visitors visit method.
 */
class lb_I_VisitableHelper : public lb_I_Unknown {
	
};

/*...sclass lb_I_DispatchRequest:0:*/
/**
 * \brief An attempt to create a request packet, that could be predefined.
 *
 * Idea: You do not need to build up a more complex event every time. Predefine
 * it as a class and instantiate it over REQUEST or directly and use it later.
 */
class lb_I_DispatchRequest : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL setRequestName(const char* name) = 0;
};
/*...e*/
/*...sclass lb_I_DispatchResponce:0:*/
/**
 * \brief An attempt to create a request packet response, that could be predefined.
 *
 * Idea: You do not need to build up a more complex response every time. Predefine
 * it as a class and instantiate it over REQUEST or directly at start time and use it later.
 */
class lb_I_DispatchResponse : public lb_I_Unknown {
public:
	virtual int LB_STDCALL isOk() = 0;
};
/*...e*/
/*...sclass lb_I_Dispatcher:0:*/
/**
 * \brief Dispatcher contains all registered event handlers.
 *
 * Dispatcher is used to hold all registered event handlers. If an event has been fired,
 * one of it's dispatch members are called to forward that event to the desired handler.
 */
class lb_I_Dispatcher : public lb_I_Unknown {
public:
	/**
	 * Set an event manager. Dispatcher stores the handlers per event ID's. It needs
	 * a manager, if it gets a symbolic event, to resolve the ID.
	 *
	 * \param EvManager The event manager.
	 */
	virtual lbErrCodes LB_STDCALL setEventManager(lb_I_EventManager* EvManager) = 0;

/*...sevent handler management:8:*/

	/**
	 * Register an event handler function under it's name. If the name is not registered, the
	 * function will fail. The dispatcher is not responsible for registering event names or id's.
	 */
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName) = 0;

	/**
	 * \brief Remove an event handler.
	 */
	virtual lbErrCodes LB_STDCALL delEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, const char* EvName) = 0;

	/**
	 * Register an event handler function under it's id. If the id is not registered, the
	 * function will fail. The dispatcher is not responsible for registering event names or id's.
	 */
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) = 0;
/*...e*/

/*...scascade management:8:*/
	/**
	 * Add a dispatcher, if it is not my self (singleton). This enables cascaded
	 * dispatching and complete replacement of a dispatcher.
	 *
	 * You could forward events to a separate dispatcher, if the main dispatcher
	 * does not contain the registered handler. So a group of handlers could be
	 * replaced by some context of an application.
	 *
	 * Sample: Some event handlers goes to a remote host due to some extend.
	 * The separate dispatcher is build up and the remote handlers are also
	 * build up before replacing a local decentand.
	 */
	virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp) = 0;

	/**
	 * Delete a decentand dispatcher.
	 *
	 * \note You must implement thread savetiness in your replace code.
	 *
	 * \param disp Deprecated. Why holding more than one decentand dispatcher ?
	 */
	virtual lbErrCodes LB_STDCALL delDispatcher(lb_I_Dispatcher* disp) = 0;
/*...e*/

/*...sdispatching:8:*/
	/**
	 * Any dispatch function should provided with the information of what type to be dispatched.
	 * An input is required - possibly NULL.
	 * A result will be generated, if succeeded.
	 *
	 */
	virtual lbErrCodes LB_STDCALL dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;
	virtual lbErrCodes LB_STDCALL dispatch(const char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;

	/**
	 * lb_I_DispatchRequest variant. Parameter contains all needed data for the dispatch request.
	 */
	virtual lb_I_DispatchResponse* LB_STDCALL dispatch(lb_I_DispatchRequest* req) = 0;

#ifdef IMPLEMENT_NEWSTUFF
	// Using the interceptor pattern at this place as it is simple to intercept all dynamic fnctionality.
	virtual lbErrCodes LB_STDCALL setInterceptor(lb_I_DispatchInterceptor* evHandlerInstance, lbInterceptor evHandler_Before, lbInterceptor evHandler_After, const char* EvName) = 0;
	virtual lbErrCodes LB_STDCALL delInterceptor(const char* EvName) = 0;

	//virtual lbErrCodes LB_STDCALL activateInterceptor(char* EvName, lb_I_EvHandler* ev) = 0;

	/** \brief Remove an intercepted instance.
	 * This is needed when a window is closed. The window has to call this function to remove the instance from the list of intercepted instances.
	 * Otherwise - at least on wxWidgets - the instance pointer gets dangling and leads to crashes.
	 */
	virtual lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_String* EvName, lb_I_Unknown* interceptedInstance) = 0;

	/** \brief Get the list of interceptors to store anywhere.
	 * This function is used to store the information of to be used interceptors.
	 * The list is a string representation and may be encrypted.
	 */
	virtual lb_I_String* LB_STDCALL getInterceptorDefinitions() = 0;

	/** \brief Set the list of interceptors to be used.
	 * The list is a string representation and may be encrypted.
	 */
	virtual lbErrCodes LB_STDCALL setInterceptorDefinitions(lb_I_String* s) = 0;
#endif

	/**
	 * Removes all event handlers from a given instance. Use this function if you
	 * want to reinstantiate a class that registers event handlers and the old gets
	 * destroyed.
	 */
	virtual void LB_STDCALL detachInstance(lb_I_EventHandler* evHandlerInstance) = 0;
/*...e*/
};
/*...e*/

class lb_I_DispatchInterceptor : public lb_I_Unknown {
public:
	/** \brief Describes the purpose of this interceptor.
	 * The designer should be able to optain information about what interceptors he / she could activate.
	 */
	virtual lb_I_String* LB_STDCALL getDescription() = 0;
	/** \brief Get the vendor name.
	 * Interceptors are typically vendor extensions to be hooked into basic functionalities such as permission handling.
	 */
	virtual lb_I_String* LB_STDCALL getVendorName() = 0;

	/** \brief Initialize and activate the interceptor.
	 * Call this function to register the interceptor to the dispatcher.
	 *
	 * \note If this is done in the designer and the plugin later is not deployed, then the dispatcher will cancel related events.
	 */
	virtual lbErrCodes LB_STDCALL initialize() = 0;

	/** \brief Enables access to the intercepted object.
	 * Due to the possibility to register multiple instances for one event (with a prefix of the instance pointer to lb_I_EventHandler type as string),
	 * the correct intercepted instance must be looked up by the instance pointer as string (key).
	 *
	 * The interceptor must cope with the correct type conversion to what the interceptor should act.
	 */
	virtual lbErrCodes LB_STDCALL addInterceptedInstance(lb_I_Unknown* intercepted) = 0;

	virtual lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_Unknown* interceptedInstance) = 0;
};

class lb_I_ChainingDispatchInterceptor : public lb_I_DispatchInterceptor {

};

class lb_I_DatabaseForm;
class lb_I_GUI;
class lb_I_Form;

/*...sclass lb_I_Frame:0:*/
/**
 * It seems, that this is the factory class for any GUI elements. It also knows about any instance.
 */
class lb_I_Frame :
public lb_I_Unknown
{
public:
//	virtual lb_I_Unknown* LB_STDCALL createFrame() = 0;
};
/*...e*/
/*...sclass lb_I_Application:0:*/
/**
 * \brief Interface for a delegated application.
 *
 * This inteface is used when the implementation of an lb_I_MetaApplication
 * loads an application and delegates the control to it. This would be done
 * by a call to loadApplication in lb_I_MetaApplication.
 */
class lb_I_Application : public lb_I_Unknown {
public:

	/**
	 * Set the graphical user interface instance that is the wrapper side.
	 */
	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* gui) = 0;

	/** \brief Set the user for the current application.
	 */
	virtual lbErrCodes LB_STDCALL setUserName(const char* user) = 0;

	/** \brief Set the application name for the current application.
	 */
	virtual lbErrCodes LB_STDCALL setApplicationName(const char* app) = 0;

    /** \brief Enable directly callable save.
     */
	virtual lbErrCodes LB_STDCALL save() = 0;

    /** \brief Enable directly callable load.
     */
	virtual lbErrCodes LB_STDCALL load() = 0;

	/**
	 * Initialize the application module. Optionally, provide user and application name.
	 */
	virtual lbErrCodes LB_STDCALL initialize(const char* user = NULL, const char* app = NULL) = 0;

	/** \brief Cleanup.
	 *
	 * This function must be called before uncontrolled destructor calls are done.
	 * It ensures a clean application exit proccess.
	 */
	virtual lbErrCodes LB_STDCALL uninitialize() = 0;

	/**
	 * \brief Run the application
	 *
	 * This lets the GUI 'start' some threads in the background or run the app without
	 * a GUI.
	 */
	virtual lbErrCodes LB_STDCALL run() = 0;

	/**
	 * \brief Get the GUI instance.
	 */
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** gui) = 0;

	virtual lbErrCodes LB_STDCALL getUserName(lb_I_String** user) = 0;
	virtual lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app) = 0;

	/**
	 * Get access to the main event manager, so all parts can initialize event handlers
	 * and then initialize Actors for still initialized event handlers.
	 */
	virtual lb_I_EventManager* LB_STDCALL getEVManager() = 0;

};
/*...e*/

/** \brief A simulated application can be used to automate tasks.
 * This interface is mainly intented for automated unit tests who interact with an user interface.
 * The automated task didn't need an user sitting on a computer to always click the same menus and answer the same questions.
 * The automated task can be setup with a set of answers done automatically and thus enables unatended tasks done in unit tests.
 *
 * As an additional feature, it may be implemented a generic event handling answering mechanism.
 */
class lb_I_SimulatedApplication : public lb_I_Application {
public:
	/** \brief Answer to a yes or no question.
	 * The answer is specified by the what parameter. The last parameter indicated end of record for answers.
	 * The last answer in a set must be flagged with last = true. No second set can and should be recorded.
	 */
	virtual void LB_STDCALL addAnswer(char* what, bool last) = 0;
	
	/** \brief Answer with a filename.
	 * The askOpenFileReadStream memberfunction in lb_I_MetaApplication can be automated to answer by what.
	 */
	virtual void LB_STDCALL setFileAnswer(char* what) = 0;
};

/*...slbDMF ORM:0:*/
/*...sclass lb_I_MetaApplication:0:*/
/**
 * \brief Interface from a wrapper and lbDMF
 *
 * The meta application is an attempt to provide an interface for the
 * application developer. It hides the real framework like MFC or others
 * from the developer.
 */
class lb_I_MetaApplication : public lb_I_Unknown {
public:

	/** \brief Save the object.
	 *
	 * This is not a replacement for private save(lb_I_XXXStream*).
	 * It is here, because this interface doesn't make all the internal
	 * data public. Thus a visitor is unable to save the whole data.
	 *
	 * To avoid external handling how to save the data, this function comes
	 * into play.
	 */
	virtual lbErrCodes LB_STDCALL save() = 0;

	/** \brief Load the object.
	 *
	 * See save for detailed description.
	 */
	virtual lbErrCodes LB_STDCALL load() = 0;

	/**
	 * Set the graphical user interface instance that is the wrapper side.
	 */
	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* gui) = 0;

	/** \brief Set user name.
	 * Set the user name. The user name is the login name in the database if lbDMF is used.
	 */
	virtual lbErrCodes LB_STDCALL setUserName(const char* user) = 0;

	/** \brief Set application name.
	 * The application name must be configured in the database and must point to a module
	 * (DLL/so) containing an interface with this name: lb_I_Application.
	 */
	virtual lbErrCodes LB_STDCALL setApplicationName(const char* app) = 0;


	/** \brief Set automatic loading of SQL data after update.
	 */
	virtual void	   LB_STDCALL setAutorefreshData(bool b) = 0;

	/** \brief Store information about maximized GUI.
	 *
	 */
	virtual void	   LB_STDCALL setGUIMaximized(bool b) = 0;

	/** \brief Get information about maximized GUI.
	 *
	 */
	virtual bool	   LB_STDCALL getGUIMaximized() = 0;

	/** \brief Set automatic loading of application.
	 * The easiest login procedure.
	 */
	virtual void	   LB_STDCALL setAutoload(bool b) = 0;

	/** \brief Set automatic selection of application.
	 * This would be used to help the login procedure to be easier.
	 */
	virtual void	   LB_STDCALL setAutoselect(bool b) = 0;

	/** \brief Set automatic loading of SQL data after update.
	 */
	virtual bool	   LB_STDCALL getAutorefreshData() = 0;

	/** \brief Get automatic loading of application.
	 * The easiest login procedure.
	 */
	virtual bool	   LB_STDCALL getAutoload() = 0;

	/** \brief Get automatic selection of application.
	 * This would be used to help the login procedure to be easier.
	 */
	virtual bool	   LB_STDCALL getAutoselect() = 0;

	/** \brief Base directory for files.
	 * This parameter is for setup the base directory for files needed by meta application.
	 */
	virtual char*	   LB_STDCALL getDirLocation() = 0;

	/** \brief Base directory for files.
	 * This parameter is for setup the base directory for files needed by meta application.
	 */
	virtual void	   LB_STDCALL setDirLocation(const char* dirloc) = 0;

	/** \brief Initialize the class.
	 * Initialize the application module. Optionally, provide user and application name.
	 * This function loads also some plugins if available. Thus it should be uninitialized
	 * before exit. This is due to the singleton instance implementation.
	 */
	virtual lbErrCodes LB_STDCALL initialize(const char* user = NULL, const char* app = NULL) = 0;

	/** \brief Uninitialize the class.
	 * After uninitialisation, the class shouldn't used any more.
	 */
	virtual lbErrCodes LB_STDCALL uninitialize() = 0;

	/**
	 * \brief Run the application
	 *
	 * This lets the GUI 'start' some threads in the background or run the app without
	 * a GUI.
	 */
	virtual lbErrCodes LB_STDCALL run() = 0;

	/**
	 * \brief Get the GUI instance.
	 */
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** gui) = 0;

	/** \brief Get the current user name.
	 *
	 */
	virtual lbErrCodes LB_STDCALL getUserName(lb_I_String** user) = 0;

	/** \brief Get the current application name.
	 *
	 */
	virtual lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app) = 0;

	/**
	 * Get access to the main event manager, so all parts can initialize event handlers
	 * and then initialize Actors for still initialized event handlers.
	 */
	virtual lb_I_EventManager* getEVManager() = 0;

	/** \brief Load target application.
	 *
	 * Used to load given application with user's rights.
	 */
	virtual lbErrCodes LB_STDCALL loadApplication(const char* user, const char* app) = 0;

	/** \brief Unload any loaded application.
	 */
	virtual lbErrCodes LB_STDCALL unloadApplication() = 0;
	/*
	 * Basic functions to be used for a UI application
	 */

	/// \brief Add a toolbar to the main window.
	virtual lbErrCodes LB_STDCALL addToolBar(const char* toolbarName) = 0;

	/// \brief Remove a toolbar to the main window.
	virtual lbErrCodes LB_STDCALL removeToolBar(const char* toolbarName) = 0;

	/// \brief Add or insert a tool to the toolbar.
	virtual lbErrCodes LB_STDCALL addToolBarButton(const char* toolbarName, const char* entry, const char* evHandler, const char* toolbarimage, const char* afterentry = NULL) = 0;

	/// \brief Remove a tool from the toolbar.
	virtual lbErrCodes LB_STDCALL removeToolBarButton(const char* toolbarName, const char* entry) = 0;

	/// \brief Activate or deactivate a tool.
	virtual lbErrCodes LB_STDCALL toggleToolBarButton(const char* toolbarName, const char* entry) = 0;

	/** Add a menubar name after.
	 */
	virtual lbErrCodes LB_STDCALL addMenuBar(const char* name, const char* after = NULL) = 0;

	/** Add a menu.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(const char* name) = 0;

	/** Add menu entry.
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry = NULL) = 0;

	/** Add a checkable menu entry.
	 *
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntryCheckable(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry = NULL) = 0;

	virtual lbErrCodes LB_STDCALL removeMenuBar(const char* name) = 0;
	virtual lbErrCodes LB_STDCALL removeMenuEntry(const char* in_menu, const char* entry) = 0;

	/** \brief Enable a given event.
	 *
	 */
	virtual lbErrCodes LB_STDCALL enableEvent(const char* name) = 0;

	/** \brief Disable a given event.
	 *
	 */
	virtual lbErrCodes LB_STDCALL disableEvent(const char* name) = 0;

	/** \brief Toggle a given event.
	 *
	 */
	virtual lbErrCodes LB_STDCALL toggleEvent(const char* name) = 0;

	/** Add a button.
	 */
	virtual lbErrCodes LB_STDCALL addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h) = 0;

	/** Add a label.
	 */
	virtual lbErrCodes LB_STDCALL addLabel(const char* text, int x, int y, int w, int h) = 0;

	/** Add a text field.
	 */
	virtual lbErrCodes LB_STDCALL addTextField(const char* name, int x, int y, int w, int h) = 0;

	/** \brief Ask the user for a file by given extention.
	 */
	virtual lb_I_InputStream* LB_STDCALL askOpenFileReadStream(const char* extentions) = 0;

	/** \brief Ask the user for YES or NO.
	 */
	virtual bool LB_STDCALL askYesNo(const char* msg) = 0;

	/** \brief Show a simple message box.
	 */
	virtual void LB_STDCALL msgBox(const char* title, const char* msg) = 0;

	virtual void LB_STDCALL addStatusBar() = 0;

	virtual void LB_STDCALL addStatusBar_TextArea(const char* name) = 0;

	virtual void LB_STDCALL setStatusText(const char* name, const char* value, bool call_yield = true) = 0;

	// Hack to avoid crash when the window close button is pressed. Used in OnExit in dynamic.cpp.
	virtual void LB_STDCALL disableStatusbar() = 0;

	/** \brief Let the GUI show the given parameters in a property panel.
	 *
	 */
	virtual lbErrCodes LB_STDCALL showPropertyPanel(lb_I_Parameter* params, bool update = false) = 0;

	/** \brief Register a handler for change events of parametes.
	 *
	 * Each parameter has a name and therefore could be used for events. In combination with the group name, the event name
	 * would be unique and could be dispatched correctly to the given handler. The handler could reverse the event name and
	 * figure out which value has been changed.
	 */
	virtual lbErrCodes LB_STDCALL registerPropertyChangeEventGroup(const char* name, lb_I_Parameter* params, lb_I_EventHandler* target, lbEvHandler handler) = 0;

	/** \brief Access to the object's parameters.
	 *
	 */
	virtual lb_I_Parameter* LB_STDCALL getParameter() = 0;


	/** \brief Login to the application.
	 *
	 * See description of addUserAccount.
	 */
	virtual bool LB_STDCALL login(const char* user, const char* pass) = 0;

	/** \brief get a list of applications.
	 *
	 * This function builds a list of application based on the user rights.
	 */
	virtual lb_I_Container* LB_STDCALL getApplications() = 0;

	/** \brief Get the ID of an application.
	 *
	 */
	virtual long LB_STDCALL getApplicationID() = 0;

	/** \brief Set the active application.
	 */
	virtual void			LB_STDCALL setActiveApplication(const char* name) = 0;

	/** \brief Get the active document.
	 * Active document per loaded application.
	 */
	virtual lb_I_Unknown*		LB_STDCALL getActiveDocument() = 0;

	/** \brief Set the active document.
	 * Active document per loaded application.
	 */
	virtual void			LB_STDCALL setActiveDocument(lb_I_Unknown* doc) = 0;

	/** \brief Set PropertyPane layout to floating.
	 *
	 */
	virtual void			LB_STDCALL setPropertyPaneLayoutFloating() = 0;
	virtual void			LB_STDCALL setPropertyPaneLayoutLeft() = 0;
	virtual bool			LB_STDCALL isPropertyPaneLayoutFloating() = 0;
	virtual bool			LB_STDCALL isPropertyPaneLayoutLeft() = 0;

	virtual void			LB_STDCALL showPropertyPanel() = 0;

	virtual lb_I_Applications* LB_STDCALL getApplicationModel() = 0;

	/** \brief Set loading of application from database.
	 */
	virtual void	   LB_STDCALL setLoadFromDatabase(bool b) = 0;
	virtual bool	   LB_STDCALL getLoadFromDatabase() = 0;

	/** \brief Add a set of properties to be stored in file.
	 *
	 * This could be used for temporary storage of variable data.
	 */
	virtual void	LB_STDCALL addPropertySet(lb_I_Parameter* properties, const char* setname) = 0;

	/** \brief Delete a set of properties.
	 *
	 * This could be used to remove property sets again.
	 */
	virtual void			LB_STDCALL delPropertySet(const char* setname) = 0;

	virtual lb_I_Parameter*	LB_STDCALL getPropertySet(const char* setname, bool copy = false) = 0;

	/** \brief Gets a directory from user.
	 *
	 * The user gets a directory chooser dialog and should provide with that information.
	 */
	virtual bool			LB_STDCALL askForDirectory(lb_I_DirLocation* loc) = 0;

	/** \brief Returns the system database backend name.
	 *
	 * If the name is empty, the internal database wrapper is used as configured in code.
	 * This is usually the lbDB module.
	 *
	 * This parameter is for using on the system configuration. To distinguish from application
	 * database backend, whose purpose is for the designed application.
	 */
	virtual char*			LB_STDCALL getSystemDatabaseBackend() = 0;

	/** \brief Returns the application database backend name.
	 *
	 * If the name is empty, the internal database wrapper is used as configured in code.
	 * This is usually the lbDB module.
	 */
	virtual char*			LB_STDCALL getApplicationDatabaseBackend() = 0;

	/** \brief Set a different system database backend.
	 */
	virtual void			LB_STDCALL setSystemDatabaseBackend(const char* backend) = 0;

	/** \brief Set a different application database backend.
	 */
	virtual void			LB_STDCALL setApplicationDatabaseBackend(const char* backend) = 0;

	/** \brief Use a different system database backend.
	 */
	virtual void			LB_STDCALL useSystemDatabaseBackend(bool backend) = 0;

	/** \brief Use a different application database backend.
	 */
	virtual void			LB_STDCALL useApplicationDatabaseBackend(bool backend) = 0;

	/** \brief Use a different system database backend.
	 */
	virtual bool			LB_STDCALL usingSystemDatabaseBackend() = 0;

	/** \brief Use a different application database backend.
	 */
	virtual bool			LB_STDCALL usingApplicationDatabaseBackend() = 0;

	/** \brief Change a property value.
	 *
	 * This function is used to change property values from within source code.
	 * Primary use would be property setup or testing purposes.
	 */
	virtual void			LB_STDCALL firePropertyChangeEvent(const char* name, const char* value) = 0;

	/** \brief Fire an event.
	 *
	 */
	virtual void			LB_STDCALL fireEvent(const char* name) = 0;

	/** \brief Set the name of the process.
	 * The user of this library should pass the process name.
	 */
	virtual void			LB_STDCALL setProcessName(const char* name) = 0;

	/** \brief Get the name of the process.
	 * The user of this library could expect a valid name while initialize is called.
	 * Thus the application should set it properly before initialisation.
	 */
	virtual lb_I_String*	LB_STDCALL getProcessName() = 0;
};
/*...e*/

/*...sclass lb_I_UserAccounts:0:*/
class lb_I_UserAccounts : public lb_I_Unknown {
public:
	/** \brief Add an user account and get it's ID.
	 *
	 * This function only works, when a super user has already logged in.
	 * If there is no such user and no database available, the current user
	 * id would be used for a local super user.
	 *
	 * The database's stored super user has more priority over the local.
	 * Locally logged in super users didn't get access to the user accounts
	 * in the database. So if the database is back any how, the user must
	 * login to the database's super user.
	 *
	 * If the passwords are inconsistent and the database is available again,
	 * the user must login arain to the database's user.
	 *
	 * If all that is ok, the super user could transfer the users to the local
	 * copy of users.
	 *
	 * Any better solutions ?
	 *
	 * Parameters:
	 *
	 *		_id would be automatically generated, if no third parameter is given.
	 *		This is the case, when the new entry would be added from user interaction and
	 *		later stored in the database.
	 *
	 *		It would be the best to directly store the new entry in the database and retrieve
	 *		the id for furter linking of applications to users.
	 *
	 * Returns -1, if given id exists (then repeat without that id).
	 * Returns -2, if user exists.
	 */
	virtual long		LB_STDCALL addAccount(const char* _user, const char* _pass, long _id = -1) = 0;

	/** \brief Select current user.
	 *
	 * Direct access by the given login name.
	 */
	virtual bool		LB_STDCALL selectAccount(const char* _user) = 0;

	/** \brief Select current user.
	 *
	 * Direct access by the given user number.
	 */
	virtual bool		LB_STDCALL selectAccount(long user_id) = 0;

	/** \brief Get the number of users.
	 */
	virtual long		LB_STDCALL getUserCount() = 0;

	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreUsers() = 0;

	/** \brief Iterate to next user.
	 */
	virtual void		LB_STDCALL setNextUser() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishUserIteration() = 0;

	/** \brief Get current user name (iteration).
	 */
	virtual char*		LB_STDCALL getUserName() = 0;

	/** \brief Get current user id.
	 */
	virtual long		LB_STDCALL getUserID() = 0;

	/** \brief Get current user password.
	 */
	virtual char*		LB_STDCALL getUserPassword() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Applications:0:*/
class lb_I_Applications : public lb_I_Unknown {
public:
	/** \brief Add a new application.
	 *
	 * The given _id is used for later linking of users to specific applications.
	 * Using _id's default value indicates a new entry in the database. Else a readout from stream/database.
	 * When using default id value, internally a 'virtual' id must be assigned, to be able to store relations.
	 *
	 * To avoid extra functions, these 'virtual' id's would be negative. This could be determined my the
	 * database stream handler.
	 */
	virtual long LB_STDCALL addApplication(const char* application, const char* titel, const char* modulename, const char* functor, const char* _interface, long _id = -1) = 0;

	/** \brief Select current application.
	 *
	 * Direct access by application name.
	 */
	virtual bool LB_STDCALL selectApplication(const char* application) = 0;

	/** \brief Select current application.
	 *
	 * Direct access by application id.
	 */
	virtual bool LB_STDCALL selectApplication(long _id) = 0;

	/** \brief Get the number of applications.
	 */
	virtual int LB_STDCALL getApplicationCount() = 0;

	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreApplications() = 0;

	/** \brief Iterate to next application.
	 */
	virtual void		LB_STDCALL setNextApplication() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishApplicationIteration() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationName() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationTitle() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationFunctor() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationModule() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationInterface() = 0;

	/** \brief Get current applications user id.
	 *
	 * Each application entry has an associated id.
	 */
	virtual long		LB_STDCALL getApplicationID() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

class lb_I_Applications_Formulars : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addRelation(long app_id, long form_id, long _id = -1) = 0;

	/** \brief Select relation by id.
	 */
	virtual bool		LB_STDCALL selectRelation(long _id) = 0;
	virtual int			LB_STDCALL getRelationCount() = 0;
	virtual bool		LB_STDCALL hasMoreRelations() = 0;
	virtual void		LB_STDCALL setNextRelation() = 0;
	virtual void		LB_STDCALL finishRelationIteration() = 0;

	virtual long		LB_STDCALL getApplicationID() = 0;
	virtual long		LB_STDCALL getFormularID() = 0;
	virtual long		LB_STDCALL getID() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};

/*...sclass lb_I_User_Applications:0:*/
class lb_I_User_Applications : public lb_I_Unknown {
public:
	/** \brief Add a new application.
	 *
	 * The given _id is used for later linking of users to specific applications.
	 * Using _id's default value indicates a new entry in the database. Else a readout from stream/database.
	 * When using default id value, internally a 'virtual' id must be assigned, to be able to store relations.
	 *
	 * To avoid extra functions, these 'virtual' id's would be negative. This could be determined my the
	 * database stream handler.
	 */
	virtual long LB_STDCALL addRelation(long app_id, long user_id, long _id = -1) = 0;

	/** \brief Select relation by id.
	 */
	virtual bool LB_STDCALL selectRelation(long _id) = 0;

	/** \brief Hide entities, not related to filter.
	 *
	 * Multiple filters are logically or'ed, but different filter names are and'ed.
	 */
	virtual bool LB_STDCALL addFilter(const char* filter, const char* value) = 0;

	/** \brief Remove filter.
	 *
	 * Removes all or specified filter(s).
	 */
	virtual bool LB_STDCALL resetFilter(const char* filter = "") = 0;

	/** \brief Get the number of applications.
	 */
	virtual int LB_STDCALL getRelationCount() = 0;

	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreRelations() = 0;

	/** \brief Iterate to next application.
	 */
	virtual void		LB_STDCALL setNextRelation() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishRelationIteration() = 0;

	/** \brief Get current applications id.
	 *
	 * Each application entry has an associated id.
	 */
	virtual long		LB_STDCALL getApplicationID() = 0;

	/** \brief Get current users id.
	 *
	 */
	virtual long		LB_STDCALL getUserID() = 0;

	virtual long		LB_STDCALL getID() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Formulars:0:*/
class lb_I_Formulars : public lb_I_Unknown {
public:
	/** \brief Ignore all other data.
	 *
	 * This will be used to ignore all data not from the specific application.
	 */
	//virtual void		LB_STDCALL setApplicationFilter(long anwendung_id) = 0;

	virtual long		LB_STDCALL addFormular(const char* name, const char* toolbarimage, const char* menuname, const char* eventname, const char* menuhilfe, long anwendung_id, long typ, long formular_id = -1) = 0;
	virtual bool		LB_STDCALL selectFormular(long _id) = 0;
	virtual int			LB_STDCALL getFormularCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormulars() = 0;
	virtual void		LB_STDCALL setNextFormular() = 0;
	virtual void		LB_STDCALL finishFormularIteration() = 0;

	virtual char*		LB_STDCALL getName() = 0;
	virtual char*		LB_STDCALL getMenuName() = 0;
	virtual char*		LB_STDCALL getToolbarImage() = 0;
	virtual char*		LB_STDCALL getEventName() = 0;
	virtual char*		LB_STDCALL getMenuHelp() = 0;
	virtual long		LB_STDCALL getApplicationID() = 0;
	virtual long		LB_STDCALL getTyp() = 0;
	virtual long		LB_STDCALL getFormularID() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Formulars:0:*/
class lb_I_Formular_Fields : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addField(const char* name, const char* tablename, const char* dbtype, bool isFK, const char* FKName, const char* FKTable, long formular_id, long fieldid = -1) = 0;
	virtual bool		LB_STDCALL selectField(long _id) = 0;
	virtual int			LB_STDCALL getFieldCount() = 0;
	virtual bool		LB_STDCALL hasMoreFields() = 0;
	virtual void		LB_STDCALL setNextField() = 0;
	virtual void		LB_STDCALL finishFieldsIteration() = 0;

	virtual char*		LB_STDCALL getName() = 0;
	virtual char*		LB_STDCALL getTableName() = 0;
	virtual char*		LB_STDCALL getDBType() = 0;
	virtual char*		LB_STDCALL getFKName() = 0;
	virtual char*		LB_STDCALL getFKTable() = 0;
	virtual long		LB_STDCALL getFormularID() = 0;
	virtual long		LB_STDCALL getID() = 0;
	virtual bool		LB_STDCALL isFK() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Formulars:0:*/
class lb_I_Column_Types : public lb_I_Unknown {
public:
	// const char* tablename, const char* name are together the logically key
	virtual long		LB_STDCALL addType(const char* tablename, const char* name, const char* specialcolumn, const char* controltype, bool readonly) = 0;
	virtual bool		LB_STDCALL selectType(const char* tablename, const char* name) = 0;
	virtual int			LB_STDCALL getTypeCount() = 0;
	virtual bool		LB_STDCALL hasMoreTypes() = 0;
	virtual void		LB_STDCALL setNextType() = 0;
	virtual void		LB_STDCALL finishTypeIteration() = 0;

	virtual char*		LB_STDCALL getTableName() = 0;
	virtual char*		LB_STDCALL getName() = 0;
	virtual char*		LB_STDCALL getSpecialColumn() = 0;
	virtual char*		LB_STDCALL getControlType() = 0;
	virtual bool		LB_STDCALL getReadonly() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/


/*...sclass lb_I_ParameterTable:0:*/
class lb_I_ParameterTable : public lb_I_Unknown {
public:
	virtual bool		LB_STDCALL selectParameter(long _id) = 0;

	virtual int			LB_STDCALL getParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreParameters() = 0;
	virtual void		LB_STDCALL setNextParameter() = 0;
	virtual void		LB_STDCALL finishParameterIteration() = 0;

	virtual long		LB_STDCALL getParameterID() = 0;
	virtual char*		LB_STDCALL getParameterName() = 0;
	virtual char*		LB_STDCALL getParameterValue() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_FormularParameter:0:*/
class lb_I_FormularParameter : public lb_I_ParameterTable {
public:
	virtual long		LB_STDCALL addParameter(const char* name, const char* value, long formular_id, long _id = -1) = 0;
	virtual long		LB_STDCALL getFormularID() = 0;
	virtual char*		LB_STDCALL getParameter(const char* name, long formular_id) = 0;
};
/*...e*/

/*...sclass lb_I_ApplicationParameter:0:*/
class lb_I_ApplicationParameter : public lb_I_ParameterTable {
public:
	virtual long		LB_STDCALL addParameter(const char* name, const char* value, long anwendungs_id, long _id = -1) = 0;
	virtual long		LB_STDCALL getApplicationID() = 0;
	virtual char*		LB_STDCALL getParameter(const char* name, long application_id) = 0;
};
/*...e*/

/*...sclass lb_I_FKPK_Mapping:0:*/
class lb_I_FKPK_Mapping : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addMapping(const char* PKTable, const char* PKName, const char* FKTable, const char* FKName, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectMapping(long _id) = 0;
	virtual int		LB_STDCALL getMappingCount() = 0;
	virtual bool		LB_STDCALL hasMoreMappings() = 0;
	virtual void		LB_STDCALL setNextMapping() = 0;
	virtual void		LB_STDCALL finishMappingIteration() = 0;

	virtual long		LB_STDCALL getMappingID() = 0;
	virtual char*		LB_STDCALL getPKTable() = 0;
	virtual char*		LB_STDCALL getPKName() = 0;
	virtual char*		LB_STDCALL getFKTable() = 0;
	virtual char*		LB_STDCALL getFKName() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Actions:0:*/
class lb_I_Actions : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addAction(const char* name, long typ, const char* source, const char* target, long _applicationid, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectAction(long _id) = 0;
	virtual int			LB_STDCALL getActionCount() = 0;
	virtual bool		LB_STDCALL hasMoreActions() = 0;
	virtual void		LB_STDCALL setNextAction() = 0;
	virtual void		LB_STDCALL finishActionIteration() = 0;

	virtual long		LB_STDCALL getActionID() = 0;
	virtual long		LB_STDCALL getActionTyp() = 0;
	virtual long		LB_STDCALL getActionApplicationID() = 0;
	virtual char*		LB_STDCALL getActionTarget() = 0;

	virtual char*		LB_STDCALL getActionSource() = 0;
	virtual char*		LB_STDCALL getActionName() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Steps:0:*/
class lb_I_Action_Steps : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addActionStep(const char* bezeichnung, long actionid, long orderNo, long type, const char* what, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionStep(long _id) = 0;
	virtual int			LB_STDCALL getActionStepCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionSteps() = 0;
	virtual void		LB_STDCALL setNextActionStep() = 0;
	virtual void		LB_STDCALL finishActionStepIteration() = 0;

	virtual long		LB_STDCALL getActionStepID() = 0;
	virtual long		LB_STDCALL getActionStepActionID() = 0;
	virtual long		LB_STDCALL getActionStepOrderNo() = 0;
	virtual long		LB_STDCALL getActionStepType() = 0;

	virtual char*		LB_STDCALL getActionStepBezeichnung() = 0;
	virtual char*		LB_STDCALL getActionStepWhat() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Steps:0:*/
class lb_I_Action_Step_Transitions : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addTransition(const char* decision, long src_actionid, long dst_actionid, const char* description, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectTransition(long _id) = 0;
	virtual int			LB_STDCALL getActionStepTransitionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionStepTransitions() = 0;
	virtual void		LB_STDCALL setNextActionStepTransition() = 0;
	virtual void		LB_STDCALL finishActionStepTransitionIteration() = 0;

	virtual long		LB_STDCALL getActionStepTransitionID() = 0;
	virtual long		LB_STDCALL getActionStepTransitionSrcActionID() = 0;
	virtual long		LB_STDCALL getActionStepTransitionDstActionID() = 0;

	virtual char*		LB_STDCALL getActionStepTransitionDecision() = 0;
	virtual char*		LB_STDCALL getActionStepTransitionDescription() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lb_I_Action_Types : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addActionTypes(const char* bezeichnung, const char* action_handler , const char* module, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionType(long _id) = 0;
	virtual int			LB_STDCALL getActionTypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionTypes() = 0;
	virtual void		LB_STDCALL setNextActionType() = 0;
	virtual void		LB_STDCALL finishActionTypeIteration() = 0;

	virtual long		LB_STDCALL getActionTypeID() = 0;

	virtual char*		LB_STDCALL getActionTypeBezeichnung() = 0;
	virtual char*		LB_STDCALL getActionTypeHandler() = 0;
	virtual char*		LB_STDCALL getActionTypeModule() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lb_I_Action_Parameters : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addActionParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionParameter(long _id) = 0;
	virtual int			LB_STDCALL getActionParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionParameters() = 0;
	virtual void		LB_STDCALL setNextActionParameter() = 0;
	virtual void		LB_STDCALL finishActionParameterIteration() = 0;

	virtual long		LB_STDCALL getActionParameterID() = 0;
	virtual long		LB_STDCALL getActionParameterActionID() = 0;

	virtual char*		LB_STDCALL getActionParameterDescription() = 0;
	virtual char*		LB_STDCALL getActionParameterName() = 0;
	virtual char*		LB_STDCALL getActionParameterValue() = 0;
	virtual char*		LB_STDCALL getActionParameterInterface() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lb_I_ActionStep_Parameters : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addActionStepParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionStepParameter(long _id) = 0;
	virtual int			LB_STDCALL getActionStepParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionStepParameters() = 0;
	virtual void		LB_STDCALL setNextActionStepParameter() = 0;
	virtual void		LB_STDCALL finishActionStepParameterIteration() = 0;

	virtual long		LB_STDCALL getActionStepParameterID() = 0;
	virtual long		LB_STDCALL getActionStepParameterActionID() = 0;

	virtual char*		LB_STDCALL getActionStepParameterDescription() = 0;
	virtual char*		LB_STDCALL getActionStepParameterName() = 0;
	virtual char*		LB_STDCALL getActionStepParameterValue() = 0;
	virtual char*		LB_STDCALL getActionStepParameterInterface() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Formular_Actions:0:*/
class lb_I_Formular_Actions : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addFormularAction(long formular, long action, const char* event, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectFormularAction(long _id) = 0;
	virtual int		LB_STDCALL getFormularActionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormularActions() = 0;
	virtual void		LB_STDCALL setNextFormularAction() = 0;
	virtual void		LB_STDCALL finishFormularActionIteration() = 0;

	virtual long		LB_STDCALL getFormularActionID() = 0;
	virtual long		LB_STDCALL getFormularActionFormularID() = 0;
	virtual long		LB_STDCALL getFormularActionActionID() = 0;

	virtual char*		LB_STDCALL getFormularActionEvent() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/

/*...sclass lb_I_Translations:0:*/
class lb_I_Translations : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addTranslation(const char* text, const char* translated, const char* language, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectTranslation(long _id) = 0;
	virtual bool		LB_STDCALL selectText(const char* text, const char* language) = 0;
	virtual int		LB_STDCALL getTranslationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreTranslations() = 0;
	virtual void		LB_STDCALL setNextTranslation() = 0;
	virtual void		LB_STDCALL finishTranslationIteration() = 0;

	virtual long		LB_STDCALL getTranslationID() = 0;
	virtual char*		LB_STDCALL getTranslationText() = 0;
	virtual char*		LB_STDCALL getTranslationTranslated() = 0;
	virtual char*		LB_STDCALL getTranslationLanguage() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};
/*...e*/
/** \brief A class to store database table information.
 *
 * This is the internal storage for database table information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_DBTables : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addTable(const char* catalog, const char* schema, const char* name, const char* type, const char* remarks, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectTable(long _id) = 0;
	virtual int			LB_STDCALL getTableCount() = 0;
	virtual bool		LB_STDCALL hasMoreTables() = 0;
	virtual void		LB_STDCALL setNextTable() = 0;
	virtual void		LB_STDCALL finishTableIteration() = 0;

	virtual long		LB_STDCALL getTableID() = 0;
	virtual char*		LB_STDCALL getTableCatalog() = 0;
	virtual char*		LB_STDCALL getTableSchema() = 0;
	virtual char*		LB_STDCALL getTableName() = 0;
	virtual char*		LB_STDCALL getTableType() = 0;
	virtual char*		LB_STDCALL getTableRemarks() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};

/** \brief A class to store database column information.
 *
 * This is the internal storage for database column information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_DBColumns : public lb_I_Unknown {
public:
	virtual bool		LB_STDCALL addPagedConainer(lb_I_Container* pagedContainer) = 0;
	virtual long		LB_STDCALL addColumn(const char* name, const char* comment, const char* typ, long len, bool isNullable, const char* PKTable, const char* PKField, const char* tablename, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectColumn(long _id) = 0;
	virtual int			LB_STDCALL getColumnCount() = 0;
	virtual bool		LB_STDCALL hasMoreColumns() = 0;
	virtual void		LB_STDCALL setNextColumn() = 0;
	virtual void		LB_STDCALL finishColumnIteration() = 0;

	virtual long		LB_STDCALL getColumnID() = 0;
	virtual char*		LB_STDCALL getColumnTableName() = 0;
	virtual char*		LB_STDCALL getColumnName() = 0;
	virtual char*		LB_STDCALL getColumnComment() = 0;
	virtual char*		LB_STDCALL getColumnTyp() = 0;
	virtual long		LB_STDCALL getColumnLen() = 0;
	virtual bool		LB_STDCALL isNullable() = 0;
	virtual char*		LB_STDCALL getColumnPKTable() = 0;
	virtual char*		LB_STDCALL getColumnPKField() = 0;

	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};

/** \brief A class to store database foreign key information.
 *
 * This is the internal storage for database foreign key information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_DBForeignKeys : public lb_I_Unknown {
public:
	/** \brief Add a foreign key information.
	 * This function is based on ODBC 1.0 and therefore didn't support the last three columns returned by the SQLForeignKeys function.
	 */
	virtual long		LB_STDCALL addForeignKey(	const char* pktable_cat, const char* pktable_schem, const char* pktable_name, const char* pkcolumn_name,
													const char* fktable_cat, const char* fktable_schem, const char* fktable_name, const char* fkcolumn_name,
													long key_seq, long update_rule, long delete_rule, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectForeignKey(long _id) = 0;
	virtual int			LB_STDCALL getForeignKeyCount() = 0;
	virtual bool		LB_STDCALL hasMoreForeignKeys() = 0;
	virtual void		LB_STDCALL setNextForeignKey() = 0;
	virtual void		LB_STDCALL finishForeignKeyIteration() = 0;

	virtual long		LB_STDCALL getForeignKeyID() = 0;
	virtual char*		LB_STDCALL getForeignKeyPKTableCatalog() = 0;
	virtual char*		LB_STDCALL getForeignKeyPKTableSchema() = 0;
	virtual char*		LB_STDCALL getForeignKeyPKTableName() = 0;
	virtual char*		LB_STDCALL getForeignKeyPKTableColumnName() = 0;

	virtual char*		LB_STDCALL getForeignKeyFKTableCatalog() = 0;
	virtual char*		LB_STDCALL getForeignKeyFKTableSchema() = 0;
	virtual char*		LB_STDCALL getForeignKeyFKTableName() = 0;
	virtual char*		LB_STDCALL getForeignKeyFKTableColumnName() = 0;

	virtual long		LB_STDCALL getForeignKeyKeySequence() = 0;
	virtual long		LB_STDCALL getForeignKeyUpdateRule() = 0;
	virtual long		LB_STDCALL getForeignKeyDeleteRule() = 0;


	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};

/** \brief A class to store database primary key information.
 *
 * This is the internal storage for database primary key information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_DBPrimaryKeys : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addPrimaryKey(	const char* pktable_cat, const char* pktable_schem, const char* pktable_name, const char* pkcolumn_name,
													long key_seq, const char* column_name, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectPrimaryKey(long _id) = 0;
	virtual int			LB_STDCALL getPrimaryKeyCount() = 0;
	virtual bool		LB_STDCALL hasMorePrimaryKeys() = 0;
	virtual void		LB_STDCALL setNextPrimaryKey() = 0;
	virtual void		LB_STDCALL finishPrimaryKeyIteration() = 0;

	virtual long		LB_STDCALL getPrimaryKeyID() = 0;
	virtual char*		LB_STDCALL getPrimaryKeyTableCatalog() = 0;
	virtual char*		LB_STDCALL getPrimaryKeyTableSchema() = 0;
	virtual char*		LB_STDCALL getPrimaryKeyTableName() = 0;
	virtual char*		LB_STDCALL getPrimaryKeyColumnName() = 0;
	virtual char*		LB_STDCALL getPrimaryKeyColumnName_ODBC_V_2() = 0;

	virtual long		LB_STDCALL getPrimaryKeySequence() = 0;


	virtual bool		LB_STDCALL ismarked() = 0;
	virtual void		LB_STDCALL mark() = 0;
	virtual void		LB_STDCALL unmark() = 0;

	virtual void		LB_STDCALL deleteUnmarked() = 0;
	virtual void		LB_STDCALL deleteMarked() = 0;
};

/** \brief A class to store report information.
 *
 * This is the internal storage for report information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_Reports : public lb_I_Unknown {
public:
/// \todo Probably add a report type to add support for other reporting engines.
	virtual long		LB_STDCALL addReport(const char* name, const char* description, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectReport(long _id) = 0;
	virtual int			LB_STDCALL getReportCount() = 0;
	virtual bool		LB_STDCALL hasMoreReports() = 0;
	virtual void		LB_STDCALL setNextReport() = 0;
	virtual void		LB_STDCALL finishReportIteration() = 0;

	virtual long		LB_STDCALL getReportID() = 0;
	virtual char*		LB_STDCALL getReportName() = 0;
	virtual char*		LB_STDCALL getReportDescription() = 0;
};

/** \brief A class to store report parameter information.
 *
 * This is the internal storage for report parameter information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportParameters : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addParameter(long reportid, const char* name, const char* value, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectParameter(long _id) = 0;
	virtual int			LB_STDCALL getParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreParameters() = 0;
	virtual void		LB_STDCALL setNextParameter() = 0;
	virtual void		LB_STDCALL finishParameterIteration() = 0;

	virtual long		LB_STDCALL getReportID() = 0;
	virtual long		LB_STDCALL getParameterID() = 0;
	virtual char*		LB_STDCALL getParameterName() = 0;
	virtual char*		LB_STDCALL getParameterValue() = 0;
};

/** \brief A class to store report elements information.
 *
 * This is the internal storage for report elements information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportElements : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addElement(long reportid, const char* name, long typ, long x, long y, long w, long h, const char* description, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectElement(long _id) = 0;
	virtual int			LB_STDCALL getElementCount() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishElementIteration() = 0;

	virtual long		LB_STDCALL getElementReportID() = 0;
	virtual long		LB_STDCALL getElementID() = 0;
	virtual char*		LB_STDCALL getElementName() = 0;
	virtual char*		LB_STDCALL getElementDescription() = 0;
	virtual long		LB_STDCALL getElementTyp() = 0;
	virtual long		LB_STDCALL getElementX() = 0;
	virtual long		LB_STDCALL getElementY() = 0;
	virtual long		LB_STDCALL getElementW() = 0;
	virtual long		LB_STDCALL getElementH() = 0;
};

/** \brief A class to store report element types information.
 *
 * This is the internal storage for report element types information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportElementTypes : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addElementType(const char* name, const char* description, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectElementType(long _id) = 0;
	virtual int			LB_STDCALL getElementTypeCount() = 0;
	virtual bool		LB_STDCALL hasMoreElementTypes() = 0;
	virtual void		LB_STDCALL setNextElementType() = 0;
	virtual void		LB_STDCALL finishElementTypeIteration() = 0;

	virtual long		LB_STDCALL getElementID() = 0;
	virtual char*		LB_STDCALL getElementName() = 0;
	virtual char*		LB_STDCALL getElementDescription() = 0;
};

/** \brief A class to store report texts information.
 *
 * This is the internal storage for report texts information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportTexts : public lb_I_Unknown {
public:
	virtual long		LB_STDCALL addText(long elementid, long line, const char* text, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectText(long _id) = 0;
	virtual int			LB_STDCALL getTextCount() = 0;
	virtual bool		LB_STDCALL hasMoreTexts() = 0;
	virtual void		LB_STDCALL setNextText() = 0;
	virtual void		LB_STDCALL finishTextIteration() = 0;

	virtual char*		LB_STDCALL getText() = 0;
	virtual long		LB_STDCALL getLine() = 0;
	virtual long		LB_STDCALL getElementID() = 0;
	virtual long		LB_STDCALL getID() = 0;
};




/*...e*/

/*...slbDMF Plugin interfaces:0:*/
class lb_I_Plugin;
class lb_I_PluginImpl;
class lb_I_PluginModule;
class lb_I_ApplicationServerModul;

/*...sclass lb_I_PluginManager:0:*/
/** \brief The plugin manager
 *
 * The plugin manager should handle automatic loading of exsisting plugins and optionally
 * unload plugins by a plugin management dialog.
 */
class lb_I_PluginManager : public lb_I_Unknown {
public:

	/** \brief Starts initializing plugins.
	 *
	 * This function reads out the plugin directory and tries to load
	 * it by the standard plugin module functor. If it exists, it will
	 * succeed. If not, the module will be ignored.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/** \brief Runs the install method per plugin module.
	 * The install method per plugin module may do install tasks. This routine is used to invoke all
	 * install tasks. Each install task must be runnable isolated and should not depend on another install
	 * task.
	 */
	virtual void LB_STDCALL runInstallers() = 0;

	/** \brief Unload plugins.
	 *
	 * Use this function to clean up all loaded plugin modules.
	 * This is nessesary due to dependencies of the modules and the
	 * order of system unload order of the plugins.
	 */
	virtual void LB_STDCALL unload() = 0;

	/** \brief Starts listing of plugins.
	 *
	 * As of lb_I_Container interface, this is similar to the beginning of
	 * enumerating its objects.
	 */
	virtual bool LB_STDCALL beginEnumPlugins() = 0;

	/** \brief Get the next plugin.
	 *
	 * Gets the next plugin handle instance. This does not
	 * load an instance of the plugin implementation. But it
	 * loads the module.
	 *
	 * To finally use the plugin, you must attach to it.
	 */
	virtual lb_I_Plugin* LB_STDCALL nextPlugin() = 0;

	/** \brief Starts listing of server plugins.
	 *
	 * This function does only list those plugins
	 *
	 * As of lb_I_Container interface, this is similar to the beginning of
	 * enumerating its objects.
	 */
	virtual bool LB_STDCALL beginEnumServerPlugins() = 0;

	/** \brief Get the next server plugin.
	 *
	 * Gets the next plugin handle instance. This does not
	 * load an instance of the plugin implementation. But it
	 * loads the module.
	 *
	 * To finally use the plugin, you must attach to it.
	 */
	virtual lb_I_Plugin* LB_STDCALL nextServerPlugin() = 0;

	virtual lb_I_ApplicationServerModul* LB_STDCALL nextServerPluginModul() = 0;
	
	/** \brief Find first matching plugin.
	 *
	 * This function searches for a plugin, that matches the match string.
	 *
	 * The match string could be a functor name, an interface name or partial of them.
	 * The order, in that this function will search is decided by the match string.
	 */
	virtual lb_I_Plugin* LB_STDCALL getFirstMatchingPlugin(const char* match, const char* _namespace, const char* _version = "1.0") = 0;
	virtual lb_I_Plugin* LB_STDCALL getFirstMatchingServerPlugin(const char* match, const char* _namespace) = 0;

	/** \brief Find first matching server plugin.
	 *
	 * This function searches for a server plugin, that matches the match string.
	 *
	 * The match string could be a functor name, an interface name or partial of them.
	 * The order, in that this function will search is decided by the match string.
	 */
	//virtual lb_I_Plugin* LB_STDCALL getFirstMatchingServerPlugin(char* match, char* _namespace) = 0;


	/** \brief Put in a plugin (via DnD as an example).
	 *
	 * Attach the plugin implementation to the plugin handle.
	 * After attaching the plugin, you will be able to init
	 * the plugin via the initialize() function.
	 */
	virtual bool LB_STDCALL attach(lb_I_PluginModule* toAttach) = 0;

	/**
	 * Detach it. If it returns true, it could be destroyed or
	 * stored permanently for replacing with other implementation.
	 */
	virtual bool LB_STDCALL detach(lb_I_PluginModule* toAttach) = 0;

	/** \brief Return the found plugin directory.
	 * There are some possible locations of plugins. The first location that is found will be used and returned here.
	 */
	virtual lb_I_String* LB_STDCALL getPluginDirectory() = 0;

	/** \brief Check if a plugin module is registered.
	 * Checks, if there is a plugin module registered with the given name.
	 */
	virtual bool LB_STDCALL isRegistered(const char* name) = 0;
};
/*...e*/

/*...sclass lb_I_PluginModule:0:*/
/** \brief Plugin module
 *
 * The plugin module is a class per module, that should list all included plugins for one
 * module. This should be similar to the BEGIN_IMPLEMENT_UNKNOWN and ADD_INTERFACE macros.
 */
class lb_I_PluginModule : public lb_I_Unknown {
public:
	/** \brief Store the name of the module.
	 * Set the name of the module. Typically the path and name to the shared library.
	 */

	virtual void LB_STDCALL setModule(const char* module) = 0;

	/** \brief Get the name of the module.
	 * Returns the name of the module.
	 */
	virtual lb_I_String* LB_STDCALL getModule() = 0;

	/**
	 * Get the list of plugins for the current plugin module.
	 */
	virtual lb_I_Container* LB_STDCALL getPlugins() = 0;

	/** \brief Prepare the list of plugins this module contains.
	 * This function must be called once per instance of this
	 * module. It internally generates the list of plugins
	 * implemented in this module.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/** \brief Run any install task this mudule may do.
	 * Each plugin module may do some installation task. This routine is responsible for this task.
	 * Please do not call any install method before the plugin manager has initialized all plugins.
	 */
	virtual void LB_STDCALL install() = 0;

protected:
	/**
	 * Used internally in the macros to build the plugin list.
	 */
	virtual void LB_STDCALL enumPlugins() = 0;
};


#define DECLARE_PLUGINS() \
	virtual void LB_STDCALL setModule(const char* module); \
	virtual lb_I_String* LB_STDCALL getModule(); \
	virtual lb_I_Container* LB_STDCALL getPlugins(); \
	virtual void LB_STDCALL enumPlugins(); \
	UAP(lb_I_Container, Plugins) \
	UAP(lb_I_String, _module)

#define BEGIN_PLUGINS(cls) \
\
void LB_STDCALL cls::setModule(const char* module) { \
	if (_module == NULL) { \
		REQUEST(getModuleInstance(), lb_I_String, _module) \
	} \
	*_module = module; \
} \
lb_I_String* LB_STDCALL cls::getModule() { \
	_module++; \
	return _module.getPtr(); \
}\
lb_I_Container* cls::getPlugins() { \
	if (Plugins != NULL) { \
		Plugins++; \
		return Plugins.getPtr(); \
	} \
	return NULL; \
} \
void LB_STDCALL cls::enumPlugins() { \
	lbErrCodes err = ERR_NONE; \
	if (Plugins != NULL) { \
		Plugins--; \
	} \
	REQUEST(getModuleInstance(), lb_I_Container, Plugins)

#define ADD_PLUGIN(plugin, namespace) \
	UAP_REQUEST(getModuleInstance(), lb_I_Plugin, P##plugin##namespace) \
	\
	P##plugin##namespace->setModule(_module->charrep()); \
	P##plugin##namespace->setName(#plugin); \
	P##plugin##namespace->setNamespace(#namespace); \
	P##plugin##namespace->setVersion("1.0"); \
	\
	UAP_REQUEST(getModuleInstance(), lb_I_String, s##plugin##namespace) \
	UAP(lb_I_KeyBase, Key##plugin##namespace) \
	UAP(lb_I_Unknown, ukPlugin##plugin##namespace) \
	\
	s##plugin##namespace->setData(#plugin); \
	QI(s##plugin##namespace, lb_I_KeyBase, Key##plugin##namespace) \
	QI(P##plugin##namespace, lb_I_Unknown, ukPlugin##plugin##namespace) \
	\
	Plugins->insert(&ukPlugin##plugin##namespace, &Key##plugin##namespace); \
	\
	UAP(lb_I_Unknown, ukPl##plugin##namespace) \
	UAP(lb_I_Plugin, Pl##plugin##namespace) \
	ukPl##plugin##namespace = Plugins->getElement(&Key##plugin##namespace); \
	QI(ukPl##plugin##namespace, lb_I_Plugin, Pl##plugin##namespace) \
	Pl##plugin##namespace->setModule(_module->charrep()); \
	Pl##plugin##namespace->setName(#plugin); \
	Pl##plugin##namespace->setNamespace(#namespace); \
	Pl##plugin##namespace->setVersion("1.0");

//	_LOG << "Plugin '" << #plugin << "' with namespace '" << #namespace << ", version '" << "1.0" << "' in '" << _module->charrep() << "' added." LOG_

#define ADD_PLUGIN_V(plugin, namespace, version) \
	UAP_REQUEST(getModuleInstance(), lb_I_Plugin, P##plugin##namespace) \
	\
	P##plugin##namespace->setModule(_module->charrep()); \
	P##plugin##namespace->setName(#plugin); \
	P##plugin##namespace->setNamespace(#namespace); \
	P##plugin##namespace->setVersion(#version); \
	\
	UAP_REQUEST(getModuleInstance(), lb_I_String, s##plugin##namespace) \
	UAP(lb_I_KeyBase, Key##plugin##namespace) \
	UAP(lb_I_Unknown, ukPlugin##plugin##namespace) \
	\
	s##plugin##namespace->setData(#plugin); \
	QI(s##plugin##namespace, lb_I_KeyBase, Key##plugin##namespace) \
	QI(P##plugin##namespace, lb_I_Unknown, ukPlugin##plugin##namespace) \
	\
	Plugins->insert(&ukPlugin##plugin##namespace, &Key##plugin##namespace); \
	\
	UAP(lb_I_Unknown, ukPl##plugin##namespace) \
	UAP(lb_I_Plugin, Pl##plugin##namespace) \
	ukPl##plugin##namespace = Plugins->getElement(&Key##plugin##namespace); \
	QI(ukPl##plugin##namespace, lb_I_Plugin, Pl##plugin##namespace) \
	Pl##plugin##namespace->setModule(_module->charrep()); \
	Pl##plugin##namespace->setName(#plugin); \
	Pl##plugin##namespace->setNamespace(#namespace); \
	Pl##plugin##namespace->setVersion(#version); \
	_LOG << "Plugin '" << #plugin << "' with namespace '" << #namespace << ", version '" << #version << "' in '" << _module->charrep() << "' added." LOG_

#define END_PLUGINS() }

#define AQUIRE_PLUGIN(interface, ns, name, errmsgpart) \
	UAP(lb_I_Plugin, pl##name) \
	UAP(lb_I_Unknown, uk##name) \
	pl##name = PM->getFirstMatchingPlugin(#interface, #ns); \
	if (pl##name != NULL) { \
		uk##name = pl##name->getImplementation(); \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin found." LOG_ \
	} \
	\
	if (uk##name != NULL) { \
		QI(uk##name, interface, name) \
		if (name == NULL) { \
			_LOG << "Error: Plugin implementation '" << #errmsgpart << " has not the given interface (" << #interface << ", version " << "1.0" << ")." LOG_ \
		} \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin implementation found." LOG_ \
	}

#define AQUIRE_PLUGIN_V(interface, ns, name, version, errmsgpart) \
	UAP(lb_I_Plugin, pl##name) \
	UAP(lb_I_Unknown, uk##name) \
	pl##name = PM->getFirstMatchingPlugin(#interface, #ns, #version); \
	if (pl##name != NULL) { \
		uk##name = pl##name->getImplementation(); \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin found." LOG_ \
	} \
	\
	if (uk##name != NULL) { \
		QI(uk##name, interface, name) \
		if (name == NULL) { \
			_LOG << "Error: Plugin implementation '" << #errmsgpart << " has not the given interface (" << #interface << ", version " << #version << ")." LOG_ \
		} \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin implementation found." LOG_ \
	}


#define AQUIRE_PLUGIN_NAMESPACE_BYSTRING(interface, ns, name, errmsgpart) \
		UAP(lb_I_Plugin, pl##name) \
		UAP(lb_I_Unknown, uk##name) \
		pl##name = PM->getFirstMatchingPlugin(#interface, ns); \
		if (pl##name != NULL) { \
			uk##name = pl##name->getImplementation(); \
		} else { \
			_LOG << "Warning: No " << #errmsgpart << " datamodel plugin found." LOG_ \
		} \
		\
		if (uk##name != NULL) { \
			QI(uk##name, interface, name) \
			if (name == NULL) { \
				_LOG << "Error: Plugin implementation '" << #errmsgpart << " has not the given interface (" << #interface << ")." LOG_ \
			} \
		} else { \
			_LOG << "Warning: No " << #errmsgpart << " datamodel plugin implementation found." LOG_ \
		}

#define AQUIRE_PLUGIN_NAMESPACE_BYSTRING_V(interface, ns, name, version, errmsgpart) \
	UAP(lb_I_Plugin, pl##name) \
	UAP(lb_I_Unknown, uk##name) \
	pl##name = PM->getFirstMatchingPlugin(#interface, ns, version); \
	if (pl##name != NULL) { \
		uk##name = pl##name->getImplementation(); \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin found." LOG_ \
	} \
	\
	if (uk##name != NULL) { \
		QI(uk##name, interface, name) \
		if (name == NULL) { \
			_LOG << "Error: Plugin implementation '" << #errmsgpart << " has not the given interface (" << #interface << ", version " << version << ")." LOG_ \
		} \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin implementation found." LOG_ \
	}

#define AQUIRE_PLUGIN_NAMESPACE_AND_INTERFACE_BYSTRING(interface, ns, name, errmsgpart) \
	UAP(lb_I_Plugin, pl##name) \
	UAP(lb_I_Unknown, uk##name) \
	pl##name = PM->getFirstMatchingPlugin(interface, ns); \
	if (pl##name != NULL) { \
		uk##name = pl##name->getImplementation(); \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin found." LOG_ \
	} \
	\
	if (uk##name != NULL) { \
		QI(uk##name, interface, name) \
		if (name == NULL) { \
			_LOG << "Error: Plugin implementation '" << #errmsgpart << " has not the given interface (" << #interface << ")." LOG_ \
		} \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin implementation found." LOG_ \
	}

#define AQUIRE_PLUGIN_NAMESPACE_AND_INTERFACE_BYSTRING_V(interface, ns, name, version, errmsgpart) \
	UAP(lb_I_Plugin, pl##name) \
	UAP(lb_I_Unknown, uk##name) \
	pl##name = PM->getFirstMatchingPlugin(interface, ns, version); \
	if (pl##name != NULL) { \
		uk##name = pl##name->getImplementation(); \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin found." LOG_ \
	} \
	\
	if (uk##name != NULL) { \
		QI(uk##name, interface, name) \
		if (name == NULL) { \
			_LOG << "Error: Plugin implementation '" << #errmsgpart << " has not the given interface (" << #interface << ", version " << version << ")." LOG_ \
		} \
	} else { \
		_LOG << "Warning: No " << #errmsgpart << " datamodel plugin implementation found." LOG_ \
	}


/*...e*/

/*...sclass lb_I_Plugin:0:*/
/**
 * \brief Interface for single plugin (forwarder).
 *
 * This should be a wrapper to the plugin implementation.
 */
class lb_I_Plugin : public lb_I_Unknown {
public:

	/** \brief Forwarder for initializion.
	 *
	 * Initialize the plugin. This function can only be called, if it has been
	 * attached by the plugin manager. If this hasn't been made, nothing happens.
	 *
	 * If the plugin is correctly set up, initialize can forward its call to the
	 * underlying plugin implementation.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/** \brief Indicates autorunability.
	 *
	 * A plugin needs autorun features to extend the UI. But a plugin shouldn't
	 * simply initialized. It should be registered to the application.
	 */
	virtual bool LB_STDCALL canAutorun() = 0;

	/** \brief Autorun this plugin.
	 * Implement this function for autorun capabilities.
	 */
	virtual lbErrCodes LB_STDCALL autorun() = 0;

	/** \brief Forwarder for running the plugin.
	 *
	 * Let the plugin implementation run.
	 */
	virtual bool LB_STDCALL run() = 0;

	/** \brief Check for given interface.
	 *
	 * This function instantiate the underlying implementation and
	 * checks, if it contains the requested interface. If this is true,
	 * the instance will stay alive. If not, it will be released.
	 */
	virtual bool LB_STDCALL hasInterface(const char* name) = 0;

	/** \brief Returns the underlying implementation as unknown instance.
	 *
	 * This function returns the instance of the implementation and left the
	 * owning by the caller. It does not clean up the instance by it self.
	 */
	virtual lb_I_Unknown* LB_STDCALL getImplementation() = 0;

/*...slb_I_Plugin management API:0:*/
	/**
	 * The plugin must know of the plugin manager to self detach at cleanup due to
	 * release calls.
	 * This function is called prior to setAttached.
	 */
	virtual void LB_STDCALL setPluginManager(lb_I_PluginManager* plM) = 0;

	/**
	 * Called by attach/detach function from plugin manager.
	 * If the parameter is NULL, the plugin should uninitialize before
	 * really detaching.
	 */
	virtual void LB_STDCALL setAttached(lb_I_PluginImpl* impl = NULL) = 0;

	/**
	 * Called inside clone to get also a reference to the plugin implementation.
	 * This is needed due to deleting issues.
	 */
	virtual lb_I_PluginImpl* LB_STDCALL getAttached() = 0;

	/**
	 * This function should uninitialize all handlers, that are registered.
	 */
	virtual void LB_STDCALL uninitialize() = 0;

	/**
	 * Set the name of the module where the plugin is in.
	 */
	virtual void LB_STDCALL setModule(const char* module) = 0;

	/**
	 * Set the name of the plugin. This would be the functor name for
	 * an instance of the plugin.
	 */
	virtual void LB_STDCALL setName(const char* name) = 0;

	/**
	 * Set the version of the plugin. The version distinguishes between
	 * different versions of the same class.
	 */
	virtual void LB_STDCALL setVersion(const char* version) = 0;


	/**
	 * The scope identifies the area of usage. If the scope is GUI, it
	 * would only be usable in graphical user environment. If it is UI,
	 * it would be usable in textual user interfaces as well. If it is
	 * NONE, it could also be used in non user interface centric apps.
	 *
	 * This means, propably a server, where no user interaction is available.
	 */
	virtual void LB_STDCALL setNamespace(const char* __namespace) = 0;

	/** \brief Get shared library name.
	 *
	 */
	virtual char* LB_STDCALL getModule() = 0;

	/** \brief Get plugin functor name.
	 *
	 */
	virtual char* LB_STDCALL getName() = 0;

	/** \brief Get plugin functor version.
	 *
	 */
	virtual char* LB_STDCALL getVersion() = 0;

	/** \brief Get namespace.
	 *
	 */
	virtual char* LB_STDCALL getNamespace() = 0;

/*...e*/

};
/*...e*/

/*...sclass lb_I_PluginImpl:0:*/
/**
 * \brief This interface must be used for each plugin implementation.
 */
class lb_I_PluginImpl : public lb_I_Unknown {
public:

	/**
	 * Let the plugin initialize it self.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/**
	 * Let the plugin uninitialize it self - later :-)
	 */
	//virtual void LB_STDCALL uninitialize() = 0;

	/** \brief Autorun this plugin.
	 * Implement this function for autorun capabilities.
	 */
	virtual lbErrCodes LB_STDCALL autorun() = 0;

	/** \brief Indicates autorunability.
	 *
	 * A plugin needs autorun features to extend the UI. But a plugin shouldn't
	 * simply initialized. It should be registered to the application.
	 */
	virtual bool LB_STDCALL canAutorun() = 0;

	/**
	 * Run the plugin.
	 */
	virtual bool LB_STDCALL run() = 0;

	/** \brief Creates an instance once.
	 *
	 * This function creates an instance once and holds it created until getImplementation
	 * is called. This enables checking for interfaces before real usage.
	 */
	virtual lb_I_Unknown* LB_STDCALL peekImplementation() = 0;

	/**
	 * \brief Release unused implementation.
	 *
	 * This function i'must be used to release the temporary instance.
	 *
	 * It has been occured, that a wxDialog based window - or even wxWindow,
	 * that will not be used by the program, eg. later Destroyed, will hang
	 * the application at exit.
	 *
	 * The lb_I_PluginImpl implementation then should call Destroy in the case
	 * of a wxWindow based class.
	 */
	virtual void LB_STDCALL releaseImplementation() = 0;

	/** \brief Get the internal implementation.
	 *
	 * Returns the implementation class as an unknown interface. Internally it releases the
	 * instance to be able to create new instances.
	 */
	virtual lb_I_Unknown* LB_STDCALL getImplementation() = 0;
};
/*...e*/

/** \brief An application server module.
 * This is an attempt to enable server side modules. They should either
 * integrated in code or loaded as a plugin. When it is a plugin, a plugin
 * wrapper could be used to encapsulate the server module.
 *
 * The code for client - server programming is very alpha and should really
 * not yet used except testing.
 */
class lb_I_ApplicationServerModul : public lb_I_PluginModule {
public:
	virtual char* LB_STDCALL getServiceName() = 0;

	/// Why did I need this, if I could get the protocol handlers from the list of plugins ?
	virtual void LB_STDCALL registerModul(lb_I_ProtocolManager* pMgr, char* serverInstance) = 0;
};

class lb_I_UnitTestModul : public lb_I_PluginModule {
public:
	virtual char* LB_STDCALL getTestFixture() = 0;

	/// Why did I need this, if I could get the protocol handlers from the list of plugins ?
	//virtual void LB_STDCALL registerModul(lb_I_ProtocolManager* pMgr) = 0;
};

class lb_I_TestFixture : public lb_I_Unknown {
public:
	virtual void LB_STDCALL registerTests() = 0;
	virtual void LB_STDCALL setUp() = 0;
	virtual void LB_STDCALL tearDown() = 0;
	virtual void LB_STDCALL runTest() = 0;
};

/** \brief An attempt to implement a proxy class for other interfaces.
 * Better use CORBA or the like, if objects have to be used remotely.
 * The development of such a functionality is not planned.
 */
class lb_I_Proxy {

};
/*...e*/

class lb_I_Parameter;

/*...slbDMF Formular action interfaces:0:*/
/**
 * \brief This interface is intended as a way to delegate actions.
 *
 * Actions may be issued with buttons, validations or any other source like
 * timer events. The goal of this attempt is to abstract the action so it can
 * be simply used in a form without knowing the type of the action target.
 */
class lb_I_Action : public lb_I_Unknown {
public:

	/** \brief Execute the action with the given parameter list.
	 */
	virtual void LB_STDCALL execute(lb_I_Parameter* params) = 0;

	/** \brief What is my action (from the database).
	 */
	virtual void LB_STDCALL setActionID(long id) = 0;
};

class lb_I_ActionTransitionLogic : public lb_I_Unknown {
	/** \brief Set the action step ID.
	 */
	virtual void LB_STDCALL setActionID(long id) = 0;

	/** \brief Compute the next step ID.
	 * This is usually only one ID, except in a desicion. In a Desicion the one is returned whose guard matches.
	 */
	virtual long LB_STDCALL getNextStepId() = 0;
	
	/** \brief Compute transitions.
	 * This method executes all transitions.
	 */
	virtual lbErrCodes LB_STDCALL executeTransitions() = 0;

	/** \brief Set the transitions to be operated upon.
	 */
	virtual void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions) = 0;
	
	/** \brief Forward parameters.
	 * The transition logic probably relies upon parameters.
	 */
	virtual void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams) = 0;
};

/// \todo Think about the interface name.
/**
 * \brief This interface is intended as a way to delegate action steps.
 *
 * Means, that the main action (lb_I_Action) could have multiple steps,
 * to be performed for one action, that may be visible with a button for
 * example.
 */
class lb_I_DelegatedAction : public lb_I_Unknown {
public:
	/** \brief The delegated action.
	 * Initially this function did not give back a long value. Now the long value returned means the next
	 * action step (ID) to be executed. When -1 is returned a linear action is used and no 'jumps' are used
	 * for this action.
	 *
	 * If an ID other than -1 and 0 is returned the next step is the action step with the returned ID.
	 * If 0 is returned, the processing of the action will be stopped.
	 * A value other than -1 and 0 could be returned if there is given a transition object that describes the
	 * possible values returned.
	 */
	virtual long LB_STDCALL execute(lb_I_Parameter* params) = 0;
	virtual void LB_STDCALL setActionID(long id) = 0;
	/** \brief Set a transition object.
	 * Use this function to activate an action step than is non linear, thus it could have more than one outgoing
	 * transition.
	 *
	 * Nonlinear actionsteps are those you could create with an UML Activity diagram and translate it to the underlying
	 * datastructure representing the activity as an action with actionsteps.
	 *
	 * If an actionstep has transitions with expressions the used expression identifers must be passed in the params container to execute
	 * the expression (mostly this should be a boolean expression).
	 */
	virtual void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions) = 0;

	/** \brief Each action step probably has some parameters.
	 * Some of the execution parameters are system parameters that do not have anything todo with bussiness logic.
	 * The current implementation of the passed parameter source field and source form are too weak. These parameters
	 * should be configured in the action parameters list and the code should pass them based on that configuration.
	 *
	 * Due to the two step implementation of actions and action steps and the truth that action steps sometimes need
	 * parameters passed trough from the action I define two different sets of action parameters. One for the action
	 * and one per action step.
	 *
	 * These action parameter sets are informations about what should be passed to the action or action step. It is not
	 * the instance of those parameters. The instances must be passed by the execute method.
	 */
	virtual void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams) = 0;

};
/*...e*/

/** \brief Interface to manage formular actions.
 */
class lb_I_FormularAction_Manager : public lb_I_VisitableHelper {
public:
	/** \brief Add a mapping from event name to it's action ID.
	 */
	virtual void addRegisteredAction(long ActionID, const char* eventName) = 0;

	/** \brief ID of action target.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when
	 */
	virtual char* getActionTargetID(const char* reversed_event) = 0;

	/** \brief ID of action target as long.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when
	 */
	virtual long getActionTargetIDLong(const char* reversed_event) = 0;

	/** \brief Source field of the action. */
	virtual char* getActionSourceDataField(const char* reversed_event) = 0;

	/** \brief ID for the action. */
	virtual long getActionID(const char* reversed_event) = 0;

	/** \brief Get the action instance.
	 *
	 * This function creates the requested action instance, stores it for caching and
	 * then returns a reference to it.
	 */
	virtual lb_I_Action* getAction(long id) = 0;

	/** \brief Validate the form.
	 *
	 * Use this function to check, if the data has a correct state.
	 */
	virtual bool validate() = 0;

	/** \brief Update master/detail views and related views.
	 *
	 * Use this function to update related views. This may master/detail views and
	 * possibly views, containing data fields related to any open views.
	 */
	virtual bool update() = 0;
};

#include <lbInterfaces-sub-transfer.h>
#include <lbInterfaces-sub-xml.h>
#include <lbInterfaces-sub-classes.h>
#include <lbInterfaces-sub-ui.h>
#include <lbInterfaces-sub-db.h>
#include <lbInterfaces-sub-wxWrapper.h>
#include <lbInterfaces-sub-visitor.h>

UAPDECL(lb_I_BinaryData)
UAPDECL(lb_I_MetaApplication)
UAPDECL(lb_I_XMLConfig)
UAPDECL(lb_I_Instance)
UAPDECL(lb_I_Boolean)
UAPDECL(lb_I_FileLocation)
UAPDECL(lb_I_Translations)
UAPDECL(lb_I_DelegatedAction)
UAPDECL(lb_I_Action_Step_Transitions)
UAPDECL(lb_I_Formulars)
UAPDECL(lb_I_Formular_Actions)
UAPDECL(lb_I_FormularParameter)
UAPDECL(lb_I_ApplicationParameter)
UAPDECL(lb_I_Actions)
UAPDECL(lb_I_Action_Steps)
UAPDECL(lb_I_Action_Types)
UAPDECL(lb_I_DatabaseForm)
UAPDECL(lb_I_GUI)
UAPDECL(lb_I_Form)
UAPDECL(lb_I_EvHandler)
UAPDECL(lb_I_Application)
UAPDECL(lb_I_SimulatedApplication)
UAPDECL(lb_I_UserAccounts)
UAPDECL(lb_I_User_Applications)
UAPDECL(lb_I_PluginImpl)
UAPDECL(lb_I_ApplicationServer)
UAPDECL(lb_I_ApplicationServerModul)
UAPDECL(lb_I_UnitTestModul)
UAPDECL(lb_I_PluginModule)
UAPDECL(lb_I_DispatchRequest)
UAPDECL(lb_I_DispatchResponse)
UAPDECL(lb_I_Applications_Formulars)
UAPDECL(lb_I_DBTables)
UAPDECL(lb_I_DBColumns)
UAPDECL(lb_I_DBPrimaryKeys)
UAPDECL(lb_I_DBForeignKeys)
UAPDECL(lb_I_Reports)
UAPDECL(lb_I_ReportParameters)
UAPDECL(lb_I_ReportElements)
UAPDECL(lb_I_ReportElementTypes)
UAPDECL(lb_I_ReportTexts)
UAPDECL(lb_I_Reference)
UAPDECL(lb_I_StandaloneStreamable)
UAPDECL(lb_I_FormularAction_Manager)
UAPDECL(lb_I_Action)

#endif // __LB_INTERFACES__
