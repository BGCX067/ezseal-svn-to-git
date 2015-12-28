// DIB.h

#ifndef __DIB_H__
#define __DIB_H__
#include "StdAfx.h"
#include <complex>

class CDib
{

public:
	CDib();
	~CDib();

	BOOL Draw( CDC *pDC, int nX = -1, int nY = -1, int nWidth = -1, int nHeight = -1, int Style = 1);
	BOOL Save( const char *pszFilename );
	BOOL Load( const char * );

//	bool Valid;
public:
	int m_BitCount;
	WORD * m_pWordData;
	CPalette m_Palette;
	unsigned char *m_pDib, *m_pDibBits;
	unsigned char *m_pOldDibShow;
	DWORD m_dwDibSize;
	BITMAPINFOHEADER *m_pBIH;
	RGBQUAD *m_pPalette;
	int m_nPaletteEntries;

public:
	void BackUpDib();
	void Pick();
	void Embed();
	BOOL LoadEmbFile(const char *);
	BOOL DrawContrast(CDC *pDC,int rect_width, int rect_height);

	UINT bitmap_size;
	UINT embfile_size;
	unsigned char *p;//ָ������ͼ������
	int tag;  //��tag���Ա�Ǵ򿪵�ͼ�����Ƿ���������Ϣ0���� else����
	unsigned char *q;//ָ�������ļ�����
	unsigned char *m_pFile;

	void SavePicked( const char *pszFilename );
};

#endif
