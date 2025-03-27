#pragma once


class CACMISResolutionSFR;

class CSFRChartProcHelper
{
public:
	CSFRChartProcHelper(void);
	~CSFRChartProcHelper(void);

	bool GetChartSetting(TChartSpec& _spec);
	bool Inspection(CACMISResolutionSFR* pChartProc, ResolutionImageBufferManager& _mgr);

};

