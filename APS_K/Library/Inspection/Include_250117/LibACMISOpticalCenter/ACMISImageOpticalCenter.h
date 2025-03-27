#pragma once

#include "export.h"
#include <LibACMISOpticalCenter\ACMISOpticalCenterDef.h>


class ACMISOPTICALCENTER_API CACMISOpticalCenterPolynomialFit : public CACMISOpticalCenter<TOpticalCenterPolyFit>
{
public:
	CACMISOpticalCenterPolynomialFit();
	~CACMISOpticalCenterPolynomialFit();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterPolyFit& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterPolyFit& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterPolyFit& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterPolyFit& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterPolyFit& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISOPTICALCENTER_API CACMISOpticalCenterCentroid : public CACMISOpticalCenter<TOpticalCenterN>
{
public:
	CACMISOpticalCenterCentroid();
	~CACMISOpticalCenterCentroid();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenter& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenter& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenter& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

private:
	bool ConvertSpec(TOpticalCenter _Spec, TOpticalCenterN& _NewSpec); // Convert Spec from TOpticalCenter to TOpticalCenterN
};

class ACMISOPTICALCENTER_API CACMISOpticalCenterCentroidG : public CACMISOpticalCenter<TOpticalCenterNG>
{
public:
	CACMISOpticalCenterCentroidG();
	~CACMISOpticalCenterCentroidG();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterG& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterG& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterG& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNG& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterNG& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterNG& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNG& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterNG& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterNG& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNG& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterNG& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

private:
	bool ConvertSpec(TOpticalCenterG _Spec, TOpticalCenterNG& _NewSpec); // Convert Spec from TOpticalCenterG to TOpticalCenterNG
};

class ACMISOPTICALCENTER_API CACMISOpticalCenterCentroidRGB : public CACMISOpticalCenter<TOpticalCenterNRGB>
{
public:
	CACMISOpticalCenterCentroidRGB();
	~CACMISOpticalCenterCentroidRGB();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterRGB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterRGB& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterRGB& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNRGB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterNRGB& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterNRGB& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNRGB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterNRGB& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterNRGB& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNRGB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterNRGB& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

private:
	bool ConvertSpec(TOpticalCenterRGB _Spec, TOpticalCenterNRGB& _NewSpec); // Convert Spec from TOpticalCenterRGB to TOpticalCenterNRGB
};
#define CACMISOpticalCenterCentroidRgb CACMISOpticalCenterCentroidRGB

class ACMISOPTICALCENTER_API CACMISOpticalCenterCentroidY : public CACMISOpticalCenter<TOpticalCenterNY>
{
public:
	CACMISOpticalCenterCentroidY();
	~CACMISOpticalCenterCentroidY();

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterY& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterY& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterY& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNY& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TOpticalCenterNY& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TOpticalCenterNY& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNY& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterNY& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterNY& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterNY& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterNY& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

private:
	bool ConvertSpec(TOpticalCenterY _Spec, TOpticalCenterNY& _NewSpec); // Convert Spec from TOpticalCenterY to TOpticalCenterNY
};

class ACMISOPTICALCENTER_API CACMISOpticalCenterDistortionDev : public CACMISOpticalCenter<TOpticalCenterDistortionDev>
{
public:
	CACMISOpticalCenterDistortionDev();
	~CACMISOpticalCenterDistortionDev();

	//const POINT* GetInspectionROI(int index) const;
};

class ACMISOPTICALCENTER_API CACMISOpticalCenterBrightest : public CACMISOpticalCenter<TOpticalCenterBrightest>
{
public:
	CACMISOpticalCenterBrightest();
	~CACMISOpticalCenterBrightest();
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterBrightest& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterBrightest& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterBrightest& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterBrightest& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterBrightest& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISOPTICALCENTER_API CACMISOpticalCenterCentroidCircle : public CACMISOpticalCenter<TOpticalCenterCentroidCircle>
{
public:
	CACMISOpticalCenterCentroidCircle();
	~CACMISOpticalCenterCentroidCircle();
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterCentroidCircle& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TOpticalCenterCentroidCircle& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TOpticalCenterCentroidCircle& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TOpticalCenterCentroidCircle& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TOpticalCenterCentroidCircle& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};