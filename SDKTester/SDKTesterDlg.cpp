
// SDKTesterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SDKTester.h"
#include "SDKTesterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}



void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSDKTesterDlg dialog

CSDKTesterDlg::CSDKTesterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSDKTesterDlg::IDD, pParent)
	, m_strDomain(_T("https://www.moxtra.com"))
	, m_strStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pUpgradeSDK = NULL;
	m_hModule = NULL;
	m_fnReleaszeInstance = NULL;
}

CSDKTesterDlg::~CSDKTesterDlg()
{
	if(m_pUpgradeSDK)
	{
		m_fnReleaszeInstance(m_pUpgradeSDK);
	}
	if(m_hModule)
		FreeLibrary(m_hModule);
}

void CSDKTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDTDOMAIN, m_strDomain);
	DDX_Control(pDX, IDC_PRDOWNLOAD, m_ctrlProgressDownload);
	DDX_Text(pDX, IDC_STATUS, m_strStatus);
}

BEGIN_MESSAGE_MAP(CSDKTesterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSDKTesterDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDTDOMAIN, &CSDKTesterDlg::OnEnChangeEdtdomain)
END_MESSAGE_MAP()


// CSDKTesterDlg message handlers
BOOL CSDKTesterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSDKTesterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSDKTesterDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSDKTesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSDKTesterDlg::OnStatusUpdate(int nState)
{
	TRACE("OnStatusUpdate nState=%d\n",nState);
	switch(nState)
	{
	case IUpgradeStatusCallback::READ_SERVER_VERSION:
		m_strStatus.SetString(_T("Read Server Plugin Version"));
		break;
	case IUpgradeStatusCallback::DOWNLOAD_INSTALL_FILE:
		m_strStatus.SetString(_T("Start to download installer file"));
		break;
	case IUpgradeStatusCallback::LAUNCH_INSTALL_FILE:
		m_strStatus.SetString(_T("Launch Installer File"));
		break;
	case IUpgradeStatusCallback::WAIT_INSTALL_DONE:
		m_strStatus.SetString(_T("Wait for Installer done"));
		break;
	case IUpgradeStatusCallback::INSTALL_DONE:
		m_strStatus.SetString(_T("Installation DONE"));
		break;
	case IUpgradeStatusCallback::NO_NEED_UPGRADE:
		m_strStatus.SetString(_T("No need to upgrade!"));
		break;
	case IUpgradeStatusCallback::FAILED_TO_DOWNLOAD:
		m_strStatus.SetString(_T("Fail to download file"));
		break;
	case IUpgradeStatusCallback::FAILED_TO_READ_SERVER_VERSION:
		m_strStatus.SetString(_T("Failed to read server plugin version!"));
		break;
	}
	UpdateData(FALSE);
}

void CSDKTesterDlg::OnDownloadProgress(int totBytes, int curBytes)
{
	TRACE("OnDownloadProgress totBytes=%d curBytes=%d\n",totBytes,curBytes);
	m_ctrlProgressDownload.SetRange(0,100);
	m_ctrlProgressDownload.SetPos(curBytes*100/totBytes);
}

void CSDKTesterDlg::InitSDK()
{
	UpdateData(TRUE);

	if(m_hModule != NULL)
		return ;
	m_hModule = LoadLibrary(_T("MXNativeUpgradeSDK.dll"));
	if(m_hModule == NULL) return ;
	m_fnCreateInstance = (t_fn_CreateUpgradeSDKInstance)GetProcAddress(m_hModule, (LPCSTR)1);
	m_fnReleaszeInstance = (t_fn_ReleaseUpgradeSdkInstance)GetProcAddress(m_hModule, (LPCSTR)2);
	m_pUpgradeSDK = m_fnCreateInstance(m_strDomain.GetString(),this);
}

void CSDKTesterDlg::FreeSDK()
{
	if(m_pUpgradeSDK)
	{
		m_fnReleaszeInstance(m_pUpgradeSDK);
	}
	if(m_hModule)
		FreeLibrary(m_hModule);
	m_hModule = NULL;
	m_pUpgradeSDK = NULL;
	m_fnReleaszeInstance = NULL;
	m_fnCreateInstance = NULL;
}

void CSDKTesterDlg::OnBnClickedOk()
{
	FreeSDK();
	InitSDK();
	if(m_pUpgradeSDK)
	{
#if 1
		if(m_pUpgradeSDK->IsNeedDownload())
		{
			MessageBox(_T("Need update"));
			m_pUpgradeSDK->CheckAndUpgrade();
		}
		else{
			MessageBox(_T("Don't need update"));
		}
#endif
	}
}

void CSDKTesterDlg::OnEnChangeEdtdomain()
{

}
