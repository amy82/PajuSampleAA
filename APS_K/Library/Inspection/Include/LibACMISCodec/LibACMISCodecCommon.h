#pragma once
#include <LibACMISCommon\ACMISCommon.h>

#define MAX_DECODE_FRAMES                               20

typedef enum _eFileExt
{
	FileExt_RAW,
	FileExt_PNG,
	FileExt_BMP,
	FileExt_JPG
}EFileExt;

typedef struct _tabFileInfo
{
	int nDataFormat;
	int nOutMode;
	int nSensorType;
	int nDemosaic;
	int nSplitCFA;
	int nEmbeddedSizeFront;
	int nEmbeddedSizeRear;
	int nFileExt;
	int nFileSize;
} FILE_INFO;

typedef struct _tagImageData
{
	char szFrameName[260];
	int nWidth;
	int nHeight;
	int nStride;
	int nColorType;
	int nBitDepth;
	FILE_INFO tFileInfo;
	uint8_t* pImageData;

	_tagImageData()
	{
		memset(szFrameName, 0, sizeof(szFrameName));
		nWidth = 0;
		nHeight = 0;
		nColorType = 0;
		nBitDepth = 8;
		nStride = 0;
		pImageData = nullptr;
		memset(&tFileInfo, 0, sizeof(FILE_INFO));
	}

	~_tagImageData()
	{
		if (pImageData != nullptr) { delete[]pImageData; }
		pImageData = nullptr;
	}
}IMAGE_DATA;

typedef struct _tagDecodeData
{
	char szFrameName[MAX_PATH];
	int nWidth;
	int nHeight;
	int nColorByte;
	int nBitDepth;
	FILE_INFO tFileInfo;
	uint8_t* pRGB;
	uint8_t* pPacked;	// 미리보기 지원
}DECODE_DATA;

typedef struct _tagMetadata
{
	char szDeviceName[128];
	// ...
}IMAGE_METADATA;

typedef enum
{
	ERROR_ENC_SUCCESS = 0,
	ERROR_ENC_FAIL_UNPACK,
	ERROR_ENC_INVALID_PARAM,
	ERROR_ENC_THREAD_FAIL,
	ERROR_ENC_STREAM_LEVEL_FAIL,
	ERROR_ENC_INFO_FAIL,
	ERROR_ENC_COLOR_ENCODE_FAIL,
	ERROR_ENC_FRAME_LOSSLESS_FAIL,
	ERROR_ENC_FRAME_SETTING_OPTION_FAIL,
	ERROR_ENC_ADD_BOX_FAIL,
	ERROR_ENC_FRAME_HEADER_FAIL,
	ERROR_ENC_FRAME_NAME_FAIL,
	ERROR_ENC_FRAME_BIT_DEPTEH_FAIL,
	ERROR_ENC_ADD_IMAGE_FRAME_FAIL,
	ERROR_ENC_PROCESSOUTPUT_FAIL,
	ERROR_ENC_FILE_OPEN_FAIL,
	ERROR_ENC_FILE_WRITE_FAIL,
	ERROR_ENC_FILE_CLOSE_FAIL,
}ENCODE_ERROR_CODE;

typedef enum
{
	ERROR_DEC_SUCCESS = 0,
	ERROR_DEC_FILE_LOAD_FAIL,
	ERROR_DEC_THREAD_FAIL,
	ERROR_DEC_DECODE_FAIL,
	ERROR_DEC_INVALID_INPUT,
	ERROR_DEC_INFO_FAIL,
	ERROR_DEC_ICC_SIZE_FAIL,
	ERROR_DEC_ICC_PROFILE_FAIL,
	ERROR_DEC_OUTBUFFER_FAIL,
	ERROR_DEC_INVALID_BUFFER_SIZE,
	ERROR_DEC_IMAGE_OUTBUFFER_FAIL,
	ERROR_DEC_UNKNOWN_ERROR,
	// ...
}DECODE_ERROR_CODE;

typedef struct
{
	char szFileName[260];
	ENCODE_ERROR_CODE enErrorCode;
}JXL_ENC_RSP;

typedef struct
{
	char szFileName[260];
	char szMetadata[512];
	DECODE_ERROR_CODE enErrorCode;
	DECODE_DATA tagImageData[MAX_DECODE_FRAMES]; //
}JXL_DEC_RSP;

using namespace std;
#define JXL_DLL_API extern "C" __declspec( dllexport )
#define JXL_API_CLASS __declspec( dllexport )
#ifndef _STDCALL
#define _STDCALL _stdcall
#endif

typedef VOID(*PJXLENCCALLBACK)(const JXL_ENC_RSP* pRsp);
typedef VOID(*PJXLDECCALLBACK)(const JXL_DEC_RSP* pRsp);

// Encode Function
/*====================================================================
Function name：ENC_JXL_Init
Function：Set Encode Callback
Parameter：Callback Function
Return Value：No
Explain: Encoding 결과를 전달받을 Callback Function 설정
====================================================================*/
JXL_DLL_API void ENC_JXL_Init(PJXLENCCALLBACK pFuncCallback);

/*====================================================================
Function name：ENC_JXL_Deinit
Function：Deinitialize Encode
Parameter：
Return Value：No
Explain: Encode 라이브러리 종료
====================================================================*/
JXL_DLL_API void ENC_JXL_Deinit();

/*====================================================================
Function name：ENC_JXL_SetEncEffort
Function：Set Encode effort
Parameter：Effort Value(1 ~ 9)
Return Value：TRUE or FALSE
Explain: Encoding을 위한 Effort 값 설정(기본: 7)
====================================================================*/
JXL_DLL_API BOOL ENC_JXL_SetEncEffort(int nEffort);

/*====================================================================
Function name：ENC_JXL_SetEncMetadata
Function：Set Metadata
Parameter：IMAGE_METADATA structure
Return Value：TRUE or FALSE
Explain: Metadata 설정(장비 별 기본 정보는 동일할 것으로 예상되어 한번 설정 후 재사용)
====================================================================*/
JXL_DLL_API BOOL ENC_JXL_SetEncMetadata(IMAGE_METADATA* ptagMetadata);

/*====================================================================
Function name：ENC_JXL_SAVE_IMAGE
Function：Encode Images to JXL File
Parameter：Output file name, Image data
Return Value：0: OK, 1: Error
Explain: 여러 이미지 Frame을 JXL 파일로 변환
====================================================================*/
JXL_DLL_API int ENC_JXL_SAVE_IMAGE(const char* pszFileName, std::vector<IMAGE_DATA*> vectorImageData);

/*====================================================================
Function name：ENC_JXL_SAVE_IMAGE
Function：Encode Images to JXL File
Parameter：Output file name, Image data, Image count
Return Value：0: OK, 1: Error
Explain: 여러 이미지 Frame을 JXL 파일로 변환
====================================================================*/
JXL_DLL_API int ENC_JXL_SAVE_IMAGEp(const char* pszFileName, IMAGE_DATA** pImageData, int nImageCount);

// Decode Function
/*====================================================================
Function name：DEC_JXL_Init
Function：Set Decode Callback
Parameter：Callback Function
Return Value：No
Explain: Decoding 결과를 전달받을 Callback Function 설정
====================================================================*/
JXL_DLL_API void DEC_JXL_Init(PJXLDECCALLBACK pFuncCallback);

/*====================================================================
Function name：DEC_JXL_Deinit
Function：Deinitialize Decode
Parameter：
Return Value：No
Explain: Decode 라이브러리 종료
====================================================================*/
JXL_DLL_API void DEC_JXL_Deinit();

/*====================================================================
Function name：DEC_JXL_LOAD_IMAGE
Function：Decode Image
Parameter：File name
Return Value：0: OK, 1: Error
Explain: JXL 이미지 Decoding
====================================================================*/
JXL_DLL_API int DEC_JXL_LOAD_IMAGE(const char* pszFileName);

/*====================================================================
Function name：DEC_JXL_LOAD_IMAGE_FILE
Function：Decode Image
Parameter：File name, Decoded Info
Return Value：0: OK, 1: Error
Explain: JXL 이미지 Decoding
====================================================================*/
JXL_DLL_API int DEC_JXL_LOAD_IMAGE_FILE(const char* pszFileName, JXL_DEC_RSP* pResult);
