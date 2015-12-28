// Word2Txt.cpp: implementation of the CWord2Txt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "Word2Txt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWordConv::CWordConv()
{

}

CWordConv::~CWordConv()
{

}
void CWordConv::DocToTxt(BSTR bstrOpenFile, BSTR bstrSaveFile)
{
	/************************************************************************/
	//delete bstrSaveFile
	_bstr_t b=bstrSaveFile;
	remove(b);
	// ******************* Declare Some Variables ********************

	// Variables that will be used and re-used in our calls
	DISPPARAMS        m_dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT            m_vResult;
	OLECHAR FAR*    m_szFunction;

	// IDispatch pointers for Word's objects
	IDispatch*        m_pDispDocs;          //Documents collection
	IDispatch*        m_pDispActiveDoc;      //ActiveDocument object

	// DISPID's
	DISPID            m_dispid_Docs;        //Documents property of Application object
	DISPID            m_dispid_ActiveDoc;   //ActiveDocument property of Application
	DISPID            m_dispid_SaveAs;      //SaveAs method of the Document object
	DISPID            m_dispid_Quit;        //Quit method of the Application object

	DISPID            m_dispid_Open;          //Open method of the Application object
	BSTR            m_bstrEmptyString ;

	// ******************** Start Automation ***********************

	//Initialize the COM libraries
	::CoInitialize(NULL);

	// Create an instance of the Word application and obtain the pointer
	// to the application's IDispatch interface.
	CLSID    m_clsid;
	CLSIDFromProgID(L"Word.Application", &m_clsid);

	IUnknown*    m_pUnk;
	HRESULT m_hr = ::CoCreateInstance( m_clsid, NULL, CLSCTX_SERVER,
		IID_IUnknown, (void**) &m_pUnk);
	IDispatch*    m_pDispApp;
	m_hr = m_pUnk->QueryInterface( IID_IDispatch, (void**)&m_pDispApp);

	// Get IDispatch* for the Documents collection object
	m_szFunction = OLESTR("Documents");
	m_hr = m_pDispApp->GetIDsOfNames (IID_NULL, &m_szFunction, 1,
		LOCALE_USER_DEFAULT, &m_dispid_Docs);
	m_hr = m_pDispApp->Invoke (m_dispid_Docs, IID_NULL, LOCALE_USER_DEFAULT,
		DISPATCH_PROPERTYGET, &m_dpNoArgs, &m_vResult,
		NULL, NULL);
	m_pDispDocs = m_vResult.pdispVal;

	// Query id of method open
	m_szFunction = OLESTR("Open");
	m_hr = m_pDispDocs->GetIDsOfNames(IID_NULL, &m_szFunction,1,
		LOCALE_USER_DEFAULT, &m_dispid_Open);

	// Prepare parameters for open method
	VARIANT        vArgsOpen[6];
	DISPPARAMS    dpOpen;
	dpOpen.cArgs        = 6;
	dpOpen.cNamedArgs   = 0;
	dpOpen.rgvarg        = vArgsOpen;

	VARIANT        vFalse, vTrue;
	vFalse.vt            = VT_BOOL;
	vFalse.boolVal        = FALSE;
	vTrue.vt            = VT_BOOL;
	vTrue.boolVal        = TRUE;


	m_bstrEmptyString = ::SysAllocString(OLESTR("")) ;

	vArgsOpen[5].vt            = VT_BSTR;
	vArgsOpen[5].bstrVal    = bstrOpenFile;
	vArgsOpen[4]            = vFalse;
	vArgsOpen[3]            = vTrue;
	vArgsOpen[2]            = vFalse;
	vArgsOpen[1].vt            = VT_BSTR;
	vArgsOpen[1].bstrVal    = m_bstrEmptyString;
	vArgsOpen[0].vt            = VT_BSTR;
	vArgsOpen[0].bstrVal    = m_bstrEmptyString;

	//Execute open method
	m_hr=m_pDispDocs->Invoke(m_dispid_Open,IID_NULL,LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,&dpOpen,NULL,NULL,NULL);

	//Query activedocument interface
	m_szFunction = OLESTR("ActiveDocument");
	m_hr = m_pDispApp->GetIDsOfNames(IID_NULL, &m_szFunction, 1,
		LOCALE_USER_DEFAULT,&m_dispid_ActiveDoc);
	m_hr = m_pDispApp->Invoke(m_dispid_ActiveDoc,IID_NULL,
		LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET,
		&m_dpNoArgs,&m_vResult,NULL,NULL);
	m_pDispActiveDoc = m_vResult.pdispVal;

	//Prepare arguments for save as .txt
	VARIANT            vArgsSaveAs[11];
	DISPPARAMS        dpSaveAs;
	dpSaveAs.cArgs            =   11;
	dpSaveAs.cNamedArgs        =   0;
	dpSaveAs.rgvarg            =   vArgsSaveAs;

	vArgsSaveAs[10].vt        =   VT_BSTR;
	vArgsSaveAs[10].bstrVal =    bstrSaveFile;        //Filename
	vArgsSaveAs[9].vt        =   VT_I4;
	vArgsSaveAs[9].lVal        =   2;                  //FileFormat(wdFormatText = 2)
	vArgsSaveAs[8]            =   vFalse;                //LockComments
	vArgsSaveAs[7].vt        =   VT_BSTR;
	vArgsSaveAs[7].bstrVal  =   m_bstrEmptyString;  //Password
	vArgsSaveAs[6].vt        =   VT_BOOL;
	vArgsSaveAs[6].boolVal  =   TRUE;               //AddToRecentFiles
	vArgsSaveAs[5].vt        =   VT_BSTR;
	vArgsSaveAs[5].bstrVal  =   m_bstrEmptyString;  //WritePassword
	vArgsSaveAs[4]            =   vFalse;             //ReadOnlyRecommended
	vArgsSaveAs[3]            =   vFalse;             //EmbedTrueTypeFonts
	vArgsSaveAs[2]            =   vFalse;             //SaveNativePictureFormat
	vArgsSaveAs[1]            =   vFalse;             //SaveFormsData
	vArgsSaveAs[0]            =   vFalse;                //SaveAsOCELetter

	// Query and execute SaveAs method
	m_szFunction = OLESTR("SaveAs");
	m_hr = m_pDispActiveDoc->GetIDsOfNames(IID_NULL,&m_szFunction,1,LOCALE_USER_DEFAULT,&m_dispid_SaveAs);
	m_hr = m_pDispActiveDoc->Invoke(m_dispid_SaveAs,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_METHOD,&dpSaveAs,NULL,NULL,NULL);
	// Invoke the Quit method
	m_szFunction = OLESTR("Quit");
	m_hr = m_pDispApp->GetIDsOfNames(IID_NULL, &m_szFunction, 1,LOCALE_USER_DEFAULT, &m_dispid_Quit);
	m_hr = m_pDispApp->Invoke(m_dispid_Quit, IID_NULL, LOCALE_USER_DEFAULT,DISPATCH_METHOD, &m_dpNoArgs, NULL, NULL, NULL);

	//Clean-up
	::SysFreeString(bstrOpenFile) ;
	::SysFreeString(bstrSaveFile) ;
	::SysFreeString(m_bstrEmptyString) ;

	m_pDispActiveDoc->Release();
	m_pDispDocs->Release();
	m_pDispApp->Release();
	m_pUnk->Release();

	::CoUninitialize();
}

void CWordConv::DocToHtml(BSTR in_doc_path, BSTR in_html_path)
{

	/************************************************************************/
	//delete bstrSaveFile
	_bstr_t b=in_html_path;
	remove(b);

	int vx_utral=(strlen(b));
	
	char *html_folder=(char *)malloc(vx_utral+10);
	memset(html_folder,'\0',vx_utral+10);
	strcpy(html_folder,b);
	html_folder[vx_utral]='s';
	html_folder[vx_utral-1]='e';
	html_folder[vx_utral-2]='l';
	html_folder[vx_utral-3]='i';
	html_folder[vx_utral-4]='f';

	TRACE1(_T("delete folder:%s"),html_folder);
	this->RemoveFolder(html_folder);

	// Variables that will be used and re-used in our calls
	DISPPARAMS        m_dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT            m_vResult;
	OLECHAR FAR*    m_szFunction;

	// IDispatch pointers for Word's objects
	IDispatch*        m_pDispDocs;          //Documents collection
	IDispatch*        m_pDispActiveDoc;      //ActiveDocument object

	// DISPID's
	DISPID            m_dispid_Docs;        //Documents property of Application object
	DISPID            m_dispid_ActiveDoc;   //ActiveDocument property of Application
	DISPID            m_dispid_SaveAs;      //SaveAs method of the Document object
	DISPID            m_dispid_Quit;        //Quit method of the Application object

	DISPID            m_dispid_Open;          //Open method of the Application object
	BSTR            m_bstrEmptyString ;

	// ******************** Start Automation ***********************

	//Initialize the COM libraries
	::CoInitialize(NULL);

	// Create an instance of the Word application and obtain the pointer
	// to the application's IDispatch interface.
	CLSID    m_clsid;
	CLSIDFromProgID(L"Word.Application", &m_clsid);

	IUnknown*    m_pUnk;
	HRESULT m_hr = ::CoCreateInstance( m_clsid, NULL, CLSCTX_SERVER,
		IID_IUnknown, (void**) &m_pUnk);
	IDispatch*    m_pDispApp;
	m_hr = m_pUnk->QueryInterface( IID_IDispatch, (void**)&m_pDispApp);

	// Get IDispatch* for the Documents collection object
	m_szFunction = OLESTR("Documents");
	m_hr = m_pDispApp->GetIDsOfNames (IID_NULL, &m_szFunction, 1,
		LOCALE_USER_DEFAULT, &m_dispid_Docs);
	m_hr = m_pDispApp->Invoke (m_dispid_Docs, IID_NULL, LOCALE_USER_DEFAULT,
		DISPATCH_PROPERTYGET, &m_dpNoArgs, &m_vResult,
		NULL, NULL);
	m_pDispDocs = m_vResult.pdispVal;

	// Query id of method open
	m_szFunction = OLESTR("Open");
	m_hr = m_pDispDocs->GetIDsOfNames(IID_NULL, &m_szFunction,1,
		LOCALE_USER_DEFAULT, &m_dispid_Open);

	// Prepare parameters for open method
	VARIANT        vArgsOpen[6];
	DISPPARAMS    dpOpen;
	dpOpen.cArgs        = 6;
	dpOpen.cNamedArgs   = 0;
	dpOpen.rgvarg        = vArgsOpen;

	VARIANT        vFalse, vTrue;
	vFalse.vt            = VT_BOOL;
	vFalse.boolVal        = FALSE;
	vTrue.vt            = VT_BOOL;
	vTrue.boolVal        = TRUE;


	m_bstrEmptyString = ::SysAllocString(OLESTR("")) ;

	vArgsOpen[5].vt            = VT_BSTR;
	vArgsOpen[5].bstrVal    = in_doc_path;
	vArgsOpen[4]            = vFalse;
	vArgsOpen[3]            = vTrue;
	vArgsOpen[2]            = vFalse;
	vArgsOpen[1].vt            = VT_BSTR;
	vArgsOpen[1].bstrVal    = m_bstrEmptyString;
	vArgsOpen[0].vt            = VT_BSTR;
	vArgsOpen[0].bstrVal    = m_bstrEmptyString;

	//Execute open method
	m_hr=m_pDispDocs->Invoke(m_dispid_Open,IID_NULL,LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,&dpOpen,NULL,NULL,NULL);

	//Query activedocument interface
	m_szFunction = OLESTR("ActiveDocument");
	m_hr = m_pDispApp->GetIDsOfNames(IID_NULL, &m_szFunction, 1,
		LOCALE_USER_DEFAULT,&m_dispid_ActiveDoc);
	m_hr = m_pDispApp->Invoke(m_dispid_ActiveDoc,IID_NULL,
		LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET,
		&m_dpNoArgs,&m_vResult,NULL,NULL);
	m_pDispActiveDoc = m_vResult.pdispVal;

	//Prepare arguments for save as .html
	VARIANT            vArgsSaveAs[11];
	DISPPARAMS        dpSaveAs;
	dpSaveAs.cArgs            =   11;
	dpSaveAs.cNamedArgs        =   0;
	dpSaveAs.rgvarg            =   vArgsSaveAs;

	vArgsSaveAs[10].vt			=   VT_BSTR;
	vArgsSaveAs[10].bstrVal		=   in_html_path;		//Filename
	vArgsSaveAs[9].vt			=   VT_I4;
	vArgsSaveAs[9].lVal			=   wdFormatHTML;		//FileFormat
	vArgsSaveAs[8]				=   vFalse;				//LockComments
	vArgsSaveAs[7].vt			=   VT_BSTR;
	vArgsSaveAs[7].bstrVal		=   m_bstrEmptyString;	//Password
	vArgsSaveAs[6].vt			=   VT_BOOL;
	vArgsSaveAs[6].boolVal		=   TRUE;				//AddToRecentFiles
	vArgsSaveAs[5].vt			=   VT_BSTR;
	vArgsSaveAs[5].bstrVal		=   m_bstrEmptyString;	//WritePassword
	vArgsSaveAs[4]				=   vFalse;				//ReadOnlyRecommended
	vArgsSaveAs[3]				=   vFalse;				//EmbedTrueTypeFonts
	vArgsSaveAs[2]				=   vFalse;				//SaveNativePictureFormat
	vArgsSaveAs[1]				=   vFalse;				//SaveFormsData
	vArgsSaveAs[0]				=   vFalse;             //SaveAsOCELetter

	// Query and execute SaveAs method
	m_szFunction = OLESTR("SaveAs");
	m_hr = m_pDispActiveDoc->GetIDsOfNames(IID_NULL,&m_szFunction,1,LOCALE_USER_DEFAULT,&m_dispid_SaveAs);
	m_hr = m_pDispActiveDoc->Invoke(m_dispid_SaveAs,IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_METHOD,&dpSaveAs,NULL,NULL,NULL);
	// Invoke the Quit method
	m_szFunction = OLESTR("Quit");
	m_hr = m_pDispApp->GetIDsOfNames(IID_NULL, &m_szFunction, 1,LOCALE_USER_DEFAULT, &m_dispid_Quit);
	m_hr = m_pDispApp->Invoke(m_dispid_Quit, IID_NULL, LOCALE_USER_DEFAULT,DISPATCH_METHOD, &m_dpNoArgs, NULL, NULL, NULL);

	//Clean-up
	::SysFreeString(in_doc_path) ;
	::SysFreeString(in_html_path) ;
	::SysFreeString(m_bstrEmptyString) ;

	m_pDispActiveDoc->Release();
	m_pDispDocs->Release();
	m_pDispApp->Release();
	m_pUnk->Release();

	::CoUninitialize();

}

/************************************************************************/
/* delete folder and all files&subfolder in it                          */
/************************************************************************/
bool CWordConv::RemoveFolder(char *DirName)
{
        CFileFind   tempFind; 
        char   tempFileFind[200]; 
        sprintf(tempFileFind, "%s\\*.* ",DirName); 
        BOOL   IsFinded=(BOOL)tempFind.FindFile(tempFileFind); 
        while(IsFinded) 
		{ 
			IsFinded=(BOOL)tempFind.FindNextFile(); 
			if(!tempFind.IsDots()) 
			{ 
				char   foundFileName[200]; 
				strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200)); 
				if(tempFind.IsDirectory()) 
				{ 
					char   tempDir[200]; 
					sprintf(tempDir, "%s\\%s ",DirName,foundFileName); 
					RemoveFolder(tempDir); 
				} 
				else 
				{ 
					char   tempFileName[200]; 
					sprintf(tempFileName, "%s\\%s ",DirName,foundFileName); 
					DeleteFile(tempFileName); 
				} 
			} 
		} 
		tempFind.Close(); 
// 		if(!RemoveDirectory(DirName)) 
// 		{ 
// 			MessageBox(0, "删除目录失败！ ", "警告信息 ",MB_OK);  
// 			return   FALSE; 
// 		} 
		return   TRUE; 
}                         

