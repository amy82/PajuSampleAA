#pragma once

#include "LibACMISCommon/CommonStruct.h"
#include "LibACMISCommon/Timer.h"

#include <atlstr.h>
#include <chrono>
#include <memory>
#include <vector>

// blob 하나, BLOB_RUN_LENGTH_DATA 의 리스트로 표현
/**
* @brief 이물로 판단된 영역을 포함하는 최소 사각형을 나타내는 클래스
*/
class CBlobRect : public CRectEx
{
public:
	int Area;
	float Intensity;

	CBlobRect() : CRectEx(0, 0, 0, 0), Area(0), Intensity(0) {};
	CBlobRect(int left, int top, int right, int bottom, int area = 0, float intensity = 0)
		: CRectEx(left, top, right, bottom), Area(area), Intensity(intensity) {}

	void Merge(const CBlobRect& other);
	static CBlobRect GetMergedRect(const CBlobRect& a, const CBlobRect& b);
	static double GetOuterDistance(const CBlobRect& a, const CBlobRect& b);
};

class CBlobList
{
private:
	std::vector<CBlobRect> m_vBlob;

public:
	CBlobList() {};
	CBlobList(const CBlobList& other) : m_vBlob(other.m_vBlob) {}
	~CBlobList() {};

	CBlobList& operator=(const CBlobList& other) { m_vBlob = other.m_vBlob; return *this; }
	void Clear() { m_vBlob.clear(); }
	void Add(CBlobRect rect) { m_vBlob.push_back(rect); }
	int Size() const { return static_cast<int>(m_vBlob.size()); }
	const CBlobRect& Get(int i) const { return m_vBlob[i]; }
	void MergeAdjacentBlob(int distanceToAdjacent);
};

/**
* @brief 모든 검사 알고리즘 클래스의 공통 변수/함수를 모아둔 템플릿 클래스
* @tparam TSpec 각 검사 알고리즘에서 사용하는 spec 설정용 구조체
*/
template<typename TSpec>
class AbstractAlgorithm
{
protected:
	// Image Spec
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nUsing8BitOnly;
	int m_nPartialDemosaic;
	TDATASPEC m_tDataSpec;

	// Inspection Setting
	TSpec m_tSpec;
	TInspectRegionOffset m_tInspectRegionOffset;
	EInspectionResultCode m_eInspectionResultCode;
	ESaturationMethod m_eSaturationMethod;
	std::vector<double> m_vSaturationResult;
	bool m_bIsCertified;

	// Result Log
	std::string m_strLogHeader;
	std::string m_strLogData;
	std::string m_strVersion;

public:
	AbstractAlgorithm()
		: m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_bIsCertified(false)
		, m_eInspectionResultCode(INSPECTION_RESULT_CODE_FAIL), m_eSaturationMethod(SaturationMethod_Y)
	{
		memset(&m_tDataSpec, 0, sizeof(TDATASPEC));
		memset(&m_tSpec, 0, sizeof(TSpec));
		memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset));
	}
	virtual ~AbstractAlgorithm() {}

	virtual void Init() = 0;
	virtual bool Inspect(const int* pBuffer, int nImageWidth, int nImageHeight, const TSpec& tSpec,
                         const TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, const TSpec& tSpec,
	                              const TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;

	virtual const char* GetLogHeader() = 0;
	virtual const char* GetLogData() = 0;
	virtual const char* GetVersion() = 0;

	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY)
	{
		m_tInspectRegionOffset = { nStartOffsetX , nStartOffsetY , nEndOffsetX , nEndOffsetY };
	}
	inline void SetInspectPosOffset(const TInspectRegionOffset& tInspectRegionOffset)
	{
		m_tInspectRegionOffset = tInspectRegionOffset;
	}
	inline void SetSaturationMethod(ESaturationMethod nMethod = SaturationMethod_Y)
	{
		m_eSaturationMethod = nMethod;
	}
	inline void SetSaturationResult(int nIndex, double dSaturationResult)
	{
		if (0 <= nIndex || nIndex < m_vSaturationResult.size())
		{
			m_vSaturationResult[nIndex] = dSaturationResult;
		}
	}
	inline double GetSaturationResult(size_t nIndex = 0) const
	{
		return (0 <= nIndex || nIndex < m_vSaturationResult.size()) ? m_vSaturationResult[nIndex] : 0.0;
	}
	inline bool GetCertificationResult() const
	{
		return m_bIsCertified;
	}
	inline EInspectionResultCode GetInspectionResultCode() const
	{
		return m_eInspectionResultCode;
	}
};


/**
* @brief 모든 검사 알고리즘을 wrapping하는 클래스의 공통 변수/함수를 모아둔 템플릿 클래스
* @tparam TSpec 각 검사 알고리즘에서 사용하는 spec 설정용 구조체
*/
template<typename TSpec>
class AbstractACMIS
{
protected:
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	long long m_elapsedTime;

	std::string m_strTimeData;
	std::string m_strLogHeader;
	std::string m_strLogData;

	std::shared_ptr<AbstractAlgorithm<TSpec>> m_pImpl;

public:
	AbstractACMIS() : m_elapsedTime(0) {}
	virtual ~AbstractACMIS() {}

	inline void Init()
	{
		m_pImpl->Init();
	}
	inline bool Inspect(const TFileInfo& tFileInfo, const TSpec& tSpec)
	{
		Timer timer(m_startTime, m_endTime, m_elapsedTime, m_strTimeData);

		BYTE* pBuffer = nullptr;
		bool bRet = false;

		if (ACMISSoftISP::LoadImageFile(tFileInfo, &pBuffer) <= 0)
		{
			bRet = m_pImpl->Inspect(pBuffer, tFileInfo.nImageWidth, tFileInfo.nImageHeight, tSpec,
                                    tFileInfo.tDataSpec, tFileInfo.nUsing8BitOnly, tFileInfo.nPartialDemosaic);
		}
		if (pBuffer)
		{
			delete[] pBuffer;
		}

		return bRet;
	}
	inline bool Inspect(const TBufferInfo& tBufferInfo, const TSpec& tSpec)
	{
		Timer timer(m_startTime, m_endTime, m_elapsedTime, m_strTimeData);
		return m_pImpl->Inspect(tBufferInfo.pBuffer, tBufferInfo.nImageWidth, tBufferInfo.nImageHeight, tSpec,
                                tBufferInfo.tDataSpec, tBufferInfo.nUsing8BitOnly, tBufferInfo.nPartialDemosaic);
	}
	inline bool Inspect(const int* pBuffer, int nImageWidth, int nImageHeight, const TSpec& tSpec,
                        const TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0)
	{
		Timer timer(m_startTime, m_endTime, m_elapsedTime, m_strTimeData);
		return m_pImpl->Inspect(pBuffer, nImageWidth, nImageHeight, tSpec, tDataSpec, nUsing8BitOnly, nPartialDemosaic);
	}
	// 하위 호환성을 위한 함수(비권장)
	inline bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TSpec& tSpec, EDATAFORMAT eDataFormat,
                        EOUTMODE eOutMode, ESENSORTYPE eSensorType, int nBlackLevel, int nUsing8BitOnly = 0,
                        int nPartialDemosaic = 0, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT)
	{
		Timer timer(m_startTime, m_endTime, m_elapsedTime, m_strTimeData);

		TDATASPEC tDataSpec;
		tDataSpec.eDataFormat = eDataFormat;
		tDataSpec.eOutMode = eOutMode;
		tDataSpec.eSensorType = eSensorType;
		tDataSpec.eDemosaicMethod = eDemosaicMethod;
		tDataSpec.nBlackLevel = 0;

		return m_pImpl->Inspect(pBuffer, nImageWidth, nImageHeight, tSpec, tDataSpec, nUsing8BitOnly, nPartialDemosaic);
	}

	inline const char* GetLogHeader()
	{
		std::string logHeader = Timer::GetTimeDataHeader() + m_pImpl->GetLogHeader();
		return logHeader.c_str();
	}
	inline const char* GetLogData()
	{
		std::string logData = m_strTimeData + m_pImpl->GetLogData();
		return logData.c_str();
	}
	inline const char* GetVersion()
	{
		return m_pImpl->GetVersion();
	}

	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY)
	{
		m_pImpl->SetInspectPosOffset(nStartOffsetX, nStartOffsetY, nEndOffsetX, nEndOffsetY);
	}
	inline void SetInspectPosOffset(const TInspectRegionOffset& tInspectRegionOffset)
	{
		m_pImpl->SetInspectPosOffset(tInspectRegionOffset);
	}
	inline void SetSaturationMethod(ESaturationMethod nMethod = SaturationMethod_Y)
	{
		m_pImpl->SetSaturationMethod(nMethod);
	}
	inline void SetSaturationResult(int nIndex, double dSaturationResult)
	{
		m_pImpl->SetSaturationResult(nIndex, dSaturationResult);
	}
	inline double GetSaturationResult(size_t nIndex = 0) const
	{
		return m_pImpl->GetSaturationResult(nIndex);
	}
	inline bool GetCertificationResult() const
	{
		return m_pImpl->GetCertificationResult();
	}
	inline EInspectionResultCode GetInspectionResultCode() const
	{
		return m_pImpl->GetInspectionResultCode();
	}
	inline std::chrono::system_clock::time_point GetStartTime() const
	{
		return m_startTime;
	}
	inline std::chrono::system_clock::time_point GetEndTime() const
	{
		return m_endTime;
	}
	inline long long GetElapsedTimeMs() const
	{
		return m_elapsedTime;
	}
};