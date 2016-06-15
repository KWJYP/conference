#pragma once
class IDNode
{
private:
		CString ID;
		CString Addr;
		CString DB_PW;
		CString DB_Name;
		CString DB_User;
		IDNode *Next;
		IDNode *Down;

public:
	IDNode(void);
	~IDNode(void);

	void SetID(CString id);
	void SetAddr(CString addr);
	void SetDB_PW(CString db_pw);
	void SetDB_Name(CString db_name);
	void SetDB_User(CString db_user);
	void SetNext(IDNode* next);
	void SetDown(IDNode* down);

	CString GetID();
	CString GetAddr();
	CString GetDB_PW();
	CString GetDB_Name();
	CString GetDB_User();
	IDNode* GetNext();
	IDNode* GetDown();


};

