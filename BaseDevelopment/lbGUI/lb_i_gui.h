/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lb_i_gui.h,v 1.1 2000/03/05 17:14:13 lolli Exp $
 *
 * $Log: lb_i_gui.h,v $
 * Revision 1.1  2000/03/05 17:14:13  lolli
 * Moved to AppDevelopment/GUI/wxGUI
 *
 * Revision 1.2  2000/01/18 21:14:14  lolli
 * Current version
 *
 * Revision 1.1  1999/11/25 21:00:00  lothar
 * Initial version
 *
 **************************************************************/

#ifndef LB_I_GUIAPPLICATION
#define LB_I_GUIAPPLICATION

#undef DLLEXPORT

#ifdef LB_I_GUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_I_GUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif

class lbComponentDictionary;
class RemoteAppRes;

class DLLEXPORT lb_I_GUIComponent {
public:
        lb_I_GUIComponent();
		virtual ~lb_I_GUIComponent();

        enum GUITypes { LB_MENUBAR, LB_MENU, LB_MENUENTRY, LB_APP_TITLE };

        GUITypes getType();

        void setApplicationName(char* name);

protected:
        virtual void setType() = 0;
        GUITypes typ;
        // This GUI component is associated to this application,
        // so request's are also possible from here.
        char* forApplication;
		RemoteAppRes* res;
};

class DLLEXPORT lb_I_GUIMenuEntry: public lb_I_GUIComponent {
public:
    lb_I_GUIMenuEntry();
    virtual ~lb_I_GUIMenuEntry();
        
    int getId();
    char* getTxt();
    char* getHlp();
    
    void setMenu(int id, char* txt, char* hlp);
protected:
    void setType();

    char* MenuTxt;
    char* MenuHlp;
    int MenuId;
};

class DLLEXPORT lb_I_GUIMenu: public lb_I_GUIComponent {
public:
    lb_I_GUIMenu();
    virtual ~lb_I_GUIMenu();
        
    GUITypes getType();
    char* getName();
    void setName(char* n);

protected:
    void setType();

    lbComponentDictionary* menuEntries;
    char* name;
};

class DLLEXPORT lb_I_GUIMenuBar: public lb_I_GUIComponent {
public:
    /**
     * This constructor is used to get the menubar for the
     * given application name. The initializion may be done
     * by network requests.
     */
    lb_I_GUIMenuBar();
    virtual ~lb_I_GUIMenuBar();

	void Setup(char* applicationName);

    int hasMoreElements();

    lb_I_GUIComponent* nextElement();


protected:
    void setType();



    // A list of menus (File, View, Help...)
    lbComponentDictionary Menus;

    // The name of the application (used to get menu setup from remote server

    char* appName;
};

class DLLEXPORT lb_I_GUIApplication {
public:
    lb_I_GUIApplication();

    virtual ~lb_I_GUIApplication();


    int isFirstStart();

    void InstallClient();
    
    char* getAppTitle();

    int hasMoreComponents();
    lb_I_GUIComponent* nextComponent();

    //GUITypes getNext();

//    wxMenu* loadMenu();

    // updateMenu(...);
    // updateHook

protected:    
    char* title;
    int componentCount;
};

#endif // LB_I_WXGUIAPPLICATION

