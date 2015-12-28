// Word2Txt.h: interface for the CWord2Txt class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_WORD2TXT_H__BFE16D75_53F4_49C3_AC30_745FC512A090__INCLUDED_)
#define AFX_WORD2TXT_H__BFE16D75_53F4_49C3_AC30_745FC512A090__INCLUDED_

#include "stdafx.h"
#include "Word2txt.h"
#include "Md5.h"
#include <ole2.h>
#include <stdio.h>
#include <comdef.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWordConv  
{
public:
	bool RemoveFolder(char *path);
	void DocToHtml(BSTR in_doc_path,BSTR in_html_path);
	CWordConv();
	virtual ~CWordConv();
    void DocToTxt(BSTR bstrOpenFile, BSTR bstrSaveFile);
};

#endif // !defined(AFX_WORD2TXT_H__BFE16D75_53F4_49C3_AC30_745FC512A090__INCLUDED_)
