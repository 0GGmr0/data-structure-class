#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "LinkList.h"
#include "Data.h"
#include <iomanip>
#include <fstream>


class Dictionary :public LinkList<Data>
{
public:
	void SortOnFrequency();													   //通过频率排序，如果频率相同则按照字母表顺序排序
	void InsertVector(const vector<Data>& data);							   //通过一个数组进行构造链表并进行排序
	void InsertWord(const string& wor);                                        //增加一个新的单词
	void showList() const;													   //输出所有单词
	int DeleteWord(const string& wor);										   //删除指定单词
	int FindWord(const string& wor);                                           //查找指定单词
	void showSingleWord(const string& wor);                                    //输出指定单词和其频率
	void ModifyWord(const string& str, const string& wor, const int& fre = -1);//修改指定单词为wor，且如果频率不为-1，那么就将频率也修改
	void AllDelete();														   //清空整个字典
	void writeToFile(ofstream& outfile);									   //重载文件写入file
private:
	void _qSort(Node<Data>* left, Node<Data>* right);
	bool _cmp(const Data & a, const Data & b)const;
	void Swap(Node<Data>*& p, Node<Data>*& t);
	//输出指定单词和频率
};

void Dictionary::showSingleWord(const string& wor)
{
	currentNode = head;
	for (int i = 0; i < length; i++)
	{
		if (currentNode->data.showWord() == wor)
		{
			cout << "单词：" << currentNode->data.showWord() <<"      "<< "频率：" << currentNode->data.showFrequency() << endl;
			return;
		}
		currentNode = currentNode->next;
	}
}
void Dictionary::writeToFile(ofstream& outfile)
{
	currentNode = head;
	for (int i = 0; i < length; i++)
	{
		outfile << left << setw(20) << currentNode->data.showWord() << right << setw(5) << currentNode->data.showFrequency() <<  endl;
		currentNode = currentNode->next;
	}
}

void Dictionary::AllDelete()
{
	Clear();
}

void Dictionary::ModifyWord(const string& str, const string& wor, const int& fre)
{
	if (FindWord(wor) == 1)
	{
		DeleteWord(str);
		//currentNode->data.Setfrequency(currentNode->data.showFrequency() - 1);
		if(fre != -1)
			currentNode->showData().Setfrequency(fre);
		return;
	}
	FindWord(str);
	currentNode->data.Setfrequency(1);

	currentNode->showData().SetWord(wor);
	if (fre != -1)
	{
		currentNode->showData().Setfrequency(fre);
	}
}

int Dictionary::FindWord(const string& wor)
{
	currentNode = head;
	for (int i = 0; i < length; i++)
	{
		if (currentNode->showData().showWord() == wor)
		{
			currentNode->data.Setfrequency(currentNode->data.showFrequency() + 1);
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}

int Dictionary::DeleteWord(const string& wor)
{
	currentNode = head;
	for (int i = 0; i < length; i++)
	{
		if (currentNode->showData().showWord() == wor)
		{
			deleteCurrentNode();
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}

void Dictionary::InsertWord(const string& wor)
{
	if (length == 0)
	{
		Data da(wor, 1);
		head = new Node<Data>(da);
		head->next = head;
		head->prior = head;
		length++;
		return;
	}
	currentNode = head;
	for (int i = 0; i < length; i++)
	{
		if (currentNode->showData().showWord() == wor)
		{
			currentNode->showData().Setfrequency(currentNode->showData().showFrequency() + 1);
			return;
		}
		if(i <length - 1)
			currentNode = currentNode->next;
	}
	Data da(wor, 1);
	Node<Data> *p = new Node<Data>(da);
	currentNode->next = p;
	currentNode->next->prior = currentNode;
	currentNode->next->next = head;
	head->prior = currentNode->next;
	length++;
	SortOnFrequency();
}

void Dictionary::InsertVector(const vector<Data>& data)
{
	int Size = data.size();
	head = new Node<Data>(data[0]);
	head->prior = head->next = head;
	currentNode = head;
	for (int i = 1; i < Size; i++)
	{
		Node<Data> *da = new Node<Data>(data[i]);
		currentNode->next = da;
		currentNode->next->prior = currentNode;
		currentNode = currentNode->next;
	}
	length = Size;
	currentNode->next = head;
	head->prior = currentNode;
}


void Dictionary::showList() const
{
	cout << setfill(' ') << setw(29) << " " << "字典目录" << endl;
	cout << "序号" << setw(4) <<" "<< "单词" << setw(12) << " "<< "频率" ;
	cout << setw(12) << " " <<"序号" << setw(4) << " " << "单词" << setw(12) << " " << "频率" << endl;
	show();
}

void Dictionary::SortOnFrequency()
{
	Node<Data> *p = head;
	for (; p->next != head; p = p->next);
	_qSort(this->head, p);
}

void Dictionary::_qSort(Node<Data> *left, Node<Data> *right) {
	if (left == right)
		return;
	Node<Data> *l = left, *r = right;
	Data key = left->data;
	while (l != r) {

		while (r != l && !_cmp(r->data, key))
			r = r->prior;
		while (r != l && _cmp(l->data, key))
			l = l->next;
		if (left == l)
			left = r;
		if (right == r)
			right = l;
		Swap(l, r);
	}
	if (right == l)
		right = left;
	Swap(left, l);
	if (l != left)
		_qSort(left, l->prior);
	if (l != right)
		_qSort(l->next, right);
}
bool Dictionary::_cmp(const Data &a, const Data &b)const
{
	if (a.showFrequency() == b.showFrequency())
		return a.showWord() <= b.showWord();
	return a.showFrequency() >= b.showFrequency();
}

void Dictionary::Swap(Node <Data> *&p, Node<Data> *&t)//p前，t后，交换后指向位置也改变
{
	if (p == t)
		return;
	Node<Data> *temp;
	goto flag;
	if (t->next == head) //t结点是否为尾结点  
	{
		if (p->next == t) //p,t结点是否相邻  
		{
			//与尾结点相邻的交换  
			t->next = p;
			t->prior = p->prior;
			p->next = head;
			p->prior->next = t;
			p->prior = t;
		}
		else
		{
			//与尾结点不相邻的交换  
			t->next = p->next;
			t->prior->next = p;
			temp = t->prior;
			t->prior = p->prior;
			p->next->prior = t;
			p->next = head;
			p->prior->next = t;
			p->prior = temp;
		}
	}
	else
	{
	flag:
		if (p->next == t) //p,t结点是否相邻  
		{
			//相邻的交换  
			t->next->prior = p;
			temp = t->next;
			t->next = p;
			t->prior = p->prior;
			p->next = temp;
			p->prior->next = t;
			p->prior = t;
		}
		else
		{
			//不相邻的交换 
			t->next->prior = p;
			temp = t->next;
			t->next = p->next;
			p->next->prior = t;
			p->next = temp;
			t->prior->next = p;
			temp = t->prior;
			t->prior = p->prior;
			p->prior->next = t;
			p->prior = temp;
		}
	}
	if (p == head)
		head = t;
	temp = p;
	p = t;
	t = temp;
}




#endif
