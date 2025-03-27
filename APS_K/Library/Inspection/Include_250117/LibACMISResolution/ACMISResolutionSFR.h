#pragma once

#include "export.h"
#include <LibACMISResolution\ACMISResolutionDef.h>


class ACMISRESOLUTION_API CACMISResolutionSFR
{
	CACMISResolutionSFR(const CACMISResolutionSFR& c);
	CACMISResolutionSFR& operator=(const CACMISResolutionSFR& c);

public:
	CACMISResolutionSFR(void);
	~CACMISResolutionSFR(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSFRSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TSFRSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TSFRSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSFRSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, TSFRSpec& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSFRSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TSFRSpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TSFRSpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSFRSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TSFRSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const double GetInspectionResult(int nROIIndex = 0, int nFreqIndex = 0) const;
	const RECT GetInspectionROI(int nROIIndex = 0) const;
	bool GetInspectionSFRBalance(double& dSFRBalance, int nStartIndex, int nEndIndex);

	///@brief This function sets imageBuffer & imageInfo for inspection.
	///       it must be called before inspection.
	bool SetImageBuffer(ResolutionImageBufferManager& mgr);

	///@brief This function set the config for calculating SFR
	void SetAlgorithmConfig(TSFRConfig _Config, bool bEnableLog = false);
	void SetAlgorithmConfig(int nMaxROIWidth, int nMaxROIHeight, double dMaxEdgeAngle = 45.0, double dPixelSize = 0.0, ESFRAlgorithmType eType = ESFRAlgorithm_ISO12233, ESFRAlgorithmMethod eMethod = ESFRMethod_Freq2SFR, ESFRFrequencyUnit eUnit = ESFRFreq_CyclePerPixel, bool bEnableLog = false);
	void SetDeltaAlgorithmType(ESFRDeltaAlgorithmType eSFRDeltaAlgorithmType);
	void SetTestLogConfig(bool bEnableLog);

	///@brief This function calculates SFR.
	///@param [in] rtROI Calculating area
	///@param [in] nEdgeDir An Edge direction. if an edge is vertical, this value is 0. if it's vertical edge, this value is 1.
	///@param [in] pFrequency Nyquist frequency lists which you want to get. ex) N/4=0.125, N/8=0.0625
	///@param [in] nFrequencyNum Frequency lists number
	///@param [out] pdSFRResult The calculated SFR result buffer. It must be inputed allocated memory buffer as nFrequencyNum.
	///@return success or fail
	bool CalcSFR(RECT& rtROI, int nEdgeDir, double* pFrequencyLists, int nFrequencyNum, double* pdSFRResult, int nIndex = 0, double dOffset = 0.0, double dGamma = 1.0, bool bUseCosineCorrection = false, int nPolyFitOrder = 1, double *dEdgeAngle = NULL);
	bool CalcSFR(const BYTE* pBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec, RECT& rtROI, int nEdgeDir, double* pFrequencyLists, int nFrequencyNum, double* pdSFRResult, int nIndex = 0, double dOffset = 0.0, double dGamma = 1.0, bool bUseCosineCorrection = false, int nPolyFitOrder = 1, double *dEdgeAngle = NULL);
	bool CalcSFR(const unsigned short* pBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec, RECT& rtROI, int nEdgeDir, double* pFrequencyLists, int nFrequencyNum, double* pdSFRResult, int nIndex = 0, double dOffset = 0.0, double dGamma = 1.0, bool bUseCosineCorrection = false, int nPolyFitOrder = 1, double *dEdgeAngle = NULL);

	///@brief This function calculates Spatial Frequency.
	///@param [in] rtROI Calculating area
	///@param [in] dSFR SFR value which you want to get.
	///@param [out] pdFreqResult The calculated Spatial frequency result buffer.
	///@return success or fail
	bool CalcFreq(RECT& rtROI, int nEdgeDir, double dSFR, double* pdFreqResult, int nIndex = 0, double dOffset = 0.0, double dGamma = 1.0, bool bUseCosineCorrection = false, int nPolyFitOrder = 1, double *dEdgeAngle = NULL);
	bool CalcFreq(const BYTE* pBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec, RECT& rtROI, int nEdgeDir, double dSFR, double* pdFreqResult, int nIndex = 0, double dOffset = 0.0, double dGamma = 1.0, bool bUseCosineCorrection = false, int nPolyFitOrder = 1, double *dEdgeAngle = NULL);
	bool CalcFreq(const unsigned short* pBuffer, int nWidth, int nHeight, TDATASPEC tDataSpec, RECT& rtROI, int nEdgeDir, double dSFR, double* pdFreqResult, int nIndex = 0, double dOffset = 0.0, double dGamma = 1.0, bool bUseCosineCorrection = false, int nPolyFitOrder = 1, double *dEdgeAngle = NULL);

	/// @brief Get the header data of CSV log file.
	/// @return log file header string
	const char* GetLogHeader();

	/// @brief Get the data of CSV log file.
	/// @return log file data string
	const char* GetLogData();

	/// @brief Get the version of Resolution algorithm.
	/// @return version data string
	const char* GetVersion();

	void SetROIInfo(TSFRROIInfo *pROIInfo, TDeltaSFRspec *pDeltaSpec, int nROICount);
	void InitResolution();
	bool CalcResolution();
	int GetMaxResolutionCount() const;

	double GetFinalSFR(int nIndex, int nFrequencyIndex = 0);
	EResolutionClass GetResolutionClass();
	const TSFRROIResult* GetSFRROIResult(int nIndex) const;
	const double GetMaxDeltaSFR() const;

	/// Check Spec
	bool InSpecResolution(int nIndex, int nFrequencyIndex = 0, double dValue = UNDEFINED_RESOLUTION_VALUE);
	double GetSpecResolution(int nIndex, int nFrequencyIndex = 0) const;
	const TSFRROIInfo& GetSFRROIInfo(int nIndex) const;

	/// forced Setting data
	void SetResolutionAll(double* pSFR, int nMaxCount, EResolutionClass eClassResult);
	void SetOffsetAll(double *pOffset, int nMaxCount);

	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const;
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const;
	inline long long GetElapsedTime() const;
	inline double GetSaturationResult(int nIndex = 0) const;
	inline bool GetCertificationResult() const;

private:
	struct ResolutionImpl;
	std::unique_ptr<ResolutionImpl> m_pImpl;
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	std::chrono::milliseconds m_elapsedTime;
	std::chrono::milliseconds m_startTimems;
	std::chrono::milliseconds m_endTimems;

	std::string m_strLogHeader;
	std::string m_strLogData;
};


