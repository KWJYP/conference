#pragma once
#include "IDNode.h"
class LinkedList
{
private :
	IDNode* Head;
public:
	LinkedList(void);
	~LinkedList(void);

	void Insert(IDNode* pnode);
	void Delete(IDNode* dnode);
	void Print();
	IDNode* GetHead();
	void SetHead(IDNode* pHead);
};

