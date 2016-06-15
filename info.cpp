// info.cpp : implementation file
//

#include "stdafx.h"
#include "HDD.h"
#include "info.h"
#include "afxdialogex.h"


// info dialog

IMPLEMENT_DYNAMIC(info, CDialog)

info::info(CWnd* pParent /*=NULL*/)
	: CDialog(info::IDD, pParent)
{

}

info::~info()
{
}

void info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(info, CDialog)
END_MESSAGE_MAP()


// info message handlers
