#include "SeqList.h"	// 顺序表类
#include<conio.h>
int main(void)
{
	char c = '*';
	SeqList<int> la(6);
	int e;
	int i;
	Status sta;

	while (c != '0')
	{
		cout << endl << "1. 生成线性表.";
		cout << endl << "2. 显示线性表.";
		cout << endl << "3. 取指定元素.";
		cout << endl << "4. 设置元素值.";
		cout << endl << "5. 删除元素.";
		cout << endl << "6. 插入元素.";
		cout << endl << "7. 求线性表长度.";
		cout << endl << "8. min";
		cout << endl << "9. max";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~9):";
		cin >> c;
		switch (c) {
		case '1':
			la.Clear();
			sta = SUCCESS;
			cout << endl << "输入e(e = 0时退出):";
			cin >> e;
			while (e != 0 && sta != OVER_FLOW) {
				sta = la.InsertElem(e);
				if (sta == OVER_FLOW)
					cout << "线性表已满." << endl;
				else
					cin >> e;
			}
			break;
		case '2':
			la.Traverse(Write<int>);
			break;
		case '3':
			cout << endl << "输入元素位置:";
			cin >> i;
			if (la.GetElem(i, e) == NOT_PRESENT)
				cout << "元素不存储." << endl;
			else
				cout << "元素:" << e << endl;
			break;
		case '4':
			cout << endl << "输入位置:";
			cin >> i;
			cout << endl << "输入元素值:";
			cin >> e;
			if (la.SetElem(i, e) == RANGE_ERROR)
				cout << "位置范围错." << endl;
			else
				cout << "设置成功." << endl;
			break;
		case '5':
			cout << endl << "输入位置:";
			cin >> i;
			if (la.DeleteElem(i, e) == RANGE_ERROR)
				cout << "位置范围错." << endl;
			else
				cout << "被删除元素值:" << e << endl;
			break;
		case '6':
			cout << endl << "输入位置:";
			cin >> i;
			cout << endl << "输入元素值:";
			cin >> e;
			sta = la.InsertElem(i, e);

			if (sta == RANGE_ERROR)
				cout << "位置范围错." << endl;
			else if (sta == OVER_FLOW)
				cout << "线性表已满." << endl;
			else
				cout << "插入成功." << endl;
			break;
		case '7':
			cout << endl << "线性表的长度为:" << la.GetLength() << endl;
			break;
		case '8':
			cout << endl << "顺序表中元素值最小的数据元素序号" << la.Min() << endl;
			break;
		case '9':
			cout << endl << "顺序表中元素值最大的数据元素序号" << la.Max() << endl;
			break;
		}
		
	}

	system("PAUSE");        		// 调用库函数system()，暂停程序运行 
	return 0;               		// 返回操作系统
}

//在顺序表类模板中增加成员函数 max()和 min()，它们分别返回顺序表中元素值最大的数据元素序号


