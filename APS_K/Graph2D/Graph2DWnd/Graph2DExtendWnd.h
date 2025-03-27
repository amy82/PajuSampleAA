#pragma once

//! Added by LHW [2008/4/9] : 상속 클래스 테스트 용

// CGraph2DExtendWnd

#include ".\\Graph2DWnd.h"

class CGraph2DExtendWnd : public CGraph2DWnd
{
	DECLARE_DYNAMIC(CGraph2DExtendWnd)

public:
	CGraph2DExtendWnd();
	virtual ~CGraph2DExtendWnd();

protected:
	DECLARE_MESSAGE_MAP()
};


