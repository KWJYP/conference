#pragma once


// Register dialog

class Register : public CDialog
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // standard constructor
	virtual ~Register();

// Dialog Data
	enum { IDD = IDD_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CString m_id;

	CString m_addr;
	CString m_name;
	CString m_pw;
	CString m_user;
	afx_msg void OnBnClickedOk();
	CString m_id;
};
