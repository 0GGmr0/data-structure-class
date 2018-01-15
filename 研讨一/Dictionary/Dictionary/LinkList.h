#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H
#include <cstddef>
#include <assert.h>
#include <windows.h>

void gotoxy(int x, int y)  //控制光标位置
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(hOut, c);
}


template <typename T>
class LinkList;

template <typename T>
class Node
{
public:
	friend class Dictionary;
	friend class LinkList<T>;
	Node();                                                      //默认构造
	Node(T Data, Node<T> *Prior = NULL, Node<T> *Next = NULL); 	 //赋值构造
	Node(const Node<T>& node);                                   //拷贝构造
	//void ModifyData(const Node<T>& node);                        //修改data
	//void ModifynNext(const Node<T>& Next);                       //修改next指向
	//void Modifunprior(const Node<T>& Prior);                     //修改prior指向
	T& showData();												 //展示数据data
private:
	Node<T> *next;
	Node<T> *prior;
	T data;

};

template <typename T>
T& Node<T>::showData()
{
	return data;
}

template <typename T>
Node<T>::Node()
{
	next = NULL;
	prior = NULL;
}

template <typename T>
Node<T>::Node(T Data, Node<T> *Prior, Node<T> *Next) :data(Data), prior(Prior), next(Next) {}

template <typename T>
Node<T>::Node(const Node<T>& node) : data(node.data), prior(node.prior), next(node.next) {}



template <typename T>
class LinkList
{
public:
	LinkList();                                         //默认构造
	LinkList(const LinkList<T>& linklist);              //拷贝构造
	int getLength() const;                              //返回链表长度
	virtual ~LinkList();                                //析构函数
	void deleteCurrentNode();                           //删除当前结点
	void Clear();                                       //清空链表
	LinkList<T>& operator=(const LinkList<T>& linklist);//重载赋值运算
	void show() const;									//输出链表

protected:
	Node<T> *head;            //指向头结点的指针
	Node<T> *currentNode;     //一个指向当前结点的指针，便于函数操作
	int length;               //链表长度
};
#endif // !LINKLIST_H

template <typename T>
LinkList<T>::LinkList() :head(NULL), currentNode(NULL), length(0) {}



template <typename T>
LinkList<T>::LinkList(const LinkList<T>& linklist) :head(NULL), currentNode(NULL)
{
	*this = linklist;
}

template <typename T>
int LinkList<T>::getLength() const
{
	return length;
}


template <typename T>
LinkList<T>::~LinkList()
{
	Clear();
}

template <typename T>
void LinkList<T>::deleteCurrentNode()
{
	if (head == NULL || currentNode == NULL)
		return;
	if (length == 1)
	{
		Clear();
		return;
	}
	if (currentNode == head)
	{
		head->next->prior = head->prior;
		head->prior->next = head->next;
		head = head->next;
		delete currentNode;
		length--;
		return;
	}

	Node<T> *p = head;
	for(int i = 0; i < length; i++)
	{
		if (p->next == currentNode)
		{
			currentNode->next->prior = p;
			p->next = currentNode->next;
			delete currentNode;
			currentNode = p;
			length--;
			return;
		}
		p = p->next;
	}
}

template <typename T>
void LinkList<T>::Clear()
{
	currentNode = head;
	Node<T> *p = head;
	if (length == 0)
	{
		return;
	}
	for (int i = 0; i < length; i++)
	{
		currentNode = currentNode->next;
		delete p;
		p = currentNode;
	}
	length = 0;
	head = NULL;
}



template <typename T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T>& linklist)
{
	Clear();
	head = linklist->head;
	currentNode = linklist->currentNode;
	length = linklist->length;
	return *this;
}

template <typename T>
void LinkList<T>::show() const
{
	Node<T> *p = head;
	if (head == NULL)
		return;
	int num = length % 2 == 0 ? (length / 2) : (length / 2 + 1); 
	int x = 0, y = 0, judge = 0, count = 0;
	for (int i = 0; i < length; i++)
	{
		if (y == num  - 1)
		{
			judge = 1;
		}

		if (length <= 2 && i == 0)
		{
			y = 0;
			x = 0;
		}
		else if (length <= 2 && i == 1)
		{
			y = 0;
			x = 40;
		}
		else if (judge == 0)
		{
			y = i;
			x = 0;
		}
		else
		{
			y = i - num;
			x = 40;
		}
		gotoxy(x, y + 2);
		cout <<" "<<setfill(' ')<< left << setw(4) << ++count <<right << p->data;
		p = p->next;
	}
	gotoxy(0, num + 3);
}