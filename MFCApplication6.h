
// MFCApplication6.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCApplication6App:
// О реализации данного класса см. MFCApplication6.cpp
//

class CMFCApplication6App : public CWinApp
{
public:
	CMFCApplication6App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication6App theApp;