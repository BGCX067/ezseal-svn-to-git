// mySeal.h : Declaration of the CmySeal

#ifndef __MYSEAL_H_
#define __MYSEAL_H_

#include "resource.h"       // main symbols
#include "stdafx.h"
#include "CreateNewSeal.h"
#import "C:\Program Files\Common Files\designer\MSADDNDR.TLB" raw_interfaces_only, raw_native_types, no_namespace, named_guids 



extern _ATL_FUNC_INFO OnClickButtonInfo;
/////////////////////////////////////////////////////////////////////////////
// CmySeal
class ATL_NO_VTABLE CmySeal : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CmySeal, &CLSID_mySeal>,
	public IDispatchImpl<ImySeal, &IID_ImySeal, &LIBID_EZSEALLib>,
	public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects>,
	public IDispEventSimpleImpl<1,CmySeal,&__uuidof(Office::_CommandBarButtonEvents)>,
	public IDispEventSimpleImpl<2,CmySeal,&__uuidof(Office::_CommandBarButtonEvents)>
{
public:
	CmySeal()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());//此句是必须的
		m_pCreateSrealDlg = new CCreateNewSeal;

		m_spCmdButton=NULL;
		m_spBtnCheck=NULL;
		m_spApp=NULL;
	}
    
DECLARE_REGISTRY_RESOURCEID(IDR_MYSEAL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CmySeal)
	COM_INTERFACE_ENTRY(ImySeal)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IDispatch, ImySeal)
	COM_INTERFACE_ENTRY(_IDTExtensibility2)
END_COM_MAP()

BEGIN_SINK_MAP(CmySeal)
	SINK_ENTRY_INFO(1, __uuidof(Office::_CommandBarButtonEvents),/*dispid*/ 0x01, OnClickButton1, &OnClickButtonInfo)
	SINK_ENTRY_INFO(2, __uuidof(Office::_CommandBarButtonEvents),/*dispid*/ 0x01, OnClickButton2, &OnClickButtonInfo)
END_SINK_MAP()

// ImySeal
public:
	bool GetSealfromDoc();
	CComPtr <Office::_CommandBarButton> m_spCmdButton;
	CComPtr <Office::_CommandBarButton> m_spBtnCheck;
	CComPtr <Word::_Application> m_spApp;
	CCreateNewSeal *m_pCreateSrealDlg;

	typedef IDispEventSimpleImpl</*nID =*/ 1,CmySeal, &__uuidof(Office::_CommandBarButtonEvents)> CommandButton1Events;
	typedef IDispEventSimpleImpl</*nID =*/ 2,CmySeal, &__uuidof(Office::_CommandBarButtonEvents)> CommandButton2Events;

	void __stdcall OnClickButton1(IDispatch * /*Office::_CommandBarButton**/ Ctrl,VARIANT_BOOL * CancelDefault);
	void __stdcall OnClickButton2(IDispatch * /*Office::_CommandBarButton**/ Ctrl,VARIANT_BOOL * CancelDefault);
	CComBSTR   GetWordPath(CComPtr <Word::_Document>   pDoc);

// _IDTExtensibility2
	STDMETHOD(OnConnection)(IDispatch * Application, ext_ConnectMode ConnectMode, IDispatch * AddInInst, SAFEARRAY * * custom)
	{
//start of manually coding
		CComPtr < Office::_CommandBars> spCmdBars; 
		CComQIPtr <Word::_Application> spApp(Application); 	
		ATLASSERT(spApp);
		
		HRESULT hr = spApp->get_CommandBars(&spCmdBars);
		if(FAILED(hr))
			return hr;
		
		ATLASSERT(spCmdBars);
		
		
		CComVariant vName("mySeal");
		CComPtr <Office::CommandBar> spNewCmdBar;
		CComVariant vPos(1); 
		CComVariant vTemp(VARIANT_TRUE);	
		CComVariant vEmpty(DISP_E_PARAMNOTFOUND, VT_ERROR);			
		spNewCmdBar = spCmdBars->Add(vName, vPos, vEmpty, vTemp);
		
		
		CComPtr < Office::CommandBarControls> spBarControls;
		spBarControls = spNewCmdBar->GetControls();
		ATLASSERT(spBarControls);
		
		
		CComVariant vToolBarType(1);
		CComVariant vShow(VARIANT_TRUE);
		CComPtr < Office::CommandBarControl> spNewBar; 
		CComPtr < Office::CommandBarControl> spNewBar2; 
		spNewBar = spBarControls->Add(vToolBarType, vEmpty, vEmpty, vEmpty, vShow); 		
		ATLASSERT(spNewBar);

		spNewBar2 = spBarControls->Add(vToolBarType, vEmpty, vEmpty, vEmpty, vShow); 
		ATLASSERT(spNewBar2);

		// 为每一个按钮指定_CommandBarButton接口，从面可以指定按钮的显示风格等
		CComQIPtr < Office::_CommandBarButton> spCmdButton(spNewBar);
		ATLASSERT(spCmdButton);
		
		CComQIPtr < Office::_CommandBarButton> spCmdButton2(spNewBar2);
		ATLASSERT(spCmdButton2);
		

		
		HBITMAP hBmp =(HBITMAP)::LoadImage(_Module.GetResourceInstance(),
			MAKEINTRESOURCE(IDB_BITMAP),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
		
		::OpenClipboard(NULL);
		::EmptyClipboard();
		::SetClipboardData(CF_BITMAP, (HANDLE)hBmp);
		::CloseClipboard();
		::DeleteObject(hBmp);		
		
		
		spCmdButton->PutStyle(Office::msoButtonIconAndCaption);
		hr = spCmdButton->PasteFace();
		if (FAILED(hr))
			return hr;
		
		spCmdButton->PutVisible(VARIANT_TRUE); 
		spCmdButton->PutCaption(OLESTR("签章")); 
		spCmdButton->PutEnabled(VARIANT_TRUE);
		spCmdButton->PutTooltipText(OLESTR("ezSeal")); 
		spCmdButton->PutTag(OLESTR("test1")); 



		/*设置第二个按钮*/
		// 设置位图按钮风格，位图为32x32大小，将其放入剪切板中用PasteFace()贴在指定按钮上
		
		hBmp =(HBITMAP)::LoadImage(_Module.GetResourceInstance(),
			MAKEINTRESOURCE(IDB_BMP_CHECK),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
		
		::OpenClipboard(NULL);
		::EmptyClipboard();
		::SetClipboardData(CF_BITMAP, (HANDLE)hBmp);
		::CloseClipboard();
		::DeleteObject(hBmp);		
		
		// 粘贴前设置显示风格
		spCmdButton2->PutStyle(Office::msoButtonIconAndCaption);
		//	spCmdButton2->PutStyle(Office::msoButtonIcon);
		hr = spCmdButton2->PasteFace();
		if (FAILED(hr))
			return hr;
		
		spCmdButton2->PutVisible(VARIANT_TRUE); 
		spCmdButton2->PutCaption(OLESTR("验章")); 
		spCmdButton2->PutEnabled(VARIANT_TRUE);
		spCmdButton2->PutTooltipText(OLESTR("验证盖章")); 
		spCmdButton2->PutTag(OLESTR("验证盖章标志")); 

		// 显示新增工具条
		
		m_spCmdButton = spCmdButton;
		m_spBtnCheck = spCmdButton2;

		m_spApp=spApp;
		
		spNewCmdBar->PutVisible(VARIANT_TRUE); 
		
		CommandButton1Events::DispEventAdvise((IDispatch*)m_spCmdButton);
		CommandButton2Events::DispEventAdvise((IDispatch*)m_spBtnCheck);

	

//end of manually
		return E_NOTIMPL;
	}
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY * * custom)
	{
		CommandButton1Events::DispEventUnadvise((IDispatch*)m_spCmdButton);
		m_spApp=NULL;
		m_spCmdButton=NULL;

		return E_NOTIMPL;
	}
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnStartupComplete)(SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnBeginShutdown)(SAFEARRAY * * custom)
	{
		return E_NOTIMPL;
	}
};

#endif //__MYSEAL_H_
