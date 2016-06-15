// Register.cpp : implementation file
//

#include "stdafx.h"
#include "HDD.h"
#include "HDDDlg.h"
#include "Register.h"
#include "afxdialogex.h"


// Register dialog

IMPLEMENT_DYNAMIC(Register, CDialog)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialog(Register::IDD, pParent)
{


	m_addr = _T("");
	m_name = _T("");
	m_pw = _T("");
	m_user = _T("");
	m_id = _T("");
}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_Addr, m_addr);
	DDV_MaxChars(pDX, m_addr, 20);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Text(pDX, IDC_PW, m_pw);
	DDV_MaxChars(pDX, m_pw, 20);
	DDX_Text(pDX, IDC_USER, m_user);
	DDV_MaxChars(pDX, m_user, 20);
	DDX_Text(pDX, IDC_EDIT2, m_id);
	DDV_MaxChars(pDX, m_id, 20);
}


BEGIN_MESSAGE_MAP(Register, CDialog)
	ON_BN_CLICKED(IDOK, &Register::OnBnClickedOk)
END_MESSAGE_MAP()


// Register message handlers


void Register::OnBnClickedOk()
{
	UpdateData(true);
	if(m_addr =="" || m_user==""|| m_pw==""|| m_name=="" || m_id =="")
   {
	   AfxMessageBox(_T("정보를 입력해주세요"));
	   UpdateData(false);
   }
	else
	{
	
	CDialog::OnOK();
	}
	
}
