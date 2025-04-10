#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>


namespace ACMISSoftISP
{
	ACMISSOFTISPBASIC_API void xInterpolation_RBCC(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RBCC(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RBCC(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RBCC(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RBCC(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RBCC(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_CCCC(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_CCCC(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_CCCC(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_CCCC(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_CCCC(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_CCCC(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_RCCC(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RCCC(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RCCC(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RCCC(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RCCC(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RCCC(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_RCCB(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RCCB(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RCCB(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RCCB(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RCCB(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RCCB(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_RGGB(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RGGB(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RGGB(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RGGB(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RGGB(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RGGB(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_BL33(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_BL33(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_BL33(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_BL33(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_BL33(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_BL33(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_VNG(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_VNG(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_VNG(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_VNG(EOUTMODE eOutMode, BYTE *pRaw, BYTE *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_VNG(EOUTMODE eOutMode, unsigned short *pRaw, unsigned short *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_VNG(EOUTMODE eOutMode, int *pRaw, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation_RBCC_Bay2Y(const BYTE* pBayer, BYTE* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RBCC_Bay2Y(const unsigned short* pBayer, unsigned short* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RBCC_Bay2Y(const int* pBayer, int* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RBCC_Bay2Y(const BYTE* pBayer, BYTE* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RBCC_Bay2Y(const unsigned short* pBayer, unsigned short* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RBCC_Bay2Y(const int* pBayer, int* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation_RCCC_Bay2Y(const BYTE* pBayer, BYTE* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RCCC_Bay2Y(const unsigned short* pBayer, unsigned short* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RCCC_Bay2Y(const int* pBayer, int* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RCCC_Bay2Y(const BYTE* pBayer, BYTE* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RCCC_Bay2Y(const unsigned short* pBayer, unsigned short* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RCCC_Bay2Y(const int* pBayer, int* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation_RCCB_Bay2Y(const BYTE* pBayer, BYTE* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_RCCB_Bay2Y(const unsigned short* pBayer, unsigned short* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_RCCB_Bay2Y(const int* pBayer, int* pY, int nWidth, int nHeight, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RCCB_Bay2Y(const BYTE* pBayer, BYTE* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RCCB_Bay2Y(const unsigned short* pBayer, unsigned short* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RCCB_Bay2Y(const int* pBayer, int* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI_RGGB_G_Interpolate(const BYTE* pBayer, BYTE* pRGB, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_RGGB_G_Interpolate(const unsigned short* pBayer, unsigned short* pRGB, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_RGGB_G_Interpolate(const int* pBayer, int* pRGB, int nWidth, int nHeight, RECT* pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	ACMISSOFTISPBASIC_API void xInterpolation_AHD(EOUTMODE eOutMode, BYTE* pRaw, BYTE* pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation2Byte_AHD(EOUTMODE eOutMode, unsigned short* pRaw, unsigned short* pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolation4Byte_AHD(EOUTMODE eOutMode, int* pRaw, int* pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI_AHD(EOUTMODE eOutMode, BYTE* pRaw, BYTE* pBMP, int nWidth, int nHeight, RECT* pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI2Byte_AHD(EOUTMODE eOutMode, unsigned short* pRaw, unsigned short* pBMP, int nWidth, int nHeight, RECT* pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISPBASIC_API void xInterpolationROI4Byte_AHD(EOUTMODE eOutMode, int* pRaw, int* pBMP, int nWidth, int nHeight, RECT* pROI, int nROICount, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
};



