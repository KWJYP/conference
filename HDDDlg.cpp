
// HDDDlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// CHDDDlg ��ȭ ����




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


// CHDDDlg �޽��� ó����

BOOL CHDDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	HBITMAP hbit;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));

	pic.SetBitmap(hbit) ;

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
		_T("����") );

	m_main.SetFont(&m_font);

	//m_font.CreatePointFont(150,_T("����"));
	//GetDlgItem(IDC_main)->SetFont(&m_font);

	RegisterTray();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CHDDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
		AfxMessageBox(_T("��ϵ� ������ �����ϴ�."));
		return ;
	}
	int i=0;
	ShowWindow(SW_HIDE);
	if(start == 1) 
	{
		AfxMessageBox(_T("�������Դϴ�."));
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

		b.Format(L"%s�� ������ �����Ͽ����ϴ�.", node->GetAddr());
		AfxMessageBox(b,MB_OK);
		return 0;
	}
	else
	{
		CString b;
		b.Format(L"%s ���� �� ���̵� ���� ����.", node->GetAddr());
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

						a.Format(L"%s���� %s�� �α��εǾ����ϴ�.", node->GetAddr(), node->GetID());
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
		AfxMessageBox(_T("�����Ͻñ� �ٶ��ϴ�."));
	}
	else
	{
		stop = 1;
		start = 0;
		AfxMessageBox(_T("���� �����Ǿ����ϴ�."));

	}
}
