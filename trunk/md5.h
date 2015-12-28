//LPCSTR TargetFile(char *filename=NULL);//计算文件的MD5值
//void TargetStr(LPCSTR str);//计算字符串的MD5值
//LPCSTR GetDigestKey();//取MD5运算后的结果
//LPCSTR GetErr();//如果有错误，取错误字串
////////////////////////////////////////////////////////////////////
///md5.h this is the head of the class md5.
#include <windows.h>
#include <fstream.h>

//using namespace std;

#ifndef __MD5CLASS__
#define __MD5CLASS__

#define ENGLISH

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

typedef LONGLONG LONG64;

class CMd5
{
public:
	CMd5();
	CMd5(char *filename);
	~CMd5();
	LPCSTR TargetFile(char *filename=NULL);
	void TargetStr(LPCSTR str);
	LPCSTR GetDigestKey();
	LPCSTR GetErr();
	
	
private:
	inline ULONG LRotate(ULONG Sdata,int nBit);
	inline ULONG F(ULONG x,ULONG y,ULONG z);
	inline ULONG G(ULONG x,ULONG y,ULONG z);
	inline ULONG H(ULONG x,ULONG y,ULONG z);
	inline ULONG I(ULONG x,ULONG y,ULONG z);
	inline void FF(ULONG &a,ULONG b,ULONG c,ULONG d,ULONG Msg,int nBit,ULONG Cnt);
	inline void GG(ULONG &a,ULONG b,ULONG c,ULONG d,ULONG Msg,int nBit,ULONG Cnt);
	inline void HH(ULONG &a,ULONG b,ULONG c,ULONG d,ULONG Msg,int nBit,ULONG Cnt);
	inline void II(ULONG &a,ULONG b,ULONG c,ULONG d,ULONG Msg,int nBit,ULONG Cnt);
private:
	bool Init();
	bool OpenFile();
	bool Read64Byte();
	void TransForm();
	bool CaculateFile();
	bool CaculateStr(LPCSTR str);
	void SetErr(int nErr);
	void JustifytoStr();
protected:
	fstream Sfile;
	ULONG *pM;
	LPVOID Pointer;
	ULONG T[4];
	bool IsSuc;
	char fname[MAX_PATH];
	LONG64 FileLen;
	static const ULONG Context[4];
	static const LPSTR ErrInfo[5][2];
	char strErr[50];
	char Digest[33];
};

#endif
