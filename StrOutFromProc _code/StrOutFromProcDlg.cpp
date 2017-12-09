// StrOutFromProcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StrOutFromProc.h"
#include "StrOutFromProcDlg.h"
#include ".\stroutfromprocdlg.h"

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


// CStrOutFromProcDlg dialog



CStrOutFromProcDlg::CStrOutFromProcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStrOutFromProcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_FileToDsk = " ";
}

void CStrOutFromProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_EDIT2, m_eCommand);
	DDX_Control(pDX, IDC_RICHEDIT21, m_Rich);
}

BEGIN_MESSAGE_MAP(CStrOutFromProcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CStrOutFromProcDlg message handlers

BOOL CStrOutFromProcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	MessageBox("StrOutFromProc End OnInitDialog");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStrOutFromProcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStrOutFromProcDlg::OnPaint() 
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
HCURSOR CStrOutFromProcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStrOutFromProcDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CStrOutFromProcDlg::OnBnClickedButton1()
{

	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sa;
	// TODO: Add your control notification handler code here

    ZeroMemory( &pi, sizeof(pi) );

	HANDLE FromStdOut = NULL, FromStdIn = NULL;
	//HANDLE ToStdOut = NULL ,ToStdIn = NULL;

	sa.nLength                  = sizeof(sa);
    sa.lpSecurityDescriptor     = NULL;
    sa.bInheritHandle           = true;

	if(!CreatePipe(&FromStdIn, &FromStdOut, &sa, 500000))
	{
		MessageBox("PipeError!!!");
		return;
	}
	/*if(!CreatePipe(&ToStdIn, &ToStdOut, &sa, 2000))
	{
		MessageBox("PipeError!!!");
	}*/
	

	ZeroMemory(&si, sizeof(si)); 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.cb = sizeof(si);
	si.hStdOutput  = FromStdOut;
    si.hStdError   = FromStdOut;
	si.hStdInput   = FromStdIn;//ToStdIn;

	//HANDLE StdOut = 0, StdIn = 0, StdError = 0;

	//si.hStdInput = StdIn;
	//si.hStdOutput = StdOut;
	//si.hStdError = StdError;

	 
	
	char sStr[200000] = "dumpbin.exe";
	char sCommand[100];
	m_eCommand.GetWindowText(sCommand, 99);
	wsprintf(sStr, "Dump\\dumpbin.exe %s %s", m_FileToDsk, (LPCTSTR)sCommand);  // wsprintf -- create and store STRING in the buffer
 		
	CString MyString;

 if( !CreateProcess( NULL,    
		sStr, 
        NULL,              
        NULL,              
        TRUE,            
        0,                
        NULL,             
        NULL,             
        &si,              
        &pi )             
    ) 
    {
		
		MyString.Format("CreateProcess failed (%d).\n", GetLastError());
        MessageBox(MyString);
        return;
    }
	//pi.
	WaitForSingleObject(pi.hProcess, INFINITE);
	//MessageBox(sStr);

	CloseHandle(FromStdOut);

	DWORD dwReaded = 0;
	ReadFile(FromStdIn, sStr, 200000, &dwReaded, 0);
	OemToChar(sStr, sStr);
	m_Edit.SetWindowText(sStr);
	//MessageBox(sStr);
	CloseHandle(FromStdIn);

/*
	CFile cFile;
	cFile.m_hFile = FromStdIn;
	cFile.Read(sStr, 200000);
	*/
	//while(cFile.Read(sStr, 2000) > 0)
	//{
	//	//OemToChar(sStr, sStr);
	//	m_Edit.SetWindowText(sStr);
	//}
	m_Edit.SetWindowText(sStr);


	//MessageBox(sStr);
	CloseHandle(FromStdIn);


	CFile cOpenFile(TEXT("Readme.txt"), CFile::modeRead);
	//CFile cOpenFile(TEXT("D:\\Books\\site.txt"), CFile::modeRead);
	if(cOpenFile.m_hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("Cannot Open!!");
	}
	EDITSTREAM es;

	es.dwCookie = (DWORD) &cOpenFile;
	es.pfnCallback = MyStreamInCallback; 
	m_Rich.StreamIn(SF_TEXT, es);

	/*
	if(cFile.m_hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("Cannot Open!!!");
	}
	EDITSTREAM es;

	es.dwCookie = (DWORD) &cFile;
	es.pfnCallback = MyStreamInCallback; 
	m_Rich.StreamIn(SF_TEXT, es);
		
*/




/*
	char buff[24];
	CloseHandle(StdOut);
	DWORD dwReaded = 0;
	char szOutput[2000] = " ";
	FILETIME endTime, tempTime;
	while(1)
	{

		ReadFile(StdIn, sStr, 2000, &dwReaded, 0);
		OemToChar(sStr, sStr);
		if(dwReaded != 0)
		{
			strcat(szOutput, sStr);
			m_Edit.SetWindowText(szOutput);
		}
		//itoa((int)dwReaded, buff, 10);
		//MessageBox(buff);
		//MessageBox(sStr);
		//if(WaitForSingleObject(pi.hProcess, 1) == WAIT_OBJECT_0)
		//{
		//	break;
		//}
		GetProcessTimes(pi.hProcess, &tempTime, &endTime, &tempTime, &tempTime);
		if(endTime.dwHighDateTime != 0)
			break;
	}
	CloseHandle(StdIn);
	*/
	
	
	//MessageBox(sStr);

	
	//itoa((int)dwReaded, buff, 10);
	//MessageBox(buff);

}

void CStrOutFromProcDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//m_FileDlg.DoModal();
	//CString fileName;
	//OPENFILENAME ofn;
	//ZeroMemory(&ofn, sizeof(ofn));

	CFileDialog m_FileDlg(TRUE, "*.dll");
	m_FileDlg.GetOFN().lpstrFile = m_FileToDsk.GetBuffer(65000);
	m_FileDlg.GetOFN().nMaxFile = 65000;
	m_FileDlg.GetOFN().lpstrFilter = "Исполняемые файлы\0*.exe\0Динамические библиотеки\0*.dll\0";
	m_FileDlg.GetOFN().nFilterIndex = 1;

	INT_PTR nResult = m_FileDlg.DoModal();
	m_FileToDsk.ReleaseBuffer();
	
}


DWORD CALLBACK CStrOutFromProcDlg::MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
	{
		CFile* pFile = (CFile*) dwCookie;

		*pcb = pFile->Read(pbBuff, cb);

		return 0;
	}
