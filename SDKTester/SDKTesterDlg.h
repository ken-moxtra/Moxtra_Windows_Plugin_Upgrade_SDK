
// SDKTesterDlg.h : header file
//

#pragma once
#include "MXNativeUpgradeSDK.h"
#include "afxcmn.h"

// CSDKTesterDlg dialog
class CSDKTesterDlg : public CDialog,public IUpgradeStatusCallback
{
// Construction
public:
	CSDKTesterDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CSDKTesterDlg();

// Dialog Data
	enum { IDD = IDD_SDKTESTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	HMODULE	m_hModule;
	IMXNativeUpgradeSDK * m_pUpgradeSDK;
	t_fn_CreateUpgradeSDKInstance m_fnCreateInstance;
	t_fn_ReleaseUpgradeSdkInstance m_fnReleaszeInstance;
public:
	virtual void OnStatusUpdate(int nState) ;
	virtual void OnDownloadProgress(int totBytes, int curBytes) ;

	void InitSDK();
	void FreeSDK();
	afx_msg void OnBnClickedOk();
	CString m_strDomain;
	CProgressCtrl m_ctrlProgressDownload;
	CString m_strStatus;
	afx_msg void OnEnChangeEdtdomain();
};
