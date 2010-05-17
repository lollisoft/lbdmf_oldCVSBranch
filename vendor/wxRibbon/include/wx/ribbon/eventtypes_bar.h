#ifndef _WX_RIBBON_BAR_EVENT_TYPES_H_
#define _WX_RIBBON_BAR_EVENT_TYPES_H_


BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGED, 2)
    DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGING, 3)
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN, 4)
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP, 5)
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN, 6)
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP, 7)
END_DECLARE_EVENT_TYPES()

#define wxDECLARE_EXPORTED_EVENT( expdecl, name, type ) \
   extern const wxEventType name

#define wxDEFINE_EVENT( expdecl, name, type ) \
   expdecl const wxEventType name( wxNewEventType() )

typedef void (wxEvtHandler::*wxRibbonBarEventFunction)(wxRibbonBarEvent&);

#define wxRibbonBarEventHandler(func) \
    wxEVENT_HANDLER_CAST(wxRibbonBarEventFunction, func)

#define EVT_RIBBONBAR_PAGE_CHANGED(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGED, winid, wxRibbonBarEventHandler(fn))
#define EVT_RIBBONBAR_PAGE_CHANGING(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGING, winid, wxRibbonBarEventHandler(fn))
#define EVT_RIBBONBAR_TAB_MIDDLE_DOWN(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN, winid, wxRibbonBarEventHandler(fn))
#define EVT_RIBBONBAR_TAB_MIDDLE_UP(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP, winid, wxRibbonBarEventHandler(fn))
#define EVT_RIBBONBAR_TAB_RIGHT_DOWN(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN, winid, wxRibbonBarEventHandler(fn))
#define EVT_RIBBONBAR_TAB_RIGHT_UP(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP, winid, wxRibbonBarEventHandler(fn))


//wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGED, wxRibbonBarEvent);
//wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGING, wxRibbonBarEvent);
//wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN, wxRibbonBarEvent);
//wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP, wxRibbonBarEvent);
//wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN, wxRibbonBarEvent);
//wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP, wxRibbonBarEvent);

#endif // _WX_RIBBON_BAR_EVENT_TYPES_H_