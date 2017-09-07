
// UsbDeviceChangeListener.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUsbMessageListenerApp:
// See UsbDeviceChangeListener.cpp for the implementation of this class
//

class CUsbDeviceChangeListenerApp : public CWinApp
{
public:
	CUsbDeviceChangeListenerApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CUsbDeviceChangeListenerApp theApp;