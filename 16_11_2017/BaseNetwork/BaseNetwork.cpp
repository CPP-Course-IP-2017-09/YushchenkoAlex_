// BaseNetwork.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BaseNetwork.h"
#include <commctrl.h>
#include <winsock.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Wsock32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


///////////////////////////////////////////////////
HANDLE hThread;
DWORD dwCount, dwThreadId;

void OnServer(HWND hDlg, HWND hRecvEdit);
void OnClient(HWND hDlg, HWND hIp);
DWORD WINAPI ThreadFunc(void * lParam); 
//////////////////////Client+Server////////////////////
#define DEF_HOSTADDR "127.0.0.1" //задание LOOPBACK-ого IP адреса, т.е. локального адреса изначально при запуске программы

int PORT = 3182;            // порт TCP, служит для организации сети
char sSend[256]="\0";       // буфер для хранения в нём отправляемых сообщений
char sRecv[256]="\0";       // временный буфер for получаемых сообщений

wchar_t swSend[256]= {0};       // буфер для хранения в нём отправляемых сообщений
wchar_t swRecv[256]= {0};       // временный буфер for получаемых сообщений

SOCKET ss, cc, r;           // сокеты для организации сети
sockaddr_in Addr;           // обьявление структуры адреса и порта для передачи и приёма данных
WSADATA Wsa;                // инициализации winsock
bool server;                // определениe режима работы программы: сервер или клиент
////////////////////////////////////////////////////


INITCOMMONCONTROLSEX INITObj = {sizeof(INITCOMMONCONTROLSEX), ICC_PAGESCROLLER_CLASS
| ICC_PROGRESS_CLASS | ICC_STANDARD_CLASSES | ICC_TREEVIEW_CLASSES | ICC_UPDOWN_CLASS};


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BASENETWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BASENETWORK));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BASENETWORK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BASENETWORK);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   InitCommonControlsEx(&INITObj);
   DialogBox(hInst, MAKEINTRESOURCE(IDD_NETWORK_DLG), NULL, DlgProc);
   return FALSE;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int wmId, wmEvent;
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			case IDOK:
			case IDCANCEL:		
				EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;		
			break;				
		}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static HWND hServRadio, hClientRadio, hIp, hSendEdit, hRecvEdit, hSendBtn;
	static int iNetStatus;
	int wmId, wmEvent;	

	switch (message)
	{
		case WM_INITDIALOG:
		{			
			                                                      /////  GUI interface 
			RECT rcDlg;			
			int xScreen = GetSystemMetrics(SM_CXSCREEN);		
			int yScreen = GetSystemMetrics(SM_CYSCREEN);		
			GetWindowRect(hDlg, &rcDlg);
			int x = xScreen/2 - rcDlg.right/2;
			int y = yScreen/2 - rcDlg.bottom/2;
			MoveWindow(hDlg, x, y, rcDlg.right, rcDlg.bottom, TRUE);
			
			hServRadio = GetDlgItem(hDlg, IDC_SERVER_RADIO);
			hClientRadio = GetDlgItem(hDlg, IDC_CLIENT_RADIO);
			hIp = GetDlgItem(hDlg, IDC_IPADDRESS1);
			hSendEdit = GetDlgItem(hDlg, IDC_SEND_EDIT);
			hRecvEdit = GetDlgItem(hDlg, IDC_RESV_EDIT);
			hSendBtn = GetDlgItem(hDlg, IDC_SEND_BTN);

			/*char sStr[10] = "abcd";
			wchar_t sTextToEdit[256] = {0};
			for(int i = 0; i < 5; ++i)
				sTextToEdit[i] = sStr[i];		*/	
			//SetWindowText(hRecvEdit, sTextToEdit);
																// network

			// Инициализация Winsock. Без этой функции сеть работать не будет. Ошибка
			// возможна из-за неправильной настройки сети или случайного удаления файла
			// winsock.dll
			if(WSAStartup(0x0101,&Wsa))
				MessageBox(hDlg, L"Cannot init WinSock", L"ERROR", MB_OK);

			// задание величины таймера, через это время программа будет проверять
			// приход сообщений, время равно 1 секунде
			//SetTimer( hDlg, ID_TIMER_1, 1000, NULL); 

			// инициализация структуры типа сообщений, адреса и порта для передачи
			// и приёма данных
			Addr.sin_family=AF_INET;
			Addr.sin_addr.s_addr=INADDR_ANY;
			Addr.sin_port=htons(PORT);
			
			return (INT_PTR)TRUE;
		}

		case WM_COMMAND: 

			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDC_SEND_BTN:
					if (!server) 
					{	
						swSend[0] = '\0';
						GetWindowText(hSendEdit, swSend, 256);
						if(swSend[0] == '\0')
							memcpy(swSend, L"empty", sizeof(L"empty"));
						if(send(cc, (const char *)swSend, sizeof(swSend), 0) == SOCKET_ERROR)
							MessageBox(hDlg, L"Server not respond.", L"Server ERROR", MB_OK);
						else
						{
							recv(cc, (char *)swRecv, sizeof(swRecv), 0);
							SetWindowText(hRecvEdit, swRecv);
						}
					}
					else
					{
						MessageBox(hDlg, L"Server cannot send.", L"Server ERROR", MB_OK);
						SetWindowText(hSendEdit, L"");
					}
				break;
				case IDOK:
				case IDCANCEL:		
					EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;		
				break;	
				case IDC_SERVER_RADIO:
				case IDC_CLIENT_RADIO:
				if(wmEvent == BN_CLICKED)
				{
					int iState   = SendMessage((HWND)lParam, BM_GETSTATE, 0,0);
					wchar_t * wStrAr[2] = {L"IDC_SERVER_RADIO", L"IDC_CLIENT_RADIO"};
					if(iState & BST_CHECKED &&
						iNetStatus != wmId)
					{					
						iNetStatus = wmId;
						MessageBox(hDlg, wStrAr[wmId - 1001], L"CHECKED", MB_OK);						
					}
					switch(wmId)
					{
						case IDC_SERVER_RADIO:
							OnServer(hDlg, hRecvEdit);
						break;
						case IDC_CLIENT_RADIO:
							OnClient(hDlg, hIp);
						break;
					}					
				}
				break;
			}
		break;
	}
	return (INT_PTR)FALSE;
}
void OnClient(HWND hDlg, HWND hIp) //функция для инициализации и работы клиента
{
	if (hThread)
		TerminateThread(hThread,0);
	if (ss)
		closesocket(ss);
	if (r)
		closesocket(r);
	if (cc)
		closesocket(cc);

	//создание соединения для передачи данных
    cc=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (cc==SOCKET_ERROR) 
    {
		 closesocket(cc);
		 cc=0;
		 MessageBox(hDlg, L"Cannot create socket", L"ERROR!!!", MB_OK);
    }

	//соединение с портом сервера
	SOCKADDR_IN servsin = {AF_INET};
	servsin.sin_port = htons(u_short(PORT));
	/////////
	DWORD dwAddr;
	SendMessage(hIp, IPM_GETADDRESS, 0, (LPARAM)&dwAddr);	
	ULONG ulAddr = htonl(dwAddr);
	servsin.sin_addr.S_un.S_addr = ulAddr;//inet_addr(m_Address);

	if (connect(cc, (LPSOCKADDR)&servsin, sizeof(servsin))==SOCKET_ERROR) 
    {
		 closesocket(cc);
		 cc=0;
		 MessageBox(hDlg, L"Cannot connect socket", L"ERROR!!!", MB_OK);
    }
   
	server=FALSE;
}
void OnServer(HWND hDlg, HWND hRecvEdit)					//функция для инициализации и работы сервера
{
    if(cc)
		closesocket(cc);
	server=TRUE;

	////создание соединения для приёма данных
	ss=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
    	  
	//привязывание созданного соединения к порту и к IP адресу
   if (bind(ss, (sockaddr*)&Addr, sizeof(Addr))==SOCKET_ERROR)
   {
      closesocket(ss);
	  ss=0;
      MessageBox(hDlg, L"Cannot bind socket", L"ERROR", MB_OK);
   }  
	
	//инициализация для приёма данных  
   if (listen(ss, SOMAXCONN)==SOCKET_ERROR) 
   {
     closesocket(ss);
	 ss=0;	 
     MessageBox(hDlg, L"Cannot listen socket", L"ERROR", MB_OK);
   }

   //открытие потока для ожидания соединения клиента
   if (ss)
	hThread=CreateThread(NULL,0, ThreadFunc, hRecvEdit, 0, &dwThreadId);
 
}

DWORD WINAPI ThreadFunc(void * pV) 
{
	HWND hRecvEdit = (HWND)pV;
   // функция ожидает соединение клиента, используется для сервера
   if(!r)
	r = accept(ss,(sockaddr*)&Addr, NULL);
   
   if (r == INVALID_SOCKET)	
	   MessageBox(NULL, L"Cannot accept socket", L"ERROR", MB_OK);
   
   if ((r!=0) && server)
   {
		swRecv[0] = '\0';
		if (recv(r, (char *)swRecv, sizeof(swRecv), 0)==SOCKET_ERROR) //функция приёма сообщений
		{
			 // при разъединении клиента с сервером, сервер заново переинициализирует
			 // функцию соединения, для ожидания следующего конекта
			 closesocket(r); 
			 r=0;
		}    
		else
		{	
			//wchar_t sTextToEdit[256] = {0};
			//for(int i = 0; i < 255 && sRecv[i] != 0; ++i) // 255 to be \0 at the end
			//	sTextToEdit[i] = sRecv[i];
			//SetWindowText(hRecvEdit, sTextToEdit);
			SetWindowText(hRecvEdit, swRecv);

			int nCount = 0;
			//i < 254 to guaranty " \0" at the end of a string without if(nCount < 256)
			for(int i = 0; nCount < 254 && swRecv[i] != '\0'; ++i)
				swSend[nCount++] = sRecv[i];			
			wchar_t * pS = L" echo"; // 5 + 1 symbols
			for(int i = 0; nCount < 255 && i < 5; ++i)
				swSend[nCount++] = pS[i];
			swSend[nCount++] = 0;

			send(r, (const char *)swSend, sizeof(swSend), 0);  //посылка подтверждения приёма   
		}
   }

   //создание нового потока, старый закрывается
   if (r!=INVALID_SOCKET) 
	hThread=CreateThread(NULL, 0, ThreadFunc, hRecvEdit, 0, &dwThreadId);

   return 0;
}