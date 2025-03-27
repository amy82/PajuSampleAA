#include "StdAfx.h"
#include "MandoFinalSFR.h"
#include "PcsUtil.h"		// 20140912 추가

CMandoFinalSFR::CMandoFinalSFR(void)
{
	m_imgBuf8 = NULL;
}


CMandoFinalSFR::~CMandoFinalSFR(void)
{
	SAFE_DELETE(m_imgBuf8);
}


//using namespace cv;
int CMandoFinalSFR::GetDistortionMarkPoint(IplImage* img, vector <POINTFLOAT>& pos, CMapData spec_)
{
	int find_num = 0;
	pos.clear();

	IplImage* YCbCr  = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	IplImage* Y		 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* Cb	 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* Cr	 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		
	cvCvtColor(img, YCbCr, CV_RGB2YCrCb);
	//cvCvtPixToPlane( YCbCr, Y, Cb, Cr, NULL);  
	cvSplit(YCbCr, Y, Cb, Cr, NULL);

	int w = cvGetSize(img).width;
	int h = cvGetSize(img).height;
	
	// spec.ini 로 뺄것
	int masksize_x,masksize_y, corner_mask;		
	double area_max, area_min;
		
	masksize_x  = spec_["DISTORTION_EXTRACT.masksize_x.i"].i;
	masksize_y  = spec_["DISTORTION_EXTRACT.masksize_y.i"].i;
	corner_mask = spec_["DISTORTION_EXTRACT.corner_mask.i"].i;
	area_max	= spec_["DISTORTION_EXTRACT.area_max.d"].d;
	area_min	= spec_["DISTORTION_EXTRACT.area_min.d"].d;
	
	// OTSU BIN & Morphology
	cvThreshold(Y, Y, 5, 255, CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
	cvErode(Y, Y, NULL, 2);
	cvDilate(Y, Y, NULL, 2);

	// center masking
	cvSetImageROI(Y, cvRect(w/2-masksize_x, h/2-masksize_y, 2*masksize_x, 2*masksize_y));
	cvSet(Y, cvScalar(0, 0, 0)); cvResetImageROI(Y);

	// corner masking
	cvSetImageROI(Y, cvRect(		    0, 0,			  corner_mask, corner_mask));	cvSet(Y, cvScalar(0, 0, 0)); cvResetImageROI(Y);
	cvSetImageROI(Y, cvRect(w-corner_mask, 0,			  corner_mask, corner_mask));	cvSet(Y, cvScalar(0, 0, 0)); cvResetImageROI(Y);
	cvSetImageROI(Y, cvRect(			0, h-corner_mask, corner_mask, corner_mask));	cvSet(Y, cvScalar(0, 0, 0)); cvResetImageROI(Y);
	cvSetImageROI(Y, cvRect(w-corner_mask, h-corner_mask, corner_mask, corner_mask));	cvSet(Y, cvScalar(0, 0, 0)); cvResetImageROI(Y);
		
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = NULL;
	
	cvFindContours(Y, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		
	double area;
	if (contours) 
	{
		while( contours )   // loop over all the contours
		{
			area = cvContourArea( contours, CV_WHOLE_SEQ );
			if (area > area_min && area < area_max) 
			{
				RotatedRect minRect = cvMinAreaRect2(contours, NULL);
				POINTFLOAT p;
				p.x = minRect.center.x; p.y = minRect.center.y;
				pos.push_back(p);
			}
			contours = contours->h_next;    // jump to the next contour
		}
	}

	cvReleaseMemStorage(&storage);

	cvReleaseImage(&YCbCr);  YCbCr  = NULL;
	cvReleaseImage(&Y);		 Y		= NULL;
	cvReleaseImage(&Cb);	 Cb		= NULL;
	cvReleaseImage(&Cr);	 Cr		= NULL;
	
	return pos.size();
}



//////////////////////////////////////////////////////////
//알고리즘 검증용 BMP이미지 관련 예제 함수
//////////////////////////////////////////////////////////

int CMandoFinalSFR::LoadBMPfile(char *filename,unsigned char *data,int *width,int *height)
{
	FILE *fp;
	BITMAPFILEHEADER bmpHeader; // Header for Bitmap file
	BITMAPINFO		 bmpInfo;

	if((fp=fopen(filename,"rb"))==NULL) return 0;
	fread((void*)&bmpHeader	 ,sizeof(unsigned char),sizeof(BITMAPFILEHEADER)/sizeof(unsigned char),fp);
	fread((void*)&bmpInfo	 ,sizeof(unsigned char),sizeof(BITMAPINFO)/sizeof(unsigned char),fp);
	
	*width=bmpInfo.bmiHeader.biWidth;
	*height=bmpInfo.bmiHeader.biHeight;
//	printf("%d %d\n",(*width),(*height));

	fseek(fp,0,SEEK_END);
	fseek(fp,ftell(fp)-(*width)*(*height)*3,SEEK_SET);
	fread((void*)data,sizeof(unsigned char),(*width)*(*height)*3,fp);

	if(fp)		fclose(fp);
	
	return 1;
}

BOOL CMandoFinalSFR::SaveImageToBmp(char *path, unsigned char* bmp_buffer, __int16 width, __int16 height)
{
	int		OffBits;
	HFILE	bmpFile;
	BITMAPFILEHEADER bmpHeader; //Header for Bitmap file
	BITMAPINFO		 bmpInfo;
	
	OffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	DWORD dwSizeImage = width*height*3;
	
	bmpHeader.bfType = ( (WORD)('M'<<8)|'B' );
	bmpHeader.bfSize = OffBits + dwSizeImage;
	bmpHeader.bfReserved1 = 0;
	bmpHeader.bfReserved2 = 0;
	bmpHeader.bfOffBits = OffBits;
	
	bmpInfo.bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth           = width;
    bmpInfo.bmiHeader.biHeight          = height;
    bmpInfo.bmiHeader.biPlanes          = 1;
    bmpInfo.bmiHeader.biBitCount        = 24;
    bmpInfo.bmiHeader.biCompression     = BI_RGB;
    bmpInfo.bmiHeader.biSizeImage       = 0; 
    bmpInfo.bmiHeader.biXPelsPerMeter   = 0;
    bmpInfo.bmiHeader.biYPelsPerMeter   = 0;
    bmpInfo.bmiHeader.biClrUsed         = 0;
    bmpInfo.bmiHeader.biClrImportant    = 0;
	
	bmpFile = _lcreat( path, 0 );
	if( bmpFile < 0 ) return FALSE;
	
	UINT len;
	len = _lwrite( bmpFile, (LPSTR)&bmpHeader, sizeof(BITMAPFILEHEADER) );
	len = _lwrite( bmpFile, (LPSTR)&bmpInfo, sizeof(BITMAPINFOHEADER) );
	len = _lwrite( bmpFile, (LPSTR)bmp_buffer, bmpHeader.bfSize - sizeof(bmpHeader) - sizeof(bmpInfo)+4 );  //+4 is for exact filesize
	_lclose( bmpFile );
	
	return TRUE;	
}



void CMandoFinalSFR::MarkRectangleOnBMPimage(unsigned char *data,int w,int h,int cx,int cy,int side_length_x,int side_length_y,int R,int G,int B)
{//이미지에 이물 위치 그리기
	int x,y;
	int l,t,r,b;
	l=cx-side_length_x/2;if(l<0) l=0;
	r=cx+side_length_x/2;if(r>w-1) r=w-1;
	t=cy-side_length_y/2;if(t<0) t=0;
	b=cy+side_length_y/2;if(b>h-1) b=h-1;

	for(y=t;y<b;y++)
	{
		x=l;
		data[(h-y-1)*w*3+(x)*3+0]=B;
		data[(h-y-1)*w*3+(x)*3+1]=G;
		data[(h-y-1)*w*3+(x)*3+2]=R;
		x=r;
		data[(h-y-1)*w*3+(x)*3+0]=B;
		data[(h-y-1)*w*3+(x)*3+1]=G;
		data[(h-y-1)*w*3+(x)*3+2]=R;

	}


	for(x=l;x<r;x++)
	{
		y=t;
		data[(h-y-1)*w*3+(x)*3+0]=B;
		data[(h-y-1)*w*3+(x)*3+1]=G;
		data[(h-y-1)*w*3+(x)*3+2]=R;
		y=b;
		data[(h-y-1)*w*3+(x)*3+0]=B;
		data[(h-y-1)*w*3+(x)*3+1]=G;
		data[(h-y-1)*w*3+(x)*3+2]=R;
	}
}

void CMandoFinalSFR::ImageFlip(unsigned char* source,unsigned char* target,int width,int height)
{
	int x,y;
	for(y=0;y<height;y++)
	{
		for(x=0;x<width*3;x++)
		{
			target[y*width*3+x]=source[(height-y-1)*width*3+x];
		}
	}
}

void CMandoFinalSFR::PRI_12BitToRaw8 ( unsigned char *p12Bit, unsigned char *pRawBit8, int w, int h )	// 1280 x 964 12bit -> 1280 x 960 8bit
{ 
	int x, y, m_iWidth = w, m_iHeight = h;
		
	for (y=0; y<m_iHeight; y++)
	{		 
		for (x=0; x<m_iWidth/2; x=x++)
		{			
			pRawBit8[y*m_iWidth + x*2]	 = (p12Bit[(y+2)*m_iWidth*2 + 4*x+0]);		
			pRawBit8[y*m_iWidth + x*2+1] = (p12Bit[(y+2)*m_iWidth*2 + 4*x+2]);	
		}
	}
}

void CMandoFinalSFR::RawToBmpQuater(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height,int ch)
{ 
	int i, j, sx=0, sy=0;
	
	if		(ch==0)		sx = 0, sy = 0;
	else if (ch==1)		sx = 1, sy = 0;
	else if (ch==2)		sx = 0, sy = 1;
	else if (ch==3)		sx = 1, sy = 1;

	for (j=sy; j<image_height; j+=2)
	{
		for (i=sx; i<image_width; i+=2)
		{
			*pBMP++ = pRaw8[(image_height-j-1)*image_width+i];
			*pBMP++ = pRaw8[(image_height-j-1)*image_width+i];
			*pBMP++ = pRaw8[(image_height-j-1)*image_width+i];
		}
	}
}
