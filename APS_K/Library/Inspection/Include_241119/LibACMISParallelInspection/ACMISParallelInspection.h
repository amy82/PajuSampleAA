#pragma once
#include <vector>
#include <ppl.h>
#include <map>
#include <algorithm>
#include <tuple>
#include <atlstr.h>

#include "export.h"
#include "ACMISParallelInspectionDef.h"

class ACMISPARALLELINSPECTION_API CLibACMISParallelInspection
{
public:
	CLibACMISParallelInspection();
	~CLibACMISParallelInspection();

	bool parallel_inspection(TBufferInfoM& tImageBuffer, std::vector<INSPECTION_INPUT> &vectorInput, std::vector<INSPECTION_RESULT> &vectorResult);

protected:
#ifdef FUNCTION_GROUT_ENABLE
	std::map<ENUM_FUNCTION_GROUP_TYPE, std::function<std::vector<INSPECTION_RESULT> (std::vector<ParallelInpsectInput> &)> > m_FunctionGroupMap;
#else
	std::map<AlgorithmTestItem, std::function<INSPECTION_RESULT(ParallelInpsectInput &)> > m_FunctionMap;
#endif

protected:
	bool MakePackedBuffer(const BYTE* pBuffer, int nImageWidth, int nImageHeight, int nPartialDemosaic, TDATASPEC tDataSpec, std::vector<RECT> vROI, int* pDstBuffer);
	bool MakeInspectImage(const int* pSrcBuffer, int nImageWidth, int nImageHeight, TInspectRegionOffset tInspectRegionOffset, EImageFormat eImageFormat, TROIData tROI, TBufferInfo* pDstBufferInfo);

#ifdef FUNCTION_GROUT_ENABLE
	void GenerateFunctionGroupMap();
#else
	void GenerateFunctionMap();
#endif
};

