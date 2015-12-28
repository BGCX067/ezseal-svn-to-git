// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__A0EA3E50_6E64_4CB9_9E49_348C4146CDA7__INCLUDED_)
#define AFX_STDAFX_H__A0EA3E50_6E64_4CB9_9E49_348C4146CDA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/************************************************************************/
/* need to clean these files @ the beginning?                           */
/************************************************************************/
//the temp file to create seal 
#define TEMP_SEAL_BMP_PATH "C:\\WINDOWS\\Temp\\temp_bmp.bmp"

//the bmp of embedded seal
#define TEMP_EMBED_SEAL_PATH "C:\\WINDOWS\\Temp\\seal_bmp.bmp"

#define TEMP_BMBED_SEAL_PATH "C:\\WINDOWS\\Temp\\beal_bmp.bmp"

//text file which get from doc file,use it to create md5
#define TEMP_TEXT_FILE_PATH "C:\\WINDOWS\\Temp\\temp_txt.txt"

//md5 file get from text file use it to create seal picture
#define TEMP_MD5_STRING_PATH "C:\\WINDOWS\\Temp\\MD5_txt.txt"

//html files to get seal picture of png format
#define TEMP_HTML_FILE_PATH "C:\\WINDOWS\\Temp\\temp_html.html"
#define TEMP_HTML_FOLDER_PATH "C:\\WINDOWS\\Temp\\temp_html.files"

//emf file which copy from doc files
#define TEMP_EMF_FILE_PATH "C:\\WINDOWS\\Temp\\emf_temp.emf"

//seal picture to extract md5 code
#define TEMP_CHECK_BMP_PATH "C:\\WINDOWS\\Temp\\temp_check.bmp"

//temp file to check md5
#define TEMP_MD5_CHECK_PATH "C:\\WINDOWS\\Temp\\MD5_TEMP.txt"

//I forgot
#define TEMP_SEAL_PNG_PATH "C:\\WINDOWS\\Temp\\temp_png.png"

//openssl setting
//pub key of rsa
#define TEMP_PKI_PUB_KEY_PATH "C:\\WINDOWS\\Temp\\pub.pem"
//private key of rsa
#define TEMP_PKI_PRI_KEY_PATH "C:\\WINDOWS\\Temp\\pri.pem"

#include <openssl/pem.h> 
#include <openssl/evp.h>

#pragma comment(lib,"ssleay32.lib")
#pragma comment(lib,"libeay32.lib")



#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h>   // MFC core and standard components
#include <afxext.h>   // MFC extensions
#include <afxdisp.h>  // MFC Automation extensions

#include <afxcmn.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>


#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE11\\mso.dll" \
rename_namespace("Office") named_guids,exclude("Pages")
using namespace Office;

#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.olb" rename_namespace("VBE6")
using namespace VBE6;

#import "C:\\Program Files\\Microsoft Office\\OFFICE11\\MSWORD.OLB"   rename("ExitWindows","ExitWindowsEx")

#import "C:\\Program Files\\Microsoft Office\\OFFICE11\\MSWORD.OLB" \
rename_namespace("Word"), raw_interfaces_only, named_guids ,exclude("Pages")
using namespace Word;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A0EA3E50_6E64_4CB9_9E49_348C4146CDA7__INCLUDED)
