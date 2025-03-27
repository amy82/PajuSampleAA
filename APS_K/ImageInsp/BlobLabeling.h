////////////////////////////////////////////////////
//
//  클래스 : CBlobLabeling
//
//                    by 마틴(http://martinblog.net)

//! Modified by LHW, 2013/3/4,  메모리 생성/해제 함수 추가
//! Modified by LHW, 2013/4/17, 메모리 생성 부분 수정 (생성 조건 변경)

#pragma once

#include <cv.h>
#include <highgui.h>

typedef struct 
{
	BOOL	bVisitedFlag;
	CvPoint ptReturnPoint;
} Visited;

class  CBlobLabeling
{
public:
	CBlobLabeling(void);
public:
	~CBlobLabeling(void);

private:
	IplImage*	m_Image;				// 레이블링을 위한 이미지
	IplImage*	m_gray_Image;			// Gray 이미지

	int         m_iWidth_Image;
	int			m_iHeight_Image;
	int			m_iWidth_Gray_Image;
	int			m_iHeight_Gray_Image;

	short*			m_pTempBuf;			//! Memory 절약을 위해, int가 아닌 short형 버퍼로 생성
	unsigned char*  m_pTempGray;

	int			m_S_Threshold;			// 레이블링 스레스홀드 값
	int			m_L_Threshold;			// 레이블링 스레스홀드 값
	float		m_gray_Threshold;		// Gray 스레스홀드 값
	
	//! 레이블링시 방문정보
	//! 특정 PC에서의 '메모리 부족' 현상 때문에 변경 (2013/3/4)
	bool		*m_pbVisited;
	int			*m_piVisitedX;
	int			*m_piVisitedY;
	int			m_MaxDefectsCount;		// 최대 불량 수
	
public:
	//! 찾아낸 이물 (Label Blob)의 결과
	int			m_nBlobs;					// 레이블의 갯수	
	CvRect		m_recBlobs[_DEF_MAX_BLOBS];	// 각 레이블 정보 
	int			m_intBlobs[_DEF_MAX_BLOBS];	// 각 레이블 인덱스, 레이블링 된 인덱스 저장
	int			m_Area    [_DEF_MAX_BLOBS];	// 각 블랍의 영역크기
	float		m_GD      [_DEF_MAX_BLOBS];	// 각 블랍의 GD
	
public:
	//! 메모리 버퍼 생성
	int         AllocMemory(int iImageWidth, int iImageHeight);

	//! 메모리 버퍼 생성
	void        FreeMemory();

	// 레이블링 이미지 선택
	bool		SetParam(IplImage* image, IplImage* gray, int S_Threshold, int L_Threshold, float m_gray_Threshold, int maxBlob);

	// 레이블링(실행)
	void		DoLabeling();

private:
	// 레이블링(동작)
	int		 Labeling(IplImage* image, IplImage* gray, int S_Threshold, int L_Threshold, float m_gray_Threshold);

	// 포인트 초기화
	void	 InitvPoint(int nWidth, int nHeight);

	// 레이블링 결과 얻기
	void	 DetectLabelingRegion(short *DataBuf, int nWidth, int nHeight);

	// 레이블링(실제 알고리즘)
	int		_Labeling(short *DataBuf, unsigned char *GrayBuf, int nWidth, int nHeight, int S_Threshold, int L_Threshold, float Gray_Threshold);
	
	// _Labling 내부 사용 함수
	int		__NRFIndNeighbor(short *DataBuf, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY );
	int		__Area(short *DataBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel);
	float	__GrayMean(short *DataBuf, unsigned char *GrayBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nHeight, int nLevel);	
};