#pragma once
#include "LinkedList.h"
#include "Register.h"
// Manage dialog

class Manage : public CDialog
{
	DECLARE_DYNAMIC(Manage)

public:
	Manage(CWnd* pParent = NULL);   // standard constructor
	virtual ~Manage();
	virtual BOOL OnInitDialog();        //생성한 클래스 헤더파일에 추가한다.
// Dialog Data
	enum { IDD = IDD_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegister();
	CListBox m_slist;
	CListBox m_ilist;
	LinkedList List;
	
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedOk();
	void Update();

};
