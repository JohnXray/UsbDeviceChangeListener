
// UsbDeviceChangeListenerDlg.h : header file
//

#pragma once


// CUsbDeviceChangeListenerDlg dialog
class CUsbDeviceChangeListenerDlg : public CDialogEx
{
	// Construction
public:
	CUsbDeviceChangeListenerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBMESSAGELISTENER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CListBox vMessageListBox;

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
