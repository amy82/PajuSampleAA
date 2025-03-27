#pragma once

#include "export.h"
#include "../LibACMISCommon\ACMISCommon.h"

//#ifndef max
//#define max(a, b)            (((a) > (b)) ? (a) : (b))
//#endif
//
//#ifndef min
//#define min(a, b)            (((a) < (b)) ? (a) : (b))
//#endif

// RGB -> YCbCr422
#define RGB2Y(R, G, B)  (BYTE)CLIP(((1053 * (R) + 2064 * (G) +  401 * (B) + 128) >> 12) +  16, 0, 255) //  0.257 * R + 0.504 * G + 0.098 * B + 16
#define RGB2Cb(R, G, B) (BYTE)CLIP(((-606 * (R) - 1192 * (G) + 1798 * (B) + 128) >> 12) + 128, 0, 255) // -0.148 * R - 0.291 * G + 0.439 * B + 128
#define RGB2Cr(R, G, B) (BYTE)CLIP(((1798 * (R) - 1507 * (G) -  291 * (B) + 128) >> 12) + 128, 0, 255) //  0.439 * R - 0.368 * G + 0.071 * B + 128

// YCbCr422 -> RGB
#define YCbCr2R(Y, Cb, Cr) (BYTE)CLIP(((4768 * (Y - 16) + 6537 * (Cr - 128)) >> 12), 0, 255);					  // 1.164 * (Y - 16) + 1.596 * (Cr - 128)
#define YCbCr2G(Y, Cb, Cr) (BYTE)CLIP(((4768 * (Y - 16) - 3330 * (Cr - 128) - 1602 * (Cb - 128)) >> 12), 0, 255); // 1.164 * (Y - 16) - 0.813 * (Cr - 128) - 0.391 * (Cb - 128)
#define YCbCr2B(Y, Cb, Cr) (BYTE)CLIP(((4768 * (Y - 16) + 8266 * (Cb - 128)) >> 12), 0, 255);					  // 1.164 * (Y - 16) + 2.018 * (Cb - 128)

namespace ACMISSoftISP
{
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										short* p2ByteBuffer, BYTE* p8BitBuffer, short* pY12BitBuffer, BYTE* pYBuffer);

	ACMISSOFTISP_API void xUnpacked10bitBuffer(const short* p10BitBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight);
	ACMISSOFTISP_API void xUnpacked12bitBuffer(const short* p12BitBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight);
	ACMISSOFTISP_API void xUnpacked2byteBuffer(const short* p2ByteBuffer, BYTE* pOrgBuffer, int nWidth, int nHeight);
	ACMISSOFTISP_API void xPacked10bitBuffer(short* p10BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel);
	ACMISSOFTISP_API void xPacked12bitBuffer(short* p12BitBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel); // CSI-2 Standard
	ACMISSOFTISP_API void xPacked2byteBuffer(short* p2ByteBuffer, const BYTE* pOrgBuffer, int nWidth, int nHeight, int nBlackLevel, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISP_API void xMake10to8Buffer(BYTE* p8BitBuffer, const short* p10bitBuffer, int nWidth, int nHeight);
	ACMISSOFTISP_API void xMake12to8Buffer(BYTE* p8BitBuffer, const short* p12bitBuffer, int nWidth, int nHeight);

	// Y = 0.2990*R + 0.5870*G + 0.1140*B;
	ACMISSOFTISP_API void xBMPtoY(BYTE* pY, const BYTE* pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xBMPtoY(SHORT* pY, const SHORT* pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, BYTE* pBMP, int nImageWidth, int nImageHeight, TDATASPEC& tDataSpec);

	ACMISSOFTISP_API void xYUV422toY(EOUTMODE eOutMode, BYTE* pY, SHORT* pY12Bit, const BYTE* pYUV, int nWidth, int nHeight);

	ACMISSOFTISP_API void xInterpolationCCCC(EOUTMODE eFormat, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolation2ByteCCCC(EOUTMODE eFormat, SHORT *pRaw, SHORT *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolationRCCC(EOUTMODE eFormat, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolation2ByteRCCC(EOUTMODE eFormat, SHORT *pRaw, SHORT *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolationRCCB(EOUTMODE eFormat, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolation2ByteRCCB(EOUTMODE eFormat, SHORT *pRaw, SHORT *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolationRGGB(EOUTMODE eFormat, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolation2ByteRGGB(EOUTMODE eFormat, SHORT *pRaw, SHORT *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolation3x3bilinear(EOUTMODE eFormat, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight);
	ACMISSOFTISP_API void xInterpolationWithOpenCV(EOUTMODE eFormat, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight);

	ACMISSOFTISP_API bool xMeanBayerData(const BYTE* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);
	ACMISSOFTISP_API bool xMean2ByteBayerData(const SHORT* pRaw, int nWidth, int nHeight, RECT& rtROI, double* pdMeanData);

	// YCbCr 422 to RGB
	ACMISSOFTISP_API void xYCbCrSD422toRGB(EOUTMODE eOutMode, const BYTE *pYuvBuffer, BYTE *pBmpBuffer, int size_x, int size_y);
	ACMISSOFTISP_API void xRGBtoYCbCrSD422(EOUTMODE eOutMode, const BYTE *pBmpBuffer, BYTE *pYuvBuffer, int size_x, int size_y);

	// Y Table
	ACMISSOFTISP_API void xMakeYLookupTable();
	ACMISSOFTISP_API BYTE xGetY(BYTE r, BYTE g, BYTE b);

	// Lens Shading Correction
	ACMISSOFTISP_API void xCreateLensShadingCorrectionGainTable(int nImageWidth, int nImageHeight, int nScaleLevel, double dGain);
	ACMISSOFTISP_API void xLensShadingCorrection(BYTE* pRaw, int nImageWidth, int nImageHeight, int nScaleLevel);

	ACMISSOFTISP_API void xBMPtoRAW(BYTE* pRAW, const BYTE* pBMP, int nWidth, int nHeight); // BGR -> RAW
	ACMISSOFTISP_API void xPNGtoRAW(BYTE* pRAW, const BYTE* pPNG, int nWidth, int nHeight); // PNG -> RAW
};



