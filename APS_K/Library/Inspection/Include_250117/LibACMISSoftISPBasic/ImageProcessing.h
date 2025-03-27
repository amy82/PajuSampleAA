#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>


namespace ACMISSoftISP
{
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

//#define USE_ELLIPSE_ANGLE
#ifdef USE_ELLIPSE_ANGLE
#define	CIRCLE_POSX(OCX, OCY, PosX, PosY, Angle)  ((double)(OCX - PosX) * cos(Angle * M_PI / 180.0) + (double)(OCY - PosY) * sin(Angle * M_PI / 180.0))
#define	CIRCLE_POSY(OCX, OCY, PosX, PosY, Angle)  (-(double)(OCX - PosX) * sin(Angle * M_PI / 180.0) + (double)(OCY - PosY) * cos(Angle * M_PI / 180.0))
#else
#define	CIRCLE_POSX(OCX, OCY, PosX, PosY, Angle)  ((double)(OCX - PosX))
#define	CIRCLE_POSY(OCX, OCY, PosX, PosY, Angle)  ((double)(OCY - PosY))
#endif

//#define POSITION(x, roi)	(((x + 1) * roi - roi / 2) * 2 - 1)
#define POSITION_CENTER(x, bsize, size0, ch)	((x == 0 ? size0 / 2 : ((x - 1) * bsize + size0 + bsize / 2)) * ch)
#define POSITION_START(x, bsize, size0, ch)		((x == 0 ? 0 : ((x - 1) * bsize + size0)) * ch)
#define POSITION_END(x, bsize, size0, ch)		((x == 0 ? size0 : (x * bsize + size0)) * ch - 1)

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


	ACMISSOFTISPBASIC_API int xGaussianNoiseCheck(BYTE* pBMP, int nWidth, int nHeight, float fThreshold, int nChannel);
	ACMISSOFTISPBASIC_API bool xGetGaussian(int nWidth, int nHeight, double dSigma, double** dKernel);
	ACMISSOFTISPBASIC_API BOOL xMedian(double* pData, int nWidth, int nHeight, int nFilterWidth, int nFilterHeight);
	ACMISSOFTISPBASIC_API void xHistogramforBMP(BYTE* pBMP, int nWidth, int nHeight, long* pHistogram, int nChannel);
	ACMISSOFTISPBASIC_API void xHistogramEqualize(BYTE* pBMP, long* pHistogram, long lNumofPx, int nChannel);
	ACMISSOFTISPBASIC_API double xRotationX(double x, double y, double angle);
	ACMISSOFTISPBASIC_API double xRotationY(double x, double y, double angle);
	ACMISSOFTISPBASIC_API void xFFT(COMPLEX *f, int logN, int numpoints, int dir);
	ACMISSOFTISPBASIC_API void xDFT(double *x, int N, double *amplitude);
	ACMISSOFTISPBASIC_API void xGetBestFit(double *x, double *y, int n, double* slope, double* offset);
	ACMISSOFTISPBASIC_API double xRsquare(double* x, double*y, int n, double slope, double offset);
	ACMISSOFTISPBASIC_API double xGetDistance(double x1, double x2, double y1, double y2);
	ACMISSOFTISPBASIC_API double xMean(BYTE* pBMP, int nWidth, int nHeight, RECT& rtROI, int nChannel, int nSelChannel); // Channel B=0, G=1, R=2
	ACMISSOFTISPBASIC_API double xMean(unsigned short* pBMP, int nWidth, int nHeight, RECT& rtROI, int nChannel, int nSelChannel);

	ACMISSOFTISPBASIC_API void GetMeanFromBayerDouble(const BYTE* pRaw, int width, int height, int l, int t, int w, int h, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromBayerDouble(const BYTE* pRaw, int width, int height, RECT rtROI, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromBayerDouble(const int* pRaw, int width, int height, int l, int t, int w, int h, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromBayerDouble(const int* pRaw, int width, int height, RECT rtROI, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromBMPdouble(const int* pData, int width, int height, int leftROI, int topROI, int rightROI, int bottomROI, double* mean, int color);
	ACMISSOFTISPBASIC_API void GetMeanFromBMPdouble(const int* pData, int width, int height, RECT rtROI, double* mean, int color);
	ACMISSOFTISPBASIC_API void GetMeanFromYdouble(const BYTE* pData, int width, int height, int leftROI, int topROI, int rightROI, int bottomROI, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromYdouble(const BYTE* pData, int width, int height, RECT rtROI, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromYdouble(const int* pData, int width, int height, int leftROI, int topROI, int rightROI, int bottomROI, double* mean);
	ACMISSOFTISPBASIC_API void GetMeanFromYdouble(const int* pData, int width, int height, RECT rtROI, double* mean);

    ACMISSOFTISPBASIC_API int PolynomialFit(const BYTE *pixel, int count);
	ACMISSOFTISPBASIC_API int PolynomialFit(const unsigned short *pixel, int count);
	ACMISSOFTISPBASIC_API int PolynomialFit(const int *pixel, int count);
	ACMISSOFTISPBASIC_API bool PolynomialFit(const double *x, const double *y, const int count, const int order, double *coeffs);
	ACMISSOFTISPBASIC_API bool PolynomialFit(const std::vector<double> &x, const std::vector<double> &y, const int order, std::vector<double> &coeffs);
	ACMISSOFTISPBASIC_API void PolyFit(double *x, double *y, int num, double *coff, int polyN);
	ACMISSOFTISPBASIC_API void GenerateLSCtableWithPolyFitCurve(BYTE *pRaw, int width, int height, struct sLensShadingCorrectionData *dataLSC);
	ACMISSOFTISPBASIC_API void LensShadingCorrectionWithPolyFit(BYTE *pRawLSCoff, BYTE *pRawLSCon, int width, int height, struct sLensShadingCorrectionData *dataLSC);

	ACMISSOFTISPBASIC_API void SeparateCFA(double* pBuffer, int nImageWidth, int nImageHeight, double* pChannelLT, double* pChannelRT, double* pChannelLB, double* pChannelRB);
	ACMISSOFTISPBASIC_API void SeparateCFA(int* pBuffer, int nImageWidth, int nImageHeight, int* pChannelLT, int* pChannelRT, int* pChannelLB, int* pChannelRB);
	ACMISSOFTISPBASIC_API void SeparateCFA(unsigned short* pBuffer, int nImageWidth, int nImageHeight, unsigned short* pChannelLT, unsigned short* pChannelRT, unsigned short* pChannelLB, unsigned short* pChannelRB);
	ACMISSOFTISPBASIC_API void SeparateCFA(BYTE* pBuffer, int nImageWidth, int nImageHeight, BYTE* pChannelLT, BYTE* pChannelRT, BYTE* pChannelLB, BYTE* pChannelRB);
	ACMISSOFTISPBASIC_API void MergeCFA(double* pChannelLT, double* pChannelRT, double* pChannelLB, double* pChannelRB, int nImageWidth, int nImageHeight, double* pBuffer);
};
