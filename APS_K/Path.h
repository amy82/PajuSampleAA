#pragma once
#include "stdafx.h"

#define		BASE_DIR			"D:\\EVMS"
#define		BASE_LOG_DIR		"D:\\EVMS\\LOG"
#define		LOG_DIR				"D:\\EVMS\\LOG\\EtcLog"
#define		BACKUP_DIR			"D:\\EVMS\\LOG\\Backup"
#define		IMAGE_BASE_DIR		"D:\\EVMS\\LOG\\ImageLog"
#define		ALARM_DIR			"D:\\EVMS\\LOG\\AlarmLog"



#define		BASE_AA_MODEL_LOAD_DIR	"D:\\EVMS\\APS_MODEL2"
#define		BASE_AA_BACKUP_DIR		"D:\\EVMS\\APS_MODEL2\\Backup"

#if (____AA_WAY == PCB_TILT_AA)
#define		AA_MODEL_LOAD_DIR		"D:\\EVMS\\APS_MODEL2\\PCBAA"
#define		AA_BACKUP_LOAD_DIR		"D:\\EVMS\\APS_MODEL2\\Backup\\PCBAA"

#else

#define		AA_MODEL_LOAD_DIR		"D:\\EVMS\\APS_MODEL2\\LENSAA"
#define		AA_BACKUP_LOAD_DIR		"D:\\EVMS\\APS_MODEL2\\Backup\\LENSAA"
#endif

