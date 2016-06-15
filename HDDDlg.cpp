
// HDDDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "HDD.h"
#include "HDDDlg.h"

#include "afxdialogex.h"
#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#define TRAY_NOTIFY          (WM_APP + 100)

#endif
UINT mthread(LPVOID param);

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
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


// CHDDDlg 대화 상자




CHDDDlg::CHDDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHDDDlg::IDD, pParent)
	, m_tray(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	start = 0;
}

void CHDDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_main, m_main);
	DDX_Control(pDX, picture, pic);
}

BEGIN_MESSAGE_MAP(CHDDDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BN_Manege, &CHDDDlg::OnBnClickedManege)
	ON_BN_CLICKED(BN_Start, &CHDDDlg::OnBnClickedStart)

	ON_MESSAGE(TRAY_NOTIFY, OnTrayBnClicked)
	ON_COMMAND(ID_32771, &CHDDDlg::OnOpenMenuClick)
	ON_COMMAND(ID_32772, &CHDDDlg::OnExitMenuClick)
	ON_BN_CLICKED(IDCANCEL, &CHDDDlg::OnBnClickedCancel)
	ON_BN_CLICKED(BN_Made, &CHDDDlg::OnBnClickedMade)
	ON_BN_CLICKED(BN_Stop, &CHDDDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CHDDDlg 메시지 처리기

BOOL CHDDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	HBITMAP hbit;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));

	pic.SetBitmap(hbit) ;

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	hdd = NULL;
	start = 0;
	CFont m_font;
	m_main.SetWindowTextW(_T("Protect my Information"));
	m_font.CreateFont(  8, 
		8, 
		0, 
		0, 
		1, 
		0,
		0, 
		0, 
		0, 
		OUT_DEFAULT_PRECIS, 
		0,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("굴림") );

	m_main.SetFont(&m_font);

	//m_font.CreatePointFont(150,_T("돋움"));
	//GetDlgItem(IDC_main)->SetFont(&m_font);

	RegisterTray();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHDDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHDDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHDDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHDDDlg::OnBnClickedManege()
{
	UpdateData(true);
	Manage man;
	int index=0;

	if(man.DoModal() != IDOK)
		return;
	UpdateData(false);
}



void CHDDDlg::OnBnClickedStart()
{

	if(hdd==NULL)
	{
		AfxMessageBox(_T("등록된 정보가 없습니다."));
		return ;
	}
	int i=0;
	ShowWindow(SW_HIDE);
	if(start == 1) 
	{
		AfxMessageBox(_T("실행중입니다."));
		return;
	}
	start =1;
	IDNode* pCur = hdd;
	IDNode* pCur2 = pCur;
	while(1)
	{
		pCur2 = pCur;
		while(1)
		{
			Sleep(1);
			AfxBeginThread(mthread,pCur2);
			pCur2 = pCur2->GetDown();
			if(pCur2 == NULL)
				break;
		}
		pCur = pCur->GetNext();
		if(pCur == NULL)
			break;
	}

}
int stop = 0;
UINT mthread(LPVOID param)
{

	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;

	IDNode* node = (IDNode*)param;
	int num_fields;
	CString Addr = node->GetAddr();
	CString User = node->GetDB_User();
	CString Pw = node->GetDB_PW();
	CString Name = node->GetDB_Name();
	CString ID = node->GetID();

	char *MYSQL_HOST=new char[Addr.GetLength()+1];
	char *MYSQL_USER=new char[User.GetLength()+1];
	char *MYSQL_PWD=new char[Pw.GetLength()+1];
	char *MYSQL_DB=new char[Name.GetLength()+1];
	char *MYSQL_ID=new char[ID.GetLength()+1];

	strcpy(MYSQL_HOST,CW2A(Addr));
	strcpy( MYSQL_USER,CW2A(User));
	strcpy(MYSQL_PWD,CW2A(Pw));
	strcpy(MYSQL_DB,CW2A(Name));
	strcpy(MYSQL_ID,CW2A(ID));

	mysql_init(&mysql);
	sleep(1);
	CString str;


	if(!mysql_real_connect(&mysql, MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB,3306,0,0))
	{
		CString b;

		b.Format(L"%s에 연결을 실패하였습니다.", node->GetAddr());
		AfxMessageBox(b,MB_OK);
		return 0;
	}
	else
	{
		CString b;
		b.Format(L"%s 에서 내 아이디 감지 시작.", node->GetAddr());
		AfxMessageBox(b);
		//mysql_close(&mysql);


		int p=0;
		while(1)
		{
			if(stop == 1)
			{
				stop = 0;

				return 0;
			}
			mysql_query(&mysql, "select * from LOGIN");
			res = mysql_use_result(&mysql);
			num_fields = mysql_num_fields(res);
			while ((row = mysql_fetch_row(res)))
			{
				for(int i = 0; i < num_fields; i++)
				{

					if(strcmp(row[i],MYSQL_ID) == 0)
					{
						p = 1;
						CString a;

						a.Format(L"%s에서 %s가 로그인되었습니다.", node->GetAddr(), node->GetID());
						AfxMessageBox(a);
						break;
					}

				}
			}
			if(p == 1)
				break;
		}
	}

	return 0;
}


void CHDDDlg::SetRestoreDialog()
{
	NOTIFYICONDATA nId;
	nId.cbSize=sizeof(NOTIFYICONDATA);
	nId.hWnd = this->m_hWnd;
	nId.uID = 0;
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();
}

void CHDDDlg::RegisterTray(void)
{
	NOTIFYICONDATA  nId;


	nId.cbSize          = sizeof(NOTIFYICONDATA);
	nId.hWnd        = this->m_hWnd;
	nId.uID             = 0;
	Shell_NotifyIcon(NIM_DELETE, &nId);

	nId.cbSize          = sizeof(NOTIFYICONDATA);
	nId.hIcon       = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nId.hWnd        = this->m_hWnd;
	CString str;
	GetWindowText(str);
	_tcscpy_s(nId.szTip, str.GetBuffer(str.GetLength()+1));
	str.ReleaseBuffer();

	nId.uID         = 0;
	nId.uFlags      = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nId.uCallbackMessage    = TRAY_NOTIFY;
	Shell_NotifyIcon(NIM_ADD, &nId);
}
afx_msg LRESULT CHDDDlg :: OnTrayBnClicked(WPARAM wParam, LPARAM IParam)
{
	switch(IParam)
	{
	case WM_LBUTTONDBLCLK:
		{
			SetRestoreDialog();
			break;
		}
	case WM_RBUTTONDOWN:
		{
			CPoint pmouse;
			::GetCursorPos(&pmouse);
			CMenu traymenu;
			traymenu.LoadMenu(TrayMenu);
			CMenu* ptraymenu = traymenu.GetSubMenu(0);
			ptraymenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pmouse.x, pmouse.y, AfxGetMainWnd());
			break;
		}
	}
	return 0;
}

void CHDDDlg::OnOpenMenuClick()
{
	SetRestoreDialog();
}


void CHDDDlg::OnExitMenuClick()
{
	CDialog::OnDestroy();

	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(nid);
	nid.hWnd= GetSafeHwnd();
	nid.uID=0;
	Shell_NotifyIcon(NIM_DELETE,&nid);
	CDialog::OnOK();

	// TODO: Add your command handler code here
}


void CHDDDlg::OnBnClickedCancel()
{
	CDialog::OnDestroy();

	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(nid);
	nid.hWnd= GetSafeHwnd();
	nid.uID=0;
	Shell_NotifyIcon(NIM_DELETE,&nid);

	CDialog::OnCancel();
}


void CHDDDlg::OnBnClickedMade()
{
	UpdateData(true);
	info made;
	int index=0;

	if(made.DoModal() != IDOK)
		return;
	UpdateData(false);
}


void CHDDDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	if(start == 0)
	{
		AfxMessageBox(_T("시작하시기 바랍니다."));
	}
	else
	{
		stop = 1;
		start = 0;
		AfxMessageBox(_T("접속 중지되었습니다."));

	}
}
