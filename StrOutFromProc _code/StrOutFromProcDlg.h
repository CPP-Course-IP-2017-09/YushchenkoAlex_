// StrOutFromProcDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CStrOutFromProcDlg dialog
class CStrOutFromProcDlg : public CDialog
{
// Construction
	
	CString m_FileToDsk;
public:
	CStrOutFromProcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STROUTFROMPROC_DIALOG };

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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	CEdit m_Edit;
	CEdit m_eCommand;
	afx_msg void OnBnClickedButton2();
	CRichEditCtrl m_Rich;
	static DWORD CALLBACK MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

};
