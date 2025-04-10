#pragma once

#include "export.h"
#include <LibACMISResolution\ACMISResolutionDef.h>


class ACMISRESOLUTION_API CACMISFiducialMark
{
	CACMISFiducialMark(const CACMISFiducialMark& c);
	CACMISFiducialMark& operator=(const CACMISFiducialMark& c);
	bool ConvertSpec(TFiducialMarkSpec _Spec, TFiducialMarkSpecN &_SpecN);

public:
	CACMISFiducialMark(void);
	~CACMISFiducialMark(void);

	// TFiducialMarkSpec 구조체 사용
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TFiducialMarkSpec& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TFiducialMarkSpec& _Spec);

	// TFiducialMarkSpecN 구조체 사용
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TFiducialMarkSpecN& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TFiducialMarkSpecN& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecN& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0);

	// TFiducialMarkSpecM 구조체 사용
	bool Inspect(TBufferInfo& tBufferInfo, TFiducialMarkSpecM& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TFiducialMarkSpecM& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecM& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecM& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0);

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TFiducialMarkSpecN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TFiducialMarkSpecN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	
	bool InspectM(TBufferInfoM& tBufferInfo, TFiducialMarkSpecM& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TFiducialMarkSpecM& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TFiducialMarkSpecM& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TFiducialMarkSpecM& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	/// @brief Get the header data of CSV log file.
	/// @return log file header string
	const char* GetLogHeader();

	/// @brief Get the data of CSV log file.
	/// @return log file data string
	const char* GetLogData();

	/// @brief Get the version of Resolution algorithm.
	/// @return version data string
	const char* GetVersion();

	/// Chart Process
#if 0   // STL 컨테이너의 Release - Debug 호환성 문제로 비활성화
	bool SetFiducialMarkSpec(TFiducialMarkInfo&  stMarkInfo,  std::vector<RECT>&       vRect, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, std::vector<RECT>&       vRect, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, std::vector<POINT>&      vMark, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, std::vector<CDPoint>&    vMark, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, std::vector<TROICPoint>& vMark, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, std::vector<TROIField>&  vMark, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, std::vector<TROISPoint>& vMark, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkSpecM& stMarkSpec, int nImageWidth, int nImageHeight);
#endif

	bool SetFiducialMarkSpec(TFiducialMarkInfo&  stMarkInfo,  RECT*       pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, RECT*       pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, POINT*      pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, CDPoint*    pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, TROICPoint* pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, TROIField*  pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);
	bool SetFiducialMarkSpec(TFiducialMarkInfoN& stMarkInfoN, TROISPoint* pVecMarkData, size_t nVecMarkSize, int nImageWidth, int nImageHeight);

	int GetMaxFiducialMarkCount(FIDUCIALMARK_INSPECT_ITEM eItem = FIDUCIALMARK_INSPECT_MAX) const;
	const CDRect& GetFiducialMarkROI(int nIndex, FIDUCIALMARK_INSPECT_ITEM eItem = FIDUCIALMARK_INSPECT_MAX) const;
	const CDPoint& GetFiducialMarkPoint(int nIndex, FIDUCIALMARK_INSPECT_ITEM eItem = FIDUCIALMARK_INSPECT_MAX) const;
	const CDRect& GetFiducialMarkRadius(int nIndex, FIDUCIALMARK_INSPECT_ITEM eItem = FIDUCIALMARK_INSPECT_MAX) const;

	bool CalcDFOV();
	bool CalcTiltAndRotation();
	bool CalcRotation();
	bool CalcDistortion();
	bool CalcTilt();

	double GetDFOV() const;
	double GetHFOV() const;
	double GetVFOV() const;
	double GetRotation() const;
	double GetDistortion() const;

	const CDPoint GetTilt() const;
	const CDPoint GetRealCenter() const; // it's NOT an Image Center. Chart center
	const CDPoint GetCmPerPixel() const;
	const CDPoint GetRefChartLength() const;

	/// Check Spec
	bool InSpecDFOV(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecHFOV(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecVFOV(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecTiltX(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecTiltY(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecRotation(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecDistortion(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecOCX(double dValue = UNDEFINED_RESOLUTION_VALUE);
	bool InSpecOCY(double dValue = UNDEFINED_RESOLUTION_VALUE);

	const double& GetSpecDFOVMin() const;
	const double& GetSpecDFOVMax() const;
	const double& GetSpecHFOVMin() const;
	const double& GetSpecHFOVMax() const;
	const double& GetSpecVFOVMin() const;
	const double& GetSpecVFOVMax() const;
	const double& GetSpecTiltXMin() const;
	const double& GetSpecTiltXMax() const;
	const double& GetSpecTiltYMin() const;
	const double& GetSpecTiltYMax() const;
	const double& GetSpecRotationMin() const;
	const double& GetSpecRotationMax() const;
	const double& GetSpecDistortionMin() const;
	const double& GetSpecDistortionMax() const;
	const double& GetSpecOCXMin() const;
	const double& GetSpecOCXMax() const;
	const double& GetSpecOCYMin() const;
	const double& GetSpecOCYMax() const;

	/// forced Setting data
	void SetFiducialMarkPoint(std::vector<CDPoint>& vData);

	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const;
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const;
	inline void SetFOVOffset(double dHFOVOffset = 1.0, double dVFOVOffset = 1.0, double dDFOVOffset = 1.0) const;
	inline void SetDistortionOffset(double dDistortionOffset = 0.0) const;
	inline void SetRotationOffset(double dRotationOffset = 0.0) const;
	inline void SetTiltOffset(double dTiltXOffset = 0.0, double dTiltYOffset = 0.0) const;
	inline void SetOCOffset(double dOCXOffset = 0.0, double dOCYOffset = 0.0) const;
	inline long long GetElapsedTime() const;
	inline double GetSaturationResult(int nIndex = 0) const;
	inline bool GetCertificationResult() const;

private:
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	std::chrono::milliseconds m_elapsedTime;
	std::chrono::milliseconds m_startTimems;
	std::chrono::milliseconds m_endTimems;

	std::string m_strLogHeader;
	std::string m_strLogData;
	std::vector<CDPoint> m_vMarkPoint;
};


