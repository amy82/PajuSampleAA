#pragma once

#include "LibACMISCommon/CommonEnum.h"
#include "LibACMISCommon/DataTypes.h"

#include <atlstr.h>
#include <vector>

struct TDATASPEC
{
	EOUTMODE eOutMode;
	EDATAFORMAT eDataFormat;
	ESENSORTYPE eSensorType;
	EDEMOSAICMETHOD eDemosaicMethod;
	int nBlackLevel;
};

struct TBufferInfo
{
	BYTE* pBuffer;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
};

struct TBufferInfoM
{
	BYTE** pBuffer;
	int nBufferCount;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
};

struct TFileInfo
{
	char* strFileName;
	bool bIsRaw;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
};

struct TFileInfoM
{
	char** strFileName;
	bool bIsRaw;
	int nFileCount;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
};

struct TColorRatio
{
	double RG;
	double BG;
	double GrGb;
	double GrG;
	double GbG;
	double R;
	double G;
	double B;
	double Gr;
	double Gb;
	TColorRatio(double _RG = 0.0, double _BG = 0.0, double _GrGb = 0.0, double _GrG = 0.0, 
		        double _GbG = 0.0, double _R = 0.0, double _G = 0.0, double _B = 0.0)
		: RG(_RG), BG(_BG), GrGb(_GrGb), GrG(_GrG), GbG(_GbG), R(_R), G(_G), B(_B), Gr(_G), Gb(_G) {}
};

struct TColorReproduction
{
	double L;
	double a;
	double b;
};
using TColorLab = TColorReproduction;

struct TROIPoint
{
	POINT ptCenter;
	LONG nROIWidth;
	LONG nROIHeight;
};
using TROICPoint = TROIPoint;

struct TROISPoint
{
	POINT ptStart;
	LONG nROIWidth;
	LONG nROIHeight;
};

struct TROIField
{
	float fHorField;
	float fVerField;
	LONG nROIWidth;
	LONG nROIHeight;
};

struct TROIDataCommon
{
	EROIType eROIType;
	float fData[4];
};

struct TROIData
{
	double* dOffset;
	EROIType eROIType;
	int ROICount;
	void* pROIData;
};

struct TInspectRegionOffset
{
	int nStartOffsetX;
	int nStartOffsetY;
	int nEndOffsetX;
	int nEndOffsetY;
};

// 입력 Image Info
struct INSPECTION_IMAGE_INFO
{
	std::vector<int> vImageIndex;
	std::vector<int> vImageType;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
	EImageFormat eImageFormat;
};

// 입력 구조체
struct INSPECTION_INPUT
{
	AlgorithmTestItem enAlgorithmType;
	INSPECTION_IMAGE_INFO tImageInfo;
	void* pSpec;
	void* pSpecExtra;
	TROIData* pROI;
};

// 결과 구조체 - 통합
struct INSPECTION_RESULT
{
	AlgorithmTestItem enAlgorithmType;
	std::string strVersion;
	std::vector<std::string> vStrLogHeader;
	std::vector<std::string> vStrLogData;
	std::vector<int> vResultCode;
	int nElapsedTime;
	void* pInspectionResult;
};

struct TCircleData
{
	double dOcx;	// 타원의 x 중심
	double dOcy;	// 타원의 y 중심
	double dRadx;	// 타원의 x 방향 반지름
	double dRady;	// 타원의 y 방향 반지름
	double dAngle;	// 타원의 기울어진 각도
};

struct TCircleSpecN
{
	bool bEnableCircle;			// 타원 영역 활성화 여부
	int nUsedFixedCircle;		// 고정 좌표 원을 사용할지 여부
								// - 0: 이미지에서 opencv를 이용해서 직접 타원 찾음
								// - 1: Horizontal 기준 1.0F 원(r = w/2)
								// - 2: MTM (미사용)
								// - 3: Diagonal 기준 1.0F 원(r = d, d^2 = (w/2)^2 + (h/2)^2)
	// 원을 찾을 때(nUsedFixedCircle == 0) 사용
	int nPosOffsetX;			// 이미지 좌우 영역 margin
	int nPosOffsetY;			// 이미지 상하 영역 margin
	double dThresholdRatio;		// 이미지 이진화 threshold
	double dROIRange;			// 이미지 중심 영역 margin 비율
	// 구한 원의 반지름을 scale할 때 사용
	double dRadiusRatioX;		// 타원의 x 방향 반지름 scaler
	double dRadiusRatioY;		// 티원의 y 방향 반지름 scaler
};

struct TCircleSpecCommon
{
	int nEnableCircle;
	int nCommonUsedFixedCircle;
	double dCommonRadiusRatioX;
	double dCommonRadiusRatioY;
	int nDetectPosOffsetX;
	int nDetectPosOffsetY;
	double dDetectThresholdRatio;
	double dDetectROIRange;
	double  dMultiZoneSizeRatio[3];
	double	dMultiThreshold[3];
};

struct TFiducialMarkType
{
	CDPoint ptFiducialMarkPoint;
	int nFiducialMarkShape; // EFiducialMarkShape
};

struct TFiducialMarkUse
{
	TFiducialMarkType tFiducialMarkType;
	int nInspectItem;
};

struct THarrisCornerPoint
{
	POINT ptCorner;
	double dValue;
	int nPatchIndex;
};

struct TPatchInfo
{
	RECT rtROI;
	POINT ptCenter;
	POINT ptStartVertex;
	double dMinPatchSize;
	double dMaxPatchSize;
	double dBinaryThreshold;
	double dAvgBrightThreshold;
	int nPatchShape;
	int nVertexCount;
	int nPatchColor;
	int nMinDistance;
	int nSeparateLevel;
	int nPatchPos;
	bool bSeparate;
};

struct TPatchSize
{
	int nArea;
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
};

struct TInspectROIData
{
	unsigned int nVersion;
	int nMaxROIFlagCount;
	float fROIFlag[20]; 
	/* 
	0: ROI type, 
	1 ~ 4: ROI data, 
	5: Offset, 
	6: Min Threshold, 
	7: Max Threshold, 
	8 ~ : Variable for each algorithm 
	*/
};

struct TInspectSpec
{
	unsigned int nVersion;
	int nROICount;
	TInspectROIData* tROI;
	int nMaxSpecFlagCount;
	float fSpecFlag[100];
	int nMaxEtcFlagCount;
	float fEtcFlag[10];
	TInspectRegionOffset tInspectRegionOffset;
	float fCircleSpec[CIRCLE_COMMON_FLAG_MAX_COUNT]; /* TCircleSpecCommon */
};

struct TInspectResult
{
	unsigned int nVersion;
	int nROICount;
	TInspectROIData* tROI;
	int nMaxResultCount;
	float fResult[100];
};