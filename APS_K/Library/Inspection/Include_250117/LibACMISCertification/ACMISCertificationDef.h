#pragma once

#include <vector>
#include <xstring>
#include <LibACMISCommon/InspectionErrorCode.h>

typedef enum __CERTIFICATION_ITEM_INDEX
{
	CERTIFICATION_ITEM_USERID,
	CERTIFICATION_ITEM_EXPIRE_DATE,
	CERTIFICATION_ITEM_PARAMETER1,
	MAX_COUNT_CERTIFICATION_ITEM
} CERTIFICATION_ITEM_INDEX;

typedef enum __CERTIFICATION_ERROR_CODE
{
	CERTIFICATION_ERROR_Invalid_Password = R_FAIL_CERTIFICATION,
	CERTIFICATION_ERROR_Invalid_Key,
	CERTIFICATION_ERROR_Invalid_Salt,
	CERTIFICATION_ERROR_Invalid_Item_Count,
	CERTIFICATION_ERROR_Invalid_UserID,
	CERTIFICATION_ERROR_No_UserID,
	CERTIFICATION_ERROR_Not_Match_UserID,
	CERTIFICATION_ERROR_License_Expired,
	CERTIFICATION_ERROR_Fail_Read_UserID,
	CERTIFICATION_ERROR_Fail_Read_IssueDate,
	CERTIFICATION_ERROR_Fail_Read_DongleIndex,
	CERTIFICATION_ERROR_Fail_Read_LicenseType,
	CERTIFICATION_ERROR_Fail_Read_ExpireDate,
	CERTIFICATION_ERROR_Fail_Read_Parameter1,
	CERTIFICATION_ERROR_Invalid_ExpireDate,
	CERTIFICATION_ERROR_Invalid_Parameter1,
	CERTIFICATION_ERROR_No_Parameter1,
	CERTIFICATION_ERROR_Too_Short_Parameter1,
	CERTIFICATION_ERROR_Fail_Open_KeyFile,
	CERTIFICATION_ERROR_Fail_Open_EncryptedFile,
	CERTIFICATION_ERROR_Fail_Resize_Buffer,
	MAX_Count_CERTIFICATION_ERROR
} CERTIFICATION_ERROR_CODE;

extern std::string CERTIFICATION_ERROR_STRING[MAX_Count_CERTIFICATION_ERROR - CERTIFICATION_ERROR_Invalid_Password];

typedef std::pair<std::string, std::string> CertificationItem;

typedef struct __CertificationParam
{
	std::string strPassword;
	std::string strSalt;
	std::string strKey;
	std::string strRefPassword;
	std::string strRefSalt;
	std::string strRefUserID;
	std::string strRefParameter1;
	std::vector<CertificationItem> vCertificatingItem;
} CertificationParam;
