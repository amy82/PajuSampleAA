#pragma once

#include <LibACMISImage\ACMISImageDef.h>

typedef struct _TLCBSpec
{
	double dCenterThreshold;
	double dEdgeThreshold;
	double dCornerThreshold;
	int nMaxSingleDefectNum;
	int nMinDefectWidthHeight;
	double dCenterMaxR;
	double dCenterMaxGr;
	double dCenterMaxGb;
	double dCenterMaxB;
	double dEdgeMaxR;
	double dEdgeMaxGr;
	double dEdgeMaxGb;
	double dEdgeMaxB;
	double dCornerMaxR;
	double dCornerMaxGr;
	double dCornerMaxGb;
	double dCornerMaxB;
	TCircleSpec tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TLCBSpec;

#define LCB_SPEC_FLAG_VERSION_MAJOR		1
#define LCB_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_LCB
{
	LCB_CENTER_THRESHOLD,
	LCB_EDGE_THRESHOLD,
	LCB_CORNER_THRESHOLD,
	LCB_MAX_SINGLE_DEFECT_NUM,
	LCB_MIN_DEFECT_SIZE,
	LCB_BLOCK_WIDTH,
	LCB_BLOCK_HEIGHT,

	LCB_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_LCB;

typedef struct _TLCBSpecN
{
	double dCenterThreshold;
	double dEdgeThreshold;
	double dCornerThreshold;
	int nMaxSingleDefectNum;
	int nMinDefectWidthHeight;
	double dCenterMaxR;
	double dCenterMaxGr;
	double dCenterMaxGb;
	double dCenterMaxB;
	double dEdgeMaxR;
	double dEdgeMaxGr;
	double dEdgeMaxGb;
	double dEdgeMaxB;
	double dCornerMaxR;
	double dCornerMaxGr;
	double dCornerMaxGb;
	double dCornerMaxB;
	TCircleSpecN tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TLCBSpecN;

typedef struct _TFDFSpec
{
	double dCenterThreshold;
	double dEdgeThreshold;
	double dCornerThreshold;
	int nMaxSingleDefectNum;
	int nMinDefectWidthHeight;
	int nMedianFilterWidth;
	int nMedianFilterHeight;
	int nWidthScaleRatio;
	int nHeightScaleRatio;
	int nWindowSize;
	int nEdgeSize;
	bool bEnableChannel;
	TCircleSpecN tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
}TFDFSpec;


#define FDF_SPEC_FLAG_VERSION_MAJOR		1
#define FDF_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_FDF
{
	FDF_CENTER_THRESHOLD,
	FDF_EDGE_THRESHOLD,
	FDF_CORNER_THRESHOLD,
	FDF_MAX_SINGLE_DEFECT_NUM,
	FDF_MIN_DEFECT_SIZE,
	FDF_BLOCK_WIDTH,
	FDF_BLOCK_HEIGHT,
	FDF_MEDIAN_FILTER_SIZE,
	FDF_LSC_BLOCK_SIZE,
	FDF_WINDOW_SIZE,
	FDF_EDGE_SIZE,
	FDF_ENABLE_CHANNEL,

	FDF_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_FDF;

typedef struct _TFDFSpecN
{
	double dCenterThreshold;
	double dEdgeThreshold;
	double dCornerThreshold;
	int nMaxSingleDefectNum;
	int nMinDefectWidthHeight;
	int nMedianFilterSize;
	int nLscBlockSize;
	int nWidthScaleRatio;
	int nHeightScaleRatio;
	int nWindowSize;
	int nEdgeSize;
	bool bEnableChannel;
	TCircleSpecN tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
}TFDFSpecN;


typedef struct _TRU_YmeanSpec
{
	// this algorithm doesn't have corner.
	int nEdgeSize;
	double fCenterThreshold;
	double fEdgeThreshold;
	double fCornerThreshold;
	int nDefectBlockSize;
	int nLscBlockSize;
	int nCalcType;
	double dMaxDefectSize;
	double dPixelSize;
	TCircleSpec tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TRU_YmeanSpec;

#define RU_YMEAN_SPEC_FLAG_VERSION_MAJOR		1
#define RU_YMEAN_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_RU_YMEAN
{
	RU_YMEAN_CENTER_THRESHOLD,
	RU_YMEAN_EDGE_THRESHOLD,
	RU_YMEAN_CORNER_THRESHOLD,
	RU_YMEAN_MIN_DEFECT_SIZE,
	RU_YMEAN_PIXEL_SIZE,
	RU_YMEAN_BLOCK_SIZE,
	RU_YMEAN_EDGE_SIZE,
	RU_YMEAN_LSC_BLOCK_SIZE,
	RU_YMEAN_CALC_TYPE,
	RU_YMEAN_MAX_RECURSIVE_COUNT,

	RU_YMEAN_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_RU_YMEAN;

typedef struct _TRU_YmeanSpecN
{
	// this algorithm doesn't have corner.
	int nEdgeSize;
	double fCenterThreshold;
	double fEdgeThreshold;
	double fCornerThreshold;
	int nDefectBlockSize;
	int nLscBlockSize;
	int nCalcType;
	int nMaxRecursiveCount;
	double dMaxDefectSize;
	double dPixelSize;
	TCircleSpecN tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TRU_YmeanSpecN;

typedef struct _TRUMultiFilterSpec
{
	int		nFilterSize[3];
	double  dZoneSizeRatio[3];

	int		nImageBoundaryThreshold;
	double	dChunkThreshold;
	//double	dBlobThreshold;
	double	dThreshold[3];
	int		nBlobSize[3];
} TRUMultiFilterSpec;

typedef struct _TRUBayerSpec
{
	int		method;

	int		nBlockSizeA;
	int		nBlockSizeB;

	double	nBlockThreshold;	//bins
	int		nBlockCountlimit;
} TRUBayerSpec;

typedef struct _TBlackSpotContrast
{
	int nBlockWidth;
	int nBlockHeight;
	int nClusterSize;
	int nDefectInCluster;
	double dDefectRatio;
	int nMaxSingleDefectNum;
	TCircleSpec tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TBlackSpotContrast;

#define BLACK_SPOT_CONTRAST_SPEC_FLAG_VERSION_MAJOR		1
#define BLACK_SPOT_CONTRAST_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_BLACK_SPOT_CONTRAST
{
	BLACK_SPOT_CONTRAST_Threshold,
	BLACK_SPOT_CONTRAST_BLOCK_WIDTH,
	BLACK_SPOT_CONTRAST_BLOCK_HEIGHT,
	BLACK_SPOT_CONTRAST_CLUSTER_SIZE,
	BLACK_SPOT_CONTRAST_DEFECT_IN_CLUSTER,
	BLACK_SPOT_CONTRAST_MAX_SINGLE_DEFECT_NUM,

	BLACK_SPOT_CONTRAST_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_BLACK_SPOT_CONTRAST;

typedef struct _TBlackSpotContrastN
{
	int nBlockWidth;
	int nBlockHeight;
	int nClusterSize;
	int nDefectInCluster;
	double dDefectRatio;
	int nMaxSingleDefectNum;
	TCircleSpecN tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TBlackSpotContrastN;

typedef struct _TBlemishOVTSpec
{
	int nBlockSize;
	int nMetaBlockSize;
	int nCalcType;
	double dDefectRatio;
	TCircleSpecN tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TBlemishOVTSpec;

typedef struct _TUnfocusedBlemish
{
	int nSingleDefectCount;
	int nMeanBlockSize;
	double dMaxBLValue[5]; // A1 ~ A5
	int nAllowedCount[5]; // A1 ~ A5
	int nRefAreaWidth; // A1,2,3,5
	int nGapAreaWidth; // A1,2,3,5
	int nRefAreaWidthEdge; // A4
	int nGapAreaWidthEdge; // A4
	int nCornerAreaSize; // A3
} TUnfocusedBlemish;

typedef struct _TFocusedBlemish
{
	int nSingleDefectCount;
	int nMeanBlockSize;
	double dMaxBLValue[5]; // A1 ~ A5
	int nAllowedCount[5]; // A1 ~ A5
	int nClusterSize;
	int nDefectInCluster;
	int nCornerAreaSize; // A3
	int nMaxSingleDefectNum;
} TFocusedBlemish;

typedef struct _TLCBPosSpec
{
	RECT nPosOffset;
} TLCBPosSpec;

template<typename T, typename DataType=BYTE, typename AREA=EImageRegion>
class IBlemishMethod
{
public:
	IBlemishMethod() {}
	virtual ~IBlemishMethod() {}

	typedef std::vector<TDefectResult> vDefectResult;

	virtual int Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& pSpec) = 0;
	virtual int GetSingleDefectCount() const = 0;
	virtual int GetDefectCount(AREA pos) const = 0;
	virtual const TDefectResult* GetDefectResult(AREA pos, int nIndex) const = 0;
	virtual const TDefectResult* GetMaxDefectResult(AREA pos) const = 0;
	virtual int GetDefectBlobCount() = 0;
	virtual const RECT* GetDefectBlobRect(int nIndex) = 0;
	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;

protected:
	std::string m_strLogHeader;
	std::string m_strLogData;
};

template<typename T, typename DataType=BYTE, typename AREA=EImageRegion>
class CACMISImage
{
protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<IBlemishMethod<T, DataType, AREA>> m_pMethod;
	CACMISImage() {}
	CACMISImage(const CACMISImage&) {}
#else
	IBlemishMethod<T, DataType, AREA>* m_pMethod;
	CACMISImage() : m_pMethod(NULL) {}
	CACMISImage(const CACMISImage&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISImage() {}

	inline int Inspect(const DataType* pBuffer, int nWidth, int nHeight, T& _Spec)
	{
		return m_pMethod->Inspect(pBuffer, nWidth, nHeight, _Spec);
	}
	inline int GetSingleDefectCount() const
	{
		return m_pMethod->GetSingleDefectCount();
	}
	inline int GetDefectCount(AREA pos) const
	{
		return m_pMethod->GetDefectCount(pos);
	}
	inline const TDefectResult* GetDefectResult(AREA pos, int nIndex) const
	{
		return m_pMethod->GetDefectResult(pos, nIndex);
	}
	inline const TDefectResult* GetMaxDefectResult(AREA pos) const
	{
		return m_pMethod->GetMaxDefectResult(pos);
	}
	inline int GetDefectBlobCount() const
	{
		return m_pMethod->GetDefectBlobCount();
	}
	inline const RECT* GetDefectBlobRect(int nIndex) const
	{
		return m_pMethod->GetDefectBlobRect(nIndex);
	}
	inline const char* GetLogHeader() const
	{
		return m_pMethod->GetLogHeader();
	}
	inline const char* GetLogData() const
	{
		return m_pMethod->GetLogData();
	}
};

//////////////////////////////////////////////////////////////////////////
// Blemish의 입력영상을 센서 입력 영상 그대로 사용하기 위해 Class 내 DataFormat 추가
template<typename T, typename DataType = BYTE, typename AREA = EImageRegion, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class IBlemishMethodCommon
{
public:
	IBlemishMethodCommon() : m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_Mask(NULL), m_nUsingMask(0), m_eSaturationMethod(SaturationMethod_Y), m_bIsCertified(false) { memset(&m_tDataSpec, 0, sizeof(TDATASPEC)); memset(&m_stSpec, 0, sizeof(T)); memset(&m_stCircleData, 0, sizeof(TCircleData)); memset(&m_tBorderLine, 0, sizeof(RECT)); memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset)); }
	virtual ~IBlemishMethodCommon() {}

	typedef std::vector<TDefectResult> vDefectResult;

	virtual bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool Inspect(TBufferInfo& tBufferInfo, T& _Spec) = 0;
	virtual bool Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual int GetSingleDefectCount() const = 0;
	virtual int GetDefectCount(AREA pos = EIMAGEREGION_CENTER) const = 0;
	virtual const TDefectResult* GetDefectResult(AREA pos, int nIndex) const = 0;
	virtual const TDefectResult* GetMaxDefectResult(AREA pos = EIMAGEREGION_CENTER) const = 0;
	virtual int GetDefectBlobCount() = 0;
	virtual const RECT* GetDefectBlobRect(int nIndex) = 0;
	virtual const TBlobResult* GetBlobDefectResult(int nIndex) = 0;
	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;
	virtual const char* GetVersion() = 0;
	virtual const TCircleData GetCircleData() = 0;
	virtual void SetCircleData(TCircleSpecN& Spec, TCircleData& tCircleData) = 0;
	virtual void SetMask(int nUsingMask, BYTE* pMask) = 0;
	virtual void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) = 0;
	virtual void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) = 0;
	virtual void Init() = 0;
	virtual const RECT* GetBorderLine() = 0;
	virtual double GetSaturationResult(int nIndex = 0) = 0;
	virtual void SetSaturationResult(int nIndex, double dSaturationResult) = 0;
	virtual void SetSaturationMethod(ESaturationMethod nMethod = SaturationMethod_Y) = 0;
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
	TCircleData m_stCircleData;
	BYTE* m_Mask;
	int m_nUsingMask;
	TInspectRegionOffset m_tInspectRegionOffset;
	RECT m_tBorderLine;
	std::vector<double> m_vSaturationResult;
	ESaturationMethod m_eSaturationMethod;
	bool m_bIsCertified;
};

template<typename T, typename DataType = BYTE, typename AREA = EImageRegion, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class CACMISBlemishCommon
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
	std::shared_ptr<IBlemishMethodCommon<T, DataType, AREA, DataFormat, OutMode, SensorType, DemosaicMethod>> m_pMethod;
	CACMISBlemishCommon() {}
	CACMISBlemishCommon(const CACMISBlemishCommon&) {}
#else
	IBlemishMethodCommon<T, DataType, AREA, DataFormat, OutMode, SensorType, DemosaicMethod>* m_pMethod;
	CACMISBlemishCommon() : m_pMethod(NULL) {}
	CACMISBlemishCommon(const CACMISBlemishCommon&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISBlemishCommon() {}

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
	inline int GetSingleDefectCount() const
	{
		return m_pMethod->GetSingleDefectCount();
	}
	inline int GetDefectCount(AREA pos = EIMAGEREGION_CENTER) const
	{
		return m_pMethod->GetDefectCount(pos);
	}
	inline const TDefectResult* GetDefectResult(AREA pos, int nIndex) const
	{
		return m_pMethod->GetDefectResult(pos, nIndex);
	}
	inline const TDefectResult* GetMaxDefectResult(AREA pos = EIMAGEREGION_CENTER) const
	{
		return m_pMethod->GetMaxDefectResult(pos);
	}
	inline int GetDefectBlobCount() const
	{
		return m_pMethod->GetDefectBlobCount();
	}
	inline const RECT* GetDefectBlobRect(int nIndex) const
	{
		return m_pMethod->GetDefectBlobRect(nIndex);
	}
	inline const TBlobResult* GetBlobDefectResult(int nIndex) const
	{
		return m_pMethod->GetBlobDefectResult(nIndex);
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
	inline const TCircleData GetCircleData() const
	{
		return m_pMethod->GetCircleData();
	}
	inline void SetCircleData(TCircleSpecN& Spec, TCircleData& tCircleData) const
	{
		return m_pMethod->SetCircleData(Spec, tCircleData);
	}
	inline void SetMask(int nUsingMask, BYTE* pMask) const
	{
		return m_pMethod->SetMask(nUsingMask, pMask);
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
	inline const RECT* GetBorderLine() const
	{
		return m_pMethod->GetBorderLine();
	}
	inline long long GetElapsedTime() const
	{
		return m_elapsedTime.count();
	}
	inline double GetSaturationResult(int nIndex) const
	{
		return m_pMethod->GetSaturationResult(nIndex);
	}
	inline void SetSaturationResult(int nIndex, double dSaturationResult) const
	{
		return m_pMethod->SetSaturationResult(nIndex, dSaturationResult);
	}
	virtual bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod, int nUsing8BitOnly = 0) { return true; }
	inline void SetSaturationMethod(ESaturationMethod nMethod) const
	{
		return m_pMethod->SetSaturationMethod(nMethod);
	}
	inline bool GetCertificationResult()
	{
		return m_pMethod->GetCertificationResult();
	}
};

