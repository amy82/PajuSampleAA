// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#pragma warning(disable: 4819)	//! MS쪽의 버그, 특정 경고 (warning C4819) 표시 안함
#pragma warning(disable: 4996)	//특정 경고 (warning C4996) 표시 안함
//

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.
#include <afxdisp.h>        // MFC 자동화 클래스입니다.
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
#include <afxsock.h>            // MFC 소켓 확장
#include "resource.h"
////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
// opencv 3.6.4 include
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <opencv2\imgproc\imgproc.hpp>	
#include <opencv2\core\core.hpp>			
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>

#pragma comment (lib, "mil.lib")
#pragma comment (lib, "milpat.lib")
#pragma comment (lib, "milmod.lib")
#pragma comment (lib, "milim.lib")
#pragma comment (lib, "milblob.lib")
#pragma comment(lib, "uxtheme.lib")








//////////////////////////////////////////////////////////////////////////////////////

#ifndef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#pragma warning(push)
#pragma warning(disable:4146)
//msado60.tlb
#import "C:\Program Files\Common files\System\ado\msado15.dll" rename ("EOF","adoEOF") no_namespace
//
//#import "c:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "EndOfFile")
//#import "C:\\Program Files (x86)\\Common files\\System\\ado\\msado15.dll" rename ("EOF","adoEOF") no_namespace
//#import "c:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "adoEOF")//EndOfFile
#pragma warning(pop) 

using namespace cv;
using namespace std;

#include "GlobalDefine.h"
#include "GlobalDeclare.h"




//
//const float imageWidth = 1280;
//const float imageHeight = 1080;
//

