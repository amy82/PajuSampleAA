#pragma once

#include <LibACMISCommon\ACMISCommon.h>

#define GRADIENT_MARGIN				3


#define BGGR	1//4
#define RGGB	2//1
#define GRBG	4//2
#define GBRG	3//3

#define RCCC	5
#define CRCC	6
#define CCRC	7
#define CCCR	8

class CDemosaicRGGB
{
private:
	int m_nImageWidth, m_nImageHeight;
	int m_nColorOrder;

	void interpolateLuminance(const int *src, std::vector<RECT> vROI, int maxValue, int *gBuf_4B);
	void interpolateChrominance(const int *src, std::vector<RECT> vROI, int maxValue, int *gBuf_4B, int *rBuf_4B, int *bBuf_4B);
	void interpolateLuminance(const unsigned short *src, std::vector<RECT> vROI, int maxValue, unsigned short *gBuf_2B);
	void interpolateChrominance(const unsigned short *src, std::vector<RECT> vROI, int maxValue, unsigned short *gBuf_2B, unsigned short *rBuf_2B, unsigned short *bBuf_2B);
	void interpolateLuminance(const BYTE *src, std::vector<RECT> vROI, int maxValue, BYTE *gBuf);
	void interpolateChrominance(const BYTE *src, std::vector<RECT> vROI, int maxValue, BYTE *gBuf, BYTE *rBuf, BYTE *bBuf);

public:
	CDemosaicRGGB();
	~CDemosaicRGGB();

	void G_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void RB_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void RB_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void RB_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void RB_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void RB_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void RB_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);

	void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
};


