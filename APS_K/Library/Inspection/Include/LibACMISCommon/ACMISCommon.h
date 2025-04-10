#pragma once

#include "LibACMISCommon/CommonClass.h"
#include "LibACMISCommon/CommonEnum.h"
#include "LibACMISCommon/CommonStruct.h"
#include "LibACMISCommon/DataTypes.h"
#include "LibACMISCommon/Timer.h"

#include <algorithm>
#include <atlstr.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <vector>

using namespace std;

#define DEBUG_FILE_SAVE_PATH	"C:\\Users\\User\\Desktop"

extern void ConvertRECT2CPoint(RECT tROIRect, TROICPoint& tCenterPoint);
extern void ConvertRECT2CField(RECT tROIRect, int nImageWidth, int nImageHeight, TROIField& tField);
extern void ConvertRECT2SPoint(RECT tROIRect, TROISPoint& tStartPoint);
extern void ConvertRECT2TROIData(std::vector<RECT>& vROI_Rect, int nImageWidth, int nImageHeight, TROIData& tROI);

extern void Convert2RECT(TROICPoint tCenterPoint, RECT& tROIRect);
extern void Convert2RECT(TROIField tField, int nImageWidth, int nImageHeight, RECT& tROIRect);
extern void Convert2RECT(TROISPoint tStartPoint, RECT& tROIRect);

extern void Convert2TROICommon(TROICPoint tCenterPoint, TROIDataCommon& tROIData);
extern void Convert2TROICommon(TROIField tField, TROIDataCommon& tROIData);
extern void Convert2TROICommon(TROISPoint tStartPoint, TROIDataCommon& tROIData);
extern void Convert2TROICommon(RECT tRect, TROIDataCommon& tROIData);
extern void Convert2TROICommon(TROIData& tROI, std::vector<TROIDataCommon>& vROI);

extern void Convert2CPoint(TROIDataCommon tROIData, TROICPoint &tCenterPoint);
extern void Convert2Field(TROIDataCommon tROIData, TROIField &tField);
extern void Convert2SPoint(TROIDataCommon tROIData, TROISPoint &tStartPoint);
extern void Convert2RECT(TROIDataCommon tROIData, RECT& tRect);

extern void Convert2RECT(TROIDataCommon tROIData, int nWidth, int nHeight, RECT &tRect);
extern void Convert2RECT(TROIData& tROI, int nWidth, int nHeight, std::vector<RECT>& vROIRect);

extern double GetPixelSize(EDATAFORMAT eDataFormat);

extern double Get8BitConversionGamma(EDATAFORMAT eDataFormat);
extern double Get16BitConversionGamma(EDATAFORMAT eDataFormat);

extern bool LoadFiducialMarkInfo(const char* strFiducialMarkInfoPath, int nImageWidth, int nImageHeight, TInspectRegionOffset& tOffset, std::vector<TFiducialMarkType>& vFiducialMarkPoint, int& nMaxSize);

extern void CalcElapsedTime(std::chrono::system_clock::time_point& m_startTime, std::chrono::system_clock::time_point& m_endTime, std::chrono::milliseconds& m_elapsedTime, std::chrono::milliseconds& m_startTimems, std::chrono::milliseconds& m_endTimems);

extern void CheckDemosaicMethod(ESENSORTYPE &nSensorType, EDEMOSAICMETHOD &nDemosaicMethod, EOUTMODE nOutMode = OUTMODE_BAYER_RGGB);

extern std::string GetAlgorithmName(int nSpecIndex);

extern bool CheckROISize(TROIData& tROI);


// Singleton 패턴을 만들기 위한 매크로
#define MAKE_SINGLETON(classname)						\
private:												\
	classname() {}										\
	classname(const classname&) = delete;				\
	classname& operator=(const classname&) = delete;	\
public:													\
	static classname& GetInstance()						\
	{													\
		static classname instance;						\
		return instance;								\
	}													\
private:
