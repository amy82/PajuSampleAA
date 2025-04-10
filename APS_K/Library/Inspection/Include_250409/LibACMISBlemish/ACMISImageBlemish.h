#pragma once

#include "export.h"
#include <LibACMISBlemish\ACMISBlemishDef.h>

// DO NOT INCLUDE HEADER FILE
//class ACMISBLEMISH_API CACMISImageBlackSpotContrast : public CACMISImage<TBlackSpotContrast>
//{
//public:
//	CACMISImageBlackSpotContrast();
//	~CACMISImageBlackSpotContrast();
//};

class ACMISBLEMISH_API CACMISImageBlackSpotContrastCommon : public CACMISBlemishCommon<TBlackSpotContrastN>
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
	bool ConvertEach2CommonSpec(TBlackSpotContrastN& _Spec, TInspectSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod, int nUsing8BitOnly = 0);

private:
	bool ConvertSpec(TBlackSpotContrast _Spec, TBlackSpotContrastN& _NewSpec); // Convert Spec from TBlackSpotContrast to TBlackSpotContrastN
};


//class ACMISBLEMISH_API CACMISImageFocusedBlemish : public CACMISImage<TFocusedBlemish, byte, EImageArea5>
//{
//public:
//	CACMISImageFocusedBlemish();
//	~CACMISImageFocusedBlemish();
//};


//class ACMISBLEMISH_API CACMISImageStainLCB : public CACMISImage<TLCBSpec, short, EImageRegion>
//{
//public:
//	CACMISImageStainLCB();
//	~CACMISImageStainLCB();
//};

class ACMISBLEMISH_API CACMISImageStainLCBCommon : public CACMISBlemishCommon<TLCBSpecN>
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
	bool ConvertEach2CommonSpec(TLCBSpecN& _Spec, TInspectSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod, int nUsing8BitOnly = 0);

private:
	bool ConvertSpec(TLCBSpec _Spec, TLCBSpecN& _NewSpec); // Convert Spec from TLCBSpec to TLCBSpecN
};

class ACMISBLEMISH_API CACMISImageFastDifferenceFiltering : public CACMISBlemishCommon<TFDFSpecN>
{
public:
	CACMISImageFastDifferenceFiltering();
	~CACMISImageFastDifferenceFiltering();

	bool Inspect(TBufferInfo& tBufferInfo, TFDFSpec& _Spec); // for backward compatibility
	bool Inspect(TFileInfo& tFileInfo, TFDFSpec& _Spec); // for backward compatibility
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFDFSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFDFSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TFDFSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TFDFSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFDFSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFDFSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFDFSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TFDFSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TFDFSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFDFSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TFDFSpecN& _NewSpec);
	bool ConvertEach2CommonSpec(TFDFSpecN& _Spec, TInspectSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod, int nUsing8BitOnly = 0);

private:
	bool ConvertSpec(TFDFSpec _Spec, TFDFSpecN& _NewSpec); // Convert Spec from TFDFSpec to TFDFSpecN
};

//class ACMISBLEMISH_API CACMISImageStainLCBCommon_Raw : public CACMISBlemishCommon<TLCBSpecN>
//{
//public:
//	CACMISImageStainLCBCommon_Raw();
//	~CACMISImageStainLCBCommon_Raw();
//};
//
//class ACMISBLEMISH_API CACMISImageStainRU_Ymean : public CACMISImage<TRU_YmeanSpec>
//{
//public:
//	CACMISImageStainRU_Ymean();
//	~CACMISImageStainRU_Ymean();
//};
//
class ACMISBLEMISH_API CACMISImageStainRU_YmeanCommon : public CACMISBlemishCommon<TRU_YmeanSpecN>
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
	bool ConvertEach2CommonSpec(TRU_YmeanSpecN& _Spec, TInspectSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	bool MakeHistEQImage(const BYTE *pBuffer, BYTE *pBMP, int nWidth, int nHeight, TDATASPEC& tDataSpec, int nHistEQMethod, int nUsing8BitOnly = 0);

private:
	bool ConvertSpec(TRU_YmeanSpec _Spec, TRU_YmeanSpecN& _NewSpec); // Convert Spec from TRU_YmeanSpec to TRU_YmeanSpecN
};

//class ACMISBLEMISH_API CACMISImageStainRU_MultiFilter : public CACMISImage<TRUMultiFilterSpec, short, EImageRegion>
//{
//public:
//	CACMISImageStainRU_MultiFilter();
//	~CACMISImageStainRU_MultiFilter();
//};
//
////bins
//class ACMISBLEMISH_API CACMISImageStainRU_Bayer : public CACMISImage<TRUBayerSpec, BYTE, EBlockType>
//{
//public:
//	CACMISImageStainRU_Bayer();
//	~CACMISImageStainRU_Bayer();
//};
//
//class ACMISBLEMISH_API CACMISImageStatinUB : public CACMISImage<TUnfocusedBlemish, BYTE, EImageArea5>
//{
//	const TDefectResult* GetDefectResult(EImageArea5 pos, int nIndex) const; // DO NOT PROVIDE THIS FUNCTION!!
//public:
//	CACMISImageStatinUB();
//	~CACMISImageStatinUB();
//};


//class ACMISBLEMISH_API CACMISImageBlemishOVT : public CACMISBlemishCommon<TBlemishOVTSpec>
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


