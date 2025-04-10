#pragma once

#include <LibACMISCommon\ACMISCommon.h>


#define BGGR	1//4
#define RGGB	2//1
#define GRBG	4//2
#define GBRG	3//3

#define RCCC	5
#define CRCC	6
#define CCRC	7
#define CCCR	8

class CDemosaicVNG
{
private:
		int m_nImageWidth, m_nImageHeight;
		int m_nColorOrder;

		void getLuminanceGradient(const int *src, int col, int row, double *dGradientEstimate);
		void getLuminanceGradient(const unsigned short *src, int col, int row, double *dGradientEstimate);
		void getLuminanceGradient(const BYTE *src, int col, int row, double *dGradientEstimate);
		void getChrominanceGradient(const int *src, int col, int row, double *dGradientEstimate);
		void getChrominanceGradient(const unsigned short *src, int col, int row, double *dGradientEstimate);
		void getChrominanceGradient(const BYTE *src, int col, int row, double *dGradientEstimate);
		void getColorData(const int* src, int col, int row, int nColorOrder, double* dGradientEstimate, double* dColorData);
		void getColorData(const unsigned short* src, int col, int row, int nColorOrder, double* dGradientEstimate, double* dColorData);
		void getColorData(const BYTE* src, int col, int row, int nColorOrder, double* dGradientEstimate, double* dColorData);

public:
		CDemosaicVNG();
		~CDemosaicVNG();

		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
};


