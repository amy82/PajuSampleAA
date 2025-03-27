#pragma once

#include <LibACMISCommon\ACMISCommon.h>

#define COLOR_INTENSITY_SPEC_FLAG_VERSION_MAJOR		1
#define COLOR_INTENSITY_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_COLOR_INTENSITY
{
	COLOR_INTENSITY_ADJUST_TYPE,
	COLOR_INTENSITY_TYPICAL_VALUE_TYPE,

	COLOR_INTENSITY_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_COLOR_INTENSITY;

#define COLOR_INTENSITY_ROI_FLAG_VERSION_MAJOR		1
#define COLOR_INTENSITY_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_COLOR_INTENSITY
{
	COLOR_INTENSITY_ROI_TYPE,
	COLOR_INTENSITY_ROI_DATA1,
	COLOR_INTENSITY_ROI_DATA2,
	COLOR_INTENSITY_ROI_DATA3,
	COLOR_INTENSITY_ROI_DATA4,
	COLOR_INTENSITY_ROI_OFFSET_R,
	COLOR_INTENSITY_ROI_OFFSET_G,
	COLOR_INTENSITY_ROI_OFFSET_B,
	COLOR_INTENSITY_ROI_COLOR_DIFF_MIN_THRESHOLD_R,
	COLOR_INTENSITY_ROI_COLOR_DIFF_MAX_THRESHOLD_R,
	COLOR_INTENSITY_ROI_COLOR_DIFF_MIN_THRESHOLD_G,
	COLOR_INTENSITY_ROI_COLOR_DIFF_MAX_THRESHOLD_G,
	COLOR_INTENSITY_ROI_COLOR_DIFF_MIN_THRESHOLD_B,
	COLOR_INTENSITY_ROI_COLOR_DIFF_MAX_THRESHOLD_B,
	COLOR_INTENSITY_ROI_DISTANCE_MIN_THRESHOLD,
	COLOR_INTENSITY_ROI_DISTANCE_MAX_THRESHOLD,
	COLOR_INTENSITY_ROI_REF_COLOR_R,
	COLOR_INTENSITY_ROI_REF_COLOR_G,
	COLOR_INTENSITY_ROI_REF_COLOR_B,

	COLOR_INTENSITY_ROI_FLAG_MAX_COUNT
} ROI_FLAG_COLOR_INTENSITY;

typedef struct _TColorIntensitySpec
{
	int nAdjustType;	// 0: plus, 1: multiply
	int nTypicalValueType; // ETypicalValueType : Mean or Median
	TROIData tROI;

	TColorRatio* ptRefColorRGB;
	double *dColorDiffTh;
	double *dDistanceTh;
} TColorIntensitySpec;

#define RESULT_COLOR_INTENSITY_VERSION_MAJOR		1
#define RESULT_COLOR_INTENSITY_VERSION_MINOR		0
typedef enum _RESULT_FLAG_COLOR_INTENSITY
{
	COLOR_INTENSITY_RESULT_INDEX,
	COLOR_INTENSITY_RESULT_ROI_LEFT,
	COLOR_INTENSITY_RESULT_ROI_TOP,
	COLOR_INTENSITY_RESULT_ROI_RIGHT,
	COLOR_INTENSITY_RESULT_ROI_BOTTOM,
	COLOR_INTENSITY_RESULT_DISTANCE,
	COLOR_INTENSITY_RESULT_COLOR_DIFF1,
	COLOR_INTENSITY_RESULT_COLOR_DIFF2,
	COLOR_INTENSITY_RESULT_COLOR_DIFF3,
	COLOR_INTENSITY_RESULT_COLOR_RATIO_R,
	COLOR_INTENSITY_RESULT_COLOR_RATIO_G,
	COLOR_INTENSITY_RESULT_COLOR_RATIO_B,
	COLOR_INTENSITY_RESULT_ADJUST_COLOR_RATIO_R,
	COLOR_INTENSITY_RESULT_ADJUST_COLOR_RATIO_G,
	COLOR_INTENSITY_RESULT_ADJUST_COLOR_RATIO_B,

	COLOR_INTENSITY_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_COLOR_INTENSITY;

typedef struct _TColorIntensityResult
{
	int nIndex;
	RECT rtROI;
	double dDistance;
	double dColorDiff[3];
	TColorRatio tColorRatio;
	TColorRatio tAdjustColorRatio;
} TColorIntensityResult;

#define RESULT_COLOR_REPRODUCTION_VERSION_MAJOR		1
#define RESULT_COLOR_REPRODUCTION_VERSION_MINOR		0
typedef enum _RESULT_FLAG_COLOR_REPRODUCTION
{
	COLOR_REPRODUCTION_RESULT_INDEX,
	COLOR_REPRODUCTION_RESULT_ROI_LEFT,
	COLOR_REPRODUCTION_RESULT_ROI_TOP,
	COLOR_REPRODUCTION_RESULT_ROI_RIGHT,
	COLOR_REPRODUCTION_RESULT_ROI_BOTTOM,
	COLOR_REPRODUCTION_RESULT_DELTA,
	COLOR_REPRODUCTION_RESULT_COLOR_LAB_L,
	COLOR_REPRODUCTION_RESULT_COLOR_LAB_A,
	COLOR_REPRODUCTION_RESULT_COLOR_LAB_B,

	COLOR_REPRODUCTION_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_COLOR_REPRODUCTION;

typedef struct _TColorReproductionResult
{
	int nIndex;
	double dDelta;
	TColorReproduction tColorLab;
	RECT rtROI;
} TColorReproductionResult;

typedef struct _TColorReproductionSpec
{
	int nROIWidth;
	int nROIHeight;
	int nMaxROICount;
	POINT *ptROICenter;
	TColorReproduction *ptRefColorLab;
	double *pdThresholdDelta;
} TColorReproductionSpec;

#define COLOR_REPRODUCTION_SPEC_FLAG_VERSION_MAJOR		1
#define COLOR_REPRODUCTION_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_COLOR_REPRODUCTION
{
	COLOR_REPRODUCTION_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_COLOR_REPRODUCTION;

#define COLOR_REPRODUCTION_ROI_FLAG_VERSION_MAJOR		1
#define COLOR_REPRODUCTION_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_COLOR_REPRODUCTION
{
	COLOR_REPRODUCTION_ROI_TYPE,
	COLOR_REPRODUCTION_ROI_DATA1,
	COLOR_REPRODUCTION_ROI_DATA2,
	COLOR_REPRODUCTION_ROI_DATA3,
	COLOR_REPRODUCTION_ROI_DATA4,
	COLOR_REPRODUCTION_ROI_OFFSET,
	COLOR_REPRODUCTION_ROI_MIN_THRESHOLD_DELTA,
	COLOR_REPRODUCTION_ROI_MAX_THRESHOLD_DELTA,
	COLOR_REPRODUCTION_ROI_REF_COLOR_L,
	COLOR_REPRODUCTION_ROI_REF_COLOR_A,
	COLOR_REPRODUCTION_ROI_REF_COLOR_B,

	COLOR_REPRODUCTION_ROI_FLAG_MAX_COUNT
} ROI_FLAG_COLOR_REPRODUCTION;

typedef struct _TColorReproductionSpecN
{
	TROIData tROI;
	TColorReproduction *ptRefColorLab;
	double *pdThresholdDelta;
} TColorReproductionSpecN;

typedef struct _TIRFilterSpec
{
	double dMinThreshold;
	double dMaxThreshold;
	double dROIVarThreshold;
	RECT rtROI;
} TIRFilterSpec;

#define IR_FILTER_SPEC_FLAG_VERSION_MAJOR		1
#define IR_FILTER_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_IR_FILTER
{
	IR_FILTER_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_IR_FILTER;

#define IR_FILTER_ROI_FLAG_VERSION_MAJOR		1
#define IR_FILTER_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_IR_FILTER
{
	IR_FILTER_ROI_TYPE,
	IR_FILTER_ROI_DATA1,
	IR_FILTER_ROI_DATA2,
	IR_FILTER_ROI_DATA3,
	IR_FILTER_ROI_DATA4,
	IR_FILTER_ROI_OFFSET_AVG,
	IR_FILTER_ROI_OFFSET_VAR,
	IR_FILTER_ROI_AVG_MIN_THRESHOLD,
	IR_FILTER_ROI_AVG_MAX_THRESHOLD,
	IR_FILTER_ROI_VAR_MIN_THRESHOLD,
	IR_FILTER_ROI_VAR_MAX_THRESHOLD,

	IR_FILTER_ROI_FLAG_MAX_COUNT
} ROI_FLAG_IR_FILTER;

typedef struct _TIRFilterSpecN
{
	double dMinThreshold;
	double dMaxThreshold;
	double dROIVarThreshold;
	TROIData tROI;
} TIRFilterSpecN;

#define RESULT_IR_FILTER_VERSION_MAJOR		1
#define RESULT_IR_FILTER_VERSION_MINOR		0
typedef enum _RESULT_FLAG_IR_FILTER
{
	IR_FILTER_RESULT_ROI_LEFT,
	IR_FILTER_RESULT_ROI_TOP,
	IR_FILTER_RESULT_ROI_RIGHT,
	IR_FILTER_RESULT_ROI_BOTTOM,
	IR_FILTER_RESULT_FULL_BRIGHT_AVERAGE,
	IR_FILTER_RESULT_ROI_BRIGHT_AVERAGE,
	IR_FILTER_RESULT_ROI_BRIGHT_VARIANCE,
	IR_FILTER_RESULT_ROI_BRIGHT_DEVIATION,

	IR_FILTER_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_IR_FILTER;

typedef struct _TIRFilterResult
{
	RECT rtROI;
	double dFullBrightAvg;
	double dROIBrightAvg;
	double dROIBrightVar;
	double dROIBrightDev;
} TIRFilterResult;

#define FLARE_SPEC_FLAG_VERSION_MAJOR		1
#define FLARE_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_FLARE
{
	FLARE_GAMMA,
	FLARE_TARGET,
	FLARE_BORDER_WIDTH,
	FLARE_RADIUS,
	FLARE_BINARY_THRESHOLD,

	FLARE_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_FLARE;

#define FLARE_ROI_FLAG_VERSION_MAJOR		1
#define FLARE_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_FLARE
{
	FLARE_ROI_TYPE,
	FLARE_ROI_DATA1,
	FLARE_ROI_DATA2,
	FLARE_ROI_DATA3,
	FLARE_ROI_DATA4,
	FLARE_ROI_OFFSET,
	FLARE_ROI_MIN_THRESHOLD,
	FLARE_ROI_MAX_THRESHOLD,

	FLARE_ROI_FLAG_MAX_COUNT
} ROI_FLAG_FLARE;

typedef struct _TFlareSpec
{
	TROIData tROI;
	EFlareTarget eFlareTarget;
	double dGamma;
	double dBorderWidth;
	double dThresholdFlare;

	// Circle Mark
	double dRadius;
	double dBinaryThreshold; /// threshold for Binary of image
} TFlareSpec;

#define RESULT_ROI_FLARE_VERSION_MAJOR		1
#define RESULT_ROI_FLARE_VERSION_MINOR		0
typedef enum _RESULT_ROI_FLAG_FLARE
{
	FLARE_RESULT_ROI_BOX_CENTER_X,
	FLARE_RESULT_ROI_BOX_CENTER_Y,
	FLARE_RESULT_ROI_BOX_SIZE_WIDTH,
	FLARE_RESULT_ROI_BOX_SIZE_HEIGHT,
	FLARE_RESULT_ROI_BOX_ANGLE,

	FLARE_RESULT_ROI_FLAG_MAX_COUNT
} RESULT_ROI_FLAG_FLARE;

#define RESULT_FLARE_VERSION_MAJOR		1
#define RESULT_FLARE_VERSION_MINOR		0
typedef enum _RESULT_FLAG_FLARE
{
	FLARE_RESULT_FLARE,
	FLARE_RESULT_WHITE_Y,
	FLARE_RESULT_BLACK_Y,

	FLARE_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_FLARE;

typedef struct _TFlareResult
{
	DBox2D BoxBlack;
	DBox2D BoxTarget;
	DBox2D BoxWhite[4];
	double dFlare;
	double dWhiteY;
	double dBlackY;
} TFlareResult;

#define VIEW_MODE_SPEC_FLAG_VERSION_MAJOR		1
#define VIEW_MODE_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_VIEW_MODE
{
	VIEW_MODE_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_VIEW_MODE;

#define VIEW_MODE_ROI_FLAG_VERSION_MAJOR		1
#define VIEW_MODE_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_VIEW_MODE
{
	VIEW_MODE_ROI_TYPE,
	VIEW_MODE_ROI_DATA1,
	VIEW_MODE_ROI_DATA2,
	VIEW_MODE_ROI_DATA3,
	VIEW_MODE_ROI_DATA4,
	VIEW_MODE_ROI_OFFSET,
	VIEW_MODE_ROI_MIN_THRESHOLD,
	VIEW_MODE_ROI_MAX_THRESHOLD,
	VIEW_MODE_ROI_REF_VERTEX_X1,
	VIEW_MODE_ROI_REF_VERTEX_Y1,
	VIEW_MODE_ROI_REF_VERTEX_X2,
	VIEW_MODE_ROI_REF_VERTEX_Y2,
	VIEW_MODE_ROI_REF_VERTEX_X3,
	VIEW_MODE_ROI_REF_VERTEX_Y3,
	VIEW_MODE_ROI_REF_VERTEX_X4,
	VIEW_MODE_ROI_REF_VERTEX_Y4,

	VIEW_MODE_ROI_FLAG_MAX_COUNT
} ROI_FLAG_VIEW_MODE;

typedef struct _TViewModeSpec
{
	TROIData tROI;
	POINT *ptRefVertex;
	double dThreshold;
} TViewModeSpec;

#define RESULT_ROI_VIEW_MODE_VERSION_MAJOR		1
#define RESULT_ROI_VIEW_MODE_VERSION_MINOR		0
typedef enum _RESULT_ROI_FLAG_VIEW_MODE
{
	VIEW_MODE_RESULT_ROI_SQURE_LEFT,
	VIEW_MODE_RESULT_ROI_SQURE_TOP,
	VIEW_MODE_RESULT_ROI_SQURE_RIGHT,
	VIEW_MODE_RESULT_ROI_SQURE_BOTTOM,
	VIEW_MODE_RESULT_ROI_VERTEX1_X,
	VIEW_MODE_RESULT_ROI_VERTEX1_Y,
	VIEW_MODE_RESULT_ROI_VERTEX2_X,
	VIEW_MODE_RESULT_ROI_VERTEX2_Y,
	VIEW_MODE_RESULT_ROI_VERTEX3_X,
	VIEW_MODE_RESULT_ROI_VERTEX3_Y,
	VIEW_MODE_RESULT_ROI_VERTEX4_X,
	VIEW_MODE_RESULT_ROI_VERTEX4_Y,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX1_X,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX1_Y,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX2_X,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX2_Y,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX3_X,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX3_Y,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX4_X,
	VIEW_MODE_RESULT_ROI_CONVERTED_VERTEX4_Y,

	VIEW_MODE_RESULT_ROI_FLAG_MAX_COUNT
} RESULT_ROI_FLAG_VIEW_MODE;

#define RESULT_VIEW_MODE_VERSION_MAJOR		1
#define RESULT_VIEW_MODE_VERSION_MINOR		0
typedef enum _RESULT_FLAG_VIEW_MODE
{
	VIEW_MODE_RESULT_MAX_DISTANCE,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX1,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX2,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX3,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX4,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX5,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX6,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX7,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX8,
	VIEW_MODE_RESULT_HOMOGRAPHY_MATRIX9,

	VIEW_MODE_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_VIEW_MODE;

typedef struct _TViewModeResult
{
	int nSqureCount;
	int nVertexCount;
	RECT *rtSqure;
	POINT *ptVertex;
	POINT *ptConvertedVertex;
	double dMaxDistance;
	double *dHomographyMatrix;
} TViewModeResult;

#define SATURATION_SPEC_FLAG_VERSION_MAJOR		1
#define SATURATION_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_SATURATION
{
	SATURATION_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_SATURATION;

#define SATURATION_ROI_FLAG_VERSION_MAJOR		1
#define SATURATION_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_SATURATION
{
	SATURATION_ROI_TYPE,
	SATURATION_ROI_DATA1,
	SATURATION_ROI_DATA2,
	SATURATION_ROI_DATA3,
	SATURATION_ROI_DATA4,
	SATURATION_ROI_OFFSET,
	SATURATION_ROI_MIN_BRIGHT,
	SATURATION_ROI_MAX_BRIGHT,
	SATURATION_ROI_BINARY_THRESHOLD,

	SATURATION_ROI_FLAG_MAX_COUNT
} ROI_FLAG_SATURATION;

typedef struct _TSaturationSpec
{
	TROIData tROI;
	double *dSpecBrightMin;
	double *dSpecBrightMax;
	double *dBinaryThreshold;
} TSaturationSpec;

#define RESULT_SATURATION_VERSION_MAJOR		1
#define RESULT_SATURATION_VERSION_MINOR		0
typedef enum _RESULT_FLAG_SATURATION
{
	SATURATION_RESULT_ROI_LEFT,
	SATURATION_RESULT_ROI_TOP,
	SATURATION_RESULT_ROI_RIGHT,
	SATURATION_RESULT_ROI_BOTTOM,
	SATURATION_RESULT_BRIGHT_MIN_X,
	SATURATION_RESULT_BRIGHT_MIN_Y,
	SATURATION_RESULT_BRIGHT_MAX_X,
	SATURATION_RESULT_BRIGHT_MAX_Y,
	SATURATION_RESULT_ROI_BRIGHT_MIN,
	SATURATION_RESULT_ROI_BRIGHT_MAX,
	SATURATION_RESULT_ROI_BRIGHT_AVERAGE,
	SATURATION_RESULT_ROI_BRIGHT_MAX_BIN,
	SATURATION_RESULT_ROI_BRIGHT_MAX_BIN_PIXEL_COUNT,

	SATURATION_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_SATURATION;

typedef struct _TSaturationResult
{
	RECT rtROI;
	POINT ptBrightMin;
	POINT ptBrightMax;
	double dROIBrightMin;
	double dROIBrightMax;
	double dROIBrightAvg;
	int nROIBrightMaxBin;
	int nROIBrightMaxBinPixelCnt;
} TSaturationResult;

#define STRAY_LIGHT_SPEC_FLAG_VERSION_MAJOR		1
#define STRAY_LIGHT_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_STRAY_LIGHT
{
	STRAY_LIGHT_BINARY_THRESHOLD0,
	STRAY_LIGHT_BINARY_THRESHOLD1,
	STRAY_LIGHT_MIN_LED_LIGHT_SIZE,
	STRAY_LIGHT_SMOOTHING,
	STRAY_LIGHT_SMOOTH_WINDOW_SIZE,
	STRAY_LIGHT_SMOOTH_WINDOW,
	STRAY_LIGHT_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_STRAY_LIGHT;

#define STRAY_LIGHT_ROI_FLAG_VERSION_MAJOR		1
#define STRAY_LIGHT_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_STRAY_LIGHT
{
	STRAY_LIGHT_ROI_TYPE,
	STRAY_LIGHT_ROI_DATA1,
	STRAY_LIGHT_ROI_DATA2,
	STRAY_LIGHT_ROI_DATA3,
	STRAY_LIGHT_ROI_DATA4,
	STRAY_LIGHT_ROI_OFFSET,
	STRAY_LIGHT_ROI_SCAN_SIZE,
	STRAY_LIGHT_ROI_EXCLUDE_SIZE,
	STRAY_LIGHT_ROI_THRESHOLD,

	STRAY_LIGHT_ROI_FLAG_MAX_COUNT
} ROI_FLAG_STRAY_LIGHT;

typedef struct _TStrayLightSpec
{
	TROIData tROI;
	int *nScanSize;
	int *nExcludeSize;
	double *dThreshold;
	int nSmoothing;
	double *dSmoothWindow;
	int nSmoothWindowSize;
	double dBinaryThreshold[2];
	int nMinLEDLightSize;
} TStrayLightSpec;

#define RESULT_ROI_STRAY_LIGHT_VERSION_MAJOR		1
#define RESULT_ROI_STRAY_LIGHT_VERSION_MINOR		0
typedef enum _RESULT_ROI_FLAG_STRAY_LIGHT
{
	STRAY_LIGHT_RESULT_ROI_FLAG_MAX_COUNT
} RESULT_ROI_FLAG_STRAY_LIGHT;

#define RESULT_STRAY_LIGHT_VERSION_MAJOR		1
#define RESULT_STRAY_LIGHT_VERSION_MINOR		0
typedef enum _RESULT_FLAG_STRAY_LIGHT
{
	STRAY_LIGHT_RESULT_ROI_CENTER_X,
	STRAY_LIGHT_RESULT_ROI_CENTER_Y,
	STRAY_LIGHT_RESULT_ROI_DIA_MAX,
	STRAY_LIGHT_RESULT_ROI_SPEC_OVER_COUNT,
	STRAY_LIGHT_RESULT_ROI_STRAY_LIGHT_THRESHOLD,
	STRAY_LIGHT_RESULT_ROI_AVG_LIGHT,
	STRAY_LIGHT_RESULT_ROI_MAX_LIGHT,
	STRAY_LIGHT_RESULT_ROI_MIN_LIGHT,
	STRAY_LIGHT_RESULT_ROI_MAX_ANGLE,
	STRAY_LIGHT_RESULT_ROI_MIN_ANGLE,
	STRAY_LIGHT_RESULT_ROI_MeanY,

	STRAY_LIGHT_RESULT_FLAG_MAX_COUNT = STRAY_LIGHT_RESULT_ROI_MeanY + 360
} RESULT_FLAG_STRAY_LIGHT;

typedef struct _TStrayLightResult
{
	POINT ptCenter;
	int nDiaMax;
	int nSpecOverCount;
	double dStrayLightThreshold;
	double dROIAvgLight;
	double dROIMaxLight;
	double dROIMinLight;
	int nROIMaxAngle;
	int nROIMinAngle;
	double dMeanY[360];
} TStrayLightResult;


template<typename T, typename TResult, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class IEtcCommon
{
public:
	IEtcCommon() : m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_bIsCertified(false) { memset(&m_tDataSpec, 0, sizeof(TDATASPEC)); memset(&m_stSpec, 0, sizeof(T)); memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset)); }
	virtual ~IEtcCommon() {}

	virtual bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool Inspect(TBufferInfo& tBufferInfo, T& _Spec) = 0;
	virtual bool Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual int GetInspectionRegionCount() = 0;
	virtual const TResult* GetInspectionResult(int nIndex = 0) = 0;
	virtual bool InSpec(const T& _Spec) = 0;
	virtual const RECT* GetInspectionROI(int nIndex = 0) = 0;
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
class CACMISEtcCommon
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
	std::shared_ptr<IEtcCommon<T, TResult, DataType, DataFormat, OutMode, SensorType, DemosaicMethod>> m_pMethod;
	CACMISEtcCommon() {}
	CACMISEtcCommon(const CACMISEtcCommon&) {}
#else
	IEtcCommon<T, TResult, DataType, DataFormat, OutMode, SensorType, DemosaicMethod>* m_pMethod;
	CACMISEtcCommon() : m_pMethod(NULL) {}
	CACMISEtcCommon(const CACMISEtcCommon&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISEtcCommon() {}

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
	inline const TResult* GetInspectionResult(int nIndex = 0)
	{
		return m_pMethod->GetInspectionResult(nIndex);
	}
	inline bool InSpec(const T& _Spec)
	{
		return m_pMethod->InSpec(_Spec);
	}
	inline const RECT* GetInspectionROI(int nIndex = 0)
	{
		return m_pMethod->GetInspectionROI(nIndex);
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

