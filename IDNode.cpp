#include "StdAfx.h"
#include "IDNode.h"
#include <iostream>
#include <string>

IDNode::IDNode(void)
{
	Next=NULL;
	Down=NULL;
}


IDNode::~IDNode(void)
{
}

void IDNode::SetID(CString id)
{
	ID=id;
}
void IDNode::SetDB_User(CString db_user)
{
	DB_User = db_user;
}



void IDNode:: SetAddr(CString addr)
{
	Addr= addr;
}
	void IDNode:: SetDB_PW(CString db_pw)
	{
		DB_PW=db_pw;
	}
	void IDNode:: SetDB_Name(CString db_name)
	{
		DB_Name = db_name;
	}
	void IDNode:: SetNext(IDNode* next)
	{
		Next = next;
	}
	void IDNode:: SetDown(IDNode* down)
	{
		Down = down;
	}
	CString IDNode:: GetID()
	{
		return ID;
	}
	CString IDNode:: GetAddr()
	{
		return Addr;
	}
	CString IDNode:: GetDB_PW()
	{
		return DB_PW;
	}
	CString IDNode:: GetDB_Name()
	{
		return DB_Name;
	}
	CString IDNode:: GetDB_User()
	{
		return DB_User;
	}
	IDNode* IDNode ::GetNext()
	{
		return Next;
	}
	IDNode* IDNode ::GetDown()
	{
		return Down;
	}
