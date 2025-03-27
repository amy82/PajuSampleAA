#pragma once

#include <LibACMISCommon\ACMISCommon.h>

#define BL33_MARGIN				1

class CDemosaicBL33
{
	private:
		int rows, cols;
		int colorOrder;

		void InterpolateBGGR(BYTE *pRaw, BYTE *pBMP, int width, int height, std::vector<RECT> vROI);
		void InterpolateRGGB(BYTE *pRaw, BYTE *pBMP, int width, int height, std::vector<RECT> vROI);
		void InterpolateGBRG(BYTE *pRaw, BYTE *pBMP, int width, int height, std::vector<RECT> vROI);
		void InterpolateGRBG(BYTE *pRaw, BYTE *pBMP, int width, int height, std::vector<RECT> vROI);
		void InterpolateBlackWhite(BYTE *pRaw, BYTE *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate2ByteBGGR(unsigned short *pRaw, unsigned short *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate2ByteRGGB(unsigned short *pRaw, unsigned short *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate2ByteGBRG(unsigned short *pRaw, unsigned short *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate2ByteGRBG(unsigned short *pRaw, unsigned short *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate2ByteBlackWhite(unsigned short *pRaw, unsigned short *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate4ByteBGGR(int *pRaw, int *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate4ByteRGGB(int *pRaw, int *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate4ByteGBRG(int *pRaw, int *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate4ByteGRBG(int *pRaw, int *pBMP, int width, int height, std::vector<RECT> vROI);
		void Interpolate4ByteBlackWhite(int *pRaw, int *pBMP, int width, int height, std::vector<RECT> vROI);

	public:
		CDemosaicBL33();
		~CDemosaicBL33();

		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
};


