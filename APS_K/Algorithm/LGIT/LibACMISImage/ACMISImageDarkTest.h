#pragma once

#include "export.h"
#include "ACMISImageDef.h"

// DO NOT INCLUDE BLEMISH HEADER FILE


class ACMISIMAGE_API CACMISImageDarkDefectPixel : public CACMISImageCommon<TDarkDefectPixel>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDarkDefectPixel();
	~CACMISImageDarkDefectPixel();
};

class ACMISIMAGE_API CACMISImageDarkDefectCluster : public CACMISImageCommon<TDarkDefectCluster>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDarkDefectCluster();
	~CACMISImageDarkDefectCluster();
};

class ACMISIMAGE_API CACMISImageDarkDefectCluster2Byte : public CACMISImage<TDarkDefectCluster, short>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;

public:
	CACMISImageDarkDefectCluster2Byte();
	~CACMISImageDarkDefectCluster2Byte();
};

class ACMISIMAGE_API CACMISImageDarkShading : public CACMISImageCommon<TDarkShading>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDarkShading();
	~CACMISImageDarkShading();
};

class ACMISIMAGE_API CACMISImageDarkBLC : public CACMISImageCommon<TDarkBLC>
{
	// below functions do not have any meanings in this algorithm.
	const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDarkBLC();
	~CACMISImageDarkBLC();
};

class ACMISIMAGE_API CACMISImageDarkLineNoise : public CACMISImageCommon<TDarkLineNoise>
{
	// below functions do not have any meanings in this algorithm.
	const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDarkLineNoise();
	~CACMISImageDarkLineNoise();
};

class ACMISIMAGE_API CACMISImageDarkLineNoise2Byte : public CACMISImage<TDarkLineNoise, short>
{
	// below functions do not have any meanings in this algorithm.
	const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;

public:
	CACMISImageDarkLineNoise2Byte();
	~CACMISImageDarkLineNoise2Byte();
};

class ACMISIMAGE_API CACMISImageDefectPixelCalibration : public CACMISImageCommon<TDefectPixelCalibration> //, short>
{
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDefectPixelCalibration();
	~CACMISImageDefectPixelCalibration();
};

class ACMISIMAGE_API CACMISImageFDWhitePixel : public CACMISImageCommon<TFDWhitePixel>//, short>
{
	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageFDWhitePixel();
	~CACMISImageFDWhitePixel();
};

class ACMISIMAGE_API CACMISImageBadPixelTable : public CACMISImageCommon<TBadPixelTable> //, short>
{
	// below functions do not have any meanings in this algorithm.
//	int GetDefectBlobCount() const;
	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageBadPixelTable();
	~CACMISImageBadPixelTable();
};

//class ACMISIMAGE_API CACMISImageBrightModeFixed2Byte : public CACMISImage<TDarkDefectPixel, short>
//{
//	// below functions do not have any meanings in this algorithm.
//	//const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
//	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
//	//const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
//	//	int GetDefectBlobCount() const;
////	const RECT& GetDefectBlobRect(int nIndex) const;
//
//public:
//	CACMISImageBrightModeFixed2Byte();
//	~CACMISImageBrightModeFixed2Byte();
//};

class ACMISIMAGE_API CACMISImageBrightModeFixedCommon : public CACMISImageCommon<TDarkDefectPixel>
{
	// below functions do not have any meanings in this algorithm.
	//const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	//const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	//	int GetDefectBlobCount() const;
	//	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageBrightModeFixedCommon();
	~CACMISImageBrightModeFixedCommon();
};

//class ACMISIMAGE_API CACMISImageDarkModeFixed2Byte : public CACMISImage<TDarkDefectPixel, short>
//{
//	// below functions do not have any meanings in this algorithm.
//	//const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
//	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
//	//const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
//	//	int GetDefectBlobCount() const;
//	//	const RECT& GetDefectBlobRect(int nIndex) const;
//
//public:
//	CACMISImageDarkModeFixed2Byte();
//	~CACMISImageDarkModeFixed2Byte();
//};

class ACMISIMAGE_API CACMISImageDarkModeFixedCommon : public CACMISImageCommon<TDarkDefectPixel>
{
	// below functions do not have any meanings in this algorithm.
	//const TDefectResult* GetMaxDefectResult(EImageRegion pos = EIMAGEREGION_CENTER) const;
	int GetDefectCount(EImageRegion pos = EIMAGEREGION_CENTER) const;
	//const TDefectResult* GetDefectResult(EImageRegion pos, int nIndex) const;
	//	int GetDefectBlobCount() const;
	//	const RECT& GetDefectBlobRect(int nIndex) const;
	const TBlobResult* GetBlobDefectResult(int nIndex) const;

public:
	CACMISImageDarkModeFixedCommon();
	~CACMISImageDarkModeFixedCommon();
};

