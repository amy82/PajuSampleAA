#include "stdafx.h"
#include "Inspection_Alg.h"

#include "../Library/Inspection/Include/LibACMISResolution/ACMISResolutionSFR.h"
#include "../PRI_INSP/MandoFinalSFR.h"

//CSFR	SFR;

//struct CInspection_Alg::results CInspection_Alg::Blob_results;
//int CInspection_Alg::Blob_results_Num;

CInspection_Alg::CInspection_Alg(void)
{
	m_bw = NULL;
	m_bw_t = NULL;
	m_Morph_Img = NULL;
	m_Sub_Img = NULL;
	m_Scale_Img = NULL;
	m_filtered_Img = NULL;

	m_iReal_Width_Image  = 0;
	m_iReal_Height_Image = 0;

	m_iWidth_Org_Image  = 0;
	m_iHeight_Org_Image = 0;

	int i = 0;
	
	for (i = 0; i < _DEF_MAX_BLOBS*4;i++){
		Blob_results.num[i] = 0;
		Blob_results.area[i] = 0;
		Blob_results.gd[i] = 0;
		Blob_results.TopLeft[i].x = 0;
		Blob_results.TopLeft[i].y = 0;
		Blob_results.BottomRight[i].x = 0;
		Blob_results.BottomRight[i].y = 0;
	}

	m_dSFR_N_4 = 0.;
	m_dSFR_N_8 = 0.;
	m_dSFR_N_4_X = 0.;
	m_dSFR_N_8_X = 0.;
	
	m_hDLL_SFR = NULL;
	m_pSFRalgo = NULL;
}
 

CInspection_Alg::~CInspection_Alg(void)
{
	Release_SFR_DLL();
	FreeMemory();	
}

int CInspection_Alg::AllocMemory(int iImageWidth, int iImageHeight)
{
	if ( iImageWidth <= 0 || iImageHeight <= 0 )
	{
		return -1;
	}
	
	FreeMemory();

	int iRet = m_blob.AllocMemory(iImageWidth, iImageHeight);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	//! 원본 이미지의 크기
	m_iWidth_Org_Image  = iImageWidth;
	m_iHeight_Org_Image = iImageHeight;

	m_bw   = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U, 1);
	m_bw_t = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U, 1);

	m_Morph_Img = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U,  1);
	m_Sub_Img   = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_16S, 1);

	m_Scale_Img    = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U, 1);
	m_filtered_Img = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8S, 1);

	//! 생성한 이미지 버퍼의 크기
	m_iReal_Width_Image  = iImageWidth;
	m_iReal_Height_Image = iImageHeight;

	if ( m_bw        == NULL || m_bw_t         == NULL || 
		 m_Morph_Img == NULL || m_Sub_Img      == NULL || 
		 m_Scale_Img == NULL || m_filtered_Img == NULL )
	{
		return -2;
	}

	return 1;
}

int CInspection_Alg::AllocMemory_Spot (int iImageWidth, int iImageHeight)
{
	if ( iImageWidth <= 0 || iImageHeight <= 0 )
	{
		return -1;
	}

	FreeMemory();

	int iRet = m_blob.AllocMemory(iImageWidth, iImageHeight);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	//! 원본 이미지의 크기
	m_iWidth_Org_Image  = iImageWidth;
	m_iHeight_Org_Image = iImageHeight;

	m_bw   = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U, 1);
	m_bw_t = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U, 1);

	m_Morph_Img = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_8U,  1);
	m_Sub_Img   = cvCreateImage(cvSize(iImageWidth, iImageHeight), IPL_DEPTH_16S, 1);
	
	//! 생성한 이미지 버퍼의 크기
	m_iReal_Width_Image  = iImageWidth;
	m_iReal_Height_Image = iImageHeight;

	if ( m_bw == NULL || m_bw_t == NULL || m_Morph_Img == NULL || m_Sub_Img == NULL )
	{
		return -2;
	}

	return 1;
}

int CInspection_Alg::AllocMemory_Scale(int iImageWidth, int iImageHeight, int iScale)
{
	if ( iImageWidth <= 0 || iImageHeight <= 0 || iScale <= 0 )
	{
		return -1;
	}

	// 영상 Scale%로 축소 또는 확대
	int iTempWidth  = iImageWidth  * iScale / 100;
	int iTempHeight = iImageHeight * iScale / 100;

	if ( iTempWidth <= 0 || iTempHeight <= 0 )
	{
		return -2;
	}

	FreeMemory();

	int iRet = m_blob.AllocMemory(iTempWidth, iTempHeight);
	if ( iRet < 0 )
	{
		return (-10 + iRet);
	}

	//! 원본 이미지의 크기
	m_iWidth_Org_Image  = iImageWidth;
	m_iHeight_Org_Image = iImageHeight;

	m_Scale_Img    = cvCreateImage(cvSize(iTempWidth, iTempHeight), IPL_DEPTH_8U, 1);
	m_filtered_Img = cvCreateImage(cvSize(iTempWidth, iTempHeight), IPL_DEPTH_8S, 1);
	m_bw           = cvCreateImage(cvSize(iTempWidth, iTempHeight), IPL_DEPTH_8U, 1);

	//! 생성한 이미지 버퍼의 크기
	m_iReal_Width_Image  = iTempWidth;
	m_iReal_Height_Image = iTempHeight;

	if ( m_bw == NULL || m_Scale_Img == NULL || m_filtered_Img == NULL )
	{
		return -2;
	}

	return 1;
}

void CInspection_Alg::FreeMemory()
{
	if ( m_bw != NULL )
	{
		if ( m_bw->roi != NULL )
		{
			cvResetImageROI(m_bw);
		}
		cvReleaseImage(&m_bw);
		m_bw = NULL;
	}
	if ( m_bw_t != NULL )
	{
		if ( m_bw_t->roi != NULL )
		{
			cvResetImageROI(m_bw_t);
		}
		cvReleaseImage(&m_bw_t);
		m_bw_t = NULL;
	}
	if ( m_Morph_Img != NULL )
	{
		if ( m_Morph_Img->roi != NULL )
		{
			cvResetImageROI(m_Morph_Img);
		}
		cvReleaseImage(&m_Morph_Img);
		m_Morph_Img = NULL;
	}
	if ( m_Sub_Img != NULL )
	{
		if ( m_Sub_Img->roi != NULL )
		{
			cvResetImageROI(m_Sub_Img);
		}
		cvReleaseImage(&m_Sub_Img);
		m_Sub_Img = NULL;
	}
	if ( m_Scale_Img != NULL )
	{
		if ( m_Scale_Img->roi != NULL )
		{
			cvResetImageROI(m_Scale_Img);
		}
		cvReleaseImage(&m_Scale_Img);
		m_Scale_Img = NULL;
	}
	if ( m_filtered_Img != NULL )
	{
		if ( m_filtered_Img->roi != NULL )
		{
			cvResetImageROI(m_filtered_Img);
		}
		cvReleaseImage(&m_filtered_Img);
		m_filtered_Img = NULL;
	}

	m_iReal_Width_Image  = 0;
	m_iReal_Height_Image = 0;

	m_blob.FreeMemory();
}

//! Modify by LHW (2013/3/29)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inspection spot function
// Input : IplImage* src_img 흑백 입력 영상 (원본 이미지 크기의 영상)
//         float m_Threshold : 평활화 된 이미지에서 불량후보 영역을 얻기위한 캐니 임계값. 0이상의 float으로 입력, 0~255까지 입력가능
//         int Defect_Small_Size, int Defect_Large_Size : 불량후보를 얻은후 labeling하여 각 라벨의 크기(화소수)가 Defect_Small_Size~Defect_Large_Size만 검출.
//         float m_GD : 불량후보를 얻은후 labeling하여 각 라벨의 평균화소값을 계산하여 화주변의 화소값 평균과의 차이가 m_GD 이상이면 검출.
//         int m_Boundary : m_Boundary는 영상의 가장자리 검사안할 영역의 픽셀수
//		   int m_MaxDefectsCount : 불량 개수제한.
// Output : 검출된 불량수
//          
//          클래스에 아래 구조체에 결과 저장
//			Blob_results.TopLeft[i] : 검출된 불량의 MBR 좌상좌표
//			Blob_results.BottomRight[i] : 검출된 불량의 MBR 우하좌표
//			Blob_results.num[i] : 검출된 불량의 번호
//			Blob_results.area[i]  : 검출된 불량의 화소개수
//			Blob_results.gd[i]  : 검출된 불량의 배경과의 차이값
//
// By CDJung
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CInspection_Alg::Inspection_Spot(IplImage* Gray_Img,
	                                 float m_Threshold, 
									 int Defect_Small_Size, int Defect_Large_Size, 
									 float m_GD, 
									 int m_Boundary, 
									 int m_MaxDefectsCount)
{
	//! 입력 매개 변수 확인
	if ( Gray_Img == NULL )
	{
		return 0;
	}

	//! [주의 사항] Boundary 값은 '1'보다 작으면 안된다.
	if ( m_Boundary < 1 )
	{
		m_Boundary = 1;
	}

	//! 버퍼 크기 확인
	bool bFlag_Memory = false;
	int  iAllocWidth  = m_iReal_Width_Image;
	int  iAllocHeight = m_iReal_Height_Image;

	if ( m_bw == NULL || m_bw_t == NULL || m_Morph_Img == NULL || m_Sub_Img == NULL )
	{
		bFlag_Memory = true;
		iAllocWidth  = Gray_Img->width;
		iAllocHeight = Gray_Img->height;
	}

	//if ( Gray_Img->width != m_iReal_Width_Image || Gray_Img->height != m_iReal_Height_Image )
	//{
	//	bFlag_Memory = true;
	//}

	if ( Gray_Img->width > m_iReal_Width_Image )
	{
		bFlag_Memory = true;
		iAllocWidth = Gray_Img->width;
	}
	if ( Gray_Img->height > m_iReal_Height_Image )
	{
		bFlag_Memory = true;
		iAllocHeight = Gray_Img->height;
	}

	if ( bFlag_Memory == true )
	{
		int iRet = AllocMemory(iAllocWidth, iAllocHeight);
		if ( iRet < 0 )
		{
			return 0;
		}
	}

	//! ROI (Region of Interest) 해제
	cvResetImageROI(Gray_Img);
	cvResetImageROI(m_Morph_Img);
	cvResetImageROI(m_Sub_Img);
	cvResetImageROI(m_bw_t);
	cvResetImageROI(m_bw);
			
	//! ROI (Region of Interest) 설정
	//cvSetImageROI(Gray_Img,    cvRect(0, 0, Gray_Img->width, Gray_Img->height));
	//cvSetImageROI(m_Morph_Img, cvRect(0, 0, Gray_Img->width, Gray_Img->height));
	//cvSetImageROI(m_Sub_Img,   cvRect(0, 0, Gray_Img->width, Gray_Img->height));
	//cvSetImageROI(m_bw_t,      cvRect(0, 0, Gray_Img->width, Gray_Img->height));
	//cvSetImageROI(m_bw,        cvRect(0, 0, Gray_Img->width, Gray_Img->height));

	//! Filtering
	int morph_num = 3; 

	cvDilate(Gray_Img,    m_Morph_Img, NULL, morph_num); 
	cvErode (m_Morph_Img, m_Morph_Img, NULL, morph_num*2);
	
	cvSub (Gray_Img,  m_Morph_Img,      m_Sub_Img); 
	cvAddS(m_Sub_Img, cvScalarAll(128), Gray_Img); 

	//! 이치화
	cvThreshold(Gray_Img, m_bw_t, 128+m_Threshold, 255, CV_THRESH_BINARY); 
	cvThreshold(Gray_Img, m_bw,   128-m_Threshold, 255, CV_THRESH_BINARY_INV); 
	
	cvAdd(m_bw, m_bw_t, m_bw);
		
	//! 불량 후보영역 BLOB 해석으로 실제 불량 검출
	int total_num = 0;
	total_num = Spot_BLOB_Analysis(m_bw, Gray_Img, Defect_Small_Size, Defect_Large_Size, m_GD, m_Boundary, m_MaxDefectsCount);

	Blob_results_Num = total_num;	
	
	return total_num;	
}

//! Added by LHW (2013/3/30)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inspection edge function
// Input : IplImage* src_img 흑백 입력 영상 (원본 이미지 크기의 영상)
//         int Scale : 영상의 크기(%), 1~100을 입력 예)50이면 영상을 50%로 축소함
//         int Filter_S_Size,int Filter_L_Size : 영상 평활화 필터 크기 Filter_S_Size는 1 또는 3, Filter_L_Size는 Filter_S_Size보다 큰 홀수(15,17,19,21 추천)
//         큰이물 검사시 3,21    작은이물 검사시 1,15   1,17   1,19 추천
//         float m_Threshold : 평활화 된 이미지에서 불량후보 영역을 얻기위한 캐니 임계값. 0이상의 float으로 입력, 0~255까지 입력가능
//         int Defect_Small_Size, int Defect_Large_Size : 불량후보를 얻은후 labeling하여 각 라벨의 크기(화소수)가 Defect_Small_Size~Defect_Large_Size만 검출.
//         float m_GD : 불량후보를 얻은후 labeling하여 각 라벨의 평균화소값을 계산하여 화주변의 화소값 평균과의 차이가 m_GD 이상이면 검출.
//         int m_Boundary, int m_Edge : m_Boundary는 영상의 가장자리 검사안할 영역의 픽셀수, m_Edge는 모서리 검사안할 영역의 픽셀수
//		   int m_MaxDefectsCount : 불량 개수제한.
// Output : 검출된 불량수
//          
//          클래스에 아래 구조체에 결과 저장
//			Blob_results.TopLeft[i] : 검출된 불량의 MBR 좌상좌표
//			Blob_results.BottomRight[i] : 검출된 불량의 MBR 우하좌표
//			Blob_results.num[i] : 검출된 불량의 번호
//			Blob_results.area[i]  : 검출된 불량의 화소개수
//			Blob_results.gd[i]  : 검출된 불량의 배경과의 차이값
//
// By CDJung
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CInspection_Alg::Inspection_edge(IplImage* Gray_Img,
	                                 int Scale, 
									 int Filter_S_Size, int Filter_L_Size,
	                                 float m_Threshold, 
									 int Defect_Small_Size, int Defect_Large_Size, 
									 float m_GD, 
									 int m_Boundary, int m_Edge, 
									 int m_MaxDefectsCount)
{
	return 1;

	//! 입력 매개 변수 확인
	if ( Gray_Img == NULL )
	{
		return 0;
	}

	//! [주의 사항] Boundary 값은 '1'보다 작으면 안된다.
	if ( m_Boundary < 1 )
	{
		m_Boundary = 1;
	}

	Filter_S_Size = 3;
	Filter_L_Size = 5;

	//! 버퍼 크기 확인
	bool bFlag_Memory = false;
	int  iAllocWidth  = m_iReal_Width_Image;
	int  iAllocHeight = m_iReal_Height_Image;
	
	// 영상 Scale%로 축소 또는 확대
	int iTempWidth  = Gray_Img->width  * Scale / 100;
	int iTempHeight = Gray_Img->height * Scale / 100;

	if ( m_bw == NULL || m_Scale_Img == NULL || m_filtered_Img == NULL )
	{
		bFlag_Memory = true;
		iAllocWidth  = iTempWidth;
		iAllocHeight = iTempHeight;
	}

	//if ( iTempWidth != m_iReal_Width_Image || iTempHeight != m_iReal_Height_Image )
	//{
	//	bFlag_Memory = true;
	//}

	if ( iTempWidth > m_iReal_Width_Image )
	{
		bFlag_Memory = true;
		iAllocWidth = iTempWidth;
	}
	if ( iTempHeight > m_iReal_Height_Image )
	{
		bFlag_Memory = true;
		iAllocHeight = iTempHeight;
	}

	if ( bFlag_Memory == true )
	{
		int iRet = AllocMemory(iAllocWidth, iAllocHeight);
		if ( iRet < 0 )
		{
			return 0;
		}
	}

	//! ROI (Region of Interest) 설정
	cvResetImageROI(Gray_Img);
	cvSetImageROI(m_Scale_Img,    cvRect(0, 0, iTempWidth, iTempHeight));
	cvSetImageROI(m_filtered_Img, cvRect(0, 0, iTempWidth, iTempHeight));
	cvSetImageROI(m_bw,           cvRect(0, 0, iTempWidth, iTempHeight));
	
	//! 입력된 이미지의 축소
	cvResize(Gray_Img, m_Scale_Img, CV_INTER_NN);
	
	//! 필터링	
	CvMat* mat_kernel = cvCreateMat(Filter_L_Size, Filter_L_Size, CV_32FC1);


	Make_Kernel(Filter_S_Size, Filter_L_Size, mat_kernel);


	cvFilter2D (m_Scale_Img, m_filtered_Img, mat_kernel, cvPoint(-1,-1));		// Filter_L_Size = 3, Filter_S_Size = 1에서 다운 되는 경우 발생.

	//! 캐니 에지 검출
	cvAddS  (m_filtered_Img, cvScalarAll(128), m_Scale_Img);
	cvSmooth(m_Scale_Img,    m_Scale_Img, CV_GAUSSIAN, 9,9,1,1);
	cvCanny (m_Scale_Img,    m_Scale_Img, m_Threshold, m_Threshold*3, 3);
	
	//! 연결성 확보
	cvSetZero(m_bw);
	cvAdd    (m_Scale_Img, m_bw, m_bw);
	cvDilate (m_bw,        m_bw, NULL, 5);
	cvErode  (m_bw,        m_bw, NULL, 5);
	
	//! 가장자리 영역 검사 제외
	Edge_Except(m_bw, Scale, m_Edge);
	
	//! 불량 후보영역 BLOB 해석으로 실제 불량 검출
	int total_num = 0;
	total_num = BLOB_Analysis(m_bw, m_Scale_Img, Defect_Small_Size, Defect_Large_Size, Scale, m_GD, m_MaxDefectsCount);
	
	//! 메모리 해제	
	cvReleaseMat(&mat_kernel);

	Blob_results_Num = total_num;

	//! ROI (Region of Interest) 해제
	cvResetImageROI(m_Scale_Img);
	cvResetImageROI(m_filtered_Img);	
	cvResetImageROI(m_bw);

	return total_num;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inspection scale function
// Input : IplImage* src_img 컬러 입력 영상 (원본 이미지 크기의 영상)
//         int Scale : 영상의 크기(%), 1~100을 입력 예)20이면 영상을 20% (1/5) 로 축소함 
//         int Filter_S_Size,int Filter_L_Size : 영상 평활화 필터 크기 Filter_S_Size는 1 또는 3, Filter_L_Size는 Filter_S_Size보다 큰 홀수(15,17,19,21 추천)
//         큰이물 검사시 3,21    작은이물 검사시 1,15   1,17   1,19 추천
//         float m_Threshold : 평활화 된 이미지에서 불량후보 영역을 얻기위한 임계값. 0이상의 float으로 입력, 0~255까지 입력가능
//         int Defect_Small_Size, int Defect_Large_Size : 불량후보를 얻은후 labeling하여 각 라벨의 크기(화소수)가 Defect_Small_Size~Defect_Large_Size만 검출.
//         float m_GD : 불량후보를 얻은후 labeling하여 각 라벨의 평균화소값을 계산하여 화주변의 화소값 평균과의 차이가 m_GD 이상이면 검출.
//         int m_Boundary, int m_Edge : m_Boundary는 영상의 가장자리 검사안할 영역의 픽셀수, m_Edge는 모서리 검사안할 영역의 픽셀수
// Output : 검출된 불량수
//          
//          클래스에 아래 구조체에 결과 저장
//			Blob_results.TopLeft[i] : 검출된 불량의 MBR 좌상좌표
//			Blob_results.BottomRight[i] : 검출된 불량의 MBR 우하좌표
//			Blob_results.num[i] : 검출된 불량의 번호
//			Blob_results.area[i]  : 검출된 불량의 화소개수
//			Blob_results.gd[i]  : 검출된 불량의 배경과의 차이값
//
// By CDJung
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CInspection_Alg::Inspection_Scale(IplImage* Gray_Img, 
										int Scale, 
										int Filter_S_Size, int Filter_L_Size,
										float m_Threshold, 
										int Defect_Small_Size, int Defect_Large_Size, 
										float m_GD, 
										int m_Boundary, int m_Edge, 
										int m_MaxDefectsCount)
{
	//! 입력 매개 변수 확인
	if ( Gray_Img == NULL )
	{
		return 0;
	}

	//! 버퍼 크기 확인
	bool bFlag_Memory = false;
	int  iAllocWidth  = m_iReal_Width_Image;
	int  iAllocHeight = m_iReal_Height_Image;

	// 영상 Scale%로 축소 또는 확대
	int iTempWidth  = Gray_Img->width  * Scale / 100;
	int iTempHeight = Gray_Img->height * Scale / 100;

	if ( m_bw == NULL || m_Scale_Img == NULL || m_filtered_Img == NULL )
	{
		bFlag_Memory = true;
		iAllocWidth  = iTempWidth;
		iAllocHeight = iTempHeight;
	}

	//if ( iTempWidth != m_iReal_Width_Image || iTempHeight != m_iReal_Height_Image )
	//{
	//	bFlag_Memory = true;
	//}

	if ( iTempWidth > m_iReal_Width_Image )
	{
		bFlag_Memory = true;
		iAllocWidth = iTempWidth;
	}
	if ( iTempHeight > m_iReal_Height_Image )
	{
		bFlag_Memory = true;
		iAllocHeight = iTempHeight;
	}

	if ( bFlag_Memory == true )
	{
		int iRet = AllocMemory(iAllocWidth, iAllocHeight);
		if ( iRet < 0 )
		{
			return 0;
		}
	}

	//! ROI (Region of Interest) 설정
	cvResetImageROI(Gray_Img);
	cvSetImageROI(m_Scale_Img,    cvRect(0, 0, iTempWidth, iTempHeight));
	cvSetImageROI(m_filtered_Img, cvRect(0, 0, iTempWidth, iTempHeight));
	cvSetImageROI(m_bw,           cvRect(0, 0, iTempWidth, iTempHeight));
	

	//! 입력된 이미지의 축소
	cvResize(Gray_Img, m_Scale_Img, CV_INTER_NN);
	
	//! Filtering
	if (Scale <= 80 && Scale >= 20)
	{
		cvSmooth(m_Scale_Img, m_Scale_Img, CV_GAUSSIAN, 3,3,1,1);
	}

	//! 필터링	
	CvMat* mat_kernel = cvCreateMat(Filter_L_Size, Filter_L_Size, CV_32FC1);
	Make_Kernel(Filter_S_Size, Filter_L_Size, mat_kernel);
	cvFilter2D (m_Scale_Img, m_filtered_Img, mat_kernel, cvPoint(-1,-1));

	//! 임계화
	cvSetZero(m_bw);
	Tri_Threshold(m_filtered_Img, m_Threshold, m_bw, Scale, m_Boundary);


/*
	cvShowImage("Kernel", mat_kernel);
	cvShowImage("Scale_Img", m_Scale_Img);
	cvShowImage("filtered_Img", m_filtered_Img);
	cvShowImage("Threshold", m_bw);
	
*/
		
	//! 가장자리 영역 검사 제외
	Edge_Except(m_bw, Scale, m_Edge);
	
	//! 불량 후보영역 BLOB 해석으로 실제 불량 검출
	int total_num = 0;
	total_num = BLOB_Analysis(m_bw, m_Scale_Img, Defect_Small_Size, Defect_Large_Size, Scale, m_GD, m_MaxDefectsCount);
	
	//! 메모리 해제	
	cvReleaseMat(&mat_kernel);

	Blob_results_Num = total_num;

	//! ROI (Region of Interest) 해제
	cvResetImageROI(m_Scale_Img);
	cvResetImageROI(m_filtered_Img);	
	cvResetImageROI(m_bw);

	return total_num;
}

//! Filter를 만든다. 
void CInspection_Alg::Make_Kernel(int small_Kernel, int large_Kernel, CvMat* mat_kernel)
{
	cvZero(mat_kernel);

	for (int i=0;i<large_Kernel;i++)
	{
		for (int j=0;j<large_Kernel;j++)
		{
			if (abs((large_Kernel-1)/2 - i) <= (small_Kernel-1)/2 && 
				abs((large_Kernel-1)/2 - j) <= (small_Kernel-1)/2)
			{
				cvmSet(mat_kernel,i,j,10.0f/(float)(small_Kernel*small_Kernel));
			}
			else 
			{
				cvmSet(mat_kernel,i,j,-10.0f/(float)(large_Kernel*large_Kernel - small_Kernel*small_Kernel));
			}
		}
	}
}

//! Filtering된 이미지에서 이물이 있는 것으로 예상되는 pixel들을 찾아낸다. 
void CInspection_Alg::Tri_Threshold(IplImage* src, float m_threshold, IplImage* bw, int scale, int boundary)
{
	int m_boundary = (int)((float)boundary*(float)scale/100);
	if (m_boundary==0)
	{
		m_boundary =1;
	}

	int iWidth  = 0;
	int iHeight = 0;
	if ( src->roi != NULL )
	{
		iWidth  = src->roi->width - m_boundary;
		iHeight = src->roi->height - m_boundary;
	}
	else
	{
		iWidth  = src->width - m_boundary;
		iHeight = src->height - m_boundary;
	}

	for (int i=m_boundary;i<iHeight;i++)
	{
		for (int j=m_boundary;j<iWidth;j++)
		{
			if (src->imageData[i*src->widthStep+j] <= -m_threshold*10) 
			{
				bw->imageData[i*src->widthStep+j] = (unsigned char)255;	//! [주의 사항] '255'로 그대로 두세요. 수정하지 마십시오. by LHW
			}
		}
	}
}

//! 이미지의 4개의 모서리를 제외한다.
void CInspection_Alg::Edge_Except(IplImage* bw,int scale, int margin)
{
	int m_margin = (int)((float)margin*(float)scale/100);
	if (m_margin==0)
	{
		m_margin = 1;
	}

	int iWidth  = 0;
	int iHeight = 0;
	if ( bw->roi != NULL )
	{
		iWidth  = bw->roi->width;
		iHeight = bw->roi->height;
	}
	else
	{
		iWidth  = bw->width;
		iHeight = bw->height;
	}

	for (int i=0;i<m_margin;i++)
	{
		for (int j=0;j<m_margin;j++)
		{
			if (sqrtf((float)i*(float)i + (float)j*(float)j)<m_margin)
			{
				bw->imageData[i*bw->widthStep+j] = 0;
			}
		}
	}
	for (int i=0;i<m_margin;i++)
	{
		for (int j=iWidth-m_margin;j<iWidth;j++)
		{
			if (sqrtf((float)i*(float)i + (float)(j-iWidth)*(float)(j-iWidth))<m_margin)
			{
				bw->imageData[i*bw->widthStep+j] = 0;
			}
		}
	}
	for (int i=iHeight-m_margin;i<iHeight;i++)
	{
		for (int j=0;j<m_margin;j++)
		{
			if (sqrtf((float)(i-iHeight)*(float)(i-iHeight) + (float)j*(float)j)<m_margin)
			{
				bw->imageData[i*bw->widthStep+j] = 0;
			}
		}
	}
	for (int i=iHeight-m_margin;i<iHeight;i++)
	{
		for (int j=iWidth-m_margin;j<iWidth;j++)
		{
			if (sqrtf((float)(i-iHeight)*(float)(i-iHeight) + (float)(j-iWidth)*(float)(j-iWidth))<m_margin)
			{
				bw->imageData[i*bw->widthStep+j] = 0;
			}
		}
	}
}

int CInspection_Alg::BLOB_Analysis(IplImage* bw,IplImage* gray,int SMALL_SIZE,int LARGE_SIZE,int scale, float gray_threshold, int m_MaxDefectsCount)
{
	m_blob.SetParam( bw, gray, SMALL_SIZE ,LARGE_SIZE, gray_threshold, m_MaxDefectsCount);	// 레이블링 할 이미지와 최소 픽셀수 등을 설정
	m_blob.DoLabeling();

	CvPoint	pt1;
	CvPoint	pt2;


	// 각 후보영역 검사
	if (m_blob.m_nBlobs > 0){
		for( int i=0; i < m_blob.m_nBlobs; i++ )
		{
			pt1 = cvPoint(	(m_blob.m_recBlobs[i].x)*100/scale,				
				            (m_blob.m_recBlobs[i].y)*100/scale );
			pt2 = cvPoint(	pt1.x + m_blob.m_recBlobs[i].width*100/scale,	
				            pt1.y + m_blob.m_recBlobs[i].height*100/scale );

			Blob_results.TopLeft[i] = pt1;
			Blob_results.BottomRight[i] = pt2;
			Blob_results.num[i] = i;
			Blob_results.area[i] = m_blob.m_Area[i];
			Blob_results.gd[i] = m_blob.m_GD[i];
		}
	}
		
	return m_blob.m_nBlobs;
}


int CInspection_Alg::Spot_BLOB_Analysis(IplImage* bw,IplImage* gray,int SMALL_SIZE,int LARGE_SIZE, float gray_threshold, int m_Boundary, int m_MaxDefectsCount)
{
	for (int i=0;i<m_Boundary;i++)
	{
		for (int j=0;j<bw->width;j++)
		{
			bw->imageData[i*bw->widthStep+j] = 0;
		}
	}	
	for (int i=bw->height-m_Boundary;i<bw->height;i++)
	{
		for (int j=0;j<bw->width;j++)
		{
			bw->imageData[i*bw->widthStep+j] = 0;
		}
	}	
	for (int i=0;i<bw->height;i++)
	{
		for (int j=0;j<m_Boundary;j++)
		{
			bw->imageData[i*bw->widthStep+j] = 0;
		}
	}
	for (int i=0;i<bw->height;i++)
	{
		for (int j=bw->width-m_Boundary;j<bw->width;j++)
		{
			bw->imageData[i*bw->widthStep+j] = 0;
		}
	}

	m_blob.SetParam( bw, gray, SMALL_SIZE ,LARGE_SIZE, gray_threshold, m_MaxDefectsCount);	// 레이블링 할 이미지와 최소 픽셀수 등을 설정
	m_blob.DoLabeling();

	CvPoint	pt1;
	CvPoint	pt2;

	// 각 후보영역 검사
	if (m_blob.m_nBlobs > 0){
		for( int i=0; i < m_blob.m_nBlobs; i++ )
		{
			pt1 = cvPoint(	m_blob.m_recBlobs[i].x, m_blob.m_recBlobs[i].y );
			pt2 = cvPoint(	pt1.x + m_blob.m_recBlobs[i].width, pt1.y + m_blob.m_recBlobs[i].height );

			Blob_results.TopLeft[i] = pt1;
			Blob_results.BottomRight[i] = pt2;
			Blob_results.num[i] = i;
			Blob_results.area[i] = m_blob.m_Area[i];
			Blob_results.gd[i] = m_blob.m_GD[i];
		}
	}

	return m_blob.m_nBlobs;
}




bool CInspection_Alg::getOpticalAxis(IplImage* src_img, int fi_scale, CRect roi, double &fo_dOffsetX, double &fo_dOffsetY, int &iAvr)
{
	int width = src_img->width;
	int height = src_img->height;

	fo_dOffsetX = width * 0.5;
	fo_dOffsetY = height * 0.5;



	int sx = roi.left;
	int ex = roi.right;
	int sy = roi.top;
	int ey = roi.bottom;

	if(sx<0)			sx = 0;
	if(sy<0)			sy = 0;
	if(ex>width)		ex = width - 1;
	if(ey>height)		ey = height - 1;

	if( (ex<=sx) || (ey<=sy))
	{
		sLogMessage.Format("getOpticalAxis Check Resin Error (%d, %d, %d, %d)", roi.left, roi.top, roi.right, roi.bottom);
		return false;
	}

	int* pHist_x;
	int* pHist_y;

	pHist_x = new int[width];
	memset(pHist_x, 0 , sizeof(int)*width);
	pHist_y = new int[height];
	memset(pHist_y, 0 , sizeof(int)*height);


	IplImage* Gray_Img;

	Gray_Img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);
	cvCvtColor(src_img, Gray_Img, CV_BGR2GRAY);

	int x, y, pos, sum, curGap;

	curGap = fi_scale * width;

	for (x=sx; x<ex; x+=fi_scale)
	{
		sum = 0;
		pos = sy*width + x;
		for (y=sy; y<ey; y+=fi_scale, pos+=curGap)
		{
			sum += Gray_Img->imageData[pos];
		}

		pHist_x[x] = sum;
	}

	int cnt=0;
	int TotalSum =0;
	curGap = fi_scale;
	for (y=sy; y<ey; y+=fi_scale)
	{
		sum = 0;
		pos = y*width + sx;
		for (x=sx; x<ex; x+=fi_scale, pos+=curGap)
		{
			cnt++;
			sum += Gray_Img->imageData[pos];
		}

		pHist_y[y] = sum;
		TotalSum += sum;
	}

	iAvr = (int)(TotalSum/cnt);
	cvReleaseImage(&Gray_Img);

	double Ax, Bx, Cx;
	double Ay, By, Cy;

	if(!calcPeakPos(width, pHist_x, Ax, Bx, Cx))
	{
		sLogMessage = "calcPeakPos Calc Fail [X].";
	}
	else if(!calcPeakPos(height, pHist_y, Ay, By, Cy))
	{
		sLogMessage = "calcPeakPos Calc Fail [Y].";
	}
	else
	{
		fo_dOffsetX = -Bx / 2 / Ax;
		fo_dOffsetY = -By / 2 / Ay;
	}

	delete [] pHist_x;
	pHist_x = NULL;

	delete [] pHist_y;
	pHist_y = NULL;

	return true;
}

//! Added by LHW (2013/3/13)
//! 해당 Color 이미지에서 각 색상별 평균값을 알아낸다. 
bool CInspection_Alg::GetAverageValue(IplImage* src_img, CRect fi_RectRoi, int fi_iSkipX, int fi_iSkipY, double &fo_dAvgRed, double &fo_dAvgGreen, double &fo_dAvgBlue)
{
	int iSizeX = fi_RectRoi.right - fi_RectRoi.left;
	int iSizeY = fi_RectRoi.bottom - fi_RectRoi.top;

	if ( iSizeX <= 0 || iSizeY <= 0 )
	{
		return false;
	}

	if(fi_RectRoi.left<0 || fi_RectRoi.top<0 )
	{
		sLogMessage.Format("Check Resin Error. L:%d, T:%d", fi_RectRoi.left, fi_RectRoi.top);
		return false;
	}

	if ( fi_iSkipX <= 0 )
	{
		fi_iSkipX = 1;
	}
	if ( fi_iSkipX >= (fi_RectRoi.Width() / 2) )
	{
		fi_iSkipX = fi_RectRoi.Width() / 2;
	}
	if ( fi_iSkipY <= 0 )
	{
		fi_iSkipY = 1;
	}
	if ( fi_iSkipY >= (fi_RectRoi.Height() / 2) )
	{
		fi_iSkipY = fi_RectRoi.Height() / 2;
	}

	CvScalar v_pixel;

	double dSumRed = 0., dSumGreen = 0., dSumBlue = 0.;
	int iCnt = 0;

	for(int y=0; y<iSizeY; y+=fi_iSkipY)
	{
		for(int x=0; x<iSizeX; x+=fi_iSkipX)
		{
			v_pixel = cvGet2D(src_img, fi_RectRoi.top+y, fi_RectRoi.left+x);

			//	openCV에서는 BGR 순으로 Color 배열..?
			dSumRed   += v_pixel.val[0];
			dSumGreen += v_pixel.val[1];
			dSumBlue  += v_pixel.val[2];	

			iCnt++;
		}
	}

	if ( iCnt <= 0 )
	{
		return false;
	}

	fo_dAvgRed   = dSumRed   / ((double)iCnt);
	fo_dAvgGreen = dSumGreen / ((double)iCnt);
	fo_dAvgBlue  = dSumBlue  / ((double)iCnt);

	return true;
}

//! SFR 연산에서 X축이 lp/mm (Line Pair/mm)일 때, X축의 데이터를 1간격으로 맞추어주는 역할을 한다.
int CInspection_Alg::Linear_Interpolation(double* xdata,double* ydata, double* L_xdata,double* L_ydata)
{
	int i = 0;
	int num = 0;
	int step = 0;
	int start = 0;
	int end = 0;

	while(1)
	{
		if (ydata[num]< 0.000001)
		{
			break;
		}
		else
		{
			num++;
		}
	}

	start	= (int)xdata[step];
	end		= (int)xdata[step+1];

	for (i=0;i<(int)xdata[num-1]+1;i++)
	{
		if (end <= i)
		{
			step++;
			start	= (int)xdata[step];
			end		= (int)xdata[step+1];
		}
		if (start <= i && end > i)
		{
			L_xdata[i] = (double)i;
			L_ydata[i] = ((ydata[step+1]-ydata[step])/(xdata[step+1]-xdata[step]))*(L_xdata[i]-xdata[step]) + ydata[step];
		}
	}
	return (int)(xdata[num-1]);
}

//! DLL 준비
bool CInspection_Alg::Ready_SFR_DLL(CString fi_sFilePath)
{
	if ( IsExist_Path(fi_sFilePath) == false )
	{
		return false;
	}

	Release_SFR_DLL();

	m_hDLL_SFR = LoadLibrary(fi_sFilePath);
	if ( m_hDLL_SFR == NULL )
	{
		return false;
	}

	m_pSFRalgo = (SFRalgorithm)GetProcAddress(m_hDLL_SFR,"SFRalgorithm");
	if ( m_pSFRalgo == NULL )
	{
		return false;
	}

	return true;
}

//! DLL 해제
void CInspection_Alg::Release_SFR_DLL()
{
	if ( m_hDLL_SFR != NULL )
	{
		FreeLibrary(m_hDLL_SFR);
		m_hDLL_SFR = NULL;
		m_pSFRalgo = NULL;
	}
}

void CInspection_Alg::doGraySharpening( IplImage* img ) 
{ 
	int w = img->width; 
	int h = img->height; 

	IplImage* gray2 = cvCreateImage( cvGetSize(img) , 32, 1 ); 

	cvConvertScale( img, gray2, 1.0 ); 

	IplImage* lapl = cvCreateImage( cvGetSize(img) , 32, 1 ); 


	CvMat* ker = cvCreateMat( 5, 5, CV_32FC1); 

	// Imatest Alg 참조.
	double ksharp = 0.3; 
	cvSet( ker, cvScalarAll( 0.0 ) ); 
	cvSet2D( ker, 2, 0, cvScalarAll( -0.5*ksharp/(1-ksharp))); 
	cvSet2D( ker, 2, 4, cvScalarAll(  -0.5*ksharp/(1-ksharp))); 
	cvSet2D( ker, 2, 2, cvScalarAll( 1/(1-ksharp)) ); 


	cvFilter2D( gray2, lapl, ker ); 

	cvReleaseMat( &ker ); 

	double maxv = 0.0; 

	double minv = DBL_MAX; 

	cvMinMaxLoc( lapl, &minv, &maxv ); 

	for( int i=0; i<w*h; i++ ) 
	{ 
		double lap_val = cvGet1D( lapl, i ).val[0]; 
		int v = (int)( (255.0*lap_val/ maxv) +0.5); 
		cvSet1D( img, i, cvScalarAll( v) ); 
	} 
	maxv = 0.0; 

	cvMinMaxLoc( img, &minv, &maxv ); 

	for( int i=0; i<w*h; i++ ) 
	{ 
		double val = cvGet1D( img, i ).val[0]; 
		int v = (int)( (255.0*val/maxv) + 0.5); 
		cvSet1D( img, i, cvScalarAll( v) ); 
	} 

	cvReleaseImage( &gray2 ); 
	cvReleaseImage(&lapl);
}

//! 2차 Fitting
bool CInspection_Alg::calcPeakPos(int cnt, int* pos, double &val_A, double &val_B, double &val_C)
{
	int count = 0;
	double XXXXi=0.0, XXXi=0.0, XXi=0.0, Xi=0.0, XXYi=0.0, XYi=0.0, Yi=0.0, D;

	for(int i=0; i<cnt; i++)
	{
		if(pos[i] != 0)
		{
			XXXXi+=(double)i*i*i*i;
			XXXi+=(double)i*i*i;
			XXi+=(double)i*i;
			Xi+=(double)i;
			XXYi+=(double)i*i*(double)pos[i];
			XYi+=(double)i*(double)pos[i];
			Yi+=(double)pos[i];
			count++;
		}
	}

	D=(XXXXi*XXi*count)+2*(XXXi*Xi*XXi)-((XXi*XXi*XXi)+(XXXXi*Xi*Xi)+(XXXi*XXXi*count));

	if(D == 0)
		return false;
	
	val_A=(((count*XXi-Xi*Xi)*XXYi)-((count*XXXi-Xi*XXi)*XYi)+((XXXi*Xi-XXi*XXi)*Yi))/D;
	val_B=(-((count*XXXi-Xi*XXi)*XXYi)+((count*XXXXi-XXi*XXi)*XYi)-((XXXXi*Xi-XXXi*XXi)*Yi))/D;
	val_C=(((XXXi*Xi-XXi*XXi)*XXYi)-((XXXXi*Xi-XXi*XXXi)*XYi)+((XXXXi*XXi-XXXi*XXXi)*Yi))/D;

	return true;
}

//! 2차 Fitting
bool CInspection_Alg::_calcDoublePeakPos(int cnt, double posX[5], double posY[5], double &val_A, double &val_B, double &val_C)
{
	double valY, gapY, rateY, pos;

	if(cnt>5)
	{
		cnt = 5;
	}


	double XXXXi=0.0, XXXi=0.0, XXi=0.0, Xi=0.0, XXYi=0.0, XYi=0.0, Yi=0.0, D;

	for(int i=0; i<cnt; i++)
	{
		XXXXi	+=posX[i]	*posX[i]	*posX[i]	*posX[i];
		XXXi	+=posX[i]	*posX[i]	*posX[i];
		XXi		+=posX[i]	*posX[i];
		Xi		+=posX[i];
		XXYi	+=posX[i]*posX[i]*posY[i];
		XYi		+=posX[i]*posY[i];
		Yi		+=posY[i];
	}

	D = (XXXXi*XXi*cnt)+2*(XXXi*Xi*XXi) - ((XXi*XXi*XXi)+(XXXXi*Xi*Xi)+(XXXi*XXXi*cnt));


//	if(D == 0)
	if(1)
	{
		int maxIndexY = -1;
		double maxVal = -9999;

		for(int i=0; i<cnt; i++)
		{
			if(maxVal < posY[i])
			{
				maxVal = posY[i];
				maxIndexY = i;
			}
		}

		if( (maxIndexY < 0) || (maxIndexY >= cnt) )
			return false;


		// double d_max_Z_pos = -d_calc_B / (2*d_calc_A);

		if(maxIndexY==0)
		{
			val_A = -0.5;
			val_B = posY[maxIndexY];
		}
		else if(maxIndexY==cnt-1)
		{
			val_A = -0.5;
			val_B = posY[maxIndexY];
		}
		else 
		{
			val_A = -0.5;

			if( posY[maxIndexY-1] > posY[maxIndexY+1] )
			{
				valY = posY[maxIndexY] - posY[maxIndexY-1];
				gapY = posY[maxIndexY] - posY[maxIndexY+1];

				rateY = valY / gapY;
				pos = posX[maxIndexY] + (posX[maxIndexY+1] - posX[maxIndexY]) * rateY;

				val_B = (posX[maxIndexY-1]+ pos) / 2;
			}
			else
			{
				valY = posY[maxIndexY] - posY[maxIndexY+1];
				gapY = posY[maxIndexY] - posY[maxIndexY-1];

				rateY = valY / gapY;
				pos = posX[maxIndexY] + (posX[maxIndexY-1] - posX[maxIndexY]) * rateY;

				val_B = (posX[maxIndexY+1]+ pos) / 2;
			}
		}

		return true;
	}
	else
	{
		val_A=(((cnt*XXi-Xi*Xi)*XXYi)-((cnt*XXXi-Xi*XXi)*XYi)+((XXXi*Xi-XXi*XXi)*Yi))/D;
		val_B=(-((cnt*XXXi-Xi*XXi)*XXYi)+((cnt*XXXXi-XXi*XXi)*XYi)-((XXXXi*Xi-XXXi*XXi)*Yi))/D;
		val_C=(((XXXi*Xi-XXi*XXi)*XXYi)-((XXXXi*Xi-XXi*XXXi)*XYi)+((XXXXi*XXi-XXXi*XXXi)*Yi))/D;
	}

	return true;
}