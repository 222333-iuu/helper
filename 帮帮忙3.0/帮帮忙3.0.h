
// 帮帮忙3.0.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// C帮帮忙30App:
// 有关此类的实现，请参阅 帮帮忙3.0.cpp
//

class C帮帮忙30App : public CWinApp
{
public:
	C帮帮忙30App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C帮帮忙30App theApp;
