#pragma once

#include <LibACMISCommon\DataTypes.h>
#include <vector>
#include <memory>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <map>
#include <list>
#include <algorithm>
#include <atlstr.h>
#include <iostream>

using namespace std;

#define DEBUG_FILE_SAVE_PATH	"C:\\Users\\User\\Desktop"

typedef enum _EOUTMODE
{
	OUTMODE_BAYER_BGGR = 1, // Bayer
	OUTMODE_BAYER_RGGB,
	OUTMODE_BAYER_GBRG,
	OUTMODE_BAYER_GRBG,
	OUTMODE_BAYER_BLACKWHITE,
	OUTMODE_YUV422_YCbYCr = 1, // YUV422
	OUTMODE_YUV422_YCrYCb = 2,
	OUTMODE_YUV422_CbYCrY = 3,
	OUTMODE_YUV422_CrYCbY = 4,
	OUTMODE_RGB_BGR = 1, // RGB
	OUTMODE_RGB_RGB = 2,
	OUTMODE_BAYER_BNGR = 1, // RGB-IR Uniform pattern
	OUTMODE_BAYER_RGNB,
	OUTMODE_BAYER_NBRG,
	OUTMODE_BAYER_GRBN,
	OUTMODE_BAYER_BGGN = 1,	// RGB-IR Pattern 2
	OUTMODE_BAYER_RGGN,
	OUTMODE_BAYER_GBNG,
	OUTMODE_BAYER_GRNG,
	OUTMODE_BAYER_NGGR,
	OUTMODE_BAYER_NGGB,
	OUTMODE_BAYER_GNRG,
	OUTMODE_BAYER_GNBG,
} EOUTMODE;

typedef enum _EYCONVERTMETHOD
{
	Y_CONVERTMETHOD_ITU_R_601,
	Y_CONVERTMETHOD_ITU_R_709
} EYCONVERTMETHOD;
#define ITU_R_709_Y		0x80
#define OrgOutMode(x)	((EOUTMODE)(x & ~ITU_R_709_Y))

typedef enum _EDATAFORMAT
{
	DATAFORMAT_YUV,
	DATAFORMAT_BAYER_8BIT,
	DATAFORMAT_BAYER_10BIT,
	DATAFORMAT_BAYER_PARALLEL_10BIT,
	DATAFORMAT_BAYER_12BIT,
	DATAFORMAT_BAYER_PARALLEL_12BIT,
	DATAFORMAT_BAYER_16BIT,
	DATAFORMAT_BAYER_16BIT_BE,
	DATAFORMAT_BAYER_12BIT_PWL_HDR,
	DATAFORMAT_BAYER_16BIT_PWL_HDR,
	DATAFORMAT_BAYER_16BIT_PWL_DECOMP,
	DATAFORMAT_BAYER_24BIT,
	DATAFORMAT_BAYER_PARALLEL_10BIT_BE,
	DATAFORMAT_BAYER_PARALLEL_12BIT_BE,
	DATAFORMAT_RGB = 100,
	DATAFORMAT_INT = 200
} EDATAFORMAT;

typedef enum _ESENSORTYPE
{
	SENSORTYPE_RGGB = 0,
	SENSORTYPE_RCCC,
	SENSORTYPE_RCCB,
	SENSORTYPE_CCCC,
	SENSORTYPE_RBCC,
	SENSORTYPE_OTHER,
	SENSORTYPE_RGBIR2,
	MAX_COUNT_SENSORTYPE
} ESENSORTYPE;

#define SENSORTYPE_RGGB_VNG		8
#define SENSORTYPE_RGGB_G_ONLY	9

typedef enum _EDEMOSAICMETHOD
{
	DEMOSAICMETHOD_NONE = 0,
	DEMOSAICMETHOD_GRADIENT,
	DEMOSAICMETHOD_BL33, // Bilinear3x3
	DEMOSAICMETHOD_OPENCV_BL,
	DEMOSAICMETHOD_OPENCV_VNG,
	DEMOSAICMETHOD_OPENCV_EA,
	DEMOSAICMETHOD_VNG,  // Variable Number of Gradient
	DEMOSAICMETHOD_GR_ONLY,
	DEMOSAICMETHOD_GB_ONLY,
	DEMOSAICMETHOD_GBTF, // Gradient based Threshold Free
	DEMOSAICMETHOD_BLLC, // Bilinear Laplacian Corrected
	DEMOSAICMETHOD_RESIDUAL, // Residual Interpolation
	DEMOSAICMETHOD_BAYER_Y, // Y = (R + Gr + Gb + B) / 4
	DEMOSAICMETHOD_AHD, // Adaptive Homogeneity-Directed
	DEMOSAICMETHOD_GRADIENT_RESIDUAL = 101, // G(Gradient) + R/B/IR(RI)
	DEMOSAICMETHOD_GBTF_RESIDUAL, // G(GBTF) + R/B/IR(RI)
	DEMOSAICMETHOD_RESIDUAL_RESIDUAL, // G(RI) + R/B/IR(RI)
	DEMOSAICMETHOD_BL33_RESIDUAL, // G(BL33) + R/B/IR(RI)
	DEMOSAICMETHOD_IR_ONLY,
	DEMOSAICMETHOD_GRADIENT_G_ONLY, // G(Gradient)
	DEMOSAICMETHOD_GBTF_G_ONLY, // G(GBTF)
	DEMOSAICMETHOD_RESIDUAL_G_ONLY, // G(RI)
	DEMOSAICMETHOD_BL33_G_ONLY, // G(BL33)
	DEMOSAICMETHOD_GRADIENT_IR_ONLY, // IR(Gradient)
	DEMOSAICMETHOD_GBTF_IR_ONLY, // IR(GBTF)
	DEMOSAICMETHOD_RESIDUAL_IR_ONLY, // IR(RI)
	DEMOSAICMETHOD_BL33_IR_ONLY, // IR(BL33)
	MAX_COUNT_DEMOSAICMETHOD
} EDEMOSAICMETHOD;

typedef enum _EImageIndex
{
	/* ONSEMI or OVT Sensor */
	EImageIndex_Bright = 0,
	EImageIndex_Dark,
	EMax_ImageIndex_Count,
	/* Sony Sensor */
	EImageIndex_Highlight_SP1L = 0,
	EImageIndex_Highlight_SP2L,
	EImageIndex_Dark_SP1L,
	EImageIndex_Dark_SP2H,
	EImageIndex_Dark_SP2L,
	EImageIndex_Saturated_SP1H,
	EImageIndex_Saturated_SP1L,
	EImageIndex_Saturated_SP2H,
	EImageIndex_Saturated_SP2L,
	EMax_Sony_ImageIndex_Count
} EImageIndex;

typedef enum _EAlgorithmTestItem
{
	BLEMISH_BLACKSPOT = 0,
	BLEMISH_LCB,
	BLEMISH_FDF,
	BLEMISH_RU_YMEAN,
	RESOLUTION_EIAJ,
	RESOLUTION_SFR2FREQ,
	RESOLUTION_FREQ2SFR,
	OPTICAL_CENTER_CENTROID, // bkkim :: modified due to the duplicated definition
	OPTICAL_CENTER_BRIGHTEST,
	OPTICAL_CENTER_POLYFIT,        // bkkim :: modified due to the duplicated definition
	OPTICAL_CENTER_FIDUCIAL_MARK,  // bkkim :: modified due to the duplicated definition
	SNR_FPN,
	SNR_BW,
	SNR_NORM,
	SNR_DARK_CURRENT,
	SNR_VNE,
	SNR_DARK_NOISE,
	ETC_COLOR_REPRODUCTION,
	ETC_IR_FILTER,
	ETC_COLOR_INTENSITY,
	ETC_FOV,
	ETC_FLARE,
	ETC_VIEW_MODE,
	ETC_SATURATION,
	ETC_STRAY_LIGHT,
	DARK_BRIGHT,
	DARK_DARK,
	DARK_HOT,
	DARK_LINE_NOISE,
	DARK_LOW_LIGHT_DARK,
	DARK_ALL_DEFECT_ONSEMI,
	DARK_ALL_DEFECT_OMS,
	DARK_ALL_DEFECT_OV,
	DARK_ALL_DEFECT_SONY,
	DARK_ALL_DEFECT_RIVIAN,
	SHADING_COLOR_SHADING,
	SHADING_COLOR_SHADING_COMMON,
	SHADING_RELATIVE_ILLUMINATION,
	SHADING_RELATIVE_ILLUMINATION_COMMON,
	SHADING_RELATIVE_ILLUMINATION_X,
	SHADING_RELATIVE_UNIFORMITY,
	SHADING_COLOR_UNIFORMITY,
	SHADING_SHADING_UNIFORMITY,
	SHADING_COLOR_SENSITIVITY,
	SHADING_LENS_SHADING,
	ALGORITHM_TESTITEM_MAX
}AlgorithmTestItem;

typedef struct _TDATASPEC
{
	EOUTMODE eOutMode;
	EDATAFORMAT eDataFormat;
	ESENSORTYPE eSensorType;
	EDEMOSAICMETHOD eDemosaicMethod;
	int nBlackLevel;
} TDATASPEC;

typedef struct _TBufferInfo
{
	BYTE *pBuffer;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
} TBufferInfo;

typedef struct _TBufferInfoM
{
	BYTE **pBuffer;
	int nBufferCount;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
} TBufferInfoM;

typedef struct _TFileInfo
{
	char *strFileName;
	bool bIsRaw;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
} TFileInfo;

typedef struct _TFileInfoM
{
	char **strFileName;
	bool bIsRaw;
	int nFileCount;
	int nImageWidth;
	int nImageHeight;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
} TFileInfoM;

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
	TColorRatio(double _RG = 0.0, double _BG = 0.0, double _GrGb = 0.0, double _GrG = 0.0, double _GbG = 0.0, double _R = 0.0, double _G = 0.0, double _B = 0.0)
		: RG(_RG), BG(_BG), GrGb(_GrGb), GrG(_GrG), GbG(_GbG), R(_R), G(_G), B(_B), Gr(_G), Gb(_G)
	{
	}
};

typedef struct _TColorReproduction
{
	double L;
	double a;
	double b;
} TColorReproduction, TColorLab;

typedef enum _EROIType
{
	ROIType_RECT,
	ROIType_POINT,
	ROIType_FIELD,
	ROIType_SPOINT,
	ROIType_Common,
	ROIType_CPOINT = ROIType_POINT
} EROIType;

typedef struct _TROIPoint
{
	POINT ptCenter;
	LONG nROIWidth;
	LONG nROIHeight;
} TROIPoint, TROICPoint;

typedef struct _TROISPoint
{
	POINT ptStart;
	LONG nROIWidth;
	LONG nROIHeight;
} TROISPoint;

typedef struct _TROIField
{
	float fHorField;
	float fVerField;
	LONG nROIWidth;
	LONG nROIHeight;
} TROIField;

typedef struct _TROITemp
{
	EROIType eROIType;
	float fData[4];
}TROIDataCommon;

typedef struct _TROIData
{
	double *dOffset;
	EROIType eROIType;
	int ROICount;
	void *pROIData;
} TROIData;

typedef struct _TInspectRegionOffset
{
	int nStartOffsetX;
	int nStartOffsetY;
	int nEndOffsetX;
	int nEndOffsetY;
} TInspectRegionOffset;


// Image type
typedef enum _EImageFormat
{
	IMAGE_TYPE_BAYER,
	IMAGE_TYPE_RGB,
	IMAGE_TYPE_Y,
	IMAGE_TYPE_G, /* Tesla Trinity */
	/*IMAGE_TYPE_YUV,*/
	MAX_COUNT_IMAGE_TYPE
} EImageFormat;

// 입력 Image Info
typedef struct _tagInspectionImageInfo
{
	std::vector<int> vImageIndex;
	std::vector<int> vImageType;
	int nUsing8BitOnly;
	int nPartialDemosaic;
	TDATASPEC tDataSpec;
	EImageFormat eImageFormat;
}INSPECTION_IMAGE_INFO;

// 입력 구조체
typedef struct _tagInspectionInput
{
	AlgorithmTestItem enAlgorithmType;
	INSPECTION_IMAGE_INFO tImageInfo;
	void* pSpec;
	void* pSpecExtra;
	TROIData* pROI;
} INSPECTION_INPUT;


// 결과 구조체 - 통합
typedef struct _tagInspectionOutput
{
	AlgorithmTestItem enAlgorithmType;
	std::string strVersion;
	std::vector<std::string> vStrLogHeader;
	std::vector<std::string> vStrLogData;
	std::vector<int> vResultCode;
	int nElapsedTime;
	void* pInspectionResult;
} INSPECTION_RESULT;


struct DSIZE
{
	double	width;
	double	height;
};

typedef struct _DBox2D
{
	DBPOINT center;
	DSIZE size;
	double angle;
	double saturation;
} DBox2D;

typedef enum _EFlareTarget
{
	FlareTarget_Dot,
	FlareTarget_Window
} EFlareTarget;

typedef struct _TCircleData
{
	double dOcx;
	double dOcy;
	double dRadx;
	double dRady;
	double dAngle;
} TCircleData;

#define CIRCLE_FLAG_VERSION_MAJOR		1
#define CIRCLE_FLAG_VERSION_MINOR		0
typedef enum _CIRCLE_FLAG
{
	CIRCLE_ENABLE,
	CIRCLE_POS_OFFSET_X,
	CIRCLE_POS_OFFSET_Y,
	CIRCLE_RADIUS_RATIO_X,
	CIRCLE_RADIUS_RATIO_Y,
	CIRCLE_THRESHOLD_RATIO,
	CIRCLE_ROI_RANGE,
	CIRCLE_USED_FIXED_CIRCLE,

	CIRCLE_FLAG_MAX_COUNT
} CIRCLE_FLAG;

typedef struct _TCircleSpecN
{
	bool bEnableCircle;
	int nPosOffsetX;
	int nPosOffsetY;
	double dRadiusRatioX;
	double dRadiusRatioY;
	double dThresholdRatio;
	double dROIRange;
	int nUsedFixedCircle;
} TCircleSpecN;

#define CIRCLE_COMMON_FLAG_VERSION_MAJOR		1
#define CIRCLE_COMMON_FLAG_VERSION_MINOR		0
typedef enum _CIRCLE_COMMON_FLAG
{
	CIRCLE_COMMON_ENABLE,
	CIRCLE_COMMON_RADIUS_RATIO_X,
	CIRCLE_COMMON_RADIUS_RATIO_Y,
	CIRCLE_COMMON_USED_FIXED_CIRCLE,
	CIRCLE_DETECT_POS_OFFSET_X,
	CIRCLE_DETECT_POS_OFFSET_Y,
	CIRCLE_DETECT_THRESHOLD_RATIO,
	CIRCLE_DETECT_ROI_RANGE,
	CIRCLE_MULTI_ZONE_SIZE_RATIO_A,
	CIRCLE_MULTI_ZONE_SIZE_RATIO_B,
	CIRCLE_MULTI_ZONE_SIZE_RATIO_C,
	CIRCLE_MULTI_THRESHOLD_A,
	CIRCLE_MULTI_THRESHOLD_B,
	CIRCLE_MULTI_THRESHOLD_C,

	CIRCLE_COMMON_FLAG_MAX_COUNT
} CIRCLE_COMMON_FLAG;

typedef struct _TCircleSpecCommon
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
} TCircleSpecCommon;

typedef enum _ECircleEnable
{
	CIRCLE_DISABLE,
	CIRCLE_SINGLE_ENABLE,
	CIRCLE_MULTI_ENABLE
} ECircleEnable;

typedef enum _ETypicalValueType
{
	TypicalValue_Mean,
	TypicalValue_Median
} ETypicalValueType;

typedef enum _EFiducialMarkShape
{
	FiducialMarkShape_BlackCircle,
	FiducialMarkShape_WhiteCircle,
	FiducialMarkShape_CrossPoint,
	FiducialMarkShape_WhiteCircleInBlack,
	FiducialMarkShape_BlackPatch,
	FiducialMarkShape_WhitePatch,
	FiducialMarkShape_Vertex
} EFiducialMarkShape;

typedef enum _ESaturationMethod
{
	SaturationMethod_Y,
	SaturationMethod_Bayer,
	SaturationMethod_RGB,
	SaturationMethod_Bayer_G,
	SaturationMethod_RGB_G
} ESaturationMethod;

typedef struct _TFiducialMarkType
{
	CDPoint ptFiducialMarkPoint;
	int nFiducialMarkShape; // Shape of Fiducial Mark : BlackCircle(0), WhiteCircle(1), CrossPoint(2), WhiteCircle in Black(3), BlackPatch(4), WhitePatch(5), Vertex(6)
} TFiducialMarkType;

typedef struct _TFiducialMarkUse
{
	TFiducialMarkType tFiducialMarkType;
	int nInspectItem;
} TFiducialMarkUse;

enum
{
	EDGEDIR_VERTICAL,
	EDGEDIR_HORIZONTAL
};

typedef struct _THarrisCornerPoint
{
	POINT ptCorner;
	double dValue;
	int nPatchIndex;
} THarrisCornerPoint;

enum
{
	EPOS_CENTER,
	EPOS_LEFT,
	EPOS_TOP,
	EPOS_RIGHT,
	EPOS_BOTTOM
};

typedef struct _TPatchInfo
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

typedef enum _EMEANTYPE
{
	MEAN_TYPE_ALL,
	MEAN_TYPE_ROW,
	MEAN_TYPE_COLUMN,
	MEAN_TYPE_ALL_BAYER,
	MEAN_TYPE_ROW_BAYER,
	MEAN_TYPE_COLUMN_BAYER,
	MAX_COUNT_MEAN_TYPE
} EMEANTYPE;

typedef struct _COMPLEX
{
	double re;
	double im;
} COMPLEX;

class CRectEx
{
public:
	int left, top, right, bottom;

	CRectEx();
	CRectEx(int l, int t, int r, int b);
	int Width();
	int Height();
	void Offset(int x, int y);
	void SetRect(int lleft, int ltop, int lright, int lbottom);
	void SetRectCentered(int centerx, int centery, int width, int height);
	BOOL EvaluateRect(int width, int height);
	void AdjustRect(int width, int height);
	POINT CenterPoint();
	// POINT가 rect 안에 드는 것인지 검사해서 TRUE 리턴
	BOOL PointInRect(int x, int y);
	void InflateRect(int x, int y);
	RECT ToRECT() const;
};

// blob 하나, BLOB_RUN_LENGTH_DATA 의 리스트로 표현
class CBlobRect : public CRectEx
{
public:
	int Area;
	float Intensity;
	CBlobRect();

	CBlobRect(int l, int t, int r, int b);
	// 두개의 blobrect 를 하나로 합침
	CBlobRect operator + (CBlobRect& rect);

	// POINT 끼리의 거리 연산
	static double GetDistance(POINT A, POINT B);

	static float GetDistance(float x1, float y1, float x2, float y2);

	// 두 Blob Rect 간의 거리
	static double GetOuterDistance(CBlobRect& a, CBlobRect& b);
};

class CBlobList
{
private:
	std::vector <CBlobRect>* m_vecBlob;	// to avoid 'needs to have dll-interface' warning, declare pointer of vector...

public:
	CBlobList();
	~CBlobList();

	CBlobList(const CBlobList& c)
	{
		m_vecBlob = new std::vector<CBlobRect>(c.m_vecBlob->size());
		std::copy(c.m_vecBlob->begin(), c.m_vecBlob->end(), m_vecBlob->begin());
	}

	CBlobList& operator=(const CBlobList& c)
	{
		m_vecBlob->resize(c.m_vecBlob->size());
		std::copy(c.m_vecBlob->begin(), c.m_vecBlob->end(), m_vecBlob->begin());
		return (*this);
	}

	void Clear();
	void Add(CBlobRect obj);
	int Size();
	CBlobRect Get(int i);
	void Remove(int index);
	CBlobList operator + (CBlobList& bloblist);

	// width, height 범위로 Blob 필터링
	void SelectBlobWidthHeight(int width_low, int width_high, int height_low, int height_high, CBlobList*);
	void SelectBlobPosition(CRectEx rect, CBlobList* vecBlob);
};

extern void ConvertRECT2CPoint(RECT tROIRect, TROICPoint& tCenterPoint);
extern void ConvertRECT2CField(RECT tROIRect, int nImageWidth, int nImageHeight, TROIField& tField);
extern void ConvertRECT2SPoint(RECT tROIRect, TROISPoint& tStartPoint);
extern void ConvertRECT2TROIData(std::vector<RECT>& vROI_Rect, int nImageWidth, int nImageHeight, TROIData& tROI);

extern void Convert2RECT(TROICPoint tCenterPoint, RECT& tROIRect);
extern void Convert2RECT(TROIField tField, int nImageWidth, int nImageHeight, RECT& tROIRect);
extern void Convert2RECT(TROISPoint tStartPoint, RECT& tROIRect);

extern void Convert2TROICommon(TROICPoint tCenterPoint, TROIDataCommon& tROIData);
extern void Convert2TROICommon(TROIField tField, TROIDataCommon& tROIData);
extern void Convert2TROICommon(TROISPoint tStartPoint, TROIDataCommon& tROIData);
extern void Convert2TROICommon(RECT tRect, TROIDataCommon& tROIData);
extern void Convert2TROICommon(TROIData& tROI, std::vector<TROIDataCommon>& vROI);

extern void Convert2CPoint(TROIDataCommon tROIData, TROICPoint &tCenterPoint);
extern void Convert2Field(TROIDataCommon tROIData, TROIField &tField);
extern void Convert2SPoint(TROIDataCommon tROIData, TROISPoint &tStartPoint);
extern void Convert2RECT(TROIDataCommon tROIData, RECT& tRect);

extern void Convert2RECT(TROIDataCommon tROIData, int nWidth, int nHeight, RECT &tRect);
extern void Convert2RECT(TROIData& tROI, int nWidth, int nHeight, std::vector<RECT>& vROIRect);

extern double GetPixelSize(EDATAFORMAT eDataFormat);

extern double Get8BitConversionGamma(EDATAFORMAT eDataFormat);
extern double Get16BitConversionGamma(EDATAFORMAT eDataFormat);

extern bool LoadFiducialMarkInfo(const char* strFiducialMarkInfoPath, int nImageWidth, int nImageHeight, TInspectRegionOffset& tOffset, std::vector<TFiducialMarkType>& vFiducialMarkPoint, int& nMaxSize);

extern void CalcElapsedTime(std::chrono::system_clock::time_point& m_startTime, std::chrono::system_clock::time_point& m_endTime, std::chrono::milliseconds& m_elapsedTime, std::chrono::milliseconds& m_startTimems, std::chrono::milliseconds& m_endTimems);

extern void CheckDemosaicMethod(ESENSORTYPE &nSensorType, EDEMOSAICMETHOD &nDemosaicMethod, EOUTMODE nOutMode = OUTMODE_BAYER_RGGB);

extern std::string GetAlgorithmName(int nSpecIndex);

extern bool CheckROISize(TROIData& tROI);

typedef enum _VAR_TYPE
{
	VAR_TYPE_BYTE = 0,
	VAR_TYPE_SHORT,
	VAR_TYPE_USHORT,
	VAR_TYPE_INT,
	VAR_TYPE_FLOAT,
	VAR_TYPE_DOUBLE
} VAR_TYPE;

#define MAKE_VERION(T,M,m)	((unsigned int)((T << 16) | (M << 8) | m))
#define GET_TYPE(V)			((unsigned int)((V >> 16) & 0xFFFF))
#define GET_MAJOR(V)		((unsigned int)((V >> 8) & 0xFF))
#define GET_MINOR(V)		((unsigned int)(V & 0xFF))

typedef enum _SPEC_TYPE
{
	/* Defect Pixel */
	SPEC_TYPE_DEFECT_PIXEL,
	SPEC_TYPE_HOT_DEFECT_PIXEL,
	SPEC_TYPE_VERY_DEFECT_PIXEL,
	SPEC_TYPE_LINE_NOISE,
	SPEC_TYPE_COLUMN_FPN,
	SPEC_TYPE_LOW_LIGHT_DARK_TEST,
	SPEC_TYPE_ALL_DEFECT_ONSEMI,
	SPEC_TYPE_ALL_DEFECT_ONSEMI_RCCB = SPEC_TYPE_ALL_DEFECT_ONSEMI,
	SPEC_TYPE_ALL_DEFECT_ONSEMI_MONO = SPEC_TYPE_ALL_DEFECT_ONSEMI,
	SPEC_TYPE_ALL_DEFECT_OMS,
	SPEC_TYPE_ALL_DEFECT_OV,
	SPEC_TYPE_ALL_DEFECT_SONY,

	/* Blemish */
	SPEC_TYPE_BLACKSPOT,
	SPEC_TYPE_LCB,
	SPEC_TYPE_YMEAN,
	SPEC_TYPE_FDF,
	SPEC_TYPE_BLEMSIH_FFT,

	/* Optical Center */
	SPEC_TYPE_OC_CETROID,
	SPEC_TYPE_OC_CETROID_BAYER = SPEC_TYPE_OC_CETROID,
	SPEC_TYPE_OC_CETROID_G = SPEC_TYPE_OC_CETROID,
	SPEC_TYPE_OC_CETROID_RGB = SPEC_TYPE_OC_CETROID,
	SPEC_TYPE_OC_CETROID_Y = SPEC_TYPE_OC_CETROID,
	SPEC_TYPE_OC_POLYFIT,
	SPEC_TYPE_OC_BRIGHTEST,

	/* Signal to Noise Ratio */
	SPEC_TYPE_SNR_NORM,
	SPEC_TYPE_SNR_VNE = SPEC_TYPE_SNR_NORM,
	SPEC_TYPE_SNR_PATTERN_NOISE,
	SPEC_TYPE_SNR_BW,
	SPEC_TYPE_DARK_CURRENT,
	SPEC_TYPE_DARK_NOISE,

	/* Resolution */
	SPEC_TYPE_SFR,
	SPEC_TYPE_EIAJ,
	SPEC_TYPE_FIDUCIAL_MARK,

	/* Shading */
	SPEC_TYPE_COLOR_SENSITIVITY,
	SPEC_TYPE_COLOR_SHADING,
	SPEC_TYPE_RELATIVE_ILLUMINATION,
	SPEC_TYPE_RELATIVE_ILLUMINATION_X,
	SPEC_TYPE_RELATIVE_UNIFORMITY,
	SPEC_TYPE_SHADING_UNIFORMITY,
	SPEC_TYPE_COLOR_UNIFORMITY,
	SPEC_TYPE_LENS_SHADING,

	/* Etc */
	SPEC_TYPE_COLOR_INTENSITY,
	SPEC_TYPE_COLOR_REPRODUCTION,
	SPEC_TYPE_IR_FILTER,
	SPEC_TYPE_FLARE,
	SPEC_TYPE_VIEW_MODE,
	SPEC_TYPE_SATURATION,
	SPEC_TYPE_STRAY_LIGHT,

	MAX_SPEC_TYPE_COUNT
} SPEC_TYPE;

typedef enum _ROI_TYPE
{
	/* Defect Pixel */
	/*ROI_TYPE_DEFECT_PIXEL,*/
	/*ROI_TYPE_HOT_DEFECT_PIXEL,*/
	/*ROI_TYPE_VERY_DEFECT_PIXEL,*/
	/*ROI_TYPE_LINE_NOISE,*/
	/*ROI_TYPE_COLUMN_FPN,*/
	/*ROI_TYPE_LOW_LIGHT_DARK_TEST,*/
	/*ROI_TYPE_ALL_DEFECT_ONSEMI,*/
	/*ROI_TYPE_ALL_DEFECT_ONSEMI_RCCB = ROI_TYPE_ALL_DEFECT_ONSEMI,*/
	/*ROI_TYPE_ALL_DEFECT_ONSEMI_MONO = ROI_TYPE_ALL_DEFECT_ONSEMI,*/
	/*ROI_TYPE_ALL_DEFECT_OMS,*/
	/*ROI_TYPE_ALL_DEFECT_OV,*/
	/*ROI_TYPE_ALL_DEFECT_SONY,*/

	/* Blemish */
	/*ROI_TYPE_BLACKSPOT,*/
	/*ROI_TYPE_LCB,*/
	/*ROI_TYPE_YMEAN,*/
	/*ROI_TYPE_FDF,*/
	/*ROI_TYPE_BLEMSIH_FFT,*/

	/* Optical Center */
	/*ROI_TYPE_OC_CETROID,*/
	/*ROI_TYPE_OC_CETROID_BAYER = ROI_OC_TYPE_CETROID,*/
	/*ROI_TYPE_OC_CETROID_G = ROI_OC_TYPE_CETROID,*/
	/*ROI_TYPE_OC_CETROID_RGB = ROI_OC_TYPE_CETROID,*/
	/*ROI_TYPE_OC_CETROID_Y = ROI_OC_TYPE_CETROID,*/
	/*ROI_TYPE_OC_POLYFIT,*/
	/*ROI_TYPE_OC_BRIGHTEST,*/

	/* Signal to Noise Ratio */
	ROI_TYPE_SNR_NORM,
	ROI_TYPE_SNR_VNE = ROI_TYPE_SNR_NORM,
	ROI_TYPE_SNR_PATTERN_NOISE,
	ROI_TYPE_SNR_BW,
	ROI_TYPE_DARK_CURRENT,
	ROI_TYPE_DARK_NOISE,

	/* Resolution */
	ROI_TYPE_SFR,
	ROI_TYPE_EIAJ,
	ROI_TYPE_FIDUCIAL_MARK,

	/* Shading */
	ROI_TYPE_COLOR_SENSITIVITY,
	ROI_TYPE_COLOR_SHADING,
	ROI_TYPE_RELATIVE_ILLUMINATION,
	/*ROI_TYPE_RELATIVE_ILLUMINATION_X,*/
	/*ROI_TYPE_RELATIVE_UNIFORMITY,*/
	ROI_TYPE_SHADING_UNIFORMITY,
	/*ROI_TYPE_COLOR_UNIFORMITY,*/
	/*ROI_TYPE_LENS_SHADING,*/

	/* Etc */
	ROI_TYPE_COLOR_INTENSITY,
	ROI_TYPE_COLOR_REPRODUCTION,
	ROI_TYPE_IR_FILTER,
	ROI_TYPE_FLARE,
	ROI_TYPE_VIEW_MODE,
	ROI_TYPE_SATURATION,
	ROI_TYPE_STRAY_LIGHT,

	MAX_ROI_TYPE_COUNT
} ROI_TYPE;

typedef enum _RESULT_ROI_TYPE
{
	/* Defect Pixel, Blemish */
	/*RESULT_ROI_TYPE_DEFECT,*/
	/*RESULT_ROI_TYPE_BLOB,*/

	/* Optical Center */
	/*RESULT_ROI_TYPE_OC,*/

	/* Signal to Noise Ratio */
	/*RESULT_ROI_TYPE_SNR_NORM,*/
	/*RESULT_ROI_TYPE_SNR_VNE = RESULT_ROI_TYPE_SNR_NORM,*/
	/*RESULT_ROI_TYPE_PATTERN_NOISE,*/
	/*RESULT_ROI_TYPE_SNR_BW,*/
	/*RESULT_ROI_TYPE_DARK_CURRENT,*/
	RESULT_ROI_TYPE_DARK_NOISE,

	/* Resolution */
	/*RESULT_ROI_TYPE_SFR,*/
	/*RESULT_ROI_TYPE_EIAJ,*/
	/*RESULT_ROI_TYPE_FIDUCIAL_MARK,*/

	/* Shading */
	/*RESULT_ROI_TYPE_COLOR_SENSITIVITY,*/
	RESULT_ROI_TYPE_COLOR_SHADING,
	RESULT_ROI_TYPE_RELATIVE_ILLUMINATION,
	/*RESULT_ROI_TYPE_RELATIVE_ILLUMINATION_X,*/
	/*RESULT_ROI_TYPE_RELATIVE_UNIFORMITY,*/
	/*RESULT_ROI_TYPE_SHADING_UNIFORMITY,*/
	/*RESULT_ROI_TYPE_COLOR_UNIFORMITY,*/
	/*RESULT_ROI_TYPE_LENS_SHADING,*/

	/* Etc */
	/*RESULT_ROI_TYPE_COLOR_INTENSITY,*/
	/*RESULT_ROI_TYPE_COLOR_REPRODUCTION,*/
	/*RESULT_ROI_TYPE_IR_FILTER,*/
	RESULT_ROI_TYPE_FLARE,
	RESULT_ROI_TYPE_VIEW_MODE,
	/*RESULT_ROI_TYPE_SATURATION,*/
	RESULT_ROI_TYPE_STRAY_LIGHT,

	MAX_RESULT_ROI_TYPE_COUNT
} RESULT_ROI_TYPE;

typedef enum _RESULT_TYPE
{
	/* Defect Pixel, Blemish */
	RESULT_TYPE_DEFECT,
	RESULT_TYPE_BLOB,

	/* Optical Center */
	RESULT_TYPE_OC,

	/* Signal to Noise Ratio */
	RESULT_TYPE_SNR_NORM,
	RESULT_TYPE_SNR_VNE = RESULT_TYPE_SNR_NORM,
	RESULT_TYPE_PATTERN_NOISE,
	RESULT_TYPE_SNR_BW,
	RESULT_TYPE_DARK_CURRENT,
	RESULT_TYPE_DARK_NOISE,

	/* Resolution */
	RESULT_TYPE_SFR,
	RESULT_TYPE_EIAJ,
	RESULT_TYPE_FIDUCIAL_MARK,

	/* Shading */
	RESULT_TYPE_COLOR_SENSITIVITY,
	RESULT_TYPE_COLOR_SHADING,
	RESULT_TYPE_RELATIVE_ILLUMINATION,
	RESULT_TYPE_RELATIVE_ILLUMINATION_X,
	RESULT_TYPE_RELATIVE_UNIFORMITY,
	RESULT_TYPE_SHADING_UNIFORMITY,
	RESULT_TYPE_COLOR_UNIFORMITY,
	RESULT_TYPE_LENS_SHADING,

	/* Etc */
	RESULT_TYPE_COLOR_INTENSITY,
	RESULT_TYPE_COLOR_REPRODUCTION,
	RESULT_TYPE_IR_FILTER,
	RESULT_TYPE_FLARE,
	RESULT_TYPE_VIEW_MODE,
	RESULT_TYPE_SATURATION,
	RESULT_TYPE_STRAY_LIGHT,

	MAX_RESULT_TYPE_COUNT
} RESULT_TYPE;

#define MULTI_CIRCLE_FLAG_VERSION_MAJOR		1
#define MULTI_CIRCLE_FLAG_VERSION_MINOR		0
typedef enum _MULTI_CIRCLE_FLAG
{
	MULTI_CIRCLE_ENABLE,
	MULTI_CIRCLE_ZONE_SIZE_RATIO_A,
	MULTI_CIRCLE_ZONE_SIZE_RATIO_B,
	MULTI_CIRCLE_ZONE_SIZE_RATIO_C,
	MULTI_CIRCLE_THRESHOLD_A,
	MULTI_CIRCLE_THRESHOLD_B,
	MULTI_CIRCLE_THRESHOLD_C,

	MULTI_CIRCLE_FLAG_MAX_COUNT
} MULTI_CIRCLE_FLAG;

typedef struct _TInspectROIData
{
	unsigned int nVersion;
	int nMaxROIFlagCount;
	float fROIFlag[20]; /* 0: ROI type, 1 ~ 4: ROI data, 5: Offset, 6: Min Threshold, 7: Max Threshold, 8 ~ : Variable for each algorithm */
} TInspectROIData;

typedef struct _TInspectSpec
{
	unsigned int nVersion;
	int nROICount;
	TInspectROIData *tROI;
	int nMaxSpecFlagCount;
	float fSpecFlag[100];
	int nMaxEtcFlagCount;
	float fEtcFlag[10];
	TInspectRegionOffset tInspectRegionOffset;
	float fCircleSpec[CIRCLE_COMMON_FLAG_MAX_COUNT]; /* TCircleSpecCommon */
} TInspectSpec;

typedef struct _TInspectResult
{
	unsigned int nVersion;
	int nROICount;
	TInspectROIData *tROI;
	int nMaxResultCount;
	float fResult[100];
} TInspectResult;


// 싱글톤 패턴 매크로
#define MAKE_SINGLETON(classname)						\
private:												\
	classname() {}										\
	classname(const classname&) = delete;				\
	classname& operator=(const classname&) = delete;	\
public:													\
	static classname& GetInstance()						\
	{													\
		static classname instance;						\
		return instance;								\
	}													\
private: