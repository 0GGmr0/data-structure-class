#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"

int main(void)
{
	Time time;
	int hour, second, minute, choose,judge = 0;
	cout << "请设置初始时间" << endl;
	cout << "请依次输入时分秒:" << endl;
	cout << "请输入时：";
	cin >> hour;
	cout << "请输入分：";
	cin >> minute;
	cout << "请输入秒:";
	cin >> second;
	time.settime(hour, minute, second);
	time.show();
	while (judge == 0)
	{
		cout << "1 修改时" << endl;
		cout << "2 修改分" << endl;
		cout << "3 修改秒" << endl;
		cout << "4 退出" << endl;
		cout << "请输入选择";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			cout << "请输入时";
			cin >> hour;
			time.sethour(hour);
			time.show();
			break;

		}
		case 2:
		{
			cout << "请输入分";
			cin >> minute;
			time.setminute(minute);
			time.show();
			break;
		}
		case 3:
		{
			cout << "请输入秒";
			cin >> second;
			time.setsecond(second);
			time.show();
			break;
		}
		default:
			judge = 1;
		}
	}
	return 0;
}
