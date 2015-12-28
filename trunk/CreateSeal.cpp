// CreateSeal.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CreateSeal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateSeal dialog


CCreateSeal::CCreateSeal(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateSeal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateSeal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCreateSeal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateSeal)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateSeal, CDialog)
	//{{AFX_MSG_MAP(CCreateSeal)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateSeal message handlers
