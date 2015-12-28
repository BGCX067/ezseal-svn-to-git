// Embedded.cpp: implementation of the CEmbedded class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "Embedded.h"
#include "windowsx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DIB_HEADER_MARKER ((WORD)('M'<<8)|'B')
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmbedded::CEmbedded()
{
	m_sTxt=_T(TEMP_MD5_STRING_PATH);
	m_sBmp=_T(TEMP_SEAL_BMP_PATH);
	m_sOut=_T(TEMP_EMBED_SEAL_PATH);
}

CEmbedded::CEmbedded(char *bmp_path,char *txt_path,char *out_path)
{
	m_sTxt=_T(txt_path);
	m_sBmp=_T(bmp_path);
	m_sOut=_T(out_path);
}
CEmbedded::CEmbedded(char *bmp_path,char *txt_path)
{
	m_sTxt=_T(txt_path);
	m_sBmp=_T(bmp_path);
}
CEmbedded::~CEmbedded()
{

}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void CEmbedded::Embedded()
{
	// TODO: Add your control notification handler code here
	if(Is24bitBMP()==-1)
		return;
	DWORD Offset=Is24bitBMP();
	BYTE byteSecret,byteBitmap[8];
	const int mark[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	
	CFile fSecret(m_sTxt,CFile::modeReadWrite);
	CFile file(m_sBmp,CFile::modeReadWrite);
	file.Seek(Offset,CFile::begin);
	DWORD fSLong=fSecret.GetLength();
	CString strTemp;
	strTemp.Format("Secret file's length is %x!",fSLong);
	//AfxMessageBox(strTemp);
	TRACE(strTemp);
	BYTE byteSLong[4];
	byteSLong[0]=(char)(fSLong & 0x000000ff);
	byteSLong[1]=(char)((fSLong & 0x0000ff00)>>8);
	byteSLong[2]=(char)((fSLong & 0x00ff0000)>>16);
	byteSLong[3]=(char)((fSLong & 0xff000000)>>24);
	strTemp.Format("length(byte0,1,2,3) is %x_%x_%x_%x!",
		byteSLong[0],byteSLong[1],byteSLong[2],byteSLong[3]);
	//		AfxMessageBox(strTemp);
	TRACE(strTemp);
	for(int i=0;i<4 && file.Read(byteBitmap,8)==8;i++)
	{
		strTemp.Format("byteBitmap is %x-%x-%x-%x-%x-%x-%x-%x!",
			byteBitmap[0],byteBitmap[1],byteBitmap[2],byteBitmap[3],
			byteBitmap[4],byteBitmap[5],byteBitmap[6],byteBitmap[7]);
		//		AfxMessageBox(strTemp);
		for(int j=0;j<8;j++)
		{
			if((byteSLong[i] & mark[j])>>j)
				byteBitmap[j]|=1;
			else
				byteBitmap[j]&=0xfe;
		}
		file.Seek(-8,CFile::current);
		file.Write(byteBitmap,8);
		strTemp.Format("byteBitmap is %x-%x-%x-%x-%x-%x-%x-%x!",
			byteBitmap[0],byteBitmap[1],byteBitmap[2],byteBitmap[3],
			byteBitmap[4],byteBitmap[5],byteBitmap[6],byteBitmap[7]);
		//		AfxMessageBox(strTemp);
		TRACE(strTemp);
	}
	while(fSecret.Read(&byteSecret,1)==1
		&& file.Read(byteBitmap,8)==8)
	{
		strTemp.Format("byteSecret is %c:%x!",byteSecret,byteSecret);
		//		AfxMessageBox(strTemp);
		for(i=0;i<8;i++)
		{
			if((byteSecret & mark[i])>>i)
				byteBitmap[i]|=1;
			else
				byteBitmap[i]&=0xfe;
		}
		file.Seek(-8,CFile::current);
		file.Write(byteBitmap,8);
	}
	file.Close();
	if(fSecret.GetPosition()!=fSecret.GetLength())
		TRACE("Bitmap is too little,Secret false!");
	else
		TRACE("OK!");
	fSecret.Close();
}
void CEmbedded::DeEmbedded()
{
	if(Is24bitBMP()==-1)
		return;
	DWORD Offset=Is24bitBMP();
	BYTE byteSecret=0,byteBitmap[8];
	const int mark[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	
	CFile file(m_sBmp,CFile::modeReadWrite);
	CFile fSecret;

	TRACE(_T("CEmbedded::DdEmbedded secret file to create:"));
	TRACE(m_sTxt);
	TRACE(_T("\r\n"));

	remove(m_sTxt.GetBuffer(0));
	m_sTxt.ReleaseBuffer(); //ms_sTxt become "",why?

	fSecret.Open(m_sTxt,CFile::modeCreate | CFile::modeReadWrite);
	file.Seek(Offset,CFile::begin);
	DWORD fSLong=0;
	BYTE byteSLong[4];
	for(int i=0;i<4 && file.Read(byteBitmap,8)==8;i++)
	{
		byteSLong[i]=0;
		for(int j=0;j<8;j++)
		{
			if(byteBitmap[j] & 0x01)
				byteSLong[i]=byteSLong[i]|(1<<j);
		}
		fSLong=fSLong|(byteSLong[i]<<(i*8));
	}
	CString strTemp;
	strTemp.Format("Secret file's length is %d!",fSLong);
	DWORD iReadLong=0;
	while(iReadLong<fSLong
		&& file.Read(byteBitmap,8)==8)
	{
		byteSecret=0;
		for(i=0;i<8;i++)
		{
			if(byteBitmap[i] & 0x01)
				byteSecret|=1<<i;
		}
		strTemp.Format("byteSecret is %c:%x!",byteSecret,byteSecret);
		fSecret.Write(&byteSecret,1);
		iReadLong++;
	}
	file.Close();
	fSecret.Close();
}
DWORD CEmbedded::Is24bitBMP()
{

	CFile file(m_sBmp,CFile::modeReadWrite);
	BITMAPFILEHEADER bmfHeader;

	if(file.Read((LPSTR)&bmfHeader,sizeof(bmfHeader))!=sizeof(bmfHeader))
	{
		AfxMessageBox("Error in Reading BitmapHeadInfo!"); 
		return -1;
	}
	if(bmfHeader.bfType!=DIB_HEADER_MARKER)
	{
		//AfxMessageBox("Isn't Bitmap file!");
		return -1;
	}

	LPBITMAPINFO lpbmInfo=(LPBITMAPINFO)GlobalAllocPtr(GHND,bmfHeader.bfOffBits-sizeof(bmfHeader));
	if(lpbmInfo==0)
	{
		AfxMessageBox("Error in Allocation LPBitmapInfo!");
		return -1;
	}
	if(file.Read(lpbmInfo,bmfHeader.bfOffBits-sizeof(bmfHeader))
		!=bmfHeader.bfOffBits-sizeof(bmfHeader))
	{
		GlobalFreePtr(lpbmInfo);
		lpbmInfo=NULL;
		AfxMessageBox("Error in Reading BitmapInfo!");
		return -1;
	}

	if(lpbmInfo->bmiHeader.biBitCount!=24||lpbmInfo->bmiHeader.biCompression!=BI_RGB)
		{
			CString str;
			str.Format("Bitmap is %dbit ,not 24bit !",lpbmInfo->bmiHeader.biBitCount);
			//AfxMessageBox(str);
			TRACE(str);
			return -1;
		}

	GlobalFreePtr(lpbmInfo);
	lpbmInfo=NULL;

	return bmfHeader.bfOffBits;
}

void CEmbedded::SetBmpPath(char *path)
{
	m_sBmp=_T(path);
}

void CEmbedded::SetTextPath(char *path)
{
	m_sTxt=_T(path);
}

void CEmbedded::Lsb_embedded(const char *in_base_pic, const char *in_sub_file)
{
	if ((NULL==in_base_pic)||(NULL==in_sub_file))
	{
		return;
	}
	m_dib.Load(in_base_pic);
	m_dib.LoadEmbFile(in_sub_file);

//////////////////////////////////////////////////////////////////////////
	
	if (m_dib.bitmap_size / m_dib.embfile_size < 8)
	{
		AfxMessageBox("文件太大，无法嵌入！");
		return;
	}
	else
	{
		m_dib.Embed();   //嵌入
		m_dib.Save( m_sOut.GetBuffer(0) );
		m_sOut.ReleaseBuffer();
	}
}
void CEmbedded::Lsb_embedded(
							 const char *in_base_pic,
							 const char *in_sub_file,
							 const char *in_output_bmp
							 )
{
	if ((NULL==in_base_pic)||(NULL==in_sub_file))
	{
		return;
	}
	m_dib.Load(in_base_pic);
	m_dib.LoadEmbFile(in_sub_file);	
	//////////////////////////////////////////////////////////////////////////	
	if (m_dib.bitmap_size / m_dib.embfile_size < 8)
	{
		AfxMessageBox("文件太大，无法嵌入！");
		return;
	}
	else
	{
		m_dib.Embed();   //嵌入
		m_dib.Save( in_output_bmp );
	}
}

void CEmbedded::Lsb_dembedded(const char *in_embedded_pic, const char *in_output_file)
{
	if ((NULL==in_embedded_pic)||(NULL==in_output_file))
	{
		TRACE(_T("\r\nNULL ptr of parameter"));
	}
	m_dib.Load(in_embedded_pic);
	if (0==m_dib.tag)
	{
		TRACE(_T("\r\nno ebedded info in this pic..\r\n"));
		return;
	}
	m_dib.Pick();
	m_dib.SavePicked(in_output_file);
}