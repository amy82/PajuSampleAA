#pragma once

#include "export.h"
#include "ACMISShadingDef.h"
#include "ACMISEtcAlgorithm.h"

// DO NOT INCLUDE HEADER FILE!

// Color Sensitivity
class ACMISSHADING_API CACMISShadingColorSensitivity : public CACMISShadingCommon<TColorSensitivitySpecN, TColorSensitivityResult>
{
public:
	CACMISShadingColorSensitivity(void);
	~CACMISShadingColorSensitivity(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorSensitivitySpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TColorSensitivitySpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TColorSensitivitySpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorSensitivitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TColorSensitivitySpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TColorSensitivitySpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorSensitivitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorSensitivitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TColorSensitivitySpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TColorSensitivitySpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorSensitivitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TColorSensitivitySpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TColorSensitivityResult* GetInspectionResult(int nIndex = 0) const;
	const RECT* GetInspectionROI(int nIndex = 0) const;
	bool InSpec(TColorSensitivitySpecN& _Spec);
	bool InSpec(TColorSensitivitySpec& _Spec);
	bool InSpec(int nIndex, TColorSensitivitySpecN& _Spec);
	bool GetInspectionColorBalance(double &dRG_Balance, double &dBG_Balance);

private:
	bool ConvertSpec(TColorSensitivitySpec _Spec, int nImageWidth, int nImageHeight, TColorSensitivitySpecN& _NewSpec);
};

// Color Shading
class ACMISSHADING_API CACMISShadingColorShading : public CACMISShadingCommon<TColorShadingSpecN, TColorShadingResult>
{
public:
	CACMISShadingColorShading(void);
	~CACMISShadingColorShading(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TColorShadingSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TColorShadingSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TColorShadingSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TColorShadingSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TColorShadingSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TColorShadingSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TColorShadingSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TColorShadingResult* GetInspectionResult() const;
	const RECT* GetInspectionROI(int nIndex) const;
	bool InSpec(TColorShadingSpecN& _Spec);
	bool InSpec(TColorShadingSpec& _Spec);

private:
	bool ConvertSpec(TColorShadingSpec _Spec, int nImageWidth, int nImageHeight, TColorShadingSpecN& _NewSpec);
};

// Relative Illumination
class ACMISSHADING_API CACMISShadingRelativeIllumination : public CACMISShadingCommon<TRelativeIlluminationSpecN, TRelativeIlluminationResultN>
{
public:
	CACMISShadingRelativeIllumination(void);
	~CACMISShadingRelativeIllumination(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TRelativeIlluminationSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TRelativeIlluminationSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TRelativeIlluminationSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TRelativeIlluminationSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TRelativeIlluminationSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TRelativeIlluminationSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TRelativeIlluminationResultN* GetInspectionResult(int nIndex);
	const TRelativeIlluminationResult* GetInspectionResult();
	const RECT* GetInspectionROI(int nIndex) const;
	bool InSpec(TRelativeIlluminationSpecN& _Spec);
	bool InSpec(TRelativeIlluminationSpec& _Spec);
	bool InSpec(int nIndex, TRelativeIlluminationSpecN& _Spec);
	bool InSpec(int nIndex, TRelativeIlluminationSpec& _Spec);
	bool GetInspectionDiffResult(double& dDiff_LR, double& dDiff_UD);
	double GetMaxDiff();
	bool GetInspectionRIBalance(double &dRIBalance);

private:
	bool ConvertSpec(TRelativeIlluminationSpec _Spec, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _NewSpec);

private:
	TRelativeIlluminationResult m_tResultOld;
};

// Relative Illumination Common
class ACMISSHADING_API CACMISShadingRelativeIllumination_Common : public CACMISShadingCommon<TRelativeIlluminationSpec_Common, TRelativeIlluminationResult_Common>
{
public:
	CACMISShadingRelativeIllumination_Common(void);
	~CACMISShadingRelativeIllumination_Common(void);

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpec_Common& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TRelativeIlluminationSpec_Common& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TRelativeIlluminationSpec_Common& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpec_Common& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	const TRelativeIlluminationResult_Common* GetInspectionResult(EROIPosition pos, int nIndex);
	const TRelativeIlluminationResult_Common* GetInspectionCenterResult() const;
	bool InSpec(EROIPosition pos, int nIndex);
};

// Relative Illumination Xpeng
class ACMISSHADING_API CACMISShadingRelativeIllumination_X : public CACMISShadingCommon<TRelativeIlluminationSpecX, TRelativeIlluminationResultX>
{
public:
	CACMISShadingRelativeIllumination_X(void);
	~CACMISShadingRelativeIllumination_X(void);

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecX& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TRelativeIlluminationSpecX& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TRelativeIlluminationSpecX& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecX& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecX& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TRelativeIlluminationResultX* GetInspectionResult(int nIndex);
	const TRelativeIlluminationResultX* GetInspectionCenterResult() const;
	bool InSpec(int nIndex);
	double GetCornerVariation(int ch);
};


// Relative Uniformity
class ACMISSHADING_API CACMISShadingRelativeUniformity : public CACMISShadingCommon<TRelativeUniformitySpec, TRelativeUniformityResult>
{
public:
	CACMISShadingRelativeUniformity(void);
	~CACMISShadingRelativeUniformity(void);

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeUniformitySpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TRelativeUniformitySpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TRelativeUniformitySpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TRelativeUniformitySpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TRelativeUniformitySpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TRelativeUniformityResult* GetInspectionResult() const;
	const RECT* GetInspectionROI() const;
};

// Shading Uniformity
class ACMISSHADING_API CACMISShadingUniformity : public CACMISShadingCommon<TShadingUniformitySpecN, TShadingUniformityResult>
{
public:
	CACMISShadingUniformity(void);
	~CACMISShadingUniformity(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TShadingUniformitySpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TShadingUniformitySpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TShadingUniformitySpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TShadingUniformitySpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TShadingUniformitySpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TShadingUniformitySpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TShadingUniformitySpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM_OMS(TBufferInfoM& tBufferInfo, TShadingUniformitySpecN& _Spec);
	bool InspectM_OMS(TFileInfoM& tFileInfo, TShadingUniformitySpecN& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TShadingUniformityResult* GetInspectionResult(EROIPosition pos, int nIndex);
	const TShadingUniformityResult* GetInspectionCenterResult() const;
	const RECT* GetInspectionROI() const;
	bool InSpec(EROIPosition pos, int nIndex);
	bool InSpec(TShadingUniformitySpecN& _Spec);
	bool InSpec(TShadingUniformitySpec& _Spec);

private:
	bool ConvertSpec(TShadingUniformitySpec _Spec, int nImageWidth, int nImageHeight, TShadingUniformitySpecN& _NewSpec);
};

// Color shading(Color Relative Illumination)
class ACMISSHADING_API CACMISShadingColorShading_Common : public CACMISShadingCommon<TColorShadingSpec_CommonN, TColorShadingResult_Common>
{
public:
	CACMISShadingColorShading_Common(void);
	~CACMISShadingColorShading_Common(void);

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpec_CommonN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TColorShadingSpec_CommonN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TColorShadingSpec_CommonN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorShadingSpec_CommonN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	const TColorShadingResult_Common* GetInspectionResult(EROIPosition pos, int nIndex) const;
	const TColorShadingResult_Common* GetInspectionCenterResult() const;
	bool InSpec(EROIPosition pos, int nIndex);
};

// Color Uniformity
class ACMISSHADING_API CACMISShadingColorUniformity : public CACMISShadingCommon<TColorUniformitySpecN, TColorUniformityResultN>
{
public:
	CACMISShadingColorUniformity(void);
	~CACMISShadingColorUniformity(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorUniformitySpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TColorUniformitySpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TColorUniformitySpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TColorUniformitySpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TColorUniformitySpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TColorUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TColorUniformitySpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TColorUniformitySpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColorUniformitySpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TColorUniformitySpecN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TColorUniformityResultN* GetInspectionResult(int nIndex) const;
	const TColorUniformityResultN GetInspectionMaxResult() const;
	const RECT* GetInspectionROI() const;

private:
	bool ConvertSpec(TColorUniformitySpec _Spec, TColorUniformitySpecN& _NewSpec);

private:
	TColorUniformitySpecN m_stSpec;
};

// Lens Shading
class ACMISSHADING_API CACMISShadingLensShading : public CACMISShadingCommon<TLensShadingSpec, TLensShadingResult>
{
public:
	CACMISShadingLensShading(void);
	~CACMISShadingLensShading(void);

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLensShadingSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TLensShadingSpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TLensShadingSpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLensShadingSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TLensShadingSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const TLensShadingResult* GetInspectionResult() const;
	const RECT* GetInspectionROI() const;
};
