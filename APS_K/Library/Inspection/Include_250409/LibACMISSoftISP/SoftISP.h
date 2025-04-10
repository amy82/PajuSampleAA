#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>


namespace ACMISSoftISP
{
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										unsigned short* p2ByteBuffer, BYTE* p8BitBuffer, unsigned short* pY12BitBuffer, BYTE* pYBuffer, double dGamma = 0.0);
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										unsigned short* p2ByteBuffer, BYTE* p8BitBuffer, unsigned short* pY12BitBuffer, BYTE* pYBuffer, RECT *pROI, int nROICount, double dGamma = 0.0);
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										short* p2ByteBuffer, BYTE* p8BitBuffer, short* pY12BitBuffer, BYTE* pYBuffer, double dGamma = 0.0);
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight,
										short* p2ByteBuffer, BYTE* p8BitBuffer, short* pY12BitBuffer, BYTE* pYBuffer, RECT *pROI, int nROICount, double dGamma = 0.0);
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight, int* pBuffer, int* pYBuffer);
	ACMISSOFTISP_API bool xChangeFormat(TDATASPEC &tDataSpec, const BYTE* pOrgBuffer, int nWidth, int nHeight, int* pBuffer, int* pYBuffer, RECT *pROI, int nROICount);

	// Y = 0.2990*R + 0.5870*G + 0.1140*B;
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, BYTE* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, BYTE* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, unsigned short* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, unsigned short* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, int* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeBMP(BYTE* pRaw, int* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeBMP(int* pRaw, int* pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeBMP(int* pRaw, int* pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);

	ACMISSOFTISP_API void xMakeY(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeY(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeY(BYTE* pRaw, unsigned short* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeY(BYTE* pRaw, unsigned short* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec, double dGamma = 0.0);
	ACMISSOFTISP_API void xMakeY(BYTE* pRaw, int* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeY(BYTE* pRaw, int* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeY(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeY(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeY(int* pRaw, int* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeY(int* pRaw, int* pY, int nWidth, int nHeight, RECT* pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeYWithPackedData(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeYWithPackedData(BYTE* pRaw, BYTE* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeYWithPackedData(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeYWithPackedData(unsigned short* pRaw, unsigned short* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeYWithPackedData(int* pRaw, int* pY, int nWidth, int nHeight, TDATASPEC& tDataSpec);
	ACMISSOFTISP_API void xMakeYWithPackedData(int* pRaw, int* pY, int nWidth, int nHeight, RECT *pROI, int nROICount, TDATASPEC& tDataSpec);

	ACMISSOFTISP_API void xBMPtoRAW(BYTE* pRAW, const BYTE* pBMP, int nWidth, int nHeight); // BGR -> RAW
	ACMISSOFTISP_API void xPNGtoRAW(BYTE* pRAW, const BYTE* pPNG, int nWidth, int nHeight); // PNG -> RAW

	ACMISSOFTISP_API void ConvertRGB2Lab(int* pBuffer, int nImageWidth, int nImageHeight, RECT rtROI, EDATAFORMAT eDataFormat, TColorLab& tLab);
	ACMISSOFTISP_API void ConvertGray2RGB(int *pGray, int *pBMP, int nWidth, int nHeight, EDATAFORMAT eDataFormat);
	ACMISSOFTISP_API void ConvertGray2RGB(int *pGray, int *pBMP, int nWidth, int nHeight, RECT *pROI, int nROICount, EDATAFORMAT eDataFormat);

	ACMISSOFTISP_API bool xSaturation(const BYTE* pBuffer, EDATAFORMAT eDataFormat, int nImageWidth, int nImageHeight, RECT rtROI, double dBinaryThreshold, double& dBrightAvg, ESaturationMethod eMethod = SaturationMethod_Y, BYTE* pMask = NULL);
	ACMISSOFTISP_API bool xSaturation(const unsigned short* pBuffer, EDATAFORMAT eDataFormat, int nImageWidth, int nImageHeight, RECT rtROI, double dBinaryThreshold, double& dBrightAvg, ESaturationMethod eMethod = SaturationMethod_Y, BYTE* pMask = NULL);
	ACMISSOFTISP_API bool xSaturation(const int* pBuffer, EDATAFORMAT eDataFormat, int nImageWidth, int nImageHeight, RECT rtROI, double dBinaryThreshold, double& dBrightAvg, ESaturationMethod eMethod = SaturationMethod_Y, BYTE* pMask = NULL);
	ACMISSOFTISP_API bool xSaturation(const int* pBuffer, const int* pFrameY, int nImageWidth, int nImageHeight, TDATASPEC tDataSpec, RECT rtROI, double dBinaryThreshold, double& dROIBrightMin, double& dROIBrightMax, double& dROIBrightAvg, POINT& ptMin, POINT& ptMax, int& nROIBrightMaxBin, int& nROIBrightMaxBinPixelCnt);
	ACMISSOFTISP_API bool xSaturationByPackedBayer(const int* pBuffer, TDATASPEC tDataSpec, int nImageWidth, int nImageHeight, RECT rtROI, double dBinaryThreshold, double& dBrightAvg, ESaturationMethod eMethod = SaturationMethod_Y, BYTE* pMask = NULL);

	ACMISSOFTISP_API void BayerSplit(void* Bayer, int bayerPattern, void* Dst);
	ACMISSOFTISP_API void AdjustBayerPattern(int bayerPattern, RECT rtROI, int& AdjustedBayerPattern);

	ACMISSOFTISP_API void CalcProject(POINT* inputPos1, POINT* inputPos2, int num, double* proMat);

	ACMISSOFTISP_API double CalcSFR4VNE(const BYTE* pBuffer, int nImageWidth, int nImageHeight, RECT& rtROI, int nEdgeDir, double dFreq, double dPixelSize, int eAlgorithmMethod);

	ACMISSOFTISP_API bool xMakeInspectImage(const TBufferInfo* pBufferInfo, TInspectRegionOffset& tInspectRegionOffset, int& nRealImageWidth, int& nRealImageHeight, RECT& rtRealImageROI, TROIData* pROI = nullptr, std::vector<int>* pIntBuffer = nullptr, std::vector<int>* pYBuffer = nullptr, std::vector<int>* pBMPBuffer = nullptr, bool isGOnly = false);
};
