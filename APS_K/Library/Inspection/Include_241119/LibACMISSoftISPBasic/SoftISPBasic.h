#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>


//#ifndef max
//#define max(a, b)            (((a) > (b)) ? (a) : (b))
//#endif
//
//#ifndef min
//#define min(a, b)            (((a) < (b)) ? (a) : (b))
//#endif

// RGB -> YUV (ITU-R BT.601)
//#define RGB2L(R, G, B) (BYTE)CLIP(((1053.0 * (R) + 2064.0 * (G) +  401.0 * (B) + 2048.0) / 4096.0) +  16, 0, 255) //  0.257 * R + 0.504 * G + 0.098 * B + 16
//#define RGB2U(R, G, B) (BYTE)CLIP(((-606.0 * (R) - 1192.0 * (G) + 1798.0 * (B) + 2048.0) / 4096.0) + 128, 0, 255) // -0.148 * R - 0.291 * G + 0.439 * B + 128
//#define RGB2V(R, G, B) (BYTE)CLIP(((1798.0 * (R) - 1507.0 * (G) -  291.0 * (B) + 2048.0) / 4096.0) + 128, 0, 255) //  0.439 * R - 0.368 * G + 0.071 * B + 128
#define RGB2L(R, G, B) (BYTE)CLIP(( 299 * R + 587 * G + 114 * B + 500) / 1000      , 0, 255)
#define RGB2U(R, G, B) (BYTE)CLIP((-147 * R - 289 * G + 436 * B + 500) / 1000 + 128, 0, 255)
#define RGB2V(R, G, B) (BYTE)CLIP(( 615 * R - 515 * G - 100 * B + 500) / 1000 + 128, 0, 255)
#define RGB2L2(R, G, B, LL, UL) CLIP((int)( 299 * R + 587 * G + 114 * B + 500) / 1000      , LL, UL)
#define RGB2U2(R, G, B, LL, UL) CLIP((int)(-147 * R - 289 * G + 436 * B + 500) / 1000 + 128, LL, UL)
#define RGB2V2(R, G, B, LL, UL) CLIP((int)( 615 * R - 515 * G - 100 * B + 500) / 1000 + 128, LL, UL)

// YUV -> RGB (ITU-R BT.601)
//#define YUV2R(Y, U, V) (BYTE)CLIP(((4768.0 * (Y - 16.0) + 6537.0 * (V - 128.0) + 2048.0) / 4096.0), 0, 255);						// 1.164 * (Y - 16) + 1.596 * (V - 128)
//#define YUV2G(Y, U, V) (BYTE)CLIP(((4768.0 * (Y - 16.0) - 3330.0 * (V - 128.0) - 1602.0 * (U - 128.0) + 2048.0) / 4096.0), 0, 255); // 1.164 * (Y - 16) - 0.813 * (V - 128) - 0.391 * (U - 128)
//#define YUV2B(Y, U, V) (BYTE)CLIP(((4768.0 * (Y - 16.0) + 8266.0 * (U - 128.0) + 2048.0) / 4096.0), 0, 255);						// 1.164 * (Y - 16) + 2.018 * (U - 128)
#define YUV2R(Y, U, V) (BYTE)CLIP((Y + 1.371 * (V - 128.0) + 0.5), 0, 255);
#define YUV2G(Y, U, V) (BYTE)CLIP((Y - 0.698 * (V - 128.0) - 0.338 * (U - 128.0) + 0.5), 0, 255);
#define YUV2B(Y, U, V) (BYTE)CLIP((Y + 1.732 * (U - 128.0) + 0.5), 0, 255);
#define YUV2R2(Y, U, V, LL, UL) CLIP((int)(Y + 1.371 * (V - 128.0) + 0.5), LL, UL);
#define YUV2G2(Y, U, V, LL, UL) CLIP((int)(Y - 0.698 * (V - 128.0) - 0.338 * (U - 128.0) + 0.5), LL, UL);
#define YUV2B2(Y, U, V, LL, UL) CLIP((int)(Y + 1.732 * (U - 128.0) + 0.5), LL, UL);

// RGB -> YCbCr (ITU-R BT.601)
//#define RGB2Y(R, G, B)  (BYTE)CLIP(((1225.0 * (R) + 2404.0 * (G) +  467.0 * (B)) / 4096.0), 0, 255)       //  0.299 * R + 0.587 * G + 0.114 * B
//#define RGB2Cb(R, G, B) (BYTE)CLIP(((-692.0 * (R) - 1356.0 * (G) + 2044.0 * (B)) / 4096.0) + 128, 0, 255) // -0.169 * R - 0.331 * G + 0.500 * B + 128
//#define RGB2Cr(R, G, B) (BYTE)CLIP(((2044.0 * (R) - 1712.0 * (G) -  333.0 * (B)) / 4096.0) + 128, 0, 255) //  0.500 * R - 0.419 * G + 0.081 * B + 128
#define RGB2Y(R, G, B)  (BYTE)CLIP(( 299 * R + 587 * G + 114 * B + 500) / 1000      , 0, 255)
#define RGB2Cb(R, G, B) (BYTE)CLIP((-169 * R - 331 * G + 500 * B + 500) / 1000 + 128, 0, 255)
#define RGB2Cr(R, G, B) (BYTE)CLIP(( 500 * R - 419 * G -  81 * B + 500) / 1000 + 128, 0, 255)
#define RGB2Y2(R, G, B, LL, UL)  CLIP((int)( 299 * R + 587 * G + 114 * B + 500) / 1000      , LL, UL)
#define RGB2Cb2(R, G, B, LL, UL) CLIP((int)(-169 * R - 331 * G + 500 * B + 500) / 1000 + 128, LL, UL)
#define RGB2Cr2(R, G, B, LL, UL) CLIP((int)( 500 * R - 419 * G - 081 * B + 500) / 1000 + 128, LL, UL)

// YCbCr -> RGB (ITU-R BT.601)
//#define YCbCr2R(Y, Cb, Cr) (BYTE)CLIP(((4096.0 * Y + 5614.0 * (Cr - 128.0)) / 4096.0), 0, 255)							// Y + 1.370705 * (Cr - 128)
//#define YCbCr2G(Y, Cb, Cr) (BYTE)CLIP(((4096.0 * Y - 2859.0 * (Cr - 128.0) - 1383.0 * (Cb - 128.0)) / 4096.0), 0, 255)	// Y - 0.698001 * (Cr - 128) - 0.337633 * (Cb - 128)
//#define YCbCr2B(Y, Cb, Cr) (BYTE)CLIP(((4096.0 * Y + 7096.0 * (Cb - 128.0)) / 4096.0), 0, 255)							// Y + 1.732446 * (Cb - 128)
#define YCbCr2R(Y, Cb, Cr) (BYTE)CLIP((Y + 1.402 * (Cr - 128.0) + 0.5), 0, 255)
#define YCbCr2G(Y, Cb, Cr) (BYTE)CLIP((Y - 0.714 * (Cr - 128.0) - 0.344 * (Cb - 128.0) + 0.5), 0, 255)
#define YCbCr2B(Y, Cb, Cr) (BYTE)CLIP((Y + 1.772 * (Cb - 128.0) + 0.5), 0, 255)
#define YCbCr2R2(Y, Cb, Cr, LL, UL) CLIP((int)(Y + 1.402 * (Cr - 128.0) + 0.5), LL, UL)
#define YCbCr2G2(Y, Cb, Cr, LL, UL) CLIP((int)(Y - 0.714 * (Cr - 128.0) - 0.344 * (Cb - 128.0) + 0.5), LL, UL)
#define YCbCr2B2(Y, Cb, Cr, LL, UL) CLIP((int)(Y + 1.772 * (Cb - 128.0) + 0.5), LL, UL)

// RGB -> Y (ITU-R BT.709)
#define RGB2YI(R, G, B) (BYTE)CLIP((2125 * R + 7154 * G +  721 * B + 5000) / 10000, 0, 255)
#define RGB2YI2(R, G, B, LL, UL) CLIP((int)(2125 * R + 7154 * G +  721 * B + 5000) / 10000, LL, UL)

typedef enum _ACMIS_DLL_TYPE
{
	DLL_ACMISImage,
	DLL_ACMISResolution,
	DLL_ACMISShading,
	DLL_ACMISSoftISP,
	DLL_ACMISParallelInspection
} ACMIS_DLL_TYPE;

namespace ACMISSoftISP
{
	ACMISSOFTISPBASIC_API bool xChangeFormatBasic(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										unsigned short* p2ByteBuffer, BYTE* p8BitBuffer, unsigned short* pY12BitBuffer, BYTE* pYBuffer);
	ACMISSOFTISPBASIC_API bool xChangeFormatBasic(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										unsigned short* p2ByteBuffer, BYTE* p8BitBuffer, unsigned short* pY12BitBuffer, BYTE* pYBuffer, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API bool xChangeFormatBasic(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										short* p2ByteBuffer, BYTE* p8BitBuffer, short* pY12BitBuffer, BYTE* pYBuffer);
	ACMISSOFTISPBASIC_API bool xChangeFormatBasic(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										short* p2ByteBuffer, BYTE* p8BitBuffer, short* pY12BitBuffer, BYTE* pYBuffer, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API bool xChangeFormatBasic(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight, int* pBuffer, int* pYBuffer);
	ACMISSOFTISPBASIC_API bool xChangeFormatBasic(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight, int* pBuffer, int* pYBuffer, RECT *pROI, int nROICount);

	ACMISSOFTISPBASIC_API void xUnpacked10bitBuffer(const unsigned short* p10BitBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked10bitBuffer(const int* p10BitBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked12bitBuffer(const unsigned short* p12BitBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked12bitBuffer(const int* p12BitBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked2byteBuffer(const unsigned short* p2ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xUnpacked2byteBuffer(const int* p2ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xUnpacked2byteBufferBE(const unsigned short* p2ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked2byteBufferBE(const int* p2ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked3byteBuffer(const int* p3ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xUnpacked3byteBufferBE(const int* p3ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel = 0);
	ACMISSOFTISPBASIC_API void xPacked10bitBuffer(unsigned short* p10BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel);
	ACMISSOFTISPBASIC_API void xPacked10bitBuffer(unsigned short* p10BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xPacked10bitBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel);
	ACMISSOFTISPBASIC_API void xPacked10bitBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xPacked12bitBuffer(unsigned short* p12BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel); // CSI-2 Standard
	ACMISSOFTISPBASIC_API void xPacked12bitBuffer(unsigned short* p12BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0); // CSI-2 Standard
	ACMISSOFTISPBASIC_API void xPacked12bitBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel);
	ACMISSOFTISPBASIC_API void xPacked12bitBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xPacked2byteBuffer(unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xPacked2byteBuffer(unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xPacked2byteBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xPacked2byteBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xPacked2byteBufferBE(unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_16BIT_BE);
	ACMISSOFTISPBASIC_API void xPacked2byteBufferBE(unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_16BIT_BE);
	ACMISSOFTISPBASIC_API void xPacked2byteBufferBE(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_16BIT_BE);
	ACMISSOFTISPBASIC_API void xPacked2byteBufferBE(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_16BIT_BE);
	ACMISSOFTISPBASIC_API void xPacked3byteBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel);
	ACMISSOFTISPBASIC_API void xPacked3byteBuffer(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xPacked3byteBufferBE(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel);
	ACMISSOFTISPBASIC_API void xPacked3byteBufferBE(int* pBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nBlackLevel, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake10to8Buffer(BYTE* p8BitBuffer, const unsigned short* p10bitBuffer, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xMake10to8Buffer(BYTE* p8BitBuffer, const unsigned short* p10bitBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake12to8Buffer(BYTE* p8BitBuffer, const unsigned short* p12bitBuffer, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xMake12to8Buffer(BYTE* p8BitBuffer, const unsigned short* p12bitBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake12to8Buffer(BYTE* p8BitBuffer, const short* p12bitBuffer, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xMake12to8Buffer(BYTE* p8BitBuffer, const short* p12bitBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake16to8Buffer(BYTE* p8BitBuffer, const unsigned short* p16bitBuffer, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xMake16to8Buffer(BYTE* p8BitBuffer, const unsigned short* p16bitBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake24to8Buffer(BYTE* p8BitBuffer, const int* pBuffer, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xMake24to8Buffer(BYTE* p8BitBuffer, const int* pBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake8bitBuffer(int* p8BitBuffer, const int* pBuffer, int nWidth, int nHeight, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xMake8bitBuffer(int* p8BitBuffer, const int* pBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake8bitBuffer(BYTE* p8BitBuffer, const int* pBuffer, int nWidth, int nHeight, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xMake8bitBuffer(BYTE* p8BitBuffer, const int* pBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMakePackedBuffer(BYTE* p8BitBuffer, unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec);
	ACMISSOFTISPBASIC_API void xMakePackedBuffer(BYTE* p8BitBuffer, unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC tDataSpec, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake8bitPackedBuffer(BYTE* p8BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec);
	ACMISSOFTISPBASIC_API void xMake8bitPackedBuffer(BYTE* p8BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC tDataSpec, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake16bitPackedBuffer(unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec);
	ACMISSOFTISPBASIC_API void xMake16bitPackedBuffer(unsigned short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC tDataSpec, int nMargin = 0);
	ACMISSOFTISPBASIC_API void xMake24bitPackedBuffer(int* p4ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec);
	ACMISSOFTISPBASIC_API void xMake24bitPackedBuffer(int* p4ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC tDataSpec, int nMargin = 0);

	// Y = 0.2990*R + 0.5870*G + 0.1140*B;
	ACMISSOFTISPBASIC_API void xBMPtoY(BYTE* pY, const BYTE* pBMP, int nWidth, int nHeight, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(BYTE* pY, const BYTE* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(unsigned short* pY, const unsigned short* pBMP, int nWidth, int nHeight, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(unsigned short* pY, const unsigned short* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(int* pY, const int* pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(int* pY, const int* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(int* pY, const BYTE* pBMP, int nWidth, int nHeight, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(int* pY, const BYTE* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(int* pY, const unsigned short* pBMP, int nWidth, int nHeight, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xBMPtoY(int* pY, const unsigned short* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode = OUTMODE_RGB_BGR);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(BYTE* pRaw, BYTE* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(BYTE* pRaw, BYTE* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(BYTE* pRaw, unsigned short* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(BYTE* pRaw, unsigned short* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(BYTE* pRaw, int* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(BYTE* pRaw, int* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(int* pRaw, int* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeBMPBasic(int* pRaw, int* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);

	ACMISSOFTISPBASIC_API void xMakeYBasic(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(BYTE* pRaw, unsigned short* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(BYTE* pRaw, unsigned short* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(BYTE* pRaw, int* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(BYTE* pRaw, int* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(int* pRaw, int* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYBasic(int* pRaw, int* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYWithPackedDataBasic(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYWithPackedDataBasic(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYWithPackedDataBasic(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYWithPackedDataBasic(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYWithPackedDataBasic(int* pRaw, int* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISPBASIC_API void xMakeYWithPackedDataBasic(int* pRaw, int* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);

	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, BYTE* pY, unsigned short* pY12Bit, const BYTE* pYUV, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, BYTE* pY, unsigned short* pY12Bit, const BYTE* pYUV, int nWidth, int nHeight, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, unsigned short* pY, const unsigned short* pYUV, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, unsigned short* pY, const unsigned short* pYUV, int nWidth, int nHeight, RECT* pROI, int nROICount);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, int* pY, const int* pYUV, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, int* pY, const int* pYUV, int nWidth, int nHeight, RECT* pROI, int nROICount);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, int* pY, const unsigned short* pYUV, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, int* pY, const unsigned short* pYUV, int nWidth, int nHeight, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, int* pY, const BYTE* pYUV, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void xYUV422toY(EOUTMODE eOutMode, int* pY, const BYTE* pYUV, int nWidth, int nHeight, RECT *pROI, int nROICount);

	ACMISSOFTISPBASIC_API bool xMedianBayerData(const BYTE* pRaw, int nWidth, int nHeight, RECT& rtROI, BYTE* pnMedianData);
	ACMISSOFTISPBASIC_API bool xMedian2ByteBayerData(const unsigned short* pRaw, int nWidth, int nHeight, RECT& rtROI, unsigned short* pnMedianData);
	ACMISSOFTISPBASIC_API bool xMedian4ByteBayerData(const int* pRaw, int nWidth, int nHeight, RECT& rtROI, int* pnMedianData);
	ACMISSOFTISPBASIC_API bool xMedianRGBData(const BYTE* pRaw, int nWidth, int nHeight, RECT& rtROI, BYTE* pnMedianData);
	ACMISSOFTISPBASIC_API bool xMedian2ByteRGBData(const unsigned short* pRaw, int nWidth, int nHeight, RECT& rtROI, unsigned short* pnMedianData);
	ACMISSOFTISPBASIC_API bool xMedian4ByteRGBData(const int* pRaw, int nWidth, int nHeight, RECT& rtROI, int* pnMedianData);

	ACMISSOFTISPBASIC_API bool xMeanBayerData(const BYTE* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);
	ACMISSOFTISPBASIC_API bool xMean2ByteBayerData(const unsigned short* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);
	ACMISSOFTISPBASIC_API bool xMean4ByteBayerData(const int* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);
	ACMISSOFTISPBASIC_API bool xMeanRGBData(const BYTE* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);
	ACMISSOFTISPBASIC_API bool xMean2ByteRGBData(const unsigned short* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);
	ACMISSOFTISPBASIC_API bool xMean4ByteRGBData(const int* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);

	ACMISSOFTISPBASIC_API bool xCalcColorRatio(const BYTE* pRaw, int nWidth, int nHeight, int nBayerOrder, int nTypicalValueType, RECT& rtROI, TColorRatio* pRatio);
	ACMISSOFTISPBASIC_API bool xCalcColorRatio(const unsigned short* pRaw, int nWidth, int nHeight, int nBayerOrder, int nTypicalValueType, RECT& rtROI, TColorRatio* pRatio);
	ACMISSOFTISPBASIC_API bool xCalcColorRatio(const int* pRaw, int nWidth, int nHeight, int nBayerOrder, int nTypicalValueType, RECT& rtROI, TColorRatio* pRatio);
	ACMISSOFTISPBASIC_API bool xCalcColorRatioRGB(const BYTE* pRaw, int nWidth, int nHeight, int nRGBOrder, int nTypicalValueType, RECT& rtROI, TColorRatio* pRatio);
	ACMISSOFTISPBASIC_API bool xCalcColorRatioRGB(const unsigned short* pRaw, int nWidth, int nHeight, int nRGBOrder, int nTypicalValueType, RECT& rtROI, TColorRatio* pRatio);
	ACMISSOFTISPBASIC_API bool xCalcColorRatioRGB(const int* pRaw, int nWidth, int nHeight, int nRGBOrder, int nTypicalValueType, RECT& rtROI, TColorRatio* pRatio);

	// YUV422 to RGB
	ACMISSOFTISPBASIC_API void xYUV422toRGB(EOUTMODE eOutMode, const BYTE* pYUVBuffer, BYTE* pBMPBuffer, int size_x, int size_y);
	ACMISSOFTISPBASIC_API void xYUV422toRGB(EOUTMODE eOutMode, const BYTE* pYUVBuffer, BYTE* pBMPBuffer, int size_x, int size_y, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API void xYUV422toRGB(EOUTMODE eOutMode, const unsigned short* pYUVBuffer, unsigned short* pBMPBuffer, int size_x, int size_y, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xYUV422toRGB(EOUTMODE eOutMode, const unsigned short* pYUVBuffer, unsigned short* pBMPBuffer, int size_x, int size_y, RECT* pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xYUV422toRGB(EOUTMODE eOutMode, const int* pYUVBuffer, int* pBMPBuffer, int size_x, int size_y, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xYUV422toRGB(EOUTMODE eOutMode, const int* pYUVBuffer, int* pBmpBuffer, int size_x, int size_y, RECT* pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xRGBtoYUV422(EOUTMODE eOutMode, const BYTE* pBMPBuffer, BYTE* pYUVBuffer, int size_x, int size_y);
	ACMISSOFTISPBASIC_API void xRGBtoYUV422(EOUTMODE eOutMode, const BYTE* pBMPBuffer, BYTE* pYUVBuffer, int size_x, int size_y, RECT *pROI, int nROICount);

	// YCbCr422 to RGB
	ACMISSOFTISPBASIC_API void xYCbCrSD422toRGB(EOUTMODE eOutMode, const BYTE* pYCbCrBuffer, BYTE* pBMPBuffer, int size_x, int size_y);
	ACMISSOFTISPBASIC_API void xYCbCrSD422toRGB(EOUTMODE eOutMode, const BYTE* pYCbCrBuffer, BYTE* pBMPBuffer, int size_x, int size_y, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API void xRGBtoYCbCrSD422(EOUTMODE eOutMode, const BYTE* pBMPBuffer, BYTE* pYCbCrBuffer, int size_x, int size_y);
	ACMISSOFTISPBASIC_API void xRGBtoYCbCrSD422(EOUTMODE eOutMode, const BYTE* pBMPBuffer, BYTE* pYCbCrBuffer, int size_x, int size_y, RECT *pROI, int nROICount);

	// Y Table
	ACMISSOFTISPBASIC_API void xMakeYLookupTable();
	ACMISSOFTISPBASIC_API BYTE xGetY(BYTE r, BYTE g, BYTE b);

	// Lens Shading Correction
	ACMISSOFTISPBASIC_API void xCreateLensShadingCorrectionGainTable(int nWidth, int nHeight, int nScaleLevel, double dGain);
	ACMISSOFTISPBASIC_API void xLensShadingCorrection(BYTE* pRaw, int nWidth, int nHeight, int nScaleLevel);

	ACMISSOFTISPBASIC_API bool GetDLLVersionInfo(char *LibName, unsigned short *versionInfo);
	ACMISSOFTISPBASIC_API bool GetDLLVersionInfo(ACMIS_DLL_TYPE LibName, unsigned short *versionInfo);

	ACMISSOFTISPBASIC_API void GetBuildTime(const char *FileName, char *strLastBuildDate, char *strLastBuildTime);

	ACMISSOFTISPBASIC_API void CheckVirtualMem(DWORDLONG &totalVirtualMem, DWORDLONG &virtualMemUsed, SIZE_T &virtualMemUsedByMe);
	ACMISSOFTISPBASIC_API void ACMISDebugString(const char * msg, ...);

	ACMISSOFTISPBASIC_API int GetMaxPixelBrightValue(EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void ConvertGray2RGB(int *pGray, int *pBMP, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void ConvertGray2RGB(unsigned short* pGray, unsigned short* pBMP, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void ConvertGray2RGB(BYTE* pGray, BYTE* pBMP, int nWidth, int nHeight);
	ACMISSOFTISPBASIC_API void ConvertGray2RGB(int *pGray, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount);
	ACMISSOFTISPBASIC_API void ConvertGray2RGB(unsigned short* pGray, unsigned short* pBMP, int nWidth, int nHeight, RECT* pROI, int nROICount);
	ACMISSOFTISPBASIC_API void ConvertGray2RGB(BYTE* pGray, BYTE* pBMP, int nWidth, int nHeight, RECT* pROI, int nROICount);

	ACMISSOFTISPBASIC_API bool CompenationMC(int nImageWidth, int nImageHeight, CDPoint ptCenter, double dRotation, std::vector<RECT>& vROI, std::vector<POINT>& vPoint, int isCompensateMC, int isCompensateRotate);
	ACMISSOFTISPBASIC_API bool CompenationMC(int nImageWidth, int nImageHeight, CDPoint ptCenter, double dRotation, TROIData& tROI, int isCompensateMC, int isCompensateRotate);
};



