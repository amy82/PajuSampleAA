#pragma once

#include <LibACMISCommon\ACMISCommon.h>
#include <opencv2/opencv.hpp>

#define BLLC_MARGIN				2

class CDemosaicBLLC
{
	private:
		int m_nImageWidth;
		int m_nImageHeight;
		int m_nColorOrder;
		float m_fAlpha, m_fBeta, m_fGamma;

		void LaplacianCorrection(std::vector<cv::Mat> &bgr, int image_height, int image_width, int bayerPattern, float alpha, float beta, float gamma, std::vector<cv::Mat> &laplacian);
		void Interpolate(BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, std::vector<RECT> vROI, int nMaxValue);
		void Interpolate2Byte(unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, std::vector<RECT> vROI, int nMaxValue);
		void Interpolate4Byte(int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, std::vector<RECT> vROI, int nMaxValue);

	public:
		CDemosaicBLLC();
		~CDemosaicBLLC();

		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, double alpha = 1.0 / 2.0, double beta = 5.0 / 8.0, double gamma = 3.0 / 4.0);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, double alpha = 1.0 / 2.0, double beta = 5.0 / 8.0, double gamma = 3.0 / 4.0);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, double alpha = 1.0 / 2.0, double beta = 5.0 / 8.0, double gamma = 3.0 / 4.0);
		void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, double alpha = 1.0 / 2.0, double beta = 5.0 / 8.0, double gamma = 3.0 / 4.0);
		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, double alpha = 1.0 / 2.0, double beta = 5.0 / 8.0, double gamma = 3.0 / 4.0);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, double alpha = 1.0 / 2.0, double beta = 5.0 / 8.0, double gamma = 3.0 / 4.0);
};


