#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>


typedef struct _THarrisCornerPoint
{
	POINT ptCorner;
	double dValue;
	int nPatchIndex;
} THarrisCornerPoint;

typedef struct _TPatchInfo
{
	RECT rtROI;
	POINT ptCenter;
	POINT ptStartVertex;
	double dThMin;
	double dThMax;
	int nPatchShape;
	int nVertexCount;
	int nPatchColor;
	int nMinDistance;
	bool bSeparate;
} TPatchInfo;

typedef struct _TPatchSize
{
	int nArea;
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
} TPatchSize;

typedef enum _EPatchShape
{
	PatchShape_Square,
	PatchShape_Clamp,
	PatchShape_PacMan,
	PatchShape_Fan,
	PatchShape_Polygon
} EPatchShape;

namespace ACMISSoftISP
{
	ACMISSOFTISP_API int xCalcImageRadius4Byte(int&ocx, int&ocy, int &radx, int &rady, const int* img, int w, int h, TCircleSpecN *Spec, double &angle, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT); // using Y Image Only
	ACMISSOFTISP_API int xCalcImageRadius2Byte(int&ocx, int&ocy, int &radx, int &rady, const unsigned short* img, int w, int h, TCircleSpecN *Spec, double &angle); // using Y Image Only
	ACMISSOFTISP_API int xCalcImageRadius(int&ocx, int&ocy, int &radx, int &rady, const BYTE* img, int w, int h, TCircleSpecN *Spec, double &angle); // using Y Image Only

	ACMISSOFTISP_API int xCalcCenterCircleObject4Byte(int&ocx, int&ocy, const int* img, int w, int h, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT); // using Y Image Only
	ACMISSOFTISP_API int xCalcCenterCircleObject2Byte(int&ocx, int&ocy, const unsigned short* img, int w, int h); // using Y Image Only
	ACMISSOFTISP_API int xCalcCenterCircleObject(int&ocx, int&ocy, const BYTE* img, int w, int h); // using Y Image Only

	ACMISSOFTISP_API void xCalcFixedCircleCenter4Byte(int&ocx, int&ocy, const int* img, int w, int h, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISP_API void xCalcFixedCircleCenter2Byte(int&ocx, int&ocy, const unsigned short* img, int w, int h);
	ACMISSOFTISP_API void xCalcFixedCircleCenter(int&ocx, int&ocy, const BYTE* img, int w, int h);

	ACMISSOFTISP_API int xCalcCircleData4Byte(const int* img, int w, int h, TCircleSpecN *Spec, int &m_nOcx, int &m_nOcy, int &m_nRadx, int &m_nRady, double &m_dAngle, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISP_API int xCalcCircleData2Byte(const unsigned short* img, int w, int h, TCircleSpecN *Spec, int &m_nOcx, int &m_nOcy, int &m_nRadx, int &m_nRady, double &m_dAngle);
	ACMISSOFTISP_API int xCalcCircleData(const BYTE* img, int w, int h, TCircleSpecN *Spec, int &m_nOcx, int &m_nOcy, int &m_nRadx, int &m_nRady, double &m_dAngle);
	ACMISSOFTISP_API int xCalcCircleData4Byte(const int* img, int w, int h, TCircleSpecN *Spec, TCircleData& tCircleData, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	ACMISSOFTISP_API int xCalcCircleData2Byte(const unsigned short* img, int w, int h, TCircleSpecN *Spec, TCircleData& tCircleData);
	ACMISSOFTISP_API int xCalcCircleData(const BYTE* img, int w, int h, TCircleSpecN *Spec, TCircleData& tCircleData);
	ACMISSOFTISP_API int xGetCircleMask(int w, int h, TCircleSpecN& Spec, TCircleData& tCircleData, BYTE* pMask);

	ACMISSOFTISP_API bool DetectSqureVertexs(const BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT* inputROI, int num, POINT* outputPos);
	ACMISSOFTISP_API bool DetectPatchVertexs(const BYTE *pBuffer, int nImageWidth, int nImageHeight, TPatchInfo* tPatchInfo, int num, std::vector< std::vector<THarrisCornerPoint> >& outputPos);
	ACMISSOFTISP_API bool DetectPatchVertexsOpenCV(const BYTE *pBuffer, int nImageWidth, int nImageHeight, void *params, std::vector<TPatchInfo> vPatchInfo, std::vector< std::vector<THarrisCornerPoint> >& outputPos, std::vector<TPatchSize>& vPatchSize);
	ACMISSOFTISP_API bool DetectPatchVertexsOpenCV(const BYTE *pBuffer, int nImageWidth, int nImageHeight, double dThreshold, TPatchInfo tPatchInfo, int nPatchIndex, std::vector<THarrisCornerPoint>& outputPos, TPatchSize& tPatchSize);
	ACMISSOFTISP_API bool DetectCrossCenter(const BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT* inputROI, int num, POINT* outputPos);
	ACMISSOFTISP_API bool GetPatchSize(const BYTE *pBuffer, int nImageWidth, int nImageHeight, double dThreshold, TPatchInfo tPatchInfo, TPatchSize& tMaxPatchSize);

	ACMISSOFTISP_API bool SearchEdgeCenter(const BYTE* pSrc, POINT tStartPoint, int nDir, RECT crop_ROI, int nROIWidth, int nROIHeight, RECT& rtROI);
	ACMISSOFTISP_API void MoveROI2EdgeCenter(BYTE* pYBuffer, int nImageWidth, int nImageHeight, int nEdgeDir, RECT& rtROI, RECT crop_ROI, int nIndex);
	ACMISSOFTISP_API bool SearchSFRPatch(const BYTE* pYBuffer, int nImageWidth, int nImageHeight, bool bUsingOpenCV, int nPatchPartialDemosaic, double dThresholdMax, std::vector<TPatchInfo>& vSFRPatchInfo, std::vector<TPatchSize>& vSFRPatchSize, std::vector< std::vector<THarrisCornerPoint> >& vVertex);

	ACMISSOFTISP_API void HarrisCorner(const BYTE* img, int w, int h, RECT rtROI, double th, std::vector<THarrisCornerPoint>& vCorners);
	ACMISSOFTISP_API void HarrisCorner(const unsigned short* img, int w, int h, RECT rtROI, double dThreshold, std::vector<THarrisCornerPoint>& vCorners);
	ACMISSOFTISP_API void HarrisCornerOpenCV(const BYTE* img, int w, int h, RECT rtROI, double dThreshold, std::vector<THarrisCornerPoint>& vCorners);
	ACMISSOFTISP_API void HarrisCornerOpenCV(const unsigned short* img, int w, int h, RECT rtROI, double dThreshold, std::vector<THarrisCornerPoint>& vCorners);
};
