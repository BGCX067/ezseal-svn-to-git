#if !defined(AFX_CREATENEWSEAL_H__0C292539_8189_461C_A9EF_595ED81A2E4F__INCLUDED_)
#define AFX_CREATENEWSEAL_H__0C292539_8189_461C_A9EF_595ED81A2E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateNewSeal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateNewSeal dialog
#define TWO_PI	 (2*3.14159)

class CCreateNewSeal : public CDialog
{
// Construction
public:
	CCreateNewSeal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateNewSeal)
	enum { IDD = IDD_MAKESEAL_DIALOG };
	CStatic	m_picture;
	CString	m_strStyle;
	int		m_nMainWidth;
	CBitmap   m_pBitmap;
	LOGFONT*  m_lf;
	CString	m_strMainText;
	int		m_nRadius;
	int		m_nTriRadius;
	int		m_nAngle;
	int		m_nTextHeight;
	int		m_nInterval;
	BOOL	m_bShowTri;
	int		m_nRadioColor;
	CString	m_strSub1Text;
	int		m_nSub2Pos;
	int		m_nSub1Pos;
	CString	m_strSub2Text;
	int		m_nSub2Width;
	int		m_nSub2Height;
	int		m_nSub1Height;
	int		m_nSub1Width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewSeal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString m_strFile;

	// Generated message map functions
	//{{AFX_MSG(CCreateNewSeal)
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	afx_msg void OnSelendokFontStyle();
	afx_msg void OnChangeMainWidth();
	afx_msg void OnChangeMainText();
	afx_msg void OnShowTri();
	afx_msg void OnChangeAngle();
	afx_msg void OnChangeInterval();
	afx_msg void OnChangeRadius();
	afx_msg void OnChangeTextHeight();
	afx_msg void OnChangeTriRadius();
	afx_msg void OnRadioRed();
	afx_msg void OnRadioBlue();
	afx_msg void OnRadioPurple();
	afx_msg void OnChangeSub1Text();
	afx_msg void OnChangeSub1Height();
	afx_msg void OnChangeSub1Pos();
	afx_msg void OnChangeSub1Width();
	afx_msg void OnSaveSeal(CDC* MemDC);
	afx_msg void OnChangeSub2Text();
	afx_msg void OnChangeSub2Pos();
	afx_msg void OnChangeSub2Height();
	afx_msg void OnChangeSub2Width();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
	void CreateBmp(CBitmap* bitmap);
	void InitLogFont(LOGFONT* lf);
	void UpdateShow();
	void DrawSeal(CDC* MemDC);
	void DrawTri(CDC* MemDC);
	void DrawSealText(CDC* MemDC);
	COLORREF ChooseColor(int *nChoice);
	void DrawSubText1(CDC* MemDC);
	void DrawSubText2(CDC * MemDC);
	BOOL SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATENEWSEAL_H__0C292539_8189_461C_A9EF_595ED81A2E4F__INCLUDED_)
