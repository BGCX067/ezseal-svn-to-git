// Embedded.h: interface for the CEmbedded class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMBEDDED_H__0441B537_A347_4AFD_B14A_CE00C3535D10__INCLUDED_)
#define AFX_EMBEDDED_H__0441B537_A347_4AFD_B14A_CE00C3535D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DIB.h"

class CEmbedded  
{
public:
	CString m_sOut;
	void Lsb_dembedded(const char  *in_embedded_pic,const char *in_output_file);
	void Lsb_embedded(const char *in_base_pic,const char *in_sub_file);
	void Lsb_embedded(const char *in_base_pic,const char *in_sub_file,const char *in_output_bmp);
	void SetTextPath(char *path);
	void SetBmpPath(char *path);
	CString m_sBmp;
	CString m_sTxt;
	CDib m_dib;

	CEmbedded();
	CEmbedded(char *bmp_path,char *txt_path,char *out_path);
	//save in bmp_path
	CEmbedded(char *bmp_path,char *txt_path);
	virtual ~CEmbedded();

	void Embedded();
	void DeEmbedded();
	DWORD Is24bitBMP();

};

#endif // !defined(AFX_EMBEDDED_H__0441B537_A347_4AFD_B14A_CE00C3535D10__INCLUDED_)
