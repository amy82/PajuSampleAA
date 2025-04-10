/*
************************************************************************************************************************
*                                            Log for inspection algorithm
*
*                                     (c) Copyright 2018, LG Innotek. All rights reserved.
*
*                                     implementation for debugging the algorithm of inspection
*
* File    : DataLog.h
* Author  : Kyu-Jeong Choi (kjchoi@lginnotek.com)
* Version : V1.1
************************************************************************************************************************
*/

/* Change log:
- Version : v1.3 (20240405)
  Move to ACMISSoftISP Lib
- Version : v1.2 (20210405)
  Move to ACMISSoftISP Lib
- Version : v1.1 (20190125)
  Change File name to DataLog from AlgorithmLog
  Change Directory to ACMIS from LibACMISResolution
- Version : V1.0 (20180403)
  New.
*/
#pragma once

#include "export.h"
#include <fstream>
#include <tchar.h>

namespace ACMISSoftISP
{
	class ACMISSOFTISPBASIC_API DataLog
	{
	public:
		DataLog();
		DataLog(LPCTSTR lpszFileName, bool bAppend = false);
		~DataLog();

		void Open(LPCTSTR lpszFileName, bool bAppend = false);
		bool Write(LPCTSTR lpszFormat, ...);

	private:
		std::ofstream m_file;
	};
}

using namespace ACMISSoftISP;
