// CreateNewSeal.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CreateNewSeal.h"

#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateNewSeal dialog


CCreateNewSeal::CCreateNewSeal(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateNewSeal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateNewSeal)
	m_strStyle = _T("幼圆");
	m_nMainWidth = 9;
	m_lf = new(LOGFONT);
	m_strMainText = _T("中国地质大学（武汉）");
	m_nRadius = 90;
	m_nTriRadius = 17;
	m_nAngle = 20;
	m_nTextHeight = 25;
	m_nInterval = 10;
	m_bShowTri = TRUE;
	m_nRadioColor = 0;
	m_strSub1Text = _T("机电学院");
	m_nSub2Pos = 0;
	m_nSub1Pos = 20;
	m_strSub2Text = _T("");
	m_nSub2Width = 6;
	m_nSub2Height = 12;
	m_nSub1Height = 24;
	m_nSub1Width = 8;
	//}}AFX_DATA_INIT
	memset(m_lf, 0, sizeof(LOGFONT));
}


void CCreateNewSeal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateNewSeal)
	DDX_Control(pDX, IDC_SHOW_WND, m_picture);
	DDX_CBString(pDX, IDC_FONT_STYLE, m_strStyle);
	DDX_Text(pDX, IDC_MAIN_WIDTH, m_nMainWidth);
	DDX_Text(pDX, IDC_MAIN_TEXT, m_strMainText);
	DDV_MaxChars(pDX, m_strMainText, 40);
	DDX_Text(pDX, IDC_RADIUS, m_nRadius);
	DDV_MinMaxInt(pDX, m_nRadius, 0, 90);
	DDX_Text(pDX, IDC_TRI_RADIUS, m_nTriRadius);
	DDV_MinMaxInt(pDX, m_nTriRadius, 0, 80);
	DDX_Text(pDX, IDC_ANGLE, m_nAngle);
	DDV_MinMaxInt(pDX, m_nAngle, 0, 50);
	DDX_Text(pDX, IDC_TEXT_HEIGHT, m_nTextHeight);
	DDV_MinMaxInt(pDX, m_nTextHeight, 0, 50);
	DDX_Text(pDX, IDC_INTERVAL, m_nInterval);
	DDV_MinMaxInt(pDX, m_nInterval, 0, 20);
	DDX_Check(pDX, IDC_SHOW_TRI, m_bShowTri);
	DDX_Radio(pDX, IDC_RADIO_RED, m_nRadioColor);
	DDX_Text(pDX, IDC_SUB1_TEXT, m_strSub1Text);
	DDX_Text(pDX, IDC_SUB2_POS, m_nSub2Pos);
	DDX_Text(pDX, IDC_SUB1_POS, m_nSub1Pos);
	DDX_Text(pDX, IDC_SUB2_TEXT, m_strSub2Text);
	DDX_Text(pDX, IDC_SUB2_WIDTH, m_nSub2Width);
	DDX_Text(pDX, IDC_SUB2_HEIGHT, m_nSub2Height);
	DDX_Text(pDX, IDC_SUB1_HEIGHT, m_nSub1Height);
	DDX_Text(pDX, IDC_SUB1_WIDTH, m_nSub1Width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateNewSeal, CDialog)
	//{{AFX_MSG_MAP(CCreateNewSeal)
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_CBN_SELENDOK(IDC_FONT_STYLE, OnSelendokFontStyle)
	ON_EN_CHANGE(IDC_MAIN_WIDTH, OnChangeMainWidth)
	ON_EN_CHANGE(IDC_MAIN_TEXT, OnChangeMainText)
	ON_BN_CLICKED(IDC_SHOW_TRI, OnShowTri)
	ON_EN_CHANGE(IDC_ANGLE, OnChangeAngle)
	ON_EN_CHANGE(IDC_INTERVAL, OnChangeInterval)
	ON_EN_CHANGE(IDC_RADIUS, OnChangeRadius)
	ON_EN_CHANGE(IDC_TEXT_HEIGHT, OnChangeTextHeight)
	ON_EN_CHANGE(IDC_TRI_RADIUS, OnChangeTriRadius)
	ON_BN_CLICKED(IDC_RADIO_RED, OnRadioRed)
	ON_BN_CLICKED(IDC_RADIO_BLUE, OnRadioBlue)
	ON_BN_CLICKED(IDC_RADIO_PURPLE, OnRadioPurple)
	ON_EN_CHANGE(IDC_SUB1_TEXT, OnChangeSub1Text)
	ON_EN_CHANGE(IDC_SUB1_HEIGHT, OnChangeSub1Height)
	ON_EN_CHANGE(IDC_SUB1_POS, OnChangeSub1Pos)
	ON_EN_CHANGE(IDC_SUB1_WIDTH, OnChangeSub1Width)
	ON_BN_CLICKED(IDC_SAVE_SEAL, OnSaveSeal)
	ON_EN_CHANGE(IDC_SUB2_TEXT, OnChangeSub2Text)
	ON_EN_CHANGE(IDC_SUB2_POS, OnChangeSub2Pos)
	ON_EN_CHANGE(IDC_SUB2_HEIGHT, OnChangeSub2Height)
	ON_EN_CHANGE(IDC_SUB2_WIDTH, OnChangeSub2Width)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateNewSeal message handlers

BOOL CCreateNewSeal::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
// 	SetIcon(m_hIcon, TRUE);			// Set big icon
// 	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here	
	
	CreateBmp(&m_pBitmap);
	m_picture.SetBitmap((HBITMAP)m_pBitmap.Detach());

	//初始化各个Spin控件
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MAIN_WIDTH);
	pSpin->SetRange(0, 100);
	pSpin->SetPos(m_nMainWidth);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_RADIUS);
	pSpin->SetRange(0, 90);
	pSpin->SetPos(m_nRadius);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TRI_RADIUS);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nTriRadius);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ANGLE);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nAngle);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TEXT_HEIGHT);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nTextHeight);	

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_INTERVAL);
	pSpin->SetRange(0, 20);
	pSpin->SetPos(m_nInterval);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB1_POS);
	pSpin->SetRange(-50, 50);
	pSpin->SetPos(m_nSub1Pos);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB1_HEIGHT);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nSub1Height);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB1_WIDTH);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nSub1Width);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB2_POS);
	pSpin->SetRange(-50, 50);
	pSpin->SetPos(m_nSub2Pos);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB2_HEIGHT);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nSub2Height);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB2_WIDTH);
	pSpin->SetRange(0, 50);
	pSpin->SetPos(m_nSub2Width);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCreateNewSeal::OnQueryDragIcon()
{
	return (HCURSOR) 0;//m_hIcon;
}


void CCreateNewSeal::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
	CString strText;
	switch(pScrollBar->GetDlgCtrlID())
	{
	//调整主字体宽度
	case IDC_SPIN_MAIN_WIDTH:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_MAIN_WIDTH));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整印章半径大小
	case IDC_SPIN_RADIUS:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_RADIUS));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整五角星外圆半径
	case IDC_SPIN_TRI_RADIUS:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_TRI_RADIUS));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整主字体间的间距
	case IDC_SPIN_ANGLE:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_ANGLE));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整字体的高度
	case IDC_SPIN_TEXT_HEIGHT:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_TEXT_HEIGHT));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整主字体与印章外圈的距离
	case IDC_SPIN_INTERVAL:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_INTERVAL));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整附字体1的高度
	case IDC_SPIN_SUB1_HEIGHT:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_SUB1_HEIGHT));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整附字体1的宽度
	case IDC_SPIN_SUB1_WIDTH:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_SUB1_WIDTH));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整附字体1的位置
	case IDC_SPIN_SUB1_POS:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_SUB1_POS));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整附字体2的高度
	case IDC_SPIN_SUB2_HEIGHT:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_SUB2_HEIGHT));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整附字体2的宽度
	case IDC_SPIN_SUB2_WIDTH:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_SUB2_WIDTH));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	//调整附字体1的位置
	case IDC_SPIN_SUB2_POS:
		((CSpinButtonCtrl*)pScrollBar)->SetBuddy((CEdit*)GetDlgItem(IDC_SUB2_POS));
		strText.Format("%d", nPos);
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strText);
		UpdateData(TRUE);
		break;
	}
	
	UpdateShow();
}


void CCreateNewSeal::CreateBmp(CBitmap *bitmap)
{
	
	
	CClientDC dc(this);
	//设置内存CDC
	CDC MemDC;
	//创建相容的bitmap和dc
	bitmap->CreateCompatibleBitmap(&dc, 198, 198);
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(bitmap);
	//在内存DC中绘制图章
	DrawSeal(&MemDC);
	DrawSealText(&MemDC);
	DrawSubText1(&MemDC);
	DrawSubText2(&MemDC);
	//判断是否绘制五角星
	if(m_bShowTri)
	{
		DrawTri(&MemDC);
	}
	//将创建图片保存在内存中
	MemDC.SelectObject(bitmap);
	
	MemDC.DeleteDC();
}

	//初始化字体
void CCreateNewSeal::InitLogFont(LOGFONT *lf)
{
	lf->lfCharSet = 134;
	lf->lfWidth = m_nMainWidth;
	lf->lfWeight = FW_BOLD;
	lf->lfHeight = m_nTextHeight;
	strcpy(lf->lfFaceName, m_strStyle);	
}

void CCreateNewSeal::OnOK() 
{
	UpdateData(TRUE);
	TRACE("m_strStyle = %s, m_strMainWidth = %d\n", m_strStyle, m_nMainWidth);
	CDialog::OnOK();
}

//重绘picture
void CCreateNewSeal::UpdateShow()
{
	m_pBitmap.DeleteObject();
	CreateBmp(&m_pBitmap);
	//在picture控件中显示位图
	m_picture.SetBitmap((HBITMAP)m_pBitmap.Detach());
}

//选择字型
void CCreateNewSeal::OnSelendokFontStyle() 
{
	CComboBox *pComboBox;
	pComboBox = (CComboBox *)GetDlgItem(IDC_FONT_STYLE);
	
	int index = pComboBox->GetCurSel();
	pComboBox->GetLBText(index, m_strStyle.GetBuffer(pComboBox->GetLBTextLen(index)));
    m_strStyle.ReleaseBuffer();
	//重绘picture
	UpdateShow();
}

//改变主字体宽度
void CCreateNewSeal::OnChangeMainWidth() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MAIN_WIDTH);
	pSpin->SetPos(m_nMainWidth);
		
	UpdateShow();
}

//改变主内容
void CCreateNewSeal::OnChangeMainText() 
{
	UpdateData(TRUE);
	UpdateShow();
}

//绘制图章基本图形
void CCreateNewSeal::DrawSeal(CDC * MemDC)
{
	int cx = 100;
	int cy = 100;
	POINT point;
	point.x = point.y = 5;
	
	LOGPEN logPen;
	
	logPen.lopnColor = ChooseColor(&m_nRadioColor);
	//绘制背景
	logPen.lopnStyle = PS_NULL;
	logPen.lopnWidth = point;
	(*MemDC).SelectObject(CreatePenIndirect(&logPen));
	(*MemDC).Rectangle(0,0,200,200);
	//设置绘笔
	logPen.lopnStyle = PS_SOLID;
	(*MemDC).SelectObject(CreatePenIndirect(&logPen));
	//设置填充
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_HOLLOW;
	logBrush.lbColor = RGB(255, 0, 0);
	(*MemDC).SelectObject(CreateBrushIndirect(&logBrush));
	//绘制外圆
	(*MemDC).Ellipse(cx - m_nRadius, cy - m_nRadius, cx + m_nRadius, cy + m_nRadius);
	
}

void CCreateNewSeal::DrawTri(CDC * MemDC)
{
	//定义五角星五个顶点
	static POINT apt[5], apt1[5];
	//定义五角星的外圆半径
	int r = m_nTriRadius;		

	static POINT point, point1;
	point.x = point.y = 100;
	point1.x = point1.y =1;

	for(int i = 0; i < 5; i++)
	{
		apt[i].y = (long)(point.y - r * cos(TWO_PI * 72 * i / 360));
		apt[i].x = (long)(point.x + r * sin(TWO_PI * 72 * i / 360));
	}
	
	apt1[0] = apt[0];
	apt1[1] = apt[2];
	apt1[2] = apt[4];
	apt1[3] = apt[1];
	apt1[4] = apt[3];
	//设置好绘制参数
	LOGPEN logPen;
	logPen.lopnColor = ChooseColor(&m_nRadioColor);
	logPen.lopnStyle = PS_NULL;
	logPen.lopnWidth = point1;
	(*MemDC).SelectObject(CreatePenIndirect(&logPen));
	(*MemDC).SetPolyFillMode(WINDING);
	(*MemDC).SelectObject(CreateSolidBrush(ChooseColor(&m_nRadioColor)));
	//绘制五角星
	(*MemDC).Polygon(apt1, 5);
	
}

void CCreateNewSeal::DrawSealText(CDC* MemDC)
{	
	InitLogFont(m_lf);

	char cha[20][4]; 
	char* temp;
	char* p;

	int nCha = strlen(m_strMainText)/2;

	temp = m_strMainText.GetBuffer(0);
	m_strMainText.ReleaseBuffer();
	p = temp;

	for(int i = 0; i < nCha; i ++)		
	{
		//将单个字保存在数组中
		memcpy(cha[i], p, 2);
		cha[i][3] = 0;
		p += 2;
	}	
	
	(*MemDC).SetTextColor(ChooseColor(&m_nRadioColor));
	(*MemDC).SetTextAlign(TA_CENTER);
	(*MemDC).SetBkMode(TRANSPARENT);
	//定义字中心到圆心的半径
	int r = m_nRadius - m_nInterval; 
	double xTemp,yTemp;
	double arc;

	arc = m_nAngle * TWO_PI/360.0;

	static POINT point;
	point.x = point.y = 100;
	
	//显示签章单位
#if 1
	//字数为偶数时
	if(nCha%2 == 0) 
	{
		//显示右半边字
	  for(int i = 0; i < nCha/2; i++)
	  {	
		xTemp = point.x + r * sin(arc/2 + i * arc);
		yTemp = point.y - r * cos(arc/2 + i * arc);
		
		
		m_lf->lfEscapement = -10 * (m_nAngle / 2 + i * m_nAngle);
		(*MemDC).SelectObject(CreateFontIndirect(m_lf));
		
		(*MemDC).TextOut((int) xTemp, (int)yTemp, cha[nCha/2 + i]);
	  }
	
	  //显示左半边字
	 for(i = 0; i < nCha/2; i++)
	  {
		xTemp = point.x - r * sin(arc/2 + i * arc);
		yTemp = point.y - r * cos(arc/2 + i * arc);
		
		m_lf->lfEscapement = 10 * (m_nAngle / 2 + i * m_nAngle);
		(*MemDC).SelectObject(CreateFontIndirect(m_lf));

		(*MemDC).TextOut((int) xTemp, (int)yTemp, cha[nCha/2 - i -1]);
	  }
	}

	//字数为奇数时
	else		
	{
		m_lf->lfEscapement = 0;	
		(*MemDC).SelectObject(CreateFontIndirect(m_lf));
		//显示中间字
		(*MemDC).TextOut(point.x, point.y - r, cha[(nCha-1)/2]);
	  //显示右半边字
	  for(int i = 1; i < (nCha + 1)/2; i++) 
	  {	
		xTemp = point.x + r * sin(i * arc);
		yTemp = point.y - r * cos(i * arc);
		
		
		m_lf->lfEscapement = -10 * (i * m_nAngle);
		(*MemDC).SelectObject(CreateFontIndirect(m_lf));

		(*MemDC).TextOut((int) xTemp, (int)yTemp, cha[(nCha-1)/2 + i]);
	  }
	  //显示左半边字
	  for(i = 1; i < (nCha + 1)/2; i++)		
	  {
		xTemp = point.x - r * sin(i * arc);
		yTemp = point.y - r * cos(i * arc);
		
		m_lf->lfEscapement = 10 * (i * m_nAngle);
		(*MemDC).SelectObject(CreateFontIndirect(m_lf));
		
		(*MemDC).TextOut((int) xTemp, (int)yTemp, cha[(nCha-1)/2 - i]);
	  }
	}
#endif	  
}
//更新显示五角星
void CCreateNewSeal::OnShowTri() 
{
	UpdateData(TRUE);
	UpdateShow();
}

//修改字间距
void CCreateNewSeal::OnChangeAngle() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ANGLE);
	pSpin->SetPos(m_nAngle);
		
	UpdateShow();
	
}
//修改字到外圆间的距离
void CCreateNewSeal::OnChangeInterval() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_INTERVAL);
	pSpin->SetPos(m_nInterval);
		
	UpdateShow();
	
}
//修改公章半径
void CCreateNewSeal::OnChangeRadius() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_RADIUS);
	pSpin->SetPos(m_nRadius);
		
	UpdateShow();
	
}
//修改主字体的高度
void CCreateNewSeal::OnChangeTextHeight() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TEXT_HEIGHT);
	pSpin->SetPos(m_nTextHeight);
		
	UpdateShow();
	
}
//修改五角星外圆半径
void CCreateNewSeal::OnChangeTriRadius() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_TRI_RADIUS);
	pSpin->SetPos(m_nTriRadius);
		
	UpdateShow();
	
}

//显示红色
void CCreateNewSeal::OnRadioRed() 
{
	UpdateData(TRUE);
	UpdateShow();
}
//显示蓝色
void CCreateNewSeal::OnRadioBlue() 
{
	UpdateData(TRUE);
	UpdateShow();
	
}
//显示紫色
void CCreateNewSeal::OnRadioPurple() 
{
	UpdateData(TRUE);
	UpdateShow();	
}
//选择颜色
COLORREF CCreateNewSeal::ChooseColor(int *nChoice)
{
	if(*nChoice == 0)
		return RGB(255, 0, 0);

	else if(*nChoice == 1)
		return RGB(0, 0, 255);
	else
		return RGB(128, 0, 128);
}

//绘制附文1
void CCreateNewSeal::DrawSubText1(CDC * MemDC)
{
	memset(m_lf, 0, sizeof(LOGFONT));
	m_lf->lfHeight = m_nSub1Height;
	m_lf->lfWidth = m_nSub1Width;
	m_lf->lfWeight = FW_BOLD;
	strcpy(m_lf->lfFaceName, m_strStyle);

	(*MemDC).SelectObject(CreateFontIndirect(m_lf));

	(*MemDC).SetTextColor(ChooseColor(&m_nRadioColor));
	(*MemDC).SetTextAlign(TA_CENTER);
	(*MemDC).SetBkMode(TRANSPARENT);

	(*MemDC).TextOut(100, 120 + m_nSub1Pos, m_strSub1Text);
}
//修改附文1的内容
void CCreateNewSeal::OnChangeSub1Text() 
{
	UpdateData(TRUE);
	UpdateShow();
}
//修改附文1的字高
void CCreateNewSeal::OnChangeSub1Height() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB1_HEIGHT);
	pSpin->SetPos(m_nSub1Height);
		
	UpdateShow();
	
}
//修改附文1的位置
void CCreateNewSeal::OnChangeSub1Pos() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB1_POS);
	pSpin->SetPos(m_nSub1Pos);
		
	UpdateShow();
	
}
//修改附文1的字宽
void CCreateNewSeal::OnChangeSub1Width() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB1_WIDTH);
	pSpin->SetPos(m_nSub1Width);
		
	UpdateShow();
	
}

//绘制附文2
void CCreateNewSeal::DrawSubText2(CDC * MemDC)
{
	memset(m_lf, 0, sizeof(LOGFONT));
	m_lf->lfHeight = m_nSub2Height;
	m_lf->lfWidth = m_nSub2Width;
	m_lf->lfWeight = FW_NORMAL;
	strcpy(m_lf->lfFaceName, m_strStyle);

	(*MemDC).SelectObject(CreateFontIndirect(m_lf));

	(*MemDC).SetTextColor(ChooseColor(&m_nRadioColor));
	(*MemDC).SetTextAlign(TA_CENTER);
	(*MemDC).SetBkMode(TRANSPARENT);

	(*MemDC).TextOut(100, 120 + m_nSub2Pos, m_strSub2Text);
}
//修改附文2的内容
void CCreateNewSeal::OnChangeSub2Text() 
{
	UpdateData(TRUE);
	UpdateShow();
}
//修改附文2的位置
void CCreateNewSeal::OnChangeSub2Pos() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB2_POS);
	pSpin->SetPos(m_nSub2Pos);
		
	UpdateShow();
	
}
//修改附文2的字高
void CCreateNewSeal::OnChangeSub2Height() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB2_HEIGHT);
	pSpin->SetPos(m_nSub2Height);
		
	UpdateShow();
}
//修改附文2的字宽
void CCreateNewSeal::OnChangeSub2Width() 
{
	UpdateData(TRUE);

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SUB2_WIDTH);
	pSpin->SetPos(m_nSub2Width);
		
	UpdateShow();
	
}
/************************************************************************/
/* save new seal picture @ system path                                                                     */
/************************************************************************/
//保存位图
void CCreateNewSeal::OnSaveSeal(CDC* MemDC) 
{
	SaveBitmapToFile(m_picture.GetBitmap(),TEMP_SEAL_BMP_PATH);

	CDialog::OnOK();
}


BOOL CCreateNewSeal::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName)   //hBitmap   为刚才的屏幕位图句柄   lpFileName   为位图文件名  
{            
	//设备描述表  
	HDC  hDC;  
    //当前分辨率下每象素所占字节数  
    int  iBits;  
    //位图中每象素所占字节数  
    WORD  wBitCount;  
    //定义调色板大小，  位图中像素字节大小  ，位图文件大小  ，  写入文件字节数    
    DWORD  dwPaletteSize=0,  dwBmBitsSize=0,  dwDIBSize=0,  dwWritten=0;    
    //位图属性结构    
    BITMAP  Bitmap;      
    //位图文件头结构  
    BITMAPFILEHEADER  bmfHdr;      
    //位图信息头结构    
    BITMAPINFOHEADER  bi;      
    //指向位图信息头结构      
    LPBITMAPINFOHEADER  lpbi;      
    //定义文件，分配内存句柄，调色板句柄    
    HANDLE  fh,  hDib,  hPal,hOldPal=NULL;    
             
    //计算位图文件每个像素所占字节数    
    hDC  =  CreateDC("DISPLAY",  NULL,  NULL,  NULL);  
    iBits  =  GetDeviceCaps(hDC,  BITSPIXEL)  *  GetDeviceCaps(hDC,  PLANES);    
    DeleteDC(hDC);    
    if  (iBits <= 1)                     
		wBitCount = 1;    
    else  if  (iBits <= 4)            
		wBitCount  =  4;    
    else  if  (iBits <= 8)       
		wBitCount = 8;    
    else  
		wBitCount = 24;    
             
    GetObject(hBitmap,  sizeof(Bitmap),  (LPSTR)&Bitmap);  
    bi.biSize = sizeof(BITMAPINFOHEADER);  
    bi.biWidth = Bitmap.bmWidth;  
    bi.biHeight = Bitmap.bmHeight;  
    bi.biPlanes = 1;  
    bi.biBitCount = wBitCount;  
    bi.biCompression = BI_RGB;  
    bi.biSizeImage = 0;  
    bi.biXPelsPerMeter = 0;  
    bi.biYPelsPerMeter = 0;  
    bi.biClrImportant = 0;  
    bi.biClrUsed = 0;  
             
    dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;  
             
    //为位图内容分配内存    
    hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));    
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);   
    *lpbi = bi;    
 
    //  处理调色板      
    hPal = GetStockObject(DEFAULT_PALETTE);    
    if(hPal)    
    {    
		hDC = ::GetDC(NULL);    
        hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);    
        RealizePalette(hDC);    
      }  
 
    //  获取该调色板下新的像素值    
    GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, 
				(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)    
                 + dwPaletteSize, (BITMAPINFO*)lpbi,  DIB_RGB_COLORS);    
             
    //恢复调色板      
    if  (hOldPal)    
    {    
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);    
        RealizePalette(hDC);    
        ::ReleaseDC(NULL, hDC);    
       }    
 
    //创建位图文件      
    fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,    
                      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);    
             
    if(fh == INVALID_HANDLE_VALUE)   
		return  FALSE;    
             
    //  设置位图文件头    
    bmfHdr.bfType = 0x4D42;  //  "BM"    
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
				+ dwPaletteSize + dwBmBitsSize;      
    bmfHdr.bfSize = dwDIBSize;    
    bmfHdr.bfReserved1 = 0;    
    bmfHdr.bfReserved2 = 0;    
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER)
						+ dwPaletteSize;    
    //  写入位图文件头    
    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);    
    //  写入位图文件其余内容    
    WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);    
    //清除      
    GlobalUnlock(hDib);    
    GlobalFree(hDib);    
    CloseHandle(fh);    
 
    return TRUE;  	
} 


void CCreateNewSeal::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
