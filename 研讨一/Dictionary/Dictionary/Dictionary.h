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
	void SortOnFrequency();													   //ͨ��Ƶ���������Ƶ����ͬ������ĸ��˳������
	void InsertVector(const vector<Data>& data);							   //ͨ��һ��������й���������������
	void InsertWord(const string& wor);                                        //����һ���µĵ���
	void showList() const;													   //������е���
	int DeleteWord(const string& wor);										   //ɾ��ָ������
	int FindWord(const string& wor);                                           //����ָ������
	void showSingleWord(const string& wor);                                    //���ָ�����ʺ���Ƶ��
	void ModifyWord(const string& str, const string& wor, const int& fre = -1);//�޸�ָ������Ϊwor�������Ƶ�ʲ�Ϊ-1����ô�ͽ�Ƶ��Ҳ�޸�
	void AllDelete();														   //��������ֵ�
	void writeToFile(ofstream& outfile);									   //�����ļ�д��file
private:
	void _qSort(Node<Data>* left, Node<Data>* right);
	bool _cmp(const Data & a, const Data & b)const;
	void Swap(Node<Data>*& p, Node<Data>*& t);
	//���ָ�����ʺ�Ƶ��
};

void Dictionary::showSingleWord(const string& wor)
{
	currentNode = head;
	for (int i = 0; i < length; i++)
	{
		if (currentNode->data.showWord() == wor)
		{
			cout << "���ʣ�" << currentNode->data.showWord() <<"      "<< "Ƶ�ʣ�" << currentNode->data.showFrequency() << endl;
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
	cout << setfill(' ') << setw(29) << " " << "�ֵ�Ŀ¼" << endl;
	cout << "���" << setw(4) <<" "<< "����" << setw(12) << " "<< "Ƶ��" ;
	cout << setw(12) << " " <<"���" << setw(4) << " " << "����" << setw(12) << " " << "Ƶ��" << endl;
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

void Dictionary::Swap(Node <Data> *&p, Node<Data> *&t)//pǰ��t�󣬽�����ָ��λ��Ҳ�ı�
{
	if (p == t)
		return;
	Node<Data> *temp;
	goto flag;
	if (t->next == head) //t����Ƿ�Ϊβ���  
	{
		if (p->next == t) //p,t����Ƿ�����  
		{
			//��β������ڵĽ���  
			t->next = p;
			t->prior = p->prior;
			p->next = head;
			p->prior->next = t;
			p->prior = t;
		}
		else
		{
			//��β��㲻���ڵĽ���  
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
		if (p->next == t) //p,t����Ƿ�����  
		{
			//���ڵĽ���  
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
			//�����ڵĽ��� 
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
