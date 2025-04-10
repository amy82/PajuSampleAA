#pragma once

#include <ppl.h>
#include <LibACMISImage\ACMISImageDef.h>

typedef enum _DEFECT_PIXEL_OFFSET_FLAG
{
	/* Offset */
	OFFSET_TYPE_HOT,
	OFFSET_TYPE_DARK,
	OFFSET_TYPE_BRIGHT,
	OFFSET_TYPE_VERY_HOT,
	OFFSET_TYPE_VERY_DARK,
	OFFSET_TYPE_VERY_BRIGHT,
	OFFSET_HOT,
	OFFSET_DARK,
	OFFSET_BRIGHT,
	OFFSET_VERY_HOT,
	OFFSET_VERY_DARK,
	OFFSET_VERY_BRIGHT,

	OFFSET_FLAG_MAX_COUNT
} DEFECT_PIXEL_OFFSET_FLAG;

#define DEFECT_PIXEL_SPEC_FLAG_VERSION_MAJOR		1
#define DEFECT_PIXEL_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_DEFECT_PIXEL
{
	DEFECT_PIXEL_DIFF_TYPE,
	DEFECT_PIXEL_DEFECT_TYPE,
	DEFECT_PIXEL_BLOCK_SIZE,
	DEFECT_PIXEL_DEFECT_RATIO,
	DEFECT_PIXEL_MAX_SINGLE_DEFECT_NUM,
	DEFECT_PIXEL_DEFECT_IN_CLUSTER,
	DEFECT_PIXEL_ENABLE_CHANNEL,

	DEFECT_PIXEL_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_DEFECT_PIXEL;

typedef struct _TDarkDefectPixel
{
	int nType;
	int nDefectType;
	int nBlockSize;
	double dDefectRatio;
	int nMaxSingleDefectNum;
	int nPixelOrder;
	int nDefectInCluster;
	int bEnableDetectGrGbCluster;
	int nEnableChannel;
} TDefectPixel;

#define HOT_DEFECT_PIXEL_SPEC_FLAG_VERSION_MAJOR		1
#define HOT_DEFECT_PIXEL_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_HOT_DEFECT_PIXEL
{
	HOT_DEFECT_PIXEL_DIFF_TYPE,
	HOT_DEFECT_PIXEL_DEFECT_TYPE,
	HOT_DEFECT_PIXEL_ALGORITHM_TYPE,
	HOT_DEFECT_PIXEL_BLOCK_SIZE,
	HOT_DEFECT_PIXEL_THRESHOLD1,
	HOT_DEFECT_PIXEL_THRESHOLD2,
	HOT_DEFECT_PIXEL_LOW_LIGHT_THRESHOLD,
	HOT_DEFECT_PIXEL_MASK,

	HOT_DEFECT_PIXEL_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_HOT_DEFECT_PIXEL;

typedef struct _THotDefectPixel
{
	int nType;
	int nAlgorithmType;
	int nDefectType;
	double dThreshold1;	// 200
	double dThreshold2;	// 1300
	int nBlockSize;
	double dLowLightTheshold;
	BYTE *mask;
} THotDefectPixel;

#define VERY_DEFECT_PIXEL_SPEC_FLAG_VERSION_MAJOR		1
#define VERY_DEFECT_PIXEL_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_VERY_DEFECT_PIXEL
{
	VERY_DEFECT_PIXEL_DIFF_TYPE,
	VERY_DEFECT_PIXEL_DEFECT_TYPE,
	VERY_DEFECT_PIXEL_BLOCK_SIZE,
	VERY_DEFECT_PIXEL_NORMAL_DEFECT_RATIO,
	VERY_DEFECT_PIXEL_VERY_DEFECT_RATIO,
	VERY_DEFECT_PIXEL_MAX_NORMAL_DEFECT_NUM,
	VERY_DEFECT_PIXEL_MAX_VERY_DEFECT_NUM,
	VERY_DEFECT_PIXEL_DEFECT_IN_CLUSTER,
	VERY_DEFECT_PIXEL_ENABLE_CHANNEL,

	VERY_DEFECT_PIXEL_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_VERY_DEFECT_PIXEL;

typedef struct _TVeryDefectPixel
{
	int nType;
	int nDefectType;
	int nBlockSize;
	double dNormalDefectRatio;
	double dVeryDefectRatio;
	int nMaxNormalDefectNum;
	int nMaxVeryDefectNum;
	int nDefectInCluster;
	int nEnableChannel;
} TVeryDefectPixel;

typedef struct _TAllDefectPixel
{
	int nType;
	int nBlockSize;
	double dDefectRatioDark;
	double dDefectRatioBright;
	int nMaxDarkDefectNum;
	int nMaxBrightDefectNum;
	int nEnableChannel;
} TAllDefectPixel;

typedef struct _TAllDefectPixel_ONSEMI_RCCB
{
	int nBlockSizeHot;
	int nBlockSizeDark;
	int nBlockSizeBright;

	int nThresholdTypeHot;					// threshold type for hot defect
	int nThresholdTypeDark;					// threshold type for dark defect
	int nThresholdTypeBright;				// threshold type for bright defect

	int nThresholdTypeLineDefect;			// threshold type for line defect
	int nAlgorithmTypeLineDefect;			// algorithm type for line defect

	double dDefectThresholdHot;				// threshold for hot defect		(dark image)
	double dDefectThresholdDark;			// threshold for dark defect	(mid-level image)
	double dDefectThresholdBright;			// threshold for bright defect	(mid-level image)
	double dDefectThresholdRowInDark;		// threshold for row defect under dark condition
	double dDefectThresholdRowInBright;		// threshold for row defect under bright condition
	double dDefectThresholdColumnInDark;	// threshold for column defect under dark condition
	double dDefectThresholdColumnInBright;	// threshold for column defect under bright condition
	double dDefectThresholdColumnFPN;		// threshold for columnFPN under bright condition

	int nMaxHotDefectNum;					// specification of the maximum number of hot defect
	int nMaxDarkDefectNum;					// specification of the maximum number of dark defect
	int nMaxBrightDefectNum;				// specification of the maximum number of bright defect

	int nMaxHotCoupletNum;					// specification of the maximum number of hot couplet
	int nMaxDarkCoupletNum;					// specification of the maximum number of dark couplet
	int nMaxBrightCoupletNum;				// specification of the maximum number of bright couplet

	int nMaxHotClusterNum;					// specification of the maximum number of hot cluster
	int nMaxDarkClusterNum;					// specification of the maximum number of dark cluster
	int nMaxBrightClusterNum;				// specification of the maximum number of bright cluster

	int nMaxRowDefectNumInDark;				// specification of the maximum number of row defect under dark condition
	int nMaxRowDefectNumInBright;			// specification of the maximum number of row defect under bright condition
	int nMaxColumnDefectNumInDark;			// specification of the maximum number of column defect under dark condition
	int nMaxColumnDefectNumInBright;		// specification of the maximum number of column defect under bright condition

	int nEnableChannel;
	int nDefectInCouplet;
	int nDefectInCluster;
	int nDefectInClusterChannel;
	int nDefectType;

	TCircleSpecN tCircleSpec;
} TAllDefectPixel_ONSEMI_RCCB;

typedef struct _TAllDefectPixel_ONSEMI_MONO
{
	int nBlockSizeHot;
	int nBlockSizeDark;
	int nBlockSizeBright;

	int nThresholdTypeHot;				// threshold type for hot defect
	int nThresholdTypeDark;				// threshold type for dark defect
	int nThresholdTypeBright;			// threshold type for bright defect

	double dDefectThresholdHot;			// threshold for hot defect		(dark image)
	double dDefectThresholdDark;		// threshold for dark defect	(mid-level image)
	double dDefectThresholdBright;		// threshold for bright defect	(mid-level image)
	double dDefectVeryThresholdHot;		// very threshold for hot defect (dark image)
	double dDefectVeryThresholdDark;	// very threshold for dark defect	(mid-level image)
	double dDefectVeryThresholdBright;	// very threshold for bright defect	(mid-level image)

	int nMaxHotDefectNum;				// specification of the maximum number of hot defect
	int nMaxDarkDefectNum;				// specification of the maximum number of dark defect
	int nMaxBrightDefectNum;			// specification of the maximum number of bright defect
	int nMaxHotVeryDefectNum;			// specification of the maximum number of very hot defect
	int nMaxDarkVeryDefectNum;			// specification of the maximum number of very dark defect
	int nMaxBrightVeryDefectNum;		// specification of the maximum number of very bright defect

	int nMaxHotClusterNum;				// specification of the maximum number of hot cluster
	int nMaxClusterNum;					// specification of the maximum number of dark/bright cluster

	int nEnableChannel;
	int nDefectInCluster;
	int nDefectType;
} TAllDefectPixel_ONSEMI_MONO;

#define ALL_DEFECT_PIXEL_ONSEMI_SPEC_FLAG_VERSION_MAJOR		1
#define ALL_DEFECT_PIXEL_ONSEMI_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_ALL_DEFECT_PIXEL_ONSEMI
{
	ALL_DEFECT_PIXEL_ONSEMI_BLOCK_SIZE_HOT,
	ALL_DEFECT_PIXEL_ONSEMI_BLOCK_SIZE_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_BLOCK_SIZE_BRIGHT,

	ALL_DEFECT_PIXEL_ONSEMI_THRESHOLD_TYPE_HOT,
	ALL_DEFECT_PIXEL_ONSEMI_THRESHOLD_TYPE_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_THRESHOLD_TYPE_BRIGHT,

	ALL_DEFECT_PIXEL_ONSEMI_THRESHOLD_TYPE_LINE_DEFECT,
	ALL_DEFECT_PIXEL_ONSEMI_ALGORITHM_TYPE_LINE_DEFECT,

	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_HOT,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_BRIGHT,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_VERY_HOT,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_VERY_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_VERY_BRIGHT,

	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_ROW_IN_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_ROW_IN_BRIGHT,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_COLUMN_IN_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_COLUMN_IN_BRIGHT,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_THRESHOLD_COLUMN_FPN,

	ALL_DEFECT_PIXEL_ONSEMI_MAX_DEFECT_NUM_HOT,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DEFECT_NUM_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DEFECT_NUM_BRIGHT,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DEFECT_NUM_VERY_HOT,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DEFECT_NUM_VERY_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DEFECT_NUM_VERY_BRIGHT,

	ALL_DEFECT_PIXEL_ONSEMI_MAX_HOT_COUPLET_NUM,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DARK_COUPLET_NUM,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_BRIGHT_COUPLET_NUM,

	ALL_DEFECT_PIXEL_ONSEMI_MAX_HOT_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_DARK_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_BRIGHT_CLUSTER_NUM,

	ALL_DEFECT_PIXEL_ONSEMI_MAX_ROW_DEFECT_NUM_IN_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_ROW_DEFECT_NUM_IN_BRIGHT,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_COLUMN_DEFECT_NUM_IN_DARK,
	ALL_DEFECT_PIXEL_ONSEMI_MAX_COLUMN_DEFECT_NUM_IN_BRIGHT,

	ALL_DEFECT_PIXEL_ONSEMI_ENABLE_CHANNEL,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_IN_COUPLET,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_IN_CLUSTER,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_IN_CLUSTER_CHANNEL,
	ALL_DEFECT_PIXEL_ONSEMI_DEFECT_TYPE,

	ALL_DEFECT_PIXEL_ONSEMI_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_ALL_DEFECT_PIXEL_ONSEMI;

typedef struct _TAllDefectPixel_ONSEMI_ALL
{
	int nBlockSizeHot;
	int nBlockSizeDark;
	int nBlockSizeBright;

	int nThresholdTypeHot;					// threshold type for hot defect
	int nThresholdTypeDark;					// threshold type for dark defect
	int nThresholdTypeBright;				// threshold type for bright defect

	int nThresholdTypeLineDefect;			// threshold type for line defect
	int nAlgorithmTypeLineDefect;			// algorithm type for line defect

	double dDefectThresholdHot;				// threshold for hot defect		(dark image)
	double dDefectThresholdDark;			// threshold for dark defect	(mid-level image)
	double dDefectThresholdBright;			// threshold for bright defect	(mid-level image)
	double dDefectVeryThresholdHot;			// very threshold for hot defect (dark image)
	double dDefectVeryThresholdDark;		// very threshold for dark defect	(mid-level image)
	double dDefectVeryThresholdBright;		// very threshold for bright defect	(mid-level image)
	double dDefectThresholdRowInDark;		// threshold for row defect under dark condition
	double dDefectThresholdRowInBright;		// threshold for row defect under bright condition
	double dDefectThresholdColumnInDark;	// threshold for column defect under dark condition
	double dDefectThresholdColumnInBright;	// threshold for column defect under bright condition
	double dDefectThresholdColumnFPN;		// threshold for columnFPN under bright condition

	int nMaxHotDefectNum;					// specification of the maximum number of hot defect
	int nMaxDarkDefectNum;					// specification of the maximum number of dark defect
	int nMaxBrightDefectNum;				// specification of the maximum number of bright defect
	int nMaxHotVeryDefectNum;				// specification of the maximum number of very hot defect
	int nMaxDarkVeryDefectNum;				// specification of the maximum number of very dark defect
	int nMaxBrightVeryDefectNum;			// specification of the maximum number of very bright defect

	int nMaxHotCoupletNum;					// specification of the maximum number of hot couplet
	int nMaxDarkCoupletNum;					// specification of the maximum number of dark couplet
	int nMaxBrightCoupletNum;				// specification of the maximum number of bright couplet

	int nMaxHotClusterNum;					// specification of the maximum number of hot cluster
	int nMaxDarkClusterNum;					// specification of the maximum number of dark cluster
	int nMaxBrightClusterNum;				// specification of the maximum number of bright cluster

	int nMaxRowDefectNumInDark;				// specification of the maximum number of row defect under dark condition
	int nMaxRowDefectNumInBright;			// specification of the maximum number of row defect under bright condition
	int nMaxColumnDefectNumInDark;			// specification of the maximum number of column defect under dark condition
	int nMaxColumnDefectNumInBright;		// specification of the maximum number of column defect under bright condition

	int nEnableChannel;
	int nDefectInCouplet;
	int nDefectInCluster;
	int nDefectInClusterChannel;
	int nDefectType;

	TCircleSpecN tCircleSpec;
} TAllDefectPixel_ONSEMI_ALL;

#define ALL_DEFECT_PIXEL_OMS_SPEC_FLAG_VERSION_MAJOR		1
#define ALL_DEFECT_PIXEL_OMS_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_ALL_DEFECT_PIXEL_OMS
{
	ALL_DEFECT_PIXEL_OMS_BLOCK_SIZE_HOT,
	ALL_DEFECT_PIXEL_OMS_BLOCK_SIZE_DARK,
	ALL_DEFECT_PIXEL_OMS_BLOCK_SIZE_BRIGHT,
	ALL_DEFECT_PIXEL_OMS_BLOCK_SIZE_LGIT_DARK,
	ALL_DEFECT_PIXEL_OMS_BLOCK_SIZE_LGIT_BRIGHT,

	ALL_DEFECT_PIXEL_OMS_THRESHOLD_TYPE_HOT,
	ALL_DEFECT_PIXEL_OMS_THRESHOLD_TYPE_DARK,
	ALL_DEFECT_PIXEL_OMS_THRESHOLD_TYPE_BRIGHT,
	ALL_DEFECT_PIXEL_OMS_THRESHOLD_TYPE_LGIT_DARK,
	ALL_DEFECT_PIXEL_OMS_THRESHOLD_TYPE_LGIT_BRIGHT,

	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_HOT1,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_HOT2,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_DARK,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_BRIGHT,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_LGIT_DARK1,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_LGIT_DARK2,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_LGIT_BRIGHT1,
	ALL_DEFECT_PIXEL_OMS_DEFECT_THRESHOLD_LGIT_BRIGHT2,

	ALL_DEFECT_PIXEL_OMS_DEFECT_ALGORITHM_TYPE_HOT,
	ALL_DEFECT_PIXEL_OMS_DEFECT_ALGORITHM_TYPE_DARK,
	ALL_DEFECT_PIXEL_OMS_DEFECT_ALGORITHM_TYPE_BRIGHT,
	ALL_DEFECT_PIXEL_OMS_DEFECT_ALGORITHM_TYPE_LGIT_DARK,
	ALL_DEFECT_PIXEL_OMS_DEFECT_ALGORITHM_TYPE_LGIT_BRIGHT,

	ALL_DEFECT_PIXEL_OMS_MAX_DEFECT_NUM_HOT,
	ALL_DEFECT_PIXEL_OMS_MAX_DEFECT_NUM_DARK,
	ALL_DEFECT_PIXEL_OMS_MAX_DEFECT_NUM_BRIGHT,
	ALL_DEFECT_PIXEL_OMS_MAX_DEFECT_NUM_LGIT_DARK,
	ALL_DEFECT_PIXEL_OMS_MAX_DEFECT_NUM_LGIT_BRIGHT,

	ALL_DEFECT_PIXEL_OMS_MAX_HOT_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_OMS_MAX_DARK_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_OMS_MAX_BRIGHT_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_OMS_MAX_LGIT_DARK_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_OMS_MAX_LGIT_BRIGHT_CLUSTER_NUM,

	ALL_DEFECT_PIXEL_OMS_DEFECT_IN_CLUSTER,
	ALL_DEFECT_PIXEL_OMS_DEFECT_TYPE,

	ALL_DEFECT_PIXEL_OMS_LOW_LIGHT_THRESHOLD,

	ALL_DEFECT_PIXEL_OMS_MASK,

	ALL_DEFECT_PIXEL_OMS_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_ALL_DEFECT_PIXEL_OMS;

typedef struct _TAllDefectPixel_OMS
{
	int nBlockSizeHot;
	int nBlockSizeDark;
	int nBlockSizeBright;
	int nBlockSizeLGITDark;
	int nBlockSizeLGITBright;

	int nThresholdTypeHot;				// threshold type for hot defect
	int nThresholdTypeDark;				// threshold type for dark defect
	int nThresholdTypeBright;			// threshold type for bright defect
	int nThresholdTypeLGITDark;			// threshold type for dark defect of LGIT
	int nThresholdTypeLGITBright;		// threshold type for bright defect of LGIT

	double dDefectThresholdHot1;		// threshold1 for hot defect			(BG On image)
	double dDefectThresholdHot2;		// threshold2 for hot defect			(BG On image)
	double dDefectThresholdDark;		// threshold for dark defect			(BG On - BG Off image)
	double dDefectThresholdBright;		// threshold for bright defect			(BG On - BG Off image)
	double dDefectThresholdLGITDark1;	// threshold1 for dark defect of LGIT	(BG On - BG Off image)
	double dDefectThresholdLGITDark2;	// threshold2 for dark defect of LGIT	(BG On - BG Off image)
	double dDefectThresholdLGITBright1;	// threshold1 for bright defect of LGIT	(BG On - BG Off image)
	double dDefectThresholdLGITBright2;	// threshold2 for bright defect of LGIT	(BG On - BG Off image)

	int nAlgorithmTypeHot;				// algorithm type for hot defect
	int nAlgorithmTypeDark;				// algorithm type for dark defect
	int nAlgorithmTypeBright;			// algorithm type for bright defect
	int nAlgorithmTypeLGITDark;			// algorithm type for hot defect of LGIT
	int nAlgorithmTypeLGITBright;		// algorithm type for hot defect of LGIT

	int nMaxHotDefectNum;				// specification of the maximum defect number of hot defect
	int nMaxDarkDefectNum;				// specification of the maximum defect number of dark defect
	int nMaxBrightDefectNum;			// specification of the maximum defect number of bright defect
	int nMaxLGITDarkDefectNum;			// specification of the maximum defect number of LGIT dark defect
	int nMaxLGITBrightDefectNum;		// specification of the maximum defect number of LGIT bright defect

	int nMaxHotClusterNum;				// specification of the maximum cluster number of hot cluster
	int nMaxDarkClusterNum;				// specification of the maximum cluster number of dark cluster
	int nMaxBrightClusterNum;			// specification of the maximum cluster number of bright cluster
	int nMaxLGITDarkClusterNum;			// specification of the maximum cluster number of dark cluster of LGIT
	int nMaxLGITBrightClusterNum;		// specification of the maximum cluster number of bright cluster of LGIT

	int nDefectInCluster;
	int nDefectType;

	double dLowLightTheshold;
	BYTE *mask;

	TCircleSpecN tCircleSpec;
} TAllDefectPixel_OMS;

#define ALL_DEFECT_PIXEL_OV_SPEC_FLAG_VERSION_MAJOR		1
#define ALL_DEFECT_PIXEL_OV_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_ALL_DEFECT_PIXEL_OV
{
	ALL_DEFECT_PIXEL_OV_BLOCK_SIZE_HOT,
	ALL_DEFECT_PIXEL_OV_BLOCK_SIZE_DARK,
	ALL_DEFECT_PIXEL_OV_BLOCK_SIZE_BRIGHT,

	ALL_DEFECT_PIXEL_OV_THRESHOLD_TYPE_HOT,
	ALL_DEFECT_PIXEL_OV_THRESHOLD_TYPE_DARK,
	ALL_DEFECT_PIXEL_OV_THRESHOLD_TYPE_BRIGHT,

	ALL_DEFECT_PIXEL_OV_THRESHOLD_TYPE_LINE_DEFECT,
	ALL_DEFECT_PIXEL_OV_ALGORITHM_TYPE_LINE_DEFECT,

	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_HOT,
	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_DARK,
	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_BRIGHT,
	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_ROW_IN_DARK,
	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_ROW_IN_BRIGHT,
	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_COLUMN_IN_DARK,
	ALL_DEFECT_PIXEL_OV_DEFECT_THRESHOLD_COLUMN_IN_BRIGHT,

	ALL_DEFECT_PIXEL_OV_MAX_DEFECT_NUM_HOT,
	ALL_DEFECT_PIXEL_OV_MAX_DEFECT_NUM_DARK,
	ALL_DEFECT_PIXEL_OV_MAX_DEFECT_NUM_BRIGHT,

	ALL_DEFECT_PIXEL_OV_MAX_HOT_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_OV_MAX_DARK_CLUSTER_NUM,
	ALL_DEFECT_PIXEL_OV_MAX_BRIGHT_CLUSTER_NUM,

	ALL_DEFECT_PIXEL_OV_MAX_ROW_DEFECT_NUM_IN_DARK,
	ALL_DEFECT_PIXEL_OV_MAX_ROW_DEFECT_NUM_IN_BRIGHT,
	ALL_DEFECT_PIXEL_OV_MAX_COLUMN_DEFECT_NUM_IN_DARK,
	ALL_DEFECT_PIXEL_OV_MAX_COLUMN_DEFECT_NUM_IN_BRIGHT,

	ALL_DEFECT_PIXEL_OV_ENABLE_CHANNEL,
	ALL_DEFECT_PIXEL_OV_DEFECT_IN_CLUSTER,
	ALL_DEFECT_PIXEL_OV_DEFECT_IN_CLUSTER_CHANNEL,
	ALL_DEFECT_PIXEL_OV_DEFECT_TYPE,

	ALL_DEFECT_PIXEL_OV_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_ALL_DEFECT_PIXEL_OV;

typedef struct _TAllDefectPixel_OV
{
	int nBlockSizeHot;
	int nBlockSizeDark;
	int nBlockSizeBright;

	int nThresholdTypeHot;					// threshold type for hot defect
	int nThresholdTypeDark;					// threshold type for dark defect
	int nThresholdTypeBright;				// threshold type for bright defect

	int nThresholdTypeLineDefect;			// threshold type for line defect
	int nAlgorithmTypeLineDefect;			// algorithm type for line defect

	double dDefectThresholdHot;				// threshold for hot defect		(dark image)
	double dDefectThresholdDark;			// threshold for dark defect	(mid-level image)
	double dDefectThresholdBright;			// threshold for bright defect	(mid-level image)
	double dDefectThresholdRowInDark;		// threshold for row defect under dark condition
	double dDefectThresholdRowInBright;		// threshold for row defect under bright condition
	double dDefectThresholdColumnInDark;	// threshold for column defect under dark condition
	double dDefectThresholdColumnInBright;	// threshold for column defect under bright condition

	int nMaxHotDefectNum;					// specification of the maximum number of hot defect
	int nMaxDarkDefectNum;					// specification of the maximum number of dark defect
	int nMaxBrightDefectNum;				// specification of the maximum number of bright defect

	int nMaxHotClusterNum;					// specification of the maximum number of hot cluster
	int nMaxDarkClusterNum;					// specification of the maximum number of dark cluster
	int nMaxBrightClusterNum;				// specification of the maximum number of bright cluster

	int nMaxRowDefectNumInDark;				// specification of the maximum number of row defect under dark condition
	int nMaxRowDefectNumInBright;			// specification of the maximum number of row defect under bright condition
	int nMaxColumnDefectNumInDark;			// specification of the maximum number of column defect under dark condition
	int nMaxColumnDefectNumInBright;		// specification of the maximum number of column defect under bright condition

	int nEnableChannel;
	int nDefectInCluster;
	int nDefectInClusterChannel;
	int nDefectType;

	TCircleSpecN tCircleSpec;
} TAllDefectPixel_OV;

#define SONY_DEFECT_PIXEL_SPEC_FLAG_VERSION_MAJOR		1
#define SONY_DEFECT_PIXEL_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_SONY_DEFECT_PIXEL
{
	SONY_DEFECT_PIXEL_DIFF_TYPE,
	SONY_DEFECT_PIXEL_DEFECT_TYPE,
	SONY_DEFECT_PIXEL_LEFT_EDGE_SIZE,
	SONY_DEFECT_PIXEL_TOP_EDGE_SIZE,
	SONY_DEFECT_PIXEL_RIGHT_EDGE_SIZE,
	SONY_DEFECT_PIXEL_BOTTOM_EDGE_SIZE,
	SONY_DEFECT_PIXEL_DEFECT_RATIO,
	SONY_DEFECT_PIXEL_MAX_SINGLE_DEFECT_NUM = SONY_DEFECT_PIXEL_DEFECT_RATIO + 4,
	SONY_DEFECT_PIXEL_DEFECT_IN_CLUSTER,
	SONY_DEFECT_PIXEL_ENABLE_CHANNEL,
	SONY_DEFECT_PIXEL_OB_LINE_COUNT,
	SONY_DEFECT_PIXEL_WINDOW_SIZE,
	SONY_DEFECT_PIXEL_DIVIDE_SUBREGION,

	SONY_DEFECT_PIXEL_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_SONY_DEFECT_PIXEL;

typedef struct _TSonyDarkDefectPixel
{
	int nType;
	int nDefectType;
	int nLeftEdgeSize;
	int nTopEdgeSize;
	int nRightEdgeSize;
	int nBottomEdgeSize;
	double dDefectRatio[4];
	int nMaxSingleDefectNum;
	int nDefectInCluster;
	int nEnableChannel;
	int nOBLineCount;
	int nWindowSize;
	int nDivideSubRegion;
} TSonyDefectPixel;

#define ALL_DEFECT_PIXEL_SONY_SPEC_FLAG_VERSION_MAJOR		1
#define ALL_DEFECT_PIXEL_SONY_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_ALL_DEFECT_PIXEL_SONY
{
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_DARK_SP1L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_DARK_SP2L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_BRIGHT_SP1L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_BRIGHT_SP2L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_BRIGHT_IN_DARK_SP1L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_BRIGHT_IN_DARK_SP2H,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_BRIGHT_IN_DARK_SP2L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_DARK_IN_SATURATED_SP1H,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_DARK_IN_SATURATED_SP1L,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_DARK_IN_SATURATED_SP2H,
	ALL_DEFECT_PIXEL_SONY_THRESHOLD_TYPE_DARK_IN_SATURATED_SP2L,

	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_SP1L,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_SP2L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_SP1L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_SP1L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_SP2L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_SP2L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_SP1L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_IN_DARK_SP1L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_SP2L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_IN_DARK_SP2H = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_IN_DARK_SP1L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_IN_DARK_SP2L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_IN_DARK_SP2H + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP1H = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_BRIGHT_IN_DARK_SP2L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP1L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP1H + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP2H = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP1L + 4,
	ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP2L = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP2H + 4,

	ALL_DEFECT_PIXEL_SONY_MAX_DEFECT_NUM_SP1 = ALL_DEFECT_PIXEL_SONY_DEFECT_THRESHOLD_DARK_IN_SATURATED_SP2L + 4,
	ALL_DEFECT_PIXEL_SONY_MAX_DEFECT_NUM_SP2,

	ALL_DEFECT_PIXEL_SONY_MAX_CLUSTER_NUM,

	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_HIGHLIGHT_SP1L,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_HIGHLIGHT_SP2L,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_DARK_SP1L,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_DARK_SP2H,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_DARK_SP2L,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_SATURATED_SP1H,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_SATURATED_SP1L,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_SATURATED_SP2H,
	ALL_DEFECT_PIXEL_SONY_OB_LINE_COUNT_IN_SATURATED_SP2L,

	ALL_DEFECT_PIXEL_SONY_ENABLE_CHANNEL,
	ALL_DEFECT_PIXEL_SONY_DEFECT_IN_CLUSTER,
	ALL_DEFECT_PIXEL_SONY_LEFT_EDGE_SIZE,
	ALL_DEFECT_PIXEL_SONY_TOP_EDGE_SIZE,
	ALL_DEFECT_PIXEL_SONY_RIGHT_EDGE_SIZE,
	ALL_DEFECT_PIXEL_SONY_BOTTOM_EDGE_SIZE,
	ALL_DEFECT_PIXEL_SONY_WINDOW_SIZE,
	ALL_DEFECT_PIXEL_SONY_DIVIDE_SUBREGION,
	ALL_DEFECT_PIXEL_SONY_DEFECT_TYPE,

	ALL_DEFECT_PIXEL_SONY_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_ALL_DEFECT_PIXEL_SONY;

typedef struct _TAllDefectPixel_SONY
{
	int nThresholdTypeDarkSP1L;					// threshold type for dark defect
	int nThresholdTypeDarkSP2L;					// threshold type for dark defect
	int nThresholdTypeBrightSP1L;				// threshold type for bright defect
	int nThresholdTypeBrightSP2L;				// threshold type for bright defect
	int nThresholdTypeBrightInDarkSP1L;			// threshold type for bright defect in the dark
	int nThresholdTypeBrightInDarkSP2H;			// threshold type for bright defect in the dark
	int nThresholdTypeBrightInDarkSP2L;			// threshold type for bright defect in the dark
	int nThresholdTypeDarkInSaturatedSP1H;		// threshold type for dark defect at signal saturated
	int nThresholdTypeDarkInSaturatedSP1L;		// threshold type for dark defect at signal saturated
	int nThresholdTypeDarkInSaturatedSP2H;		// threshold type for dark defect at signal saturated
	int nThresholdTypeDarkInSaturatedSP2L;		// threshold type for dark defect at signal saturated

	double dDefectThresholdDarkSP1L[4];			// threshold for dark defect	(mid-level image)
	double dDefectThresholdDarkSP2L[4];			// threshold for dark defect	(mid-level image)
	double dDefectThresholdBrightSP1L[4];			// threshold for bright defect	(mid-level image)
	double dDefectThresholdBrightSP2L[4];			// threshold for bright defect	(mid-level image)
	double dDefectThresholdBrightInDarkSP1L[4];	// threshold for bright defect	(dark image)
	double dDefectThresholdBrightInDarkSP2H[4];	// threshold for bright defect	(dark image)
	double dDefectThresholdBrightInDarkSP2L[4];	// threshold for bright defect	(dark image)
	double dDefectThresholdDarkInSaturatedSP1H[4];	// threshold for dark defect	(saturated image)
	double dDefectThresholdDarkInSaturatedSP1L[4];	// threshold for dark defect	(saturated image)
	double dDefectThresholdDarkInSaturatedSP2H[4];	// threshold for dark defect	(saturated image)
	double dDefectThresholdDarkInSaturatedSP2L[4];	// threshold for dark defect	(saturated image)

	int nMaxDefectNumSP1;						// specification of the maximum number of SP1 defect
	int nMaxDefectNumSP2;						// specification of the maximum number of SP2 defect

	int nMaxClusterNum;							// specification of the maximum number of cluster

	int nOBStartLineInHighlightSP1L;			// specification of the OB Start line at signal saturated
	int nOBStartLineInHighlightSP2L;			// specification of the OB Start line at signal saturated
	int nOBStartLineInDarkSP1L;					// specification of the OB Start line at signal saturated
	int nOBStartLineInDarkSP2H;					// specification of the OB Start line at signal saturated
	int nOBStartLineInDarkSP2L;					// specification of the OB Start line at signal saturated
	int nOBStartLineInSaturatedSP1H;			// specification of the OB Start line at signal saturated
	int nOBStartLineInSaturatedSP1L;			// specification of the OB Start line at signal saturated
	int nOBStartLineInSaturatedSP2H;			// specification of the OB Start line at signal saturated
	int nOBStartLineInSaturatedSP2L;			// specification of the OB Start line at signal saturated
	int nOBLineCountInHighlightSP1L;			// specification of the OB line number at signal saturated
	int nOBLineCountInHighlightSP2L;			// specification of the OB line number at signal saturated
	int nOBLineCountInDarkSP1L;					// specification of the OB line number at signal saturated
	int nOBLineCountInDarkSP2H;					// specification of the OB line number at signal saturated
	int nOBLineCountInDarkSP2L;					// specification of the OB line number at signal saturated
	int nOBLineCountInSaturatedSP1H;			// specification of the OB line number at signal saturated
	int nOBLineCountInSaturatedSP1L;			// specification of the OB line number at signal saturated
	int nOBLineCountInSaturatedSP2H;			// specification of the OB line number at signal saturated
	int nOBLineCountInSaturatedSP2L;			// specification of the OB line number at signal saturated

	int nEnableChannel;
	int nDefectInCluster;
	int nLeftEdgeSize;
	int nTopEdgeSize;
	int nRightEdgeSize;
	int nBottomEdgeSize;
	int nWindowSize;
	int nDivideSubRegion;
	int nDefectType;

	TCircleSpecN tCircleSpec;
} TAllDefectPixel_SONY;

#define ALL_DEFECT_PIXEL_RIVIAN_SPEC_FLAG_VERSION_MAJOR		1
#define ALL_DEFECT_PIXEL_RIVIAN_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_ALL_DEFECT_PIXEL_RIVIAN
{
	ALL_DEFECT_PIXEL_RIVIAN_THRESHOLD_TYPE_DARK_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_THRESHOLD_TYPE_DARK_IN_BRIGHT,
	ALL_DEFECT_PIXEL_RIVIAN_THRESHOLD_TYPE_BRIGHT_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_THRESHOLD_TYPE_BRIGHT_IN_BRIGHT,

	ALL_DEFECT_PIXEL_RIVIAN_THRESHOLD_TYPE_LINE_DEFECT,
	ALL_DEFECT_PIXEL_RIVIAN_ALGORITHM_TYPE_LINE_DEFECT,

	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_DARK_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_DARK_IN_BRIGHT,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_BRIGHT_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_BRIGHT_IN_BRIGHT,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_ROW_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_ROW_IN_BRIGHT,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_COLUMN_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_THRESHOLD_COLUMN_IN_BRIGHT,

	ALL_DEFECT_PIXEL_RIVIAN_MAX_DEFECT_NUM_DARK_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_DEFECT_NUM_DARK_IN_BRIGHT,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_DEFECT_NUM_BRIGHT_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_DEFECT_NUM_BRIGHT_IN_BRIGHT,

	ALL_DEFECT_PIXEL_RIVIAN_MAX_DARK_CLUSTER_IN_DARK_NUM,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_DARK_CLUSTER_IN_BRIGHT_NUM,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_BRIGHT_CLUSTER_IN_DARK_NUM,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_BRIGHT_CLUSTER_IN_BRIGHT_NUM,

	ALL_DEFECT_PIXEL_RIVIAN_MAX_ROW_DEFECT_NUM_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_ROW_DEFECT_NUM_IN_BRIGHT,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_COLUMN_DEFECT_NUM_IN_DARK,
	ALL_DEFECT_PIXEL_RIVIAN_MAX_COLUMN_DEFECT_NUM_IN_BRIGHT,

	ALL_DEFECT_PIXEL_RIVIAN_ENABLE_CHANNEL,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_IN_CLUSTER,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_IN_CLUSTER_CHANNEL,
	ALL_DEFECT_PIXEL_RIVIAN_DEFECT_TYPE,

	ALL_DEFECT_PIXEL_RIVIAN_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_ALL_DEFECT_PIXEL_RIVIAN;

typedef struct _TAllDefectPixel_RIVIAN
{
	int nThresholdTypeDarkInDark;			// threshold type for dark defect under dark condition
	int nThresholdTypeDarkInBright;			// threshold type for dark defect under bright condition
	int nThresholdTypeBrightInDark;			// threshold type for bright defect under dark condition
	int nThresholdTypeBrightInBright;		// threshold type for bright defect under bright condition

	int nThresholdTypeLineDefect;			// threshold type for line defect
	int nAlgorithmTypeLineDefect;			// algorithm type for line defect

	double dDefectThresholdDarkInDark;		// threshold for dark defect under dark condition
	double dDefectThresholdDarkInBright;	// threshold for dark defect under bright condition
	double dDefectThresholdBrightInDark;	// threshold for bright defect under dark condition
	double dDefectThresholdBrightInBright;	// threshold for bright defect under bright condition
	double dDefectThresholdRowInDark;		// threshold for row defect under dark condition
	double dDefectThresholdRowInBright;		// threshold for row defect under bright condition
	double dDefectThresholdColumnInDark;	// threshold for column defect under dark condition
	double dDefectThresholdColumnInBright;	// threshold for column defect under bright condition

	int nMaxDarkDefectInDarkNum;			// specification of the maximum number of dark defect under dark condition
	int nMaxDarkDefectInBrightNum;			// specification of the maximum number of dark defect under bright condition
	int nMaxBrightDefectInDarkNum;			// specification of the maximum number of bright defect under dark condition
	int nMaxBrightDefectInBrightNum;		// specification of the maximum number of bright defect under bright condition

	int nMaxDarkClusterInDarkNum;			// specification of the maximum number of dark cluster under dark condition
	int nMaxDarkClusterInBrightNum;			// specification of the maximum number of dark cluster under bright condition
	int nMaxBrightClusterInDarkNum;			// specification of the maximum number of bright cluster under dark condition
	int nMaxBrightClusterInBrightNum;		// specification of the maximum number of bright cluster under bright condition

	int nMaxRowDefectNumInDark;				// specification of the maximum number of row defect under dark condition
	int nMaxRowDefectNumInBright;			// specification of the maximum number of row defect under bright condition
	int nMaxColumnDefectNumInDark;			// specification of the maximum number of column defect under dark condition
	int nMaxColumnDefectNumInBright;		// specification of the maximum number of column defect under bright condition

	int nEnableChannel;
	int nDefectInCluster;
	int nDefectInClusterChannel;
	int nDefectType;

	TCircleSpecN tCircleSpec;
} TAllDefectPixel_RIVIAN;

//1: white pixels in the dark; 2: white pixels at high light; 3: black pixels at high light
typedef enum _EDPCType
{
	EDPCType_WhitePixelDark,
	EDPCType_WhitePixelHighlight,
	EDPCType_BlackPixelHighlight,
} EDPCType;

typedef enum _EDefectType
{
	/* Common */
	EDefectType_WhitePixel = 0,
	EDefectType_BlackPixel,
	EDefectType_HotPixel,
	EMax_DefectType_Defect,
	EDefectType_All = 6,
	EDefectType_LineHor = 0,
	EDefectType_LineVer,
	EDefectType_LineHorInBright = 0,
	EDefectType_LineVerInBright,
	EDefectType_LineHorInDark,
	EDefectType_LineVerInDark,
	EMax_DefectType_Line,
	/* ONSEMI Sensor */
	EDefectType_VeryWhitePixel = 3,
	EDefectType_VeryBlackPixel,
	EDefectType_VeryHotPixel,
	EMax_DefectType_VeryDefect,
	EDefectType_VeryAll = 7,
	/* OMS */
	EDefectType_LGITWhitePixel = 3,
	EDefectType_LGITBlackPixel,
	/* Sony Sensor */
	EDefectType_WhitePixel_SP1L = 0,
	EDefectType_WhitePixel_SP2L,
	EDefectType_BlackPixel_SP1L,
	EDefectType_BlackPixel_SP2L,
	EDefectType_WhitePixelInDark_SP1L,
	EDefectType_WhitePixelInDark_SP2H,
	EDefectType_WhitePixelInDark_SP2L,
	EDefectType_BlackPixelInSaturated_SP1H,
	EDefectType_BlackPixelInSaturated_SP1L,
	EDefectType_BlackPixelInSaturated_SP2H,
	EDefectType_BlackPixelInSaturated_SP2L,
	EMax_DefectType_Sony,
	/* Rivian */
	EDefectType_WhitePixelInBright = 0,
	EDefectType_BlackPixelInBright,
	EDefectType_WhitePixelInDark,
	EDefectType_BlackPixelInDark,
	EMax_DefectType_RIVIAN,
} EDefectType;

#define EdefectType_OV_All 10

typedef enum _EDefectKind
{
	/* Common */
	EDefectKind_WhitePixel				= 0x00000001,
	EDefectKind_BlackPixel				= 0x00000002,
	EDefectKind_HotPixel				= 0x00000004,
	EDefectKind_VeryWhitePixel			= 0x00000008,
	EDefectKind_VeryBlackPixel			= 0x00000010,
	EDefectKind_VeryHotPixel			= 0x00000020,
	EDefectKind_WhiteCouplet			= 0x00000040,
	EDefectKind_BlackCouplet			= 0x00000080,
	EDefectKind_HotCouplet				= 0x00000100,
	EDefectKind_WhiteCluster			= 0x00001000,
	EDefectKind_BlackCluster			= 0x00002000,
	EDefectKind_HotCluster				= 0x00004000,
	EDefectKind_WhiteClusterColor		= 0x00008000,
	EDefectKind_BlackClusterColor		= 0x00010000,
	EDefectKind_HotClusterColor			= 0x00020000,
	EDefectKind_LineHorInDark			= 0x00040000,
	EDefectKind_LineVerInDark			= 0x00080000,
	EDefectKind_LineHorInBright			= 0x00100000,
	EDefectKind_LineVerInBright			= 0x00200000,
	EDefectKind_ColumnFPN				= 0x00400000,
	/* ONSEMI or OVT Sensor */
	EDefectKind_VeryWhiteCouplet		= EDefectKind_WhiteCouplet,
	EDefectKind_VeryBlackCouplet		= EDefectKind_BlackCouplet,
	EDefectKind_VeryHotCouplet			= EDefectKind_HotCouplet,
	EDefectKind_VeryWhiteCluster		= EDefectKind_WhiteCluster,
	EDefectKind_VeryBlackCluster		= EDefectKind_BlackCluster,
	EDefectKind_VeryHotCluster			= EDefectKind_HotCluster,
	EDefectKind_VeryWhiteClusterColor	= EDefectKind_WhiteClusterColor,
	EDefectKind_VeryBlackClusterColor	= EDefectKind_BlackClusterColor,
	EDefectKind_VeryHotClusterColor		= EDefectKind_HotClusterColor,
	/* Sony Sensor */
	EDefectKind_WhitePixel_SP1L			= 0x00000001,
	EDefectKind_WhitePixel_SP2L			= 0x00000002,
	EDefectKind_BlackPixel_SP1L			= 0x00000004,
	EDefectKind_BlackPixel_SP2L			= 0x00000008,
	EDefectKind_WhitePixelInDark_SP1L	= 0x00000010,
	EDefectKind_WhitePixelInDark_SP2H	= 0x00000020,
	EDefectKind_WhitePixelInDark_SP2L	= 0x00000040,
	EDefectKind_BlackPixelInSaturated_SP1H	= 0x00000080,
	EDefectKind_BlackPixelInSaturated_SP1L	= 0x00000100,
	EDefectKind_BlackPixelInSaturated_SP2H	= 0x00000200,
	EDefectKind_BlackPixelInSaturated_SP2L	= 0x00000400,
	EDefectKind_WhiteClusterColor_SP1L	= 0x00000800,
	EDefectKind_WhiteClusterColor_SP2L	= 0x00001000,
	EDefectKind_BlackClusterColor_SP1L	= 0x00002000,
	EDefectKind_BlackClusterColor_SP2L	= 0x00004000,
	EDefectKind_WhiteClusterColorInDark_SP1L = 0x00008000,
	EDefectKind_WhiteClusterColorInDark_SP2H = 0x00010000,
	EDefectKind_WhiteClusterColorInDark_SP2L = 0x00020000,
	EDefectKind_BlackClusterColorInSaturated_SP1H = 0x00040000,
	EDefectKind_BlackClusterColorInSaturated_SP1L = 0x00080000,
	EDefectKind_BlackClusterColorInSaturated_SP2H = 0x00100000,
	EDefectKind_BlackClusterColorInSaturated_SP2L = 0x00200000,
	/* Rivian */
	EDefectKind_WhitePixelInDark			= 0x00000001,
	EDefectKind_BlackPixelInDark			= 0x00000002,
	EDefectKind_WhitePixelInBright			= 0x00000004,
	EDefectKind_BlackPixelInBright			= 0x00000008,
	EDefectKind_WhiteClusterInDark			= 0x00000010,
	EDefectKind_BlackClusterInDark			= 0x00000010,
	EDefectKind_WhiteClusterInBright		= 0x00000040,
	EDefectKind_BlackClusterInBright		= 0x00000080,
	EDefectKind_WhiteClusterColorInDark		= 0x00000100,
	EDefectKind_BlackClusterColorInDark		= 0x00000200,
	EDefectKind_WhiteClusterColorInBright	= 0x00000400,
	EDefectKind_BlackClusterColorInBright	= 0x00000800,

	EDefectKind_All						= 0xFFFFFFFF
} EDefectKind;

typedef enum _ELightCondition
{
	/* Common */
	ELightCondition_Highlight,
	ELightCondition_Dark,
	ELightCondition_All,
	/* Sony Sensor*/
	ELightCondition_Highlight_SP1L = 0,
	ELightCondition_Highlight_SP2L,
	ELightCondition_Dark_SP1L,
	ELightCondition_Dark_SP2H,
	ELightCondition_Dark_SP2L,
	ELightCondition_Saturated_SP1H,
	ELightCondition_Saturated_SP1L,
	ELightCondition_Saturated_SP2H,
	ELightCondition_Saturated_SP2L,
} ELightCondition;

typedef enum _EDiffType
{
	EDiffType_Ratio,
	EDiffType_Diff
} EDiffType;

typedef struct _TDefectPixelCalibration
{
	int nDefectType;
	int nLightContition;
	double dDefectSpec;
	int nMaxCoupletNum;
	int nBlockSize;
	RECT stROI;
} TDefectPixelCalibration;

typedef struct _TFDWhitePixel
{
	int nLightContition;
	double dDefectSpec[2];
	int nBlockSize;
} TFDWhitePixel;

typedef struct _TDarkDefectPixel TDefectCluster;

typedef struct _TDarkDefectPixel TDarkShading;

typedef struct _TDarkBLC
{
	double dBLCspec;
	double dBLCAccuracyResult[4]; // per bayer channel
} TDarkBLC;

#define LINE_NOISE_SPEC_FLAG_VERSION_MAJOR		1
#define LINE_NOISE_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_LINE_NOISE
{
	LINE_NOISE_ALGORITHM_TYPE,
	LINE_NOISE_DIFF_TYPE,
	LINE_NOISE_DEFECT_TYPE,
	LINE_NOISE_HOR_SPEC,
	LINE_NOISE_VER_SPEC,
	LINE_NOISE_ENAABLE_CHANNEL,

	LINE_NOISE_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_LINE_NOISE;

typedef struct _TDarkLineNoise
{
	int nAlgorithmType;
	int nType;
	int nDefectType;
	double dLineNoiseHorSpec;
	double dLinenoiseVerSpec;
	int nEnableChannel;
} TDarkLineNoise;

#define COLUMN_FPN_SPEC_FLAG_VERSION_MAJOR		1
#define COLUMN_FPN_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_COLUMN_FPN
{
	COLUMN_FPN_SPEC,

	COLUMN_FPN_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_COLUMN_FPN;

typedef struct _TColumnFPNDefect
{
	double dColumnFPNSpec;
} TColumnFPNDefect;

#define LOW_LIGHT_DARK_TEST_SPEC_FLAG_VERSION_MAJOR		1
#define LOW_LIGHT_DARK_TEST_SPEC_FLAG_VERSION_MINOR		0
typedef enum _SPEC_FLAG_LOW_LIGHT_DARK_TEST
{
	LOW_LIGHT_DARK_TEST_BLOCK_SIZE,
	LOW_LIGHT_DARK_TEST_SPEC_A,
	LOW_LIGHT_DARK_TEST_SPEC_B,
	LOW_LIGHT_DARK_TEST_RADIUS_A,
	LOW_LIGHT_DARK_TEST_RADIUS_B,
	LOW_LIGHT_DARK_TEST_MAX_COUNT,
	LOW_LIGHT_DARK_TEST_DIFF_TYPE,

	LOW_LIGHT_DARK_TEST_SPEC_FLAG_MAX_COUNT
} SPEC_FLAG_LOW_LIGHT_DARK_TEST;

typedef struct _TLowLightDarkTestSpec
{
	int		nBlockSize;
	double	dInxpectSpecA;
	double	dInxpectSpecB;
	double	dRadiusA;	// 사용자 입력
	double	dRadiusB;	// 사용자 입력
	int		nMaxCount;
	int		nType;
} TLowLightDarkTest;

//typedef struct _TLowLightDarkTestResult
//{
//	int		nPosX;
//	int		nPosY;
//	double	dRefVal;
//	double	dValue;
//	double	dRatioVal;
//	int		nArea;//A영역, B영역
//} TLowLightDarkTestResult;

typedef struct _TDefectOffset
{
	int nHotOffsetType;
	int nBrightOffsetType;
	int nDarkOffsetType;
	int nVeryHotOffsetType;
	int nVeryBrightOffsetType;
	int nVeryDarkOffsetType;
	double dHotDefectOffset;
	double dBrightDefectOffset;
	double dDarkDefectOffset;
	double dVeryHotDefectOffset;
	double dVeryBrightDefectOffset;
	double dVeryDarkDefectOffset;
} TDefectOffset;

//////////////////////////////////////////////////////////////////////////
// Defect
template<typename T, typename DataType = BYTE, typename DefectType = EDefectType, typename DefectKind = EDefectKind, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class IDefectMethodCommon
{
public:
	IDefectMethodCommon() : m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_nRadX(0), m_nRadY(0), m_dRad(0.0), m_Mask(NULL), m_nUsingMask(0), m_eSaturationMethod(SaturationMethod_Y), m_bIsCertified(false)
							{ memset(&m_tDataSpec, 0, sizeof(TDATASPEC)); memset(&m_stSpec, 0, sizeof(T)); memset(&m_stCircleData, 0, sizeof(TCircleData)); memset(&m_stCircleSpec, 0, sizeof(TCircleSpecN)); memset(&m_stDefectOffset, 0, sizeof(TDefectOffset)); memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset)); }
	virtual ~IDefectMethodCommon() {}

	typedef std::vector<TDefectResult> vDefectResult;

	virtual bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool Inspect(TBufferInfo& tBufferInfo, T& _Spec) = 0;
	virtual bool Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual int GetSingleDefectCount() const = 0;
	virtual int GetDefectCount(DefectType type = EDefectType_All) const = 0;
	virtual const TDefectResult* GetDefectResult(DefectType type, int nIndex) const = 0;
	virtual const TDefectResult* GetMaxDefectResult(DefectType type = EDefectType_All) const = 0;
	virtual int GetDefectClusterCount(DefectType type = EDefectType_All) = 0;
	virtual const RECT* GetDefectClusterRect(DefectType type, int nIndex) = 0;
	virtual const TBlobResult* GetDefectClusterResult(DefectType type, int nIndex) = 0;
	virtual const char* GetLogHeader(DefectKind kind = EDefectKind_All) = 0;
	virtual const char* GetLogData(DefectKind kind = EDefectKind_All) = 0;
	virtual const char* GetVersion() = 0;
	virtual void Init(ELightCondition LightCondition = ELightCondition_All) = 0;
	virtual int CalcCircleData(TBufferInfo& tBufferInfo, TCircleSpecN& Spec, TCircleData& tCircleData, TInspectRegionOffset& tInspectRegionOffset) = 0;
	virtual int SetCircleData(TCircleSpecN& Spec, TCircleData& tCircleData) = 0;
	virtual void SetMask(int nUsingMask, BYTE* pMask) = 0;
	virtual void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) = 0;
	virtual void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) = 0;
	virtual void SetDefectOffset(TDefectOffset tDefectOffset) = 0;
	virtual double GetSaturationResult(int nIndex = 0) = 0;
	virtual void SetSaturationResult(int nIndex, double dSaturationResult) = 0;
	virtual void SetSaturationMethod(ESaturationMethod nMethod = SaturationMethod_Y) = 0;
	virtual bool GetCertificationResult() = 0;

protected:
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nUsing8BitOnly;
	int m_nPartialDemosaic;
	std::string m_strLogHeader;
	std::string m_strLogData;
	std::string m_strVersion;
	TDATASPEC m_tDataSpec;
	T m_stSpec;
	TCircleData m_stCircleData;
	TCircleSpecN m_stCircleSpec;
	int m_nRadX;
	int m_nRadY;
	double m_dRad;
	BYTE *m_Mask;
	int m_nUsingMask;
	TInspectRegionOffset m_tInspectRegionOffset;
	TDefectOffset m_stDefectOffset;
	std::vector<double> m_vSaturationResult;
	ESaturationMethod m_eSaturationMethod;
	bool m_bIsCertified;
};

template<typename T, typename DataType = BYTE, typename DefectType = EDefectType, typename DefectKind = EDefectKind, typename LightCondition = ELightCondition, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class IDefectMethodCommonM
{
public:
	IDefectMethodCommonM() : m_nImageWidth(0), m_nImageHeight(0), m_nUsing8BitOnly(0), m_nPartialDemosaic(0), m_nRadX(0), m_nRadY(0), m_dRad(0.0), m_Mask(NULL), m_nUsingMask(0), m_eSaturationMethod(SaturationMethod_Y), m_bIsCertified(false)
							{ memset(&m_tDataSpec, 0, sizeof(TDATASPEC)); memset(&m_stSpec, 0, sizeof(T)); memset(&m_stCircleData, 0, sizeof(TCircleData)); memset(&m_stCircleSpec, 0, sizeof(TCircleSpecN)); memset(&m_stDefectOffset, 0, sizeof(TDefectOffset)); memset(&m_tInspectRegionOffset, 0, sizeof(TInspectRegionOffset)); }
	virtual ~IDefectMethodCommonM() {}

	typedef std::vector<TDefectResult> vDefectResult;

	virtual bool Inspect() = 0;
	virtual bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool Inspect(TBufferInfo& tBufferInfo, T& _Spec) = 0;
	virtual bool Inspect(TFileInfo& tFileInfo, T& _Spec) = 0;
	virtual bool InspectAlgorithm() = 0;
	virtual bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0) = 0;
	virtual int GetSingleDefectCount() const = 0;
	virtual int GetDefectCount(DefectType type = EDefectType_All) const = 0;
	virtual const TDefectResult* GetDefectResult(DefectType type, int nIndex) const = 0;
	virtual const TDefectResult* GetMaxDefectResult(DefectType type = EDefectType_All) const = 0;
	virtual int GetDefectCoupletCount(DefectType type = EDefectType_All) = 0;
	virtual const RECT* GetDefectCoupletRect(DefectType type, int nIndex) = 0;
	virtual const TBlobResult* GetDefectCoupletResult(DefectType type, int nIndex) = 0;
	virtual int GetDefectClusterCount(DefectType type = EDefectType_All) = 0;
	virtual const RECT* GetDefectClusterRect(DefectType type, int nIndex) = 0;
	virtual const TBlobResult* GetDefectClusterResult(DefectType type, int nIndex) = 0;
	virtual int GetDefectClusterColorCount(DefectType type = EDefectType_All) = 0;
	virtual const RECT* GetDefectClusterColorRect(DefectType type, int nIndex) = 0;
	virtual const TBlobResult* GetDefectClusterColorResult(DefectType type, int nIndex) = 0;
	virtual int GetDefectLineCount(DefectType type, LightCondition light) = 0;
	virtual const TDefectResult* GetDefectLineResult(DefectType type, LightCondition light, int nIndex) const = 0;
	virtual int GetDefectColumnFPNCount() = 0;
	virtual const TDefectResult* GetDefectColumnFPNResult(int nIndex = 0) const = 0;
	virtual const char* GetLogHeader(DefectKind type = EDefectKind_All) = 0;
	virtual const char* GetLogData(DefectKind type = EDefectKind_All) = 0;
	virtual const char* GetVersion() = 0;
	virtual bool SetImageSpec(int nImageWidth, int nImageHeight, int nImageCount, T& pSpecc, EDATAFORMAT dataFormat, EOUTMODE outMode, ESENSORTYPE sensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) = 0;
	virtual bool SetImageBuffer(const DataType* pBuffer, int nImageWidth, int nImageHeight, int nImageIndex, EDATAFORMAT eDataFormat = DATAFORMAT_BAYER_12BIT) = 0;
	virtual const TCircleData GetCircleData() = 0;
	virtual void Init(ELightCondition LightCondition = ELightCondition_All) = 0;
	virtual int CalcCircleData(TBufferInfo& tBufferInfo, TCircleSpecN& Spec, TCircleData& tCircleData, TInspectRegionOffset& tInspectRegionOffset) = 0;
	virtual int SetCircleData(TCircleSpecN& Spec, TCircleData& tCircleData) = 0;
	virtual void SetMask(int nUsingMask, BYTE* pMask) = 0;
	virtual void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) = 0;
	virtual void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) = 0;
	virtual void SetDefectOffset(TDefectOffset tDefectOffset) = 0;
	virtual double GetSaturationResult(int nIndex = 0) = 0;
	virtual void SetSaturationResult(int nIndex, double dSaturationResult) = 0;
	virtual void SetSaturationMethod(ESaturationMethod nMethod = SaturationMethod_Y) = 0;
	virtual bool GetCertificationResult() = 0;

protected:
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nUsing8BitOnly;
	int m_nPartialDemosaic;
	std::string m_strLogHeader;
	std::string m_strLogData;
	std::string m_strVersion;
	TDATASPEC m_tDataSpec;
	T m_stSpec;
	TCircleData m_stCircleData;
	TCircleSpecN m_stCircleSpec;
	int m_nRadX;
	int m_nRadY;
	double m_dRad;
	BYTE *m_Mask;
	int m_nUsingMask;
	TInspectRegionOffset m_tInspectRegionOffset;
	TDefectOffset m_stDefectOffset;
	std::vector<double> m_vSaturationResult;
	std::vector< std::vector<BYTE> > m_vRawBuffer;
	ESaturationMethod m_eSaturationMethod;
	bool m_bIsCertified;
};

template<typename T, typename DataType = BYTE, typename DefectType = EDefectType, typename DefectKind = EDefectKind, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class CACMISDefectCommon
{
protected:
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	std::chrono::milliseconds m_elapsedTime;
	std::chrono::milliseconds m_startTimems;
	std::chrono::milliseconds m_endTimems;

	std::string m_strLogHeader;
	std::string m_strLogData;

protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<IDefectMethodCommon<T, DataType, DefectType, DefectKind, DataFormat, OutMode, SensorType, DemosaicMethod>> m_pMethod;
	CACMISDefectCommon() {}
	CACMISDefectCommon(const CACMISDefectCommon&) {}
#else
	IDefectMethodCommon<T, DataType, DefectType, DefectKind, DataFormat, OutMode, SensorType, DemosaicMethod>* m_pMethod;
	CACMISDefectCommon() : m_pMethod(NULL) {}
	CACMISDefectCommon(const CACMISDefectCommon&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISDefectCommon() {}

	inline bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, nDataFormat, nOutMode, nSensorType, nBlackLevel, nUsing8BitOnly, nPartialDemosaic, nDemosaicMethod);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(TBufferInfo& tBufferInfo, T& _Spec)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(tBufferInfo, _Spec);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->InspectAlgorithm(pBuffer, nImageWidth, nImageHeight, _Spec, tDataSpec, nUsing8BitOnly, nPartialDemosaic);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(TFileInfo& tFileInfo, T& _Spec)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(tFileInfo, _Spec);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline int GetSingleDefectCount() const
	{
		return m_pMethod->GetSingleDefectCount();
	}
	inline int GetDefectCount(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetDefectCount(type);
	}
	inline const TDefectResult* GetDefectResult(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectResult(type, nIndex);
	}
	inline const TDefectResult* GetMaxDefectResult(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetMaxDefectResult(type);
	}
	inline int GetDefectClusterCount(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetDefectClusterCount(type);
	}
	inline const RECT* GetDefectClusterRect(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectClusterRect(type, nIndex);
	}
	inline const TBlobResult* GetDefectClusterResult(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectClusterResult(type, nIndex);
	}
	inline const char* GetLogHeader(DefectKind kind = EDefectKind_All)
	{
		m_strLogHeader = "StarTime,EndTime,ElapsedTime,";
		m_strLogHeader += m_pMethod->GetLogHeader(kind);
		return m_strLogHeader.c_str();
	}
	inline const char* GetLogData(DefectKind kind = EDefectKind_All)
	{
		char temp[512];

		memset(temp, 0, sizeof(temp));

		std::time_t startTime_c = std::chrono::system_clock::to_time_t(m_startTime);
		struct tm* tmStartTime = std::localtime(&startTime_c);
		sprintf_s(temp, sizeof(temp), "\'%04d-%02d-%02d %02d:%02d:%02d.%03d,", tmStartTime->tm_year + 1900, tmStartTime->tm_mon + 1, tmStartTime->tm_mday, tmStartTime->tm_hour, tmStartTime->tm_min, tmStartTime->tm_sec, (int)m_startTimems.count());
		m_strLogData = temp;

		std::time_t endTime_c = std::chrono::system_clock::to_time_t(m_endTime);
		struct tm* tmEndTime = std::localtime(&endTime_c);
		sprintf_s(temp, sizeof(temp), "\'%04d-%02d-%02d %02d:%02d:%02d.%03d,", tmEndTime->tm_year + 1900, tmEndTime->tm_mon + 1, tmEndTime->tm_mday, tmEndTime->tm_hour, tmEndTime->tm_min, tmEndTime->tm_sec, (int)m_endTimems.count());
		m_strLogData += temp;

		sprintf_s(temp, sizeof(temp), "%lld,", m_elapsedTime.count());
		m_strLogData += temp;
		m_strLogData += m_pMethod->GetLogData(kind);

		return m_strLogData.c_str();
	}
	inline const char* GetVersion() const
	{
		return m_pMethod->GetVersion();
	}
	inline void Init(ELightCondition LightCondition = ELightCondition_All) const
	{
		return m_pMethod->Init(LightCondition);
	}
	inline int CalcCircleData(TBufferInfo& tBufferInfo, TCircleSpecN& Spec, TCircleData& tCircleData, TInspectRegionOffset& tInspectRegionOffset) const
	{
		return m_pMethod->CalcCircleData(tBufferInfo, Spec, tCircleData, tInspectRegionOffset);
	}
	inline int SetCircleData(TCircleSpecN& Spec, TCircleData& tCircleData) const
	{
		return m_pMethod->SetCircleData(Spec, tCircleData);
	}
	inline void SetMask(int nUsingMask, BYTE* pMask) const
	{
		return m_pMethod->SetMask(nUsingMask, pMask);
	}
	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const
	{
		return m_pMethod->SetInspectPosOffset(nStartOffsetX, nStartOffsetY, nEndOffsetX, nEndOffsetY);
	}
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const
	{
		return m_pMethod->SetInspectPosOffset(tInspectRegionOffset);
	}
	inline void SetDefectOffset(TDefectOffset tDefectOffset) const
	{
		return m_pMethod->SetDefectOffset(tDefectOffset);
	}
	inline long long GetElapsedTime() const
	{
		return m_elapsedTime.count();
	}
	inline double GetSaturationResult(int nIndex) const
	{
		return m_pMethod->GetSaturationResult(nIndex);
	}
	inline void SetSaturationResult(int nIndex, double dSaturationResult) const
	{
		return m_pMethod->SetSaturationResult(nIndex, dSaturationResult);
	}
	inline void SetSaturationMethod(ESaturationMethod nMethod) const
	{
		return m_pMethod->SetSaturationMethod(nMethod);
	}
	inline bool GetCertificationResult()
	{
		return m_pMethod->GetCertificationResult();
	}
};

template<typename T, typename DataType = BYTE, typename DefectType = EDefectType, typename DefectKind = EDefectKind, typename LightCondition = ELightCondition, typename DataFormat = EDATAFORMAT, typename OutMode = EOUTMODE, typename SensorType = ESENSORTYPE, typename DemosaicMethod = EDEMOSAICMETHOD>
class CACMISDefectCommonM
{
protected:
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	std::chrono::milliseconds m_elapsedTime;
	std::chrono::milliseconds m_startTimems;
	std::chrono::milliseconds m_endTimems;

	std::string m_strLogHeader;
	std::string m_strLogData;

protected:
#if (_MSC_VER >= 1700)	// Visual C++ 11
	std::shared_ptr<IDefectMethodCommonM<T, DataType, DefectType, DefectKind, LightCondition, DataFormat, OutMode, SensorType, DemosaicMethod>> m_pMethod;
	CACMISDefectCommonM() {}
	CACMISDefectCommonM(const CACMISDefectCommonM&) {}
#else
	IDefectMethodCommonM<T, DataType, DefectType, DefectKind, LightCondition, DataFormat, OutMode, SensorType, DemosaicMethod>* m_pMethod;
	CACMISDefectCommonM() : m_pMethod(NULL) {}
	CACMISDefectCommonM(const CACMISDefectCommonM&) { delete m_pMethod; }
#endif

public:
	virtual ~CACMISDefectCommonM() {}

	inline bool Inspect()
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect();

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(const DataType* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, EDATAFORMAT nDataFormat, EOUTMODE nOutMode, ESENSORTYPE nSensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(pBuffer, nImageWidth, nImageHeight, _Spec, nDataFormat, nOutMode, nSensorType, nBlackLevel, nUsing8BitOnly, nPartialDemosaic, nDemosaicMethod);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(TBufferInfo& tBufferInfo, T& _Spec)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(tBufferInfo, _Spec);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool Inspect(TFileInfo& tFileInfo, T& _Spec)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->Inspect(tFileInfo, _Spec);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool InspectAlgorithm()
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->InspectAlgorithm();

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline bool InspectAlgorithm(const int* pBuffer, int nImageWidth, int nImageHeight, T& _Spec, TDATASPEC& tDataSpec, int nUsing8BitOnly = 0, int nPartialDemosaic = 0)
	{
		m_startTime = std::chrono::system_clock::now();

		bool bRet = m_pMethod->InspectAlgorithm(pBuffer, nImageWidth, nImageHeight, _Spec, tDataSpec, nUsing8BitOnly, nPartialDemosaic);

		m_endTime = std::chrono::system_clock::now();
		CalcElapsedTime(m_startTime, m_endTime, m_elapsedTime, m_startTimems, m_endTimems);

		return bRet;
	}
	inline int GetSingleDefectCount() const
	{
		return m_pMethod->GetSingleDefectCount();
	}
	inline int GetDefectCount(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetDefectCount(type);
	}
	inline const TDefectResult* GetDefectResult(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectResult(type, nIndex);
	}
	inline const TDefectResult* GetMaxDefectResult(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetMaxDefectResult(type);
	}
	inline int GetDefectCoupletCount(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetDefectCoupletCount(type);
	}
	inline const RECT* GetDefectCoupletRect(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectCoupletRect(type, nIndex);
	}
	inline const TBlobResult* GetDefectCoupletResult(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectCoupletResult(type, nIndex);
	}
	inline int GetDefectClusterCount(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetDefectClusterCount(type);
	}
	inline const RECT* GetDefectClusterRect(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectClusterRect(type, nIndex);
	}
	inline const TBlobResult* GetDefectClusterResult(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectClusterResult(type, nIndex);
	}
	inline int GetDefectClusterColorCount(DefectType type = EDefectType_All) const
	{
		return m_pMethod->GetDefectClusterColorCount(type);
	}
	inline const RECT* GetDefectClusterColorRect(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectClusterColorRect(type, nIndex);
	}
	inline const TBlobResult* GetDefectClusterColorResult(DefectType type, int nIndex) const
	{
		return m_pMethod->GetDefectClusterColorResult(type, nIndex);
	}
	inline int GetDefectLineCount(DefectType type, LightCondition light) const
	{
		return m_pMethod->GetDefectLineCount(type, light);
	}
	inline const TDefectResult* GetDefectLineResult(DefectType type, LightCondition light, int nIndex) const
	{
		return m_pMethod->GetDefectLineResult(type, light, nIndex);
	}
	inline int GetDefectColumnFPNCount() const
	{
		return m_pMethod->GetDefectColumnFPNCount();
	}
	inline const TDefectResult* GetDefectColumnFPNResult(int nIndex = 0) const
	{
		return m_pMethod->GetDefectColumnFPNResult(nIndex);
	}
	inline const char* GetLogHeader(DefectKind kind = EDefectKind_All)
	{
		m_strLogHeader = "StarTime,EndTime,ElapsedTime,";
		m_strLogHeader += m_pMethod->GetLogHeader(kind);
		return m_strLogHeader.c_str();
	}
	inline const char* GetLogData(DefectKind kind = EDefectKind_All)
	{
		char temp[512];

		memset(temp, 0, sizeof(temp));

		std::time_t startTime_c = std::chrono::system_clock::to_time_t(m_startTime);
		struct tm* tmStartTime = std::localtime(&startTime_c);
		sprintf_s(temp, sizeof(temp), "\'%04d-%02d-%02d %02d:%02d:%02d.%03d,", tmStartTime->tm_year + 1900, tmStartTime->tm_mon + 1, tmStartTime->tm_mday, tmStartTime->tm_hour, tmStartTime->tm_min, tmStartTime->tm_sec, (int)m_startTimems.count());
		m_strLogData = temp;

		std::time_t endTime_c = std::chrono::system_clock::to_time_t(m_endTime);
		struct tm* tmEndTime = std::localtime(&endTime_c);
		sprintf_s(temp, sizeof(temp), "\'%04d-%02d-%02d %02d:%02d:%02d.%03d,", tmEndTime->tm_year + 1900, tmEndTime->tm_mon + 1, tmEndTime->tm_mday, tmEndTime->tm_hour, tmEndTime->tm_min, tmEndTime->tm_sec, (int)m_endTimems.count());
		m_strLogData += temp;

		sprintf_s(temp, sizeof(temp), "%lld,", m_elapsedTime.count());
		m_strLogData += temp;
		m_strLogData += m_pMethod->GetLogData(kind);

		return m_strLogData.c_str();
	}
	inline const char* GetVersion() const
	{
		return m_pMethod->GetVersion();
	}
	inline bool SetImageSpec(int nImageWidth, int nImageHeight, int nImageCount, T& _Spec, EDATAFORMAT dataFormat, EOUTMODE outMode, ESENSORTYPE sensorType, int nBlackLevel, int nUsing8BitOnly = 0, int nPartialDemosaic = 0, EDEMOSAICMETHOD nDemosaicMethod = DEMOSAICMETHOD_GRADIENT) const
	{
		return m_pMethod->SetImageSpec(nImageWidth, nImageHeight, nImageCount, _Spec, dataFormat, outMode, sensorType, nBlackLevel, nUsing8BitOnly, nPartialDemosaic, nDemosaicMethod);
	}
	inline bool SetImageBuffer(const DataType* pBuffer, int nImageWidth, int nImageHeight, int nImageIndex, EDATAFORMAT eDataFormat)
	{
		return m_pMethod->SetImageBuffer(pBuffer, nImageWidth, nImageHeight, nImageIndex, eDataFormat);
	}
	inline const TCircleData GetCircleData() const
	{
		return m_pMethod->GetCircleData();
	}
	inline void Init(ELightCondition LightCondition = ELightCondition_All) const
	{
		return m_pMethod->Init(LightCondition);
	}
	inline int CalcCircleData(TBufferInfo& tBufferInfo, TCircleSpecN& Spec, TCircleData& tCircleData, TInspectRegionOffset& tInspectRegionOffset) const
	{
		return m_pMethod->CalcCircleData(tBufferInfo, Spec, tCircleData, tInspectRegionOffset);
	}
	inline int SetCircleData(TCircleSpecN& Spec, TCircleData& tCircleData) const
	{
		return m_pMethod->SetCircleData(Spec, tCircleData);
	}
	inline void SetMask(int nUsingMask, BYTE* pMask) const
	{
		return m_pMethod->SetMask(nUsingMask, pMask);
	}
	inline void SetInspectPosOffset(int nStartOffsetX, int nStartOffsetY, int nEndOffsetX, int nEndOffsetY) const
	{
		return m_pMethod->SetInspectPosOffset(nStartOffsetX, nStartOffsetY, nEndOffsetX, nEndOffsetY);
	}
	inline void SetInspectPosOffset(TInspectRegionOffset tInspectRegionOffset) const
	{
		return m_pMethod->SetInspectPosOffset(tInspectRegionOffset);
	}
	inline void SetDefectOffset(TDefectOffset tDefectOffset) const
	{
		return m_pMethod->SetDefectOffset(tDefectOffset);
	}
	inline long long GetElapsedTime() const
	{
		return m_elapsedTime.count();
	}
	inline double GetSaturationResult(int nIndex) const
	{
		return m_pMethod->GetSaturationResult(nIndex);
	}
	inline void SetSaturationResult(int nIndex, double dSaturationResult) const
	{
		return m_pMethod->SetSaturationResult(nIndex, dSaturationResult);
	}
	inline void SetSaturationMethod(ESaturationMethod nMethod) const
	{
		return m_pMethod->SetSaturationMethod(nMethod);
	}
	inline bool GetCertificationResult()
	{
		return m_pMethod->GetCertificationResult();
	}
};

