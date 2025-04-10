#pragma once

#include <LibACMISCommon\ACMISCommon.h>
#include <opencv2/opencv.hpp>

#define GBTF_MARGIN				10
#define GBTF_ROI_MARGIN			(GBTF_MARGIN - 4)

class CDemosaicGBTF
{
private:
	int m_nImageWidth, m_nImageHeight;
	int m_nColorOrder;

	void AdjustROI(RECT rtROI, int image_width, int image_height, int bayerPattern, cv::Rect &cvRect, RECT &rtMargin, int &nWidthMargin, int& nHeightMargin);
	void CalHVcolordiff(cv::Mat &src1ch, cv::Mat &HCDMap, cv::Mat &VCDMap);
	void CalHVcolordiffGrad(cv::Mat &HCDMap, cv::Mat &VCDMap, cv::Mat &HGradientMap, cv::Mat &VGradientMap);
	void CalWeightingTable(std::vector<float> &WeightTable, cv::Mat &HGradientMap, cv::Mat &VGradientMap, int nWidthMargin, int nHeightMargin);
	void GBTF_CFAInterpolation(BYTE* pBayer, BYTE* pBGR, int image_height, int image_width, RECT* pROI, int nROICount, int bayerPattern = 0, int nMaxValue = 0); // Partial Image Demosaic
	void GBTF_CFAInterpolation(unsigned short* pBayer, unsigned short* pBGR, int image_height, int image_width, RECT* pROI, int nROICount, int bayerPattern = 0, int nMaxValue = 0); // Partial Image Demosaic
	void GBTF_CFAInterpolation(int* pBayer, int* pBGR, int image_height, int image_width, RECT* pROI, int nROICount, int bayerPattern = 0, int nMaxValue = 0); // Partial Image Demosaic

	cv::Mat GBTF_G_Interpolation(cv::Mat &Bayer, cv::Mat &BMP, int nMaxValue);
	void GBTF_RB_Interpolation(cv::Mat &Dst, cv::Mat &TPdiff, int nMaxValue);

public:
	CDemosaicGBTF();
	~CDemosaicGBTF();

	cv::Mat GBTF_G_Interpolation(cv::Mat &orgBayer, cv::Mat &Bayer, cv::Mat &BMP, int nMaxValue);
	void GBTF_CFAInterpolation(cv::Mat &Bayer, cv::Mat &BMP, int bayerPattern = 0, int nMaxValue = 0, bool isGOnly = false); // Full Image Demosaic
	void G_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);
	void G_Interpolate(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat);

	void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const int *pBayer, int *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
	void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, RECT *pROI, int nROICount, int bayerPattern, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_PARALLEL_12BIT);
};
