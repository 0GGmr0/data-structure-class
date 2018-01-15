//1．定义一个时间类 Time，能提供和设置由时、分、秒组成的时间，并编出应用程序，
//定义时间对象，设置时间，输出该对象提供的时间。
#define _CRT_SECURE_NO_WARNINGS
#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;

class Time
{
private:
	int hour;
	int minute;
	int second;
public:
	void show();
	Time(int Hour = 0, int Minute = 0,int Second = 0);
	void settime(int Hour = 0, int Minute = 0, int Second = 0);
	void sethour(int Hour);
	void setminute(int Minute);
	void setsecond(int Second);
};

void Time::show()
{
	cout << "当前时间为  ";
	if (hour > 10)
		cout << hour;
	else
		cout << "0" << hour;
	cout << ":";
	if (minute > 10)
		cout << minute;
	else
		cout << "0" << minute;
	cout << ":";
	if (second > 10)
		cout << second;
	else
		cout << "0" << second;
	cout << endl;
}

Time::Time(int Hour, int Minute, int Second) :hour(Hour), minute(Minute), second(Second)
{
	if (second >= 60)
		second = 59;
	if (second < 0)
		second = 0;
	if (minute >= 60)
		minute = 59;
	if (minute < 0)
		minute = 0;
	if (hour >= 24)
		hour = 23;
	if (hour < 0)
		hour = 0;
}

void Time::settime(int Hour, int Minute, int Second)
{
	hour = Hour;
	minute = Minute;
	second = Second;
	if (second >= 60)
		second = 59;
	if (second < 0)
		second = 0;
	if (minute >= 60)
		minute = 59;
	if (minute < 0)
		minute = 0;
	if (hour >= 24)
		hour = 23;
	if (hour < 0)
		hour = 0;
}

void Time::sethour(int Hour)
{
	hour = Hour;
	if (hour >= 24)
		hour = 23;
	if (hour < 0)
		hour = 0;
}

void Time::setminute(int Minute)
{
	minute = Minute;
	if (minute >= 60)
		minute = 59;
	if (minute < 0)
		minute = 0;
}

void Time::setsecond(int Second)
{
	second = Second;
	if (second >= 60)
		second = 59;
	if (second < 0)
		second = 0;
}

#endif // !TIME_H


