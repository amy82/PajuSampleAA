#pragma once

#include "../Algorithm/INSP/algo_base.h"
#include "../Library/Utility/ximg/ximage.h"		//2017101201
#include "../Library/Inspection/Include/LibACMISResolution/ACMISResolutionSFR.h"
#include "../Library/Inspection/Include/LibACMISSoftISP/SoftISP.h"




#define FINAL_SPEC_FILE_ERROR	-2
#define FINAL_IMAGE_ERROR		-1
#define FINAL_SFR_ERROR			 1
#define FINAL_DISTORTION_ERROR	 2
#define FINAL_OC_ERROR			 4

#define SAFE_DELETE(ptr) if (ptr != NULL) delete [] ptr;

class CMandoFinalSFR
{
public:
	CMandoFinalSFR(void);
	~CMandoFinalSFR(void);

public:
	//int func_check_MandoSFR_Final(IplImage* img, CString ResultPath, bool bMTFRelsultReg = true, bool bAutoMode = false, bool bUvTiming = true);		//20150116 À±½Â¿ë¼ö¼® º¯°æ »çÇ×
	int func_check_MandoSFR_Final(IplImage* img, unsigned char* imgBuf12, CString ResultPath = _T(""), bool bMTFRelsultReg = true, bool bAutoMode = false, bool bUvTiming = true);		
	int func_check_MandoSFR_Final_Quad(IplImage* img, unsigned char* imgBuf12, CString ResultPath = _T(""), bool bMTFRelsultReg = true, bool bAutoMode = false, bool bUvTiming = true);		
	int GetDistortionMarkPoint(IplImage* img, vector <POINTFLOAT>& pos, CMapData spec_);
	
	int LoadBMPfile(char *filename,unsigned char *data,int *width,int *height);
	BOOL SaveImageToBmp(char *path, unsigned char* bmp_buffer, __int16 width, __int16 height);
	void MarkRectangleOnBMPimage(unsigned char *data,int w,int h,int cx,int cy,int side_length_x,int side_length_y,int R,int G,int B);
	void ImageFlip(unsigned char* source,unsigned char* target,int width,int height);



	unsigned char* m_imgBuf8;
	void RawToBmpQuater(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height,int ch);
	void PRI_12BitToRaw8 (unsigned char *p12Bit, unsigned char *pRawBit8, int w, int h);
};
