// ImageConv.h: interface for the CImageConv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGECONV_H__5A97CC33_C457_4D83_9EDA_FBE4C6BC168B__INCLUDED_)
#define AFX_IMAGECONV_H__5A97CC33_C457_4D83_9EDA_FBE4C6BC168B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageConv  
{
public:
	bool png2bmp(char *in_png_path,char *in_bmp_path);
	bool emf2bmp(char *in_emf_path,char *in_bmp_path);
	bool bmp2png(char *in_bmp_path,char *in_png_path);
	CImageConv();
	virtual ~CImageConv();

};

#endif // !defined(AFX_IMAGECONV_H__5A97CC33_C457_4D83_9EDA_FBE4C6BC168B__INCLUDED_)
