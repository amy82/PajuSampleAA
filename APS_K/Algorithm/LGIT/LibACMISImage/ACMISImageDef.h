#pragma once

//#include <XGraphic\xDataTypes.h>
#include "../../INSP/XGraphic/xDataTypes.h"
#include <vector>
#include <memory>
//#include <LibACMISCommon\ACMISCommon.h>
#include "../LibACMISCommon/ACMISCommon.h"

typedef enum _EImageRegion
{
	EIMAGEREGION_CENTER,
	EIMAGEREGION_EDGE,
	EIMAGEREGION_CORNER,
	EIMAGEREGION_CIRCLE,
	EIMAGEREGION_MAX
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
} TDefectResult;

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

typedef struct _TRU_YmeanSpec
{
	// this algorithm doesn't have corner.
	int nEdgeSize;
	float fCenterThreshold;
	float fEdgeThreshold;
	float fCornerThreshold;
	int nDefectBlockSize;
	int nLscBlockSize;
	int nCalcType;
	TCircleSpec tCircleSpec;
	TMultiCircleSpec tMultiCircleSpec;
} TRU_YmeanSpec;

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

typedef struct _TDarkDefectPixel
{
	int nBlockSize;
	double dDefectRatio;
	int nMaxSingleDefectNum;
	int nPixelOrder;
	int nDefectInCluster;
	int bEnableDetectGrGbCluster;
} TDarkDefectPixel;

//1: white pixels in the dark; 2: white pixels at high light; 3: black pixels at high light
typedef enum _EDPCType
{
	EDPCType_WhitePixelDark,
	EDPCType_WhitePixelHighlight,
	EDPCType_BlackPixelHighlight,
} EDPCType;

typedef enum _EDefectType
{
	EDefectType_WhitePixel,
	EDefectType_BlackPixel
} EDefectType;

typedef enum _ELightCondition
{
	ELightCondition_Highlight,
	ELightCondition_Dark
} ELightCondition;

typedef struct _TDefectPixelCalibration
{
	int nDefectPixelType;
	int nLightContition;
	double dDefectSpec;
	int nMaxCoupletNum;
	int nBlockSize;
	RECT stROI;
} TDefectPixelCalibration;

typedef struct _TFDWhitePixel
{
	int nLightContition;
	double dDefectSpec[2];
	int nBlockSize;
} TFDWhitePixel;

typedef struct _TDarkDefectPixel TDarkDefectCluster;

typedef struct _TDarkDefectPixel TDarkShading;

typedef struct _TDarkBLC
{
	double dBLCspec;
	double dBLCAccuracyResult[4]; // per bayer channel
} TDarkBLC;

typedef struct _TDarkLineNoise
{
	double dLineNoiseSpec;
	double dDarkLineNoise[4][2]; // Horizontal, Vertical
} TDarkLineNoise;

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

typedef struct _TBadPixelTable
{
//	int nBadPixelBrightSpec;
	int nMaxBadPixelBlobSpec;
	int nBlockSizeX;
	int nBlockSizeY;
	double dConstantMultipeBrightSpec;
	double dConstantPlusBrightSpec;
} TBadPixelTable;

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
template<typename T, typename DataType = BYTE, typename AREA = EImageRegion, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE>
class IBlemishMethodCommon
{
public:
	IBlemishMethodCommon() {}
	virtual ~IBlemishMethodCommon() {}

	typedef std::vector<TDefectResult> vDefectResult;

	virtual int Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false) = 0;
	virtual int Inspect(TBufferInfo& tBufferInfo, T& _Spec) = 0;
	virtual int Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual int GetSingleDefectCount() const = 0;
	virtual int GetDefectCount(AREA pos) const = 0;
	virtual const TDefectResult* GetDefectResult(AREA pos, int nIndex) const = 0;
	virtual const TDefectResult* GetMaxDefectResult(AREA pos = EIMAGEREGION_CENTER) const = 0;
	virtual int GetDefectBlobCount() = 0;
	virtual const RECT* GetDefectBlobRect(int nIndex) = 0;
	virtual const TBlobResult* GetBlobDefectResult(int nIndex) = 0;
	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;
	virtual const char* GetVersion() = 0;

protected:
	std::string m_strLogHeader;
	std::string m_strLogData;
	std::string m_strVersion;
};

template<typename T, typename DataType = BYTE, typename AREA = EImageRegion, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE>
class CACMISImageCommon
{
protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<IBlemishMethodCommon<T, DataType, AREA, DataFormat, OutMode>> m_pMethod;
	CACMISImageCommon() {}
	CACMISImageCommon(const CACMISImageCommon&) {}
#else
	IBlemishMethodCommon<T, DataType, AREA, DataFormat, OutMode>* m_pMethod;
	CACMISImageCommon() : m_pMethod(NULL) {}
	CACMISImageCommon(const CACMISImageCommon&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISImageCommon() {}

	inline int Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false)
	{
		return m_pMethod->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, nDataFormat, nOutMode, nSensorType, nBlackLevel, bUsing8BitOnly);
	}
	inline int Inspect(TBufferInfo& tBufferInfo, T& _Spec)
	{
		return m_pMethod->Inspect(tBufferInfo, _Spec);
	}
	inline int Inspect(TFileInfo& tFileInfo, T& _Spec)
	{
		return m_pMethod->Inspect(tFileInfo, _Spec);
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
	inline const char* GetLogHeader() const
	{
		return m_pMethod->GetLogHeader();
	}
	inline const char* GetLogData() const
	{
		return m_pMethod->GetLogData();
	}
	inline const char* GetVersion() const
	{
		return m_pMethod->GetVersion();
	}
};

//////////////////////////////////////////////////////////////////////////
// Optical Center

typedef struct _TOpticalCenter
{
	double dOpticalCenterSpecX;
	double dOpticalCenterSpecY;
	double dPixelPitch;
	int nOcBlockSize;
	int nedgeTopMargin;
} TOpticalCenter;

typedef struct _TOpticalCenterRgb
{
	double dOpticalCenterSpecX;
	double dOpticalCenterSpecY;
	double dPixelPitch;
	int nOcBlockSize;
	int nedgeTopMargin;
} TOpticalCenterRgb;

typedef struct _TOpticalCenterPolyFit
{
	double dOpticalCenterSpecX;
	double dOpticalCenterSpecY;
	double dPixelPitch;
} TOpticalCenterPolyFit;

template<typename T, typename DataType=BYTE>
class IOpticalCenterMethod
{
public:
	IOpticalCenterMethod() {}
	virtual ~IOpticalCenterMethod() {}

	virtual int Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& pSpec) = 0;

	virtual const DPOINT* GetOpticalCenterResult() = 0;

	virtual int GetSubPointCount() = 0;

	virtual const POINT* GetSubPoint(int nIndex) = 0;

	virtual const char* GetLogHeader() = 0;

	virtual const char* GetLogData() = 0;

protected:
	std::string m_strLogHeader;
	std::string m_strLogData;
};

template<typename T, typename DataType=BYTE> class CACMISOpticalCenter
{
protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<IOpticalCenterMethod<T, DataType>> m_pMethod;
	CACMISOpticalCenter() {}
	CACMISOpticalCenter(const CACMISOpticalCenter&) {}
#else
	IOpticalCenterMethod<T, DataType>* m_pMethod;
	CACMISOpticalCenter() : m_pMethod(NULL) {}
	CACMISOpticalCenter(const CACMISOpticalCenter&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISOpticalCenter() {}

	inline int Inspect(const DataType* pBuffer, int nWidth, int nHeight, T& _Spec)
	{
		return m_pMethod->Inspect(pBuffer, nWidth, nHeight, _Spec);
	}
	inline const DPOINT* GetOpticalCenterResult() const
	{
		return m_pMethod->GetOpticalCenterResult();
	}
	inline int GetSubPointCount() const
	{
		return m_pMethod->GetSubPointCount();
	}
	inline const POINT* GetSubPoint(int nIndex) const
	{
		return m_pMethod->GetSubPoint(nIndex);
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
// Signal to Noise Ratio

typedef enum _EPatternNoiseType
{
	EFPN_DSNU,
	EFPN_PRNU
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

typedef struct _TSNROECFSpec
{
	int nROIWidth;
	int nROIHeight;
	int nLscBlockSize;
	int nMaxROICount;
	POINT *ptROICenter;
	double dSNRThreshold;
} TSNROECFSpec;

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

template<typename T, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE>
class ISignalNoiseRatio
{
protected:
	int GetPixelSize()
	{
		int nPixelSize = 1;

		switch(m_tDataSpec.eDataFormat)
		{
		case DATAFORMAT_BAYER_8BIT:
		case DATAFORMAT_YUV:
			nPixelSize = 1;
			break;
		case DATAFORMAT_BAYER_10BIT:
		case DATAFORMAT_BAYER_12BIT:
		case DATAFORMAT_BAYER_PARALLEL_10BIT:
		case DATAFORMAT_BAYER_PARALLEL_12BIT:
			nPixelSize = 2;
			break;
		default:
			nPixelSize = 1;
			break;
		}

		return nPixelSize;
	}

public:
	ISignalNoiseRatio() : m_nImageWidth(0), m_nImageHeight(0), m_bUsing8BitOnly(false) {}
	virtual ~ISignalNoiseRatio() {}

	typedef std::vector<TSNRResult> vSNRResult;

	virtual int Inspect() = 0;
	virtual int Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false) = 0;
	virtual int Inspect(TBufferInfo& tBuferInfo, T& _Spec) = 0;
	virtual int Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual int GetSNRRegionCount() = 0;
	virtual const TSNRResult* GetSNRResult(int nIndex) = 0;
	virtual const TSNRResult* GetMinSNRResult() = 0;
	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;
	virtual const char* GetVersion() = 0;
	virtual int SetImageSpec(int nImageWidth, int nImageHeight, int nImageCount, T& pSpecc, EDATAFORMAT dataFormat, EOUTMODE outMode, ESENSORTYPE sensorType, int nBlackLevel, bool bUsing8BitOnly = false) = 0;
	virtual int SetImageBuffer(const DataType* pBuffer, int nImageWidth, int nImageHeight, int nImageIndex) = 0;

protected:
	int m_nImageWidth;
	int m_nImageHeight;
	bool m_bUsing8BitOnly;
	std::string m_strLogHeader;
	std::string m_strLogData;
	std::string m_strVersion;
	TDATASPEC m_tDataSpec;
	T m_pSpec;
	vSNRResult m_vSNRResult;

	std::vector< std::vector<BYTE> > m_vRawBuffer;
};

template<typename T, typename DataType = BYTE, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE>
class CACMISSignalNoiseRatio
{
protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<ISignalNoiseRatio<T, DataType, DataFormat, OutMode>> m_pMethod;
	CACMISSignalNoiseRatio() {}
	CACMISSignalNoiseRatio(const CACMISSignalNoiseRatio&) {}
#else
	ISignalNoiseRatio<T, DataType>* m_pMethod;
	CACMISSignalNoiseRatio() : m_pMethod(NULL) {}
	CACMISSignalNoiseRatio(const CACMISSignalNoiseRatio&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISSignalNoiseRatio() {}

	inline int Inspect()
	{
		return m_pMethod->Inspect();
	}
	inline int Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false)
	{
		return m_pMethod->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, nDataFormat, nOutMode, nSensorType, nBlackLevel, bUsing8BitOnly);
	}
	inline int Inspect(TBufferInfo& tBufferInfo, T& _Spec)
	{
		return m_pMethod->Inspect(tBufferInfo, _Spec);
	}
	inline int Inspect(TFileInfo& tFileInfo, T& _Spec)
	{
		return m_pMethod->Inspect(tFileInfo, _Spec);
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
	inline const char* GetLogHeader() const
	{
		return m_pMethod->GetLogHeader();
	}
	inline const char* GetLogData() const
	{
		return m_pMethod->GetLogData();
	}
	inline const char* GetVersion() const
	{
		return m_pMethod->GetVersion();
	}
	inline int SetImageSpec(int nImageWidth, int nImageHeight, int nImageCount, T& pSpec, EDATAFORMAT dataFormat, EOUTMODE outMode, ESENSORTYPE sensorType, int nBlackLevel, bool bUsing8BitOnly = false) const
	{
		return m_pMethod->SetImageSpec(nImageWidth, nImageHeight, nImageCount, pSpec, dataFormat, outMode, sensorType, nBlackLevel, bUsing8BitOnly);
	}
	inline int SetImageBuffer(const DataType* pBuffer, int nImageWidth, int nImageHeight, int nImageIndex)
	{
		return m_pMethod->SetImageBuffer(pBuffer, nImageWidth, nImageHeight, nImageIndex);
	}
};

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