#include "StdAfx.h"
#include "MandoFinalSFR.h"
#include "PcsUtil.h"		// 20140912 추가

#include <io.h>

unsigned char originBMP[1300 * 1000 * 3];		//CM_Grabber에서는 1280 * 960
unsigned char bufferBMP[1300 * 1000 * 3];
unsigned char resultBMP[1300 * 1000 * 3];

//#ifndef _SVIP
//extern CVision vision;
//extern MandoInspLog		MandoInspLog;
//extern CModelData		model;
//extern CWork			work;
//extern CMandoSfrSpec	MandoSfrSpec;
//extern CSystemData		sysData;
//extern CMESCommunication	MESCommunication;
//#endif

CMandoFinalSFR::CMandoFinalSFR(void)
{
	m_imgBuf8 = NULL;
}


CMandoFinalSFR::~CMandoFinalSFR(void)
{
	SAFE_DELETE(m_imgBuf8);
}

int CMandoFinalSFR::func_check_MandoSFR_Final(IplImage* img, unsigned char* imgBuf12, CString ResultPath, bool bMTFRelsultReg, bool bAutoMode, bool bUvTiming)
{//bMTFRelsultReg => MTF 판정 포함 여부 선택 (T:판정 포함, F:미포함)
 // 20141120 LHC - 마지막인자값 bUvTiming 추가 (T:UV전, F:UV후)
	int error = 0;

	return error;

}


int CMandoFinalSFR::func_check_MandoSFR_Final_Quad(IplImage* img, unsigned char* imgBuf12, CString ResultPath, bool bMTFRelsultReg, bool bAutoMode, bool bUvTiming)
{//bMTFRelsultReg => MTF 판정 포함 여부 선택 (T:판정 포함, F:미포함)
 // 20141120 LHC - 마지막인자값 bUvTiming 추가 (T:UV전, F:UV후)

	return 1;
}

BOOL CMandoFinalSFR::SaveImageToBmp(char *path, unsigned char* bmp_buffer, __int16 width, __int16 height)
{
	int		OffBits;
	HFILE	bmpFile;
	BITMAPFILEHEADER bmpHeader; //Header for Bitmap file
	BITMAPINFO		 bmpInfo;

	OffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	DWORD dwSizeImage = width*height * 3;

	bmpHeader.bfType = ((WORD)('M' << 8) | 'B');
	bmpHeader.bfSize = OffBits + dwSizeImage;
	bmpHeader.bfReserved1 = 0;
	bmpHeader.bfReserved2 = 0;
	bmpHeader.bfOffBits = OffBits;

	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;
	bmpInfo.bmiHeader.biXPelsPerMeter = 0;
	bmpInfo.bmiHeader.biYPelsPerMeter = 0;
	bmpInfo.bmiHeader.biClrUsed = 0;
	bmpInfo.bmiHeader.biClrImportant = 0;

	bmpFile = _lcreat(path, 0);
	if (bmpFile < 0) return FALSE;

	UINT len;
	len = _lwrite(bmpFile, (LPSTR)&bmpHeader, sizeof(BITMAPFILEHEADER));
	len = _lwrite(bmpFile, (LPSTR)&bmpInfo, sizeof(BITMAPINFOHEADER));
	len = _lwrite(bmpFile, (LPSTR)bmp_buffer, bmpHeader.bfSize - sizeof(bmpHeader) - sizeof(bmpInfo) + 4);  //+4 is for exact filesize
	_lclose(bmpFile);

	return TRUE;
}



void CMandoFinalSFR::MarkRectangleOnBMPimage(unsigned char *data, int w, int h, int cx, int cy, int side_length_x, int side_length_y, int R, int G, int B)
{//이미지에 이물 위치 그리기
	int x, y;
	int l, t, r, b;
	l = cx - side_length_x / 2; if (l<0) l = 0;
	r = cx + side_length_x / 2; if (r>w - 1) r = w - 1;
	t = cy - side_length_y / 2; if (t<0) t = 0;
	b = cy + side_length_y / 2; if (b>h - 1) b = h - 1;

	for (y = t; y<b; y++)
	{
		x = l;
		data[(h - y - 1)*w * 3 + (x) * 3 + 0] = B;
		data[(h - y - 1)*w * 3 + (x) * 3 + 1] = G;
		data[(h - y - 1)*w * 3 + (x) * 3 + 2] = R;
		x = r;
		data[(h - y - 1)*w * 3 + (x) * 3 + 0] = B;
		data[(h - y - 1)*w * 3 + (x) * 3 + 1] = G;
		data[(h - y - 1)*w * 3 + (x) * 3 + 2] = R;

	}


	for (x = l; x<r; x++)
	{
		y = t;
		data[(h - y - 1)*w * 3 + (x) * 3 + 0] = B;
		data[(h - y - 1)*w * 3 + (x) * 3 + 1] = G;
		data[(h - y - 1)*w * 3 + (x) * 3 + 2] = R;
		y = b;
		data[(h - y - 1)*w * 3 + (x) * 3 + 0] = B;
		data[(h - y - 1)*w * 3 + (x) * 3 + 1] = G;
		data[(h - y - 1)*w * 3 + (x) * 3 + 2] = R;
	}
}

void CMandoFinalSFR::ImageFlip(unsigned char* source, unsigned char* target, int width, int height)
{
	int x, y;
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width * 3; x++)
		{
			target[y*width * 3 + x] = source[(height - y - 1)*width * 3 + x];
		}
	}
}

CString CMandoFinalSFR::SetDir_Check(CString sPath)
{
	CString sRtn, FolderName;
	CFileFind finder;
	BOOL IsFind;

	SYSTEMTIME time;
	::GetLocalTime(&time);

	FolderName.Format("%s\\%04d%02d", sPath, time.wYear, time.wMonth);
	IsFind = finder.FindFile(FolderName);
	if (!IsFind)
	{
		CreateDirectory(FolderName, NULL);
	}

	sRtn.Format("%s\\%04d%02d\\%02d", sPath, time.wYear, time.wMonth, time.wDay);
	IsFind = finder.FindFile(sRtn);
	if (!IsFind)
	{
		CreateDirectory(sRtn, NULL);
	}

	sRtn.Format("%s\\%04d%02d\\%02d\\", sPath, time.wYear, time.wMonth, time.wDay);

	return sRtn;
}

void CMandoFinalSFR::PRI_12BitToRaw8(unsigned char *p12Bit, unsigned char *pRawBit8, int w, int h)	// 1280 x 964 12bit -> 1280 x 960 8bit
{
	/*int x, y, m_iWidth = w, m_iHeight = h;

	for (y=0; y<m_iHeight; y++)
	{
	for (x=0; x<m_iWidth/2; x=x++)
	{
	pRawBit8[y*m_iWidth + x*2]	 = (p12Bit[(y+2)*m_iWidth*2 + 4*x+0]);
	pRawBit8[y*m_iWidth + x*2+1] = (p12Bit[(y+2)*m_iWidth*2 + 4*x+2]);
	}
	}*/


	int		x, y, m_iWidth = w, m_iHeight = h;

	for (y = 0; y<h; y++)
	{

		for (x = 0; x<m_iWidth / 2; x = x++)
		{
			pRawBit8[y*m_iWidth + x * 2] = (p12Bit[y*m_iWidth * 2 + 4 * x + 0]);
			pRawBit8[y*m_iWidth + x * 2 + 1] = (p12Bit[y*m_iWidth * 2 + 4 * x + 2]);
		}
	}
}

void CMandoFinalSFR::RawToBmpQuater(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height, int ch)
{
	int i, j, sx = 0, sy = 0;

	if (ch == 0)		sx = 0, sy = 0;
	else if (ch == 1)		sx = 1, sy = 0;
	else if (ch == 2)		sx = 0, sy = 1;
	else if (ch == 3)		sx = 1, sy = 1;

	for (j = sy; j<image_height; j += 2)
	{
		for (i = sx; i<image_width; i += 2)
		{
			*pBMP++ = pRaw8[(image_height - j - 1)*image_width + i];
			*pBMP++ = pRaw8[(image_height - j - 1)*image_width + i];
			*pBMP++ = pRaw8[(image_height - j - 1)*image_width + i];
		}
	}
}


void CMandoFinalSFR::unpackRaw12(const unsigned char *src, unsigned short *dst, int rows, int cols)
{
	int nByteWidth = cols * 3 / 2;

    //if(nByteWidth  % 4)
	//      nByteWidth  += 2;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j += 2)
		{
			dst[i * cols + j + 0] = (((unsigned short)src[i * nByteWidth + (j * 3 / 2) + 0] << 4) | ((unsigned short)(src[i * nByteWidth + (j * 3 / 2) + 2] & 0xF0) >> 4));
			dst[i * cols + j + 1] = (((unsigned short)src[i * nByteWidth + (j * 3 / 2) + 1] << 4) | ((unsigned short)(src[i * nByteWidth + (j * 3 / 2) + 2] & 0x0F) >> 0));
        }
	}
}

void CMandoFinalSFR::Raw12to8(unsigned short *pBuffer, unsigned char *pBuf, int rows, int cols)
{
	for (int i = 0; i < rows * cols; i++)
	{
		pBuf[i] = (pBuffer[i] & 0x0FF0) >> 4;
    }
}

void CMandoFinalSFR::RawToBmpQuater2(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height, int ch)
{
	 int i, j, sx = 0, sy = 0;

     if (ch == 0)           sx = 0, sy = 0;
     else if (ch == 1)      sx = 1, sy = 0;
     else if (ch == 2)      sx = 0, sy = 1;
     else if (ch == 3)      sx = 1, sy = 1;

     for (j = sy; j < image_height; j += 2)
     {
		 for (i = sx; i < image_width; i += 2)
         {
			 *pBMP++ = pRaw8[(image_height - j - 1)*image_width + i];
             *pBMP++ = pRaw8[(image_height - j - 1)*image_width + i];
             *pBMP++ = pRaw8[(image_height - j - 1)*image_width + i];
         }
	}
}