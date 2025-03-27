#include "stdafx.h"
#include "SFRChartProcHelper.h"
#include "opencv2\highgui\highgui.hpp"

#define PDC_LAVENDER				RGB(230,230,250)
#define PDC_GREEN					RGB(0,128,0)
#define PDC_LIGHTGREEN				RGB(144,238,144)
#define PDC_YELLOW					RGB(255,255,0)
#define PDC_BLACK					RGB(0,0,0)
#define PDC_RED						RGB(255,0,0)
#define PDC_BLUE					RGB(0,0,255)

#define CV_LAVENDER					CV_RGB(230,230,250)
#define CV_GREEN					CV_RGB(0,128,0)
#define CV_LIGHTGREEN				CV_RGB(144,238,144)
#define CV_YELLOW					CV_RGB(255,255,0)
#define CV_BLACK					CV_RGB(0,0,0)
#define CV_RED						CV_RGB(255,0,0)
#define CV_BLUE						CV_RGB(0,0,255)

CSFRChartProcHelper::CSFRChartProcHelper()
{
}

CSFRChartProcHelper::~CSFRChartProcHelper(void)
{
}

bool CSFRChartProcHelper::GetChartSetting(TChartSpec& _spec)
{
	// chart data
	_spec.dbufferType = 0; // not used
	_spec.dModuleChartDistance = 58.24133333;

	// Main Fiducial Mark data
	char strChartType[1024] = "DOT";
	_spec.stMainFiducialMark.pszChartType = strChartType;
	_spec.stMainFiducialMark.dDistanceXFromCenter = 205;//178.000000;
	_spec.stMainFiducialMark.dDistanceYFromCenter = 55.000000;
	_spec.stMainFiducialMark.nROIBoxSize = 75;
	_spec.stMainFiducialMark.dRealGapX = 35.0;
	_spec.stMainFiducialMark.dRealGapY = 10.0;
	_spec.stMainFiducialMark.dRadius = 20;

	// sub Fiducial Mark data
	_spec.stSubFiducialMark.pszChartType = strChartType;
	_spec.stSubFiducialMark.dDistanceXFromCenter = 178.000000;
	_spec.stSubFiducialMark.dDistanceYFromCenter = 50.000000;
	_spec.stSubFiducialMark.nROIBoxSize = 75;
	_spec.stSubFiducialMark.dRealGapX = 35.000000;
	_spec.stSubFiducialMark.dRealGapY = 10.000000;
	_spec.stSubFiducialMark.dRadius = 20;

	_spec.nAlgorithmType = 0;	// ISO12233
	_spec.ptDisplayXY.x = 500;
	_spec.ptDisplayXY.y = 50;
	_spec.nFontSize = 0.5;
	_spec.nDisplayGap = 20;
	_spec.nDisplayGapFromROI = 20;
	//_spec.bUseFFT = 1;

	_spec.rDFOVSpec.min = 100.000000;
	_spec.rDFOVSpec.max = 120.000000;
	_spec.rXTiltSpec.min = -300.000000;
	_spec.rXTiltSpec.max = 300.000000;
	_spec.rYTiltSpec.min = -300.000000;
	_spec.rYTiltSpec.max = 300.000000;
	_spec.rRotationSpec.min = -100.000000;
	_spec.rRotationSpec.max = 100.000000;
	_spec.rDistortionSpec.min = -3000;
	_spec.rDistortionSpec.max = 30000;

	char* pszChartPath = "specMTF_Fisheye.csv";
	if( pszChartPath && *pszChartPath != '\0' )
		_spec.strChartDetailInfoPath = pszChartPath;

	char *pszChartDeltaSpecPath = "specMTFdelta.csv";
	if( pszChartDeltaSpecPath && *pszChartDeltaSpecPath != '\0' )
		_spec.strChartDetailDeltaSpecInfoPath = pszChartDeltaSpecPath;	

	_spec.dFrequency[0] = 0.225000;	// convert 60lp/mm to cy/px 

	return true;

}

bool CSFRChartProcHelper::Inspection( CACMISResolutionSFR* pChartProc, ResolutionImageBufferManager& _mgr)
{
	if( pChartProc == NULL ) return false;

	pChartProc->SetImageBuffer(_mgr);

	printf("0-0");
	bool bFindAlign = pChartProc->ScanMainFiducialMark();
	printf("0-1");
	pChartProc->CalcDFOV();
	pChartProc->CalcTiltAndRotation();
	printf("0-2");
	if( !bFindAlign )
		return false;

	printf("0-3");

	if( pChartProc->ScanSubFiducialMark() )
	{
		pChartProc->CalcDFOV();
		pChartProc->CalcDistortion();
	}	

	printf("0-4");

	pChartProc->InitResolution();
	pChartProc->CalcResolution();

	return true;
}

