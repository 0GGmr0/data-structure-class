#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"

int main(void)
{
	Time time;
	int hour, second, minute, choose,judge = 0;
	cout << "�����ó�ʼʱ��" << endl;
	cout << "����������ʱ����:" << endl;
	cout << "������ʱ��";
	cin >> hour;
	cout << "������֣�";
	cin >> minute;
	cout << "��������:";
	cin >> second;
	time.settime(hour, minute, second);
	time.show();
	while (judge == 0)
	{
		cout << "1 �޸�ʱ" << endl;
		cout << "2 �޸ķ�" << endl;
		cout << "3 �޸���" << endl;
		cout << "4 �˳�" << endl;
		cout << "������ѡ��";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			cout << "������ʱ";
			cin >> hour;
			time.sethour(hour);
			time.show();
			break;

		}
		case 2:
		{
			cout << "�������";
			cin >> minute;
			time.setminute(minute);
			time.show();
			break;
		}
		case 3:
		{
			cout << "��������";
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
