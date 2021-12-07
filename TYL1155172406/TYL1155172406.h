
// TYL1155172406.h : main header file for the TYL1155172406 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTYL1155172406App:
// See TYL1155172406.cpp for the implementation of this class
//

class CTYL1155172406App : public CWinApp
{
public:
	CTYL1155172406App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTYL1155172406App theApp;
