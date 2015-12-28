// FileFilter.cpp: implementation of the CFileFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "FileFilter.h"

#include "Embedded.h"
#include "ImageConv.h"
#include "RSATool.h"

#include <fstream>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileFilter::CFileFilter()
{
	m_filenames.empty();
}

CFileFilter::~CFileFilter()
{

}

//DEL bool CFileFilter::GetSeal(char *in_folder_path,int *out_count,char **out_file_names)
//DEL {
//DEL 	if (NULL==in_folder_path)
//DEL 	{
//DEL 		return false;
//DEL 	}
//DEL 
//DEL 	return false;
//DEL }
bool CFileFilter::GetSeal(char *in_folder_path,const char *in_md5_str)
{
	char path[256];
	memset(path,'\0',256);

	if (NULL==in_folder_path) 
	{
		return false;
	}
	strcpy(path,in_folder_path);

	int path_lenght=strlen(in_folder_path);
	if ( '\\' != in_folder_path[path_lenght] )//path string has no end of 
	{
		strcat(path,"\\");
	}

	this->Find(path);
	this->FilPicture(in_md5_str);

	return true;
}

void CFileFilter::Find(char *in_folder_path)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind,in_folder_path);
	strcat(szFind,"\\*.png");

	m_folder.Empty();
	m_folder.Format(_T("%s"),in_folder_path);

	HANDLE hFind=::FindFirstFile(szFind,&FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
		return;
	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0]!='.')
			{
				strcpy(szFind,in_folder_path);
				strcat(szFind,"");
				strcat(szFind,FindFileData.cFileName);
				Find(szFind);
			}
		}
		else
		{
			//png file name cout << FindFileData.cFileName<<endl;
			m_filenames.push_back(_T(FindFileData.cFileName));
		}
		if(!FindNextFile(hFind,&FindFileData))	break;
	}
	FindClose(hFind);
}

/************************************************************************
*filt picture names and check md5 code
*
*support only one seal
*
*1:check every file in m_filenames;
*	convert it to bmp
*	get md5 file->check file length(32)->
*	check md5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
*	check file content((0-9)||(a-f))
*	get png which is not a seal,put the flag into index
*2:remove m_filenames' superfluous member
************************************************************************/
bool CFileFilter::FilPicture(const char *in_md5_str)
{
	int counts=0;//png files count in temp folder
	vector<int> index;
	char filepath[256];//png file full path
	CImageConv imgconv;

	counts=m_filenames.size();
	if (counts ==0)
	{
		return false;
	}
	
	//md5 code from doc

	char md5[40];
	memset(md5,'\0',40);
	strcpy(md5,in_md5_str);

	TRACE1(_T("md5 code : %s"),md5);

	for (int i=0;i<counts;i++)
	{
		CString spath=m_folder+m_filenames[i];
		LPCTSTR p=spath.GetBuffer(0);
		if (p==NULL)
		{
			return false;
		}
		memset(filepath,'\0',256);
		strcpy(filepath,p);
		TRACE1(_T("\r\ntesting png file: %s\r\n"),filepath);

		::remove(TEMP_SEAL_BMP_PATH);
		::remove(TEMP_MD5_CHECK_PATH);
		//png->bmp->md5 file 
		imgconv.png2bmp(filepath,TEMP_SEAL_BMP_PATH);
		spath.ReleaseBuffer();
		CEmbedded objemb(TEMP_SEAL_BMP_PATH,TEMP_MD5_CHECK_PATH);
		objemb.DeEmbedded();

		//check file length 
		fstream fs_check;
		fs_check.open(TEMP_MD5_CHECK_PATH,ios::in);
		fs_check.seekg(0,ios::end);
		long flength=fs_check.tellg();
//		if (32!=flength)
//		{
//			index.push_back(i);
//			fs_check.close();
//			continue;
//		}
		char *buffer=NULL;
		buffer=(char *)malloc(200*sizeof(char));
		memset(buffer,'\0',200);

		//get check file content
		fs_check.seekg(ios::beg);
		fs_check.read(buffer,flength);
		
		TRACE1(_T("signed string from image: %s"),buffer);
		fs_check.close();

		CRSATool otool;
		if (true==otool.Verify(in_md5_str,strlen(in_md5_str),buffer,sizeof(buffer)))
		{
			return true;//get seal
		}
		else
		{
			index.push_back(i);
			continue;
		}
// 		for (int j=0;j<32;j++)
// 		{
// 			if ((buffer[j]<48)||(buffer[j]>57))//!(0-9)
// 			{
// 				index.push_back(i);
// 				j=32;
// 			}
// 			if ((buffer[j]<97)||(buffer[j]>102))//!(a-f)
// 			{
// 				index.push_back(i);
// 				j=32;
// 			}
// 		}//end of j

	}//end of counts

// 	//remove the index[i] file name;
// 	for (vector<int>::iterator flag=index.begin();flag!=index.end();flag++)
// 	{
// 		m_filenames.erase(m_filenames.begin()+*flag);
// 	}
// 	if (0==m_filenames.size())
// 	{
// 		TRACE(_T("no seal detected...\r\n"));
// 		return false;
// 	}

	return false;
}
