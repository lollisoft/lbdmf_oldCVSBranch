
/* Implementation class for fixed database formular
 *  lbDMFManager
 */
 

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

#include <lbConfigHook.h>
#include <lbInterfaces.h>

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif


#ifdef __GNUG__
#pragma implementation "wxSFDesignerAnwendungenImplementation.cpp"
#pragma interface "wxSFDesignerAnwendungenImplementation.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wizard.h>
#include <wx/image.h>


#include <wx/wxsf/wxShapeFramework.h>

// Include base class definition
#include <wxSFDesignerBase.h>
#include <wxSFDesignerAnwendungenImplementation.h> 

BEGIN_IMPLEMENT_LB_UNKNOWN(Anwendungen)
	ADD_INTERFACE(lb_I_Window)
	ADD_INTERFACE(lb_I_Form)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfAnwendungen, Anwendungen)

lbErrCodes LB_STDCALL Anwendungen::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_VERBOSE << "Anwendungen::setData(...) not implemented yet" LOG_

		UAP(lb_I_Form, dbForm)
		QI(uk, lb_I_Form, dbForm)
		
        return ERR_NOT_IMPLEMENTED;
}

Anwendungen::Anwendungen() 
{
	_CL_LOG << "Anwendungen::Anwendungen() called." LOG_
	formName = strdup("Anwendungen");
}

Anwendungen::~Anwendungen() {
	_CL_LOG << "Anwendungen::~Anwendungen() called." LOG_
}

lbErrCodes LB_STDCALL Anwendungen::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev)

	dispatcher->setEventManager(ev.getPtr());

	registerBaseEventHandler(dispatcher);
	
	lb_I_EventHandler* evHandler = (lb_I_EventHandler*) this;

	int temp;

	char* designermenu = strdup(_trans("&Anwendungsdesigner"));
	
	metaapp->addToolBar("Anwendungsdesigner");
	
	sprintf(eventName, "%pModeApplication", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry(designermenu, "Anwendungen designen", eventName, "");
	metaapp->addToolBarButton("Anwendungsdesigner", "Anwendung", eventName, "kthememgr.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &Anwendungen::lbSetAnwendungenMode, eventName);
	
	
	sprintf(eventName, "%pModeFormular", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry(designermenu, "Formulare designen", eventName, "");
	metaapp->addToolBarButton("Anwendungsdesigner", "Formular", eventName, "kpersonalizer.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &Anwendungen::lbSetFormulareMode, eventName);
	
	return ERR_NONE;
}


lbErrCodes LB_STDCALL Anwendungen::lbSetAnwendungenMode(lb_I_Unknown* uk) {
	ToolMode = 1;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL Anwendungen::lbSetFormulareMode(lb_I_Unknown* uk) {
	ToolMode = 2;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL Anwendungen::lbMouseDown(lb_I_Unknown* uk) {
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL Anwendungen::lbMouseUp(lb_I_Unknown* uk) {
	
	return ERR_NONE;
}


// Formular init routine



// Initialization of the form via source code

void LB_STDCALL Anwendungen::init() {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	_LOG << "Anwendungen::init() called." LOG_
	
	currentDiagramManager = new wxSFDiagramManager();
	SetDiagramManager(currentDiagramManager);	

	GetDiagramManager()->ClearAcceptedShapes();
	GetDiagramManager()->AcceptShape(wxT("All"));
	GetHistoryManager().SetMode(wxSFCanvasHistory::histUSE_SERIALIZATION);
	SaveCanvasState();
	
	
	AddStyle(sfsGRID_USE);
	AddStyle(sfsGRID_SHOW);
	// distances between grid lines can be modified via following function:
	SetGridLineMult(10);
	// grid line style can be set as follows:
	SetGridStyle(wxSHORT_DASH);
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	registerEventHandler(*&dispatcher);
}

class lbPluginAnwendungen : public lb_I_PluginImpl {
public:
	lbPluginAnwendungen();
	
	virtual ~lbPluginAnwendungen();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungen)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungen, lbPluginAnwendungen)

lbErrCodes LB_STDCALL lbPluginAnwendungen::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungen::setData(...) called.\n" LOG_

    return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungen::lbPluginAnwendungen() {
	_CL_VERBOSE << "lbPluginAnwendungen::lbPluginAnwendungen() called.\n" LOG_
}

lbPluginAnwendungen::~lbPluginAnwendungen() {
	_CL_VERBOSE << "lbPluginAnwendungen::~lbPluginAnwendungen() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungen::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungen::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungen::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungen::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungen::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		Anwendungen* _Anwendungen = new Anwendungen();
	
		QI(_Anwendungen, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginAnwendungen::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungen::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Anwendungen* _Anwendungen = new Anwendungen();
	
		QI(_Anwendungen, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungen::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
