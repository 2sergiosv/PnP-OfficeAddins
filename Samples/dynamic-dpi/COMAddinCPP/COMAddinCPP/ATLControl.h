// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// ATLControl.h : Declaration of the CATLControl
#pragma once
#include <atlctl.h>
#include "Addin.h"
#include "Addin_i.c"
#include "resource.h"       // main symbols
#include <string>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;



// CATLControl
class ATL_NO_VTABLE CATLControl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IATLControl, &IID_IATLControl, &LIBID_COMAddinCPPLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleControlImpl<CATLControl>,
	public IOleObjectImpl<CATLControl>,
	public IOleInPlaceActiveObjectImpl<CATLControl>,
	public IViewObjectExImpl<CATLControl>,
	public IOleInPlaceObjectWindowlessImpl<CATLControl>,
	public CComCoClass<CATLControl, &CLSID_ATLControl>,
	public CComControl<CATLControl>
{
public:


	CATLControl()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_ATLCONTROL)


BEGIN_COM_MAP(CATLControl)
	COM_INTERFACE_ENTRY(IATLControl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
END_COM_MAP()

BEGIN_PROP_MAP(CATLControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_MSG_MAP(CATLControl)
	CHAIN_MSG_MAP(CComControl<CATLControl>)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, CATLControl::OnLButtonDown)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IATLControl
public:
	HRESULT OnDraw(ATL_DRAWINFO& di);
	HRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
private:
	std::string m_text = "ATLControl";
};

OBJECT_ENTRY_AUTO(__uuidof(ATLControl), CATLControl)
