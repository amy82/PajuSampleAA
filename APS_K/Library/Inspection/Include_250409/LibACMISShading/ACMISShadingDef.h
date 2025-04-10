#pragma once

#include <LibACMISCommon\ACMISCommon.h>

typedef enum _EPos
{
	POS_CENTER,
	POS_LT,
	POS_RT,
	POS_LB,
	POS_RB
} EPos;

typedef enum _EROIPOSITION
{
	eHorizontal = 0,
	eVertical,
	eDiagonalA,
	eDiagonalB,
	eCenter
} EROIPosition;

typedef enum _ERICommonType
{
	RICommon_Coordinate,
	RICommon_Block_Uniform,
	RICommon_Block_NonUniform,
	RICommon_Ratio
}ERICommonType;

enum
{
	VIGNETTING_Y_MEAN_RATIO = 0,
	VIGNETTING_DSTRIPE,
	VIGNETTING_ALL
};


typedef enum _EColorSpaceType
{
	ColorSpace_Bayer,
	ColorSpace_RGB
} EColorSpaceType;

typedef enum _EMaxDiffType
{
	MaxDiff_Total,
	MaxDiff_Each,
	MaxRatio_Total,
	MaxRatio_Each
} EMaxDiffType;

typedef struct _TColorSensitivitySpec
{
	bool bAdjustFactor;
	double dRGFactor;
	double dBGFactor;
	double dGrGbFactor;
	double dSpecROISizeRatio;

	double dSpecDevMaxRG;
	double dSpecDevMinRG;
	double dSpecDevMaxBG;
	double dSpecDevMinBG;
	double dSpecDevMaxGrGb;
	double dSpecDevMinGrGb;
} TColorSensitivitySpec;

#define COLOR_SENSITIVITY_SPEC_FLAG_VERSION_MAJOR		1
#define COLOR_SENSITIVITY_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_COLOR_SENSITIVITY
{
	COLOR_SENSITIVITY_ADJUST_TYPE,
	COLOR_SENSITIVITY_TYPICAL_VALUE_TYPE,

	COLOR_SENSITIVITY_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_COLOR_SENSITIVITY;

#define COLOR_SENSITIVITY_ROI_FLAG_VERSION_MAJOR		1
#define COLOR_SENSITIVITY_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_COLOR_SENSITIVITY
{
	COLOR_SENSITIVITY_ROI_TYPE,
	COLOR_SENSITIVITY_ROI_DATA1,
	COLOR_SENSITIVITY_ROI_DATA2,
	COLOR_SENSITIVITY_ROI_DATA3,
	COLOR_SENSITIVITY_ROI_DATA4,
	COLOR_SENSITIVITY_ROI_OFFSET_RG,
	COLOR_SENSITIVITY_ROI_OFFSET_BG,
	COLOR_SENSITIVITY_ROI_OFFSET_GRGB,
	COLOR_SENSITIVITY_ROI_DEV_MIN_THRESHOLD_RG,
	COLOR_SENSITIVITY_ROI_DEV_MAX_THRESHOLD_RG,
	COLOR_SENSITIVITY_ROI_DEV_MIN_THRESHOLD_BG,
	COLOR_SENSITIVITY_ROI_DEV_MAX_THRESHOLD_BG,
	COLOR_SENSITIVITY_ROI_DEV_MIN_THRESHOLD_GRGB,
	COLOR_SENSITIVITY_ROI_DEV_MAX_THRESHOLD_GRGB,

	COLOR_SENSITIVITY_ROI_FLAG_MAX_COUNT
} ROI_FLAG_COLOR_SENSITIVITY;

typedef struct _TColorSensitivitySpecN
{
	int nAdjustType;	// 0: plus, 1: multiply
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	TROIData tROI;

	double dSpecDevMaxRG;
	double dSpecDevMinRG;
	double dSpecDevMaxBG;
	double dSpecDevMinBG;
	double dSpecDevMaxGrGb;
	double dSpecDevMinGrGb;
} TColorSensitivitySpecN;

#define RESULT_COLOR_SENSITIVITY_VERSION_MAJOR		1
#define RESULT_COLOR_SENSITIVITY_VERSION_MINOR		0
typedef enum _RESULT_FLAG_COLOR_SENSITIVITY
{
	COLOR_SENSITIVITY_RESULT_ROI_LEFT,
	COLOR_SENSITIVITY_RESULT_ROI_TOP,
	COLOR_SENSITIVITY_RESULT_ROI_RIGHT,
	COLOR_SENSITIVITY_RESULT_ROI_BOTTOM,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_R,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_G,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_B,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_GR,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_GB,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_RG,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_BG,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_GRGB,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_GRG,
	COLOR_SENSITIVITY_RESULT_COLOR_RATIO_GBG,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_R,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_G,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_B,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_GR,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_GB,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_RG,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_BG,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_GRGB,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_GRG,
	COLOR_SENSITIVITY_RESULT_ADJUST_COLOR_RATIO_GBG,

	COLOR_SENSITIVITY_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_COLOR_SENSITIVITY;

typedef struct _TColorSensitivityResult
{
	RECT rtROI;
	TColorRatio tColorRatio;
	TColorRatio tAdjustColorRatio;
} TColorSensitivityResult;

typedef struct _TColorShadingSpec
{
	double dSpecROISizeRatio;

	double dSpecDevMaxRG;
	double dSpecDevMinRG;
	double dSpecDevMaxBG;
	double dSpecDevMinBG;
	double dSpecDevMaxGrGb;
	double dSpecDevMinGrGb;

	double dSpecOffsetMaxRG;
	double dSpecOffsetMinRG;
	double dSpecOffsetMaxBG;
	double dSpecOffsetMinBG;
	double dSpecOffsetMaxGrGb;
	double dSpecOffsetMinGrGb;

	double dSpecDiffRG;
	double dSpecDiffBG;
	double dSpecDiffGrGb;
} TColorShadingSpec;

#define COLOR_SHADING_SPEC_FLAG_VERSION_MAJOR		1
#define COLOR_SHADING_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_COLOR_SHADING
{
	COLOR_SHADING_TYPICAL_VALUE_TYPE,
	COLOR_SHADING_DEV_MIN_THRESHOLD_RG,
	COLOR_SHADING_DEV_MAX_THRESHOLD_RG,
	COLOR_SHADING_DEV_MIN_THRESHOLD_BG,
	COLOR_SHADING_DEV_MAX_THRESHOLD_BG,
	COLOR_SHADING_DEV_MIN_THRESHOLD_GRGB,
	COLOR_SHADING_DEV_MAX_THRESHOLD_GRGB,
	COLOR_SHADING_OFFSET_MIN_THRESHOLD_RG,
	COLOR_SHADING_OFFSET_MAX_THRESHOLD_RG,
	COLOR_SHADING_OFFSET_MIN_THRESHOLD_BG,
	COLOR_SHADING_OFFSET_MAX_THRESHOLD_BG,
	COLOR_SHADING_OFFSET_MIN_THRESHOLD_GRGB,
	COLOR_SHADING_OFFSET_MAX_THRESHOLD_GRGB,
	COLOR_SHADING_DIFF_THRESHOLD_RG,
	COLOR_SHADING_DIFF_THRESHOLD_BG,
	COLOR_SHADING_DIFF_THRESHOLD_GRGB,
	COLOR_SHADING_RI_MIN_THRESHOLD_R,
	COLOR_SHADING_RI_MIN_THRESHOLD_GR,
	COLOR_SHADING_RI_MIN_THRESHOLD_GB,
	COLOR_SHADING_RI_MIN_THRESHOLD_B,
	COLOR_SHADING_RI_MIN_THRESHOLD_RG,
	COLOR_SHADING_RI_MAX_THRESHOLD_RG,
	COLOR_SHADING_RI_MIN_THRESHOLD_BG,
	COLOR_SHADING_RI_MAX_THRESHOLD_BG,
	COLOR_SHADING_RI_MIN_THRESHOLD_GRGB,
	COLOR_SHADING_RI_MAX_THRESHOLD_GRGB,

	COLOR_SHADING_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_COLOR_SHADING;

#define COLOR_SHADING_ROI_FLAG_VERSION_MAJOR		1
#define COLOR_SHADING_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_COLOR_SHADING
{
	COLOR_SHADING_ROI_TYPE,
	COLOR_SHADING_ROI_DATA1,
	COLOR_SHADING_ROI_DATA2,
	COLOR_SHADING_ROI_DATA3,
	COLOR_SHADING_ROI_DATA4,
	COLOR_SHADING_ROI_OFFSET,

	COLOR_SHADING_ROI_FLAG_MAX_COUNT
} ROI_FLAG_COLOR_SHADING;

typedef struct _TColorShadingSpecN
{
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	TROIData tROI;

	double dSpecDevMaxRG;
	double dSpecDevMinRG;
	double dSpecDevMaxBG;
	double dSpecDevMinBG;
	double dSpecDevMaxGrGb;
	double dSpecDevMinGrGb;

	double dSpecOffsetMaxRG;
	double dSpecOffsetMinRG;
	double dSpecOffsetMaxBG;
	double dSpecOffsetMinBG;
	double dSpecOffsetMaxGrGb;
	double dSpecOffsetMinGrGb;

	double dSpecDiffRG;
	double dSpecDiffBG;
	double dSpecDiffGrGb;

	double dSpecRIMinR;
	double dSpecRIMinGr;
	double dSpecRIMinGb;
	double dSpecRIMinB;

	double dSpecRIMaxRG;
	double dSpecRIMinRG;
	double dSpecRIMaxBG;
	double dSpecRIMinBG;
	double dSpecRIMaxGrGb;
	double dSpecRIMinGrGb;
} TColorShadingSpecN;

#define RESULT_ROI_COLOR_SHADING_VERSION_MAJOR		1
#define RESULT_ROI_COLOR_SHADING_VERSION_MINOR		0
typedef enum _RESULT_ROI_FLAG_COLOR_SHADING
{
	COLOR_SHADING_RESULT_ROI_RG,
	COLOR_SHADING_RESULT_ROI_BG,
	COLOR_SHADING_RESULT_ROI_GRGB,
	COLOR_SHADING_RESULT_ROI_GRG,
	COLOR_SHADING_RESULT_ROI_GBG,
	COLOR_SHADING_RESULT_ROI_R,
	COLOR_SHADING_RESULT_ROI_G,
	COLOR_SHADING_RESULT_ROI_B,
	COLOR_SHADING_RESULT_ROI_GR,
	COLOR_SHADING_RESULT_ROI_GB,

	COLOR_SHADING_RESULT_ROI_FLAG_MAX_COUNT
} RESULT_ROI_FLAG_COLOR_SHADING;

#define RESULT_COLOR_SHADING_VERSION_MAJOR		1
#define RESULT_COLOR_SHADING_VERSION_MINOR		0
typedef enum _RESULT_FLAG_COLOR_SHADING
{
	COLOR_SHADING_RESULT_DEV_MAX_RG,
	COLOR_SHADING_RESULT_DEV_MIN_RG,
	COLOR_SHADING_RESULT_DEV_MAX_BG,
	COLOR_SHADING_RESULT_DEV_MIN_BG,
	COLOR_SHADING_RESULT_DEV_MAX_GRGB,
	COLOR_SHADING_RESULT_DEV_MIN_GRGB,
	COLOR_SHADING_RESULT_OFFSET_RG,
	COLOR_SHADING_RESULT_OFFSET_BG,
	COLOR_SHADING_RESULT_OFFSET_GRGB,
	COLOR_SHADING_RESULT_DIFF_RG,
	COLOR_SHADING_RESULT_DIFF_BG,
	COLOR_SHADING_RESULT_DIFF_GRGB,
	COLOR_SHADING_RESULT_RI_MIN_R,
	COLOR_SHADING_RESULT_RI_MIN_GR,
	COLOR_SHADING_RESULT_RI_MIN_GB,
	COLOR_SHADING_RESULT_RI_MIN_B,
	COLOR_SHADING_RESULT_RI_MAX_RG,
	COLOR_SHADING_RESULT_RI_MIN_RG,
	COLOR_SHADING_RESULT_RI_MAX_BG,
	COLOR_SHADING_RESULT_RI_MIN_BG,
	COLOR_SHADING_RESULT_RI_MAX_GRGB,
	COLOR_SHADING_RESULT_RI_MIN_GRGB,

	COLOR_SHADING_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_COLOR_SHADING;

typedef struct _TColorShadingResult
{
	double dDevMaxRG;
	double dDevMinRG;
	double dDevMaxBG;
	double dDevMinBG;
	double dDevMaxGrGb;
	double dDevMinGrGb;

	double dOffsetRG;
	double dOffsetBG;
	double dOffsetGrGb;

	double dDiffRG;
	double dDiffBG;
	double dDiffGrGb;

	double dRIMinR;
	double dRIMinGr;
	double dRIMinGb;
	double dRIMinB;

	double dRIMaxRG;
	double dRIMinRG;
	double dRIMaxBG;
	double dRIMinBG;
	double dRIMaxGrGb;
	double dRIMinGrGb;

	TColorRatio *pColorRatio;
} TColorShadingResult;

typedef struct _TColorChannelThreshold
{
	double dCH_R_Max;
	double dCH_GR_Max;
	double dCH_GB_Max;
	double dCH_B_Max;
	double dCH_R_Min;
	double dCH_GR_Min;
	double dCH_GB_Min;
	double dCH_B_Min;
} TColorChannelThreshold;

typedef struct _TColorShadingSpec_CommonN
{
	int nNormalizeIndex;
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	TROIData tHorROI;
	TROIData tVerROI;
	TROIData tDiaAROI;
	TROIData tDiaBROI;
	double *dHorThreshold;
	double *dVerThreshold;
	double *dDiaThreshold;
	double dHorThdMin[4];
	double dHorThdMax[4];
	double dVerThdMin[4];
	double dVerThdMax[4];
	double dDiaThdMin[4];
	double dDiaThdMax[4];
} TColorShadingSpec_CommonN;

typedef struct _TColorShadingResult_Common
{
	RECT rtROI;
	int nROIPosition;
	int nIndex;
	double dResult[4];
	double dNormalResult[4];
	bool bPass;
} TColorShadingResult_Common;

typedef struct _TRelativeIlluminationSpec
{
	double dBoxField;
	int	nBoxSize;
	double dSpecRIcornerMin;
	double dSpecRIcornerMax;
	double dSpecRIminMin;
	double dSpecRIminMax;
	double dCenterIntensity;
} TRelativeIlluminationSpec;

#define RELATIVE_ILLUMINATION_SPEC_FLAG_VERSION_MAJOR		1
#define RELATIVE_ILLUMINATION_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_RELATIVE_ILLUMINATION
{
	RELATIVE_ILLUMINATION_CENTER_INTENSITY,
	RELATIVE_ILLUMINATION_NORMALIZE_INDEX,

	RELATIVE_ILLUMINATION_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_RELATIVE_ILLUMINATION;

#define RELATIVE_ILLUMINATION_ROI_FLAG_VERSION_MAJOR		1
#define RELATIVE_ILLUMINATION_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_RELATIVE_ILLUMINATION
{
	RELATIVE_ILLUMINATION_ROI_TYPE,
	RELATIVE_ILLUMINATION_ROI_DATA1,
	RELATIVE_ILLUMINATION_ROI_DATA2,
	RELATIVE_ILLUMINATION_ROI_DATA3,
	RELATIVE_ILLUMINATION_ROI_DATA4,
	RELATIVE_ILLUMINATION_ROI_OFFSET,
	RELATIVE_ILLUMINATION_ROI_MIN_THRESHOLD,
	RELATIVE_ILLUMINATION_ROI_MAX_THRESHOLD,

	RELATIVE_ILLUMINATION_ROI_FLAG_MAX_COUNT
} ROI_FLAG_RELATIVE_ILLUMINATION;

typedef struct _TRelativeIlluminationSpecN
{
	TROIData tROI;
	double dSpecRIcornerMin;
	double dSpecRIcornerMax;
	double dSpecRIminMin;
	double dSpecRIminMax;
	double dCenterIntensity;
	int nSpecRINormalizeIndex;
} TRelativeIlluminationSpecN;

#define RELATIVE_ILLUMINATION_X_SPEC_FLAG_VERSION_MAJOR		1
#define RELATIVE_ILLUMINATION_X_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_RELATIVE_ILLUMINATION_X
{
	RELATIVE_ILLUMINATION_X_CENTER_BLOCK_SIZE,
	RELATIVE_ILLUMINATION_X_ENABLE_CHANNEL,
	RELATIVE_ILLUMINATION_X_CENTER_INTENSITY_CH0,
	RELATIVE_ILLUMINATION_X_CENTER_INTENSITY_CH1,
	RELATIVE_ILLUMINATION_X_CENTER_INTENSITY_CH2,
	RELATIVE_ILLUMINATION_X_CENTER_INTENSITY_CH3,

	RELATIVE_ILLUMINATION_X_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_RELATIVE_ILLUMINATION_X;

#define RELATIVE_ILLUMINATION_X_ROI_FLAG_VERSION_MAJOR		1
#define RELATIVE_ILLUMINATION_X_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_RELATIVE_ILLUMINATION_X
{
	RELATIVE_ILLUMINATION_X_ROI_TYPE,
	RELATIVE_ILLUMINATION_X_ROI_DATA1,
	RELATIVE_ILLUMINATION_X_ROI_DATA2,
	RELATIVE_ILLUMINATION_X_ROI_DATA3,
	RELATIVE_ILLUMINATION_X_ROI_DATA4,
	RELATIVE_ILLUMINATION_X_ROI_OFFSET,
	RELATIVE_ILLUMINATION_X_ROI_MIN_THRESHOLD_CH0,
	RELATIVE_ILLUMINATION_X_ROI_MAX_THRESHOLD_CH0,
	RELATIVE_ILLUMINATION_X_ROI_MIN_THRESHOLD_CH1,
	RELATIVE_ILLUMINATION_X_ROI_MAX_THRESHOLD_CH1,
	RELATIVE_ILLUMINATION_X_ROI_MIN_THRESHOLD_CH2,
	RELATIVE_ILLUMINATION_X_ROI_MAX_THRESHOLD_CH2,
	RELATIVE_ILLUMINATION_X_ROI_MIN_THRESHOLD_CH3,
	RELATIVE_ILLUMINATION_X_ROI_MAX_THRESHOLD_CH3,

	RELATIVE_ILLUMINATION_X_ROI_FLAG_MAX_COUNT
} ROI_FLAG_RELATIVE_ILLUMINATION_X;

typedef struct _TRelativeIlluminationSpecX
{
	TROIData tROI;
	int nSpecPixelCntInBlock;
	int nEnableChannel;
	double *dSpecCH0Threshold;
	double *dSpecCH1Threshold;
	double *dSpecCH2Threshold;
	double *dSpecCH3Threshold;
	double dSpecCenterIntensity[4];
} TRelativeIlluminationSpecX;

typedef struct _TRelativeIlluminationResult
{
	double dRIcornerRAW[4];
	double dRIROIMin[5];
	double dRIROIMax[5];
	double dRIcenterRAW;
	double dRIcorner;
	double dRImin;
} TRelativeIlluminationResult;

#define RESULT_ROI_RELATIVE_ILLUMINATION_VERSION_MAJOR		1
#define RESULT_ROI_RELATIVE_ILLUMINATION_VERSION_MINOR		0
typedef enum _RESULT_ROI_FLAG_RELATIVE_ILLUMINATION
{
	RELATIVE_ILLUMINATION_RESULT_ROI_CORNER_RAW,
	RELATIVE_ILLUMINATION_RESULT_ROI_CORNER_RATIO,
	RELATIVE_ILLUMINATION_RESULT_ROI_MIN,
	RELATIVE_ILLUMINATION_RESULT_ROI_MAX,

	RELATIVE_ILLUMINATION_RESULT_ROI_FLAG_MAX_COUNT
} RESULT_ROI_FLAG_RELATIVE_ILLUMINATION;

#define RESULT_RELATIVE_ILLUMINATION_VERSION_MAJOR		1
#define RESULT_RELATIVE_ILLUMINATION_VERSION_MINOR		0
typedef enum _RESULT_FLAG_RELATIVE_ILLUMINATION
{
	RELATIVE_ILLUMINATION_RESULT_CENTER_RAW,
	RELATIVE_ILLUMINATION_RESULT_CORNER,
	RELATIVE_ILLUMINATION_RESULT_MIN,

	RELATIVE_ILLUMINATION_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_RELATIVE_ILLUMINATION;

typedef struct _TRelativeIlluminationResultN
{
	double *dRIcornerRAW;
	double *dRIcornerRatio;
	double *dRIROIMin;
	double *dRIROIMax;
	double dRIcenterRAW;
	double dRIcorner;
	double dRImin;
} TRelativeIlluminationResultN;

#define RESULT_RELATIVE_ILLUMINATION_X_VERSION_MAJOR		1
#define RESULT_RELATIVE_ILLUMINATION_X_VERSION_MINOR		0
typedef enum _RESULT_FLAG_RELATIVE_ILLUMINATION_X
{
	RELATIVE_ILLUMINATION_X_RESULT_ROI_LEFT,
	RELATIVE_ILLUMINATION_X_RESULT_ROI_TOP,
	RELATIVE_ILLUMINATION_X_RESULT_ROI_RIGHT,
	RELATIVE_ILLUMINATION_X_RESULT_ROI_BOTTOM,
	RELATIVE_ILLUMINATION_X_RESULT_ROI_POSITION,
	RELATIVE_ILLUMINATION_X_RESULT_INDEX,
	RELATIVE_ILLUMINATION_X_RESULT_RAW_RESULT1,
	RELATIVE_ILLUMINATION_X_RESULT_RAW_RESULT2,
	RELATIVE_ILLUMINATION_X_RESULT_RAW_RESULT3,
	RELATIVE_ILLUMINATION_X_RESULT_RAW_RESULT4,
	RELATIVE_ILLUMINATION_X_RESULT_NORMAL_RESULT1,
	RELATIVE_ILLUMINATION_X_RESULT_NORMAL_RESULT2,
	RELATIVE_ILLUMINATION_X_RESULT_NORMAL_RESULT3,
	RELATIVE_ILLUMINATION_X_RESULT_NORMAL_RESULT4,
	RELATIVE_ILLUMINATION_X_RESULT_PASS,

	RELATIVE_ILLUMINATION_X_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_RELATIVE_ILLUMINATION_X;

typedef struct _TRelativeIlluminationResultX
{
	RECT rtROI;
	int nROIPosition;
	int nIndex;
	double dRIRawResult[4];
	double dRINormalResult[4];
	bool bPass;
} TRelativeIlluminationResultX;

#define RELATIVE_UNIFORMITY_SPEC_FLAG_VERSION_MAJOR		1
#define RELATIVE_UNIFORMITY_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_RELATIVE_UNIFORMITY
{
	RELATIVE_UNIFORMITY_ROI_SIZE,
	RELATIVE_UNIFORMITY_USE_OVERLAP,
	RELATIVE_UNIFORMITY_SPEC_MAX_DIFF,

	RELATIVE_UNIFORMITY_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_RELATIVE_UNIFORMITY;

typedef struct _TRelativeUniformitySpec
{
	int	nROISize;
	int nUseOverlap;
	double dSpecMax;
} TRelativeUniformitySpec;

#define RESULT_RELATIVE_UNIFORMITY_VERSION_MAJOR		1
#define RESULT_RELATIVE_UNIFORMITY_VERSION_MINOR		0
typedef enum _RESULT_FLAG_RELATIVE_UNIFORMITY
{
	RELATIVE_UNIFORMITY_RESULT_MAX,
	RELATIVE_UNIFORMITY_RESULT_MAX_BLOCK_X,
	RELATIVE_UNIFORMITY_RESULT_MAX_BLOCK_Y,
	RELATIVE_UNIFORMITY_RESULT_REF_BLOCK_X,
	RELATIVE_UNIFORMITY_RESULT_REF_BLOCK_Y,

	RELATIVE_UNIFORMITY_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_RELATIVE_UNIFORMITY;

typedef struct _TRelativeUniformityResult
{
	double dResultMax;
	int nMaxBlockX;
	int nMaxBlockY;
	int nRefBlockX; // 기준점
	int nRefBlockY; // 기준점
} TRelativeUniformityResult;

typedef struct _TShadingUniformitySpec
{
	int nROIWidth;
	int nROIHeight;
	int nMaxROICount;
	int nNormalizeIndex;
	POINT *ptHorROI;
	POINT *ptVerROI;
	POINT *ptDiaAROI;
	POINT *ptDiaBROI;
	double *dHorThreshold;
	double *dVerThreshold;
	double *dDiaThreshold;
	double dHorThdMin;
	double dHorThdMax;
	double dVerThdMin;
	double dVerThdMax;
	double dDiaThdMin;
	double dDiaThdMax;
} TShadingUniformitySpec;

#define SHADING_UNIFORMITY_SPEC_FLAG_VERSION_MAJOR		1
#define SHADING_UNIFORMITY_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_SHADING_UNIFORMITY
{
	SHADING_UNIFORMITY_NORMALIZE_INDEX,
	SHADING_UNIFORMITY_HOR_THRESHOLD_MIN,
	SHADING_UNIFORMITY_HOR_THRESHOLD_MAX,
	SHADING_UNIFORMITY_VER_THRESHOLD_MIN,
	SHADING_UNIFORMITY_VER_THRESHOLD_MAX,
	SHADING_UNIFORMITY_DIA_THRESHOLD_MIN,
	SHADING_UNIFORMITY_DIA_THRESHOLD_MAX,

	SHADING_UNIFORMITY_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_SHADING_UNIFORMITY;

#define SHADING_UNIFORMITY_ROI_FLAG_VERSION_MAJOR		1
#define SHADING_UNIFORMITY_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_SHADING_UNIFORMITY
{
	SHADING_UNIFORMITY_ROI_TYPE,
	SHADING_UNIFORMITY_ROI_DATA1,
	SHADING_UNIFORMITY_ROI_DATA2,
	SHADING_UNIFORMITY_ROI_DATA3,
	SHADING_UNIFORMITY_ROI_DATA4,
	SHADING_UNIFORMITY_ROI_OFFSET,
	SHADING_UNIFORMITY_ROI_THRESHOLD,

	SHADING_UNIFORMITY_ROI_FLAG_MAX_COUNT
} ROI_FLAG_SHADING_UNIFORMITY;

typedef struct _TShadingUniformitySpecN
{
	int nNormalizeIndex;
	TROIData tHorROI;
	TROIData tVerROI;
	TROIData tDiaAROI;
	TROIData tDiaBROI;
	double *dHorThreshold;
	double *dVerThreshold;
	double *dDiaThreshold;
	double dHorThdMin;
	double dHorThdMax;
	double dVerThdMin;
	double dVerThdMax;
	double dDiaThdMin;
	double dDiaThdMax;
} TShadingUniformitySpecN;

#define RESULT_SHADING_UNIFORMITY_VERSION_MAJOR		1
#define RESULT_SHADING_UNIFORMITY_VERSION_MINOR		0
typedef enum _RESULT_FLAG_RELATIVE_SHADING_UNIFORMITY
{
	SHADING_UNIFORMITY_RESULT_ROI_LEFT,
	SHADING_UNIFORMITY_RESULT_ROI_TOP,
	SHADING_UNIFORMITY_RESULT_ROI_RIGHT,
	SHADING_UNIFORMITY_RESULT_ROI_BOTTOM,
	SHADING_UNIFORMITY_RESULT_ROI_POSITION,
	SHADING_UNIFORMITY_RESULT_INDEX,
	SHADING_UNIFORMITY_RESULT_RAW_RESULT,
	SHADING_UNIFORMITY_RESULT_NORMAL_RESULT,
	SHADING_UNIFORMITY_RESULT_PASS,

	SHADING_UNIFORMITY_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_SHADING_UNIFORMITY;

typedef struct _TShadingUniformityResult
{
	RECT rtROI;
	int nROIPosition;
	int nIndex;
	double dResult;
	double dNormalResult;
	bool bPass;
} TShadingUniformityResult;

typedef struct _TRICommon_Coordinate
{
	TROIData tHorROI;
	TROIData tVerROI;
	TROIData tDiaAROI;
	TROIData tDiaBROI;
}TRICommon_Coordinate;

typedef struct _TRICommon_Block
{
	int *ptHorROI;
	int *ptVerROI;
	int *ptDiaAROI;
	int *ptDiaBROI;
}TRICommon_Block;

typedef struct _TRelativeIlluminationSpec_Common
{
	int ntype;
	int nBlockWidth;
	int nBlockHeight;
	int nMaxROICount;
	int nNormalizeIndex;
	int *ptHorROI;
	int *ptVerROI;
	int *ptDiaAROI;
	int *ptDiaBROI;
	double *dHorThreshold;
	double *dVerThreshold;
	double *dDiaThreshold;
	double *dHorOffset;
	double *dVerOffset;
	double *dDiaAOffset;
	double *dDiaBOffset;
	double dHorThdMin;
	double dHorThdMax;
	double dVerThdMin;
	double dVerThdMax;
	double dDiaThdMin;
	double dDiaThdMax;
} TRelativeIlluminationSpec_Common;

typedef struct _TRelativeIlluminationResult_Common
{
	RECT rtROI;
	int nROIPosition;
	int nIndex;
	double dResult;
	double dNormalResult;
	bool bPass;
} TRelativeIlluminationResult_Common;

typedef struct _TLowLightSpec
{
	int nThreshold_ParticleCount;
	double dThreshold_Center;
	double dThreshold_Middle;
	double dThreshold_Full;
	int nFullRectWidth;
	int nFullRectHeight;
	bool bEnableEllipseMiddle;
	bool bEnableEllipseCenter;
} TLowLightSpec;

typedef struct _TLowLightResult
{
	int nParticleCnt;
	POINT *ptParticlePnt;
	RECT *rtParticleRect;
	RECT rtROIRect[3];
} TLowLightResult;

typedef struct _TVignettingSpec
{
	double dYmeanSpec;
	double dYmeanROISizeRatio;
	double dDStripeSpec;
	double dDStripeStrideRatio;
	int nMode;
} TVignettingSpec;

typedef struct _TVignettingData
{
	RECT rtVignettingROI[5]; // center(index 0) + 4 corner
	double dROIRatioX[5];
	double dROIRatioY[5];
	double dVignetting[4]; // 4 corner vignetting
} TVignettingData;

#define COLOR_UNIFORMITY_SPEC_FLAG_VERSION_MAJOR		1
#define COLOR_UNIFORMITY_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_COLOR_UNIFORMITY
{
	COLOR_UNIFORMITY_GRID_SIZE_X,
	COLOR_UNIFORMITY_GRID_SIZE_Y,
	COLOR_UNIFORMITY_TYPICAL_VALUE_TYPE,
	COLOR_UNIFORMITY_COLOR_SPACE_TYPE,
	COLOR_UNIFORMITY_USE_OVERLAP,
	COLOR_UNIFORMITY_MAX_DIFF_TYPE,
	COLOR_UNIFORMITY_SPEC_MAX_DIFF_RG,
	COLOR_UNIFORMITY_SPEC_MAX_DIFF_BG,
	COLOR_UNIFORMITY_SPEC_MAX_DIFF_RB,
	COLOR_UNIFORMITY_SPEC_MAX_DIFF_GRGB,
	COLOR_UNIFORMITY_SPEC_MIN_DIFF_RG,
	COLOR_UNIFORMITY_SPEC_MIN_DIFF_BG,
	COLOR_UNIFORMITY_SPEC_MIN_DIFF_RB,
	COLOR_UNIFORMITY_SPEC_MIN_DIFF_GRGB,

	COLOR_UNIFORMITY_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_COLOR_UNIFORMITY;

typedef struct _TColorUniformitySpecN
{
	int	nGridSizeX;
	int nGridSizeY;
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	int nColorSpaceType;   // EColorSpaceType : Bayer or RGB
	int nUseOverlap;
	int nMaxDiffType;      // EMaxDiffType : Total diff or Each max diff
	double dSpecMaxDiffRG;
	double dSpecMaxDiffBG;
	double dSpecMaxDiffRB;
	double dSpecMaxDiffGrGb;
	double dSpecMinDiffRG;
	double dSpecMinDiffBG;
	double dSpecMinDiffRB;
	double dSpecMinDiffGrGb;
} TColorUniformitySpecN;

typedef struct _TColorUniformitySpec
{
	int	nGridSizeX;
	int nGridSizeY;
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	int nColorSpaceType;   // EColorSpaceType : Bayer or RGB
	int nUseOverlap;
	int nMaxDiffType;      // EMaxDiffType : Total diff or Each max diff
	double dSpecMaxDiffRG;
	double dSpecMaxDiffBG;
	double dSpecMaxDiffRB;
} TColorUniformitySpec;

#define RESULT_COLOR_UNIFORMITY_VERSION_MAJOR		1
#define RESULT_COLOR_UNIFORMITY_VERSION_MINOR		0
typedef enum _RESULT_FLAG_COLOR_UNIFORMITY
{
	COLOR_UNIFORMITY_RESULT_RG,
	COLOR_UNIFORMITY_RESULT_RB,
	COLOR_UNIFORMITY_RESULT_BG,
	COLOR_UNIFORMITY_RESULT_GRGB,
	COLOR_UNIFORMITY_RESULT_MAX_TOTAL_DIFF_RG,
	COLOR_UNIFORMITY_RESULT_MAX_TOTAL_DIFF_RB,
	COLOR_UNIFORMITY_RESULT_MAX_TOTAL_DIFF_BG,
	COLOR_UNIFORMITY_RESULT_MAX_TOTAL_DIFF_GRGB,
	COLOR_UNIFORMITY_RESULT_MAX_EACH_DIFF_RG,
	COLOR_UNIFORMITY_RESULT_MAX_EACH_DIFF_RB,
	COLOR_UNIFORMITY_RESULT_MAX_EACH_DIFF_BG,
	COLOR_UNIFORMITY_RESULT_MAX_EACH_DIFF_GRGB,
	COLOR_UNIFORMITY_RESULT_MIN_TOTAL_DIFF_RG,
	COLOR_UNIFORMITY_RESULT_MIN_TOTAL_DIFF_RB,
	COLOR_UNIFORMITY_RESULT_MIN_TOTAL_DIFF_BG,
	COLOR_UNIFORMITY_RESULT_MIN_TOTAL_DIFF_GRGB,
	COLOR_UNIFORMITY_RESULT_MIN_EACH_DIFF_RG,
	COLOR_UNIFORMITY_RESULT_MIN_EACH_DIFF_RB,
	COLOR_UNIFORMITY_RESULT_MIN_EACH_DIFF_BG,
	COLOR_UNIFORMITY_RESULT_MIN_EACH_DIFF_GRGB,
	COLOR_UNIFORMITY_RESULT_MAX_BLOCK_X,
	COLOR_UNIFORMITY_RESULT_MAX_BLOCK_Y,
	COLOR_UNIFORMITY_RESULT_MAX_REF_BLOCK_X,
	COLOR_UNIFORMITY_RESULT_MAX_REF_BLOCK_Y,
	COLOR_UNIFORMITY_RESULT_MIN_BLOCK_X,
	COLOR_UNIFORMITY_RESULT_MIN_BLOCK_Y,
	COLOR_UNIFORMITY_RESULT_MIN_REF_BLOCK_X,
	COLOR_UNIFORMITY_RESULT_MIN_REF_BLOCK_Y,

	COLOR_UNIFORMITY_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_COLOR_UNIFORMITY;

typedef struct _TColorUniformityResultN
{
	double dRG;
	double dRB;
	double dBG;
	double dGrGb;
	double dMaxTotalDiffRG;
	double dMaxTotalDiffRB;
	double dMaxTotalDiffBG;
	double dMaxTotalDiffGrGb;
	double dMaxEachDiffRG;
	double dMaxEachDiffRB;
	double dMaxEachDiffBG;
	double dMaxEachDiffGrGb;
	double dMinTotalDiffRG;
	double dMinTotalDiffRB;
	double dMinTotalDiffBG;
	double dMinTotalDiffGrGb;
	double dMinEachDiffRG;
	double dMinEachDiffRB;
	double dMinEachDiffBG;
	double dMinEachDiffGrGb;
	int nMaxBlockX;
	int nMaxBlockY;
	int nMaxRefBlockX; // 기준점
	int nMaxRefBlockY; // 기준점
	int nMinBlockX;
	int nMinBlockY;
	int nMinRefBlockX; // 기준점
	int nMinRefBlockY; // 기준점
} TColorUniformityResultN;

typedef struct _TColorUniformityResult
{
	double dRG;
	double dRB;
	double dBG;
	double dMaxDiffRG;
	double dMaxDiffRB;
	double dMaxDiffBG;
	int nMaxBlockX;
	int nMaxBlockY;
	int nRefBlockX; // 기준점
	int nRefBlockY; // 기준점
} TColorUniformityResult;

#define LENS_SHADING_SPEC_FLAG_VERSION_MAJOR		1
#define LENS_SHADING_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_LENS_SHADING
{
	LENS_SHADING_BLOCK_CNT_X,
	LENS_SHADING_BLOCK_CNT_Y,
	LENS_SHADING_TYPICAL_VALUE_TYPE,
	LENS_SHADING_COLOR_SPACE_TYPE,
	LENS_SHADING_USE_OVERLAP,
	LENS_SHADING_CENTER_BLOCK_SIZE,
	LENS_SHADING_ENABLE_CHANNEL,

	LENS_SHADING_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_LENS_SHADING;

typedef struct _TLensShadingSpec
{
	int	nBlockCntX;
	int nBlockCntY;
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	int nColorSpaceType;   // EColorSpaceType : Bayer or RGB
	int nUseOverlap;
	int nSpecPixelCntInBlock;
	int nEnableChannel;
} TLensShadingSpec;

#define RESULT_LENS_SHADING_VERSION_MAJOR		1
#define RESULT_LENS_SHADING_VERSION_MINOR		0
typedef enum _RESULT_FLAG_LENS_SHADING
{
	LENS_SHADING_RESULT_ROI_LEFT,
	LENS_SHADING_RESULT_ROI_TOP,
	LENS_SHADING_RESULT_ROI_RIGHT,
	LENS_SHADING_RESULT_ROI_BOTTOM,
	LENS_SHADING_RESULT_RIR,
	LENS_SHADING_RESULT_RIG,
	LENS_SHADING_RESULT_RIB,
	LENS_SHADING_RESULT_RIGR,
	LENS_SHADING_RESULT_RIGB,
	LENS_SHADING_RESULT_R,
	LENS_SHADING_RESULT_G,
	LENS_SHADING_RESULT_B,
	LENS_SHADING_RESULT_GR,
	LENS_SHADING_RESULT_GB,

	LENS_SHADING_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_LENS_SHADING;

typedef struct _TLensShadingResult
{
	RECT rtROI;
	double dRIR;
	double dRIG;
	double dRIB;
	double dRIGr;
	double dRIGb;
	double dR;
	double dG;
	double dB;
	double dGr;
	double dGb;
} TLensShadingResult;


template<typename T, typename TResult, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class IShadingCommon
{
public:
	IShadingCommon() : m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_bIsCertified(false) { memset(&m_tDataSpec, 0, sizeof(TDATASPEC)); memset(&m_stSpec, 0, sizeof(T)); memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset)); }
	virtual ~IShadingCommon() {}

	virtual bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool Inspect(TBufferInfo& tBufferInfo, T& _Spec) = 0;
	virtual bool Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual int GetInspectionRegionCount() = 0;
	virtual const TResult* GetInspectionResult(int nIndex = 0, EROIPosition pos = eHorizontal) = 0;
	virtual bool InSpec(const T& _Spec) = 0;
	virtual const RECT* GetInspectionROI(int nIndex = 0, EROIPosition pos = eHorizontal) = 0;
	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;
	virtual const char* GetVersion() = 0;
	virtual void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) = 0;
	virtual void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) = 0;
	virtual void Init() = 0;
	virtual double GetSaturationResult(int nIndex = 0) = 0;
	virtual bool GetCertificationResult() = 0;

protected:
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nUsing8BitOnly;
	int m_nPartialDemosaic;
	std::string m_strLogHeader;
	std::string m_strLogData;
	std::string m_strVersion;
	TDATASPEC m_tDataSpec;
	T m_stSpec;
	TInspectRegionOffset m_tInspectRegionOffset;
	std::vector<double> m_vSaturationResult;
	bool m_bIsCertified;
};

template<typename T, typename TResult, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class CACMISShadingCommon
{
protected:
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	std::chrono::milliseconds m_elapsedTime;
	std::chrono::milliseconds m_startTimems;
	std::chrono::milliseconds m_endTimems;

	std::string m_strLogHeader;
	std::string m_strLogData;

protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<IShadingCommon<T, TResult, DataType, DataFormat, OutMode, SensorType, DemosaicMethod>> m_pMethod;
	CACMISShadingCommon() {}
	CACMISShadingCommon(const CACMISShadingCommon&) {}
#else
	IShadingCommon<T, TResult, DataType, DataFormat, OutMode, SensorType, DemosaicMethod>* m_pMethod;
	CACMISShadingCommon() : m_pMethod(NULL) {}
	CACMISShadingCommon(const CACMISShadingCommon&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISShadingCommon() {}

	inline bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, nDataFormat, nOutMode, nSensorType, nBlackLevel, nUsing8BitOnly, nPartialDemosaic, nDemosaicMethod);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(TBufferInfo& tBufferInfo, T& _Spec)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(tBufferInfo, _Spec);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(TFileInfo& tFileInfo, T& _Spec)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(tFileInfo, _Spec);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->InspectAlgorithm(pBuffer, nImageWidth, nImageHeight, _Spec, tDataSpec, nUsing8BitOnly, nPartialDemosaic);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline int GetInspectionRegionCount()
	{
		return m_pMethod->GetInspectionRegionCount();
	}
	inline const TResult* GetInspectionResult(int nIndex = 0, EROIPosition pos = eHorizontal)
	{
		return m_pMethod->GetInspectionResult(nIndex, pos);
	}
	inline bool InSpec(const T& _Spec)
	{
		return m_pMethod->InSpec(_Spec);
	}
	inline const RECT* GetInspectionROI(int nIndex = 0, EROIPosition pos = eHorizontal)
	{
		return m_pMethod->GetInspectionROI(nIndex, pos);
	}
	inline const char* GetLogHeader()
	{
		m_strLogHeader = "StarTime,EndTime,ElapsedTime,";
		m_strLogHeader += m_pMethod->GetLogHeader();
		return m_strLogHeader.c_str();
	}
	inline const char* GetLogData()
	{
		char temp[512];

		memset(temp, 0, sizeof(temp));

		std::time_t startTime_c = std::chrono::system_clock::to_time_t(m_startTime);
		struct tm* tmStartTime = std::localtime(&startTime_c);
		sprintf_s(temp, sizeof(temp), "\'%04d-%02d-%02d %02d:%02d:%02d.%03d,", tmStartTime->tm_year + 1900, tmStartTime->tm_mon + 1, tmStartTime->tm_mday, tmStartTime->tm_hour, tmStartTime->tm_min, tmStartTime->tm_sec, (int)m_startTimems.count());
		m_strLogData = temp;

		std::time_t endTime_c = std::chrono::system_clock::to_time_t(m_endTime);
		struct tm* tmEndTime = std::localtime(&endTime_c);
		sprintf_s(temp, sizeof(temp), "\'%04d-%02d-%02d %02d:%02d:%02d.%03d,", tmEndTime->tm_year + 1900, tmEndTime->tm_mon + 1, tmEndTime->tm_mday, tmEndTime->tm_hour, tmEndTime->tm_min, tmEndTime->tm_sec, (int)m_endTimems.count());
		m_strLogData += temp;

		sprintf_s(temp, sizeof(temp), "%lld,", m_elapsedTime.count());
		m_strLogData += temp;
		m_strLogData += m_pMethod->GetLogData();

		return m_strLogData.c_str();
	}
	inline const char* GetVersion()
	{
		return m_pMethod->GetVersion();
	}
	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const
	{
		return m_pMethod->SetInspectPosOffset(nStartOffsetX, nStartOffsetY, nEndOffsetX, nEndOffsetY);
	}
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const
	{
		return m_pMethod->SetInspectPosOffset(tInspectRegionOffset);
	}
	inline void Init() const
	{
		return m_pMethod->Init();
	}
	inline long long GetElapsedTime() const
	{
		return m_elapsedTime.count();
	}
	inline double GetSaturationResult(int nIndex) const
	{
		return m_pMethod->GetSaturationResult(nIndex);
	}
	inline bool GetCertificationResult()
	{
		return m_pMethod->GetCertificationResult();
	}
};
