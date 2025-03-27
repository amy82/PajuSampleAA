#pragma once

#include <LibACMISCommon\ACMISCommon.h>
#include <LibACMISImage\ACMISImageDef.h>
#include <LibACMISResolution\ACMISResolutionDef.h>
#include <LibACMISShading\ACMISShadingDef.h>
#include <LibACMISEtc\ACMISEtcDef.h>
#include <LibACMISCommon\InspectionErrorCode.h>
#include <LibACMISBlemish\ACMISBlemishDef.h>
#include <LibACMISDefect\ACMISDefectDef.h>
#include <LibACMISOpticalCenter\ACMISOpticalCenterDef.h>
#include <LibACMISNoise\ACMISSignalNoiseRatioDef.h>

#include <atlstr.h>

//#define FUNCTION_GROUT_ENABLE


// 검사 항목 공용체
#ifdef FUNCTION_GROUT_ENABLE
typedef enum _enumFunctionGroupType
{
	ENUM_FUNCTION_GROUP_BLEMISH,
	ENUM_FUNCTION_GROUP_RESOLUTION,
	ENUM_FUNCTION_GROUP_OPTICAL_CENTER,
	ENUM_FUNCTION_GROUP_SNR,
	ENUM_FUNCTION_GROUP_ETC,
	ENUM_FUNCTION_GROUP_DARK_TEST,
	ENUM_FUNCTION_GROUP_SHADING,
	MAX_COUNT_FUNCTION_GROUP_TYPE
} ENUM_FUNCTION_GROUP_TYPE;
#endif

typedef struct _tagParallelInpsectInput
{
	INSPECTION_INPUT* pInspectionInput;
	std::vector<TBufferInfo*> vBufferInfo;
} ParallelInpsectInput;


// 각 검사 항목별 결과 구조체 - 수정 필요
typedef struct _tagBlemishResult
{
	int nSingleDefectCount;
	vTBlobResult vBlobResult;
	int nDefectCount[EIMAGEREGION_MAX];
	TDefectResult tMaxResult[EIMAGEREGION_MAX];
	TCircleData tCircleData;
	RECT rtBorderLine;
	std::vector<double> vSaturationResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_BLEMISH;

typedef struct _tagDefectResult
{
	std::vector<int> vDefectCount;
	std::vector<int> vCoupletCount;
	std::vector<int> vClusterCount;
	std::vector<int> vClusterColorCount;
	std::vector<int> vLineCount;
	int nColumnFPNCount;
	std::vector< std::vector<TDefectResult> > vDefectResult;
	std::vector< std::vector<TBlobResult> > vCoupletResult;
	std::vector< std::vector<TBlobResult> > vClusterResult;
	std::vector< std::vector<TBlobResult> > vClusterColorResult;
	std::vector< std::vector<TDefectResult> > vLineResult;
	std::vector<TDefectResult> vColumnFPNResult;
	std::vector<TDefectResult> vMaxResult;
	TCircleSpecN tCircleSpec;
	TCircleData tCircleData;
	std::vector<double> vSaturationResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_DEFECT;

typedef struct _tagEIAJResult
{
	std::vector<TEIAJROIResult> vResult;
	std::vector<double> vSaturationResult;
	CDPoint ptRealCenter;
	double dRotation;
	std::vector<CDPoint> vFiducialMark;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_EIAJ;

typedef struct _tagSFRResult
{
	std::vector<TSFRROIResult> vResult;
	std::vector<double> vSaturationResult;
	std::vector<std::vector<int> > vDiffGroup;
	CDPoint ptRealCenter;
	double dRotation;
	bool bApplyChartInfo;
	std::vector< std::vector<THarrisCornerPoint> > vVertex;
	std::vector<TPatchSize> vSFRPatchSize;
	std::vector<CDPoint> vFiducialMark;
	int nSFRPatchElapsedTime;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_SFR;

typedef struct _tagOCResult
{
	DBPOINT ptOC;
	std::vector<DBPOINT> vSubOC;
	bool bSpecIn;
	std::vector<double> vSaturationResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_OC;

typedef struct _tagOCFiducialMarkResult
{
	DBPOINT ptOC;
	std::vector<DBPOINT> vSubOC;
	std::vector<CDRect> vMarkROI;
	std::vector<CDRect> vMarkRadiusBox;
	bool bSpecIn;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_OC_FIDUCIAL_MARK;

typedef struct _tagPatternNoiseResult
{
	std::vector<TPatternNoiseResult> vResult;
	std::vector<TSNRResult> vSNRResult;
	TSNRResult tMinResult;
	int nImageCount;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_PATTERN_NOISE;

typedef struct _tagSNRBWResult
{
	std::vector<TSNRBWResult> vResult;
	std::vector<TSNRResult> vSNRResult;
	TSNRResult tMinResult;
	int nImageCount;
	CDPoint ptRealCenter;
	double dRotation;
	std::vector<CDPoint> vFiducialMark;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_SNR_BW;

typedef struct _tagSNRNormResult
{
	std::vector<TSNRResult> vResult;
	TSNRResult tMinResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_SNR_NORM, RESULT_SNR_VNE;

typedef struct _tagDarkCurrentResult
{
	std::vector<TDarkCurrentResult> vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_DARK_CURRENT;

typedef struct _tagDarkNoiseResult
{
	std::vector<TDarkNoiseResult> vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_DARK_NOISE;

typedef struct _tagColorReproductionResult
{
	std::vector<TColorReproductionResult> vResult;
	CDPoint ptRealCenter;
	double dRotation;
	std::vector<CDPoint> vFiducialMark;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_COLOR_REPRODUCTION;

typedef struct _tagIRFilterResult
{
	std::vector<TIRFilterResult> vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_IR_FILTER;

typedef struct _tagColorIntensityResult
{
	std::vector<TColorIntensityResult> vResult;
	CDPoint ptRealCenter;
	double dRotation;
	std::vector<CDPoint> vFiducialMark;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_COLOR_INTENSITY;

typedef struct _tagFOVResult
{
	CDPoint ptCenter;
	CDPoint ptTilt;
	double dRotation;
	double dDFOV;
	double dHFOV;
	double dVFOV;
	double dDistortion;
	std::vector<CDRect> vFOVMarkROI;
	std::vector<CDRect> vDistortionMarkROI;
	std::vector<CDRect> vRotateMarkROI;
	std::vector<CDRect> vTiltMarkROI;
	std::vector<CDRect> vFOVMarkRadiusBox;
	std::vector<CDRect> vDistortionMarkRadiusBox;
	std::vector<CDRect> vRotateMarkRadiusBox;
	std::vector<CDRect> vTiltMarkRadiusBox;
	std::vector<CDPoint> vFOVMarkPoint;
	std::vector<CDPoint> vDistortionMarkPoint;
	std::vector<CDPoint> vRotateMarkPoint;
	std::vector<CDPoint> vTiltMarkPoint;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_FOV;

typedef struct _tagFlareResult
{
	std::vector<TFlareResult> vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_FLARE;

typedef struct _tagSaturationResult
{
	std::vector<TSaturationResult> vResult;
	std::vector<double> vAverageSaturation;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_SATURATION;

typedef struct _tagStrayLightResult
{
	std::vector<TStrayLightResult> vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_STRAY_LIGHT;

typedef struct _tagViewModeResult
{
	TViewModeResult tResult;
	CDPoint ptRealCenter;
	double dRotation;
	std::vector<CDPoint> vFiducialMark;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_VIEW_MODE;

typedef struct _tagRelativeIlluminationResult
{
	TRelativeIlluminationResultN tResult;
	std::vector<RECT> vROI;
	double dDiff_LR;
	double dDiff_UB;
	double dRIBalance;
	std::vector<int> vSpecIn;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_RELATIVE_ILLUMINATION;

typedef struct _tagRelativeIlluminationXResult
{
	TRelativeIlluminationResultX tCenterResult;
	std::vector<TRelativeIlluminationResultX> vResult;
	double dCornerVariation[4];
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_RELATIVE_ILLUMINATION_X;

typedef struct _tagRelativeUniformityResult
{
	TRelativeUniformityResult tResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_RELATIVE_UNIFORMITY;

typedef struct _tagColorUniformityResult
{
	bool bSpecIn;
	std::vector<TColorUniformityResultN> vResult;
	TColorUniformityResultN tMaxResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_COLOR_UNIFORMITY;

typedef struct _tagShadingUniformityResult
{
	TShadingUniformityResult tCenterResult;
	std::vector< std::vector<TShadingUniformityResult> > vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_SHADING_UNIFORMITY;

typedef struct _tagColorShadingResult
{
	bool bSpecIn;
	TColorShadingResult tResult;
	std::vector<RECT> vROI;
	std::vector < std::vector<double> > vRI;
	std::vector < std::vector<double> > vRIBalance;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_COLOR_SHADING;

typedef struct _tagColorSensitivityResult
{
	std::vector<TColorSensitivityResult> vResult;
	double dRG_Balance;
	double dBG_Balance;
	std::vector<int> vSpecIn;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_COLOR_SENSITIVITY;

typedef struct _tagLensShadingResult
{
	TLensShadingResult tCenterResult;
	std::vector<TLensShadingResult> vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_LENS_SHADING;

typedef struct _tagRelativeIlluminationCommonResult
{
	TRelativeIlluminationResult_Common tCenterResult;
	std::vector< std::vector<TRelativeIlluminationResult_Common> > vResult;
	double dCornerVariation;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_RELATIVE_ILLUMINATION_COMMON;

typedef struct _tagColorShadingCommonResult
{
	TColorShadingResult_Common tCenterResult;
	std::vector< std::vector<TColorShadingResult_Common> > vResult;
	TInspectRegionOffset tInspectRegionOffset;
} RESULT_COLOR_SHADING_COMMON;

typedef struct _tagCOMMON_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
} COMMON_EXTRA_SPEC, SHADING_EXTRA_SPEC, SNR_EXTRA_SPEC;

typedef struct _tagBLEMISH_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	ESaturationMethod eSaturationMethod;
	int nUsingMask;
	CString strMaskFilePath;
} BLEMISH_EXTRA_SPEC;

typedef struct _tagDARK_TEST_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	int nTestInspectType;
	TDefectOffset tDefectOffset;
	ESaturationMethod eSaturationMethod;
	TCircleSpecN tCircleSpec;
	int nUsingMask;
	CString strMaskFilePath;
} DARK_TEST_EXTRA_SPEC;

typedef struct _tagRESOLUTION_SFR_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	TFiducialMarkSpecN tFiducialMarkSpec;
	std::vector<TSFRROIInfo> vROIInfoBag;
	std::vector<TSFRROIPatchInfo> vROIPatchInfo;
	std::vector<TPatchInfo> vSFRPatchInfo;
	int isCompensateMC;
	int isCompensateRotate;
	int nFMPartialDemosaic;
	int nPatchPartialDemosaic;
	TCircleSpecN tCircleSpec;
} RESOLUTION_SFR_EXTRA_SPEC;

typedef struct _tagRESOLUTION_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	TFiducialMarkSpecN tFiducialMarkSpec;
	int isCompensateMC;
	int isCompensateRotate;
	int nFMPartialDemosaic;
} RESOLUTION_EXTRA_SPEC, SNR_BW_EXTRA_SPEC, ETC_EXTRA_SPEC;

typedef struct _tagOPTICAL_CENTER_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	int nTestInspectType;
} OPTICAL_CENTER_EXTRA_SPEC;

typedef struct _tagETC_FOV_EXTRA_SPEC
{
	TInspectRegionOffset tInspectRegionOffset;
	TFiducialMarkSpecN tFiducialMarkSpec;
	TChartSpec tChartSpec;
	bool bEnableFOV;
	bool bEnableDistortion;
	bool bEnableRotate;
	bool bEnableTilt;
} ETC_FOV_EXTRA_SPEC;
