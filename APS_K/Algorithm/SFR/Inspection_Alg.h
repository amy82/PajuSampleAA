#pragma once
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "BlobLabeling.h"


//! Modified by LHW, 2013/3/4, 메모리 생성/해제 함수 추가, Spot 검사 추가
//! Modified by LHW, 2013/3/13, GetAverageValue 함수 추가
//! Modified by LHW, 2013/3/17, SFR 함수 수정
//! Modified by LHW, 2013/3/30, Edge 검사 추가
//! Modified by LHW, 2013/4/18, 이물 검사 관련하여 메모리 생성을 최소화 (OpenCV 버퍼에서의 ROI 설정)
//! Modified by LHW, 2013/4/23, LG 이노텍에서 제공한 SFR 연산 DLL 사용

#define		MAX_SFR_DATA_CNT		4000

//! LG 이노텍에서 제공한 DLL에서 SFR 연산 함수의 정의
typedef int(*SFRalgorithm)(
	int *pROI
	, int widthROI
	, int heightROI
	, int directionROI
	, double *SFR, double *cyclePerPixel
	, double cyclePerPixel1, double *valueSFR1
	, double cyclePerPixel2, double *valueSFR2
	, int optionSFR
	);

class CInspection_Alg
{
public:
	CInspection_Alg(void);
	~CInspection_Alg(void);

public:
	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! 이물 검사
	//! 찾아낸 이물의 상세 정보
	struct results
	{
		int num[_DEF_MAX_BLOBS * 4];
		int area[_DEF_MAX_BLOBS * 4];
		float gd[_DEF_MAX_BLOBS * 4];
		CvPoint	TopLeft[_DEF_MAX_BLOBS * 4];
		CvPoint	BottomRight[_DEF_MAX_BLOBS * 4];
	};
	//static struct results Blob_results;	
	//static int            Blob_results_Num;

	struct results Blob_results;
	int            Blob_results_Num;

	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CString	sLogMessage;

public:
	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! 이물 검사
	int AllocMemory(int iImageWidth, int iImageHeight);
	int AllocMemory_Spot(int iImageWidth, int iImageHeight);
	int AllocMemory_Scale(int iImageWidth, int iImageHeight, int iScale);
	void FreeMemory();

	int Inspection_Scale(IplImage* Gray_Img,
		int Scale,
		int Filter_S_Size, int Filter_L_Size,
		float m_Threshold,
		int Defect_Small_Size, int Defect_Large_Size,
		float m_GD,
		int m_Boundary, int m_Edge,
		int m_MaxDefectsCount);

	int Inspection_Spot(IplImage* Gray_Img,
		float m_Threshold,
		int Defect_Small_Size, int Defect_Large_Size,
		float m_GD,
		int m_Boundary,
		int m_MaxDefectsCount);

	int Inspection_edge(IplImage* Gray_Img,
		int Scale,
		int Filter_S_Size, int Filter_L_Size,
		float m_Threshold,
		int Defect_Small_Size, int Defect_Large_Size,
		float m_GD,
		int m_Boundary, int m_Edge,
		int m_MaxDefectsCount);

	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! 광축 검사
	bool getOpticalAxis(IplImage* src_img, int scale, CRect roi, double &offsetX, double &offsetY, int &iAvr);

	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! SFR 연산
	bool getSFR(IplImage* src_img, int fi_iWidth, int fi_iHight, float fi_fCcdSize, CRect fi_RectRoi, int& iDataCnt, double fo_DataX[MAX_SFR_DATA_CNT], double fo_DataY[MAX_SFR_DATA_CNT], double dGain = 1.0);
	bool getSFR2(unsigned char* r_buf, unsigned char* g_buf, unsigned char* b_buf, int fi_iWidth, int fi_iHight, float fi_fCcdSize, CRect fi_RectRoi, int& iDataCnt, double fo_DataX[MAX_SFR_DATA_CNT], double fo_DataY[MAX_SFR_DATA_CNT], double dGain = 1.0);
	double GetValue_SFR_N_4() { return m_dSFR_N_4; }
	double GetValue_SFR_N_8() { return m_dSFR_N_8; }
	double GetValue_SFR_N_4_X() { return m_dSFR_N_4_X; }
	double GetValue_SFR_N_8_X() { return m_dSFR_N_8_X; }

	HINSTANCE	 m_hDLL_SFR;					//! SFR DLL 핸들
	SFRalgorithm m_pSFRalgo;					//! 함수 포인터 (DLL의 SFR 본체 연산 함수)
	bool Ready_SFR_DLL(CString fi_sFilePath);	//! DLL 준비
	void Release_SFR_DLL();						//! DLL 해제

												//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
												//! 2차 Fitting
	bool calcPeakPos(int cnt, int* pos, double &val_A, double &val_B, double &val_C);
	bool _calcDoublePeakPos(int cnt, double posX[5], double posY[5], double &val_A, double &val_B, double &val_C);

	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! Added by LHW (2013/3/13)
	//! 해당 Color 이미지에서 각 색상별 평균값을 알아낸다. 
	bool GetAverageValue(IplImage* src_img, CRect fi_RectRoi, int fi_iSkipX, int fi_iSkipY, double &fo_dAvgRed, double &fo_dAvgGreen, double &fo_dAvgBlue);

private:
	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! 이물 검사
	CBlobLabeling m_blob;

	IplImage* m_bw;
	IplImage* m_bw_t;
	IplImage* m_Morph_Img;
	IplImage* m_Sub_Img;
	IplImage* m_Scale_Img;
	IplImage* m_filtered_Img;
	CvMat*    m_Mat_kernel;

	//! 위의 이미지 버퍼의 크기
	int m_iReal_Width_Image;
	int m_iReal_Height_Image;

	//! 원본 이미지의 크기 (기준값이 필요해서 따로 임시 저장한다.)
	int m_iWidth_Org_Image;
	int m_iHeight_Org_Image;

	void Make_Kernel(int S_KERNEL_LENGTH, int L_KERNEL_LENGTH, CvMat* mat_kernel);
	void Tri_Threshold(IplImage* src, float m_threshold, IplImage* bw, int scale, int boundary);
	void Edge_Except(IplImage* bw, int scale, int margin);
	int  BLOB_Analysis(IplImage* bw, IplImage* gray, int SMALL_SIZE, int LARGE_SIZE, int scale, float gray_threshold, int m_MaxDefectsCount);
	int  Spot_BLOB_Analysis(IplImage* bw, IplImage* gray, int SMALL_SIZE, int LARGE_SIZE, float gray_threshold, int m_Boundary, int m_MaxDefectsCount);

	//! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//! SFR 연산
	double m_dSFR_N_4;	//! SFR N/4값, 0.125
	double m_dSFR_N_8;	//! SFR N/8값, 0.0625
	double m_dSFR_N_4_X;
	double m_dSFR_N_8_X;

	void doGraySharpening(IplImage* img);
	int Linear_Interpolation(double* xdata, double* ydata, double* L_xdata, double* L_ydata);
};

