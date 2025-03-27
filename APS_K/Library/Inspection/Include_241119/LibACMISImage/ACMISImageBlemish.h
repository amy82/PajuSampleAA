#pragma once

#include "export.h"
#include "ACMISBlemishDef.h"

// DO NOT INCLUDE HEADER FILE
class CImageHistogramEq;

enum { HistogramEQ_NONE, HistogramEQ_CLAHE, HistogramEQ_WholeRegion, HistogramEQ_Binary, HistogramEQ_CumulativeCLAHE };

class ACMISIMAGE_API CACMISImageHistogramEqualizer
{
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<CImageHistogramEq> m_pHistogramEq;
#else
	CImageHistogramEq* m_pHistogramEq;
#endif

public:
	CACMISImageHistogramEqualizer();
	~CACMISImageHistogramEqualizer();

	bool HistogramEqualizerCLAHE(BYTE* pBMPBuffer, BYTE* pYBuffer, int nImageWidth, int nImageHeight, int nMinGrayValue = 30, int nMaxGrayValue = 255,
		unsigned int nContextualRegionX = 16, unsigned int nContextualRegionY = 12, unsigned int nNumOfGrayBin = 200, float fNormalizedClipLimit = 20);

	bool HistogramEqualizerWholeRegion(BYTE* pBMPBuffer, int nImageWidth, int nImageHeight);

	bool HistogramEqualizerBinary(BYTE* pBMPBuffer, int nImageWidth, int nImageHeight);

	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod);
};


//class ACMISIMAGE_API CACMISImageBlackSpotContrast : public CACMISImage<TBlackSpotContrast>
//{
//public:
//	CACMISImageBlackSpotContrast();
//	~CACMISImageBlackSpotContrast();
//};

class ACMISIMAGE_API CACMISImageBlackSpotContrastCommon : public CACMISImageCommon<TBlackSpotContrastN>
{
public:
	CACMISImageBlackSpotContrastCommon();
	~CACMISImageBlackSpotContrastCommon();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TBlackSpotContrast& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT); // for backward compatibility
	bool Inspect(TBufferInfo& tBufferInfo, TBlackSpotContrast& _Spec); // for backward compatibility
	bool Inspect(TFileInfo& tFileInfo, TBlackSpotContrast& _Spec); // for backward compatibility
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TBlackSpotContrastN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TBlackSpotContrastN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TBlackSpotContrastN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TBlackSpotContrastN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TBlackSpotContrastN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TBlackSpotContrastN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TBlackSpotContrastN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TBlackSpotContrastN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TBlackSpotContrastN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(TBufferInfoM& tBufferInfo, TBlackSpotContrastN& _Spec);
	bool InspectM_OMS(TFileInfoM& tFileInfo, TBlackSpotContrastN& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TBlackSpotContrastN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod);

private:
	bool ConvertSpec(TBlackSpotContrast _Spec, TBlackSpotContrastN& _NewSpec); // Convert Spec from TBlackSpotContrast to TBlackSpotContrastN
};


//class ACMISIMAGE_API CACMISImageFocusedBlemish : public CACMISImage<TFocusedBlemish, byte, EImageArea5>
//{
//public:
//	CACMISImageFocusedBlemish();
//	~CACMISImageFocusedBlemish();
//};


//class ACMISIMAGE_API CACMISImageStainLCB : public CACMISImage<TLCBSpec, short, EImageRegion>
//{
//public:
//	CACMISImageStainLCB();
//	~CACMISImageStainLCB();
//};

class ACMISIMAGE_API CACMISImageStainLCBCommon : public CACMISImageCommon<TLCBSpecN>
{
public:
	CACMISImageStainLCBCommon();
	~CACMISImageStainLCBCommon();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TLCBSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT); // for backward compatibility
	bool Inspect(TBufferInfo& tBufferInfo, TLCBSpec& _Spec); // for backward compatibility
	bool Inspect(TFileInfo& tFileInfo, TLCBSpec& _Spec); // for backward compatibility
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TLCBSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TLCBSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TLCBSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TLCBSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLCBSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TLCBSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TLCBSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLCBSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLCBSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(TBufferInfoM& tBufferInfo, TLCBSpecN& _Spec);
	bool InspectM_OMS(TFileInfoM& tFileInfo, TLCBSpecN& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TLCBSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod);

private:
	bool ConvertSpec(TLCBSpec _Spec, TLCBSpecN& _NewSpec); // Convert Spec from TLCBSpec to TLCBSpecN
};

class ACMISIMAGE_API CACMISImageFastDifferenceFiltering : public CACMISImageCommon<TFDFSpec>
{
public:
	CACMISImageFastDifferenceFiltering();
	~CACMISImageFastDifferenceFiltering();

	bool Inspect(TBufferInfo& tBufferInfo, TFDFSpec& _Spec); // for backward compatibility
	bool Inspect(TFileInfo& tFileInfo, TFDFSpec& _Spec); // for backward compatibility
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFDFSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFDFSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFDFSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TFDFSpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TFDFSpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFDFSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TFDFSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod);
};

//class ACMISIMAGE_API CACMISImageStainLCBCommon_Raw : public CACMISImageCommon<TLCBSpecN>
//{
//public:
//	CACMISImageStainLCBCommon_Raw();
//	~CACMISImageStainLCBCommon_Raw();
//};
//
//class ACMISIMAGE_API CACMISImageStainRU_Ymean : public CACMISImage<TRU_YmeanSpec>
//{
//public:
//	CACMISImageStainRU_Ymean();
//	~CACMISImageStainRU_Ymean();
//};
//
class ACMISIMAGE_API CACMISImageStainRU_YmeanCommon : public CACMISImageCommon<TRU_YmeanSpecN>
{
public:
	CACMISImageStainRU_YmeanCommon();
	~CACMISImageStainRU_YmeanCommon();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRU_YmeanSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT); // for backward compatibility
	bool Inspect(TBufferInfo& tBufferInfo, TRU_YmeanSpec& _Spec); // for backward compatibility
	bool Inspect(TFileInfo& tFileInfo, TRU_YmeanSpec& _Spec); // for backward compatibility
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRU_YmeanSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TRU_YmeanSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TRU_YmeanSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRU_YmeanSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRU_YmeanSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TRU_YmeanSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TRU_YmeanSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRU_YmeanSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRU_YmeanSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(TBufferInfoM& tBufferInfo, TRU_YmeanSpecN& _Spec);
	bool InspectM_OMS(TFileInfoM& tFileInfo, TRU_YmeanSpecN& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TRU_YmeanSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod);

private:
	bool ConvertSpec(TRU_YmeanSpec _Spec, TRU_YmeanSpecN& _NewSpec); // Convert Spec from TRU_YmeanSpec to TRU_YmeanSpecN
};

//class ACMISIMAGE_API CACMISImageStainRU_MultiFilter : public CACMISImage<TRUMultiFilterSpec, short, EImageRegion>
//{
//public:
//	CACMISImageStainRU_MultiFilter();
//	~CACMISImageStainRU_MultiFilter();
//};
//
////bins
//class ACMISIMAGE_API CACMISImageStainRU_Bayer : public CACMISImage<TRUBayerSpec, BYTE, EBlockType>
//{
//public:
//	CACMISImageStainRU_Bayer();
//	~CACMISImageStainRU_Bayer();
//};
//
//class ACMISIMAGE_API CACMISImageStatinUB : public CACMISImage<TUnfocusedBlemish, BYTE, EImageArea5>
//{
//	const TDefectResult* GetDefectResult(EImageArea5 pos, int nIndex) const; // DO NOT PROVIDE THIS FUNCTION!!
//public:
//	CACMISImageStatinUB();
//	~CACMISImageStatinUB();
//};


//class ACMISIMAGE_API CACMISImageBlemishOVT : public CACMISImageCommon<TBlemishOVTSpec>
//{
//public:
//	CACMISImageBlemishOVT();
//	~CACMISImageBlemishOVT();
//
//	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TBlemishOVTSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
//	bool Inspect(TBufferInfo& tBufferInfo, TBlemishOVTSpec& _Spec);
//	bool Inspect(TFileInfo& tFileInfo, TBlemishOVTSpec& _Spec);
//	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TBlemishOVTSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
//	bool InspectM(TBufferInfoM& tBufferInfo, TBlemishOVTSpec& _Spec);
//	bool InspectM(TFileInfoM& tFileInfo, TBlemishOVTSpec& _Spec);
//};


