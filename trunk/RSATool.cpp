// RSATool.cpp: implementation of the CRSATool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "RSATool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRSATool::CRSATool()
{

}

CRSATool::~CRSATool()
{

}

bool CRSATool::Sign(const char *in_buffer,char *out_bufer,unsigned int *out_buffer_len)
{
	bool bret=false;
	//openssl operator...
	BIO *pBpri=NULL;
	RSA *pRpri=NULL;	

	OpenSSL_add_all_algorithms();
	pBpri=BIO_new_file(TEMP_PKI_PRI_KEY_PATH,"r");
	if (NULL==pBpri)
	{
		TRACE("failed to create pBpri\r\n");
		return false;
	}
	pRpri=RSA_new();
	if (NULL==pRpri)
	{
		TRACE("fail to create pRpri\r\n");
		return false;
	}
	pRpri=PEM_read_bio_RSAPrivateKey(pBpri,&pRpri,NULL,NULL);
	if (NULL==pRpri)
	{
		TRACE("fail to read pRpri from pri.pem\r\n");
		return false;
	}
	
	int iret=RSA_sign(
					NID_md5,
					reinterpret_cast<const unsigned char *>(in_buffer),
					55,
					reinterpret_cast<unsigned char *>(out_bufer),
					out_buffer_len,
					pRpri);
	if (1!=iret)
	{
		TRACE("FAIL TO SIGN BUFFER\r\n");
		return false;
	}
	
	return true;
}

bool CRSATool::Verify(const char *in_md5,unsigned int in_md5_len,char *in_sign,unsigned int in_sign_len)
{
	BIO *pBpub=NULL;
	RSA *pRpub=NULL;
	
	OpenSSL_add_all_algorithms();

	pBpub=BIO_new_file(TEMP_PKI_PUB_KEY_PATH,"r");
	if (NULL==pBpub)
	{
		TRACE("fail to create pBpub\r\n");
		return false;
	}
	pRpub=RSA_new();
	if (NULL==pRpub)
	{
		TRACE("fail to create pRpub\r\n");
		return 0;
	}
	pRpub=PEM_read_bio_RSA_PUBKEY(pBpub,&pRpub,NULL,NULL);
	if (NULL==pRpub)
	{
		TRACE("fail to read pRpub from pBpub\r\n");
		return 0;
	}

	int iret=0;
	iret=RSA_verify(
		NID_md5,
		reinterpret_cast<const unsigned char *>(in_md5),
		in_md5_len,
		reinterpret_cast<unsigned char *>(in_sign),
		in_sign_len,
		pRpub);
	if (1!=iret)
	{
		TRACE("fail to verify\r\n");
		return false;
	}

	return true;
}
