#pragma once


// info dialog

class info : public CDialog
{
	DECLARE_DYNAMIC(info)

public:
	info(CWnd* pParent = NULL);   // standard constructor
	virtual ~info();

// Dialog Data
	enum { IDD = IDD_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
