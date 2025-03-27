// ImageProcessing.h: interface for the CImageProcessing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESSING_H__F885DCCC_610D_4DB9_9780_6888AC47404E__INCLUDED_)
#define AFX_IMAGEPROCESSING_H__F885DCCC_610D_4DB9_9780_6888AC47404E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "export.h"
#include <list>
#include <vector>

//#include <LibACMISCommon\ACMISCommon.h>
#include "../LibACMISCommon/ACMISCommon.h"

using namespace std;


namespace ACMISSoftISP
{
	typedef struct _POINTF
	{
		double x, y;
	} POINTD;

	typedef enum _EMEANTYPE
	{
		MEAN_TYPE_ALL,
		MEAN_TYPE_ROW,
		MEAN_TYPE_COLUMN
	} EMEANTYPE;

	class ACMISSOFTISP_API CStopWatch
	{
	private:
		LARGE_INTEGER freq, start, end;

	public:
		CStopWatch()
		{
			QueryPerformanceFrequency(&freq);
			start.QuadPart = 0;
			end.QuadPart = 0;
			StartTime();
		};

		inline void StartTime()
		{
			QueryPerformanceCounter(&start);
		};

		inline double CheckTime()
		{
			QueryPerformanceCounter(&end);

			return (double)(end.QuadPart - start.QuadPart) / (freq.QuadPart * 1000); // ms
			//TRACE("%.2f msec\n", elapsed);
		};
	};

	// blob 을 표현하는 run length encoding data
	class CBlobRunLengthData
	{
	public:
		BOOL visited;
		unsigned short blob_index;	// blob 번호
		unsigned short row;
		unsigned short col_start;		// run length encoding start
		unsigned short col_length;		// run length encoding end
		CBlobRunLengthData() {};
		CBlobRunLengthData(unsigned short blob_index, unsigned short row, unsigned short start, unsigned short length)
		{
			this->blob_index = blob_index;
			this->row = row;
			this->col_start = start;
			this->col_length = length;
			this->visited = FALSE;
		};
	};

	class ACMISSOFTISP_API CRectEx
	{
	public:
		int left, top, right, bottom;

		CRectEx();
		CRectEx(int l, int t, int r, int b);
		int Width();
		int Height();
		void Offset(int x, int y);
		void SetRect(int lleft, int ltop, int lright, int lbottom);
		void SetRectCentered(int centerx, int centery, int width, int height);
		BOOL EvaluateRect(int width, int height);
		void AdjustRect(int width, int height);
		POINT CenterPoint();
		// POINT가 rect 안에 드는 것인지 검사해서 TRUE 리턴
		BOOL PointInRect(int x, int y);
		void InflateRect(int x, int y);
		RECT ToRECT() const;
	};

	// blob 하나, BLOB_RUN_LENGTH_DATA 의 리스트로 표현
	class ACMISSOFTISP_API CBlobRect : public CRectEx
	{
	public:
		int Area;
		float Intensity;
		CBlobRect();

		CBlobRect(int l, int t, int r, int b);
		// 두개의 blobrect 를 하나로 합침
		CBlobRect operator + (CBlobRect &rect);

		// POINT 끼리의 거리 연산
		static inline double GetDistance(POINT A, POINT B);

		static inline float GetDistance(float x1, float y1, float x2, float y2);

		// 두 Blob Rect 간의 거리
		static inline double GetOuterDistance(CBlobRect &a, CBlobRect &b);
	};

	class ACMISSOFTISP_API CBlobList
	{
	private:
		vector <CBlobRect> *m_vecBlob;	// to avoid 'needs to have dll-interface' warning, declare pointer of vector...

	public:
		CBlobList();
		~CBlobList();

		CBlobList(const CBlobList& c)
		{
			m_vecBlob = new vector<CBlobRect>(c.m_vecBlob->size());
			std::copy(c.m_vecBlob->begin(), c.m_vecBlob->end(), m_vecBlob->begin());
		}

		CBlobList& operator=(const CBlobList& c)
		{
			m_vecBlob->resize(c.m_vecBlob->size());
			std::copy(c.m_vecBlob->begin(), c.m_vecBlob->end(), m_vecBlob->begin());
			return (*this);
		}

		void Clear();
		void Add(CBlobRect obj);
		int Size();
		CBlobRect Get(int i);
		void Remove(int index);
		CBlobList operator + (CBlobList &bloblist);

		// width, height 범위로 Blob 필터링
		void SelectBlobWidthHeight(int width_low, int width_high, int height_low, int height_high, CBlobList *);
		void SelectBlobPosition(CRectEx rect, CBlobList *vecBlob);
	};

	class CRawImageProccessor
	{
	private:
		enum COLORCHANNEL
		{
			chR = 0,
			chGr,
			chGb,
			chB
		};

		enum BAYERORDER
		{
			bayerOrderRGGB = 0,
			bayerOrderBGGR
		};

		// raw image 크기 만큼의 bayer type array 를 저장 하는 table
		// 0 : R, 1 : G, 2 : B, 3 : c
		BYTE *BayerTypeTable;
		int *IntegralImageSum[4];
		int *IntegralImageCount[4];
		int width, height;

		void NormalizeLSCTable(int blockCountX, int blockCountY);
		void SaveTextLSCRawTrainingModel(int blockCountX, int blockCountY);

	public:
		CRawImageProccessor();
		virtual ~CRawImageProccessor();

		BYTE *ColorPlane[4];

		BYTE * GetBayerTypeTable() { return BayerTypeTable; }

		// 0 : RGBC, 1 : BGGR
		void GenerateBayerTypeTable(int width, int height, BAYERORDER bayerOrder);
		void CalculateIntegralImage(BYTE *SrcImage, int width, int height);
		void DestroyBayerTypeTable();
		void CalculateMeanBlock(CRectEx rect, float mean[4]);

		// Integral Sum 과 Count 로 해당 Block 의 평균을 리턴 (width, height 도 이미 CalculateIntegralImage 에서 이미 저장 해놓음)
		void CalculateMeanBlock(int x0, int y0, int x1, int y1, float mean[4]);

		void CalculateMeanBlockDirect(BYTE *raw, int width, int height, int x0, int y0, int x1, int y1, float mean[4]);
		void SplitColorPlane(BYTE *pixel, int width, int height);
	};

	ACMISSOFTISP_API void Threshold(BYTE *srcpixel, int width, int height, CBlobList *bloblist, int min_thr, int max_thr, int MinArea, int BoundaryMarginX, int BoundaryMarginY);
	ACMISSOFTISP_API float Intensity(BYTE *pixel, int width, int height, CRectEx roi);
	ACMISSOFTISP_API void MeanImage(BYTE *image, BYTE *dest, int width, int height, int WindowSize);
	ACMISSOFTISP_API void MeanImage2Byte(SHORT *image, SHORT *dest, int width, int height, int WindowSize);
	ACMISSOFTISP_API void MeanImageFloat(BYTE *image, float *dest, int width, int height, int WindowSize);
	ACMISSOFTISP_API void MeanImageFloat2Byte(SHORT *image, float *dest, int width, int height, int WindowSize);
	ACMISSOFTISP_API void MergeAdjacentBlob(CBlobList &BlobList, CBlobList *BlobListMergedResult, int BlockCriteria, int distance);
	ACMISSOFTISP_API float CalculateRegionIntensity(BYTE *pixel, int width, int height, CRectEx roi);

	ACMISSOFTISP_API void LensShadingCorrection(BYTE *pixel, BYTE *DestPixel, int MeanBlockSize, int width, int height);
	ACMISSOFTISP_API void LensShadingCorrection(short *pixel, short *DestPixel, int MeanBlockSize, int width, int height);
	ACMISSOFTISP_API float IntensityFiltered(BYTE *pixel, int width, int height, CRectEx roi, float filter);
	ACMISSOFTISP_API float IntensityMax(float *pixel, int width, int height, RECT roi);
	ACMISSOFTISP_API void IntensityRGB(BYTE *pixel, int width, int height, CRectEx roi, float *R, float *G, float *B);

	ACMISSOFTISP_API int CalcAvgSdv(BYTE *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISP_API int CalcAvgSdv(short *pBuffer, int nImageWidth, int nImageHeight, RECT &rtROI, long double *dAvg, long double *dVar, long double *dSdv, EMEANTYPE eMeanType);
	ACMISSOFTISP_API bool LoadImageFile(TFileInfo& tFileInfo, BYTE **pBuffer);
};

#endif // !defined(AFX_IMAGEPROCESSING_H__F885DCCC_610D_4DB9_9780_6888AC47404E__INCLUDED_)
