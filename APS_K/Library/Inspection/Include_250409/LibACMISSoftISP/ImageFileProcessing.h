#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>

namespace ACMISSoftISP
{
	ACMISSOFTISP_API int LoadImageFile(TFileInfo& tFileInfo, BYTE **pBuffer);

	ACMISSOFTISP_API bool xSaveImage(char* strFileName, void* srcImage);
	ACMISSOFTISP_API bool xSaveImage(char* strFileName, BYTE* pBuffer, int nImageWidth, int nImageHeight, int nType);
	ACMISSOFTISP_API bool xSaveImage(char* strFileName, BYTE* pBuffer, int nImageWidth, int nImageHeight, int nChannel, int nDepth);
	ACMISSOFTISP_API bool xSaveRawImage(char* strFileName, BYTE* pBuffer, int nImageSize);
};
