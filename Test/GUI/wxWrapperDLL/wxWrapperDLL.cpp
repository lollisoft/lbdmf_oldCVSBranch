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

#define USE_PROPGRID

// I have trouble with Open Watcom compiler when using version 1.7a or below.
// But 1.8 of OW has problems with initialization. The matching version of
// wxPropgrid in CVS is tagged with wxPG_1_2_2
#ifdef __WATCOMC__
#define USE_PROPGRID_1_2_2
#endif
#ifdef __MINGW32__
//#define USE_PROPGRID_1_2_2
#endif

//#define USE_WXAUI
#define USE_WXAUI_TOOLBAR

#ifdef OSX
//#define IN_PANEL
#endif

#ifdef LINUX
//#define IN_PANEL
#endif

#ifdef SOLARIS
//#define IN_PANEL
#endif

/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "lbLoginWizard.cpp"
#pragma interface "lbLoginWizard.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <lbDMF_wxPrec.h>

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
#include "mondrian.xpm"
#endif
/*...e*/

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include "wx/wizard.h"
#include "wx/splitter.h"
#include "wx/imaglist.h"
#include "wx/window.h"
#include "wx/statusbr.h"
#include <wx/image.h>
#include <wx/treectrl.h>
#include <wx/artprov.h>
#include <wx/notebook.h>
#include <wx/file.h>
#include <wx/splash.h>
#include <wx/treebase.h>
#include <wx/html/htmlwin.h>
#ifdef USE_PROPGRID
// Necessary header file
#include "wx/propgrid/propgrid.h"
#ifndef LBWXVERSION_CURRENT
#include "wx/propgrid/propdev.h"
#endif
// This defines wxPropertyGridManager.
#include <wx/propgrid/manager.h>


#endif

#ifndef OSX
#ifdef LINUX
#define wxAuiPaneInfo wxPaneInfo
#define wxAuiManager wxFrameManager
#include <manager.h>
#endif
#ifdef WINDOWS
#include <wx/aui/aui.h>
#endif
#endif

#ifdef OSX
 #ifdef USE_WXAUI
  #ifdef OSVERSION_Panther
   #define wxAuiPaneInfo wxPaneInfo
   #define wxAuiManager wxFrameManager
   #include <manager.h>
  #else
   #include <wx/aui/aui.h>
  #endif
 #endif
#endif

/*...e*/

/*...sLB_DATABASE_DLL scope:0:*/
#define LB_LOGINWIZARD_DLL
#include <lbloginwizard-module.h>
/*...e*/

#include <wxWrapperDLL.h>

#define DYNAMIC_QUIT            1000

/*...swxAppSelectPage:0:*/
class wxAppSelectPage :
public lb_I_Unknown,
public lb_I_AppSelectPage,
public wxWizardPageSimple
{
public:

        wxAppSelectPage() {
                app = wxString(wxT(""));
        }

        virtual ~wxAppSelectPage() {
            _CL_VERBOSE << "wxAppSelectPage::~wxAppSelectPage() called" LOG_
        }


        DECLARE_LB_UNKNOWN()

        wxAppSelectPage(wxWizard *parent);

        wxString LB_STDCALL getSelectedApp() { return app; }

        void setLoggedOnUser(const char* user);

        virtual bool TransferDataFromWindow();

        void OnWizardPageChanging(wxWizardEvent& event);


private:
		void OnIdle(wxIdleEvent& WXUNUSED(event));


        wxCheckBox *m_checkbox;
        char* userid;
        bool  loggingin;
        wxChoice* box;
        wxString app;
        wxBoxSizer* sizerMain;

        UAP(lb_I_Database, database)
        UAP(lb_I_Query, sampleQuery)

        DECLARE_EVENT_TABLE()


        // l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
        // l and buf are therefore as a bugfix.
        long l;
        char buf[100];
};

BEGIN_EVENT_TABLE(wxAppSelectPage, wxWizardPageSimple)
    EVT_WIZARD_PAGE_CHANGING(-1, wxAppSelectPage::OnWizardPageChanging)
END_EVENT_TABLE()

BEGIN_IMPLEMENT_LB_UNKNOWN(wxAppSelectPage)
END_IMPLEMENT_LB_UNKNOWN()

/*...swxAppSelectPage\58\\58\wxAppSelectPage\40\wxWizard \42\parent\41\:0:*/
wxAppSelectPage::wxAppSelectPage(wxWizard *parent) : wxWizardPageSimple(parent)
{
        //m_bitmap = wxBITMAP(wiztest2);

    userid = NULL;
    loggingin = false;

        sizerMain  = new wxBoxSizer(wxVERTICAL);

        wxStaticText* text = new wxStaticText(this, -1, (wxChar*) _trans("Application:"));
        box = new wxChoice(this, -1);

        sizerMain->Add(text, 0, wxEXPAND | wxALL, 5);
        sizerMain->Add(box, 0, wxEXPAND | wxALL, 5);

        SetSizer(sizerMain);

        sizerMain->SetSizeHints(this);
        sizerMain->Fit(this);

        box->SetFocusFromKbd();

        Centre();
}
/*...e*/
lbErrCodes LB_STDCALL wxAppSelectPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxAppSelectPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...svirtual bool wxAppSelectPage\58\\58\TransferDataFromWindow\40\\41\:0:*/
        bool wxAppSelectPage::TransferDataFromWindow()
        {
                return !loggingin;
        }
/*...e*/
/*...svoid wxAppSelectPage\58\\58\OnWizardPageChanging\40\wxWizardEvent\38\ event\41\:0:*/
void wxAppSelectPage::OnWizardPageChanging(wxWizardEvent& event) {
                if (event.GetDirection()) {
                        int sel = box->GetSelection();
                        app = box->GetString(sel);

                        if (!app.IsEmpty()) {
                                UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

                                char* _app = strdup(app.c_str());

                                _CL_LOG << "Load application '" << _app << "'" LOG_
                                loggingin = true;
                                meta->loadApplication(userid, _app);

                                free(_app);
                        }
                }
        }
/*...e*/
/*...svoid wxAppSelectPage\58\\58\setLoggedOnUser\40\char\42\ user\41\:0:*/
void wxAppSelectPage::setLoggedOnUser(const char* user) {
                lbErrCodes err = ERR_NONE;

                if (userid != NULL) free(userid);
                userid = strdup(user);

                UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
                UAP(lb_I_Container, apps)

                _CL_LOG << "Set Logged on user to '" << userid << "'" LOG_

                meta->setUserName(userid);

                apps = meta->getApplications();

                box->Clear();

                while (apps->hasMoreElements()) {
                        UAP(lb_I_String, name)
                        UAP(lb_I_Unknown, uk)

                        uk = apps->nextElement();
                        QI(uk, lb_I_String, name)

                        box->Append(wxString(name->charrep()));
                }

                box->SetSelection(0);

                sizerMain->Fit(this);
                //Fit();

                return;
}
/*...e*/
/*...e*/

/*...swxLogonPage:0:*/
class wxLogonPage :
public lb_I_Unknown,
public lb_I_LogonPage,
public wxWizardPageSimple
{
public:


DECLARE_LB_UNKNOWN()

        wxLogonPage();
        virtual ~wxLogonPage();

        wxLogonPage(wxWizard *parent);

        char const * LB_STDCALL getTextValue(const char* _name);

        void setAppSelectPage(wxAppSelectPage* p);

        // wizard event handlers
        void OnWizardCancel(wxWizardEvent& event);

        lbErrCodes LB_STDCALL createPasswdCtrl(const char* _name);
        lbErrCodes LB_STDCALL createTextCtrl(const char* _name);
        virtual bool TransferDataFromWindow();
        void init(wxWindow* parent);


//      UAP(lb_I_Database, database)
//      UAP(lb_I_Query, sampleQuery)


        // l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
        // l and buf are therefore as a bugfix.
        long l;
        char buf[100];

        wxWindow* OkButton;
        wxWindow* CancelButton;

        wxString textValue;

        wxBoxSizer* sizerMain;
        wxBoxSizer* sizerHor;
        wxBoxSizer* sizerAddRem;
        wxBoxSizer* sizerLeft;
        wxBoxSizer* sizerRight;

        wxAppSelectPage* appselect;
};


BEGIN_IMPLEMENT_LB_UNKNOWN(wxLogonPage)
END_IMPLEMENT_LB_UNKNOWN()

wxLogonPage::wxLogonPage() {

}

wxLogonPage::~wxLogonPage() {
}

wxLogonPage::wxLogonPage(wxWizard *parent) : wxWizardPageSimple(parent) {
                //m_bitmap = wxBITMAP(wiztest2);
}


lbErrCodes LB_STDCALL wxLogonPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxLogonPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

void wxLogonPage::setAppSelectPage(wxAppSelectPage* p) {
        appselect = p;
}

        // wizard event handlers
void wxLogonPage::OnWizardCancel(wxWizardEvent& event) {
        if ( wxMessageBox(_T("Do you really want to cancel?"), _T("Question"),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            // not confirmed
            event.Veto();
        }
}


/*...slbErrCodes LB_STDCALL wxLogonPage\58\\58\createPasswdCtrl\40\char\42\ _name\41\:0:*/
lbErrCodes LB_STDCALL wxLogonPage::createPasswdCtrl(const char* _name) {
        char* name = NULL;

        name = strdup(_name);

        wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint(), wxDefaultSize, wxTE_PASSWORD);

        text->SetName(name);

        sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

        char* tLabel = new char[strlen(name) + 1];

        tLabel[0] = 0;

        tLabel = strcat(tLabel, name);

        wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
                sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);

        delete [] tLabel;
        free(name);

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL wxLogonPage\58\\58\createTextCtrl\40\char\42\ _name\41\:0:*/
lbErrCodes LB_STDCALL wxLogonPage::createTextCtrl(const char* _name) {
        char* name = NULL;

        name = strdup(_name);

        wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint());

        text->SetName(name);

        sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

        char* tLabel = new char[strlen(name) + 1];

        tLabel[0] = 0;

        tLabel = strcat(tLabel, name);

        wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
                sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);

        delete [] tLabel;
        free(name);

        return ERR_NONE;
}
/*...e*/
/*...svirtual bool wxLogonPage\58\\58\TransferDataFromWindow\40\\41\:0:*/
bool wxLogonPage::TransferDataFromWindow() {
        lbErrCodes err = ERR_NONE;

        const char* pass = strdup(getTextValue("Passwort:"));
        const char* user = strdup(getTextValue("Benutzer:"));

        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

        if (meta->login(user, pass)) {
                appselect->setLoggedOnUser(user);
                if (pass) free((void*)pass);
                if (user) free((void*)user);

                return TRUE;
        } else {
                char* buf = strdup(_trans("Login to database failed.\n\nYou could not use the dynamic features of the\napplication without a proper configured database."));
                char* buf1 = strdup(_trans("Error"));
                wxMessageDialog dialog(NULL, buf, buf1, wxOK);

                dialog.ShowModal();

                free(buf);
                free(buf1);

                return FALSE;
        }
}
/*...e*/
/*...svoid wxLogonPage\58\\58\init\40\wxWindow\42\ parent\41\:0:*/
void wxLogonPage::init(wxWindow* parent) {
        char prefix[100] = "";
        sprintf(prefix, "%p", this);

        SetLabel("Login");

        sizerMain  = new wxBoxSizer(wxVERTICAL);
        sizerHor   = new wxBoxSizer(wxHORIZONTAL);
        sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
        sizerLeft  = new wxBoxSizer(wxVERTICAL);
        sizerRight = new wxBoxSizer(wxVERTICAL);

        int LoginOk;
        int LoginCancel;

        UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
        UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

        char eventName[100] = "";

        dispatcher->setEventManager(eman.getPtr());

        sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
        sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);

        createTextCtrl("Benutzer:");
        createPasswdCtrl("Passwort:");

        //#define CONNECTOR ((wxFrame*) frame)
        #define CONNECTOR this

        SetAutoLayout(TRUE);

        sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
        sizerMain->Add(sizerAddRem, 0, wxEXPAND | wxALL, 5);

        SetSizer(sizerMain);

        sizerMain->SetSizeHints(this);
        sizerMain->Fit(this);

        //Centre();
}
/*...e*/

/*...schar const \42\ LB_STDCALL wxLogonPage\58\\58\getTextValue\40\char\42\ _name\41\:0:*/
char const * LB_STDCALL wxLogonPage::getTextValue(const char* _name) {

        wxWindow* w = FindWindow(wxString(_name));

        if (w != NULL) {
                wxTextCtrl* tx = (wxTextCtrl*) w;

                textValue = tx->GetValue();

                return textValue.c_str();
        }

        return "";
}
/*...e*/
/*...e*/

WX_DEFINE_LIST(ToolCountList);

ToolCount::ToolCount(wxString& _name) {
        count = 0;
        name =  _name;
}

ToolCount::~ToolCount() {
}

wxString& ToolCount::getName() {
        return name;
}

void ToolCount::incCount() {
        count++;
}

void ToolCount::decCount() {
        count--;
}

int ToolCount::getCount() {
        return count;
}


/*...sclass lb_wxFrame:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxFrame)
//        ADD_INTERFACE(lb_I_EventSink)
//        ADD_INTERFACE(lb_I_wxFrame)
END_IMPLEMENT_LB_UNKNOWN()


lb_wxFrame::lb_wxFrame() :
	m_timer(this)
//      wxFrame(NULL, -1, _trans("Dynamic sample"), wxPoint(50, 50), wxSize(450, 340))
{
        OnQuitAccepted = false;
        menu_bar = NULL;
        gui = NULL;
        guiCleanedUp = 0;

        // Splitter window handling
        m_left = m_right = NULL;
        m_splitter = NULL;
        m_replacewindow = NULL;
        stb_areas = 1;
		timerrunning = false;
	timerenabled = false;

#ifdef SOLARIS
        skipfirstResizeEvent = true;
#endif

        _isSplitted = false;

        // Use lbDatabasePanel
        panelUsage = true;
        tableUsage = false;

}

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::registerEventHandler(lb_I_Dispatcher* disp) {
        UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)

        int temp;

#ifdef USE_WXAUI
        m_mgr.SetFrame(this);
#endif

#ifdef USE_WXAUI_TOOLBAR
        m_mgr.SetManagedWindow(this);
#endif

        eman->registerEvent("switchPanelUse", on_panel_usage);
        eman->registerEvent("switchTableUse", on_table_usage);
        eman->registerEvent("ShowPropertyPanel", _showLeftPropertyBar);
        eman->registerEvent("setPreferredPropertyPanelByNamespace", temp);
        eman->registerEvent("showMsgBox", temp);

        eman->registerEvent("addStatusBar", temp);
        eman->registerEvent("addStatusBar_TextArea", temp);
        eman->registerEvent("setStatusText", temp);

        eman->registerEvent("addToolBar", temp);
        eman->registerEvent("addTool_To_ToolBar", temp);
        eman->registerEvent("removeTool_From_ToolBar", temp);
        eman->registerEvent("toggleTool_From_ToolBar", temp);
        eman->registerEvent("openWebPage", temp);


		eman->registerEvent("removeToolBar", temp);
		eman->registerEvent("showLeftTreeView", _showLeftTreeView);


        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::showLeftPropertyBar, "ShowPropertyPanel");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::switchPanelUse, "switchPanelUse");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::switchTableUse, "switchTableUse");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::setPreferredPropertyPanelByNamespace, "setPreferredPropertyPanelByNamespace");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::showMsgBox, "showMsgBox");

        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::addStatusBar, "addStatusBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::addStatusBarTextArea, "addStatusBar_TextArea");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::setText_To_StatusBarTextArea, "setStatusText");

        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::addToolBar, "addToolBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::removeToolBar, "removeToolBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::addTool_To_ToolBar, "addTool_To_ToolBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::removeTool_From_ToolBar, "removeTool_From_ToolBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::toggleTool_From_ToolBar, "toggleTool_From_ToolBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::openWebPage, "openWebPage");

		disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxFrame::showLeftTreeView, "showLeftTreeView");


		Connect( _showLeftPropertyBar,  -1, wxEVT_COMMAND_MENU_SELECTED,
						(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
						&lb_wxFrame::OnDispatch );

		Connect( _showLeftTreeView,  -1, wxEVT_COMMAND_MENU_SELECTED,
						(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
						&lb_wxFrame::OnDispatch );

		Connect( on_panel_usage,  -1, wxEVT_COMMAND_MENU_SELECTED,
                        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                        &lb_wxFrame::OnDispatch );

        Connect( on_table_usage,  -1, wxEVT_COMMAND_MENU_SELECTED,
                        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                        &lb_wxFrame::OnDispatch );

        Connect( DYNAMIC_QUIT,  -1, wxEVT_COMMAND_MENU_SELECTED,
                         (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                         &lb_wxFrame::OnDispatch );

        Connect( DYNAMIC_ABOUT, -1, wxEVT_COMMAND_MENU_SELECTED,
                         (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                         &lb_wxFrame::OnDispatch );

        Connect( DYNAMIC_BUILDMENU, -1, wxEVT_COMMAND_MENU_SELECTED,
                         (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                         &lb_wxFrame::OnDispatch );

        Connect( DYNAMIC_VERBOSE, -1, wxEVT_COMMAND_MENU_SELECTED,
                         (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                         &lb_wxFrame::OnVerbose );

        Connect( CLOSE_CURRENT_PAGE, -1, wxEVT_COMMAND_MENU_SELECTED,
                        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                        &lb_wxFrame::OnCloseCurrentPage );

        Connect( REFRESHALL_FORMS, -1, wxEVT_COMMAND_MENU_SELECTED,
                        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                        &lb_wxFrame::OnRefreshAll );

        Connect( SHOW_PENDING_MESSAGES, -1, wxEVT_NULL,
                         (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                         &lb_wxFrame::OnDispatch );



        // Make a menubar
        wxMenu *file_menu = new wxMenu;

        file_menu->Append(DYNAMIC_ABOUT  , _trans("&About\tCtrl-A"));
        file_menu->Append(DYNAMIC_VERBOSE, _trans("&Verbose\tCtrl-V"));
        file_menu->Append(DYNAMIC_QUIT   , _trans("E&xit\tCtrl-x"));
        file_menu->Append(CLOSE_CURRENT_PAGE, _trans("&Close current page\tCtrl-c"));
        file_menu->Append(REFRESHALL_FORMS, _trans("Refresh all forms"));

        file_menu->Append(on_panel_usage, _trans("&switch Panel usage"));
        file_menu->Append(on_table_usage , _trans("&switch Table usage"));
		file_menu->Append(_showLeftPropertyBar, _trans("Show &left property panel\tCtrl-R"));
		file_menu->Append(_showLeftTreeView, _trans("Show &left tree panel"));

        menu_bar = new wxMenuBar;
        menu_bar->Append(file_menu, _trans("&File"));

        SetMenuBar(menu_bar);

        return ERR_NONE;
}
/*...e*/

lb_I_Unknown* LB_STDCALL lb_wxFrame::getUnknown() {
        lb_I_Unknown* ukp;
        queryInterface("lb_I_Unknown", (void**) &ukp, __FILE__, __LINE__);
        return ukp;
}

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::setData(lb_I_Unknown* uk) {
        _LOG << "lb_wxFrame::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
lbErrCodes LB_STDCALL lb_wxFrame::switchPanelUse(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;

        panelUsage = !panelUsage;

        return err;
}

lbErrCodes LB_STDCALL lb_wxFrame::switchTableUse(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;

        tableUsage = !tableUsage;

        return err;
}
/*...e*/

/*...sclass lb_wxGUI:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxGUI)
        ADD_INTERFACE(lb_I_wxGUI)
END_IMPLEMENT_LB_UNKNOWN()


/*...sUnimplemented code:0:*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\setDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "lb_wxGUI::setDispatcher() not implemented yet" LOG_

        return ERR_NONE;
}
/*...e*/

lb_I_Unknown* LB_STDCALL lb_wxGUI::getUnknown() {
        lb_I_Unknown* ukp;
        queryInterface("lb_I_Unknown", (void**) &ukp, __FILE__, __LINE__);
        return ukp;
}


/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEvent(char* EvName, int & EvNr) {
       _LOG << "Registering an event" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::addDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "Add a sub dispatcher" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\dispatchEvent\40\int EvNr\44\ lb_I_Unknown\42\ EvData\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::dispatchEvent(int EvNr, lb_I_Unknown* EvData) {
       _LOG << "Dispatch an event" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\queryEvent\40\char\42\ EvName\44\ lb_I_Unknown\42\ EvData\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::queryEvent(char* EvName, lb_I_Unknown* EvData) {
       _LOG << "Query an event" LOG_;
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes lb_wxGUI\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setData(lb_I_Unknown* uk) {
        _LOG << "lb_wxGUI::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenu\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenu() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenuBar\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenuBar() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenuEntry\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\deactivateMenuEntry\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::deactivateMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\activateMenuEntry\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::activateMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\gotoMenuRoot\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::gotoMenuRoot() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\addMenuEntry\40\lb_I_Unknown\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::addMenuEntry(lb_I_Unknown* entry) {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\insertMenuEntry\40\lb_I_Unknown\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::insertMenuEntry(lb_I_Unknown* entry) {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...e*/


/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEventHandler(lb_I_Dispatcher* disp) {

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\cleanup\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::cleanup() {
        _LOG << "lb_wxGUI::cleanup() called." LOG_

        /* Destroy all still created forms that are hidden.
        * If this would not be taken, the application will hang,
        * because these windows are still there.
        *
        * But the container must be deleted and there seems to be
        * a double delete. So I need a removeAll function for the container.
        */

        if (forms == NULL) {
                _LOG << "lb_wxGUI::cleanup() has nothing to clean up. Forms list is not initialized." LOG_
                return ERR_NONE;
        }

        if (forms->Count() == 0) {
                _LOG << "Info: No forms to be destroyed." LOG_
        }

        if (frame->isPanelUsage()) {
                while (notebook && notebook->GetPageCount() > 0) {
                        //notebook->RemovePage(0);
						closeCurrentPage();
                }
        }
		
		if (openedDialogs != NULL) {
			while (openedDialogs->hasMoreElements() == 1) {
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_String, s)
				
				uk = openedDialogs->nextElement();
				QI(uk, lb_I_String, s);
				
				
				forms->finishIteration();
				while (forms->hasMoreElements()) {
					lbErrCodes err = ERR_NONE;

					lb_I_Unknown* form = forms->nextElement();

					if (!form) continue;

					_LOG << "Destroy a dynamic form '" << form->getClassName() << "'." LOG_

					UAP(lb_I_Form, d)
					QI(form, lb_I_Form, d)
					
					if (d != NULL && *s == d->getName()) {
                        _LOG << "Destroy a dynamic form with " << d->getRefCount() << " references ..." LOG_

                        //d->reopen(); // Avoid invalid database object while closing.
                        d->destroy();
                        d.resetPtr();
                        _LOG << "Destroyed the dynamic form." LOG_
					}
				}
			}
			forms->detachAll();
			forms->deleteAll();
		}

        return ERR_NONE;
}
/*...e*/
/*...slb_I_Form\42\ LB_STDCALL lb_wxGUI\58\\58\createLoginForm\40\\41\:0:*/
lb_I_Form* LB_STDCALL lb_wxGUI::createLoginForm() {
        wxWizard *wizard = new wxWizard(NULL, -1, _T("Anmeldung"));

        wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);

        wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

        wxSize size = text->GetBestSize();

        wxLogonPage *page2 = new wxLogonPage(wizard);

        page2->init(frame);

        wxAppSelectPage *page3 = new wxAppSelectPage(wizard);

        page2->setAppSelectPage(page3);


        page1->SetNext(page2);
        page2->SetPrev(page1);
        page2->SetNext(page3);
        page3->SetPrev(page2);


        wizard->SetPageSize(size);

        if ( ! wizard->RunWizard(page1) )
        {
            wxMessageBox(_T("Anmeldung fehlgeschlagen"), _T("That's all"),
            wxICON_INFORMATION | wxOK);
        }

//      wxString app = page3->getSelectedApp();

        wizard->Destroy();

	return NULL;
}
/*...e*/

lbErrCodes LB_STDCALL lb_wxGUI::openWebPage(const char* pagename, const char* url) {

		wxLaunchDefaultBrowser(url);
		return ERR_NONE;

        if (frame->isPanelUsage()) {
                if (!notebook) {
                        notebook = new wxNotebook(frame, -1);
                        sizerMain = new wxBoxSizer(wxVERTICAL);

                        frame->SetAutoLayout(TRUE);
                        notebook->SetAutoLayout(TRUE);

                        sizerMain->Add(notebook, 1, wxEXPAND | wxALL, 0);

                        frame->SetSizer(sizerMain);
#ifdef USE_WXAUI
                        frame->getAUIManager().AddPane(notebook,   wxCENTER, wxT("Workplace"));
                        frame->getAUIManager().Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
                        frame->getAUIManager().AddPane(notebook,   wxCENTER, wxT("Workplace"));
                        frame->getAUIManager().Update();
#endif
                }
        }


		// Remove old Page
		int num = notebook->GetPageCount();
		for (int i = 0; i < num; i++) {
			if (strncmp(notebook->GetPageText(i).c_str(), pagename, strlen(pagename)) == 0) {
				notebook->DeletePage(i);
				break; // Bug: The num variable is not updated and will produce an index out of range error.
			}
		}


		if (frame->isPanelUsage()) {
				wxHtmlWindow* htw = new wxHtmlWindow(notebook);
				htw->LoadPage(url);
				wxWindow* w = htw;
				w->Fit();

				_LOG << "Add notebook pane with name " << pagename LOG_
				notebook->AddPage(w, pagename, true);

				if (!frame->IsMaximized()) {
						notebook->SetSizeHints(w->GetSize());
						notebook->Fit();
				}

				if (frame->isSplitted()) {
						if (!frame->IsMaximized()) frame->Fit();
				} else {
						if (!frame->IsMaximized()) {

							frame->SetSizeHints(notebook->GetSize());
							frame->Fit();
							frame->Centre();
						}
				}
		}

}

lb_I_Form* LB_STDCALL lb_wxGUI::addCustomForm(lb_I_Form* form, const char* formName) {
		lbErrCodes err = ERR_NONE;
	
        _LOG << "lb_wxGUI::addCustomDBForm() called with '" << formName << "'." LOG_

        if (frame->isPanelUsage()) {
                if (!notebook) {
                        notebook = new wxNotebook(frame, -1);
                        sizerMain = new wxBoxSizer(wxVERTICAL);

                        frame->SetAutoLayout(TRUE);
                        notebook->SetAutoLayout(TRUE);

                        sizerMain->Add(notebook, 1, wxEXPAND | wxALL, 0);

                        frame->SetSizer(sizerMain);

#ifdef USE_WXAUI
                        frame->getAUIManager().AddPane(notebook,   wxCENTER, wxT("Workplace"));
                        frame->getAUIManager().Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
                        frame->getAUIManager().AddPane(notebook,   wxCENTER, wxT("Workplace"));
                        frame->getAUIManager().Update();
#endif
                }
        }

        UAP(lb_I_Form, _dialog)

        if (forms == NULL) {
                REQUEST(getModuleInstance(), lb_I_Container, forms)
        }

        UAP(lb_I_Unknown, uk)
        UAP(lb_I_KeyBase, key)

        UAP_REQUEST(getModuleInstance(), lb_I_String, fName)
        fName->setData(formName);

        QI(fName, lb_I_KeyBase, key)

        uk = forms->getElement(&key);

        if (uk != NULL) {
                QI(uk, lb_I_Form, _dialog)
        }

        if (_dialog.getPtr() == NULL) {
                QI(form, lb_I_Unknown, uk)
                forms->insert(&uk, &key);

                form->destroy();
                form = NULL;

                //-------------------------------------------------------

                TRMemStopLocalCount();
                TRMemResetLocalCount();

                uk = forms->getElement(&key);

                if (uk != NULL) {
                        QI(uk, lb_I_Form, _dialog)
                }

                _dialog->setName(formName);

                if (frame->isPanelUsage()) {
                        _dialog->create(notebook->GetId());
                }

                _LOG << "Initialize custom form..." LOG_
                _dialog->init();

                if (frame->isPanelUsage()) {
                        wxWindow* w = frame->FindWindowById(_dialog->getId());
                        w->Fit();

                        notebook->AddPage(w, _dialog->getFormName(), true);

                        if (!frame->IsMaximized()) {
                                notebook->SetSizeHints(frame->FindWindowById(_dialog->getId())->GetSize());
                                notebook->Fit();
                        }

                        if (frame->isSplitted()) {
                                if (!frame->IsMaximized()) frame->Fit();
                        } else {
                                if (!frame->IsMaximized()) {

                                        frame->SetSizeHints(notebook->GetSize());
                                        frame->Fit();
                                        frame->Centre();
                                }
                        }
                }

        } else {
                if (frame->isPanelUsage()) {
                        int num = notebook->GetPageCount();
                        for (int i = 0; i < num; i++) {
                                if (strncmp(notebook->GetPageText(i).c_str(), _dialog->getFormName(), strlen(_dialog->getFormName())) == 0) {
                                        notebook->SetSelection(i);
                                }
                        }
                }
        }
/*...e*/

        _dialog++;

        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, app)
        app->enableEvent("ShowPropertyPanel");

        return _dialog.getPtr();
}


/*...slb_I_DatabaseForm\42\ LB_STDCALL lb_wxGUI\58\\58\createDBForm\40\char\42\ formName\44\ char\42\ queryString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
lb_I_DatabaseForm* LB_STDCALL lb_wxGUI::createDBForm(const char* formName, const char* queryString, const char* DBName, const char* DBUser, const char* DBPass) {
        lbErrCodes err = ERR_NONE;

        // Locate the form instance in the container

        if ((queryString == NULL) ||
                (DBName == NULL) ||
                (DBUser == NULL) ||
                (DBPass == NULL) ||
                (strcmp(queryString, "") == 0) ||
                (strcmp(DBName, "") == 0) ||
                (strcmp(DBUser, "") == 0) ||
                (strcmp(DBPass, "") == 0)) {
                UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

                *msg = _trans("Database SQL query, name, user or password is NULL or empty. Could not use database forms without proper parameters!");
                if (formName != NULL) {
                        *msg += _trans("\n\nThe formular name is: '");
                        *msg += formName;
                        *msg += "'";
                }

                msgBox(_trans("Error"), msg->charrep());
                return NULL;
        }

        _LOG << "Create database formular for '" << formName << "', '" << queryString << "', '" << DBName << "', '" << DBUser << "', '" << DBPass << "'" LOG_

        if (frame->isPanelUsage()) {
                if (!notebook) {
                        notebook = new wxNotebook(frame, -1);
                        sizerMain = new wxBoxSizer(wxVERTICAL);

                        frame->SetAutoLayout(TRUE);
                        notebook->SetAutoLayout(TRUE);

                        sizerMain->Add(notebook, 1, wxEXPAND | wxALL, 0);

                        frame->SetSizer(sizerMain);

#ifdef USE_WXAUI
                        frame->getAUIManager().AddPane(notebook,   wxCENTER, wxT("Workplace"));
                        frame->getAUIManager().Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
                        frame->getAUIManager().AddPane(notebook,   wxCENTER, wxT("Workplace"));
                        frame->getAUIManager().Update();
#endif
                }
        }

        UAP(lb_I_DatabaseForm, _dialog)

        if (forms == NULL) {
                REQUEST(getModuleInstance(), lb_I_Container, forms)
        }

        UAP(lb_I_Unknown, uk)
        UAP(lb_I_KeyBase, key)

        UAP_REQUEST(getModuleInstance(), lb_I_String, fName)
        fName->setData(formName);

        QI(fName, lb_I_KeyBase, key)

        uk = forms->getElement(&key);

        if (uk != NULL) {
                QI(uk, lb_I_DatabaseForm, _dialog)
        }

/*...sCheck for recreation of the form:8:*/
//      if ((_dialog.getPtr() != NULL) && (strcmp(queryString, _dialog->getQuery()) != 0)) {
        if (_dialog.getPtr() != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_String, ClassName)
                // SQL query from database has been changed. Recreate the dialog from scratch.

                // Don't delete any forms inside the container
                forms->detachAll();
                forms->remove(&key);
                // Else uk gets a dangling pointer
                uk.resetPtr();

                *ClassName = _dialog->getClassName();

                if (*ClassName == "lbDatabasePanel") {
                        int num = notebook->GetPageCount();
                        for (int i = 0; i < num; i++) {
                                if (strncmp(notebook->GetPageText(i).c_str(), formName, strlen(formName)) == 0) {
                                        notebook->DeletePage(i);
                                        break; // Bug: The num variable is not updated and will produce an index out of range error.
                                }
                        }
                }
                if (*ClassName == "lbDatabaseTableViewPanel") {
                        int num = notebook->GetPageCount();
                        for (int i = 0; i < num; i++) {
                                if (strncmp(notebook->GetPageText(i).c_str(), formName, strlen(formName)) == 0) {
                                        notebook->DeletePage(i);
                                        break; // Bug: The num variable is not updated and will produce an index out of range error.
                                }
                        }
                }
                if (*ClassName == "lbDatabaseDialog") {
                        _dialog->destroy();
                }
                if (*ClassName == "lbDatabaseTableViewDialog") {
                        _dialog->destroy();
                }

                _dialog.resetPtr();
        }
/*...e*/

/*...sCreate new\44\ if not yet done:8:*/
        if (_dialog.getPtr() == NULL) {
                /*
                 * Try to find a database form plugin, having the interface lb_I_DatabaseForm.
                 *
                 * This interface contains one and only one member function to initialize the
                 * form with a given SQL query, the required database name, login and password.
                 *
                 * This demonstrates the extensibleability of the GUI wrapper with the new plugin
                 * framework.
                 */

                UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
                UAP(lb_I_Plugin, pl)

                TRMemStartLocalCount();

                if (frame->isTableUsage()) {
                        if (frame->isPanelUsage()) {
                                pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm", "GUITableViewPanel");
                        } else {
                                pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm", "GUITableViewDialog");
                        }
                } else {
                        if (frame->isPanelUsage()) {
                                pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm", "GUIPanel");
                        } else {
                                pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm", "GUIDialog");
                        }
                }

                if (pl == NULL) {
                        char* msg = (char*) malloc(200);
                        msg[0] = 0;
                        strcpy(msg, _trans("Database form plugin not found or not installed.\n\nDatabase forms are not available."));
                        msgBox(_trans("Error"), msg);
                        free(msg);
                        return NULL;
                }

                uk = pl->getImplementation();

                forms->insert(&uk, &key);

                //-------------------------------------------------------
                // The form has been cloned. Destroy the unused instance.
                // This avoids application hang at exit.

                UAP(lb_I_DatabaseForm, form)
                QI(uk, lb_I_DatabaseForm, form)

                form->destroy();
                form = NULL;

                //-------------------------------------------------------

                TRMemStopLocalCount();
                TRMemResetLocalCount();

                uk = forms->getElement(&key);

                if (uk != NULL) {
                        QI(uk, lb_I_DatabaseForm, _dialog)
                }

                if (frame->isPanelUsage()) {
                        _dialog->create(notebook->GetId());
                } else {
						registerFormCleanup(*&form, *&fName);
				}

                _LOG << "Set formname to " << formName LOG_
                _dialog->setName(formName);

                _LOG << "Formname before init is " << formName LOG_
                _dialog->init(queryString, DBName, DBUser, DBPass);
                _LOG << "Formname after init is " << formName LOG_

                if (frame->isPanelUsage()) {
                        wxWindow* w = frame->FindWindowById(_dialog->getId());
                        w->Fit();

                        _LOG << "Add notebook pane with name " << formName LOG_
                        notebook->AddPage(w, formName, true);

                        if (!frame->IsMaximized()) {
								_LOG << "Frame is not maximized" LOG_
                                notebook->SetSizeHints(frame->FindWindowById(_dialog->getId())->GetSize());
                                notebook->Fit();
                        } else {
							_LOG << "Frame is maximized" LOG_
						}

                        if (frame->isSplitted()) {
                                if (!frame->IsMaximized()) frame->Fit();
                        } else {
                                if (!frame->IsMaximized()) {
									_LOG << "Frame is not maximized and centers to screen" LOG_
                                        frame->SetSizeHints(notebook->GetSize());
                                        frame->Fit();
                                        frame->Centre();
                                }
                        }
                }

        } else {
                if (frame->isPanelUsage()) {
                        int num = notebook->GetPageCount();
                        for (int i = 0; i < num; i++) {
                                if (strncmp(notebook->GetPageText(i).c_str(), formName, strlen(formName)) == 0) {
                                        notebook->SetSelection(i);
                                }
                        }
                }
        }
/*...e*/

        _dialog++;

        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, app)
        app->enableEvent("ShowPropertyPanel");

		if (!findDBForm(formName)) {
			_LOGERROR << "Error: Form not found after creating it!" LOG_
		}
		
        return _dialog.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createFrame\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createFrame() {
        frame = new lb_wxFrame();

        frame->Create(NULL, -1, _trans("Dynamic sample"), wxPoint(50, 50), wxSize(600, 500));

        
        frame->queryInterface("lb_I_Unknown", (void**) &_main_frame, __FILE__, __LINE__);

        frame->setGUI(this);

        #ifdef VERBOSE
        char ptr[20] = "";
        sprintf(ptr, "%p", frame);

        _LOG << "Created a lb_wxFrame object at " << ptr LOG_
        #endif

        return frame;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\getFrame\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::getFrame() {
        lb_I_Unknown* f = NULL;

        _main_frame->queryInterface("lb_I_Unknown", (void**) &f, __FILE__, __LINE__);

        return f;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\gotoMenuEntry\40\char\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::gotoMenuEntry(const char* entry) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_Frame, frame)

        QI(_main_frame, lb_I_Frame, frame)


        /**
         * Create the dispatch request
         */


        UAP_REQUEST(getModuleInstance(), lb_I_DispatchRequest, d_req)

        /**
         * We get a dispatch responce
         */

        UAP(lb_I_DispatchResponse, d_res)

        if (d_req.getPtr()) {
                // d_req must resolve the symbolic request name to its Id.
                // So it must have an instance from lb_I_EventManager
                d_req->setRequestName("hasMenuEntry");

                d_res = myDispatcher->dispatch(*&d_req);

                if ((d_res.getPtr()) && (d_res->isOk())) {
                } else {
                }
        }

/*        id (frame->hasMenuEntry(entry)) {
                if (currentMenuEntry) free(currentMenuEntry);
                currentMenuEntry = strdup(entry);
        }
*/
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\msgBox\40\char\42\ windowTitle\44\ char\42\ msg\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::msgBox(const char* windowTitle, const char* msg) {
        if (!splashOpened) {
			wxMessageDialog dialog(frame, msg, windowTitle, wxOK);

			frame->enableTimer(false);
			dialog.ShowModal();
			frame->enableTimer(true);
        } else {
                if (pendingMessages == NULL) {
                        REQUEST(getModuleInstance(), lb_I_String, pendingMessages)
                        *pendingMessages = "";
                }

                *pendingMessages += "\n";
                *pendingMessages += windowTitle;
                *pendingMessages += "\n";
                *pendingMessages += msg;
                *pendingMessages += "\n";
        }
        return ERR_NONE;
}
/*...e*/
lb_I_FixedDatabaseForm* LB_STDCALL lb_wxGUI::findCustomDBForm(const char* name) {
        lbErrCodes err = ERR_NONE;

        wxWindow* W = ::wxFindWindowByName(wxString(name));
        if (W == NULL) {
                return NULL;
        }

        UAP_REQUEST(getModuleInstance(), lb_I_String, fName)
        UAP(lb_I_KeyBase, key)
        UAP(lb_I_Unknown, uk)

        fName->setData(name);

        QI(fName, lb_I_KeyBase, key)

        uk = forms->getElement(&key);

        if (uk == NULL) {
                _CL_LOG << "Error: No form with name '" << name << "' found." LOG_
                return NULL;
        }

        UAP(lb_I_FixedDatabaseForm, w)
        QI(uk, lb_I_FixedDatabaseForm, w)
        // Not really needed, because my dialogs are forced to not be smart.
        if (w != NULL) {
                w++;
                return w.getPtr();
        }
        return NULL;
}
/*...slb_I_DatabaseForm\42\ LB_STDCALL lb_wxGUI\58\\58\findDBForm\40\char\42\ name\41\:0:*/
lb_I_DatabaseForm* LB_STDCALL lb_wxGUI::findDBForm(const char* name) {
        lbErrCodes err = ERR_NONE;

        wxWindow* W = ::wxFindWindowByName(wxString(name));
        if (W == NULL) {
                _LOG << "Error: No form with name '" << name << "' found." LOG_
                return NULL;
        }

        UAP_REQUEST(getModuleInstance(), lb_I_String, fName)
        UAP(lb_I_KeyBase, key)
        UAP(lb_I_Unknown, uk)

        fName->setData(name);

        QI(fName, lb_I_KeyBase, key)

        uk = forms->getElement(&key);

        if (uk == NULL) {
                _LOGERROR << "Error: No form with name '" << name << "' found." LOG_
                return NULL;
        }

        UAP(lb_I_DatabaseForm, w)
        QI(uk, lb_I_DatabaseForm, w)
        // Not really needed, because my dialogs are forced to not be smart.

        if (w != NULL) {
                w++;
                _LOG << "Form with name '" << name << "' found." LOG_
                return w.getPtr();
        }
		_LOGERROR << "Error: Form with name '" << name << "' is not lb_I_DatabaseForm." LOG_
        return NULL;
}
/*...e*/
void LB_STDCALL lb_wxGUI::showForm(const char* name) {
        if (frame->isPanelUsage()) {
                int num = notebook->GetPageCount();

                lb_I_DatabaseForm* f = findDBForm(name);

                if (f != NULL) {
                        for (int i = 0; i < num; i++) {
                                wxString pageText = notebook->GetPageText(i);

                                wxStringTokenizer tkz(pageText, " - ");
                                wxString token;
                                while ( tkz.HasMoreTokens() )
                                {
                                        token += tkz.GetNextToken();

                                        if (token == name) {
                                                notebook->SetPageText(i, f->getFormName());
                                                notebook->SetSelection(i);
                                        }

                                        token += " - "; // If the base formname contains this in it's name, then there would be more than two tokens. Append and recompare.
                                }
                        }
                } else {
                        lb_I_FixedDatabaseForm* f = findCustomDBForm(name);
                        if (f != NULL) {
                                for (int i = 0; i < num; i++) {
                                        wxString pageText = notebook->GetPageText(i);

                                        wxStringTokenizer tkz(pageText, " - ");
                                        wxString token;
                                        while ( tkz.HasMoreTokens() )
                                        {
                                                token += tkz.GetNextToken();

                                                if (token == name) {
                                                        notebook->SetPageText(i, f->getFormName());
                                                        notebook->SetSelection(i);
                                                }

                                                token += " - "; // If the base formname contains this in it's name, then there would be more than two tokens. Append and recompare.
                                        }
                                }
                        }
                }
        } else {
                lb_I_DatabaseForm* f = findDBForm(name);

                if (f != NULL) {
                        f->show();
                } else {
                        lb_I_FixedDatabaseForm* f = findCustomDBForm(name);
                        if (f != NULL) {
                                f->show();
                        }
                }
        }
}

void LB_STDCALL lb_wxGUI::closeCurrentPage() {
        if (!notebook) return;

        int sel = notebook->GetSelection();

        UAP(lb_I_Window, windowToClose)

        if (sel != wxNOT_FOUND)
        {
                wxWindow* w = notebook->GetCurrentPage();
                lb_I_KeyBase* key = NULL;
                forms->finishIteration();
                while (forms->hasMoreElements()) {
                        lbErrCodes err = ERR_NONE;

                        lb_I_Unknown* form = forms->nextElement();

                        if (!form) continue;

                        _LOG << "Destroy a dynamic form '" << form->getClassName() << "'." LOG_

                        UAP(lb_I_Window, window)
                        QI(form, lb_I_Window, window)

                        if ((window != NULL) && (window->getId() == w->GetId())) {
                                QI(form, lb_I_Window, windowToClose)
                                key = forms->currentKey();
                        }

                }

                forms->finishIteration();
                while (forms->hasMoreElements()) {
                        lbErrCodes err = ERR_NONE;

                        lb_I_Unknown* form = forms->nextElement();

                        if (!form) continue;

                        UAP(lb_I_Window, window)
                        QI(form, lb_I_Window, window)

                        if ((window != NULL) && !(windowToClose == NULL)) window->windowIsClosing(*&windowToClose);
                }

                windowToClose.resetPtr();

                if (key != NULL) {
                        forms->remove(&key);
                }
                notebook->DeletePage(sel);
        }

}

void LB_STDCALL lb_wxGUI::refreshAll() {
        if (forms == NULL) {
                _LOG << "lb_wxGUI::cleanup() has nothing to clean up. Forms list is not initialized." LOG_
                return;
        }

        if (forms->Count() == 0) {
                _LOG << "Info: No forms to be destroyed." LOG_
                return;
        }

        forms->finishIteration();
        while (forms->hasMoreElements()) {
                lbErrCodes err = ERR_NONE;

                lb_I_Unknown* form = forms->nextElement();

                if (!form) continue;

                _LOG << "Refresh a dynamic form '" << form->getClassName() << "'." LOG_

                UAP(lb_I_DatabaseForm, d)
                QI(form, lb_I_DatabaseForm, d)

                if (d != NULL) {
                        _LOG << "Destroy a dynamic form with " << d->getRefCount() << " references ..." LOG_

                        d->close(); // Avoid invalid database object while closing.
                        _LOG << "Destroyed the dynamic form." LOG_
                }
        }

        forms->finishIteration();
        while (forms->hasMoreElements()) {
                lbErrCodes err = ERR_NONE;

                lb_I_Unknown* form = forms->nextElement();

                if (!form) continue;

                _LOG << "Refresh a dynamic form '" << form->getClassName() << "'." LOG_

                UAP(lb_I_DatabaseForm, d)
                QI(form, lb_I_DatabaseForm, d)

                if (d != NULL) {
                        _LOG << "Destroy a dynamic form with " << d->getRefCount() << " references ..." LOG_

                        d->open(); // Avoid invalid database object while closing.
                        _LOG << "Destroyed the dynamic form." LOG_
                }
        }
}

void LB_STDCALL lb_wxGUI::setIcon(const char* name) {
        #ifdef __WXMSW__
            frame->SetIcon(wxIcon("mondrian"));
        #endif
        #if defined(__WXGTK__) || defined(__WXMOTIF__)
            frame->SetIcon(wxIcon(mondrian_xpm));
        #endif
}

void LB_STDCALL lb_wxGUI::registerFormCleanup(lb_I_Form* form, lb_I_String* formName) {
	if (openedDialogs == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, openedDialogs);
	}
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Unknown, nuk)
	*name = formName->charrep();
	QI(name, lb_I_Unknown, nuk)
	
	UAP(lb_I_KeyBase, key)
	QI(formName, lb_I_KeyBase, key)

	if (openedDialogs->exists(&key) == 0) {
		openedDialogs->insert(&nuk, &key);
	}
	
	if (forms == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, forms)
	}
	
	UAP(lb_I_Unknown, ukForm)

	QI(form, lb_I_Unknown, ukForm)
	
	if (forms->exists(&key)) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Form, formToClose)
		uk = forms->getElement(&key);
		
		QI(uk, lb_I_Form, formToClose)

		forms->remove(&key);
		
		formToClose->destroy();
	}
	
	// Forms normally get cloned yet :-(
///\todo Refactor all cloning logic.
	forms->setCloning(false);
	forms->insert(&ukForm, &key);
	forms->setCloning(true);
}

void LB_STDCALL lb_wxGUI::registerDBForm(const char* formName, lb_I_DatabaseForm* form) {

}

void LB_STDCALL lb_wxGUI::splashDestroyed() {
        splashOpened = false;

        if (frame) {
                _LOG << "Add a pending event..." LOG_
                wxCommandEvent event( wxEVT_NULL, SHOW_PENDING_MESSAGES );
                event.SetEventObject( frame );
                frame->GetEventHandler()->AddPendingEvent(event);
        }
}

void LB_STDCALL lb_wxGUI::splashCreated() {
        splashOpened = true;
}

void LB_STDCALL lb_wxGUI::showPendingMessages() {
        if (pendingMessages != NULL) {
                msgBox("Pending messages", pendingMessages->charrep());
                pendingMessages--;
                pendingMessages.resetPtr();
        }
}

/*...slb_wxFrame:0:*/

// My frame constructor
lb_wxFrame::lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h):
  wxFrame(frame, -1, title, wxPoint(x, y), wxSize(w, h))
, m_timer(this)
{
        OnQuitAccepted = false;
        menu_bar = NULL;
        guiCleanedUp = 0;
        stb_areas = 1;
        // Splitter window handling
        m_left = m_right = NULL;
        m_splitter = NULL;
        m_replacewindow = NULL;
		gelangweilt = false;
		timerrunning = false;

#ifdef SOLARIS
        skipfirstResizeEvent = true;
#endif

        _isSplitted = false;
}

lb_wxFrame::~lb_wxFrame() {
        _LOG << "lb_wxFrame::~lb_wxFrame() called." LOG_
        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaApp)

        metaApp->setGUIMaximized(IsMaximized());
        metaApp->save();


#ifdef USE_WXAUI
        wxPropertyGrid* oldpg = (wxPropertyGrid*) m_mgr.GetPane("Properties").window;

        if (oldpg) {
                m_mgr.DetachPane(oldpg);
                oldpg->Close();
        }

        // deinitialize the frame manager
        m_mgr.UnInit();
#endif
#ifdef USE_WXAUI_TOOLBAR
        wxPropertyGrid* oldpg = (wxPropertyGrid*) m_mgr.GetPane("Properties").window;

        if (oldpg) {
                m_mgr.DetachPane(oldpg);
                oldpg->Close();
        }

        // deinitialize the frame manager
        m_mgr.UnInit();
#endif

        if (guiCleanedUp == 0) {
                _LOG << "lb_wxFrame::~lb_wxFrame() Info: GUI cleanup has not yet been done. Do it now." LOG_
                if (gui) gui->cleanup();
                guiCleanedUp = 1;
        }
}

void LB_STDCALL lb_wxFrame::enableTimer(bool enable) {
	timerenabled = enable;
	if (!enable) {
		m_timer.Stop();
		timerrunning = false;
	}
}

void lb_wxFrame::OnTimer(wxTimerEvent& WXUNUSED(event)) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	// Don't tell too much useless stuff :-)
	if (isVerbose()) meta->setStatusText("Info", _trans("Timer ..."), false);
	m_timer.Stop();
	// Do timer stuff

	if (eman == NULL) {
		REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	}
	
	if (dispatcher == NULL) {
		// Create, but check if application didn't shutdown.
		_LOG << "Error: Dispatcher is not initialized. Assume an initialized dispatcher. Initialize it now." LOG_
		REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	}

	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
	
	parameter->setData("msg");
	value->setData("lb_wxFrame::OnTimer");
	param->setUAPString(*&parameter, *&value);
	parameter->setData("title");
	value->setData("Timer triggered");
	param->setUAPString(*&parameter, *&value);
	
	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	int event = 0;
	
	eman->resolveEvent("timerEvent", event);
	
	dispatcher->dispatch("timerEvent", uk.getPtr(), &uk_result);
	
	// Let OnIdle restart the timer...
	timerrunning = false;
}

void lb_wxFrame::OnIdle(wxIdleEvent& WXUNUSED(event))
{
	if (!timerrunning && timerenabled) {
		timerrunning = true;
		m_timer.Start(500);
	}
	
	if (!gelangweilt) {
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->setStatusText("Info", _trans("Gelangweilt ..."));
	}
}

/*...svoid lb_wxFrame\58\\58\OnRunLogonWizard\40\wxCommandEvent\38\ WXUNUSED\40\event\41\\41\:0:*/
void lb_wxFrame::OnRunLogonWizard(wxCommandEvent& WXUNUSED(event)) {
    wxWizard *wizard = new wxWizard(this, -1, _T("Anmeldung"));

    wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);

    wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

    wxSize size = text->GetBestSize();

    wxLogonPage *page2 = new wxLogonPage(wizard);
    wxAppSelectPage *page3 = new wxAppSelectPage(wizard);

    wxWizardPageSimple::Chain(page2, page3);

    wizard->SetPageSize(size);

    if ( wizard->RunWizard(page1) )
    {
        wxMessageBox(_T("The wizard successfully completed"), _T("That's all"),
                     wxICON_INFORMATION | wxOK);
    }

    wizard->Destroy();
}
/*...e*/

void lb_wxFrame::OnCloseCurrentPage(wxCommandEvent& WXUNUSED(event) )
{
        if (gui) gui->closeCurrentPage();
}

void lb_wxFrame::OnRefreshAll(wxCommandEvent& event) {
        if (gui) gui->refreshAll();
}

/*...slb_wxFrame\58\\58\OnQuit\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->save();

        /*
         * Let the lb_wxGUI class cleanup it's created  and hidden forms.
         * The database form sample is a modal form and may be making the
         * problem, if it is not destroyed here.
         */

        // Signalize that I am quitting.
        OnQuitAccepted = true;

        if (guiCleanedUp == 0) {
                if (gui) gui->cleanup();
                guiCleanedUp = 1;
        }


		// Done in OnExit in dynamic.cpp. Calling this twice actually let the datastructure be uninitialized
		// and thus the second call to deinitApplicationSwitcher fails
        meta->unloadApplication();
		meta->uninitialize();

        Close(TRUE);
}

void lb_wxFrame::OnVerbose(wxCommandEvent& WXUNUSED(event) ) {
    setVerbose(!isVerbose());
}

/*...e*/
/*...slb_wxFrame\58\\58\OnAbout\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  char* buf = strdup(_trans("This is the wxWindows GUI wrapper.\nA interface to any application."));
  char* buf1 = strdup(_trans("About wxWidgets GUI wrapper"));
  wxMessageDialog dialog(NULL, buf, buf1, wxOK);

  dialog.ShowModal();

  free(buf);
  free(buf1);
}
/*...e*/
#ifdef USE_WXAUI

//IMPLEMENT_CLASS(lb_wxFrame, wxFrame)

BEGIN_EVENT_TABLE(lb_wxFrame, wxFrame)
	EVT_TIMER(wxID_ANY, lb_wxFrame::OnTimer)
	EVT_IDLE(lb_wxFrame::OnIdle)
	EVT_PG_CHANGED( PGID, lb_wxFrame::OnPropertyGridChange )
    EVT_ERASE_BACKGROUND(lb_wxFrame::OnEraseBackground)
    EVT_SIZE(lb_wxFrame::OnSize)
END_EVENT_TABLE()


void lb_wxFrame::OnEraseBackground(wxEraseEvent& event)
{
        _CL_LOG << "OnEraseBackground() called for " << event.GetEventObject()->GetClassInfo()->GetClassName() << "." LOG_
    event.Skip();
}

void lb_wxFrame::OnSize(wxSizeEvent& event)
{
        _CL_LOG << "OnSize() called for " << event.GetEventObject()->GetClassInfo()->GetClassName() << "." LOG_
        //SetMinSize(event.GetSize());

#ifdef SOLARIS
#ifdef bla
        if (skipfirstResizeEvent == false) {
                m_mgr.Update();
                event.Skip();
        }
        skipfirstResizeEvent = false;
#endif
#endif
#ifndef SOLARIS
        m_mgr.Update();
        event.Skip();
#endif

}

#endif
#ifdef USE_WXAUI_TOOLBAR

//IMPLEMENT_CLASS(lb_wxFrame, wxFrame)

BEGIN_EVENT_TABLE(lb_wxFrame, wxFrame)
	EVT_TIMER(wxID_ANY, lb_wxFrame::OnTimer)
	EVT_IDLE(lb_wxFrame::OnIdle)
	EVT_PG_CHANGED( PGID, lb_wxFrame::OnPropertyGridChange )
    EVT_ERASE_BACKGROUND(lb_wxFrame::OnEraseBackground)
    EVT_SIZE(lb_wxFrame::OnSize)
END_EVENT_TABLE()


void lb_wxFrame::OnEraseBackground(wxEraseEvent& event)
{
        _CL_LOG << "OnEraseBackground() called for " << event.GetEventObject()->GetClassInfo()->GetClassName() << "." LOG_
    event.Skip();
}

void lb_wxFrame::OnSize(wxSizeEvent& event)
{
        _CL_LOG << "OnSize() called for " << event.GetEventObject()->GetClassInfo()->GetClassName() << "." LOG_
        //SetMinSize(event.GetSize());

#ifdef SOLARIS
#ifdef bla
        if (skipfirstResizeEvent == false) {
                m_mgr.Update();
                event.Skip();
        }
        skipfirstResizeEvent = false;
#endif
#endif
#ifndef SOLARIS
        m_mgr.Update();
        event.Skip();
#endif

}

#endif

/*...slb_wxFrame\58\\58\OnCheck\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnCheck(wxCommandEvent& WXUNUSED(event) ) {
        char ptr[200] = "";
        sprintf(ptr, "%p for instance %p", menu_bar, this);

        _LOG << "Have this instance now: " << ptr LOG_
}
/*...e*/
/*...slb_wxFrame\58\\58\OnBuildMenu\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnBuildMenu(wxCommandEvent& WXUNUSED(event) ) {
        wxMenu *menu = new wxMenu;
        wxMenuBar* mbar = NULL;

        menu->Append(DYNAMIC_ABOUT, "&About");
        menu->Append(DYNAMIC_QUIT, "E&xit");

        char ptr[200] = "";
        sprintf(ptr, "%p for instance %p", menu_bar, this);
        _LOG << "Request for a menu pointer: " << ptr LOG_

        mbar = getMenuBar();
        if (menu_bar) menu_bar->Append(menu, "T&est");

}
/*...e*/
/*...svoid lb_wxFrame\58\\58\OnPropertyGridChange \40\ wxPropertyGridEvent\38\ event \41\:0:*/
void lb_wxFrame::OnPropertyGridChange ( wxPropertyGridEvent& event )
{
        lbErrCodes err = ERR_NONE;

        wxPGProperty* pProperty = event.GetProperty();

        // Get name of changed property
        const wxString& PropertyName = event.GetPropertyName();

        wxString PropValue = pProperty->GetValueAsString();

        UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
        UAP_REQUEST(getModuleInstance(), lb_I_String, name)
        UAP_REQUEST(getModuleInstance(), lb_I_String, value)
        UAP_REQUEST(getModuleInstance(), lb_I_Integer, evId)

        int PropertyEvent;

        if (eman == NULL) {
                REQUEST(getModuleInstance(), lb_I_EventManager, eman)
        }

        eman->resolveEvent((const char*) PropertyName.c_str(), PropertyEvent);

        name->setData("eventId");
        evId->setData(PropertyEvent);
        param->setUAPInteger(*&name, *&evId);

        _LOG << "Property '" << PropertyName.c_str() << "' changed to '" << PropValue.c_str() << "'" LOG_

        name->setData("value");
        value->setData((const char*) PropValue.c_str());
        param->setUAPString(*&name, *&value);

        name->setData("name");
        value->setData((const char*) PropertyName.c_str());
        param->setUAPString(*&name, *&value);

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
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, pname)
		*pname = PropertyName.c_str();
		
		if (pname != NULL && *pname == "Application Database settingsDB Name")
		{
			if (PropValue.Trim() == "") {
				pProperty->GetGrid()->SetPropertyBackgroundColour(wxPGPropArgCls(pname->charrep()), *wxRED, wxPG_DONT_RECURSE);
			} else {
				pProperty->GetGrid()->SetPropertyBackgroundColour(wxPGPropArgCls(pname->charrep()), wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxPG_DONT_RECURSE);				
			}
		}
}
/*...e*/
/*...slb_wxFrame\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lb_wxFrame::OnDispatch(wxCommandEvent& event ) {
        lbErrCodes err = ERR_NONE;
        switch (event.GetId()) {
                case POST_PENDING_EVENT:
                        {
                                        // Unpack the event and dispatch accordingly
                                if (event.GetClientData() != NULL) {
                        lbErrCodes err = ERR_NONE;

                                        if (eman == NULL) {
                                                REQUEST(getModuleInstance(), lb_I_EventManager, eman)
                                        }

                                        if (dispatcher == NULL) {
                                                REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
                                                dispatcher->setEventManager(eman.getPtr());
                                        }

                                        UAP_REQUEST(getModuleInstance(), lb_I_Integer, param)

                                        UAP(lb_I_Container, eventToPost)
                                        UAP(lb_I_Unknown, uk)

                                        uk = (lb_I_Unknown*) event.GetClientData();
                                        QI(uk, lb_I_Container, eventToPost)

                                        UAP(lb_I_Unknown, ukName)
                                        UAP(lb_I_String, evName)
                                        UAP_REQUEST(getModuleInstance(), lb_I_String, evKeyName)
                                        UAP(lb_I_KeyBase, evKey)

                                        UAP(lb_I_Unknown, ukEventObject)

                                        *evKeyName = "EventName";
                                        QI(evKeyName, lb_I_KeyBase, evKey)

                                        ukName = eventToPost->getElement(&evKey);

                                        if (ukName != NULL) {
                                                QI(ukName, lb_I_String, evName)
                                        } else {
                                                _LOG << "Error: Required parameter is not in the container." LOG_
                                                return;
                                        }

                                        *evKeyName = "EventObject";
                                        QI(evKeyName, lb_I_KeyBase, evKey)

                                        ukEventObject = eventToPost->getElement(&evKey);

                                        if (ukEventObject != NULL) {
                                                int evID = 0;
                                                eman->resolveEvent(evName->charrep(), evID);

                                                UAP_REQUEST(getModuleInstance(), lb_I_String, result)
                                                UAP(lb_I_Unknown, uk_result)
                                                QI(result, lb_I_Unknown, uk_result)

                                                /* What do I when I have to forward the eventID as in the default?
                                                 * In the default portion, always an integer object is passed. It would
                                                 * be used for sample in the OnActionButton event handler for actions.
                                                 *
                                                 * So when posting an event that should trigger another OnActionButton event,
                                                 * it will fail due to the lack of integer parameter.
                                                 *
                                                 * So my question: Is there a need to post issue an OnActionButton event?
                                                 */
                                                dispatcher->dispatch(event.GetId(), ukEventObject.getPtr(), &uk_result);
                                        } else {
                                                _LOG << "Error: Required event object is not in the container." LOG_
                                                return;
                                        }
                                }
                        }
                break;
        case DYNAMIC_QUIT:
                OnQuit(event);
                break;
        case DYNAMIC_ABOUT:
                OnAbout(event);
                break;
        case DYNAMIC_VERBOSE:
                OnVerbose(event);
                break;
        case DYNAMIC_BUILDMENU:
                {
                        OnBuildMenu(event);
                }
                break;
        case SHOW_PENDING_MESSAGES:
                if (gui) {
                        gui->showPendingMessages();
                }
                break;
        default:
                // Delegate all other events
                {
                        lbErrCodes err = ERR_NONE;
                        lb_I_Module* m = getModuleInstance();

                        if (eman == NULL) {
                                REQUEST(m, lb_I_EventManager, eman)
                        }

                        if (dispatcher == NULL) {
                                REQUEST(m, lb_I_Dispatcher, dispatcher)
                                dispatcher->setEventManager(eman.getPtr());
                        }

                        UAP_REQUEST(m, lb_I_Integer, param)

                        param->setData(event.GetId());

                        UAP(lb_I_Unknown, uk)
                        QI(param, lb_I_Unknown, uk)

                        UAP_REQUEST(m, lb_I_String, result)
                        UAP(lb_I_Unknown, uk_result)
                        QI(result, lb_I_Unknown, uk_result)

                        dispatcher->dispatch(event.GetId(), uk.getPtr(), &uk_result);
                }
                break;
        }
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\setPreferredPropertyPanelByNamespace\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::setPreferredPropertyPanelByNamespace(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;

        UAP(lb_I_Parameter, param)
        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, _namespace)
        QI(uk, lb_I_Parameter, param)

        parameter->setData("namespace");
        param->getUAPString(*&parameter, *&_namespace);

        if (PanelNamespace == NULL) {
                REQUEST(getModuleInstance(), lb_I_String, PanelNamespace)
        }

        *PanelNamespace = _namespace->charrep();

        return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\showMsgBox\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::showMsgBox(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;

        UAP(lb_I_Parameter, param)
        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
        UAP_REQUEST(getModuleInstance(), lb_I_String, title)
        QI(uk, lb_I_Parameter, param)

        parameter->setData("msg");
        param->getUAPString(*&parameter, *&msg);
        parameter->setData("title");
        param->getUAPString(*&parameter, *&title);

        gui->msgBox(title->charrep(), msg->charrep());

        return err;
}
/*...e*/
/*...swxPropertyGrid\42\ lb_wxFrame\58\\58\CreatePropertyGrid\40\wxWindow\42\ parent\41\:0:*/
wxPropertyGrid* lb_wxFrame::CreatePropertyGrid(wxWindow* parent) {
        wxPropertyGrid* pg = new wxPropertyGrid(
                parent,
                PGID,
                wxPoint(0, 0),
                wxSize(160, 250),
                wxPG_AUTO_SORT |
                wxPG_DEFAULT_STYLE );

        if (currentProperties == NULL) {
#ifdef USE_PROPGRID_1_2_2
                pg->Append (wxIntProperty ( wxT("IntProperty"), wxPG_LABEL, 12345678 ) );
                pg->Append (wxFloatProperty ( wxT("FloatProperty"), wxPG_LABEL, 12345.678 ) );
                pg->Append (wxBoolProperty ( wxT("BoolProperty"), wxPG_LABEL, false ) );

                pg->Append (wxLongStringProperty (wxT("LongStringProperty"),
                   wxPG_LABEL,
                   wxT("This is much longer string than the ")
                   wxT("first one. Edit it by clicking the button.")));
#else
                pg->Append ( new wxIntProperty ( wxT("IntProperty"), wxPG_LABEL, 12345678 ) );
                pg->Append ( new wxFloatProperty ( wxT("FloatProperty"), wxPG_LABEL, 12345.678 ) );
                pg->Append ( new wxBoolProperty ( wxT("BoolProperty"), wxPG_LABEL, false ) );

                pg->Append ( new wxLongStringProperty (wxT("LongStringProperty"),
                   wxPG_LABEL,
                   wxT("This is much longer string than the ")
                   wxT("first one. Edit it by clicking the button.")));
#endif
        } else {
                UAP(lb_I_Container, parameter)
                parameter = currentProperties->getParameterList();
                populateProperties(pg, *&parameter);
        }

        return pg;
}
/*...e*/
/*...svoid lb_wxFrame\58\\58\populateFileLocation\40\wxPropertyGrid\42\ pg\44\ lb_I_Unknown\42\ uk\44\ lb_I_KeyBase\42\ name\44\ char\42\ category\41\:0:*/
void lb_wxFrame::populateFileLocation(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_FileLocation, s)
        UAP_REQUEST(getModuleInstance(), lb_I_String, category_name)
        QI(uk, lb_I_FileLocation, s)

        if (category) *category_name = category;
        *category_name += name->charrep();

#ifdef LBWXVERSION_CURRENT
        wxPGProperty* pgid = pg->GetPropertyByLabel(name->charrep());

        if (pgid != NULL) {
                pg->SetPropertyValueString(pgid, s->charrep());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxFileProperty (name->charrep(), category_name->charrep(), s->charrep()));
#else
                pg->Append(new wxFileProperty (name->charrep(), category_name->charrep(), s->charrep()));
#endif
        }
#else
        wxPGId pgid = pg->GetPropertyByLabel(name->charrep());
        
        if (wxPGIdIsOk(pgid)) {
                pg->SetPropertyValueString(pgid, s->charrep());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxFileProperty (name->charrep(), category_name->charrep(), s->charrep()));
#else
                pg->Append(new wxFileProperty (name->charrep(), category_name->charrep(), s->charrep()));
#endif
        }
#endif		
		
}
/*...e*/
/*...svoid lb_wxFrame\58\\58\populateDirLocation\40\wxPropertyGrid\42\ pg\44\ lb_I_Unknown\42\ uk\44\ lb_I_KeyBase\42\ name\44\ char\42\ category\41\:0:*/
void lb_wxFrame::populateDirLocation(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_DirLocation, s)
        UAP_REQUEST(getModuleInstance(), lb_I_String, category_name)
        QI(uk, lb_I_DirLocation, s)

        if (category) *category_name = category;
        *category_name += name->charrep();

#ifdef LBWXVERSION_CURRENT
        wxPGProperty* pgid = pg->GetPropertyByLabel(name->charrep());

        if (pgid != NULL) {
                pg->SetPropertyValueString(pgid, s->charrep());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxDirProperty (name->charrep(), category_name->charrep(), s->charrep()));
#else
                pg->Append(new wxDirProperty (name->charrep(), category_name->charrep(), s->charrep()));
#endif
        }
#else
        wxPGId pgid = pg->GetPropertyByLabel(name->charrep());

        if (wxPGIdIsOk(pgid)) {
                pg->SetPropertyValueString(pgid, s->charrep());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxDirProperty (name->charrep(), category_name->charrep(), s->charrep()));
#else
                pg->Append(new wxDirProperty (name->charrep(), category_name->charrep(), s->charrep()));
#endif
        }
#endif
}
/*...e*/
/*...svoid lb_wxFrame\58\\58\populateString\40\wxPropertyGrid\42\ pg\44\ lb_I_Unknown\42\ uk\44\ lb_I_KeyBase\42\ name\44\ char\42\ category\41\:0:*/
void lb_wxFrame::populateString(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_String, s)
        UAP_REQUEST(getModuleInstance(), lb_I_String, category_name)
        QI(uk, lb_I_String, s)

        if (category) *category_name = category;
        *category_name += name->charrep();

#ifdef LBWXVERSION_CURRENT
        wxPGProperty* pgid = pg->GetPropertyByLabel(name->charrep());

        if (pgid != NULL) {
                pg->SetPropertyValueString(pgid, s->charrep());
				
				UAP(lb_I_String, pname)
				QI(name, lb_I_String, pname)
				
				if (pname != NULL && *pname == "DB Name")
				{
					if (*s == "") {
						//wxPGPropArgCls id(pgid);
						pg->SetPropertyBackgroundColour(pgid, *wxRED, wxPG_DONT_RECURSE);
					} else {
						pg->SetPropertyBackgroundColour(pgid, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxPG_DONT_RECURSE);				
					}
				}
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxStringProperty (name->charrep(), category_name->charrep(), s->charrep()));
#else
                pg->Append(new wxStringProperty (name->charrep(), category_name->charrep(), s->charrep()));
#endif

				UAP(lb_I_String, pname)
				QI(name, lb_I_String, pname)
				
				if (pname != NULL && *pname == "DB Name")
				{
					s->trim();
				
					if (*s == "") {
						pg->SetPropertyBackgroundColour(wxPGPropArgCls(category_name->charrep()), *wxRED, wxPG_DONT_RECURSE);
					} else {
						pg->SetPropertyBackgroundColour(wxPGPropArgCls(category_name->charrep()), wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxPG_DONT_RECURSE);				
					}
				}

		}
#else
        wxPGId pgid = pg->GetPropertyByLabel(name->charrep());

        if (wxPGIdIsOk(pgid)) {
                pg->SetPropertyValueString(pgid, s->charrep());
				
				UAP(lb_I_String, pname)
				QI(name, lb_I_String, pname)
				
				if (pname != NULL && *pname == "DB Name")
				{
					if (*s == "") {
						//wxPGPropArgCls id(pgid);
						pg->SetPropertyBackgroundColour(pgid, *wxRED, wxPG_DONT_RECURSE);
					} else {
						pg->SetPropertyBackgroundColour(pgid, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxPG_DONT_RECURSE);				
					}
				}
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxStringProperty (name->charrep(), category_name->charrep(), s->charrep()));
#else
                pg->Append(new wxStringProperty (name->charrep(), category_name->charrep(), s->charrep()));
#endif

				UAP(lb_I_String, pname)
				QI(name, lb_I_String, pname)
				
				if (pname != NULL && *pname == "DB Name")
				{
					s->trim();
				
					if (*s == "") {
						pg->SetPropertyBackgroundColour(wxPGPropArgCls(category_name->charrep()), *wxRED, wxPG_DONT_RECURSE);
					} else {
						pg->SetPropertyBackgroundColour(wxPGPropArgCls(category_name->charrep()), wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxPG_DONT_RECURSE);				
					}
				}

		}
#endif
}
/*...e*/
/*...svoid lb_wxFrame\58\\58\populateBoolean\40\wxPropertyGrid\42\ pg\44\ lb_I_Unknown\42\ uk\44\ lb_I_KeyBase\42\ name\44\ char\42\ category\41\:0:*/
void lb_wxFrame::populateBoolean(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_Boolean, s)
        UAP_REQUEST(getModuleInstance(), lb_I_String, category_name)
        QI(uk, lb_I_Boolean, s)

        if (category) *category_name = category;
        *category_name += name->charrep();

#ifdef LBWXVERSION_CURRENT
        wxPGProperty* pgid = pg->GetPropertyByLabel(name->charrep());

        if (pgid != NULL) {
                pg->SetPropertyValue(pgid, s->getData());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxBoolProperty (name->charrep(), category_name->charrep(), s->getData()));
#else
                pg->Append(new wxBoolProperty (name->charrep(), category_name->charrep(), s->getData()));
#endif
        }
#else
        wxPGId pgid = pg->GetPropertyByLabel(name->charrep());
        
        if (wxPGIdIsOk(pgid)) {
                pg->SetPropertyValueBool(pgid, s->getData());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxBoolProperty (name->charrep(), category_name->charrep(), s->getData()));
#else
                pg->Append(new wxBoolProperty (name->charrep(), category_name->charrep(), s->getData()));
#endif
        }
#endif
}
/*...e*/
/*...svoid lb_wxFrame\58\\58\populateInteger\40\wxPropertyGrid\42\ pg\44\ lb_I_Unknown\42\ uk\44\ lb_I_KeyBase\42\ name\44\ char\42\ category\41\:0:*/
void lb_wxFrame::populateInteger(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_Integer, i)
        UAP_REQUEST(getModuleInstance(), lb_I_String, category_name)
        QI(uk, lb_I_Integer, i)

        _LOG << "Add integer property (" << name->charrep() << "): " << i->charrep() LOG_

        if (category) *category_name = category;
        *category_name += name->charrep();

#ifdef LBWXVERSION_CURRENT
        wxPGProperty* pgid = pg->GetPropertyByLabel(name->charrep());

        if (pgid != NULL) {
                pg->SetPropertyValue(pgid, i->getData());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxIntProperty (name->charrep(), category_name->charrep(), i->getData()));
#else
                pg->Append(new wxIntProperty (name->charrep(), category_name->charrep(), i->getData()));
#endif
        }
#else
        wxPGId pgid = pg->GetPropertyByLabel(name->charrep());
        
        if (wxPGIdIsOk(pgid)) {
                pg->SetPropertyValue(pgid, i->getData());
        } else {
#ifdef USE_PROPGRID_1_2_2
                pg->Append(wxIntProperty (name->charrep(), category_name->charrep(), i->getData()));
#else
                pg->Append(new wxIntProperty (name->charrep(), category_name->charrep(), i->getData()));
#endif
        }
#endif
}
/*...e*/
/*...svoid lb_wxFrame\58\\58\populateProperties\40\wxPropertyGrid\42\ pg\44\ lb_I_Container\42\ properties\44\ char\42\ category\41\:0:*/
void lb_wxFrame::populateProperties(wxPropertyGrid* pg, lb_I_Container* properties, char* category) {
        lbErrCodes err = ERR_NONE;
        if (properties == NULL) {
                _LOG << "Error: No properties given!" LOG_
                return;
        }

                for (int i = 1; i <= properties->Count(); i++) {
                        UAP(lb_I_Unknown, uk)
                        UAP(lb_I_KeyBase, key)

                        uk = properties->getElementAt(i);
                        key = properties->getKeyAt(i);

                        bool found = false;

                        if (strcmp(uk->getClassName(), "lbString") == 0) {
                                populateString(pg, *&uk, *&key, category);
                                found = true;
                        }
                        if (strcmp(uk->getClassName(), "lbDirLocation") == 0) {
                                populateDirLocation(pg, *&uk, *&key, category);
                                found = true;
                        }
                        if (strcmp(uk->getClassName(), "lbFileLocation") == 0) {
                                populateFileLocation(pg, *&uk, *&key, category);
                                found = true;
                        }
                        if (strcmp(uk->getClassName(), "lbInteger") == 0) {
                                populateInteger(pg, *&uk, *&key, category);
                                found = true;
                        }
                        if (strcmp(uk->getClassName(), "lbBoolean") == 0) {
                                populateBoolean(pg, *&uk, *&key, category);
                                found = true;
                        }
                        if (strcmp(uk->getClassName(), "lbParameter") == 0) {
                                UAP(lb_I_Container, props)
                                UAP(lb_I_Parameter, param)
                                QI(uk, lb_I_Parameter, param)

                                _CL_LOG << "Add property category: " << key->charrep() LOG_

#ifdef LBWXVERSION_CURRENT
                                pg->Append( new wxPropertyCategory(key->charrep()) );
#else
								pg->AppendCategory( key->charrep() );
#endif
                                props = param->getParameterList();

                                populateProperties(pg, *&props, key->charrep());
                                found = true;
                        }

                        if (found == false) {
                                _LOG << "No handler for parameter of type " << uk->getClassName() << " found." LOG_
                        }

                }
}
/*...e*/
/*...swxTreeCtrl\42\ lb_wxFrame\58\\58\CreateTreeCtrl\40\wxWindow\42\ parent\41\:0:*/
wxTreeCtrl* lb_wxFrame::CreateTreeCtrl(wxWindow* parent) {
    wxTreeCtrl* tree = new wxTreeCtrl(parent, -1,
                                      wxPoint(0,0), wxSize(160,250),
                                      wxTR_DEFAULT_STYLE | wxNO_BORDER);

    wxTreeItemId root = tree->AddRoot(wxT("wxAUI Project"));
    wxArrayTreeItemIds items;


    wxImageList* imglist = new wxImageList(16, 16, true, 2);
    imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
    imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
    tree->AssignImageList(imglist);

    items.Add(tree->AppendItem(root, wxT("Item 1"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 2"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 3"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 4"), 0));
    items.Add(tree->AppendItem(root, wxT("Item 5"), 0));


    int i, count;
    for (i = 0, count = items.Count(); i < count; ++i)
    {
        wxTreeItemId id = items.Item(i);
        tree->AppendItem(id, wxT("Subitem 1"), 1);
        tree->AppendItem(id, wxT("Subitem 2"), 1);
        tree->AppendItem(id, wxT("Subitem 3"), 1);
        tree->AppendItem(id, wxT("Subitem 4"), 1);
        tree->AppendItem(id, wxT("Subitem 5"), 1);
    }


    tree->Expand(root);

    return tree;
}
/*...e*/

wxPoint lb_wxFrame::GetStartPosition()
{
    static int x = 0;
    x += 20;
    //wxPoint pt = ClientToScreen(::wxGetMousePosition());
    //return wxPoint(pt.x + x, pt.y + x);
	return ::wxGetMousePosition();
}

lbErrCodes LB_STDCALL lb_wxFrame::removeToolBar(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
#ifndef USE_WXAUI_TOOLBAR
        wxToolBar* tb;
#endif
#ifdef USE_WXAUI_TOOLBAR
        wxAuiToolBar* tb;
#endif
        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, name)

        UAP(lb_I_Parameter, params)
        QI(uk, lb_I_Parameter, params)

        if (params != NULL) {
                err = ERR_NONE;

                *parameter = "toolbarName";
                params->getUAPString(*&parameter, *&name);

#ifdef USE_WXAUI
                tb = (wxToolBar*) m_mgr.GetPane(name->charrep()).window;
				if (tb != NULL) {
					m_mgr.DetachPane(tb);
					m_mgr.Update();
					tb->Destroy();
				}
#endif
#ifdef USE_WXAUI_TOOLBAR
                tb = (wxAuiToolBar*) m_mgr.GetPane(name->charrep()).window;
				if (tb != NULL) {
					m_mgr.DetachPane(tb);
					m_mgr.Update();
					tb->Destroy();
				}
#endif
        }

        return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\addToolBar\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::addToolBar(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
#ifndef USE_WXAUI_TOOLBAR
        wxToolBar* tb;
#endif
#ifdef USE_WXAUI_TOOLBAR
        wxAuiToolBar* tb;
#endif

        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, name)

        UAP(lb_I_Parameter, params)
        QI(uk, lb_I_Parameter, params)

        if (params != NULL) {
                err = ERR_NONE;

                *parameter = "toolbarName";
                params->getUAPString(*&parameter, *&name);
        }

/*...sInit main toolbar \40\exit tool\41\:8:*/
#ifdef USE_WXAUI_TOOLBAR
        wxAuiToolBar* maintb;
#endif
#ifndef USE_WXAUI_TOOLBAR
        wxToolBar* maintb;
#endif

#ifdef USE_WXAUI_TOOLBAR
        maintb = (wxAuiToolBar*) m_mgr.GetPane("Main Toolbar").window;
#endif
#ifndef USE_WXAUI_TOOLBAR
        maintb = (wxToolBar*) m_mgr.GetPane("Main Toolbar").window;
#endif

        if (maintb == NULL) {
#ifdef USE_WXAUI_TOOLBAR
				wxAuiToolBarItemArray prepend_items;
				wxAuiToolBarItemArray append_items;

				maintb = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE); // | wxAUI_TB_OVERFLOW);
				maintb->SetCustomOverflowItems(prepend_items, append_items);
#endif
#ifdef USE_WXAUI
                maintb = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
#endif

#ifdef USE_WXAUI
                m_mgr.AddPane(maintb, wxAuiPaneInfo().
							Name(wxT("Main Toolbar")).Caption("Main Toolbar").
							ToolbarPane().Top().
							Fixed().
							LeftDockable(false).RightDockable(false));
                m_mgr.Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
				m_mgr.AddPane(maintb, wxAuiPaneInfo().
							Name("Main Toolbar").Caption("Main Toolbar").
							ToolbarPane().Top().
							Fixed().
							LeftDockable(false).RightDockable(false));
#endif

                wxImage::AddHandler(new wxXPMHandler);
                wxImage::AddHandler(new wxPNGHandler);

                maintb->SetToolBitmapSize(wxSize(32, 32));

                UAP_REQUEST(getModuleInstance(), lb_I_String, toolbarfile)
                UAP_REQUEST(getModuleInstance(), lb_I_String, images)
                UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, app)

                *toolbarfile += app->getDirLocation();

#ifdef OSX
                *images = "/toolbarimages/";
#endif
#ifdef LINUX
                *images = "/toolbarimages/";
#endif
#ifdef WINDOWS
                *images = "\\toolbarimages\\";
#endif
                *toolbarfile += images->charrep();

#ifdef OSX
                if (opendir(toolbarfile->charrep()) == NULL) {
                        UAP(lb_I_String, pName)
                        pName = app->getProcessName();
                        *toolbarfile = "./";
                        *toolbarfile += pName->charrep();
                        *toolbarfile += ".app/Contents/Resources/toolbarimages/";
                }
#endif

                *toolbarfile += "exit.png";


                if (!wxFile::Exists(toolbarfile->charrep())) {
                    // Fallback
#ifdef OSX
#endif
#ifdef LINUX
                    *toolbarfile = "/usr/share/lbdmf";
                    *toolbarfile += images->charrep();
                    *toolbarfile += "exit.png";
#endif
#ifdef WINDOWS
#endif
                }

                wxImage* im;

                im = new wxImage(toolbarfile->charrep(), wxBITMAP_TYPE_PNG);

#ifdef LBWXVERSION_CURRENT
				wxVector<wxBitmap> bitmaps;
                wxBitmap bm = wxBitmap(*im);
				bitmaps.push_back(bm);

                maintb->AddTool(DYNAMIC_QUIT, (const char*) _trans("Exit"), bm);
#else
                wxBitmap bm = wxBitmap(*im);

                maintb->AddTool(DYNAMIC_QUIT, bm, _trans("Exit"));
#endif
                maintb->Realize();

#ifdef USE_WXAUI_TOOLBAR
                wxSize s = wxSize(maintb->GetToolBitmapSize().GetWidth()*maintb->GetToolCount(), maintb->GetToolBitmapSize().GetHeight());
#endif
#ifdef USE_WXAUI
                wxSize s = wxSize(maintb->GetToolSize().GetWidth()*maintb->GetToolsCount(), maintb->GetToolSize().GetHeight());
#endif

                maintb->SetSize(s);
                maintb->SetMinSize(s);
                maintb->Fit();

#ifndef USE_WXAUI
#ifndef USE_WXAUI_TOOLBAR
                SetToolBar(maintb);
#endif
#endif

#ifdef USE_WXAUI
                m_mgr.DetachPane(maintb);

                m_mgr.AddPane(maintb, wxAuiPaneInfo().
                          Name("Main Toolbar").Caption("Main Toolbar").
                          ToolbarPane().Top().
                          Fixed().
                          LeftDockable(false).RightDockable(false));
                m_mgr.Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
                m_mgr.DetachPane(maintb);

                m_mgr.AddPane(maintb, wxAuiPaneInfo().
                          Name("Main Toolbar").Caption("Main Toolbar").
                          ToolbarPane().Top().
                          Fixed().
                          LeftDockable(false).RightDockable(false));
                m_mgr.Update();
#endif
        }
/*...e*/

#ifndef USE_WXAUI
#ifndef USE_WXAUI_TOOLBAR
        tb = GetToolBar();
#endif
#endif
#ifdef USE_WXAUI
        tb = (wxToolBar*) m_mgr.GetPane(name->charrep()).window;
#endif
#ifdef USE_WXAUI_TOOLBAR
        tb = (wxAuiToolBar*) m_mgr.GetPane(name->charrep()).window;
#endif

        if ((tb == NULL) && (params != NULL)) {
#ifdef USE_WXAUI_TOOLBAR
				wxAuiToolBarItemArray prepend_items;
				wxAuiToolBarItemArray append_items;

				tb = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE); // | wxAUI_TB_OVERFLOW);
				tb->SetCustomOverflowItems(prepend_items, append_items);
#endif
#ifdef USE_WXAUI
                tb = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
#endif

                wxImage::AddHandler(new wxXPMHandler);
                wxImage::AddHandler(new wxPNGHandler);

                tb->SetToolBitmapSize(wxSize(32, 32));

                err = ERR_NONE;

                *parameter = "toolbarName";
                params->getUAPString(*&parameter, *&name);

                wxImage::AddHandler(new wxXPMHandler);
                wxImage::AddHandler(new wxPNGHandler);

#ifndef USE_WXAUI
#ifndef USE_WXAUI_TOOLBAR
                SetToolBar(tb);
#endif
#endif

				//tb->Realize();

#ifdef USE_WXAUI
                m_mgr.AddPane(tb, wxAuiPaneInfo().
										Name(name->charrep()).Caption(name->charrep()).
										ToolbarPane().Top().
										//Fixed().
										LeftDockable(false).RightDockable(false));
                m_mgr.Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
				m_mgr.AddPane(tb, wxAuiPaneInfo().
										Name(name->charrep()).Caption(name->charrep()).
										ToolbarPane().Top().
										//Fixed().
										LeftDockable(false).RightDockable(false));
                m_mgr.Update();
#endif

                return ERR_NONE;
        }

        return err;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\addTool_To_ToolBar\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::addTool_To_ToolBar(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
        UAP(lb_I_Parameter, params)

        QI(uk, lb_I_Parameter, params)

        if (params != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
                UAP_REQUEST(getModuleInstance(), lb_I_String, name)
                UAP_REQUEST(getModuleInstance(), lb_I_String, tooltype)
                UAP_REQUEST(getModuleInstance(), lb_I_String, entry)
                UAP_REQUEST(getModuleInstance(), lb_I_String, evHandler)
                UAP_REQUEST(getModuleInstance(), lb_I_String, toolbarimage)

                *parameter = "toolbarName";
                params->getUAPString(*&parameter, *&name);
                *parameter = "tooltype";
                params->getUAPString(*&parameter, *&tooltype);
                *parameter = "entry";
                params->getUAPString(*&parameter, *&entry);
                *parameter = "evHandler";
                params->getUAPString(*&parameter, *&evHandler);
                *parameter = "toolbarimage";
                params->getUAPString(*&parameter, *&toolbarimage);

        toolbarimage->trim();

        if (*toolbarimage == "") {
            _LOG << "Error: Could not add a tool with no image file name. It is an empty string!" LOG_
            return ERR_NONE;
        }

#ifdef USE_WXAUI_TOOLBAR
                wxAuiToolBar* tb;
#endif
#ifdef USE_WXAUI
                wxToolBar* tb;
#endif

#ifndef USE_WXAUI
#ifndef USE_WXAUI_TOOLBAR
                tb = GetToolBar();
#endif
#endif
#ifdef USE_WXAUI_TOOLBAR
                tb = (wxAuiToolBar*) m_mgr.GetPane(name->charrep()).window;
#endif
#ifdef USE_WXAUI
                tb = (wxToolBar*) m_mgr.GetPane(name->charrep()).window;
#endif

                if (tb != NULL) {
                        UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)

                        int EvNr = 0;

                        if (ev_manager->resolveEvent(evHandler->getData(), EvNr) == ERR_EVENT_NOTREGISTERED) {
                                _CL_LOG << "ERROR: Could not resolve a toolbar entry (" << entry->charrep() << ")" LOG_

                                return ERR_EVENT_NOTREGISTERED;
                        }

                        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, app)

                        UAP_REQUEST(getModuleInstance(), lb_I_String, toolbarfile)
                        UAP_REQUEST(getModuleInstance(), lb_I_String, images)

                        *toolbarfile = app->getDirLocation();

#ifdef OSX
                        *images = "/toolbarimages/";
#endif
#ifdef LINUX
                        *images = "/toolbarimages/";
#endif
#ifdef WINDOWS
                        *images = "\\toolbarimages\\";
#endif
                        *toolbarfile += images->charrep();

#ifdef OSX
                        if (opendir(toolbarfile->charrep()) == NULL) {
                                UAP(lb_I_String, pName)
                                pName = app->getProcessName();
                                *toolbarfile = "./";
                                *toolbarfile += pName->charrep();
                                *toolbarfile += ".app/Contents/Resources/toolbarimages/";
                        }
#endif

                        *toolbarfile += toolbarimage->charrep();

                        if (!wxFile::Exists(toolbarfile->charrep())) {
                            // Fallback
#ifdef OSX
#endif
#ifdef LINUX
                            *toolbarfile = "/usr/share/lbdmf";
                            *toolbarfile += images->charrep();
                            *toolbarfile += toolbarimage->charrep();
#endif
#ifdef WINDOWS
#endif
                        }


                        _LOG << "Add a toolbar tool with image '" << toolbarfile->charrep() << "'" LOG_

                        wxString f = wxString(toolbarimage->charrep());

                        wxImage* im;

                        if (f.Upper().Contains(".XPM") == 1) {
                                im = new wxImage(toolbarfile->charrep(), wxBITMAP_TYPE_XPM);
                        }

                        if (f.Upper().Contains(".PNG") == 1) {
                                im = new wxImage(toolbarfile->charrep(), wxBITMAP_TYPE_PNG);
                        }

#ifdef LBWXVERSION_CURRENT
						wxVector<wxBitmap> bitmaps;
						wxBitmap bm = wxBitmap(*im);
						bitmaps.push_back(bm);

                        tb->AddTool(EvNr, entry->charrep(), bm);
#else
						wxBitmap bm = wxBitmap(*im);

                        tb->AddTool(EvNr, bm, entry->charrep());
#endif
                        tb->Realize();

#ifdef USE_WXAUI_TOOLBAR
                        _LOG << "Toolbar size is " << (long) tb->GetToolCount() << "." LOG_
#endif
#ifdef USE_WXAUI
                        _LOG << "Toolbar size is " << (long) tb->GetToolsCount() << "." LOG_
#endif

                        //wxSize s = wxSize(tb->GetSize().GetHeight()*tb->GetToolsCount(), tb->GetSize().GetHeight());
						//tb->Fit();
                        //tb->SetSize(wxSize(tb->GetSize().GetWidth()+5, tb->GetSize().GetHeight()+5));
						//tb->Fit();

#ifdef USE_WXAUI
                        wxToolBar* maintb = (wxToolBar*) m_mgr.GetPane("Main Toolbar").window;
                        m_mgr.DetachPane(maintb);

						// Keep Main Toolbar the most left one
                        m_mgr.AddPane(maintb, wxAuiPaneInfo().
								Name("Main Toolbar").Caption("Main Toolbar").
								ToolbarPane().Top().
								LeftDockable(false).RightDockable(false));

                        m_mgr.DetachPane(tb);
                        m_mgr.AddPane(tb, wxAuiPaneInfo().
                                  Name(name->charrep()).Caption(name->charrep()).
                                  ToolbarPane().Top().
                                  LeftDockable(false).RightDockable(false));

						m_mgr.Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
                        wxAuiToolBar* maintb = (wxAuiToolBar*) m_mgr.GetPane("Main Toolbar").window;
                        m_mgr.DetachPane(maintb);

						// Keep Main Toolbar the most left one
						m_mgr.AddPane(maintb, wxAuiPaneInfo().
								Name("Main Toolbar").Caption("Main Toolbar").
								ToolbarPane().Top().
								LeftDockable(false).RightDockable(false));

                        m_mgr.DetachPane(tb);
                        m_mgr.AddPane(tb, wxAuiPaneInfo().
                                  Name(name->charrep()).Caption(name->charrep()).
                                  ToolbarPane().Top().
                                  LeftDockable(false).RightDockable(false));
                        
						m_mgr.Update();
#endif

                }

                err = ERR_NONE;
        }
        return err;

}
/*...e*/

lbErrCodes LB_STDCALL lb_wxFrame::removeTool_From_ToolBar(lb_I_Unknown* uk) {
        return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_wxFrame::toggleTool_From_ToolBar(lb_I_Unknown* uk) {
        return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_wxFrame::openWebPage(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
        UAP(lb_I_Parameter, param)
        QI(uk, lb_I_Parameter, param)

		if (param == NULL) {
			_LOGERROR << "lb_wxFrame::openWebPage() Error: Called with a wrong parameter type. Expected lb_I_Parameter." LOG_
			return err;
		}
		
        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, url)
        UAP_REQUEST(getModuleInstance(), lb_I_String, pagename)

        *parameter = "URL";
        param->getUAPString(*&parameter, *&url);
        *parameter = "URL";
        param->getUAPString(*&parameter, *&pagename);

		gui->openWebPage(pagename->charrep(), url->charrep());
		
        return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\addStatusBar\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::addStatusBar(lb_I_Unknown* uk) {
        wxStatusBar *sb = GetStatusBar();
        if (sb == NULL) {
                wxStatusBar* statusBar = new wxStatusBar(this, wxID_ANY, wxST_SIZEGRIP);
                stb_withs = new int[stb_areas];
                stb_withs[0] = -1;
                stb_areas = 1;

                statusBar->SetStatusWidths(stb_areas, stb_withs);
                statusBar->SetStatusText(wxT("Ready"), 0);

                SetStatusBar(statusBar);
        } else {
                if (stb_withs == NULL) {
                                gui->msgBox("Error", "Statusbar withs fields array is not implemented!");
                } else {

                        _LOG << "Set status bar field count to " << stb_areas LOG_
                        sb->SetFieldsCount(stb_areas, NULL);
                        sb->SetStatusText(wxT("Ready"), 0);
                }
        }

        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\addStatusBarTextArea\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::addStatusBarTextArea(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;

        UAP_REQUEST(getModuleInstance(), lb_I_Integer, index)
        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, name)

        UAP(lb_I_Parameter, param)
        UAP(lb_I_KeyBase, key)
        UAP(lb_I_Unknown, value)

        if (statusbar_name_mappings == NULL) {
                REQUEST(getModuleInstance(), lb_I_Container, statusbar_name_mappings)
        }

        QI(uk, lb_I_Parameter, param)
        QI(index, lb_I_Unknown, value)

        *parameter = "Name";
        param->getUAPString(*&parameter, *&name);
        QI(name, lb_I_KeyBase, key)

        if (key != NULL) {
			if (statusbar_name_mappings->exists(&key) == 0) {
				int* new_stb_withs = new int [stb_areas];
				int* old_stb_withs;

				stb_areas++;

                for (int i = 1; i < stb_areas; i++) {
                        new_stb_withs[i-1] = stb_withs[i-1];
                }
                new_stb_withs[stb_areas-1] = -1;
                old_stb_withs = stb_withs;

                stb_withs = new_stb_withs;
                addStatusBar(uk);

                delete[] old_stb_withs;

                index->setData(stb_areas);

                statusbar_name_mappings->insert(&value, &key);

                err = ERR_NONE;
			}
        }

        return err;
}
/*...e*/

lbErrCodes LB_STDCALL lb_wxFrame::removeStatusBarTextArea(lb_I_Unknown* uk) {
        return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_wxFrame\58\\58\setText_To_StatusBarTextArea\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::setText_To_StatusBarTextArea(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
        UAP(lb_I_Parameter, params)

        QI(uk, lb_I_Parameter, params)

        if (OnQuitAccepted) return ERR_NONE; // Skip the action from now on.

	if (statusbar_name_mappings == NULL) return ERR_NONE;

        if (params != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
                UAP_REQUEST(getModuleInstance(), lb_I_String, name)
				UAP_REQUEST(getModuleInstance(), lb_I_String, value)
				UAP_REQUEST(getModuleInstance(), lb_I_String, CallYield)

                *parameter = "Name";
                params->getUAPString(*&parameter, *&name);
                *parameter = "Value";
                params->getUAPString(*&parameter, *&value);
				*parameter = "CallYield";
				params->getUAPString(*&parameter, *&CallYield);

                UAP(lb_I_KeyBase, key)
                QI(name, lb_I_KeyBase, key)

                UAP(lb_I_Integer, index)
                UAP(lb_I_Unknown, uk_index)
                uk_index = statusbar_name_mappings->getElement(&key);
                QI(uk_index, lb_I_Integer, index)

                wxStatusBar* sb = GetStatusBar();
                if (sb != NULL) {
                    sb->SetStatusText(value->charrep(), index->getData() - 1);
                    sb->Update();
					//if ((CallYield->charrep() != NULL) && (*CallYield == "true")) wxYield();
					if (*value == _trans("Gelangweilt ...")) {
						gelangweilt = true;
					} else {
						gelangweilt = false;
					}
                }

                err = ERR_NONE;
        }

        return err;
}
/*...e*/

lbErrCodes LB_STDCALL lb_wxFrame::postEvent(lb_I_Unknown* uk) {
/// \todo Implement this.
        lbErrCodes err = ERR_NONE;

        UAP(lb_I_Container, eventToPost)

        QI(uk, lb_I_Container, eventToPost)

        if (eventToPost != NULL) {
                // Get the event name to be used when the event has been triggered.
                UAP(lb_I_Unknown, ukName)
                UAP(lb_I_String, evName)
                UAP_REQUEST(getModuleInstance(), lb_I_String, evKeyName)
                UAP(lb_I_KeyBase, evKey)

                UAP(lb_I_Unknown, ukEventObject)

                *evKeyName = "EventName";
                QI(evKeyName, lb_I_KeyBase, evKey)

                ukName = eventToPost->getElement(&evKey);

                if (ukName != NULL) {
                        QI(ukName, lb_I_String, evName)
                } else {
                        _LOG << "Error: Required parameter is not in the container." LOG_
                        return ERR_DISPATCH_PARAMETER_WRONG;
                }

                *evKeyName = "EventObject";
                QI(evKeyName, lb_I_KeyBase, evKey)

                ukEventObject = eventToPost->getElement(&evKey);

                if (ukEventObject != NULL) {
                        // Have the name and the object. Pack it into the wxWidgets event instance and Post the event. This may be unsave.

                        // Avoid too early destroy, because wxWidgets does not support my reference counting.
                        uk++;

                        wxCommandEvent wxEv = wxCommandEvent(0, POST_PENDING_EVENT);

                        wxEv.SetClientData((void*) *&uk);

                        AddPendingEvent(wxEv);
                } else {
                        _LOG << "Error: Required event object is not in the container." LOG_
                        return ERR_DISPATCH_PARAMETER_WRONG;
                }
        } else {
                _LOG << "Error: Given parameter is not of type lb_I_Containerr." LOG_
                return ERR_DISPATCH_PARAMETER_WRONG;
        }

        return ERR_NONE;
}

wxTreeItemId* lb_wxFrame::lookupTreeItemId(lb_I_String* name) {
	wxTreeItemId* item = NULL;

	return NULL;
}

lbErrCodes LB_STDCALL lb_wxFrame::addTreeViewNode(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;

	UAP_REQUEST(getModuleInstance(), lb_I_Integer, index)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_Parameter, param)
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, value)

	QI(uk, lb_I_Parameter, param)
	QI(index, lb_I_Unknown, value)

	*parameter = "TreePath";
	param->getUAPString(*&parameter, *&name);
	QI(name, lb_I_KeyBase, key)

	if (key != NULL) {
		wxTreeItemId* tid = lookupTreeItemId(*&name);

		if (tid == NULL) {
			UAP(lb_I_String, left)
			left = name->left(name->rstrpos("/"));
			tid = lookupTreeItemId(*&left);

			if (tid == NULL) {
				_LOG << "Error: Parent tree item not found. (" << left->charrep() << ")" LOG_
				return err;
			}
			err = ERR_NONE;
		}
	}

	return err;
}

lbErrCodes LB_STDCALL lb_wxFrame::delTreeViewNode(lb_I_Unknown* uk) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_wxFrame::replaceTreeViewNode(lb_I_Unknown* uk) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_wxFrame::showLeftTreeView(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

#ifdef USE_WXAUI
	wxTreeCtrl* oldpg = (wxTreeCtrl*) m_mgr.GetPane("TreeView").window;

	if (oldpg != NULL) {
		_LOG << "Replace old treeview values..." LOG_

		//UAP(lb_I_Container, parameter)
		//parameter = currentProperties->getParameterList();
		//populateProperties(oldpg, *&parameter);

		m_mgr.GetPane("TreeView").Show();

		m_mgr.Update();

		return ERR_NONE;
	}
#endif


#ifdef USE_WXAUI
	wxWindow* leftPanel = NULL;
#ifdef IN_PANEL
	wxScrolledWindow* panel = new wxScrolledWindow(this, -1);
#endif


#ifdef IN_PANEL
	wxTreeCtrl* tv = new wxTreeCtrl(panel, -1, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS, wxDefaultValidator, "treeCtrl");
	leftPanel = panel;
#endif
#ifndef IN_PANEL
	wxTreeCtrl* tv = new wxTreeCtrl(this, -1, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS, wxDefaultValidator, "treeCtrl");
	leftPanel = tv;
#endif

	leftPanel->SetAutoLayout(TRUE);
	tv->SetAutoLayout(TRUE);

	m_mgr.AddPane(tv, wxAuiPaneInfo().
				  Name(wxT("TreeView")).Caption(wxT("TreeView")).
				  Left().
				  FloatingSize(wxSize(300,200)));

	m_mgr.Update();
#endif

	return err;
}

lbErrCodes LB_STDCALL lb_wxFrame::showLeftPropertyBar(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;

        if (currentProperties == NULL) {
                REQUEST(getModuleInstance(), lb_I_Parameter, currentProperties)
        }

        // Fill optionally given bunch of parameters
        UAP(lb_I_Parameter, params)
        QI(uk, lb_I_Parameter, params)
        if (params != NULL) {

                if (params->Count() > 0) {
                        currentProperties--;
                        currentProperties.resetPtr();
                        REQUEST(getModuleInstance(), lb_I_Parameter, currentProperties)

                        currentProperties->setData(uk);

                        // Fill up the properties from meta application
                        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
                        UAP_REQUEST(getModuleInstance(), lb_I_String, group)
                        UAP(lb_I_Parameter, param)

                        param = meta->getParameter();

                        group->setData("General");

                        currentProperties->setUAPParameter(*&group, *&param);
                }
/*
        } else {
                _LOG << "No optional properties given. Do nothing." LOG_
                return ERR_NONE;
*/
        }


#ifdef USE_WXAUI_TOOLBAR
        wxPropertyGrid* oldpg = (wxPropertyGrid*) m_mgr.GetPane("Properties").window;

        if (oldpg != NULL) {
                _LOG << "Replace old property values..." LOG_

                UAP(lb_I_Container, parameter)
                parameter = currentProperties->getParameterList();
                populateProperties(oldpg, *&parameter);

                m_mgr.GetPane("Properties").Show();

                m_mgr.Update();

                return ERR_NONE;
        }
#endif
#ifdef USE_WXAUI
        wxPropertyGrid* oldpg = (wxPropertyGrid*) m_mgr.GetPane("Properties").window;

        if (oldpg != NULL) {
                _LOG << "Replace old property values..." LOG_

                UAP(lb_I_Container, parameter)
                parameter = currentProperties->getParameterList();
                populateProperties(oldpg, *&parameter);

                m_mgr.GetPane("Properties").Show();

                m_mgr.Update();

                return ERR_NONE;
        }
#endif

/*...sNo wxAUI:0:*/
#ifndef USE_WXAUI
#ifndef USE_WXAUI_TOOLBAR
        if (m_splitter == NULL) {
                m_splitter = new wxSplitterWindow(this, wxID_ANY,
                          wxDefaultPosition, wxDefaultSize,
                          wxSP_3D | wxSP_LIVE_UPDATE /*| wxCLIP_CHILDREN*/ /* | wxSP_NO_XP_THEME */ );

                wxList children = GetChildren();
                wxNode* node = children.GetFirst();

                if (children.IsEmpty()) {
                        _CL_LOG << "Warning: No child window found." LOG_

                        wxPanel* leftPanel = new wxPanel(m_splitter);

                        m_splitter->Initialize(leftPanel);
                } else {
                        wxWindow *current = (wxWindow*) node->GetData();

                        // Select a proper implementation based on default or plugin availability
                        wxWindow* leftPanel = NULL;

                        //                      if (PanelNamespace == NULL)
                        //                              leftPanel = new wxScrolledWindow(m_splitter);
                        //                              else {
#ifdef IN_PANEL
                        wxPanel* panel = new wxPanel(m_splitter,-1);
                        wxPropertyGrid* pg = CreatePropertyGrid(panel);
                        leftPanel = panel;
#endif
#ifndef IN_PANEL
                        wxPropertyGrid* pg = CreatePropertyGrid(this);
                        leftPanel = pg;
#endif
#ifndef USE_PROPGRID
                        leftPanel = new wxScrolledWindow(m_splitter);
#endif
                        //                              }

                        wxBoxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
                        wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);
                        wxBoxSizer* sizerLeft = new wxBoxSizer(wxVERTICAL);

                        current->Reparent(m_splitter);

                        sizerMain->Add(m_splitter, 1, wxEXPAND, 0);
                        sizerLeft->Add(leftPanel, 1, wxEXPAND, 0);
                        sizerRight->Add(current, 1, wxEXPAND, 0);

                        current->SetSizer(sizerRight);
                        current->SetAutoLayout(TRUE);

                        m_splitter->SetSizer(sizerMain);
                        m_splitter->SetAutoLayout(TRUE);

                        leftPanel->SetSizer(sizerLeft);
                        leftPanel->SetAutoLayout(TRUE);

                        SetSizer(sizerMain);

                        //sizerMain->SetSizeHints( this );

                        //m_splitter->Initialize(leftPanel);
                        m_splitter->SplitVertically(leftPanel, current, 200);

                        Layout();
                        Fit();

                        _isSplitted = true;

                        _CL_LOG << "Done activating splitter ..." LOG_
                }
        }
#endif
#endif
/*...e*/

#ifdef USE_WXAUI
                wxList children = GetChildren();
                wxNode* node = children.GetFirst();

                wxWindow* leftPanel = NULL;
#ifdef IN_PANEL
                wxScrolledWindow* panel = new wxScrolledWindow(this, -1);
#endif


#ifdef IN_PANEL
                wxPropertyGrid* pg = CreatePropertyGrid(panel);
                leftPanel = panel;
#endif
#ifndef IN_PANEL
                wxPropertyGrid* pg = CreatePropertyGrid(this);
                leftPanel = pg;
#endif

                leftPanel->SetAutoLayout(TRUE);
                pg->SetAutoLayout(TRUE);
/*
                wxSizer* s = GetSizer();

                if (s != NULL) {
                        _CL_LOG << "Got the sizer object..." LOG_
                        s->Add(leftPanel, 1, wxEXPAND | wxALL, 0);
                }

                pg->SetSizeHints(leftPanel->GetSize());
*/


                m_mgr.AddPane(pg, wxAuiPaneInfo().
                        Name(wxT("Properties")).Caption(wxT("Properties")).
                        //Float().FloatingPosition(GetStartPosition()).
                        Left().
                        FloatingSize(wxSize(300,200)));

                m_mgr.Update();
#endif
#ifdef USE_WXAUI_TOOLBAR
                wxList children = GetChildren();
                wxNode* node = children.GetFirst();

                wxWindow* leftPanel = NULL;
#ifdef IN_PANEL
                wxScrolledWindow* panel = new wxScrolledWindow(this, -1);
#endif


#ifdef IN_PANEL
                wxPropertyGrid* pg = CreatePropertyGrid(panel);
                leftPanel = panel;
#endif
#ifndef IN_PANEL
                wxPropertyGrid* pg = CreatePropertyGrid(this);
                leftPanel = pg;
#endif

                leftPanel->SetAutoLayout(TRUE);
                pg->SetAutoLayout(TRUE);
/*
                wxSizer* s = GetSizer();

                if (s != NULL) {
                        _CL_LOG << "Got the sizer object..." LOG_
                        s->Add(leftPanel, 1, wxEXPAND | wxALL, 0);
                }

                pg->SetSizeHints(leftPanel->GetSize());
*/


                m_mgr.AddPane(pg, wxAuiPaneInfo().
                        Name(wxT("Properties")).Caption(wxT("Properties")).
                        //Float().FloatingPosition(GetStartPosition()).
                        Left().
                        FloatingSize(wxSize(300,200)));

                m_mgr.Update();
#endif

        return ERR_NONE;
}
/*...e*/


lbSplashScreen::lbSplashScreen(lb_I_GUI* gui, const wxBitmap& bitmap, long splashStyle, int milliseconds, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
  wxSplashScreen(bitmap, splashStyle, milliseconds, parent, id, pos, size, style)
{
        _gui = gui;
}

lbSplashScreen::~lbSplashScreen() {
        if (_gui) _gui->splashDestroyed();
}
/*
void lbSplashScreen::OnCloseWindow(wxCloseEvent& event) {
        if (_gui) _gui->splashDestroyed();
}
*/


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                        TRMemOpen();
                        TRMemSetModuleName(__FILE__);

                        if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);

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
                        if (situation)
                        {
                                _CL_VERBOSE << "DLL released by system." LOG_
                        }
                        else
                        {
                                _CL_VERBOSE << "DLL released by program.\n" LOG_
                        }
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
