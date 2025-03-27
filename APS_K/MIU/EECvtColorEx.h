/******************************************************************************
*	Project : Eagle Eye Project (Gigabit Ethernet Camera)
*
*
*	
*	File Name : EECvtColorEx.h 
*	author : hkkim
******************************************************************************/
#ifndef __EECVT_COLOR_EX_H__
#define __EECVT_COLOR_EX_H__

#ifdef _USRDLL
#define DLLFunction  __declspec(dllexport)
#else
#define DLLFunction  __declspec(dllimport)
#endif


#ifdef _cplusplus
extern "C" {
#endif

/**************************************************************************************************
*   ConvYUYVtoRGB : YUYV 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYUYVtoRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvUYVYtoRGB : YUYV 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvUYVYtoRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYVYUtoRGB : YVYU 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYVYUtoRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvVYUYtoRGB : VYUY 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvVYUYtoRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYUV420PLANARtoRGB : YUV420 Planar 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYUV420PLANARtoRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYUV420PLANARNV21toRGB : YUV420 Planar NV21 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
//DLLFunction void __stdcall  ConvYUV420PLANARNV21toRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);

/**************************************************************************************************
*   ConvRGBtoYUV420Planar : RGB 영상을 YUV420 Planar 로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvRGBtoYUV420Planar(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYUV422PLANARtoRGB : YUV422 Planar 영상을 RGB로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYUV422PLANARtoRGB(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);

/**************************************************************************************************
*   ConvRGBtoYUV422Planar : RGB 영상을 YUV422 Planar 로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvRGBtoYUV422Planar(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYUYVtoY : YUYV 영상을 Y로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYUYVtoY(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYUYVtoYYU420_NV21 : YUYV 영상을 YUV420 NV21로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYUYVtoYYU420_NV21(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvYUYVtoYYU420_NV12 : YUYV 영상을 YUV420 NV12로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvYUYVtoYYU420_NV12(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);

/**************************************************************************************************
*   ConvUYVYtoY : YUYV 영상을 Y로 변환 한다  
*
*   @param      pSrc, [in] 변환할 Source Image 
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvUYVYtoY(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


/**************************************************************************************************
*   ConvUYVYtoRGB_601 : UYVY 영상을 RGB로 변환 한다  - 601 Format
*
*   @param      pSrc, [in] 변환할 Source Image (OpenCV의 IplImage*)
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvUYVYtoRGB_601(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);

/**************************************************************************************************
*   ConvUYVYtoRGB_709 : UYVY 영상을 RGB로 변환 한다  - 709 Format
*
*   @param      pSrc, [in] 변환할 Source Image (OpenCV의 IplImage*)
*   @param      pDest, [inout] 변환 결과를 넘겨줄 Destination Image   
*   @param      nWidth, [in] Image Width
*	@param		nHeight, [in] Image Height  
*
*   @return     Error Value
**************************************************************************************************/
DLLFunction void __stdcall  ConvUYVYtoRGB_709(unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);


#ifdef _cplusplus
}
#endif
#endif		//__EECVT_COLOR_EX_H__