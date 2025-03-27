#pragma once

#include <ppl.h>
#include <LibACMISCommon\ACMISCommon.h>

//////////////////////////////////////////////////////////////////////////
// Signal to Noise Ratio

typedef enum _EFPNMethod
{
	EFPN_Common,
	EFPN_ONSEMI,
	EFPN_EMVA1288
} EFPNMethod;

typedef enum _EPatternNoiseType
{
	EFPN_DSNU,
	EFPN_PRNU,
	EFPN_DSNU_ONSEMI,
	EFPN_PRNU_ONSEMI,
	EFPN_DSNU_EMVA1288,
	EFPN_PRNU_EMVA1288
} EPatternNoiseType;

typedef enum _SNR_BW_IMAGE_INDEX
{
	SNR_BW_IMAGE_WHITE,
	SNR_BW_IMAGE_BLACK,
	SNR_BW_IMAGE_GRAY
} SNR_BW_IMAGE_INDEX;

typedef struct _TSNR
{
	double dSNRResult;
	double dDRResult;
	long double dAverage;
	long double dVariance;
	RECT rtROI;
	int nIndex;
} TSNRResult;

typedef struct _TSNRNormSpec
{
	int nROIWidth;
	int nROIHeight;
	int nLscBlockSize;
	int nMaxROICount;
	POINT *ptROICenter;
	double dSNRThreshold;
} TSNRNormSpec;
#define TSNROECFSpec TSNRNormSpec

#define SNR_NORM_SPEC_FLAG_VERSION_MAJOR		1
#define SNR_NORM_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_SNR_NORM
{
	SNR_NORM_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_SNR_NORM;

#define SNR_NORM_ROI_FLAG_VERSION_MAJOR		1
#define SNR_NORM_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_SNR_NORM
{
	SNR_NORM_ROI_TYPE,
	SNR_NORM_ROI_DATA1,
	SNR_NORM_ROI_DATA2,
	SNR_NORM_ROI_DATA3,
	SNR_NORM_ROI_DATA4,
	SNR_NORM_ROI_OFFSET,
	SNR_NORM_ROI_SNR_MIN_THRESHOLD,
	SNR_NORM_ROI_SNR_MAX_THRESHOLD,

	SNR_NORM_ROI_FLAG_MAX_COUNT
} ROI_FLAG_SNR_NORM;

typedef struct _TSNRNormSpecN
{
	TROIData tROI;
	double dSNRThreshold;
} TSNRNormSpecN;

#define RESULT_SNR_NORM_VERSION_MAJOR		1
#define RESULT_SNR_NORM_VERSION_MINOR		0
typedef enum _RESULT_FLAG_SNR_NORM
{
	SNR_NORM_RESULT_SNR,
	SNR_NORM_RESULT_AVERAGE,
	SNR_NORM_RESULT_VARIANCE,
	SNR_NORM_RESULT_ROI_LEFT,
	SNR_NORM_RESULT_ROI_TOP,
	SNR_NORM_RESULT_ROI_RIGHT,
	SNR_NORM_RESULT_ROI_BOTTOM,
	SNR_NORM_RESULT_INDEX,

	SNR_NORM_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_SNR_NORM;

typedef struct _TSNRNormResult
{
	double dSNRResult;
	double dAverage;
	double dVariance;
	RECT rtROI;
	int nIndex;
} TSNRNormResult;

typedef struct _TPatternNoiseSpec
{
	int nROIWidth;
	int nROIHeight;
	int nPatternType;
	int nLscBlockSize;
	int nMaxROICount;
	double dROIXPosRatio;
	double dROIYPosRatio;
	double dSNRThreshold;
} TPatternNoiseSpec;

#define PATTERN_NOISE_SPEC_FLAG_VERSION_MAJOR		1
#define PATTERN_NOISE_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_PATTERN_NOISE
{
	PATTERN_NOISE_PATTERN_TYPE,

	PATTERN_NOISE_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_PATTERN_NOISE;

#define PATTERN_NOISE_ROI_FLAG_VERSION_MAJOR		1
#define PATTERN_NOISE_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_PATTERN_NOISE
{
	PATTERN_NOISE_ROI_TYPE,
	PATTERN_NOISE_ROI_DATA1,
	PATTERN_NOISE_ROI_DATA2,
	PATTERN_NOISE_ROI_DATA3,
	PATTERN_NOISE_ROI_DATA4,
	PATTERN_NOISE_ROI_OFFSET,
	PATTERN_NOISE_ROI_SNR_MIN_THRESHOLD,
	PATTERN_NOISE_ROI_SNR_MAX_THRESHOLD,

	PATTERN_NOISE_ROI_FLAG_MAX_COUNT
} ROI_FLAG_PATTERN_NOISE;

typedef struct _TPatternNoiseSpecN
{
	int nPatternType;
	TROIData tROI;
	double dSNRThreshold;
} TPatternNoiseSpecN;

#define RESULT_PATTERN_NOISE_VERSION_MAJOR		1
#define RESULT_PATTERN_NOISE_VERSION_MINOR		0
typedef enum _RESULT_FLAG_PATTERN_NOISE
{
	PATTERN_NOISE_RESULT_DSNU,
	PATTERN_NOISE_RESULT_PRNU,
	PATTERN_NOISE_RESULT_FPN_DATA1,
	PATTERN_NOISE_RESULT_FPN_DATA2,
	PATTERN_NOISE_RESULT_FPN_DATA3,
	PATTERN_NOISE_RESULT_FPN_DATA4,
	PATTERN_NOISE_RESULT_FPN_DATA5,
	PATTERN_NOISE_RESULT_FPN_DATA6,
	PATTERN_NOISE_RESULT_ROI_LEFT,
	PATTERN_NOISE_RESULT_ROI_TOP,
	PATTERN_NOISE_RESULT_ROI_RIGHT,
	PATTERN_NOISE_RESULT_ROI_BOTTOM,
	PATTERN_NOISE_RESULT_INDEX,

	PATTERN_NOISE_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_PATTERN_NOISE;

typedef struct _TPatternNoiseResult
{
	double dDSNU;
	double dPRNU;
	double dFPNData[6];
	RECT rtROI;
	int nIndex;
} TPatternNoiseResult;

typedef enum _EFPNDATAINDEX
{
	FPNDATA_DSNU_AVERAGE,
	FPNDATA_DSNU_VARIANCE,
	FPNDATA_PRNU_AVERAGE,
	FPNDATA_PRNU_VARIANCE,
	FPNDATA_PRNU_VAR_TOT = FPNDATA_PRNU_VARIANCE,
	FPNDATA_PRNU_VAR_ROW,
	FPNDATA_PRNU_VAR_COL,
	FPNDATA_PRNU_DARK_AVG = FPNDATA_PRNU_AVERAGE,
	FPNDATA_PRNU_DARK_VAR,
	FPNDATA_PRNU_SAT50_AGV,
	FPNDATA_PRNU_SAT50_VAR
} EFPNDATAINDEX;

typedef struct _TSNRBWSpec
{
	int nROIWidth;
	int nROIHeight;
	int nLscBlockSize;
	int nMaxROICount;
	POINT *ptROICenter;
	double dSNRThreshold;
	double dDRThreshold;
} TSNRBWSpec;

#define SNR_BW_SPEC_FLAG_VERSION_MAJOR		1
#define SNR_BW_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_SNR_BW
{
	SNR_BW_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_SNR_BW;

#define SNR_BW_ROI_FLAG_VERSION_MAJOR		1
#define SNR_BW_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_SNR_BW
{
	SNR_BW_ROI_TYPE,
	SNR_BW_ROI_DATA1,
	SNR_BW_ROI_DATA2,
	SNR_BW_ROI_DATA3,
	SNR_BW_ROI_DATA4,
	SNR_BW_ROI_OFFSET,
	SNR_BW_ROI_SNR_MIN_THRESHOLD,
	SNR_BW_ROI_SNR_MAX_THRESHOLD,
	SNR_BW_ROI_DR_MIN_THRESHOLD,
	SNR_BW_ROI_DR_MAX_THRESHOLD,

	SNR_BW_ROI_FLAG_MAX_COUNT
} ROI_FLAG_SNR_BW;

typedef struct _TSNRBWSpecN
{
	TROIData tROI;
	double dSNRThreshold;
	double dDRThreshold;
} TSNRBWSpecN;

#define RESULT_SNR_BW_VERSION_MAJOR		1
#define RESULT_SNR_BW_VERSION_MINOR		0
typedef enum _RESULT_FLAG_SNR_BW
{
	SNR_BW_RESULT_WHITE_AVERAGE,
	SNR_BW_RESULT_BLACK_AVERAGE,
	SNR_BW_RESULT_GRAY_VARIANCE,
	SNR_BW_RESULT_SNR,
	SNR_BW_RESULT_DR,
	SNR_BW_RESULT_ROI_LEFT,
	SNR_BW_RESULT_ROI_TOP,
	SNR_BW_RESULT_ROI_RIGHT,
	SNR_BW_RESULT_ROI_BOTTOM,
	SNR_BW_RESULT_INDEX,

	SNR_BW_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_SNR_BW;

typedef struct _TSNRBWResult
{
	double dWhiteAverage;
	double dBlackAverage;
	double dGrayVariance;
	double dSNRResult;
	double dDRResult;
	RECT rtROI;
	int nIndex;
} TSNRBWResult;

#define DARK_CURRENT_SPEC_FLAG_VERSION_MAJOR		1
#define DARK_CURRENT_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_DARK_CURRENT
{
	DARK_CURRENT_EXPOSURE_TIME_INTERVAL,
	DARK_CURRENT_START_EXPOSURE_TIME,

	DARK_CURRENT_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_DARK_CURRENT;

#define DARK_CURRENT_ROI_FLAG_VERSION_MAJOR		1
#define DARK_CURRENT_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_DARK_CURRENT
{
	DARK_CURRENT_ROI_TYPE,
	DARK_CURRENT_ROI_DATA1,
	DARK_CURRENT_ROI_DATA2,
	DARK_CURRENT_ROI_DATA3,
	DARK_CURRENT_ROI_DATA4,
	DARK_CURRENT_ROI_OFFSET,
	DARK_CURRENT_ROI_MIN_THRESHOLD,
	DARK_CURRENT_ROI_MAX_THRESHOLD,

	DARK_CURRENT_ROI_FLAG_MAX_COUNT
} ROI_FLAG_DARK_CURRENT;

typedef struct _TDarkCurrentSpec
{
	TROIData tROI;
	double dDarkCurrentThreshold;
	double dExposureTimeInterval;
	double dStartExposureTime;
} TDarkCurrentSpec;

#define RESULT_DARK_CURRENT_VERSION_MAJOR		1
#define RESULT_DARK_CURRENT_VERSION_MINOR		0
typedef enum _RESULT_FLAG_DARK_CURRENT
{
	DARK_CURRENT_RESULT_DARK_CURRENT,
	DARK_CURRENT_RESULT_DARK_SIGNAL_BASE,
	DARK_CURRENT_RESULT_ROI_LEFT,
	DARK_CURRENT_RESULT_ROI_TOP,
	DARK_CURRENT_RESULT_ROI_RIGHT,
	DARK_CURRENT_RESULT_ROI_BOTTOM,
	DARK_CURRENT_RESULT_INDEX,

	DARK_CURRENT_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_DARK_CURRENT;

typedef struct _TDarkCurrentResult
{
	double dDarkCurrent;
	double dDarkSignalBasis;
	RECT rtROI;
	int nIndex;
} TDarkCurrentResult;

#define TSNRVNESpec TSNRNormSpecN
#define TSNRVNEResult TSNRNormResult

#define DARK_NOISE_SPEC_FLAG_VERSION_MAJOR		1
#define DARK_NOISE_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_DARK_NOISE
{
	DARK_NOISE_K,
	DARK_NOISE_ALTERNATIVE_VALUE,
	DARK_NOISE_ENABLE_CHANNEL,
	DARK_NOISE_BIT_DEPTH,
	DARK_NOISE_PEDESTAL,
	DARK_NOSE_CONV_KERNEL_SIZE,
	DARK_NOISE_CONV_KERNEL,
	DARK_NOISE_THRESHOLD_FPNP = (DARK_NOISE_CONV_KERNEL + DARK_NOSE_CONV_KERNEL_SIZE),
	DARK_NOISE_THRESHOLD_COLUMN_FPNP = (DARK_NOISE_THRESHOLD_FPNP + 4),
	DARK_NOISE_THRESHOLD_ROW_FPNP = (DARK_NOISE_THRESHOLD_COLUMN_FPNP + 4),
	DARK_NOISE_THRESHOLD_MAX_COLUMN_FPNP = (DARK_NOISE_THRESHOLD_ROW_FPNP + 4),
	DARK_NOISE_THRESHOLD_MAX_ROW_FPNP = (DARK_NOISE_THRESHOLD_MAX_COLUMN_FPNP + 4),
	DARK_NOISE_THRESHOLD_COLUMN_FPNV = (DARK_NOISE_THRESHOLD_MAX_ROW_FPNP + 4),
	DARK_NOISE_THRESHOLD_ROW_FPNV = (DARK_NOISE_THRESHOLD_COLUMN_FPNV + 4),
	DARK_NOISE_THRESHOLD_TEMPORAL_NOISEP = (DARK_NOISE_THRESHOLD_ROW_FPNV + 4),
	DARK_NOISE_THRESHOLD_COLUMN_NOISEP = (DARK_NOISE_THRESHOLD_TEMPORAL_NOISEP + 4),
	DARK_NOISE_THRESHOLD_ROW_NOISEP = (DARK_NOISE_THRESHOLD_COLUMN_NOISEP + 4),
	DARK_NOISE_THRESHOLD_T = (DARK_NOISE_THRESHOLD_ROW_NOISEP + 4),
	DARK_NOISE_THRESHOLD_COLUMN_NOISEV = (DARK_NOISE_THRESHOLD_T + 4),
	DARK_NOISE_THRESHOLD_ROW_NOISEV = (DARK_NOISE_THRESHOLD_COLUMN_NOISEV + 4),
	DARK_NOISE_THRESHOLD_BLACK_LEVEL = (DARK_NOISE_THRESHOLD_ROW_NOISEV + 4),

	DARK_NOISE_SPEC_FLAG_MAX_COUNT = (DARK_NOISE_THRESHOLD_BLACK_LEVEL + 4),
} SPEC_FLAG_DARK_NOISE;

#define DARK_NOISE_ROI_FLAG_VERSION_MAJOR		1
#define DARK_NOISE_ROI_FLAG_VERSION_MINOR		0
typedef enum _ROI_FLAG_DARK_NOISE
{
	DARK_NOISE_ROI_TYPE,
	DARK_NOISE_ROI_DATA1,
	DARK_NOISE_ROI_DATA2,
	DARK_NOISE_ROI_DATA3,
	DARK_NOISE_ROI_DATA4,
	DARK_NOISE_ROI_OFFSET,

	DARK_NOISE_ROI_FLAG_MAX_COUNT
} ROI_FLAG_DARK_NOISE;

typedef struct _TDarkNoiseSpec
{
	TROIData tROI;
	double dK;
	int nAlternativeValue;
	int nEnableChannel;
	int nBitDepth;
	int nPedestal;
	int nConvKerenelSize;
	double *pConvKernel;
	double dFPNPThreshold[4];
	double dColumnFPNPThreshold[4];
	double dRowFPNPThreshold[4];
	double dMaxColumnFPNPThreshold[4];
	double dMaxRowFPNPThreshold[4];
	double dColumnFPNVThreshold[4];
	double dRowFPNVThreshold[4];
	double dTemporalNoisePThreshold[4];
	double dColumnNoisePThreshold[4];
	double dRowNoisePThreshold[4];
	double dTThreshold[4];
	double dColumnNoiseVThreshold[4];
	double dRowNoiseVThreshold[4];
	double dBlackLevelThreshold[4];
} TDarkNoiseSpec;

#define RESULT_DARK_NOISE_VERSION_MAJOR		1
#define RESULT_DARK_NOISE_VERSION_MINOR		0
typedef enum _RESULT_FLAG_DARK_NOISE
{
	DARK_NOISE_RESULT_FPNP,
	DARK_NOISE_RESULT_COLUMN_FPNP = DARK_NOISE_RESULT_FPNP + 4,
	DARK_NOISE_RESULT_ROW_FPNP = DARK_NOISE_RESULT_COLUMN_FPNP + 4,
	DARK_NOISE_RESULT_MAX_COLUMN_FPNP = DARK_NOISE_RESULT_ROW_FPNP + 4,
	DARK_NOISE_RESULT_MAX_ROW_FPNP = DARK_NOISE_RESULT_MAX_COLUMN_FPNP + 4,
	DARK_NOISE_RESULT_COLUMN_FPNV = DARK_NOISE_RESULT_MAX_ROW_FPNP + 4,
	DARK_NOISE_RESULT_ROW_FPNV = DARK_NOISE_RESULT_COLUMN_FPNV + 4,
	DARK_NOISE_RESULT_TEMPORAL_NOISEP = DARK_NOISE_RESULT_ROW_FPNV + 4,
	DARK_NOISE_RESULT_COLUMN_NOISEP = DARK_NOISE_RESULT_TEMPORAL_NOISEP + 4,
	DARK_NOISE_RESULT_ROW_NOISEP = DARK_NOISE_RESULT_COLUMN_NOISEP + 4,
	DARK_NOISE_RESULT_T = DARK_NOISE_RESULT_ROW_NOISEP + 4,
	DARK_NOISE_RESULT_COLUMN_NOISEV = DARK_NOISE_RESULT_T + 4,
	DARK_NOISE_RESULT_ROW_NOISEV = DARK_NOISE_RESULT_COLUMN_NOISEV + 4,
	DARK_NOISE_RESULT_BLACK_LEVEL = DARK_NOISE_RESULT_ROW_NOISEV + 4,
	DARK_NOISE_RESULT_ROI_LEFT = DARK_NOISE_RESULT_BLACK_LEVEL + 4,
	DARK_NOISE_RESULT_ROI_TOP,
	DARK_NOISE_RESULT_ROI_RIGHT,
	DARK_NOISE_RESULT_ROI_BOTTOM,
	DARK_NOISE_RESULT_INDEX,

	DARK_NOISE_RESULT_FLAG_MAX_COUNT
} RESULT_FLAG_DARK_NOISE;

typedef struct _TDarkNoiseResult
{
	double dFPNP[4];
	double dColumnFPNP[4];
	double dRowFPNP[4];
	double dMaxColumnFPNP[4];
	double dMaxRowFPNP[4];
	double dColumnFPNV[4];
	double dRowFPNV[4];
	double dTemporalNoiseP[4];
	double dColumnNoiseP[4];
	double dRowNoiseP[4];
	double dT[4];
	double dColumnNoiseV[4];
	double dRowNoiseV[4];
	double dBlackLevel[4];
	RECT rtROI;
	int nIndex;
} TDarkNoiseResult;


template<typename T, typename TResult, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class ISignalNoiseRatio
{
public:
	ISignalNoiseRatio() : m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_bIsCertified(false) { memset(&m_tDataSpec, 0, sizeof(TDATASPEC)); memset(&m_stSpec, 0, sizeof(T)); memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset));}
	virtual ~ISignalNoiseRatio() {}

	typedef std::vector<TSNRResult> vSNRResult;

	virtual bool Inspect() = 0;
	virtual bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool Inspect(TBufferInfo& tBuferInfo, T& _Spec) = 0;
	virtual bool Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual bool InspectAlgorithm() = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual int GetSNRRegionCount() = 0;
	virtual const TSNRResult* GetSNRResult(int nIndex) = 0;
	virtual const TSNRResult* GetMinSNRResult() = 0;
	virtual int GetInspectionRegionCount() = 0;
	virtual const TResult* GetInspectionResult(int nIndex) = 0;
	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;
	virtual const char* GetVersion() = 0;
	virtual bool SetImageSpec(int nImageWidth, int nImageHeight, int nImageCount, T& pSpecc, EDATAFORMAT dataFormat, EOUTMODE outMode, ESENSORTYPE sensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool SetImageBuffer(const DataType* pBuffer, int nImageWidth, int nImageHeight, int nImageIndex, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_12BIT) = 0;
	virtual void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) = 0;
	virtual void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) = 0;
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
	vSNRResult m_vSNRResult;
	std::vector<TResult> m_vResult;
	TInspectRegionOffset m_tInspectRegionOffset;
	std::vector<double> m_vSaturationResult;
	bool m_bIsCertified;

	std::vector< std::vector<BYTE> > m_vRawBuffer;
};

template<typename T, typename TResult, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class CACMISSignalNoiseRatio
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
	std::shared_ptr<ISignalNoiseRatio<T, TResult, DataType, DataFormat, OutMode, SensorType, DemosaicMethod>> m_pMethod;
	CACMISSignalNoiseRatio() {}
	CACMISSignalNoiseRatio(const CACMISSignalNoiseRatio&) {}
#else
	ISignalNoiseRatio<T, TResult, DataType, DataFormat, OutMode, SensorType, DemosaicMethod>* m_pMethod;
	CACMISSignalNoiseRatio() : m_pMethod(NULL) {}
	CACMISSignalNoiseRatio(const CACMISSignalNoiseRatio&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISSignalNoiseRatio() {}

	inline bool Inspect()
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect();

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
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
	inline bool InspectAlgorithm()
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->InspectAlgorithm();

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
	inline int GetSNRRegionCount() const
	{
		return m_pMethod->GetSNRRegionCount();
	}
	inline const TSNRResult* GetSNRResult(int nIndex) const
	{
		return m_pMethod->GetSNRResult(nIndex);
	}
	inline const TSNRResult* GetMinSNRResult() const
	{
		return m_pMethod->GetMinSNRResult();
	}
	inline int GetInspectionRegionCount() const
	{
		return m_pMethod->GetInspectionRegionCount();
	}
	inline const TResult* GetInspectionResult(int nIndex) const
	{
		return m_pMethod->GetInspectionResult(nIndex);
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
	inline const char* GetVersion() const
	{
		return m_pMethod->GetVersion();
	}
	inline bool SetImageSpec(int nImageWidth, int nImageHeight, int nImageCount, T& _Spec, EDATAFORMAT dataFormat, EOUTMODE outMode, ESENSORTYPE sensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) const
	{
		return m_pMethod->SetImageSpec(nImageWidth, nImageHeight, nImageCount, _Spec, dataFormat, outMode, sensorType, nBlackLevel, nUsing8BitOnly, nPartialDemosaic, nDemosaicMethod);
	}
	inline bool SetImageBuffer(const DataType* pBuffer, int nImageWidth, int nImageHeight, int nImageIndex, EDATAFORMAT eDataFormat)
	{
		return m_pMethod->SetImageBuffer(pBuffer, nImageWidth, nImageHeight, nImageIndex, eDataFormat);
	}
	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const
	{
		return m_pMethod->SetInspectPosOffset(nStartOffsetX, nStartOffsetY, nEndOffsetX, nEndOffsetY);
	}
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const
	{
		return m_pMethod->SetInspectPosOffset(tInspectRegionOffset);
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

