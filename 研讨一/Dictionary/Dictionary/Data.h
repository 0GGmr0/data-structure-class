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
	Data(const string Word = "", const int Frequency = 0);                    //赋值构造函数
	Data(const Data& data);                                            							    //拷贝构造
	friend ostream& operator << (ostream& out, const Data& data);      								//重载输出流函数
	void Setfrequency(int fre);                                                                     //设置频率
	string showWord() const;                                                                        //显示单词
	int showFrequency() const;                                                                      //显示频率
	void SetWord(const string& wd);                                                                 //设置单词

private:
	string word;   //单词
	int frequency; //频率
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

