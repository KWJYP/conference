// Manage.cpp : implementation file
//

#include "stdafx.h"
#include "HDD.h"
#include "HDDDlg.h"
#include "Manage.h"
#include "IDNode.h"
#include "LinkedList.h"
#include "Register.h"
#include "afxdialogex.h"


// Manage dialog

IMPLEMENT_DYNAMIC(Manage, CDialog)

Manage::Manage(CWnd* pParent /*=NULL*/)
	: CDialog(Manage::IDD, pParent)
{
	
}

Manage::~Manage()
{
}

void Manage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, Site_List, m_slist);
	DDX_Control(pDX, ID_List, m_ilist);
}


BEGIN_MESSAGE_MAP(Manage, CDialog)
	ON_BN_CLICKED(BN_Register, &Manage::OnBnClickedRegister)
	ON_LBN_SELCHANGE(Site_List, &Manage::OnLbnSelchangeList)
	ON_BN_CLICKED(BN_Delete, &Manage::OnBnClickedDelete)
	ON_BN_CLICKED(IDOK, &Manage::OnBnClickedOk)
END_MESSAGE_MAP()


// Manage message handlers

BOOL Manage::OnInitDialog()
{
	CDialog::OnInitDialog();
	List.SetHead(((CHDDDlg*)GetParent())->hdd);
	IDNode* temp = List.GetHead();
	while(temp !=NULL)
	{
		while(temp!=NULL)
		{
			m_slist.AddString(temp->GetAddr());
			if(temp->GetDown() !=NULL)
			{
				while(temp != NULL)
				{
					m_ilist.AddString(temp->GetID());
					temp=temp->GetDown();
				}
			}
			else
			{
				temp=temp->GetNext();
			}
		}
	}
	return true;
}
void Manage::OnBnClickedRegister()
{
		UpdateData(true);

   Register reg;
   IDNode* node = new IDNode;
      
   if(reg.DoModal() != IDOK)
         return;
   node->SetAddr(reg.m_addr);
   node->SetDB_Name(reg.m_name);
   node->SetDB_PW(reg.m_pw);
   node->SetID(reg.m_id);
   node->SetDB_User(reg.m_user);
   List.Insert(node);

   //m_ilist.AddString(node->GetID());
   int index=0;
   
   while((index=m_slist.FindString(index,reg.m_addr)==LB_ERR))
   {
	if(index ==0)
	{
	   return;
	}
   m_slist.AddString(node->GetAddr());
   }
 //  UpdateData(false);
	// TODO: Add your control notification handler code here
}
void Manage::Update()
{
	
}

void Manage::OnLbnSelchangeList()
{

	IDNode* temp=List.GetHead();
	int index = m_slist.GetCurSel();
	int flag=0;
	CString str;

	while(temp !=NULL)
	{
		if(index == -1)
		{
			 AfxMessageBox(_T("올바른 사이트를 선택하여주십시오"));
			 break;
		}
		else
		{
		m_slist.GetText(index,str);
		m_ilist.ResetContent();
		if(temp->GetAddr()==str)
		{
			while(temp!=NULL)
			{
			m_ilist.AddString(temp->GetID());
			temp=temp->GetDown();
			}
			
		}
		else
		{
			temp=temp->GetNext();
		}
		}
	}
	// TODO: Add your control notification handler code here
}


void Manage::OnBnClickedDelete()
{
	UpdateData(true);
	CString dsite;
	CString did;
	CString msg;
	IDNode* node = new IDNode;
	int index;
	m_ilist.GetText(m_ilist.GetCurSel(),did);
	m_slist.GetText(m_slist.GetCurSel(),dsite);
	msg.Format(_T("%s의 %s를 삭제하겠습니다."),dsite,did);
	node->SetAddr(dsite);
	node->SetID(did);
	List.Delete(node);
	AfxMessageBox(msg);
	
	 m_ilist.DeleteString(m_ilist.GetCurSel());
	 index=m_ilist.GetCount();
	 if(index == 0)
	 {
		 m_slist.DeleteString(m_slist.GetCurSel());
	 }
		UpdateData(false);
}


void Manage::OnBnClickedOk()
{
	((CHDDDlg*)GetParent())->hdd = List.GetHead();

	CDialog::OnOK();
}
