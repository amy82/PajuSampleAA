#pragma once

#include "export.h"
#include <memory>
#include "ACMISImageDef.h"

// DO NOT INCLUDE STAIN HEADER FILE!
class CImageHistogramEq;

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

	bool HistogramEqualizerCLAHE(BYTE* pBMPBuffer, BYTE* pYBuffer, int nImageWidth, int nImageHeight, int nMinGrayValue=30, int nMaxGrayValue=255,
		unsigned int nContextualRegionX=16, unsigned int nContextualRegionY=12, unsigned int nNumOfGrayBin=200, float fNormalizedClipLimit=20);

	bool HistogramEqualizerWholeRegion(BYTE* pBMPBuffer, int nImageWidth, int nImageHeight);

	bool HistogramEqualizerBinary(BYTE* pBMPBuffer, int nImageWidth, int nImageHeight);
};

class ACMISIMAGE_API CACMISImageStainLCB : public CACMISImage<TLCBSpec, short, EImageRegion>
{
public:
	CACMISImageStainLCB();
	~CACMISImageStainLCB();
};

class ACMISIMAGE_API CACMISImageStainLCBCommon : public CACMISImageCommon<TLCBSpec, BYTE, EImageRegion, EDATAFORMAT, EOUTMODE>
{
public:
	CACMISImageStainLCBCommon();
	~CACMISImageStainLCBCommon();
};

class ACMISIMAGE_API CACMISImageStainLCBCommon_Raw : public CACMISImageCommon<TLCBSpec, BYTE, EImageRegion, EDATAFORMAT, EOUTMODE>
{
public:
	CACMISImageStainLCBCommon_Raw();
	~CACMISImageStainLCBCommon_Raw();
};

class ACMISIMAGE_API CACMISImageStainRU_Ymean : public CACMISImage<TRU_YmeanSpec>
{
public:
	CACMISImageStainRU_Ymean();
	~CACMISImageStainRU_Ymean();
};

class ACMISIMAGE_API CACMISImageStainRU_YmeanCommon : public CACMISImageCommon<TRU_YmeanSpec>
{
public:
	CACMISImageStainRU_YmeanCommon();
	~CACMISImageStainRU_YmeanCommon();
};

class ACMISIMAGE_API CACMISImageStainRU_MultiFilter : public CACMISImage<TRUMultiFilterSpec, short, EImageRegion>
{
public:
	CACMISImageStainRU_MultiFilter();
	~CACMISImageStainRU_MultiFilter();
};

//bins
class ACMISIMAGE_API CACMISImageStainRU_Bayer : public CACMISImage<TRUBayerSpec, BYTE, EBlockType>
{
public:
	CACMISImageStainRU_Bayer();
	~CACMISImageStainRU_Bayer();
};

class ACMISIMAGE_API CACMISImageStatinUB : public CACMISImage<TUnfocusedBlemish,BYTE, EImageArea5>
{
	const TDefectResult* GetDefectResult(EImageArea5 pos, int nIndex) const; // DO NOT PROVIDE THIS FUNCTION!!
public:
	CACMISImageStatinUB();
	~CACMISImageStatinUB();
};
