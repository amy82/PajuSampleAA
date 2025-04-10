#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>

enum EFixedCircle
{
	FIXED_CIRCLE_DISABLED,
	FIXED_CIRCLE_HORIZONTAL_FIELD,
	FIXED_CIRCLE_MTM,	// no more used
	FIXED_CIRCLE_DIAGONAL_FIELD,
};

namespace ACMISSoftISP
{
	ACMISSOFTISP_API int xCalcImageRadius4Byte(
		const int* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat,
		int& ocx, int& ocy, int& radx, int& rady, double& angle); // using Y Image Only
	ACMISSOFTISP_API int xCalcImageRadius2Byte(
		const unsigned short* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat,
		int& ocx, int& ocy, int& radx, int& rady, double& angle); // using Y Image Only
	ACMISSOFTISP_API int xCalcImageRadius(
		const BYTE* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat,
		int& ocx, int& ocy, int& radx, int& rady, double& angle); // using Y Image Only

	ACMISSOFTISP_API int xCalcCenterCircleObject4Byte(int&ocx, int&ocy, const int* img, int w, int h); // using Y Image Only
	ACMISSOFTISP_API int xCalcCenterCircleObject2Byte(int&ocx, int&ocy, const unsigned short* img, int w, int h); // using Y Image Only
	ACMISSOFTISP_API int xCalcCenterCircleObject(int&ocx, int&ocy, const BYTE* img, int w, int h); // using Y Image Only

	ACMISSOFTISP_API void xCalcFixedCircleCenter4Byte(int&ocx, int&ocy, const int* img, int w, int h);
	ACMISSOFTISP_API void xCalcFixedCircleCenter2Byte(int&ocx, int&ocy, const unsigned short* img, int w, int h);
	ACMISSOFTISP_API void xCalcFixedCircleCenter(int&ocx, int&ocy, const BYTE* img, int w, int h);

	ACMISSOFTISP_API int xCalcCircleData4Byte(
		const int* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat,
		int &ocx, int &ocy, int &radx, int &rady, double &angle);
	ACMISSOFTISP_API int xCalcCircleData2Byte(
		const unsigned short* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat,
		int& ocx, int& ocy, int& radx, int& rady, double& angle);
	ACMISSOFTISP_API int xCalcCircleData(
		const BYTE* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat,
		int& ocx, int& ocy, int& radx, int& rady, double& angle);
	ACMISSOFTISP_API int xCalcCircleData4Byte(
		const int* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat, TCircleData& tCircleData);
	ACMISSOFTISP_API int xCalcCircleData2Byte(
		const unsigned short* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat, TCircleData& tCircleData);
	ACMISSOFTISP_API int xCalcCircleData(
		const BYTE* pImage, int width, int height, const TCircleSpecN& tSpec, EDATAFORMAT eDataFormat, TCircleData& tCircleData);
	ACMISSOFTISP_API int xGetCircleMask(int w, int h, TCircleSpecN& Spec, TCircleData& tCircleData, BYTE* pMask);

	ACMISSOFTISP_API bool DetectSqureVertexs(const BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT* inputROI, int num, POINT* outputPos);
	ACMISSOFTISP_API bool DetectPatchVertexs(const BYTE *pBuffer, int nImageWidth, int nImageHeight, TPatchInfo* tPatchInfo, int num, std::vector< std::vector<THarrisCornerPoint> >& outputPos);
	ACMISSOFTISP_API bool DetectPatchVertexsOpenCV(const BYTE* pBuffer, int nImageWidth, int nImageHeight, int nDataType, std::vector<TPatchInfo> vPatchInfo, std::vector<BYTE>& vMask, std::vector< std::vector<THarrisCornerPoint> >& outputPos, std::vector<TPatchSize>& vPatchSize);
#if 0
	ACMISSOFTISP_API bool DetectPatchVertexsOpenCV(const BYTE *pBuffer, int nImageWidth, int nImageHeight, TPatchInfo tPatchInfo, int nPatchIndex, std::vector<BYTE>& vMask, std::vector<THarrisCornerPoint>& outputPos, TPatchSize& tPatchSize);
#endif
	ACMISSOFTISP_API bool DetectCrossCenter(const BYTE *pBuffer, int nImageWidth, int nImageHeight, int nDataType, RECT* inputROI, int num, double dQualityLevel, POINT* outputPos); // default dQualityLevel = 0.1
	ACMISSOFTISP_API bool GetPatchSize(const BYTE *pBuffer, int nImageWidth, int nImageHeight, int nDataType, double dThreshold, TPatchInfo tPatchInfo, std::vector<BYTE>& vMask, TPatchSize& tMaxPatchSize);

	ACMISSOFTISP_API bool SearchEdgeCenter(const BYTE* pSrc, POINT tStartPoint, int nEdgeDir, int nScanDir, RECT crop_ROI, int nROIWidth, int nROIHeight, RECT& rtROI);
	ACMISSOFTISP_API void MoveROI2EdgeCenter(BYTE* pYBuffer, int nImageWidth, int nImageHeight, int nDataType, int nEdgeDir, RECT& rtROI, RECT crop_ROI, int nIndex);
	ACMISSOFTISP_API bool SearchSFRPatch(const BYTE* pYBuffer, int nImageWidth, int nImageHeight, DBPOINT ptDeltaOC, int nDataType, int nPatchPartialDemosaic, TCircleSpecN& tCircleSpec, std::vector<TPatchInfo>& vSFRPatchInfo, std::vector<TPatchSize>& vSFRPatchSize, std::vector< std::vector<THarrisCornerPoint> >& vVertex);

	ACMISSOFTISP_API void HarrisCorner(const BYTE* img, int w, int h, RECT rtROI, double th, std::vector<THarrisCornerPoint>& vCorners);
	ACMISSOFTISP_API void HarrisCorner(const unsigned short* img, int w, int h, RECT rtROI, double dThreshold, std::vector<THarrisCornerPoint>& vCorners);
	ACMISSOFTISP_API void HarrisCornerOpenCV(const BYTE* img, int w, int h, RECT rtROI, double dThreshold, std::vector<THarrisCornerPoint>& vCorners);
	ACMISSOFTISP_API void HarrisCornerOpenCV(const unsigned short* img, int w, int h, RECT rtROI, double dThreshold, std::vector<THarrisCornerPoint>& vCorners);

	ACMISSOFTISP_API DBPOINT GetCentroidCircleCenter(int* pBuffer, int nImageWidth, int nImageHeight, double dThresholdRatio, double dThresholdMargin, int bEnableChannel, TDATASPEC& tDataSpec, double dCenterAvgBright, double* dCornerAvgBright, double& dThresholdUL, double& dThresholdLL);
	ACMISSOFTISP_API bool FindFiducialMark(const int* pBuffer, int nImageWidth, int nImageHeight, std::vector< POINT> ptROICenter, double dBinThreshold, double dMinCircularity, int nMinSize, double dMaxROIDelta, TInspectRegionOffset tInspectRegionOffset, std::vector<POINT>& vMarkPoint, std::vector<CDRect>& vMarkRadiusBox, std::vector<CDRect>& vMarkROI);
	ACMISSOFTISP_API bool DefectFlareMark(BYTE* pFrameY, int nImageWidth, int nImageHeight, int nDataType, RECT rtROI, double dBinaryThreshold, double dRadius, double dBorderWidth, std::vector<DBox2D>& vBox);
	ACMISSOFTISP_API bool DefectStrayLightPoint(BYTE* pBuffer, int nROIWidth, int nROIHeight, int nDataType, double* dBinaryThreshold, int nMinLEDLightSize, TROICPoint tCenterPoint, POINT& ptStrayLightCenter, int& nMaxBlobSize);
	ACMISSOFTISP_API bool FindFiducialMark(BYTE* pFrameY, int nImageWidth, int nImageHeight, int nDataType, RECT rtFiducialMarkROI, int nROIBoxSize, int nMaxROIBoxSize, CDPoint ptFiducialMarkPoint, double dBinaryThreshold, double dMaxDeviation, double dRadius, EFiducialMarkShape eFiducialMarkShape, CDPoint& MarkPoint, CDRect& MarkRadiusBox, CDRect& MarkROI);
	ACMISSOFTISP_API bool FindFiducialMark(BYTE* pFrameY, int nImageWidth, int nImageHeight, int nDataType, int nROIBoxSize, int nMaxROIBoxSize, double dBinaryThreshold, double dRadius, std::vector<CDPoint>& vMarkPoint, std::vector<CDRect>& vMarkRadiusBox, std::vector<CDRect>& vMarkROI);
};
