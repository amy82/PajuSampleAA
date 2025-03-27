#pragma once

#include "export.h"
#include <memory>
#include "ACMISImageDef.h"


class ACMISIMAGE_API CACMISOpticalCenterPolynomialFit : public CACMISOpticalCenter<TOpticalCenterPolyFit, BYTE>
{
public:
	CACMISOpticalCenterPolynomialFit();
	~CACMISOpticalCenterPolynomialFit();

	// pBuffer : 8bit raw image buffer
	inline int Inspect(const BYTE* pBuffer, int nWidth, int nHeight, TOpticalCenterPolyFit& _Spec)
	{
		return CACMISOpticalCenter::Inspect(pBuffer, nWidth, nHeight, _Spec);
	}
};

class ACMISIMAGE_API CACMISOpticalCenterCentroid : public CACMISOpticalCenter<_TOpticalCenter, BYTE>
{
public:
	CACMISOpticalCenterCentroid();
	~CACMISOpticalCenterCentroid();

	// pBuffer : 8bit raw image buffer
	inline int Inspect(const BYTE* pBuffer, int nWidth, int nHeight, _TOpticalCenter& _Spec)
	{
		return CACMISOpticalCenter::Inspect(pBuffer, nWidth, nHeight, _Spec);
	}
};

class ACMISIMAGE_API CACMISOpticalCenterCentroidRgb : public CACMISOpticalCenter<_TOpticalCenterRgb, BYTE>
{
public:
	CACMISOpticalCenterCentroidRgb();
	~CACMISOpticalCenterCentroidRgb();

	// pBuffer : 8bit bmp image buffer
	inline int Inspect(const BYTE* pBuffer, int nWidth, int nHeight, _TOpticalCenterRgb& _Spec)
	{
		return CACMISOpticalCenter::Inspect(pBuffer, nWidth, nHeight, _Spec);
	}
};
