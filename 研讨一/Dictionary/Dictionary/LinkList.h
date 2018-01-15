#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H
#include <cstddef>
#include <assert.h>
#include <windows.h>

void gotoxy(int x, int y)  //���ƹ��λ��
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
	Node();                                                      //Ĭ�Ϲ���
	Node(T Data, Node<T> *Prior = NULL, Node<T> *Next = NULL); 	 //��ֵ����
	Node(const Node<T>& node);                                   //��������
	//void ModifyData(const Node<T>& node);                        //�޸�data
	//void ModifynNext(const Node<T>& Next);                       //�޸�nextָ��
	//void Modifunprior(const Node<T>& Prior);                     //�޸�priorָ��
	T& showData();												 //չʾ����data
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
	LinkList();                                         //Ĭ�Ϲ���
	LinkList(const LinkList<T>& linklist);              //��������
	int getLength() const;                              //����������
	virtual ~LinkList();                                //��������
	void deleteCurrentNode();                           //ɾ����ǰ���
	void Clear();                                       //�������
	LinkList<T>& operator=(const LinkList<T>& linklist);//���ظ�ֵ����
	void show() const;									//�������

protected:
	Node<T> *head;            //ָ��ͷ����ָ��
	Node<T> *currentNode;     //һ��ָ��ǰ����ָ�룬���ں�������
	int length;               //������
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