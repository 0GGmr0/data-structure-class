#pragma once
#ifndef DATA_H
#define DATA_H
#include<iostream>
#include<string>
#include<sstream>
#include <vector>
#include <iomanip>
using namespace std;
class Data
{
public:
	Data(const string Word = "", const int Frequency = 0);                    //��ֵ���캯��
	Data(const Data& data);                                            							    //��������
	friend ostream& operator << (ostream& out, const Data& data);      								//�������������
	void Setfrequency(int fre);                                                                     //����Ƶ��
	string showWord() const;                                                                        //��ʾ����
	int showFrequency() const;                                                                      //��ʾƵ��
	void SetWord(const string& wd);                                                                 //���õ���

private:
	string word;   //����
	int frequency; //Ƶ��
};


void Data::SetWord(const string& wd)
{
	word = wd;
}

int Data::showFrequency() const
{
	return frequency;
}

string Data::showWord() const
{
	return word;
}

void Data::Setfrequency(int fre)
{
	frequency = fre;
}
Data::Data(const string Word, const int Frequency)
{
	word = Word;
	frequency = Frequency;
}

Data::Data(const Data& data) :word(data.word), frequency(data.frequency){}

ostream& operator << (ostream& out, const Data& data)
{
	out << setfill(' ') << setw(3)<<" "<< left << setw(17) << data.word << setw(5) << data.frequency << right;
	return out;
}
#endif

