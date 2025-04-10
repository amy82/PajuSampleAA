#pragma once

#include <LibACMISCommon\ACMISCommon.h>


#define MAX_SFR_LIMIT					(100)

#define WRONG_CHART_ALIGN_SFR_VALUE		(-100)
#define WRONG_EDGE_SLOPE_SFR_VALUE		(-101)
#define WRONG_AVERAGE_SFR_VALUE			(-102)
#define WRONG_ROI_WIDTH_VALUE			(-103)
#define WRONG_ROI_HEIGHT_VALUE			(-104)
#define WRONG_FREQUENCY_VALUE			(-105)
#define WRONG_SFR_VALUE					(-106)
#define FAILED_TO_INITIALIZE_BUFFER		(-107)
#define WRONG_ROI_RANGE_VALUE			(-108)
#define WRONG_PARAMETER_VALUE			(-109)
#define WRONG_EDGE_DIR_SFR_VALUE		(-110)


#define	ROI_LEFT	(0)
#define	ROI_TOP		(1)
#define	ROI_RIGHT	(2)
#define	ROI_BOTTOM	(3)

typedef unsigned int VOIDTYPE;


typedef enum _ESFRAlgorithmType
{
	ESFRAlgorithm_ISO12233,				///< ISO12233 algorithm type
	ESFRAlgorithm_RHOMBUS, 				///< RHOMBUS algorithm type
	ESFRAlgorithm_LGIT_ISO, 			///< Modified ISO12233 algorithm type
	ESFRAlgorithm_VNE,
	ESFRAlgorithm_Mobis,
	ESFRAlgorithm_Tesla_Trinity
} ESFRAlgorithmType;

typedef enum _ESFRAlgorithmMethod
{
	ESFRMethod_Freq2SFR,				///< Calculate SFR value using Spatial Frequency
	ESFRMethod_SFR2Freq					///< Calculate Spatial Frequency using SFR value
} ESFRAlgorithmMethod;

typedef enum _ESFRFrequencyUnit
{
	ESFRFreq_CyclePerPixel,
	ESFRFreq_LinePairPerMilliMeter,
	ESFRFreq_LineWidthPerPictureHeight
} ESFRFrequencyUnit;

typedef enum _EEIAJAlgorithmType
{
	EEIAJAlgorithm_GETLINEMTF,			///< GETLINEMTF algorithm type
	ESFRAlgorithm_GETSOMTHING,			///< GETSOMTHING algorithm type
} EEIAJAlgorithmType;

typedef enum _EResolutionClass
{
	EResolutionClass_A_PASS,			///< All PASS
	EResolutionClass_B_PASS,			///< Conditional PASS
	EResolutionClass_RESOLUTION_FAIL,	///< FAIL
	EResolutionClass_DELTA_FAIL			///< Delta fail
} EResolutionClass;

typedef enum _EAlignType
{
	EAlign_DOT,
	EAlign_CROSSHAIR
}EAlignType;

typedef enum _EChartAlignStatus
{
	EChartAlign_NORMAL,
	EChartAlign_WRONG
} EChartAlignStatus;

typedef struct _DRANGE
{
	double min;
	double max;

	struct _DRANGE() { min = 0.0; max = 0.0; }
} DRANGE;

typedef enum _ESFRDeltaAlgorithmType
{
	ESFRDelta_Diff,
	ESFRDelta_Ratio
} ESFRDeltaAlgorithmType;

typedef enum _EDistortionAlgorithmType
{
	EDistortion_RealRatio,
	EDistortion_TV,
	EDistortion_SMIA
} EDistortionAlgorithmType;

typedef enum _EFindMarkROIType
{
	EMark_CIRCLE,
	EMark_RECT,
	EMark_SHITOMASHI
} EFindMarkROIType;

typedef struct _TFindROIResult
{
	CDPoint	LT;
	CDPoint	RT;
	CDPoint	LB;
	CDPoint	RB;
}TFindROIResult;

typedef enum _EMarkROIType
{
	EFixed_ROI,
	ERelative_ROI,
	EAuto_ROI
} EMarkROIType;

#define MAX_RESOLUTION_ROI_COUNT			(80)
#define MAX_FREQUENCY_NUM					(3)//(1)
#define MAX_FIDUCIAL_MARK_COUNT				(4)
#define MAX_SUB_FIDUCIAL_MARK_COUNT			(2)
#define UNDEFINED_RESOLUTION_VALUE			(9999)

typedef enum _EFOVAlgorithmMethod
{
	FOV_METHOD_MODULE_DISTANCE,
	FOV_METHOD_EFL,
	FOV_METHOD_MOBIS_MOTIONAL,
	FOV_METHOD_SHM_CORNER,
	FOV_METHOD_SHM_CIRCLE_H150,
	FOV_METHOD_FORD_L3,
	FOV_METHOD_FIGURE_AI,
} EFOVAlgorithmMethod;
#define FOV_METHOD_PIXEL_COUNT FOV_METHOD_MOBIS_MOTIONAL

typedef enum _EFiducialMarkType
{
	FIDUCIALMARKTYPE_DOT,				// Fiducial Mark Num = 4
	FIDUCIALMARKTYPE_CROSSDOT,			// Fiducial Mark Num = 4
	FIDUCIALMARKTYPE_GRID,				// Fiducial Mark Num = 9
	FIDUCIALMARKTYPE_MOBIS_MOTIONAL,	// Fiducial Mark Num = 2(H) + 2(V)
	FIDUCIALMARKTYPE_SINGLE,			// Fiducial Mark Num = 1
	FIDUCIALMARKTYPE_SHM_CORNER,		// Fiducial Mark Num = 16(H100), 14(H150)
	FIDUCIALMARKTYPE_SHM_CIRCLE,		// Fiducial Mark Num = 8
	FIDUCIALMARKTYPE_FORD_L3,			// Fiducial Mark Num 
	FIDUCIALMARKTYPE_MAX
} EFiducialMarkType;
#define FIDUCIALMARKTYPE_LINE FIDUCIALMARKTYPE_MOBIS_MOTIONAL

typedef enum _FIDUCIALMARK_INSPECT_ITEM
{
	FIDUCIALMARK_INSPECT_FOV = 0x01,
	FIDUCIALMARK_INSPECT_DISTORTION = 0x02,
	FIDUCIALMARK_INSPECT_ROTATE = 0x04,
	FIDUCIALMARK_INSPECT_TILT = 0x08,
	FIDUCIALMARK_INSPECT_OC = 0x10,
	FIDUCIALMARK_INSPECT_ALL = 0x1F,
	FIDUCIALMARK_INSPECT_MAX = 0x20
} FIDUCIALMARK_INSPECT_ITEM;

typedef struct _TFiducialMarkInfo
{
	int nInspectItem;			/// 검사 종류. FIDUCIALMARK_INSPECT_ITEM 열거형
	int nAlgorithmIndex;		/// 알고리즘 인덱스 (EFOVAlgorithmMethod 등 검사별 알고리즘 열거형에 따름)
	double dDistanceXFromCenter; ///< pixel or relative position of main fiducial mark
	double dDistanceYFromCenter; ///< pixel or relative position of main fiducial mark
	int nROIBoxSize;
	int nMaxROIBoxSize;
	double dRadius;
	double dRealGapX; ///< cm, between horizontal bases
	double dRealGapY;  ///< cm between vertical bases
	int nFiducialMarkType;
	double dModuleChartDistance; ///< distance between module and chart
} TFiducialMarkInfo;

typedef struct _TFiducialMarkInfoN
{
	int nFiducialMarkType; /// EFiducialMarkType의 멤버(DOT, CROSSDOT,...)
	int nInspectItem;      /// 검사 종류. FIDUCIALMARK_INSPECT_ITEM 열거형
	int nAlgorithmIndex;   /// 알고리즘 인덱스 (EFOVAlgorithmMethod 등 검사별 알고리즘 열거형에 따름)
	double* pVecParamData; /// 알고리즘에 추가적으로 필요한 값들은 담은 벡터의 시작 주소
	size_t  nVecParamSize; /// 알고리즘에 추가적으로 필요한 값들을 담은 벡터의 크기

	double dRealGapX; ///< cm, between horizontal bases
	double dRealGapY;  ///< cm between vertical bases

	double dModuleChartDistance; ///< distance between module and chart
	double dPixelSize; /// Pixel size of Image Sensor
	double dEFL; /// Effective Focal Length of Lens

	double dRadius;
	double dBinaryThreshold; /// threshold for Binary of image
	double dMaxDeviation; /// maximum deviation from ROI center
	int nROIBoxSize;
	int nMaxROIBoxSize;
} TFiducialMarkInfoN;

typedef struct _TFiducialMarkSpec
{
	int nUsedFixedROI; ///< for SFR Value, 0: Relative ROI, 1:Fixed ROI(read from csv file), 2:Auto ROI
	int nUseMachine;   ///< True if the Machine finds the Fiducial Mark

	// Fiducial Mark Info
	TFiducialMarkInfoN stFiducialMark;
	std::vector<POINT> vRefFiducialMark;

	// Spec
	double dXTiltSpecMin;
	double dXTiltSpecMax;
	double dYTiltSpecMin;
	double dYTiltSpecMax;
	double dHFOVSpecMIn;
	double dHFOVSpecMax;
	double dVFOVSpecMIn;
	double dVFOVSpecMax;
	double dDFOVSpecMIn;
	double dDFOVSpecMax;
	double dRotationSpecMin;
	double dRotationSpecMax;
	double dDistortionSpecMin;
	double dDistortionSpecMax;

	// Offset
	double dTiltXOffset;
	double dTiltYOffset;
	double dHFOVOffset;
	double dVFOVOffset;
	double dDFOVOffset;
	double dRotateOffset;
	double dDistortionOffset;
} TFiducialMarkSpec;

#define FIDUCIAL_MARK_SPEC_FLAG_VERSION_MAJOR		1
#define FIDUCIAL_MARK_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_FIDUCIAL_MARK
{
	FIDUCIAL_MARK_USED_FIXED_ROI,
	FIDUCIAL_MARK_USE_MACHINE,

	FIDUCIAL_MARK_DISTANCE_X_FROM_CENTER,
	FIDUCIAL_MARK_DISTANCE_Y_FROM_CENTER,
	FIDUCIAL_MARK_ROI_BOX_SIZE,
	FIDUCIAL_MARK_MAX_ROI_BOX_SIZE,
	FIDUCIAL_MARK_RADIUSs,
	FIDUCIAL_MARK_REAL_GAP_X,
	FIDUCIAL_MARK_REAL_GAP_Y,
	FIDUCIAL_MARK_REAL_SUB_GAP_X,
	FIDUCIAL_MARK_REAL_SUB_GAP_Y,
	FIDUCIAL_MARK_MODULE_CHART_DISTANCE,
	FIDUCIAL_MARK_DISTORTION_ALGORITHM_TYPE,
	FIDUCIAL_MARK_BINARY_THRESHOLD,
	FIDUCIAL_MARK_MAX_DEVIATION,
	FIDUCIAL_MARK_PIXEL_SIZE,
	FIDUCIAL_MARK_EFL,

	FIDUCIAL_MARK_INFO_COUNT,

	FIDUCIAL_MARK_X_TILT_SPEC_MIN,
	FIDUCIAL_MARK_X_TILT_SPEC_MAX,
	FIDUCIAL_MARK_Y_TILT_SPEC_MIN,
	FIDUCIAL_MARK_Y_TILT_SPEC_MAX,
	FIDUCIAL_MARK_HFOV_SPEC_MIN,
	FIDUCIAL_MARK_HFOV_SPEC_MAX,
	FIDUCIAL_MARK_VFOV_SPEC_MIN,
	FIDUCIAL_MARK_VFOV_SPEC_MAX,
	FIDUCIAL_MARK_DFOV_SPEC_MIN,
	FIDUCIAL_MARK_DFOV_SPEC_MAX,
	FIDUCIAL_MARK_ROTATE_SPEC_MIN,
	FIDUCIAL_MARK_ROTATE_SPEC_MAX,
	FIDUCIAL_MARK_DISTORTION_SPEC_MIN,
	FIDUCIAL_MARK_DISTORTION_SPEC_MAX,

	FIDUCIAL_MARK_TILT_X_OFFSET,
	FIDUCIAL_MARK_TILT_Y_OFFSET,
	FIDUCIAL_MARK_HFOV_OFFSET,
	FIDUCIAL_MARK_VFOV_OFFSET,
	FIDUCIAL_MARK_DFOV_OFFSET,
	FIDUCIAL_MARK_ROTATE_OFFSET,
	FIDUCIAL_MARK_DISTORTION_OFFSET,

	FIDUCIAL_MARK_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_FIDUCIAL_MARK;

#define FIDUCIAL_MARK_ROI_FLAG_VERSION_MAJOR		1
#define FIDUCIAL_MARK_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_FIDUCIAL_MARK
{
	FIDUCIAL_MARK_X,
	FIDUCIAL_MARK_Y,
	FIDUCIAL_MARK_SHAPE,

	FIDUCIAL_MARK_ROI_FLAG_MAX_COUNT
} ROI_FLAG_FIDUCIAL_MARK;

#define FIDUCIAL_MARK_USE_ROI_FLAG_VERSION_MAJOR		1
#define FIDUCIAL_MARK_USE_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_FIDUCIAL_MARK_USE
{
	FIDUCIAL_MARK_USE_X,
	FIDUCIAL_MARK_USE_Y,
	FIDUCIAL_MARK_USE_SHAPE,
	FIDUCIAL_MARK_USE_INSPECT_ITEM,

	FIDUCIAL_MARK_USE_ROI_FLAG_MAX_COUNT
} ROI_FLAG_FIDUCIAL_MARK_USE;

#define FIDUCIAL_MARK_INFO_FLAG_VERSION_MAJOR		1
#define FIDUCIAL_MARK_INFO_FLAG_VERSION_MINOR		0
typedef enum _FLAG_FIDUCIAL_MARK_INFO
{
	FIDUCIAL_MARK_INFO_PSZ_CHART_TYPE,
	FIDUCIAL_MARK_INFO_NUM,
	FIDUCIAL_MARK_INFO_TYPE,

	FIDUCIAL_MARK_INFO_FLAG_MAX_COUNT
} FLAG_FIDUCIAL_MARK_INFO;

typedef struct _TFiducialMarkSpecM
{
	int nUsedFixedROI; ///< for SFR Value, 0: Relative ROI, 1:Fixed ROI(read from csv file), 2:Auto ROI
	int nUseMachine;   ///< True if the Machine finds the Fiducial Mark

	// Fiducial Mark Info
	std::vector<TFiducialMarkInfoN> vFiducialMarkInfo;
	std::vector<TFiducialMarkUse> vRefFiducialMark;

	// Spec
	double dXOCSpecMin;
	double dXOCSpecMax;
	double dYOCSpecMin;
	double dYOCSpecMax;
	double dXTiltSpecMin;
	double dXTiltSpecMax;
	double dYTiltSpecMin;
	double dYTiltSpecMax;
	double dHFOVSpecMIn;
	double dHFOVSpecMax;
	double dVFOVSpecMIn;
	double dVFOVSpecMax;
	double dDFOVSpecMIn;
	double dDFOVSpecMax;
	double dRotationSpecMin;
	double dRotationSpecMax;
	double dDistortionSpecMin;
	double dDistortionSpecMax;

	// Offset
	double dOCXOffset;
	double dOCYOffset;
	double dTiltXOffset;
	double dTiltYOffset;
	double dHFOVOffset;
	double dVFOVOffset;
	double dDFOVOffset;
	double dRotateOffset;
	double dDistortionOffset;

	_TFiducialMarkSpecM() : dOCXOffset(0.0), dOCYOffset(0.0), dTiltXOffset(0.0), dTiltYOffset(0.0), dHFOVOffset(1.0), dVFOVOffset(1.0), dDFOVOffset(1.0), dRotateOffset(0.0), dDistortionOffset(0.0)
	{
	}
} TFiducialMarkSpecM;

typedef struct _TFiducialMarkSpecN
{
	int nUsedFixedROI; ///< for SFR Value, 0: Relative ROI, 1:Fixed ROI(read from csv file), 2:Auto ROI
	int nUseMachine;   ///< True if the Machine finds the Fiducial Mark

	// Fiducial Mark Info
	TFiducialMarkInfoN stFiducialMark;
	std::vector<TFiducialMarkType> vRefFiducialMark;

	// Spec
	double dXOCSpecMin;
	double dXOCSpecMax;
	double dYOCSpecMin;
	double dYOCSpecMax;
	double dXTiltSpecMin;
	double dXTiltSpecMax;
	double dYTiltSpecMin;
	double dYTiltSpecMax;
	double dHFOVSpecMIn;
	double dHFOVSpecMax;
	double dVFOVSpecMIn;
	double dVFOVSpecMax;
	double dDFOVSpecMIn;
	double dDFOVSpecMax;
	double dRotationSpecMin;
	double dRotationSpecMax;
	double dDistortionSpecMin;
	double dDistortionSpecMax;

	// Offset
	double dOCXOffset;
	double dOCYOffset;
	double dTiltXOffset;
	double dTiltYOffset;
	double dHFOVOffset;
	double dVFOVOffset;
	double dDFOVOffset;
	double dRotateOffset;
	double dDistortionOffset;

	_TFiducialMarkSpecN() : dOCXOffset(0.0), dOCYOffset(0.0), dTiltXOffset(0.0), dTiltYOffset(0.0), dHFOVOffset(1.0), dVFOVOffset(1.0), dDFOVOffset(1.0), dRotateOffset(0.0), dDistortionOffset(0.0)
	{
	}
} TFiducialMarkSpecN;

#define RESULT_FIDUCIAL_MARK_VERSION_MAJOR		1
#define RESULT_FIDUCIAL_MARK_VERSION_MINOR		0
typedef enum _RESULT_FLAG_FIDUCIAL_MARK
{
	FIDUCIAL_MARK_RESULT_DFOV,
	FIDUCIAL_MARK_RESULT_HFOV,
	FIDUCIAL_MARK_RESULT_VFOV,
	FIDUCIAL_MARK_RESULT_ROTATION,
	FIDUCIAL_MARK_RESULT_DISTORTION,
	FIDUCIAL_MARK_RESULT_TILT_X,
	FIDUCIAL_MARK_RESULT_TILT_Y,
	FIDUCIAL_MARK_RESULT_REAL_CENTER_X,
	FIDUCIAL_MARK_RESULT_REAL_CENTER_Y,

	FIDUCIAL_MARK_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_FIDUCIAL_MARK;

typedef struct _TChartSpec
{
	int dbufferType;			 ///< buffer type define

	// align info
	TFiducialMarkInfoN stMainFiducialMark;
	TFiducialMarkInfoN stSubFiducialMark;

	// spec.
	DRANGE  rSFRSpec;
	DRANGE	rXOCSpec; ///< chart x spec(min, max)
	DRANGE	rYOCSpec; ///< chart y spec(min, max)
	DRANGE	rXTiltSpec; ///< chart x tilt spec(min, max)
	DRANGE	rYTiltSpec; ///< chart y tilt spec(min, max)
	DRANGE	rDFOVSpec; ///< Diagonal FOV spec(min, max)
	DRANGE	rHFOVSpec; ///< Horizontal FOV spec(min, max)
	DRANGE	rVFOVSpec; ///< Vertical FOV spec(min, max)
	DRANGE	rRotationSpec; ///< chart rotation spec(min, max)
	DRANGE	rDistortionSpec; ///< chart Distortion spec(min,max)

	// Offset
	double dHFOVOffset;
	double dVFOVOffset;
	double dDFOVOffset;
	double dRotateOffset;
	double dTiltXOffset;
	double dTiltYOffset;
	double dOCXOffset;
	double dOCYOffset;
	double dDistortionOffset;

	/// frequency(Nyquest) lists..
	double	dCriteria[MAX_FREQUENCY_NUM];

	/// Pixel Size
	double dPixelSize; ///< Unit: um

	/// SFR Method
	int nAlgorithmMethod; ///< algorithm method such as Caculate SFR using spatial frequency, Caculate spatial frequecy using SFR value

	/// Frequency Unit
	int nFreqUnit; ///< SFR spatial frequency unit such as C/P, lp/mm, LW/PH

	/// ROI detail info - full path name(csv file)
	char* strDetailInfoPath;
	char* strDetailDeltaSpecInfoPath;

	int nAlgorithmType;	///< algorithm info like SFR_ISO12233, SFR_ROHMBUS...
	int nDeltaAlgorithmType; ///< algorithm for calculation differece value among corner resolution values
	int nMTFavgLineNum; ///< Number of Average MTF Value for EIAJ ROI's

	POINT ptDisplayXY; ///< Result display position
	int nFontSize; ///< Result display font size
	int nDisplayGap; ///< Result display line gap
	int nDisplayGapFromROI; ///< Result display result gap from SFR ROI

	int nUsedFixedROI; ///< for SFR Value, 0: Relative ROI, 1:Fixed ROI(read from csv file), 2:Auto ROI
	int nUseMachine;   // /< True if the Machine finds the Fiducial Mark
	int nROIWidth;		///< Only Use Auto ROI
	int nROIHeight;		///< Only Use Auto ROI
	int nDisplayROI;	///< Only Use Auto ROI

	int nCompensationMC; // mechanical OC corretion
	int nCompensationRotate; // Rotation correction

	int nSearchMaxPoxStep;
	int nUseFineSearch;
	int nSearchExclusionSize;

	double dGamma;

	char* strFiducialMarkInfoPath;

	// Inspection Algorithm
	int nFOVAlgorithmMethod; // EFOVAlgorithmMethod
	int nDistortionAlgorithmMethod; // EDistortionAlgorithmType

	_TChartSpec() : strDetailInfoPath(NULL), strDetailDeltaSpecInfoPath(NULL), nDeltaAlgorithmType(0), nAlgorithmType(0), strFiducialMarkInfoPath(NULL),
		dOCXOffset(0.0), dOCYOffset(0.0), dTiltXOffset(0.0), dTiltYOffset(0.0), dHFOVOffset(1.0), dVFOVOffset(1.0), dDFOVOffset(1.0), dRotateOffset(0.0), dDistortionOffset(0.0)
	{
		memset(&stMainFiducialMark, 0, sizeof(TFiducialMarkInfoN));
		memset(&stSubFiducialMark, 0, sizeof(TFiducialMarkInfoN));
	}
} TChartSpec;

// EIAJ CSV
/* Old */ //number	name	signX	signY	direction  TxtPosition	threshold	relativeX	relativeY	ROI width	ROI height
/* New */ //number	name	Left	Top		Right		Bottom		direction  TxtPosition	threshold	relativeX	relativeY	ROI width	ROI height
// average_flag	average_index0	average_index1	average_index2	average_index3
typedef struct _TEIAJROIInfo
{
	int number;
	//char name[64];
	//int signX;
	//int signY;
	//int nLeft;
	//int nTop;
	//int nRight;
	//int nBottom;
	//int ROIwidth;
	//int ROIheight;
	TROIDataCommon tROIData;
	int nRoiDirection;
	int nTxtPosition;
	int nThresholdVlaue;
	double relativeX;
	double relativeY;
	double offset;
	int averageCount;
	int averageIndex[MAX_RESOLUTION_ROI_COUNT];
	int nMTFspec;
	int nSharpspec;
	int nMaxResolutionValue;
	int nMinResolutionValue;
	int nValidMTFguaranteeMargin;
} TEIAJROIInfo;

// SFR CSV
//number	name	signX	signY	direction  TxtPosition	threshold	relativeX	relativeY	ROI width	ROI height
// average_flag	average_index0	average_index1	average_index2	average_index3
typedef struct _TSFRROIInfo
{
	int number;
	//char name[64];
	//int signX;
	//int signY;
	//int ROIwidth;
	//int ROIheight;
	TROIDataCommon tROIData;
	int direction;
	int txtPosition;
	double threshold;
	double relativeX;
	double relativeY;
	double freq[MAX_FREQUENCY_NUM]; // for Freq2SFR method
	double sfr; // for SFR2Freq method
	int freqUnit;
	double offset;
	bool bUseCosineCorrection;
	int nPolyFitOrder;
	int averageCount;
	int averageIndex[MAX_RESOLUTION_ROI_COUNT];
	int nDiffIndex;
} TSFRROIInfo;

typedef struct _TDeltaSFRspec
{
	int nNumber;
	double dLowLimit;
	double dHighLimit;
	bool bEnablePassFail;
	int nGrade;
	int nDeltaROIcount;
	int nDeltaROIIndex[MAX_RESOLUTION_ROI_COUNT];
	bool bPassFailResult;
	double dDeltaSFR;
} TDeltaSFRspec;

#define RESULT_SFR_VERSION_MAJOR		1
#define RESULT_SFR_VERSION_MINOR		0
typedef enum _RESULT_FLAG_SFR
{
	SFR_RESULT_SFR1,
	SFR_RESULT_SFR2,
	SFR_RESULT_SFR3,
	SFR_RESULT_ROI_LEFT,
	SFR_RESULT_ROI_TOP,
	SFR_RESULT_ROI_RIGHT,
	SFR_RESULT_ROI_BOTTOM,
	SFR_RESULT_CENTER_X,
	SFR_RESULT_CENTER_Y,
	SFR_RESULT_EDGE_ANGLE,
	SFR_RESULT_CHART_STATUS,

	SFR_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_SFR;

typedef struct _TSFRROIResult
{
	CDPoint ptCenter; ///< Found edge center in ROI
	CDRect rtROI; ///< ROI of calculating Resolution
	double dFinalResult[MAX_FREQUENCY_NUM]; ///< the final result lists per frequency
	double dEdgeAngle;
	double dSaturation;
	EChartAlignStatus eChartStatus; ///< Chart status. if this value is WRONG_CHART, FinalResult is WRONG value.

	void Init()
	{
		dEdgeAngle = 0.0;
		dSaturation = 0.0;
		eChartStatus = EChartAlign_NORMAL;
		for(int i = 0; i < MAX_FREQUENCY_NUM; i++)
			dFinalResult[i] = 0.0;
	}
} TSFRROIResult;

typedef struct _TSFRConfig
{
	int nMaxROIWidth;
	int nMaxROIHeight;
	double dMaxEdgeAngle;
	double dPixelSize;
	ESFRAlgorithmType eAlgorithmType;
	ESFRAlgorithmMethod eAlgorithmMethod;
	ESFRFrequencyUnit eFrequencyUnit;
} TSFRConfig;

#define SFR_SPEC_FLAG_VERSION_MAJOR		1
#define SFR_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_SFR
{
	SFR_ALGORITHM_TYPE,
	SFR_ALGORITHM_METHOD,
	SFR_FREQUENCY_UNIT,
	SFR_MAX_ROI_WIDTH,
	SFR_MAX_ROI_HEIGHT,
	SFR_MAX_EDGE_ANGLE,
	SFR_PIXEL_SIZE,
	SFR_GAMMA,

	SFR_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_SFR;

#define SFR_ROI_FLAG_VERSION_MAJOR		1
#define SFR_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_SFR
{
	SFR_ROI_TYPE,
	SFR_ROI_DATA1,
	SFR_ROI_DATA2,
	SFR_ROI_DATA3,
	SFR_ROI_DATA4,
	SFR_ROI_OFFSET,
	SFR_ROI_MIN_THRESHOLD,
	SFR_ROI_MAX_THRESHOLD,
	SFR_ROI_EDGE_DIRECTION,
	SFR_ROI_FREQUENCY,
	SFR_ROI_FREQUENCY2,
	SFR_ROI_FREQUENCY3,
	SFR_ROI_SFR,
	SFR_ROI_COSINE_CORRECTION,
	SFR_ROI_POLY_FIT_ORDER,
	SFR_ROI_DIFF_GROUP_INDEX,

	SFR_ROI_FLAG_MAX_COUNT
} ROI_FLAG_SFR;

typedef struct _TSFRSpec
{
	ESFRDeltaAlgorithmType eSFRDeltaAlgorithmType;
	TSFRConfig tSFRConfig;
	TROIData tROI;
	int *dEdgeDir;
	double *dFrequency;
	double *dSFR;
	double *dThreshold;
	double dGamma;
	TDeltaSFRspec *tDelataSpec;
} TSFRSpec;

typedef struct _TSFRROIPatchInfo
{
	int nPatchIndex;
	int nVertex[2];
	double dRatio;
} TSFRROIPatchInfo;

typedef struct _TEIAJConfig
{
	EEIAJAlgorithmType eAlgorithmType;
	int nMTFavgLineNum;
} TEIAJConfig;

typedef struct _TEIAJROISpec
{
	int		nMTFspec;
	float	fDeltaSpec;
	int		nSharpSpec;

	int		nMinResolutionValue;
	int		nMaxResolutionValue;
	int		nValidMTFguaranteeMargin;

	_TEIAJROISpec() : nMTFspec(0), fDeltaSpec(0.0f), nSharpSpec(0), nMinResolutionValue(0), nMaxResolutionValue(0), nValidMTFguaranteeMargin(0)
	{
	}
} TEIAJROISpec;

#define RESULT_EIAJ_VERSION_MAJOR		1
#define RESULT_EIAJ_VERSION_MINOR		0
typedef enum _RESULT_FLAG_EIAJ
{
	EIAJ_RESULT_RESOLUTION_VALUE,
	EIAJ_RESULT_THRESHOLD_AXIS,
	EIAJ_RESULT_OFFSET,
	EIAJ_RESULT_ROI_DIRECTION,
	EIAJ_RESULT_AVERAGE_MTF,
	EIAJ_RESULT_RESOLUTION_AXIS,
	EIAJ_RESULT_ROI_LEFT,
	EIAJ_RESULT_ROI_TOP,
	EIAJ_RESULT_ROI_RIGHT,
	EIAJ_RESULT_ROI_BOTTOM,
	EIAJ_RESULT_CENTER_X,
	EIAJ_RESULT_CENTER_Y,
	EIAJ_RESULT_CHART_STATUS,

	EIAJ_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_EIAJ;

typedef struct _TEIAJROIResult
{
	POINT	ptCenter;
	RECT	rtROI;
	BOOL	bPass;
	int		nThresholdAxis;
	int		nResolutionValue;
	double	dOffset;

	TEIAJROISpec tROISpec;

	int		nRoiDirection;

	double	dAvgMTF;

	int		nResolutionAxis;
	EChartAlignStatus eChartStatus;

	void Init()
	{
		eChartStatus = EChartAlign_NORMAL;
		ptCenter.x = 0;
		ptCenter.y = 0;
		rtROI.left = 0;
		rtROI.right = 0;
		rtROI.top = 0;
		rtROI.bottom = 0;
		tROISpec.nMTFspec = 50;
		tROISpec.fDeltaSpec = 0.0f;
		tROISpec.nSharpSpec = 50;
		tROISpec.nMinResolutionValue = 0;
		tROISpec.nMaxResolutionValue = 0;
		tROISpec.nValidMTFguaranteeMargin = 0;
	}

	_TEIAJROIResult() : bPass(FALSE), nThresholdAxis(0), nResolutionValue(0),
		nRoiDirection(0), dAvgMTF(0.0), nResolutionAxis(0), eChartStatus(EChartAlign_NORMAL)
	{
		Init();
	}
} TEIAJROIResult;

#define EIAJ_SPEC_FLAG_VERSION_MAJOR		1
#define EIAJ_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_EIAJ
{
	EIAJ_ALGORITHM_TYPE,
	EIAJ_MTF_AVG_LINE_NUM,

	EIAJ_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_EIAJ;

#define EIAJ_ROI_FLAG_VERSION_MAJOR		1
#define EIAJ_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_EIAJ
{
	EIAJ_ROI_TYPE,
	EIAJ_ROI_DATA1,
	EIAJ_ROI_DATA2,
	EIAJ_ROI_DATA3,
	EIAJ_ROI_DATA4,
	EIAJ_ROI_OFFSET,
	EIAJ_ROI_MIN_THRESHOLD,
	EIAJ_ROI_MAX_THRESHOLD,
	EIAJ_ROI_DIRECTION,
	EIAJ_ROI_MTF_SPEC,
	/*EIAJ_ROI_DELTA_SPEC,*/
	/*EIAJ_ROI_SHARP_SPEC,*/
	EIAJ_ROI_MIN_RESOLUTION,
	EIAJ_ROI_MAX_RESOLUTION,
	EIAJ_ROI_VALID_MTF_GUARANTEE_MARGIN,

	EIAJ_ROI_FLAG_MAX_COUNT
} ROI_FLAG_EIAJ;

typedef struct _TEIAJSpec
{
	TEIAJConfig tConfig;
	TEIAJROISpec *tROISpec;
	TROIData tROI;
	int *nDirection;
	int *nThreshold;
} TEIAJSpec;

typedef struct _TSFRResolutionResult
{
	EResolutionClass eClass; ///< Class Level
	/// status string. PASS is '1', FAIL is '0'. dash(-) means separator of field ex) "1111-0111"
	char strStatus[MAX_FREQUENCY_NUM][128];
	std::vector<TSFRROIResult> vROIResult;
	int nDeltaResult;
	double dMaxDeltaSFR;
	int nMaxDeltaSFRgrade;

	void Init()
	{
		eClass = EResolutionClass_RESOLUTION_FAIL;
		for(int i = 0; i < MAX_FREQUENCY_NUM; i++)
			*(strStatus[i]) = '\0';
		std::for_each(vROIResult.begin(), vROIResult.end(), [](TSFRROIResult& n) { n.Init(); });
	}

	_TSFRResolutionResult() : nDeltaResult(0), dMaxDeltaSFR(0.0), nMaxDeltaSFRgrade(0) { Init(); }
} TSFRResolutionResult;

typedef struct _TEIAJResolutionResult
{
	EResolutionClass eClass; ///< Class Level
	/// status string. PASS is '1', FAIL is '0'. dash(-) means separator of field ex) "1111-0111"
	char strStatus[128];
	int nMaxROINum;
	std::vector <TEIAJROIResult> pROIResult;

	void Init()
	{
		eClass = EResolutionClass_RESOLUTION_FAIL;
			*(strStatus) = '\0';
		nMaxROINum = static_cast<int>(pROIResult.size());
		std::for_each(pROIResult.begin(), pROIResult.end(), [](TEIAJROIResult& n) { n.Init(); } );
	}
} TEIAJResolutionResult;

class IResolutionBuffer
{
public:
	IResolutionBuffer(){};
	virtual ~IResolutionBuffer() {};
	virtual void* GetBuffer(void) const = 0;
	virtual int GetLengthBytes() const = 0;
	virtual int GetWBytes() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual const type_info& GetBufferTypeid() const = 0;
	virtual const TDATASPEC& GetDataSpec() const = 0;
	virtual void SetDataSpec(EDATAFORMAT eDataFormat, EOUTMODE eOutMode, ESENSORTYPE eSensorType, int nBlackLevel) {};
};

template<typename T> class ResolutionBufferPtr : public IResolutionBuffer
{
	const T* m_pImageBuffer;
	int m_nWidth;
	int m_nHeight;
	int m_nWBytes;
	TDATASPEC m_tDataSpec;

public:
	ResolutionBufferPtr() : m_pImageBuffer(nullptr), m_nWBytes(0), m_nWidth(0), m_nHeight(0)
	{
		InitDataSpec();
	}
	ResolutionBufferPtr(const T* pImageBuffer, int nWidth, int nHeight, int nWidthByte)
		: m_pImageBuffer(pImageBuffer), m_nWidth(nWidth), m_nHeight(nHeight), m_nWBytes(nWidthByte)
	{
		InitDataSpec();
	}

	virtual ~ResolutionBufferPtr() { }

	T &operator[](size_t i) const
	{
		return m_vImageBuffer[i];
	}

	void Set(const T* pImageBuffer, int nWidth, int nHeight, int nWidthByte)
	{
		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_nWBytes = nWidthByte;
		m_pImageBuffer = pImageBuffer;
	}

	void InitDataSpec()
	{
		SetDataSpec(DATAFORMAT_YUV, OUTMODE_YUV422_YCbYCr, (ESENSORTYPE)OUTMODE_YUV422_YCbYCr, 0);
	}

	void SetDataSpec(EDATAFORMAT eDataFormat, EOUTMODE eOutMode, ESENSORTYPE eSensorType, int nBlackLevel)
	{
		m_tDataSpec.eDataFormat = eDataFormat;
		m_tDataSpec.eOutMode = eOutMode;
		m_tDataSpec.eSensorType = eSensorType;
		m_tDataSpec.nBlackLevel = nBlackLevel;
	}

	void* GetBuffer() const { return (void*)m_pImageBuffer; }
	int GetWBytes() const { return m_nWBytes; }
	int GetWidth() const { return m_nWidth; }
	int GetHeight() const { return m_nHeight; }

	int GetLengthBytes() const { return sizeof(T); }
	const type_info& GetBufferTypeid() const { return typeid(T); }
	const TDATASPEC& GetDataSpec() const { return m_tDataSpec; }
};

class ResolutionImageBufferManager
{
	std::shared_ptr<IResolutionBuffer> m_Ptr;

public:
	template<typename T> ResolutionImageBufferManager(const T* pImageBuffer, int nWidth, int nHeight, int nWidthByte)
		: m_Ptr(new ResolutionBufferPtr<T>(pImageBuffer, nWidth, nHeight, nWidthByte)) {}

	inline void* GetBuffer() const { return m_Ptr->GetBuffer(); }
	inline const type_info& GetBufferTypeid() { return m_Ptr->GetBufferTypeid(); }
	inline int GetLengthBytes() { return m_Ptr->GetLengthBytes(); }
	inline int GetWidth() const { return m_Ptr->GetWidth(); }
	inline int GetHeight() const { return m_Ptr->GetHeight(); }
	inline int GetWBytes() const { return m_Ptr->GetWBytes(); }
	inline const TDATASPEC& GetDataSpec() const { return m_Ptr->GetDataSpec(); }
	inline void SetDataSpec(EDATAFORMAT eDataFormat, EOUTMODE eOutMode, ESENSORTYPE eSensorType, int nBlackLevel) { m_Ptr->SetDataSpec(eDataFormat, eOutMode, eSensorType, nBlackLevel); }
};
