#pragma once

#include <LibACMISCommon\ACMISCommon.h>

typedef enum _EImageRegion
{
	EIMAGEREGION_CENTER,
	EIMAGEREGION_EDGE,
	EIMAGEREGION_CORNER,
	EIMAGEREGION_CIRCLE,
	EIMAGEREGION_MAX,
	EIMAGEREGION_EDGE_HORIZONTAL,
	EIMAGEREGION_EDGE_VERTICAL,
	EIMAGEREGION_CIRCLE_A = EIMAGEREGION_CENTER,
	EIMAGEREGION_CIRCLE_B,
	EIMAGEREGION_CIRCLE_C
} EImageRegion;

typedef enum _EImageArea5
{
	EImageArea_A1,
	EImageArea_A2,
	EImageArea_A3,
	EImageArea_A4,
	EImageArea_A5
} EImageArea5;

typedef enum _EBlockType
{
	EBLOCKTYPE_A,
	EBLOCKTYPE_B
} EBlockType;

#define RESULT_DEFECT_VERSION_MAJOR		1
#define RESULT_DEFECT_VERSION_MINOR		0
typedef enum _RESULT_FLAG_DEFECT
{
	DEFECT_RESULT_CHANNEL,
	DEFECT_RESULT_VALUE,
	DEFECT_RESULT_POS_X,
	DEFECT_RESULT_POS_Y,
	DEFECT_RESULT_WIDTH,
	DEFECT_RESULT_HEIGHT,
	DEFECT_RESULT_COUNT,
	DEFECT_RESULT_TYPE,
	DEFECT_RESULT_CONTRAST_MAX_R,
	DEFECT_RESULT_CONTRAST_MAX_GR,
	DEFECT_RESULT_CONTRAST_MAX_GB,
	DEFECT_RESULT_CONTRAST_MAX_B,

	DEFECT_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_DEFECT;

typedef struct _TDefectResult
{
	int nChannel;
	double dValue; // defect contrast
	POINT ptPos;	// defect cluster center position (unit:pixel or block)
	int nWidth; // defect cluster width (unit:pixel or block)
	int nHeight; // defect cluster height (unit:pixel or block)
	int nCount; // defect number in defect cluster (unit: pixel or block)
	double dContrastMaxR;	// max defect contrast on R channel
	double dContrastMaxGr;	// max defect contrast on Gr channel
	double dContrastMaxGb;	// max defect contrast on Gb channel
	double dContrastMaxB;	// max defect contrast on B channel
	int nType; // type of defect
} TDefectResult;

#define RESULT_BLOB_VERSION_MAJOR		1
#define RESULT_BLOB_VERSION_MINOR		0
typedef enum _RESULT_FLAG_BLOB
{
	BLOB_RESULT_ROI_LEFT = DEFECT_RESULT_FLAG_MAX_COUNT,
	BLOB_RESULT_ROI_TOP,
	BLOB_RESULT_ROI_RIGHT,
	BLOB_RESULT_ROI_BOTTOM,
	BLOB_RESULT_REGION,
	BLOB_RESULT_PASS,

	BLOB_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_BLOB;

typedef struct _TBlobResult
{
	TDefectResult tDefectData;
	RECT rROI;
	EImageRegion ERegion;
	bool bPass;
} TBlobResult;

typedef std::vector<TBlobResult> vTBlobResult;


typedef struct _TCircleSpec
{
	bool bEnableCircle;
	int nPosOffsetX;
	int nPosOffsetY;
	double dRadiusRatioX;
	double dRadiusRatioY;
} TCircleSpec;


typedef struct _TMultiCircleSpec
{
	bool bEnableMultiCircle;
	double  dZoneSizeRatio[3];
	double	dThreshold[3];
	int		nBlobSize[3];
} TMultiCircleSpec;


typedef struct _TFindMarkSpec
{
	int nMarkType;
	int nMarkNum;
	int nMinMarkSize;
	int nMaxMarkSize;
	double dRatio;
} TFindMarkSpec;

typedef struct _TMarkROISpec
{
	POINT pt;
	RECT rt;
} TMarkROISpec;

#include "ACMISBlemishDef.h"
#include "ACMISDefectDef.h"
#include "ACMISOpticalCenterDef.h"
#include "ACMISSignalNoiseRatioDef.h"
