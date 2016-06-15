
// HDDDlg.h : ��� ����
//

#pragma once
#include "LinkedList.h"
#include "Manage.h"
#include "Register.h"
#include "info.h"
#include "afxwin.h"
#define  UM_TRAYICON  WM_USER+7
// CHDDDlg ��ȭ ����
class CHDDDlg : public CDialog
{
// �����Դϴ�.
public:
	CHDDDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HDD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	LinkedList list;
	IDNode* hdd;


	afx_msg void OnBnClickedManege();
	afx_msg void OnBnClickedStart();
	
	afx_msg LRESULT OnTrayBnClicked(WPARAM, LPARAM);
	void SetRestoreDialog();
protected:
	bool m_tray;
private:
	void RegisterTray(void);
public:
	afx_msg void OnOpenMenuClick();
	afx_msg void OnExitMenuClick();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedMade();
	CStatic m_main;
	CStatic pic;
	afx_msg void OnBnClickedStop();
	int start;
};
