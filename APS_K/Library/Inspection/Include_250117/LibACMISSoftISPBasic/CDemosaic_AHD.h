#pragma once

#include <LibACMISCommon\ACMISCommon.h>

#define AHD_MARGIN				1

class CDemosaicAHD
{
	private:
		int rows, cols;
		int colorOrder;

		int BayerSplit(BYTE* pRaw, int image_width, int image_height, BYTE* pRGB, int bayerPattern, std::vector<RECT> vROI);
		int BayerSplit2Byte(unsigned short* pRaw, int image_width, int image_height, unsigned short* pRGB, int bayerPattern, std::vector<RECT> vROI);
		int BayerSplit4Byte(int* pRaw, int image_width, int image_height, int* pRGB, int bayerPattern, std::vector<RECT> vROI);
		int InterpolateRB(BYTE* pBufferH, BYTE* pBufferV, int image_width, int image_height, int y, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int InterpolateG(BYTE* pRGB, BYTE* pBufferH, BYTE* pBufferV, int image_width, int image_height, int y, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int Interpolate2ByteRB(unsigned short* pBufferH, unsigned short* pBufferV, int image_width, int image_height, int y, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int Interpolate2ByteG(unsigned short* pRGB, unsigned short* pBufferH, unsigned short* pBufferV, int image_width, int image_height, int y, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int Interpolate4ByteRB(int* pBufferH, int* pBufferV, int image_width, int image_height, int y, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int Interpolate4ByteG(int* pRGB, int* pBufferH, int* pBufferV, int image_width, int image_height, int y, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int HomogeneityMap(BYTE* hom_buffer_h, BYTE* hom_buffer_v, BYTE* buffer_h, BYTE* buffer_v, int image_width);
		int HomogeneityMap2Byte(unsigned short* hom_buffer_h, unsigned short* hom_buffer_v, unsigned short* buffer_h, unsigned short* buffer_v, int image_width);
		int HomogeneityMap4Byte(int* hom_buffer_h, int* hom_buffer_v, int* buffer_h, int* buffer_v, int image_width);
		int Interpolate(BYTE* pRaw, BYTE* pRGB, int image_width, int image_height, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int Interpolate2Byte(unsigned short *pRaw, unsigned short *pBMP, int image_width, int image_height, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);
		int Interpolate4Byte(int *pRaw, int *pBMP, int image_width, int image_height, int bayerPattern, int nMaxValue, std::vector<RECT> vROI);

	public:
		CDemosaicAHD();
		~CDemosaicAHD();

		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
};


