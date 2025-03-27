/******************************************************************************
*	Project : Eagle Eye Project (Gigabit Ethernet Camera)
*
*
*	
*	File Name : ConvertColor.cpp 
*	author : hkkim
******************************************************************************/
 
#include "stdafx.h"
#include "ConvertColor.h"
#include "PixelFormat.h"
#include "EECvtColorEx.h"


/**************************************************************************************************
*   Shift10BitMode : Test 용 -> 10 bit 를 8bit로 shift
*
*   @param      pImage, [in] Image Pointer
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
void Shift10BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int i,j,k;
	unsigned int nByteWidth;
	unsigned int *piDest;

	nByteWidth = nWidth * 5 / 4 ;
	piDest = (unsigned int *)pDest;
	nWidth >>= 2;

	for(i=0; i<nHeight; i++)
	{
		for(j=0, k=0; j<nWidth; j++, k+=5)
		{
			 piDest[j] = (pImage[k+3]<<24) +  (pImage[k+2]<<16) +  (pImage[k+1]<<8) +  (pImage[k]);
		}

		piDest += nWidth;
		pImage += nByteWidth;
	}
}

/**************************************************************************************************
*   Shift10BitMode : Test 용 -> 12 bit 를 8bit로 shift  
*
*   @param      pImage, [in] Image Pointer
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
void Shift12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int	i,j,k;
	unsigned int	nByteWidth;
	unsigned short *psDest;

	nByteWidth = nWidth * 3 / 2 ;
	psDest = (unsigned short *)pDest;
	nWidth >>= 1;
	for(i=0; i<nHeight; i++)
	{
		for(j=0, k = 0; j<nWidth; j++,k+=3)
		{
			psDest[j] =  (pImage[k+1]<<8) +  (pImage[k]);			
		}
		psDest += nWidth;
		pImage += nByteWidth;
	}
}


//#define	CONVTIMECHECK

/**************************************************************************************************
*   ConvertColor : Display 하기 위해 입력 영상을 RGB로 변환 한다  
*
*   @param      iPixelFormat, [in] Pixel Format
*   @param      pSrc, [in] 변환할 Source Image (OpenCV의 IplImage*)
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      pTemp, [inout] 10bit 이상일 경우 사용하는 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
void ConvertColor(unsigned int iPixelFormat, IplImage* pSrc, IplImage* pDest, IplImage* pTemp, unsigned int nWidth, unsigned int nHeight)
{
#ifdef CONVTIMECHECK
	LARGE_INTEGER start, finish;
	LARGE_INTEGER ticksPerSec;
	double timeSec;

	if (!QueryPerformanceFrequency(&ticksPerSec))
	{ 
		return;
	} 
	QueryPerformanceCounter(&start);
#endif
	switch(iPixelFormat)
    {
		case MIU_MONO8:
			cvCvtColor(pSrc, pDest, CV_GRAY2RGB);
			break;

		case MIU_MONO10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData,nWidth, nHeight);
			cvCvtColor(pTemp, pDest, CV_GRAY2RGB);
			break;

		case MIU_MONO12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor(pTemp, pDest, CV_GRAY2RGB);
			break;

		case MIU_MONO14:

			break;

        case MIU_BAYERGR8:
            cvCvtColor( pSrc, pDest, CV_BayerGR2RGB);  // interpolation  
			break;

        case MIU_BAYERGB8:
            cvCvtColor( pSrc, pDest, CV_BayerGB2RGB);  // interpolation					
            break;

		 case MIU_BAYERRG8:
            cvCvtColor( pSrc, pDest, CV_BayerRG2RGB);  // interpolation  
			break;

        case MIU_BAYERBG8:
            cvCvtColor( pSrc, pDest, CV_BayerBG2RGB);  // interpolation					
            break;

		case MIU_BAYERRG10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			//cvCvtColor( pTemp, pDest, CV_BayerRG2RGB);  // interpolation 
			break;

		case MIU_BAYERGR10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGR2RGB);  // interpolation 
			break;

		case MIU_BAYERBG10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerBG2RGB);  // interpolation 
			break;

		case MIU_BAYERGB10_PACKED:
			Shift10BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGB2RGB);  // interpolation 
			
			break;

		case MIU_BAYERGR12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGR2RGB);  // interpolation 
			break;

		case MIU_BAYERGB12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerGB2RGB);  // interpolation 
			break;

		case MIU_BAYERRG12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerRG2RGB);  // interpolation 
			break;

		case MIU_BAYERBG12_PACKED:
			Shift12BitMode((unsigned char*)pSrc->imageData, (unsigned char*)pTemp->imageData, nWidth, nHeight);
			cvCvtColor( pTemp, pDest, CV_BayerBG2RGB);  // interpolation 
			break;

		case MIU_YUV422_YUYV_PACKED:
			ConvYUYVtoRGB((unsigned char*)pSrc->imageData, (unsigned char*)pDest->imageData, nWidth, nHeight);				
			break;

		case MIU_YUV422_PACKED:
			ConvUYVYtoRGB((unsigned char*)pSrc->imageData, (unsigned char*)pDest->imageData, nWidth, nHeight);
			break;

		case MIU_RGB565:
			cvCvtColor( pSrc, pDest, CV_BGR5652BGR);   
			break;
		
		case MIU_BGR565:
			cvCvtColor( pSrc, pDest, CV_BGR5652RGB);  
			break;

		case MIU_RGB8_PACKED:
			cvCopyImage( pSrc, pDest );
			break;
	
		case MIU_BGR8_PACKED:
			cvCvtColor( pSrc, pDest, CV_BGR2RGB);
			break;

		//Added DSI
		case MIU_YUV420_PLANAR:
//			ConvYUV420PLANARNV21toRGB((unsigned char*)pSrc->imageData, (unsigned char*)pDest->imageData, nWidth, nHeight);
			break;
       
       
        default:
            break;
    }
#ifdef CONVTIMECHECK
	QueryPerformanceCounter(&finish);
	// 경과시간 구하기 (초단위)
	timeSec = (finish.QuadPart - start.QuadPart) / (double)ticksPerSec.QuadPart;
	TRACE("Display : %.6f\n", timeSec);
#endif
}
void Shift12to16BitMode(unsigned char* p12bitRaw, unsigned char* p16bitRaw , int nWidth, int nHeight)
{

		
		int k = 0;
		int n12bitRawSize = nWidth * nHeight * 1.5;

		for(int i = 0; i < n12bitRawSize ; i+=3)
		{
			p16bitRaw[k+1] = (p12bitRaw[i] & 0xF0) >> 4 ;
			p16bitRaw[k+0] = ((p12bitRaw[i] & 0x0F) << 4 ) +  ((p12bitRaw[i + 2]  & 0x0F )) ;

			p16bitRaw[k+3] = (p12bitRaw[i + 1] & 0xF0) >> 4 ;
			p16bitRaw[k+2] = ((p12bitRaw[i + 1] & 0x0F) << 4 ) +  ((p12bitRaw[i + 2]  & 0xF0 ) >> 4) ;

			k += 4;
		}


}
void Shift16to12BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int i,j,k;
	unsigned int nScrWidth, nDestWidth;
	unsigned char *pcDest;

	nDestWidth = nWidth * 3 / 2;
	nScrWidth = nWidth * 2;

	pcDest = (unsigned char *) pDest;

	for(i=0; i<(nHeight); i++)
	{
		for(j=0, k=0; j < nDestWidth ; j+=6, k+=8)
		{
			pcDest[j+0] = ((pImage[k] & 0xF0) >> 4 ) +  ((pImage[k + 1]  & 0x0f ) << 4) ;
			pcDest[j+1] = ((pImage[k + 2] & 0xF0) >> 4 ) +  ((pImage[k + 3]  & 0x0f ) << 4) ;
			pcDest[j+2] = (pImage[k] & 0x0F) + ((pImage[k + 2]  & 0x0f ) << 4) ;

			pcDest[j+3] = ((pImage[k + 4] & 0xF0) >> 4 ) +  ((pImage[k + 5]  & 0x0f ) << 4) ;
			pcDest[j+4] = ((pImage[k + 6] & 0xF0) >> 4 ) +  ((pImage[k + 7]  & 0x0f ) << 4) ;
			pcDest[j+5] = (pImage[k + 4] & 0x0F) + ((pImage[k + 6]  & 0x0f ) << 4) ;
		}
		pcDest += nDestWidth;
		pImage += nScrWidth;
	}	
}
void CCCR_Interpolation(unsigned short* pData, int nWidth, int nHeight)
{
	int nNewValue = 0;
	int startY = 1;
	int startX = 1;
	bool m_chkDirection = false;
	/*for (int p = 1; p < nHeight - 1; p+=2)
	{
		for (int k = 1; k < nWidth - 1; k+=2)
		{
			nNewValue =  pData[(p - 1) * nWidth + (k + 0)] + pData[(p + 1) * nWidth + (k + 0)] + pData[(p + 0) * nWidth + (k - 1)]  + pData[(p + 0) * nWidth + (k - 1)] ;
			nNewValue = nNewValue / 4;
			pData[p * nWidth + k] = (unsigned short) nNewValue;
			
		}
	}*/

	
	for (int p = startY; p < nHeight - 1; p+=2)
	{
		for (int k = startX; k < nWidth - 1; k+=2)
		{
			if(m_chkDirection)  //nio = false(m_chkDirection)
			{
				int absV = abs(pData[(p - 1) * nWidth + (k + 0)] - pData[(p + 1) * nWidth + (k + 0)]);
				int absH = abs(pData[(p + 0) * nWidth + (k - 1)] - pData[(p + 0) * nWidth + (k + 1)]);
				pData[p * nWidth + k] = (absV < absH) ? (pData[(p - 1) * nWidth + (k + 0)] + pData[(p + 1) * nWidth + (k + 0)]) / 2 : (pData[(p + 0) * nWidth + (k - 1)] + pData[(p + 0) * nWidth + (k + 1)]) / 2;
			}
			else
			{
				nNewValue =  pData[(p - 1) * nWidth + (k + 0)] + pData[(p + 1) * nWidth + (k + 0)] + pData[(p + 0) * nWidth + (k - 1)]  + pData[(p + 0) * nWidth + (k + 1)] ;
				nNewValue = nNewValue / 4;
				pData[p * nWidth + k] = (unsigned short) nNewValue;

			}
			
		}
	}
	
}
void unpackRaw12(const unsigned char *src, unsigned short *dst, int rows, int cols)//void unpackRaw12(const unsigned char *src, unsigned short *dst, int rows, int cols)
{
        int nByteWidth = cols * 3 / 2;
 
        for (int i = 0; i < rows; i++)
        {
               for (int j = 0; j < cols; j += 2)
               {
                       dst[i * cols + j + 0] = (((unsigned short)src[i * nByteWidth + (j * 3 / 2) + 0] << 4) | ((unsigned short)(src[i * nByteWidth + (j * 3 / 2) + 2] & 0xF0) >> 4));
                       dst[i * cols + j + 1] = (((unsigned short)src[i * nByteWidth + (j * 3 / 2) + 1] << 4) | ((unsigned short)(src[i * nByteWidth + (j * 3 / 2) + 2] & 0x0F) >> 0));
               }
        }
}
 // src: 12-bit RAW
// dst: 12-bit Grayscale
// colorOrder: refer to header file
// rows: image-height
// cols: image-width
void DemosaicRCCC(unsigned short *src, unsigned short *dst, int colorOrder, int rows, int cols)
{
	double hDiff, vDiff, tmp;

	int offsetX, offsetY;

	int minusX, plusX;	// minusX = x - 1 or x - 2, plusX = x + 1 or x + 2
	int minusY, plusY;	// minusY = y - 1 or y - 2, plusY = y + 1 or y + 2

	memcpy_s(dst, sizeof(unsigned short) * rows * cols, src, sizeof(unsigned short) * rows * cols);

	switch (colorOrder)
	{
	default:
	case J_RCCC:
		offsetX = 0;
		offsetY = 0;
		break;
	case J_CRCC:
		offsetX = 1;
		offsetY = 0;
		break;
	case J_CCRC:
		offsetX = 0;
		offsetY = 1;
		break;
	case J_CCCR:
		offsetX = 1;
		offsetY = 1;
		break;
	}

	for (int j = offsetY; j < rows; j+=2)
	{
		for (int i = offsetX; i < cols; i+=2)
		{
			// Calculate H/V-difference
			minusX = (i - 2) < 0 ? (i + 2) : (i - 2);
			plusX = (i + 2) > (cols - 2) ? (i - 2) : (i + 2);

			minusY = (j - 2) < 0 ? (j + 2) : (j - 2);
			plusY = (j + 2) > (rows - 2) ? (j - 2) : (j + 2);

			hDiff = fabs((double)(src[minusX + j * cols] + src[plusX + j * cols]) / 2.0 - (double)src[i + j * cols]);
			vDiff = fabs((double)(src[i + minusY * cols] + src[i + plusY * cols]) / 2.0 - (double)src[i + j * cols]);

			// Calculate green color value on R/B-pixel
			minusX = (i - 1) < 0 ? (i + 1) : (i - 1);
			plusX = (i + 1) > (cols - 1) ? (i - 1) : (i + 1);

			minusY = (j - 1) < 0 ? (j + 1) : (j - 1);
			plusY = (j + 1) > (rows - 1) ? (j - 1) : (j + 1);

			if (hDiff < vDiff)
			{
				tmp = (double)(src[minusX + j * cols] + src[plusX + j * cols]) / 2.0;
				dst[i + j * cols] = (unsigned short)(tmp + 0.5);
			}
			else if (vDiff < hDiff)
			{
				tmp = (double)(src[i + minusY * cols] + src[i + plusY * cols]) / 2.0;
				dst[i + j * cols] = (unsigned short)(tmp + 0.5);
			}
			else
			{
				tmp = (double)(src[i + minusY * cols] + src[i + plusY * cols] + src[minusX + j * cols] + src[plusX + j * cols]) / 4.0;
				dst[i + j * cols] = (unsigned short)(tmp + 0.5);
			}
		}
	}
}

void DemosaicRCCC(unsigned char *src, unsigned char *dst, int colorOrder, int rows, int cols)
{
	double hDiff, vDiff, tmp;

	int offsetX, offsetY;

	int minusX, plusX;	// minusX = x - 1 or x - 2, plusX = x + 1 or x + 2
	int minusY, plusY;	// minusY = y - 1 or y - 2, plusY = y + 1 or y + 2

	memcpy_s(dst, sizeof(unsigned char) * rows * cols, src, sizeof(unsigned char) * rows * cols);

	switch (colorOrder)
	{
	default:
	case J_RCCC:
		offsetX = 0;
		offsetY = 0;
		break;
	case J_CRCC:
		offsetX = 1;
		offsetY = 0;
		break;
	case J_CCRC:
		offsetX = 0;
		offsetY = 1;
		break;
	case J_CCCR:
		offsetX = 1;
		offsetY = 1;
		break;
	}

	for (int j = offsetY; j < rows; j += 2)
	{
		for (int i = offsetX; i < cols; i += 2)
		{
			// Calculate H/V-difference
			minusX = (i - 2) < 0 ? (i + 2) : (i - 2);
			plusX = (i + 2) > (cols - 2) ? (i - 2) : (i + 2);

			minusY = (j - 2) < 0 ? (j + 2) : (j - 2);
			plusY = (j + 2) > (rows - 2) ? (j - 2) : (j + 2);

			hDiff = fabs((double)(src[minusX + j * cols] + src[plusX + j * cols]) / 2.0 - (double)src[i + j * cols]);
			vDiff = fabs((double)(src[i + minusY * cols] + src[i + plusY * cols]) / 2.0 - (double)src[i + j * cols]);

			// Calculate green color value on R/B-pixel
			minusX = (i - 1) < 0 ? (i + 1) : (i - 1);
			plusX = (i + 1) > (cols - 1) ? (i - 1) : (i + 1);

			minusY = (j - 1) < 0 ? (j + 1) : (j - 1);
			plusY = (j + 1) > (rows - 1) ? (j - 1) : (j + 1);

			if (hDiff < vDiff)
			{
				tmp = (double)(src[minusX + j * cols] + src[plusX + j * cols]) / 2.0;
				dst[i + j * cols] = (unsigned char)(tmp + 0.5);
			}
			else if (vDiff < hDiff)
			{
				tmp = (double)(src[i + minusY * cols] + src[i + plusY * cols]) / 2.0;
				dst[i + j * cols] = (unsigned char)(tmp + 0.5);
			}
			else
			{
				tmp = (double)(src[i + minusY * cols] + src[i + plusY * cols] + src[minusX + j * cols] + src[plusX + j * cols]) / 4.0;
				dst[i + j * cols] = (unsigned char)(tmp + 0.5);
			}
		}
	}
}