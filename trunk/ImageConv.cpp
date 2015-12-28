// ImageConv.cpp: implementation of the CImageConv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ImageConv.h"

#include "inc/ximage.h"

#pragma comment(lib,"lib/cximage.lib")
#pragma comment(lib,"lib/png.lib")
#pragma comment(lib,"lib/jpeg.lib")
#pragma comment(lib,"lib/zlib.lib")
#pragma comment(lib,"lib/tiff.lib")
#pragma comment(lib,"lib/jasper.lib")


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageConv::CImageConv()
{

}

CImageConv::~CImageConv()
{

}

bool CImageConv::bmp2png(char *in_bmp_path, char *in_png_path)
{
	bool ret=false;
	CxImage pic;
	ret=pic.Load(in_bmp_path,CXIMAGE_FORMAT_BMP);
	if (ret==false)
	{
		TRACE("failed to load bmp file\r\n");
		return ret;
	}
	remove(in_png_path);
	ret=pic.Save(in_png_path,CXIMAGE_FORMAT_PNG);
	if (ret==false)
	{
		TRACE("failed to conve png file\r\n");
		return ret;
	}
	return ret;
}

bool CImageConv::emf2bmp(char *in_emf_path, char *in_bmp_path)
{
	bool ret=false;
	CxImage seal;
	seal.Load(in_emf_path,CXIMAGE_FORMAT_WMF);
	remove(in_bmp_path);
	seal.Save(in_bmp_path,CXIMAGE_FORMAT_BMP);
	return true;
}

bool CImageConv::png2bmp(char *in_png_path, char *in_bmp_path)
{
	bool ret=false;
	CxImage seal;
	seal.Load(in_png_path,CXIMAGE_FORMAT_PNG);
	remove(in_bmp_path);
	seal.Save(in_bmp_path,CXIMAGE_FORMAT_BMP);
	
	return true;
}
