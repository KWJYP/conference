#include "StdAfx.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList(void)
{
	Head = NULL;
}


LinkedList::~LinkedList(void)
{
}

void LinkedList :: Insert(IDNode * pnode)
{
	if(Head == NULL)
	{
		Head = pnode;
		return;
	}
	else
	{
		IDNode *temp=Head;
		IDNode *ptemp=Head;
		while(temp != NULL)
		{
			if(temp->GetAddr()==pnode->GetAddr())
			{
				while(temp !=NULL)
				{
					if(temp->GetID() == pnode->GetID())
					{
						AfxMessageBox(_T("이미 등록된 정보입니다."));
						return;
					}
					ptemp = temp;
					temp = temp->GetDown();
				}
				ptemp->SetDown(pnode);
				return;
			}
			else
			{
				ptemp = temp;
				temp = temp->GetNext();
			}
		}
		ptemp->SetNext(pnode);
		return;
	}
}
void LinkedList ::Delete(IDNode* dnode)
{
	IDNode* temp = Head;
	IDNode* ptemp = Head;

	while(temp != NULL)
	{
		if(temp->GetAddr()==dnode->GetAddr())
		{
			while(temp != NULL)
			{
				if(temp->GetID()==dnode->GetID())
				{
					if(temp==Head)
					{
						if(temp->GetDown()==NULL)
						{
							Head=Head->GetNext();
							delete temp;
							return;
						}
					temp->GetDown()->SetNext(Head->GetNext());
					Head = Head->GetDown();;
					delete temp;
					return;
					}
					else if(temp->GetNext()==NULL)
					{
						ptemp->SetNext(NULL);
						delete temp;
						return;
					}
					else
					{
					ptemp->SetDown(temp->GetDown());
					delete temp;
					return;
					}
				}
				else
				{
					ptemp = temp;
					temp = temp->GetDown();
				}
			}
		}
		else
		{
			ptemp = temp;
			temp = temp->GetNext();
		}
	}	
}
void LinkedList ::Print()
{
	IDNode* temp = Head;
	IDNode* ptemp =Head;
	while(ptemp !=NULL)
	{
		temp = ptemp;
		cout << "주소\t\t" << temp->GetAddr()<<endl;
		while(temp!=NULL)
		{
		cout << "DB명\t\t" << "USER비밀번호\t\t" << "USERID\t\t" <<endl;
		cout <<  temp->GetDB_Name()  << "\t\t" << temp->GetDB_PW()  << "\t\t" <<temp->GetID()<<endl;
		temp = temp->GetDown();
		}
		ptemp = ptemp->GetNext();
	}
}
IDNode* LinkedList ::GetHead()
{
	return Head;
}
	void LinkedList::SetHead(IDNode* phead)
	{
	Head = phead;
	}
