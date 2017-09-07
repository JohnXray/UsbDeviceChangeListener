
// UsbDeviceChangeListenerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxmsg_.h"
#include "dbt.h"
#include "UsbDeviceChangeListener.h"
#include "UsbDeviceChangeListenerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUsbMessageListenerDlg dialog



CUsbDeviceChangeListenerDlg::CUsbDeviceChangeListenerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USBMESSAGELISTENER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsbDeviceChangeListenerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MessageListBox, vMessageListBox);
}

BEGIN_MESSAGE_MAP(CUsbDeviceChangeListenerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DEVICECHANGE, OnDeviceChange)
END_MESSAGE_MAP()


// CUsbDeviceChangeListenerDlg message handlers

BOOL CUsbDeviceChangeListenerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

LRESULT CUsbDeviceChangeListenerDlg::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{// Every USB serial device connect or disconnect generates two device change
 // messages. One sends the device port and the other send the action occurring.
 // And they come in reverse order whether connecting or disconnecting.
	CString ComPortId;
	CString TimeString = (CTime::GetCurrentTime()).Format("%H:%M:%S");
	CString msVal; msVal.Format(_T(".%d  "), GetTickCount() % 1000);
	TimeString += msVal;
	if (DBT_DEVICEARRIVAL == wParam || DBT_DEVICEREMOVECOMPLETE == wParam)
	{
		PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
		PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
		PDEV_BROADCAST_HANDLE pDevHnd;
		PDEV_BROADCAST_OEM pDevOem;
		PDEV_BROADCAST_PORT pDevPort;
		PDEV_BROADCAST_VOLUME pDevVolume;

		CString Direction;
		if(DBT_DEVICEARRIVAL == wParam) Direction = "USB Inserted";
		else Direction = "USB Removed";

		switch (pHdr->dbch_devicetype)
		{
		case DBT_DEVTYP_DEVICEINTERFACE:
		{
			pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
			CString msg; msg.Format(_T("%s Received DBT_DEVTYP_DEVICEINTERFACE  wParam:%x  lParam:%x    %s"), TimeString, wParam, lParam, Direction);
			vMessageListBox.AddString(msg);
		}
		break;
		case DBT_DEVTYP_HANDLE:
		{
			pDevHnd = (PDEV_BROADCAST_HANDLE)pHdr;
			CString msg; msg.Format(_T("%s Received DBT_DEVTYP_HANDLE           wParam:%x  lParam:%x    %s"), TimeString, wParam, lParam, Direction);
			vMessageListBox.AddString(msg);
		}
		break;
		case DBT_DEVTYP_OEM:
		{
			pDevOem = (PDEV_BROADCAST_OEM)pHdr;
			CString msg; msg.Format(_T("%s Received DBT_DEVTYP_OEM              wParam:%x  lParam:%x    %s"), TimeString, wParam, lParam, Direction);
			vMessageListBox.AddString(msg);
		}
		break;
		case DBT_DEVTYP_PORT:
		{
			pDevPort = (PDEV_BROADCAST_PORT)pHdr;
			ComPortId = pDevPort->dbcp_name;
			CString msg; msg.Format(_T("%s Received DBT_DEVTYP_PORT                 wParam:%x  lParam:%x    %s %s"), TimeString, wParam, lParam, ComPortId, Direction);
			vMessageListBox.AddString(msg);
		}
		break;
		case DBT_DEVTYP_VOLUME:
			pDevVolume = (PDEV_BROADCAST_VOLUME)pHdr;
			CString msg; msg.Format(_T("%s Received DBT_DEVTYP_VOLUME           wParam:%x  lParam:%x    %s"), TimeString, wParam, lParam, Direction);
			vMessageListBox.AddString(msg);
			break;
		}
	}
	else
		if (DBT_DEVNODES_CHANGED == wParam)
		{
			CString msg; msg.Format(_T("%s Received DBT_DEVNODES_CHANGED         wParam:%x  lParam:%x"), TimeString, wParam, lParam);
			vMessageListBox.AddString(msg);
		}
		else
		{
			CString msg; msg.Format(_T("%s Received Unknown Message         wParam:%x  lParam:%x"), TimeString, wParam, lParam);
			vMessageListBox.AddString(msg);
		}
	return 1;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUsbDeviceChangeListenerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUsbDeviceChangeListenerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

