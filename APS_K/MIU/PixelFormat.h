/**************************************************************************************************
*	Project : Eagle Eye Project (Gigabit Ethernet Camera)
*
*
*	
*	File Name : PixelFormat.h 
*	author : hkkim
**************************************************************************************************/

#ifndef __PIXEL_FORMAT_H__
#define __PIXEL_FORMAT_H__

//=================================================================================================
//	PIXEL FORMATS
//=================================================================================================
#define MIU_MONO							0x01000000
#define	MIU_BAYER							0x02000000
#define	MIU_YUV								0x03000000
#define	MIU_RGB								0x04000000

#define MIU_OCCUPY8BIT						0x00080000
#define MIU_OCCUPY10BIT						0x000A0000
#define MIU_OCCUPY12BIT						0x000C0000
#define MIU_OCCUPY16BIT						0x00100000
#define MIU_OCCUPY24BIT						0x00180000

#define MIU_MONO8							(MIU_MONO	|	MIU_OCCUPY8BIT	|	0x0001)
#define	MIU_MONO10_PACKED					(MIU_MONO	|	MIU_OCCUPY10BIT	|   0x0002)
#define MIU_MONO12_PACKED					(MIU_MONO	|	MIU_OCCUPY12BIT	|   0x0003)
#define MIU_MONO14                          (MIU_MONO   |   MIU_OCCUPY16BIT |   0x0004)

#define MIU_BAYERGR8						(MIU_BAYER	|	MIU_OCCUPY8BIT	|	0x0001)
#define MIU_BAYERRG8						(MIU_BAYER	|	MIU_OCCUPY8BIT	|	0x0002)
#define MIU_BAYERGB8						(MIU_BAYER	|	MIU_OCCUPY8BIT	|   0x0003)
#define	MIU_BAYERBG8						(MIU_BAYER	|	MIU_OCCUPY8BIT	|   0x0004)

#define MIU_BAYERGR10_PACKED				(MIU_BAYER	|	MIU_OCCUPY10BIT	|	0x0005)
#define MIU_BAYERRG10_PACKED				(MIU_BAYER	|	MIU_OCCUPY10BIT	|	0x0006)
#define MIU_BAYERGB10_PACKED				(MIU_BAYER	|	MIU_OCCUPY10BIT	|   0x0007)
#define	MIU_BAYERBG10_PACKED				(MIU_BAYER	|	MIU_OCCUPY10BIT	|   0x0008)
 	
#define MIU_BAYERGR12_PACKED				(MIU_BAYER	|	MIU_OCCUPY12BIT	|	0x0009)
#define MIU_BAYERRG12_PACKED				(MIU_BAYER	|	MIU_OCCUPY12BIT	|	0x000A)
#define MIU_BAYERGB12_PACKED				(MIU_BAYER	|	MIU_OCCUPY12BIT	|   0x000B)
#define	MIU_BAYERBG12_PACKED				(MIU_BAYER	|	MIU_OCCUPY12BIT	|   0x000C)

#define MIU_RGB565							(MIU_RGB	|	MIU_OCCUPY16BIT	|	0x0001)
#define MIU_BGR565							(MIU_RGB	|	MIU_OCCUPY16BIT	|	0x0002)
#define	MIU_RGB8_PACKED						(MIU_RGB	|	MIU_OCCUPY24BIT	|	0x0001)
#define	MIU_BGR8_PACKED						(MIU_RGB	|	MIU_OCCUPY24BIT	|	0x0002)

#define	MIU_YUV422_PACKED					(MIU_YUV	|	MIU_OCCUPY16BIT	|	0x0001)
#define	MIU_YUV422_YUYV_PACKED				(MIU_YUV	|	MIU_OCCUPY16BIT	|	0x0002)

#define MIU_YUV420_PLANAR					(MIU_YUV	|   MIU_OCCUPY12BIT |   0x0003)


#endif	// __PIXEL_FORMAT_H__