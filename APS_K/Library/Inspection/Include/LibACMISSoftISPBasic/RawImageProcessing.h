#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>

namespace ACMISSoftISP
{
	ACMISSOFTISPBASIC_API void MeanImage(
		const BYTE *image, BYTE *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImage2Byte(
		const unsigned short *image, unsigned short *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImage4Byte(
		const int *image, int *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageFloat(
		const BYTE *image, float *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageFloat2Byte(
		const unsigned short *image, float *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageFloat4Byte(
		const int *image, float *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageDouble(
		const BYTE *image, double *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageDouble2Byte(
		const unsigned short *image, double *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);
	ACMISSOFTISPBASIC_API void MeanImageDouble4Byte(
		const int *image, double *dest, int width, int height, int WindowSize, 
		int startX = 0, int startY = 0, int endX = 0, int endY = 0);

	ACMISSOFTISPBASIC_API double CalculateBlockAverage(
		const BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT rtROI);
	ACMISSOFTISPBASIC_API double CalculateBlockAverage(
		const unsigned short* pBuffer, int nImageWidth, int nImageHeight, RECT rtROI);
	ACMISSOFTISPBASIC_API double CalculateBlockAverage(
		const int* pBuffer, int nImageWidth, int nImageHeight, RECT rtROI);
	ACMISSOFTISPBASIC_API double CalculateBlockAverage(
		const BYTE* pBuffer, int nWidth, int nHeight, int nBlockWidth, int nBlockHeight, 
		int nStartX, int nStartY, const TInspectRegionOffset& tRegionOffset = { 0, 0, 0, 0 });
	ACMISSOFTISPBASIC_API double CalculateBlockAverage(
		const unsigned short* pBuffer, int nWidth, int nHeight, int nBlockWidth, int nBlockHeight, 
		int nStartX, int nStartY, const TInspectRegionOffset& tRegionOffset = { 0, 0, 0, 0 });
	ACMISSOFTISPBASIC_API double CalculateBlockAverage(
		const int* pBuffer, int nWidth, int nHeight, int nBlockWidth, int nBlockHeight, 
		int nStartX, int nStartY, const TInspectRegionOffset& tRegionOffset = { 0, 0, 0, 0 });

	ACMISSOFTISPBASIC_API void LensShadingCorrection(
		const BYTE *pixel, BYTE *DestPixel, int MeanBlockSize, int width, int height, 
		int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API void LensShadingCorrection(
		const unsigned short *pixel, unsigned short *DestPixel, int MeanBlockSize, int width, int height, 
		int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);
	ACMISSOFTISPBASIC_API void LensShadingCorrection(
		const int *pixel, int *DestPixel, int MeanBlockSize, int width, int height, EDATAFORMAT eDataFormat, 
		int nStartOffsetX = 0, int nStartOffsetY = 0, int nEndOffsetX = 0, int nEndOffsetY = 0);

	ACMISSOFTISPBASIC_API float FindMaxIntensity(float* image, int width, int height, RECT roi);
	ACMISSOFTISPBASIC_API float FindMaxIntensity(float* image, int width, int height, RECT roi, int& posX, int& posY);

	ACMISSOFTISPBASIC_API CBlobList MakeBlobList(
		BYTE* image, int width, int height, int minTh, int maxTh, int minArea, 
		const TInspectRegionOffset& tRegionOffset = { 0, 0, 0, 0 });

	ACMISSOFTISPBASIC_API int CalcAvgSdv(BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(short *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(unsigned short *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(int *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(float *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(double *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISPBASIC_API int CalcAvgSdv(void *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType, int Variable_Type);
	ACMISSOFTISPBASIC_API bool AverageImage(BYTE **pBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec, int nImageCount, BYTE *pDstBuffer);
	ACMISSOFTISPBASIC_API bool GetIRImage(const BYTE **pSrcBuffer, int nImageWidth, int nImageHeight, TDATASPEC tDataSpec, BYTE *pDstBuffer);
	ACMISSOFTISPBASIC_API void MakeGammaLUT(EDATAFORMAT eDataFormat, double dGamma, std::vector<double>& vGamma);
	ACMISSOFTISPBASIC_API void MakeGammaLUT(EDATAFORMAT eDataFormat, double m_dGamma, std::vector<unsigned short> &m_vGamma);
	ACMISSOFTISPBASIC_API void MakeGammaLUT(EDATAFORMAT eDataFormat, double m_dGamma, std::vector<int> &m_vGamma);

	ACMISSOFTISPBASIC_API bool xMakeCompPWLLUT(int nSizeLut, int nSizeInOut, long * pLutX, long * pLutY);
	ACMISSOFTISPBASIC_API long* xGetCompPWLLUTData();
	ACMISSOFTISPBASIC_API long xGetCompPWLLUTDataSize();
	ACMISSOFTISPBASIC_API void xClearCompPWLLUTData();
	ACMISSOFTISPBASIC_API bool xMakeDecompPWLLUT(int nSizeLut, int nSizeInOut, long * pLutX, long * pLutY);
	ACMISSOFTISPBASIC_API long* xGetDecompPWLLUTData();
	ACMISSOFTISPBASIC_API long xGetDecompPWLLUTDataSize();
	ACMISSOFTISPBASIC_API void xClearDecompPWLLUTData();
};
