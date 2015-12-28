#if !defined(AFX_CREATESEAL_H__37EC8BFB_3CF9_4C2B_9FB7_E421760B8E85__INCLUDED_)
#define AFX_CREATESEAL_H__37EC8BFB_3CF9_4C2B_9FB7_E421760B8E85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateSeal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateSeal dialog

class CCreateSeal : public CDialog
{
// Construction
public:
	CCreateSeal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateSeal)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateSeal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateSeal)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATESEAL_H__37EC8BFB_3CF9_4C2B_9FB7_E421760B8E85__INCLUDED_)
