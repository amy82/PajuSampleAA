// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RAWTOBMP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RAWTOBMP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef RAWTOBMP_EXPORTS
#define RAWTOBMP_API __declspec(dllexport)
#else
#define RAWTOBMP_API __declspec(dllimport)
#endif

RAWTOBMP_API void RawToBmp(unsigned char *pRaw8, unsigned char *pBMP, int image_width, int image_height, int bayer_format);