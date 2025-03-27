#pragma once

#include "export.h"
#include "ACMISSignalNoiseRatioDef.h"

// DO NOT INCLUDE HEADER FILE

class ACMISIMAGE_API CACMISSignalNoiseRatioNorm : public CACMISSignalNoiseRatio<TSNRNormSpecN, TSNRNormResult>
{
public:
	CACMISSignalNoiseRatioNorm();
	~CACMISSignalNoiseRatioNorm();

	bool Inspect();
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRNormSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TSNRNormSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TSNRNormSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRNormSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TSNRNormSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TSNRNormSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRNormSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRNormSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TSNRNormSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TSNRNormSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRNormSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRNormSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(TBufferInfoM& tBufferInfo, TSNRNormSpecN& _Spec);
	bool InspectM_OMS(TFileInfoM& tFileInfo, TSNRNormSpecN& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TSNRNormSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

private:
	bool ConvertSpec(TSNRNormSpec _Spec, TSNRNormSpecN& _NewSpec);
};
#define CACMISSignalNoiseRatioOECF CACMISSignalNoiseRatioNorm

class ACMISIMAGE_API CACMISPatternNoise : public CACMISSignalNoiseRatio<TPatternNoiseSpecN, TPatternNoiseResult>
{
public:
	CACMISPatternNoise();
	~CACMISPatternNoise();

	bool Inspect();
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TPatternNoiseSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TPatternNoiseSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TPatternNoiseSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TPatternNoiseSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TPatternNoiseSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TPatternNoiseSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TPatternNoiseSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TPatternNoiseSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TPatternNoiseSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TPatternNoiseSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TPatternNoiseSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TPatternNoiseSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
	const TSNRResult* GetSNRResult(int nIndex, int channel = -1);

private:
	bool ConvertSpec(TPatternNoiseSpec _Spec, int nImageWidth, int nImageHeight, TPatternNoiseSpecN& _NewSpec);

private:
	TSNRResult m_stResult;
};

class ACMISIMAGE_API CACMISSignalNoiseRatioBW : public CACMISSignalNoiseRatio<TSNRBWSpecN, TSNRBWResult>
{
public:
	CACMISSignalNoiseRatioBW();
	~CACMISSignalNoiseRatioBW();

	bool Inspect();
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRBWSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TSNRBWSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TSNRBWSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRBWSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TSNRBWSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TSNRBWSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRBWSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRBWSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TSNRBWSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TSNRBWSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRBWSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TSNRBWSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

private:
	bool ConvertSpec(TSNRBWSpec _Spec, TSNRBWSpecN& _NewSpec);
};

class ACMISIMAGE_API CACMISDarkCurrent : public CACMISSignalNoiseRatio<TDarkCurrentSpec, TDarkCurrentResult>
{
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TDarkCurrentSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TDarkCurrentSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TDarkCurrentSpec& _Spec);

public:
	CACMISDarkCurrent();
	~CACMISDarkCurrent();

	bool Inspect();
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDarkCurrentSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDarkCurrentSpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDarkCurrentSpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDarkCurrentSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TDarkCurrentSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISIMAGE_API CACMISSignalNoiseRatioVNE : public CACMISSignalNoiseRatio<TSNRVNESpec, TSNRVNEResult>
{
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSNRVNESpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TSNRVNESpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TSNRVNESpec& _Spec);

public:
	CACMISSignalNoiseRatioVNE();
	~CACMISSignalNoiseRatioVNE();

	bool Inspect();
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRVNESpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TSNRVNESpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TSNRVNESpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSNRVNESpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TSNRVNESpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISIMAGE_API CACMISDarkNoise : public CACMISSignalNoiseRatio<TDarkNoiseSpec, TDarkNoiseResult>
{
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TDarkNoiseSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TDarkNoiseSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TDarkNoiseSpec& _Spec);

public:
	CACMISDarkNoise();
	~CACMISDarkNoise();

	bool Inspect();
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDarkNoiseSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDarkNoiseSpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDarkNoiseSpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDarkNoiseSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TDarkNoiseSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

