#pragma once

#include <LibACMISCommon\ACMISCommon.h>


class CDemosaicRCCB
{
	private:
		int rows, cols;
		int colorOrder;

		void InterpolationRBCC(BYTE* pRaw, BYTE* pData, int nWidth, int nHeight, EOUTMODE eOutMode, int nMaxValue);
		void Interpolation2ByteRBCC(unsigned short* pRaw, unsigned short* pData, int nWidth, int nHeight, EOUTMODE eOutMode, int nMaxValue);
		void Interpolation4ByteRBCC(int* pRaw, int* pData, int nWidth, int nHeight, EOUTMODE eOutMode, int nMaxValue);
		void InterpolationRBCC(BYTE* pRaw, BYTE* pData, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode, int nMaxValue);
		void Interpolation2ByteRBCC(unsigned short* pRaw, unsigned short* pData, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode, int nMaxValue);
		void Interpolation4ByteRBCC(int* pRaw, int* pData, int nWidth, int nHeight, RECT *pROI, int nROICount, EOUTMODE eOutMode, int nMaxValue);
		void DemosaicRCCC(BYTE *src, BYTE *dst, EOUTMODE eOutMode, int rows, int cols, int nMaxValue);
		void DemosaicRCCC(unsigned short *src, unsigned short *dst, EOUTMODE eOutMode, int rows, int cols, int nMaxValue);
		void DemosaicRCCC(int *src, int *dst, EOUTMODE eOutMode, int rows, int cols, int nMaxValue);
		void DemosaicRCCC(BYTE *src, BYTE *dst, EOUTMODE eOutMode, int rows, int cols, RECT *pROI, int nROICount, int nMaxValue);
		void DemosaicRCCC(unsigned short *src, unsigned short *dst, EOUTMODE eOutMode, int rows, int cols, RECT *pROI, int nROICount, int nMaxValue);
		void DemosaicRCCC(int *src, int *dst, EOUTMODE eOutMode, int rows, int cols, RECT *pROI, int nROICount, int nMaxValue);

	public:
		CDemosaicRCCB();
		~CDemosaicRCCB();

		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2Y(const int *pBayer, int *pY, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2Y(const unsigned short *pBayer, unsigned short *pY, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2Y(const BYTE *pBayer, BYTE *pY, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2Y(const int *pBayer, int *pY, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2Y(const unsigned short *pBayer, unsigned short *pY, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
		void Bayer2Y(const BYTE *pBayer, BYTE *pY, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, ESENSORTYPE eSensorType = SENSORTYPE_RCCB);
};


