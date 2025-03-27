#pragma once

#include "export.h"
#include <LibACMISDefect\ACMISDefectDef.h>


// DO NOT INCLUDE BLEMISH HEADER FILE


class ACMISDEFECT_API CACMISDefectPixel : public CACMISDefectCommon<TDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectPixel();
	~CACMISDefectPixel();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};
#define CACMISImageDefectPixel CACMISDefectPixel

class ACMISDEFECT_API CACMISDefectHotPixel : public CACMISDefectCommon<TDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectHotPixel();
	~CACMISDefectHotPixel();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISDEFECT_API CACMISDefectHotPixelOMS : public CACMISDefectCommon<THotDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectHotPixelOMS();
	~CACMISDefectHotPixelOMS();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, THotDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, THotDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, THotDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, THotDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, THotDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISDEFECT_API CACMISDefectCluster : public CACMISDefectCommon<TDefectCluster>
{
	// below functions do not have any meanings in this algorithm.
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectCluster();
	~CACMISDefectCluster();
};
#define CACMISImageDefectCluster CACMISDefectCluster

class ACMISDEFECT_API CACMISDefectDarkShading : public CACMISDefectCommon<TDarkShading>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectCount(EDefectType type = EDefectType_All) const;
	const TDefectResult* GetDefectResult(EDefectType type, int nIndex) const;
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectDarkShading();
	~CACMISDefectDarkShading();
};

class ACMISDEFECT_API CACMISDefectDarkBLC : public CACMISDefectCommon<TDarkBLC>
{
	// below functions do not have any meanings in this algorithm.
	const TDefectResult* GetMaxDefectResult(EDefectType type = EDefectType_All) const;
	int GetDefectCount(EDefectType type = EDefectType_All) const;
	const TDefectResult* GetDefectResult(EDefectType type, int nIndex) const;
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectDarkBLC();
	~CACMISDefectDarkBLC();
};

class ACMISDEFECT_API CACMISDefectDarkLineNoise : public CACMISDefectCommon<TDarkLineNoise>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectDarkLineNoise();
	~CACMISDefectDarkLineNoise();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDarkLineNoise& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDarkLineNoise& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDarkLineNoise& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDarkLineNoise& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TDarkLineNoise& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetHorDefectCount() const;
	int GetVerDefectCount() const;
	const TDefectResult* GetHorDefectResult(int nIndex) const;
	const TDefectResult* GetVerDefectResult(int nIndex) const;
};
#define CACMISImageDarkLineNoise CACMISDefectDarkLineNoise

class ACMISDEFECT_API CACMISDefectColumnFPN : public CACMISDefectCommon<TColumnFPNDefect>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectColumnFPN();
	~CACMISDefectColumnFPN();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColumnFPNDefect& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TColumnFPNDefect& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TColumnFPNDefect& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TColumnFPNDefect& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TColumnFPNDefect& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISDEFECT_API CACMISDefectPixelCalibration : public CACMISDefectCommon<TDefectPixelCalibration>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectPixelCalibration();
	~CACMISDefectPixelCalibration();
};

class ACMISDEFECT_API CACMISDefectFDWhitePixel : public CACMISDefectCommon<TFDWhitePixel>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectFDWhitePixel();
	~CACMISDefectFDWhitePixel();
};

class ACMISDEFECT_API CACMISDefectBadPixelTable : public CACMISDefectCommon<TBadPixelTable>
{
	// below functions do not have any meanings in this algorithm.
	//int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectBadPixelTable();
	~CACMISDefectBadPixelTable();
};

class ACMISDEFECT_API CACMISDefectBrightModeFixedCommon : public CACMISDefectCommon<TDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectBrightModeFixedCommon();
	~CACMISDefectBrightModeFixedCommon();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};
#define CACMISImageBrightModeFixedCommon CACMISDefectBrightModeFixedCommon

class ACMISDEFECT_API CACMISDefectDarkModeFixedCommon : public CACMISDefectCommon<TDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectDarkModeFixedCommon();
	~CACMISDefectDarkModeFixedCommon();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};
#define CACMISImageDarkModeFixedCommon CACMISDefectDarkModeFixedCommon

class ACMISDEFECT_API CACMISDefectVeryDefectPixel : public CACMISDefectCommon<TVeryDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectVeryDefectPixel();
	~CACMISDefectVeryDefectPixel();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TVeryDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TVeryDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TVeryDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TVeryDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TVeryDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetVeryDefectCount() const;
	int GetVeryBrightDefectCount() const;
	int GetVeryDarkDefectCount() const;
	const TDefectResult* GetVeryDefectResult(int nIndex) const;
	const TDefectResult* GetVeryBrightDefectResult(int nIndex) const;
	const TDefectResult* GetVeryDarkDefectResult(int nIndex) const;
	int GetNormalDefectCount() const;
	int GetNormalBrightDefectCount() const;
	int GetNormalDarkDefectCount() const;
	const TDefectResult* GetNormalDefectResult(int nIndex) const;
	const TDefectResult* GetNormalBrightDefectResult(int nIndex) const;
	const TDefectResult* GetNormalDarkDefectResult(int nIndex) const;
};
#define CACMISImageVeryDefectPixel CACMISDefectVeryDefectPixel

class ACMISDEFECT_API CACMISDefectAllDefectPixel : public CACMISDefectCommon<TAllDefectPixel>
{
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectAllDefectPixel();
	~CACMISDefectAllDefectPixel();

	int GetBrightDefectCount() const;
	const TDefectResult* GetBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectResult() const;

	int GetDarkDefectCount() const;
	const TDefectResult* GetDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectResult() const;
};
#define CACMISImageDetectAllDefectPixel CACMISDefectAllDefectPixel

class ACMISDEFECT_API CACMISDefectLowLightDarkTest : public CACMISDefectCommon<TLowLightDarkTest>
{
	// below functions do not have any meanings in this algorithm.
	int GetDefectClusterCount(EDefectType type = EDefectType_All) const;
	const RECT& GetDefectClusterRect(EDefectType type, int nIndex) const;
	const TBlobResult* GetDefectClusterResult(EDefectType type, int nIndex) const;

public:
	CACMISDefectLowLightDarkTest();
	~CACMISDefectLowLightDarkTest();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLowLightDarkTest& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TLowLightDarkTest& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TLowLightDarkTest& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TLowLightDarkTest& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TLowLightDarkTest& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};
#define CACMISImageLowLightDarkTest CACMISDefectLowLightDarkTest

class ACMISDEFECT_API CACMISDefectSonyDefect : public CACMISDefectCommon<TSonyDefectPixel>
{
public:
	CACMISDefectSonyDefect();
	~CACMISDefectSonyDefect();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSonyDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TSonyDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TSonyDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TSonyDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TSonyDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

/*
class ACMISDEFECT_API CACMISDefectAllDefectPixel_ONSEMI_RCCB : public CACMISDefectCommonM<TAllDefectPixel_ONSEMI_RCCB>
{
public:
	CACMISDefectAllDefectPixel_ONSEMI_RCCB();
	~CACMISDefectAllDefectPixel_ONSEMI_RCCB();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_RCCB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_ONSEMI_RCCB& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_ONSEMI_RCCB& _Spec);

	int GetBrightDefectCount() const;
	const TDefectResult* GetBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectResult() const;

	int GetDarkDefectCount() const;
	const TDefectResult* GetDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectResult() const;

	int GetHotDefectCount() const;
	const TDefectResult* GetHotDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotDefectResult() const;

	int GetBrightDefectCoupletCount() const;
	const RECT& GetBrightDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetBrightDefectCoupletResult(int nIndex) const;

	int GetDarkDefectCoupletCount() const;
	const RECT& GetDarkDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetDarkDefectCoupletResult(int nIndex) const;

	int GetHotDefectCoupletCount() const;
	const RECT& GetHotDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetHotDefectCoupletResult(int nIndex) const;

	int GetBrightDefectClusterCount() const;
	const RECT& GetBrightDefectClusterRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterResult(int nIndex) const;

	int GetDarkDefectClusterCount() const;
	const RECT& GetDarkDefectClusterRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterResult(int nIndex) const;

	int GetHotDefectClusterCount() const;
	const RECT& GetHotDefectClusterRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterResult(int nIndex) const;

	int GetBrightDefectClusterColorCount() const;
	const RECT& GetBrightDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterColorResult(int nIndex) const;

	int GetDarkDefectClusterColorCount() const;
	const RECT& GetDarkDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterColorResult(int nIndex) const;

	int GetHotDefectClusterColorCount() const;
	const RECT& GetHotDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterColorResult(int nIndex) const;

	int GetDefectRowLineCountInDark() const;
	const TDefectResult* GetDefectRowLineResultInDark(int nIndex) const;
	int GetDefectColumnLineCountInDark() const;
	const TDefectResult* GetDefectColumnLineResultInDark(int nIndex) const;
	int GetDefectRowLineCountInBright() const;
	const TDefectResult* GetDefectRowLineResultInBright(int nIndex) const;
	int GetDefectColumnLineCountInBright() const;
	const TDefectResult* GetDefectColumnLineResultInBright(int nIndex) const;
	int GetDefectAllLineCountInDark() const;
	int GetDefectAllLineCountInBright() const;
	int GetDefectAllLineCount() const;

	int GetDefectColumnFPNCount() const;
	const TDefectResult* GetDefectColumnFPNResult(int nIndex = 0) const;
};

class ACMISDEFECT_API CACMISDefectAllDefectPixel_ONSEMI_MONO : public CACMISDefectCommonM<TAllDefectPixel_ONSEMI_MONO>
{
public:
	CACMISDefectAllDefectPixel_ONSEMI_MONO();
	~CACMISDefectAllDefectPixel_ONSEMI_MONO();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_MONO& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_ONSEMI_MONO& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_ONSEMI_MONO& _Spec);

	int GetBrightDefectCount() const;
	const TDefectResult* GetBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectResult() const;

	int GetBrightVeryDefectCount() const;
	const TDefectResult* GetBrightVeryDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightVeryDefectResult() const;

	int GetDarkDefectCount() const;
	const TDefectResult* GetDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectResult() const;

	int GetDarkVeryDefectCount() const;
	const TDefectResult* GetDarkVeryDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkVeryDefectResult() const;

	int GetHotDefectCount() const;
	const TDefectResult* GetHotDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotDefectResult() const;

	int GetHotVeryDefectCount() const;
	const TDefectResult* GetHotVeryDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotVeryDefectResult() const;

	int GetDefectCoupletCount() const;
	const RECT& GetDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetDefectCoupletResult(int nIndex) const;

	int GetHotDefectCoupletCount() const;
	const RECT& GetHotDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetHotDefectCoupletResult(int nIndex) const;

	int GetDefectClusterCount() const;
	const RECT& GetDefectClusterRect(int nIndex) const;
	const TBlobResult* GetDefectClusterResult(int nIndex) const;

	int GetHotDefectClusterCount() const;
	const RECT& GetHotDefectClusterRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterResult(int nIndex) const;
};
*/

class ACMISDEFECT_API CACMISDefectAllDefectPixel_OMS : public CACMISDefectCommonM<TAllDefectPixel_OMS>
{
public:
	CACMISDefectAllDefectPixel_OMS();
	~CACMISDefectAllDefectPixel_OMS();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_OMS& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_OMS& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_OMS& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_OMS& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TAllDefectPixel_OMS& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetBrightDefectCount() const;
	const TDefectResult* GetBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectResult() const;

	int GetDarkDefectCount() const;
	const TDefectResult* GetDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectResult() const;

	int GetHotDefectCount() const;
	const TDefectResult* GetHotDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotDefectResult() const;

	int GetLGITBrightDefectCount() const;
	const TDefectResult* GetLGITBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxLGITBrightDefectResult() const;

	int GetLGITDarkDefectCount() const;
	const TDefectResult* GetLGITDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxLGITDarkDefectResult() const;

	int GetBrightDefectClusterCount() const;
	const RECT& GetBrightDefectClusterRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterResult(int nIndex) const;

	int GetDarkDefectClusterCount() const;
	const RECT& GetDarkDefectClusterRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterResult(int nIndex) const;

	int GetHotDefectClusterCount() const;
	const RECT& GetHotDefectClusterRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterResult(int nIndex) const;

	int GetLGITBrightDefectClusterCount() const;
	const RECT& GetLGITBrightDefectClusterRect(int nIndex) const;
	const TBlobResult* GetLGITBrightDefectClusterResult(int nIndex) const;

	int GetLGITDarkDefectClusterCount() const;
	const RECT& GetLGITDarkDefectClusterRect(int nIndex) const;
	const TBlobResult* GetLGITDarkDefectClusterResult(int nIndex) const;
};

class ACMISDEFECT_API CACMISDefectAllDefectPixel_OV : public CACMISDefectCommonM<TAllDefectPixel_OV>
{
public:
	CACMISDefectAllDefectPixel_OV();
	~CACMISDefectAllDefectPixel_OV();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_OV& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_OV& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_OV& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_OV& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TAllDefectPixel_OV& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetBrightDefectCount() const;
	const TDefectResult* GetBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectResult() const;

	int GetDarkDefectCount() const;
	const TDefectResult* GetDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectResult() const;

	int GetHotDefectCount() const;
	const TDefectResult* GetHotDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotDefectResult() const;

	int GetBrightDefectClusterCount() const;
	const RECT& GetBrightDefectClusterRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterResult(int nIndex) const;

	int GetDarkDefectClusterCount() const;
	const RECT& GetDarkDefectClusterRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterResult(int nIndex) const;

	int GetHotDefectClusterCount() const;
	const RECT& GetHotDefectClusterRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterResult(int nIndex) const;

	int GetBrightDefectClusterColorCount() const;
	const RECT& GetBrightDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterColorResult(int nIndex) const;

	int GetDarkDefectClusterColorCount() const;
	const RECT& GetDarkDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterColorResult(int nIndex) const;

	int GetHotDefectClusterColorCount() const;
	const RECT& GetHotDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterColorResult(int nIndex) const;

	int GetDefectRowLineCountInDark() const;
	const TDefectResult* GetDefectRowLineResultInDark(int nIndex) const;
	int GetDefectColumnLineCountInDark() const;
	const TDefectResult* GetDefectColumnLineResultInDark(int nIndex) const;
	int GetDefectRowLineCountInBright() const;
	const TDefectResult* GetDefectRowLineResultInBright(int nIndex) const;
	int GetDefectColumnLineCountInBright() const;
	const TDefectResult* GetDefectColumnLineResultInBright(int nIndex) const;
	int GetDefectAllLineCountInDark() const;
	int GetDefectAllLineCountInBright() const;
	int GetDefectAllLineCount() const;
};

class ACMISDEFECT_API CACMISDefectAllDefectPixel_ONSEMI_ALL : public CACMISDefectCommonM<TAllDefectPixel_ONSEMI_ALL>
{
public:
	CACMISDefectAllDefectPixel_ONSEMI_ALL();
	~CACMISDefectAllDefectPixel_ONSEMI_ALL();

	bool Inspect();
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_ALL& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TAllDefectPixel_ONSEMI_ALL& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TAllDefectPixel_ONSEMI_ALL& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_ALL& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_RCCB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TAllDefectPixel_ONSEMI_RCCB& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TAllDefectPixel_ONSEMI_RCCB& _Spec);
	bool Inspect(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_MONO& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool Inspect(TBufferInfo& tBufferInfo, TAllDefectPixel_ONSEMI_MONO& _Spec);
	bool Inspect(TFileInfo& tFileInfo, TAllDefectPixel_ONSEMI_MONO& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_ALL& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_ONSEMI_ALL& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_ONSEMI_ALL& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_ALL& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_RCCB& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_ONSEMI_RCCB& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_ONSEMI_RCCB& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_ONSEMI_MONO& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_ONSEMI_MONO& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_ONSEMI_MONO& _Spec);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertSpec(TAllDefectPixel_ONSEMI_RCCB& _Spec, TAllDefectPixel_ONSEMI_ALL& _NewSpec);
	bool ConvertSpec(TAllDefectPixel_ONSEMI_MONO& _Spec, TAllDefectPixel_ONSEMI_ALL& _NewSpec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TAllDefectPixel_ONSEMI_ALL& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetBrightDefectCount() const;
	const TDefectResult* GetBrightDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectResult() const;

	int GetBrightVeryDefectCount() const;
	const TDefectResult* GetBrightVeryDefectResult(int nIndex) const;
	const TDefectResult* GetMaxBrightVeryDefectResult() const;

	int GetDarkDefectCount() const;
	const TDefectResult* GetDarkDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectResult() const;

	int GetDarkVeryDefectCount() const;
	const TDefectResult* GetDarkVeryDefectResult(int nIndex) const;
	const TDefectResult* GetMaxDarkVeryDefectResult() const;

	int GetHotDefectCount() const;
	const TDefectResult* GetHotDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotDefectResult() const;

	int GetHotVeryDefectCount() const;
	const TDefectResult* GetHotVeryDefectResult(int nIndex) const;
	const TDefectResult* GetMaxHotVeryDefectResult() const;

	int GetBrightDefectCoupletCount() const;
	const RECT& GetBrightDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetBrightDefectCoupletResult(int nIndex) const;

	int GetDarkDefectCoupletCount() const;
	const RECT& GetDarkDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetDarkDefectCoupletResult(int nIndex) const;

	int GetHotDefectCoupletCount() const;
	const RECT& GetHotDefectCoupletRect(int nIndex) const;
	const TBlobResult* GetHotDefectCoupletResult(int nIndex) const;

	int GetBrightDefectClusterCount() const;
	const RECT& GetBrightDefectClusterRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterResult(int nIndex) const;

	int GetDarkDefectClusterCount() const;
	const RECT& GetDarkDefectClusterRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterResult(int nIndex) const;

	int GetHotDefectClusterCount() const;
	const RECT& GetHotDefectClusterRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterResult(int nIndex) const;

	int GetBrightDefectClusterColorCount() const;
	const RECT& GetBrightDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterColorResult(int nIndex) const;

	int GetDarkDefectClusterColorCount() const;
	const RECT& GetDarkDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterColorResult(int nIndex) const;

	int GetHotDefectClusterColorCount() const;
	const RECT& GetHotDefectClusterColorRect(int nIndex) const;
	const TBlobResult* GetHotDefectClusterColorResult(int nIndex) const;

	int GetDefectRowLineCountInDark() const;
	const TDefectResult* GetDefectRowLineResultInDark(int nIndex) const;
	int GetDefectColumnLineCountInDark() const;
	const TDefectResult* GetDefectColumnLineResultInDark(int nIndex) const;
	int GetDefectRowLineCountInBright() const;
	const TDefectResult* GetDefectRowLineResultInBright(int nIndex) const;
	int GetDefectColumnLineCountInBright() const;
	const TDefectResult* GetDefectColumnLineResultInBright(int nIndex) const;
	int GetDefectAllLineCountInDark() const;
	int GetDefectAllLineCountInBright() const;
	int GetDefectAllLineCount() const;

	int GetDefectColumnFPNCount() const;
	const TDefectResult* GetDefectColumnFPNResult(int nIndex = 0) const;
};
#define CACMISDefectAllDefectPixel_ONSEMI_RCCB CACMISDefectAllDefectPixel_ONSEMI_ALL
#define CACMISDefectAllDefectPixel_ONSEMI_MONO CACMISDefectAllDefectPixel_ONSEMI_ALL

class ACMISDEFECT_API CACMISDefectAllDefectPixel_SONY : public CACMISDefectCommonM<TAllDefectPixel_SONY>
{
public:
	CACMISDefectAllDefectPixel_SONY();
	~CACMISDefectAllDefectPixel_SONY();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_SONY& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_SONY& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_SONY& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_SONY& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TAllDefectPixel_SONY& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetBrightDefectSP1LCount() const;
	const TDefectResult* GetBrightDefectSP1LResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectSP1LResult() const;
	int GetBrightDefectSP2LCount() const;
	const TDefectResult* GetBrightDefectSP2LResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectSP2LResult() const;

	int GetDarkDefectSP1LCount() const;
	const TDefectResult* GetDarkDefectSP1LResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectSP1LResult() const;
	int GetDarkDefectSP2LCount() const;
	const TDefectResult* GetDarkDefectSP2LResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectSP2LResult() const;

	int GetBrightDefectSP1LInDarkCount() const;
	const TDefectResult* GetBrightDefectSP1LInDarkResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectSP1LInDarkResult() const;
	int GetBrightDefectSP2HInDarkCount() const;
	const TDefectResult* GetBrightDefectSP2HInDarkResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectSP2HInDarkResult() const;
	int GetBrightDefectSP2LInDarkCount() const;
	const TDefectResult* GetBrightDefectSP2LInDarkResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectSP2LInDarkResult() const;

	int GetDarkDefectSP1HInSaturatedCount() const;
	const TDefectResult* GetDarkDefectSP1HInSaturatedResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectSP1HInSaturatedResult() const;
	int GetDarkDefectSP1LInSaturatedCount() const;
	const TDefectResult* GetDarkDefectSP1LInSaturatedResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectSP1LInSaturatedResult() const;
	int GetDarkDefectSP2HInSaturatedCount() const;
	const TDefectResult* GetDarkDefectSP2HInSaturatedResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectSP2HInSaturatedResult() const;
	int GetDarkDefectSP2LInSaturatedCount() const;
	const TDefectResult* GetDarkDefectSP2LInSaturatedResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectSP2LInSaturatedResult() const;

	int GetBrightDefectClusterSP1LCount() const;
	const RECT& GetBrightDefectClusterSP1LRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterSP1LResult(int nIndex) const;
	int GetBrightDefectClusterSP2LCount() const;
	const RECT& GetBrightDefectClusterSP2LRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterSP2LResult(int nIndex) const;

	int GetDarkDefectClusterSP1LCount() const;
	const RECT& GetDarkDefectClusterSP1LRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterSP1LResult(int nIndex) const;
	int GetDarkDefectClusterSP2LCount() const;
	const RECT& GetDarkDefectClusterSP2LRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterSP2LResult(int nIndex) const;

	int GetBrightDefectClusterSP1LInDarkCount() const;
	const RECT& GetBrightDefectClusterSP1LInDarkRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterSP1LInDarkResult(int nIndex) const;
	int GetBrightDefectClusterSP2HInDarkCount() const;
	const RECT& GetBrightDefectClusterSP2HInDarkRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterSP2HInDarkResult(int nIndex) const;
	int GetBrightDefectClusterSP2LInDarkCount() const;
	const RECT& GetBrightDefectClusterSP2LInDarkRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterSP2LInDarkResult(int nIndex) const;

	int GetDarkDefectClusterSP1HInSaturatedCount() const;
	const RECT& GetDarkDefectClusterSP1HInSaturatedRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterSP1HInSaturatedResult(int nIndex) const;
	int GetDarkDefectClusterSP1LInSaturatedCount() const;
	const RECT& GetDarkDefectClusterSP1LInSaturatedRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterSP1LInSaturatedResult(int nIndex) const;
	int GetDarkDefectClusterSP2HInSaturatedCount() const;
	const RECT& GetDarkDefectClusterSP2HInSaturatedRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterSP2HInSaturatedResult(int nIndex) const;
	int GetDarkDefectClusterSP2LInSaturatedCount() const;
	const RECT& GetDarkDefectClusterSP2LInSaturatedRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterSP2LInSaturatedResult(int nIndex) const;
};

class ACMISDEFECT_API CACMISDefectRivianPixel : public CACMISDefectCommon<TDefectPixel>
{
	// below functions do not have any meanings in this algorithm.

public:
	CACMISDefectRivianPixel();
	~CACMISDefectRivianPixel();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 1, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TDefectPixel& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TDefectPixel& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TDefectPixel& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 1, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TDefectPixel& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);
};

class ACMISDEFECT_API CACMISDefectAllDefectPixel_RIVIAN : public CACMISDefectCommonM<TAllDefectPixel_RIVIAN>
{
public:
	CACMISDefectAllDefectPixel_RIVIAN();
	~CACMISDefectAllDefectPixel_RIVIAN();

	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_RIVIAN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, bool bUsing8BitOnly = false, int nImageCount = 2, bool bPartialDemosaic = false, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectM(TBufferInfoM& tBufferInfo, TAllDefectPixel_RIVIAN& _Spec);
	bool InspectM(TFileInfoM& tFileInfo, TAllDefectPixel_RIVIAN& _Spec);
	bool InspectM(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TAllDefectPixel_RIVIAN& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectC(TBufferInfo& tBufferInfo, TInspectSpec& _Spec);
	bool InspectC(TFileInfo& tFileInfo, TInspectSpec& _Spec);
	bool InspectMC(const BYTE** pBuffer, int nImageWidth, int nImageHeight, TInspectSpec& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nImageCount = 2, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT);
	bool InspectMC(TBufferInfoM& tBufferInfo, TInspectSpec& _Spec);
	bool InspectMC(TFileInfoM& tFileInfo, TInspectSpec& _Spec);
	bool ConvertCommon2EachSpec(TInspectSpec& _Spec, TAllDefectPixel_RIVIAN& _NewSpec);
	bool GetInspectionResultC(TInspectResult &tResult, int nIndex = 0);

	int GetBrightDefectInDarkCount() const;
	const TDefectResult* GetBrightDefectInDarkResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectInDarkResult() const;

	int GetDarkDefectInDarkCount() const;
	const TDefectResult* GetDarkDefectInDarkResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectInDarkResult() const;

	int GetBrightDefectInBrightCount() const;
	const TDefectResult* GetBrightDefectInBrightResult(int nIndex) const;
	const TDefectResult* GetMaxBrightDefectInBrightResult() const;

	int GetDarkDefectInBrightCount() const;
	const TDefectResult* GetDarkDefectInBrightResult(int nIndex) const;
	const TDefectResult* GetMaxDarkDefectInBrightResult() const;

	int GetBrightDefectClusterInDarkCount() const;
	const RECT& GetBrightDefectClusterInDarkRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterInDarkResult(int nIndex) const;

	int GetDarkDefectClusterInDarkCount() const;
	const RECT& GetDarkDefectClusterInDarkRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterInDarkResult(int nIndex) const;

	int GetBrightDefectClusterInBrightCount() const;
	const RECT& GetBrightDefectClusterInBrightRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterInBrightResult(int nIndex) const;

	int GetDarkDefectClusterInBrightCount() const;
	const RECT& GetDarkDefectClusterInBrightRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterInBrightResult(int nIndex) const;

	int GetBrightDefectClusterColorInDarkCount() const;
	const RECT& GetBrightDefectClusterColorInDarkRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterColorInDarkResult(int nIndex) const;

	int GetDarkDefectClusterColorInDarkCount() const;
	const RECT& GetDarkDefectClusterColorInDarkRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterColorInDarkResult(int nIndex) const;

	int GetBrightDefectClusterColorInBrightCount() const;
	const RECT& GetBrightDefectClusterColorInBrightRect(int nIndex) const;
	const TBlobResult* GetBrightDefectClusterColorInBrightResult(int nIndex) const;

	int GetDarkDefectClusterColorInBrightCount() const;
	const RECT& GetDarkDefectClusterColorInBrightRect(int nIndex) const;
	const TBlobResult* GetDarkDefectClusterColorInBrightResult(int nIndex) const;

	int GetDefectRowLineCountInDark() const;
	const TDefectResult* GetDefectRowLineResultInDark(int nIndex) const;
	int GetDefectColumnLineCountInDark() const;
	const TDefectResult* GetDefectColumnLineResultInDark(int nIndex) const;
	int GetDefectRowLineCountInBright() const;
	const TDefectResult* GetDefectRowLineResultInBright(int nIndex) const;
	int GetDefectColumnLineCountInBright() const;
	const TDefectResult* GetDefectColumnLineResultInBright(int nIndex) const;
	int GetDefectAllLineCountInDark() const;
	int GetDefectAllLineCountInBright() const;
	int GetDefectAllLineCount() const;
};

