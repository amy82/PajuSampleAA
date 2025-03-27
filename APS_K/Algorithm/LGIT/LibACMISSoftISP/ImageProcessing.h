#pragma once

#include "export.h"
#include "CDemosaic.h"

namespace ACMISSoftISP
{
	typedef struct _COMPLEX
	{
		double re;
		double im;
	} COMPLEX;

#define HIGH_CLIP(x, limit) (((x) > (limit)) ? (limit) : (x))
#define LOW_CLIP(x, limit)  (((x) < (limit)) ? (limit) : (x))
#define CLIP(x, l, h) HIGH_CLIP(LOW_CLIP(x, l), h)

#define CHECK_HIGH_LIMIT(x, limit) (((x) > (limit)) ? (false) : (true))
#define CHECK_LOW_LIMIT(x, limit)  (((x) < (limit)) ? (false) : (true))
#define CHECK_LIMIT(x, l, h) (CHECK_HIGH_LIMIT(x, h) && CHECK_LOW_LIMIT(x, l))

#ifndef ABS
#define ABS(x) ((x < 0) ? (-(x)) : (x))
#endif

#define	ROUND2INTEGER(X) (((X) > 0) ? ((int)((X) + 0.5)) : ((int)((X) - 0.5)))

#define MAX_POLYFIT_N 		9
#define LSC_SHIFT_FACTOR 	8
#define LSC_FACTOR 			256
#define LS_DATA_ROI_SIZE 	50
#define LSC_IMAGE_MAX_X		5500
#define LSC_IMAGE_MAX_Y		3190
#define MAX_LSC_INDEX 		(LSC_IMAGE_MAX_X * LSC_IMAGE_MAX_Y / LS_DATA_ROI_SIZE / LS_DATA_ROI_SIZE + 50)
#define ROUND2EVEN(x) 		((int)((((float)(x) / 2.0) + 0.5) * 2.0))
#define MAX_LSC_CHANNEL 	4

	struct sLensShadingCorrectionData
	{
		double ocx;
		double ocy;
		int maxIndex;
		double maxData[MAX_LSC_CHANNEL];
		double data[MAX_LSC_CHANNEL][MAX_LSC_INDEX * 3];
		//	double error[MAX_LSC_CHANNEL][MAX_LSC_INDEX * 3];
		//	double fitCurve[MAX_LSC_CHANNEL][MAX_LSC_INDEX * 3];
		//	double rsquare[MAX_LSC_CHANNEL];
		double coefficientLSCcurve[MAX_LSC_CHANNEL][MAX_POLYFIT_N + 1];
		int x[MAX_LSC_INDEX * 3];
		int y[MAX_LSC_INDEX * 3];
		double distance[MAX_LSC_INDEX * 3];
		double tableLSCcurve[MAX_LSC_CHANNEL][LSC_IMAGE_MAX_X * 2];
		int tableLSCgain[MAX_LSC_CHANNEL][LSC_IMAGE_MAX_X * 2];
		int tableLSCgainlength;
	};

	struct _TCirclePosSpec
	{
		int nPosOffsetX;
		int nPosOffsetY;
		double dRadiusRatioX;
		double dRadiusRatioY;
	};


	ACMISSOFTISP_API int xGaussianNoiseCheck(BYTE* pBMP, int nWidth, int nHeight, float fThreshold, int nChannel);
	ACMISSOFTISP_API BOOL xMedian(double* pData, int nWidth, int nHeight, int nFilterWidth, int nFilterHeight);
	ACMISSOFTISP_API void xHistogramforBMP(BYTE* pBMP, int nWidth, int nHeight, long* pHistogram, int nChannel);
	ACMISSOFTISP_API void xHistogramEqualize(BYTE* pBMP, long* pHistogram, long lNumofPx, int nChannel);
	ACMISSOFTISP_API double xRotationX(double x, double y, double angle);
	ACMISSOFTISP_API double xRotationY(double x, double y, double angle);
	ACMISSOFTISP_API void xFFT(COMPLEX *f, int logN, int numpoints, int dir);
	ACMISSOFTISP_API void xDFT(double *x, int N, double *amplitude);
	ACMISSOFTISP_API void xGetBestFit(double *x, double *y, int n, double* slope, double* offset);
	ACMISSOFTISP_API double xRsquare(double* x, double*y, int n, double slope, double offset);
	ACMISSOFTISP_API double xGetDistance(double x1, double x2, double y1, double y2);
	ACMISSOFTISP_API double xMean(BYTE* pBMP, int nWidth, int nHeight, RECT& rtROI, int nChannel, int nSelChannel); // Channel B=0, G=1, R=2

    ACMISSOFTISP_API int PolynomialFit(const BYTE *pixel, int count);
	ACMISSOFTISP_API void PolyFit(double *x, double *y, int num, double *coff, int polyN);
	ACMISSOFTISP_API void GenerateLSCtableWithPolyFitCurve(BYTE *pRaw, int width, int height, struct sLensShadingCorrectionData *dataLSC);
	ACMISSOFTISP_API void LensShadingCorrectionWithPolyFit(BYTE *pRawLSCoff, BYTE *pRawLSCon, int width, int height, struct sLensShadingCorrectionData *dataLSC);

	ACMISSOFTISP_API int xCalcImageRadius2Byte(int&ocx, int&ocy, int &radx, int &rady, const short* img, int w, int h, _TCirclePosSpec *Spec); // using Y Image Only
	ACMISSOFTISP_API int xCalcImageRadius(int&ocx, int&ocy, int &radx, int &rady, const BYTE* img, int w, int h, _TCirclePosSpec *Spec); // using Y Image Only
};
