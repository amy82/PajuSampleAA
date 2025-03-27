#pragma once

typedef enum _EOUTMODE
{
	OUTMODE_BAYER_BGGR = 1,
	OUTMODE_BAYER_RGGB,
	OUTMODE_BAYER_GBRG,
	OUTMODE_BAYER_GRBG,
	OUTMODE_BAYER_BLACKWHITE,
	OUTMODE_YUV422_YCbYCr = 1,
	OUTMODE_YUV422_YCrYCb = 2,
	OUTMODE_YUV422_CbYCrY = 3,
	OUTMODE_YUV422_CrYCbY = 4
} EOUTMODE;

typedef enum _EDATAFORMAT
{
	DATAFORMAT_YUV,
	DATAFORMAT_BAYER_8BIT,
	DATAFORMAT_BAYER_10BIT,
	DATAFORMAT_BAYER_PARALLEL_10BIT,
	DATAFORMAT_BAYER_12BIT,
	DATAFORMAT_BAYER_PARALLEL_12BIT
} EDATAFORMAT;

typedef enum _ESENSORTYPE
{
	SENSORTYPE_RGGB = 0,
	SENSORTYPE_RCCC,
	SENSORTYPE_RCCB,
	SENSORTYPE_CCCC,
	SENSORTYPE_OTHER
} ESENSORTYPE;

typedef struct _TDATASPEC
{
	EOUTMODE eOutMode;
	EDATAFORMAT eDataFormat;
	ESENSORTYPE eSensorType;
	int nBlackLevel;
} TDATASPEC;

typedef struct _TBufferInfo
{
	BYTE *pBuffer;
	int nImageWidth;
	int nImageHeight;
	bool bUsing8BitOnly;
	TDATASPEC tDataSpec;
} TBufferInfo;

typedef struct _TFileInfo
{
	char *strFileName;
	bool bIsRaw;
	int nImageWidth;
	int nImageHeight;
	bool bUsing8BitOnly;
	TDATASPEC tDataSpec;
} TFileInfo;
