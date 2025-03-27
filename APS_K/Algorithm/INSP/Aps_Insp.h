#pragma once

#include "algo_base.h"

typedef struct __TStainSpec
{
    TBlackSpotContrastN stSpecBlackSpot;
    TLCBSpecN stSpecLCB;
    TRU_YmeanSpecN stSpecYmean;
} TStainSpec;

//250327 Thunder Cheetah 모델검사 항목

//==.AA
//1.sfr
//2.oc
//3.Stain
//4.Defect

//==.Eol
//1.sfr
//2.Lens Shading Cal
//3. Shading_RG,BG,RG/BG Balance
//4.Stain
//5.Defect(Highlight)
//6.Edge shading
//7.iLLumination OC
//8.Dark


class CAPS_Insp
{
public:
	CAPS_Insp(void);
	~CAPS_Insp(void);
	
	void SetUnit(int nUnit){ m_nUnit = nUnit;}


	bool func_insp_CDP800_Current();
	bool func_insp_Voltage();
	bool func_Insp_CurrentMeasure(bool bLogDraw=true, bool bAutoMode = false);			//전류 측정 검사
	CString SetDir_Check(CString sPath);

    //color uniformity
    bool func_Insp_Stain(BYTE* img);


    int LCBInsp(BYTE* img, int nWidth, int nHeight, TDATASPEC& tDataSpec);//, IplImage* bmpImg);
    int Blemish_YmeanInsp(BYTE* img, int nWidth, int nHeight, TDATASPEC& tDataSpec);//, IplImage* bmpImg);
	int FDFInsp(BYTE* img, bool bAutoMode);
	//oc

	//R/C,B/C,Cr/Cb
	bool func_Insp_ColorSensitivity(BYTE* stainImg, int index, bool bAutoMode);


	//Relative Illumination (RI)
	bool func_Insp_Shm_Illumination(BYTE* img, bool bAutoMode = false, bool bUse8BitOnly = false);
	//Color Reproduction  shm모델 240625
	bool func_Insp_Color_reproduction(const BYTE* img, bool bAutoMode = false);
	bool g_GetIllumination(BYTE* RawImage);



	bool func_Insp_Illumination(BYTE* img, bool bAutoMode = false, bool bUse8BitOnly = false);
	int Inspect_RelativeIllumination(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecN& _Spec, TDATASPEC& tDataSpec, IplImage *cvImgRI, bool bUse8BitOnly = false);
	int Inspect_RelativeIlluminationX(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeIlluminationSpecX& _Spec, TDATASPEC& tDataSpec, IplImage *cvImgRI, bool bUse8BitOnly = false);
	int Inspect_RelativeUniformity(const BYTE* pBuffer, int nImageWidth, int nImageHeight, TRelativeUniformitySpec& _Spec, TDATASPEC& tDataSpec, IplImage *cvImgRU, bool bUse8BitOnly = false);
	int Inspect_ColorSensitivity(const BYTE* pBuffer, bool bUse8BitOnly = false);
	
	//dark , white , hot
	bool func_Insp_Defect(BYTE* midImage, BYTE* lowImage, bool bAutoMode = false);

	bool func_Insp_Saturation(BYTE* ChartRawImage, bool bAutoMode = false);

public:
	int  m_iPatternTest_ErrCnt;

#ifndef _M_X64
	CAlgoPixelDefectInspection* m_pAlgoPixelDefectInspection;
	CAlgoStainInspection* m_pAlgoStainInspection;
	CAlgoUniformityInspection* m_pAlgoUniformityInspection;
#endif

private:
	int m_nUnit;
};
