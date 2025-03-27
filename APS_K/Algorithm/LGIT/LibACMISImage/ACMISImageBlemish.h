#pragma once

#include "export.h"
#include "ACMISImageDef.h"

// DO NOT INCLUDE HEADER FILE

class ACMISIMAGE_API CACMISImageBlackSpotContrast : public CACMISImage<TBlackSpotContrast>
{
public:
	CACMISImageBlackSpotContrast();
	~CACMISImageBlackSpotContrast();
};

class ACMISIMAGE_API CACMISImageBlackSpotContrastCommon : public CACMISImageCommon<TBlackSpotContrast, BYTE, EImageRegion, EDATAFORMAT, EOUTMODE>
{
public:
	CACMISImageBlackSpotContrastCommon();
	~CACMISImageBlackSpotContrastCommon();
};


class ACMISIMAGE_API CACMISImageFocusedBlemish : public CACMISImage<TFocusedBlemish, byte, EImageArea5>
{
public:
	CACMISImageFocusedBlemish();
	~CACMISImageFocusedBlemish();
};
