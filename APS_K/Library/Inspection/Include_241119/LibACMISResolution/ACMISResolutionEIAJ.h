#pragma once

#include "export.h"
#include "ACMISResolutionDef.h"


class ACMISRESOLUTION_API CACMISResolutionEIAJ
{
	CACMISResolutionEIAJ(const CACMISResolutionEIAJ&);
	CACMISResolutionEIAJ& operator=(const CACMISResolutionEIAJ&);

public:
	CACMISResolutionEIAJ(void);
	~CACMISResolutionEIAJ(void);

	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TEIAJSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TEIAJSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TEIAJSpec& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TEIAJSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, TEIAJSpec& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TEIAJSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TEIAJSpec& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TEIAJSpec& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TEIAJSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect_CMA(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TEIAJSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false);
	bool Inspect_CMA(TBufferInfo& tBufferInfo, TEIAJSpec& _Spec);
	bool Inspect_CMA(TFileInfo& tFileInfo, TEIAJSpec& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, int nImageWidth, int nImageHeight, TEIAJSpec& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	const double GetInspectionResult(int nROIIndex = 0) const;
	const RECT GetInspectionROI(int nROIIndex = 0) const;

	///@brief This function sets imageBuffer & imageInfo for inspection.
	///       it must be called before inspection.
	bool SetImageBuffer(ResolutionImageBufferManager& mgr);

	///@brief This function set the config for calculating EIAJ MTF
	///@param [in] eType The Calculating method of EIAJ MTF. [EEIAJAlgorithm_GETLINEMTF, ESFRAlgorithm_GETSOMTHING]
	///@param [in] bEnableLog Enable/Disable the Log for debugging. [true, false]
	void SetAlgorithmConfig(EEIAJAlgorithmType eType, bool bEnableLog = false);
	void SetTestLogConfig(bool bEnableLog);

	///@brief This function calculates EIAJ MTF.
	///@param [in] rtROI Calculating area
	///@param [in] nRoiDirection An ROI direction. [ROI_LEFT, ROI_RIGHT, ROI_TOP, ROI_BOTTOM]
	///@param [in] tROISpec An ROI spec(MTF spec, Sharpness spec, etc).
	///@param [out] pdEIAJResult The calculated EIAJ result buffer.
	///@return success or fail
	bool CalcEIAJ(RECT& rtROI, int nRoiDirection, TEIAJROISpec& tROISpec, double* pdEIAJResult);
	bool CalcEIAJ_CMA(RECT& rtROI, int nRoiDirection, TEIAJROISpec& tROISpec, double* pdEIAJResult);

	/// @brief Get the header data of CSV log file.
	/// @return log file header string
	const char* GetLogHeader();

	/// @brief Get the data of CSV log file.
	/// @return log file data string
	const char* GetLogData();

	/// @brief Get the version of Resolution algorithm.
	/// @return version data string
	const char* GetVersion();

	void SetROIInfo(TEIAJROIInfo *pROIInfo, TDeltaSFRspec *pDeltaSpec, int nROICount);
	void InitResolution();
	bool CalcResolution();
	int GetMaxResolutionCount() const;

	int GetFinalResolution(int nIndex, int nFrequencyIndex = 0);
	EResolutionClass GetResolutionClass();
	const TEIAJROIResult* GetEIAJROIResult(int nIndex) const;

	/// Check Spec
	bool InSpecResolution(int nIndex, int nFrequencyIndex = 0, int nValue = UNDEFINED_RESOLUTION_VALUE);
	double GetSpecResolution(int nIndex, int nFrequencyIndex = 0) const;
	const TEIAJROIInfo& GetEIAJROIInfo(int nIndex) const;
	double GetFinalMTF(int nIndex) const;

	/// forced Setting data
	void SetResolutionAll(int* pEIAJ, int nMaxCount, EResolutionClass eClassResult = EResolutionClass_A_PASS);
	void SetThresholdAxisAll(int* pThreshold, int nMaxCount);
	void SetOffsetAll(double *pOffset, int nMaxCount);

	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const;
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const;
	inline long long GetElapsedTime() const;
	inline double GetSaturationResult(int nIndex = 0) const;

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


