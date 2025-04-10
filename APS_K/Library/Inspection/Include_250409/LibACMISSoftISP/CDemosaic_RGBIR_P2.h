#pragma once

#include <LibACMISCommon\ACMISCommon.h>
#include <opencv2/opencv.hpp>

#define RGBIR_P2_MARGIN				26	// G(15) + X(11)

class CDemosaicRGBIR_P2
{
private:
	int m_nImageWidth, m_nImageHeight;
	int m_nColorOrder;
	double m_dSigma;
	EDATAFORMAT m_eDataFormat;
	EDEMOSAICMETHOD m_eDemosaicMethod;

	void BayerSplit(void *Bayer, int bayerPattern, void *Dst);
	void AdjustBayerPattern(int bayerPattern, RECT rtROI, int &AdjustedBayerPattern);
	void GetGreenMask(int image_width, int image_height, int bayerPattern, cv::Mat &maskGr, cv::Mat &maskGb, cv::Mat &maskGirr, cv::Mat &maskGirb);
	cv::Mat RGBIR_P2_G_Interpolation(cv::Mat &Src, std::vector<cv::Mat> &bgr, std::vector<cv::Mat> &mask, int bayerPattern, double sigma);
	cv::Mat RGBIR_P2_X_Interpolation(cv::Mat &X, cv::Mat &G, cv::Mat &maskX);
	void RGBIR_P2_Interpolation(cv::Mat &Bayer, cv::Mat &RGBI, RECT* pROI, int nROICount, int bayerPattern = 0, int nMaxValue = 0, double sigma = 1.0, bool bIR = false, bool bIROnly = false); // Partial Image Demosaic

public:
	CDemosaicRGBIR_P2();
	~CDemosaicRGBIR_P2();

	void G_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void G_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void G_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void G_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void G_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void G_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void RB_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void RB_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void RB_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void RB_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void RB_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void RB_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void IR_Interpolate(const int *pBayer, int *pBGRI, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void IR_Interpolate(const unsigned short *pBayer, unsigned short *pBGRI, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void IR_Interpolate(const BYTE *pBayer, BYTE *pBGRI, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void IR_Interpolate(const int *pBayer, int *pBGRI, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void IR_Interpolate(const unsigned short *pBayer, unsigned short *pBGRI, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void IR_Interpolate(const BYTE *pBayer, BYTE *pBGRI, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);

	void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);

	void Bayer2BGRI(const int *pBayer, int *pBGRI, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGRI(const unsigned short *pBayer, unsigned short *pBGRI, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGRI(const BYTE *pBayer, BYTE *pBGRI, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGRI(const int *pBayer, int *pBGRI, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGRI(const unsigned short *pBayer, unsigned short *pBGRI, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
	void Bayer2BGRI(const BYTE *pBayer, BYTE *pBGRI, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT, EDEMOSAICMETHOD eDemosaicMethod = DEMOSAICMETHOD_GRADIENT_RESIDUAL, double sigma = 1.0);
};
