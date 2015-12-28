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
// 		MessageBox(NULL,   W2CT(bstrName),   _T("��ǰ�ĵ�"),   MB_OK); 

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
	*	�ڵ�ǰ������ڴ��������ͼ�»����ǩ��
	*   1���ҵ���ǰ������ڴ�(Ŀǰʵ�ֵ������ĵ���δβ����ͼ��
	*   2���򿪶Ի���
	*   3��ѡ�����ͼ��
	*   4������ָ��λ�ã�����ͼ�ν��д���
	*   5���Ե�ǰ��ͼ�»�ǩ�����������Ϣ
	*   ʹ��������������ͼƬ������ı���,�ı���������ʾ���߻�������Ϣ
	*
	*/
   
	//  �õ���ǰ��ĵ�
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
	

	//  �õ���ǰ��ĵ���Paragraph����
    pParagraphs = pWordDocument->GetParagraphs ();
//    ATLASSERT( pParagraph);
    
	// �õ���ǰ�ĵ���paragraphs��,��ֵlParaCnt
	lParaCnt = pParagraphs ->GetCount (); 
      
	// Ϊ������
	// ��ʾlParaCntֵ
//	char string[25]; 
//	itoa(lParaCnt, string, 10); 
//	MessageBox(NULL,string, "lParaCnt", MB_OK);
	 
    /*  
	*   ����֪ʶ��Range   
	*	Range��������ĵ��е�һ��������Χ��
	*   ÿһ�� Range ������һ��ʼ��һ��ֹ�ַ�λ�ö��塣
	*   ʹ�� Range ����ʶ���ĵ���ָ�����֡�
	*   Range ����ֻ�ڶ���ö���Ĺ�����������ʱ�Ŵ��ڡ�
    *   ע��:   Range �������ѡ�����໥������
	*           ���ɶ���͸���һ����Χ������ı���ѡ���ݡ�
	*           �������ĵ��ж�������Χ����ÿһ��������ֻ����һ����ѡ���ݡ�
	*
	*/
	
	//  ���lParaCnt>0 �����ִ������Ĳ���
	//  ���򣬶�һ���հ��ĵ�ǩ��û������

	if( lParaCnt > 0 ) 
    {
      //  ָ���ĵ������һ��
	  
	 // pParagraph=pParagraphs->GetFirst();
	  pParagraph = pParagraphs->Item (lParaCnt);
//      ATLASSERT( pParagraph);

	  //  �õ����һ�ε�Range 
	  pRange = pParagraph ->GetRange ();
      //ATLASSERT( pRange);
 
	  //  �õ����һ�ε�End(��λ�ú��ֽڼ���)
      lParaEnd = pRange ->GetEnd();
	  
	  /*
	  *   ����֪ʶ��Selection
	  *   Selection��������ڻ򴰸��еĵ�ǰ��ѡ���ݡ�
	  *   ��ѡ���ݴ����ĵ��б�ѡ������ͻ����ʾ�ģ����������ĵ���û����ѡ���ݣ���������㡣
	  *	  ÿ���ĵ�����ֻ����һ����� Selection ����
	  *   ����Ӧ�ó�����ֻ����һ����� Selection ����
	  *
	  */

	  if( lParaEnd <= 5) 
	   {
	       //  ���lParaEnd <= 5		  
		   
		   pSelection = m_spApp-> GetSelection();

           pSelection ->TypeText("����������");
		   
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
		  *   ����֪ʶ��InlineShapes
		  *   ���� InlineShape ������ɵļ��ϣ�
		  *   �ü��ϴ����ĵ��������ѡ�����ݵ�����Ƕ��ʽͼ�Ρ�
		  *   �� InlineShapes ���Կɷ��� InlineShapes ���ϡ�
		  *   ע�⣺
		  *     1���ɽ���ĵ��е�ÿ��Ƕ��ʽͼ��ת��Ϊ Shape ����
		  *        ���� Shape ����������ĳһ�ı�����
		  *        ���ɽ������ɸ��ƣ����ɽ��������ҳ���ϵ��κ�λ�á�
		  *        ���� ConvertToInlineShape ������ ConvertToShape ������ת��ͼ�ε����͡�
		  *     2��ֻ�ܽ�ͼƬ��OLE ����� ActiveX �ؼ�ת��ΪǶ��ʽͼ�Ρ�
		  *        �ĵ��иü��ϵ� Count ���Խ��������Ĳ��ֵ���Ŀ����
		  *		   ʹ�ü��ϵ� Range ����ɼ����������ֵ���Ŀ����
		  *
		  */

		  //������
	//	  itoa(pRange->GetStart(), string, 10);
	//	  MessageBox(NULL,string, "2-lParaStart", MB_OK);	
		  
	//	  itoa(pRange->GetEnd(), string, 10);
	//	  MessageBox(NULL,string, "2-2 ParaEnd", MB_OK);		  
		  
		  // ��ָ��λ�ò���ͼ��
		  LPCTSTR FileName =_T(TEMP_SEAL_BMP_PATH); 
		  CComVariant LinkToFile(FALSE);
		  CComVariant SaveWithDocument(TRUE); 

	
		  // ��һ�䲻̫��ȷ�����һ��λ�ò�����֪���������
		   pInlineshapes->AddPicture(FileName,&LinkToFile,&SaveWithDocument/*,varSrc*/);

      
		  /*
		  *   �Ե�ǰ��ͼ�½��и�������
		  *   1����õ�ǰ�ĵ��е�InlineShapes����
		  *   2����ѡ����InlineShape������Ƕ��ʽͼ��ת��Ϊshape
		  *   3����shape������и�������
		  */
		  
		  // ��õ�ǰ�ĵ��е�InlineShapes����
		  pInlineshapes=pWordDocument->GetInlineShapes();
		  InlineShapesCnt = pInlineshapes->Count;
 
		  pInlineshape = pInlineshapes->Item(InlineShapesCnt);
		  
		  pInlineshape->Select();
		  pInlineshape->ConvertToShape();
	  	  			
		  pSelection =m_spApp->GetSelection();

		  pShapeRange=pSelection->GetShapeRange(); 


		  // �Ե�ǰ��ͼ�ν��и������ߴ��С���� 

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
		  MessageBox(NULL,_T("ǩ�³ɹ�"),_T("��ʾ"),MB_OK);
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
	//  �õ���ǰ��ĵ�
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
		MessageBox(NULL,_T("û�м�⵽����ǩ��"),_T("��ʾ"),MB_OK);
	}
	else
	{
		MessageBox(NULL,_T("����ͨ��"),_T("��ʾ"),MB_OK);
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
		
		dwError=GetLastError();   //   dwError=6����Ч�ľ����   
		
		
		CString str = "d:\\aaa.emf";
		
		HENHMETAFILE   hMetaFile=CopyEnhMetaFile(hEnhMetaFile, str);//���浽�ļ�
		
		//�ر�CMetafileDC��������ľ��
		
		DeleteEnhMetaFile(hMetaFile);
		
		dwError=GetLastError();   //   dwError=6����Ч�ľ����   
	} 
	
	::CloseClipboard();
	return true;
}

