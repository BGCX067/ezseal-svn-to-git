// mySeal.cpp : Implementation of CmySeal
#include "stdafx.h"
#include "EzSeal.h"
#include "mySeal.h"

#include "Embedded.h"
#include "Word2Txt.h"
#include "ImageConv.h"
#include "FileFilter.h"
#include "md5.h"
#include "RSATool.h"

#include <afxwin.h> 
#include <afxdlgs.h>


/////////////////////////////////////////////////////////////////////////////
// CmySeal
_ATL_FUNC_INFO OnClickButtonInfo = {CC_STDCALL,VT_EMPTY,2,{VT_DISPATCH,VT_BYREF | VT_BOOL}};

CComBSTR   CmySeal::GetWordPath(CComPtr <Word::_Document>   pDoc)
{
	HRESULT hr   =   this->m_spApp-> get_ActiveDocument(&pDoc); 
	
	if   (pDoc   !=   NULL) 
	{ 
		CComBSTR   bstrName; 
		pDoc-> get_FullName(&bstrName); 
		
// 		USES_CONVERSION; 
// 		MessageBox(NULL,   W2CT(bstrName),   _T("当前文档"),   MB_OK); 

		return bstrName;
	} 
	return NULL;

}
void __stdcall CmySeal::OnClickButton1(IDispatch * 
        /*Office::_CommandBarButton**/ Ctrl,VARIANT_BOOL * CancelDefault)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (IDOK!=m_pCreateSrealDlg->DoModal())
	{
		return;
	} 

	//start of new coding @2010-12-2
    ATLASSERT(m_spApp);
	m_spApp->Visible=true;

	Word::RangePtr pRange ;
 	Word::ParagraphPtr pParagraph;
 	Word::SelectionPtr pSelection;
	Word::_DocumentPtr pWordDocument;
	Word::ParagraphsPtr pParagraphs;
    Word::InlineShapesPtr pInlineshapes;
	Word::InlineShapePtr pInlineshape;
	Word::ShapeRangePtr pShapeRange;
	Word::LineFormatPtr pLineFormat;
	Word::PictureFormatPtr pPictureFormat;
	Word::WrapFormatPtr pWrapFormat;
	Word::FillFormatPtr pFillFormat;
	
 	long  lParaCnt,lParaEnd,lParaStart,InlineShapesCnt;
	    
   /*
	*
	*	在当前光标所在处插入电子图章或电子签名
	*   1、找到当前光标所在处(目前实现的是在文档的未尾插入图形
	*   2、打开对话框
	*   3、选择电子图章
	*   4、插入指定位置，并对图形进行处理
	*   5、对当前的图章或签名建立相关信息
	*   使用容器，容器除图片外包含文本框,文本框用来显示作者或其它信息
	*
	*/
   
	//  得到当前活动文档
	pWordDocument =m_spApp-> GetActiveDocument();
	if (pWordDocument == NULL)
	{
		return;
	}
	//ATLASSERT(pWordDocument);
	//create txt temp file
	BSTR doc_full_path_name,txt_full_path_name;
	pWordDocument->get_FullName(&doc_full_path_name);

	_variant_t var_temp_txt_path(TEMP_TEXT_FILE_PATH);
	txt_full_path_name=var_temp_txt_path.bstrVal;

	CWordConv conv;
	conv.DocToTxt(doc_full_path_name,txt_full_path_name);

	//get md5 and write it into file
	CMd5 oGetMd5(TEMP_TEXT_FILE_PATH);
	LPCTSTR md5str = oGetMd5.GetDigestKey();
	TRACE(_T(md5str));

	CRSATool orsa;
	char *buffer=NULL;
	unsigned int buffer_len=200;
	buffer=( char *)malloc(200*sizeof( char));
	if (NULL==buffer)
	{
		TRACE("fail to malloc buffer to save signed md5 str\r\n");
		return; 
	}
	else
	{
		memset((void*)buffer,'\0',200);
	}
	if(false == orsa.Sign(md5str,buffer,&buffer_len))
	{
		TRACE("failed to cal orsa->Sign\r\n");
		return; 
	}

	FILE *pfmd5;
	pfmd5=fopen(TEMP_MD5_STRING_PATH,"w+");
	fprintf(pfmd5,buffer);
	fclose(pfmd5);


	//embedded md5 into bmp
	CEmbedded oEmbed(TEMP_SEAL_BMP_PATH,TEMP_MD5_STRING_PATH);
	oEmbed.Embedded();
	

	//  得到当前活动文档的Paragraph集合
    pParagraphs = pWordDocument->GetParagraphs ();
//    ATLASSERT( pParagraph);
    
	// 得到当前文档的paragraphs数,赋值lParaCnt
	lParaCnt = pParagraphs ->GetCount (); 
      
	// 为调试用
	// 显示lParaCnt值
//	char string[25]; 
//	itoa(lParaCnt, string, 10); 
//	MessageBox(NULL,string, "lParaCnt", MB_OK);
	 
    /*  
	*   补充知识：Range   
	*	Range对象代表文档中的一个连续范围。
	*   每一个 Range 对象由一起始和一终止字符位置定义。
	*   使用 Range 对象识别文档的指定部分。
	*   Range 对象只在定义该对象的过程正在运行时才存在。
    *   注意:   Range 对象和所选内容相互独立。
	*           即可定义和复制一个范围而不需改变所选内容。
	*           还可在文档中定义多个范围，但每一个窗格中只能有一个所选内容。
	*
	*/
	
	//  如果lParaCnt>0 则继续执行下面的操作
	//  否则，对一个空白文档签名没有意义

	if( lParaCnt > 0 ) 
    {
      //  指向文档的最后一段
	  
	 // pParagraph=pParagraphs->GetFirst();
	  pParagraph = pParagraphs->Item (lParaCnt);
//      ATLASSERT( pParagraph);

	  //  得到最后一段的Range 
	  pRange = pParagraph ->GetRange ();
      //ATLASSERT( pRange);
 
	  //  得到最后一段的End(按位置和字节计数)
      lParaEnd = pRange ->GetEnd();
	  
	  /*
	  *   补充知识：Selection
	  *   Selection对象代表窗口或窗格中的当前所选内容。
	  *   所选内容代表文档中被选定（或突出显示的）的区域，若文档中没有所选内容，则代表插入点。
	  *	  每个文档窗格只能有一个活动的 Selection 对象。
	  *   整个应用程序中只能有一个活动的 Selection 对象。
	  *
	  */

	  if( lParaEnd <= 5) 
	   {
	       //  如果lParaEnd <= 5		  
		   
		   pSelection = m_spApp-> GetSelection();

           pSelection ->TypeText("　　　　　");
		   
		   CComVariant Pos(lParaEnd);
		   
		   pRange = pWordDocument->Range(&Pos,&Pos);

//		   MessageBox(NULL, "lParaEnd <= 5", "OnClickButton", MB_OK); 
	   }
       else
       {
		   CComVariant Pos(lParaEnd-5);
		   pRange = pWordDocument->Range(&Pos,&Pos);

//		   MessageBox(NULL, "lParaEnd > 5", "OnClickButton", MB_OK);
	   }
      	   
	   pRange->Select();
	  
  //     MessageBox(NULL, "0000", "OnClickButton", MB_OK);
	}
    else
	{
		return;
	}

     try
	 {      		
		  pSelection =m_spApp->GetSelection();
		  //ATLASSERT( pSelection);

		  pRange = pSelection->GetRange();
		  //ATLASSERT( pRange);

		  pRange ->get_InlineShapes(&pInlineshapes);//>InlineShapes;//>GetInlineShapes();

		  /*
		  *   补充知识：InlineShapes
		  *   是由 InlineShape 对象组成的集合，
		  *   该集合代表文档、区域或选定内容的所有嵌入式图形。
		  *   用 InlineShapes 属性可返回 InlineShapes 集合。
		  *   注意：
		  *     1、可将活动文档中的每个嵌入式图形转换为 Shape 对象。
		  *        尽管 Shape 对象锁定于某一文本区域，
		  *        但可将其自由浮移，并可将其放置于页面上的任何位置。
		  *        可用 ConvertToInlineShape 方法和 ConvertToShape 方法来转换图形的类型。
		  *     2、只能将图片、OLE 对象和 ActiveX 控件转换为嵌入式图形。
		  *        文档中该集合的 Count 属性仅返回正文部分的项目数。
		  *		   使用集合的 Range 对象可计算其他部分的项目数。
		  *
		  */

		  //测试用
	//	  itoa(pRange->GetStart(), string, 10);
	//	  MessageBox(NULL,string, "2-lParaStart", MB_OK);	
		  
	//	  itoa(pRange->GetEnd(), string, 10);
	//	  MessageBox(NULL,string, "2-2 ParaEnd", MB_OK);		  
		  
		  // 在指定位置插入图形
		  LPCTSTR FileName =_T(TEMP_SEAL_BMP_PATH); 
		  CComVariant LinkToFile(FALSE);
		  CComVariant SaveWithDocument(TRUE); 

	
		  // 这一句不太正确，最后一个位置参数不知该如何设置
		   pInlineshapes->AddPicture(FileName,&LinkToFile,&SaveWithDocument/*,varSrc*/);

      
		  /*
		  *   对当前的图章进行浮动处理
		  *   1、获得当前文档中的InlineShapes集合
		  *   2、将选定的InlineShape对象由嵌入式图形转换为shape
		  *   3、对shape对象进行浮动处理
		  */
		  
		  // 获得当前文档中的InlineShapes集合
		  pInlineshapes=pWordDocument->GetInlineShapes();
		  InlineShapesCnt = pInlineshapes->Count;
 
		  pInlineshape = pInlineshapes->Item(InlineShapesCnt);
		  
		  pInlineshape->Select();
		  pInlineshape->ConvertToShape();
	  	  			
		  pSelection =m_spApp->GetSelection();

		  pShapeRange=pSelection->GetShapeRange(); 


		  // 对当前的图形进行浮动及尺寸大小处理 

		  pFillFormat = pShapeRange ->GetFill();
		  //ATLASSERT( pFillFormat);

		  pFillFormat->put_Visible(msoFalse);
		 // pShapeRange ->Fill->put_Transparency((float)1);
		  
		  pLineFormat = pShapeRange ->GetLine();
		  
		  pLineFormat->put_Weight(0.75);
		  pLineFormat->put_DashStyle(msoLineSolid);
		  pLineFormat->put_Style(msoLineSingle);
		  pLineFormat->put_Transparency((float)0);
		  pLineFormat->put_Visible(msoFalse);

		  pShapeRange->put_LockAspectRatio(msoTrue);
		  pShapeRange->put_Height(118.5);
		  pShapeRange->put_Width ((float)129);

		  pPictureFormat =pShapeRange ->GetPictureFormat();
		  //ATLASSERT(pWrapFormat);

		  pPictureFormat->put_Brightness(0.5);
		  pPictureFormat->put_Contrast(0.5);
		  pPictureFormat->put_ColorType(msoPictureAutomatic);
		  pPictureFormat->put_CropLeft((float)0);
		  pPictureFormat->put_CropRight((float)0);
		  pPictureFormat->put_CropTop((float)0);
		  pPictureFormat->put_CropBottom((float)0);
      
		  pShapeRange->put_RelativeHorizontalPosition(wdRelativeHorizontalPositionPage);
		  pShapeRange->put_RelativeVerticalPosition(wdRelativeVerticalPositionPage);
		  pShapeRange->put_Left(m_spApp->CentimetersToPoints(11.17));
		  pShapeRange->put_Top(m_spApp->CentimetersToPoints(19.02));
		  pShapeRange->put_LockAnchor(true);
		  
		  pWrapFormat= pShapeRange ->GetWrapFormat();
		  //ATLASSERT(pWrapFormat);

		  pWrapFormat->put_AllowOverlap(true);
		  pWrapFormat->put_Side(wdWrapBoth);
		  pWrapFormat->put_DistanceLeft(m_spApp->CentimetersToPoints(0.32));
		  pWrapFormat->put_DistanceTop(m_spApp->CentimetersToPoints(0));
		  pWrapFormat->put_DistanceBottom(m_spApp->CentimetersToPoints(0));
		  pWrapFormat->put_DistanceRight(m_spApp->CentimetersToPoints(0.32));
		  pWrapFormat->put_Type(wdWrapNone);
		  
	//	  pShapeRange->ZOrder(msoSendBehindText);
		  pPictureFormat->put_TransparentBackground(msoTrue);
		  pPictureFormat->put_TransparencyColor(RGB(255, 255, 255)); 
		  pFillFormat->put_Visible(msoFalse);
      
		  m_spApp->Visible=true;
		  MessageBox(NULL,_T("签章成功"),_T("提示"),MB_OK);
		  return;
	}
    catch(LPCTSTR errInfo)
	{
      MessageBox(NULL, errInfo, "Error Information", MB_OK);
	}
}

/*
 *	check the file
 */
void __stdcall CmySeal::OnClickButton2(IDispatch * 
        /*Office::_CommandBarButton**/ Ctrl,VARIANT_BOOL * CancelDefault)
{
	//start of new coding @2011-1-3
    ATLASSERT(m_spApp);
	m_spApp->Visible=true;

	Word::RangePtr pRange ;
 	Word::ParagraphPtr pParagraph;
 	Word::SelectionPtr pSelection;
	Word::_DocumentPtr pWordDocument;
	Word::ParagraphsPtr pParagraphs;
    Word::InlineShapesPtr pInlineshapes;
	Word::InlineShapePtr pInlineshape;
	Word::ShapeRangePtr pShapeRange;
	Word::LineFormatPtr pLineFormat;
	Word::PictureFormatPtr pPictureFormat;
	Word::WrapFormatPtr pWrapFormat;
	Word::FillFormatPtr pFillFormat;
	
 	long  lParaCnt,lParaEnd,lParaStart,InlineShapesCnt;   
	//  得到当前活动文档
	pWordDocument =m_spApp-> GetActiveDocument();
	pSelection =m_spApp->GetSelection();

	//convert doc 2 html thus seal become png format with alpha to white color
	CWordConv doconv;
	BSTR doc_path;
	pWordDocument->get_FullName(&doc_path);
	_variant_t html_path(TEMP_HTML_FILE_PATH);
	_variant_t text_path(TEMP_TEXT_FILE_PATH);//MD5 FILE FROM DOC FILE

	doconv.DocToHtml(doc_path,html_path.bstrVal);

	doconv.DocToTxt(doc_path,text_path.bstrVal);
	//get md5 and write it into file
	CMd5 oGetMd5(TEMP_TEXT_FILE_PATH);
	LPCTSTR md5str = oGetMd5.GetDigestKey();
	TRACE(_T(md5str));

	//search in TEMP_HTML_FOLDER_PATH looking for ***.png
	CFileFilter objfile;
	bool ret=objfile.GetSeal(TEMP_HTML_FOLDER_PATH,md5str);
	if (false==ret)
	{
		MessageBox(NULL,_T("没有监测到数字签名"),_T("提示"),MB_OK);
	}
	else
	{
		MessageBox(NULL,_T("检验通过"),_T("提示"),MB_OK);
	}

}
/*
 *	get seal picture from document,note that file format is emf,and the seal has alpha
 *	need to convert emf file's black color to bmp file's white color
 */
bool CmySeal::GetSealfromDoc()
{
	if(!OpenClipboard(0))
	{
		return false;
	}
	
	DWORD   dwError; 
	UINT nRet = EnumClipboardFormats(CF_ENHMETAFILE);
	if(nRet) 
	{
		BOOL   ba=::IsClipboardFormatAvailable(CF_ENHMETAFILE);   
		
		HANDLE   hClip=::GetClipboardData(CF_ENHMETAFILE); 
		
		HENHMETAFILE hEnhMetaFile=(HENHMETAFILE)hClip;  
		
		dwError=GetLastError();   //   dwError=6，无效的句柄。   
		
		
		CString str = "d:\\aaa.emf";
		
		HENHMETAFILE   hMetaFile=CopyEnhMetaFile(hEnhMetaFile, str);//保存到文件
		
		//关闭CMetafileDC并获得它的句柄
		
		DeleteEnhMetaFile(hMetaFile);
		
		dwError=GetLastError();   //   dwError=6，无效的句柄。   
	} 
	
	::CloseClipboard();
	return true;
}

