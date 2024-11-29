
// AftThreadsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AftThreads.h"
#include "AftThreadsDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAftThreadsDlg dialog




CAftThreadsDlg::CAftThreadsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAftThreadsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetMyController();
}

void CAftThreadsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAftThreadsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START_AFX, &CAftThreadsDlg::OnBnClickedButtonStartAfx)
	ON_BN_CLICKED(IDC_BUTTON_STOP_AFX, &CAftThreadsDlg::OnBnClickedButtonStopAfx)
	ON_MESSAGE(WM_AFX_THREAD_END, OnAfxThreadEnd)
	ON_MESSAGE(WM_AFX_THREAD_FORCED_END, OnAfxThreadForcedEnd)
END_MESSAGE_MAP()


// CAftThreadsDlg message handlers

BOOL CAftThreadsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CAftThreadsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAftThreadsDlg::OnPaint()
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
HCURSOR CAftThreadsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAftThreadsDlg::OnBnClickedButtonStartAfx()
{
	m_PtrMyController->SetPtrThreadManager(new ThreadManager(m_PtrMyController->AfxFunction, (LPVOID)this, "AfxThread"));
	m_PtrMyController->GetThreadManager()->StartAfxThread();
}


void CAftThreadsDlg::OnBnClickedButtonStopAfx()
{
	m_PtrMyController->StopAfxThreadManager(m_PtrMyController->GetThreadManager());
}


afx_msg LRESULT CAftThreadsDlg::OnAfxThreadEnd(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(L"Afx thread ended normally!", MB_OK | MB_ICONINFORMATION);

	return 0;
}

afx_msg LRESULT CAftThreadsDlg::OnAfxThreadForcedEnd(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(L"Afx thread ended due to stop button!", MB_OK | MB_ICONINFORMATION);

	return 0;
}