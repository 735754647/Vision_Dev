// AutoCSD.h : main header file for the AutoCSD DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSDVisionDev
// See AutoCSD.cpp for the implementation of this class
//

class CSDVisionDev : public CWinApp
{
public:
	CSDVisionDev();
	~CSDVisionDev();
	// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
