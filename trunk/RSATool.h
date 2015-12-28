// RSATool.h: interface for the CRSATool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSATOOL_H__87E3218A_52D7_4FB3_A924_B446AD233E0A__INCLUDED_)
#define AFX_RSATOOL_H__87E3218A_52D7_4FB3_A924_B446AD233E0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRSATool  
{
public:
	bool Verify(const char *in_md5,unsigned int in_md5_len,char *in_sign,unsigned int in_sign_len);
	bool Sign(const char *in_buffer,char *out_bufer,unsigned int *out_buffer_len);
	CRSATool();
	virtual ~CRSATool();

};

#endif // !defined(AFX_RSATOOL_H__87E3218A_52D7_4FB3_A924_B446AD233E0A__INCLUDED_)
