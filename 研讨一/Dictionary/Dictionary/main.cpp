#define _CRT_SECURE_NO_WARNINGS
#include "Dictionary.h"
#include <iomanip>
#include <cstdlib>
#include <fstream>

void ShowBackground();															//进入界面
void Exit();																	//退出界面
void replaceToBlank(vector<char>& lists);										//将文章中的字符串的非字母改成空格
void readArticleAndToWords(const vector<char>& lists, vector<string>& words);   //读取文章并且把单词存到字符串里
void writeToData(vector<string>& words, vector<Data>& da);						//把单词弄到data类对象并且得到频率
void insertNewWord(Dictionary& dic);											//插入一个新单词
void deleteNewWord(Dictionary& dic);											//删除一个新单词
void modifyWord(Dictionary& dic);												//修改一个单词
void FindNewWord(Dictionary& dic);                                              //查找一个单词
void DeleteAll(Dictionary& dic);												//清空字典
void Tofile(Dictionary &dic);													//输出到文件
void ChangeToSmall(string& str);                                                //将单词大写
int main(void)
{
	ShowBackground();
	char choose;
	cin >> choose;
	if (choose != '1')
	{
		Exit();
		return 0;
	}
	else
	{
		vector<string> words; //用来存放单词
		vector<Data> da;      //把单词和频率存入data对象

		ifstream infile;
		infile.open("Dictionary.in");
		vector<char> lists;   //用来存储字符串
		infile.unsetf(ios::skipws);
		if (infile.peek() == EOF)
		{
			cout << "文件为空！" << endl;
			return 0;
		}
		while (infile.peek() != EOF)
		{
			char ch;
			infile >> ch;
			lists.push_back(ch);
		}
		infile.close();
		replaceToBlank(lists);     //用空格代替除字母外的情况,并且把所有的大写字母转化成小写字母
		readArticleAndToWords(lists, words);
		writeToData(words, da);

		Dictionary dic; //真正用来存储数据的对象

		dic.InsertVector(da);//创建链表
		dic.SortOnFrequency();//对链表排序
		int judge = 0;
		while (true)
		{
			if (judge == 1) break;
			system("cls");
			dic.showList();//显示数据
			cout << endl << "请输入要执行的字典的功能:" << endl;
			cout << "1 - 增加单词    2 - 删除单词    3 - 修改单词    4 - 查找单词" << endl;
			cout << "5 - 清空字典    0 - 退出字典" << endl;
			cout << "请输入你的选择:  ";
			cin >> choose;
			char ch;
			while ((ch = getchar()) != '\n'&& ch != EOF);
			system("cls");
			switch (choose)
			{
			case '1': insertNewWord(dic); break;			 //增加新单词和其频率
			case '2': deleteNewWord(dic); break;             //删除指定单词
			case '3': modifyWord(dic);    break;             //修改单词
			case '4': FindNewWord(dic);   break;			 //查找单词
			case '5': DeleteAll(dic);     break;			 //清空所有
			default:  Exit(); judge = 1;  break;             //回到主菜单
			}
		}
		Tofile(dic);
	}

	return 0;
}
void FindNewWord(Dictionary& dic)
{
	string str;
	cout << "请输入你要查找的单词(若单词不存在，则停顿3秒后返回主界面): ";
	cin >> str;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	if (dic.FindWord(str) == 0)
	{
		cout << "抱歉，没有这个单词，在三秒后返回主界面" << endl;
		Sleep(3000);
	}
	else
	{
		dic.showSingleWord(str);
		dic.SortOnFrequency();
		cout << "三秒后返回主界面" << endl;
		Sleep(3000);
	}
}

void DeleteAll(Dictionary& dic)
{
	string judge;
	cout << "请您确定是否真的要清空字典,是则输入yes，否输入no: ";
	cin >> judge;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	while (judge != "yes" && judge != "no")
	{
		cout << "您的输入有误，请按照正确格式输入" << endl;
		cout << "请重新输入: ";
		cin >> judge;
		while ((ch = getchar()) != '\n'&& ch != EOF);
	}
	if (judge == "yes")
	{
		dic.AllDelete();
	}
}

void modifyWord(Dictionary& dic)
{
	cout << "请输入你要修改的单词(若单词不存在，则停顿3秒后返回主界面): ";
	string str;
	char ch;
	cin >> str;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	if (dic.FindWord(str) == 0)
	{
		cout << "抱歉，没有这个单词，在三秒后返回主界面" << endl;
		Sleep(3000);
		return;
	}
	cout << "请输入您对单词的修改: ";
	string Str;
	cin >> Str;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(Str);
	cout << "请确定是否要修改单词频率，如果是请输入yes，否请输入no"<<endl;
	string judge;
	cout << "请输入您的选择: ";
	cin >> judge;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	while (judge != "yes" && judge != "no")
	{
		cout << "您的输入有误，请按照正确格式输入" << endl;
		cout << "请重新输入: ";
		cin >> judge;
		while ((ch = getchar()) != '\n'&& ch != EOF);
	}
	if (judge == "yes")
	{
		cout << "请输入您修改后的频率(频率必须大于等于1): ";
		int fre;
		cin >> fre;
		while (fre < 1)
		{
			cout << "您的输入有误，请按照正确格式输入" << endl;
			cout << "请重新输入: ";
			cin >> fre;
			while ((ch = getchar()) != '\n'&& ch != EOF);
		}
		dic.ModifyWord(str, Str, fre);
	}
	else
	{
		dic.ModifyWord(str, Str);
	}
	dic.SortOnFrequency();
}

void deleteNewWord(Dictionary& dic)	
{
	cout << "请输入你要删除的单词(若单词不存在，则停顿3秒后返回主界面): ";
	string str;
	cin >> str;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	if (dic.DeleteWord(str) == 0)
	{
		cout << "抱歉，没有这个单词，在三秒后返回主界面" << endl;
		Sleep(3000);
	}
}

void insertNewWord(Dictionary& dic)
{
	string str;
	cout << "请输入要加入的单词(若单词已存在，则其频率加1): ";
	cin >> str;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	dic.InsertWord(str);
	dic.SortOnFrequency();
}

void ShowBackground()
{
	cout << setfill('*') << setw(50) << '*' << endl;
	cout << '*' << setfill(' ') << setw(49) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << '*' << setw(18) << ' ' << "欢迎使用字典" << setw(19) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << setfill('*') << setw(50) << '*' << endl;
	cout << "请选择输入 1--读取文本   0--退出字典" << endl << endl;
	cout << "请按照功能提示输入:  ";
}

void Exit()
{
	system("cls");
	cout << setfill('*') << setw(50) << '*' << endl;
	cout << setfill(' ');
	cout << right << '*' << setw(49) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << '*' << setw(20) << " " << "Good Bye" << setw(21) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << setfill('*') << setw(50) << '*' << endl;
}

void replaceToBlank(vector<char>& lists)
{
	for (int i = 0; i<lists.size(); i++)//把非英文字母替换为空格
	{
		if (!(lists[i] >= 'a'&&lists[i] <= 'z' || lists[i] >= 'A'&&lists[i] <= 'Z' || lists[i] == '\''))
		{
			lists[i] = ' ';
		}
		if (lists[i] >= 'A'&&lists[i] <= 'Z')
		{
			lists[i] += 32;
		}
	}
}

void readArticleAndToWords(const vector<char>& lists, vector<string>& words)
{

	string temporyList;        //存放字符串
	string s;                  //读取字符串的单词
	int _size = lists.size();
	for (int i = 0; i < _size; i++)
	{
		temporyList += lists[i];
	}
	istringstream is(temporyList);
	while (is >> s)
	{
		words.push_back(s);
	}
}

void writeToData(vector<string>& words, vector<Data>& da)
{
	int Size = words.size();

	for (int i = 0; i < Size; i++)
	{
		int judge = 0;
		int _size = da.size();
		for (int j = 0; j < _size; j++)
			if (words[i] == da[j].showWord())
			{
				judge++;
				break;
			}
		if (judge == 0)
		{
			Data da0(words[i], 1);
			da.push_back(da0);
		}
	}
}

void ChangeToSmall(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
}

void Tofile(Dictionary &dic)
{
	ofstream outfile("Dictionary.out");
	dic.writeToFile(outfile);
	outfile.close();
}

