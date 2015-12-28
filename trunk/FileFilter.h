// FileFilter.h: interface for the CFileFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEFILTER_H__BB9218A3_46C9_4B2B_8A23_F1D2DFA9D6F7__INCLUDED_)
#define AFX_FILEFILTER_H__BB9218A3_46C9_4B2B_8A23_F1D2DFA9D6F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CFileFilter  
{
public:
	void Find(char *in_folder_path);
	CFileFilter();
	CFileFilter(char *in_folder_path){m_folder=in_folder_path;};
	virtual ~CFileFilter();

public:
	CString m_folder;
	bool FilPicture(const char *in_md5_str);
	bool GetSeal(char *in_folder_path,const char *in_md5_str);
	std::vector<CString> m_filenames;

};

#endif // !defined(AFX_FILEFILTER_H__BB9218A3_46C9_4B2B_8A23_F1D2DFA9D6F7__INCLUDED_)
