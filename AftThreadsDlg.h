// AftThreadsDlg.h : header file
//

#pragma once
#include "MyController.h"
#include "resource.h"

// ”никальные WinApi сообщени€ дл€ завершени€ потоков 
enum ThreadMessages
{
	WM_AFX_THREAD_END = WM_USER + 1,
	WM_AFX_THREAD_FORCED_END
};

// CAftThreadsDlg dialog
class CAftThreadsDlg : public CDialogEx
{
private:
	
// Construction
public:
	CAftThreadsDlg(CWnd* pParent = NULL);	// standard constructor

	MyController* m_PtrMyController;

// Dialog Data
	enum { IDD = IDD_AFTTHREADS_DIALOG };

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

protected:
	afx_msg LRESULT OnAfxThreadEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAfxThreadForcedEnd(WPARAM wParam, LPARAM lParam);


public:
	afx_msg void OnBnClickedButtonStartAfx();
	afx_msg void OnBnClickedButtonStopAfx();

	void SetMyController()
	{
		m_PtrMyController = new MyController(110);
	}
};
