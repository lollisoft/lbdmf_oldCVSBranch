/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lb_i_wxgui.h,v 1.1 2000/03/05 17:14:14 lolli Exp $
 *
 * $Log: lb_i_wxgui.h,v $
 * Revision 1.1  2000/03/05 17:14:14  lolli
 * Moved to AppDevelopment/GUI/wxGUI
 *
 * Revision 1.3  2000/01/23 15:15:47  lolli
 * Corrected revision conflict
 *
 * Revision 1.1  1999/11/25 21:00:00  lothar
 * Initial version
 *
 **************************************************************/


#ifndef LB_I_WXGUIAPPLICATION
#define LB_I_WXGUIAPPLICATION


#undef DLLEXPORT

#ifdef LB_I_WXGUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_I_WXGUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#ifdef __GNUG__
    #pragma implementation "minimal.cpp"
    #pragma interface "minimal.cpp"
#endif


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// ressources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "mondrian.xpm"
#endif



class wxMenu;
class wxMenuBar;
class wxEvtHandler;


class DLLEXPORT lb_I_wxGUIComponent {
public:
        lb_I_wxGUIComponent();
		virtual ~lb_I_wxGUIComponent();

        enum GUITypes { LB_MENUBAR, LB_MENU, LB_MENUENTRY, LB_APP_TITLE };

        GUITypes getType();

        void setApplicationName(wxString name);

protected:
        virtual void setType() = 0;
        GUITypes typ;
        // This GUI component is associated to this application,
        // so request's are also possible from here.
        wxString forApplication; 
};

class DLLEXPORT lb_I_wxGUIMenuBar: public lb_I_wxGUIComponent {
public:
    lb_I_wxGUIMenuBar(wxString &applicationName);
	virtual ~lb_I_wxGUIMenuBar();

// Application specific
    wxString getAppName();

// MenuBar specific
    wxMenuBar* getMenuBar(wxEvtHandler* evtHandle, wxObjectEventFunction func);

protected:
    void setType();

    // A list of  (File, View, Help...)
    lbComponentDictionary* Menus;

    // The name of the application (used to get menu setup from remote server

    wxString appName;
};

class DLLEXPORT lb_I_wxGUIMenu: public lb_I_wxGUIComponent {
public:
    lb_I_wxGUIMenu();
	virtual ~lb_I_wxGUIMenu();
        
//    GUITypes getType();
    wxMenu* getMenu(wxEvtHandler* evtHandle, wxObjectEventFunction func);
    wxString getName();
    void setName(wxString n);

protected:
    void setType();

    lbComponentDictionary* menuEntries;
    wxString name;
};

class DLLEXPORT lb_I_wxGUIMenuEntry: public lb_I_wxGUIComponent {
public:
    lb_I_wxGUIMenuEntry();
	virtual ~lb_I_wxGUIMenuEntry();
        
//    GUITypes getType();

    int getId();
    wxString getTxt();
    wxString getHlp();
    
    void setMenu(int id, wxString txt, wxString hlp);
protected:
    void setType();

    wxString MenuTxt;
    wxString MenuHlp;
    int MenuId;
};

class DLLEXPORT lb_I_wxGUIApplication {
public:
    lb_I_wxGUIApplication();
	virtual ~lb_I_wxGUIApplication();


    int isFirstStart();

    void InstallClient();
    
    char* getAppTitle();

    int hasMoreComponents();
    lb_I_wxGUIComponent* nextComponent();

    //GUITypes getNext();

    wxMenu* loadMenu();

    // updateMenu(...);
    // updateHook

protected:    
    char* title;
    int componentCount;
};

#endif // LB_I_WXGUIAPPLICATION
