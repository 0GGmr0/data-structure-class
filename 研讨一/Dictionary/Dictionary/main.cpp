#define _CRT_SECURE_NO_WARNINGS
#include "Dictionary.h"
#include <iomanip>
#include <cstdlib>
#include <fstream>

void ShowBackground();															//�������
void Exit();																	//�˳�����
void replaceToBlank(vector<char>& lists);										//�������е��ַ����ķ���ĸ�ĳɿո�
void readArticleAndToWords(const vector<char>& lists, vector<string>& words);   //��ȡ���²��Ұѵ��ʴ浽�ַ�����
void writeToData(vector<string>& words, vector<Data>& da);						//�ѵ���Ū��data������ҵõ�Ƶ��
void insertNewWord(Dictionary& dic);											//����һ���µ���
void deleteNewWord(Dictionary& dic);											//ɾ��һ���µ���
void modifyWord(Dictionary& dic);												//�޸�һ������
void FindNewWord(Dictionary& dic);                                              //����һ������
void DeleteAll(Dictionary& dic);												//����ֵ�
void Tofile(Dictionary &dic);													//������ļ�
void ChangeToSmall(string& str);                                                //�����ʴ�д
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
		vector<string> words; //������ŵ���
		vector<Data> da;      //�ѵ��ʺ�Ƶ�ʴ���data����

		ifstream infile;
		infile.open("Dictionary.in");
		vector<char> lists;   //�����洢�ַ���
		infile.unsetf(ios::skipws);
		if (infile.peek() == EOF)
		{
			cout << "�ļ�Ϊ�գ�" << endl;
			return 0;
		}
		while (infile.peek() != EOF)
		{
			char ch;
			infile >> ch;
			lists.push_back(ch);
		}
		infile.close();
		replaceToBlank(lists);     //�ÿո�������ĸ������,���Ұ����еĴ�д��ĸת����Сд��ĸ
		readArticleAndToWords(lists, words);
		writeToData(words, da);

		Dictionary dic; //���������洢���ݵĶ���

		dic.InsertVector(da);//��������
		dic.SortOnFrequency();//����������
		int judge = 0;
		while (true)
		{
			if (judge == 1) break;
			system("cls");
			dic.showList();//��ʾ����
			cout << endl << "������Ҫִ�е��ֵ�Ĺ���:" << endl;
			cout << "1 - ���ӵ���    2 - ɾ������    3 - �޸ĵ���    4 - ���ҵ���" << endl;
			cout << "5 - ����ֵ�    0 - �˳��ֵ�" << endl;
			cout << "���������ѡ��:  ";
			cin >> choose;
			char ch;
			while ((ch = getchar()) != '\n'&& ch != EOF);
			system("cls");
			switch (choose)
			{
			case '1': insertNewWord(dic); break;			 //�����µ��ʺ���Ƶ��
			case '2': deleteNewWord(dic); break;             //ɾ��ָ������
			case '3': modifyWord(dic);    break;             //�޸ĵ���
			case '4': FindNewWord(dic);   break;			 //���ҵ���
			case '5': DeleteAll(dic);     break;			 //�������
			default:  Exit(); judge = 1;  break;             //�ص����˵�
			}
		}
		Tofile(dic);
	}

	return 0;
}
void FindNewWord(Dictionary& dic)
{
	string str;
	cout << "��������Ҫ���ҵĵ���(�����ʲ����ڣ���ͣ��3��󷵻�������): ";
	cin >> str;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	if (dic.FindWord(str) == 0)
	{
		cout << "��Ǹ��û��������ʣ�������󷵻�������" << endl;
		Sleep(3000);
	}
	else
	{
		dic.showSingleWord(str);
		dic.SortOnFrequency();
		cout << "����󷵻�������" << endl;
		Sleep(3000);
	}
}

void DeleteAll(Dictionary& dic)
{
	string judge;
	cout << "����ȷ���Ƿ����Ҫ����ֵ�,��������yes��������no: ";
	cin >> judge;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	while (judge != "yes" && judge != "no")
	{
		cout << "�������������밴����ȷ��ʽ����" << endl;
		cout << "����������: ";
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
	cout << "��������Ҫ�޸ĵĵ���(�����ʲ����ڣ���ͣ��3��󷵻�������): ";
	string str;
	char ch;
	cin >> str;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	if (dic.FindWord(str) == 0)
	{
		cout << "��Ǹ��û��������ʣ�������󷵻�������" << endl;
		Sleep(3000);
		return;
	}
	cout << "���������Ե��ʵ��޸�: ";
	string Str;
	cin >> Str;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(Str);
	cout << "��ȷ���Ƿ�Ҫ�޸ĵ���Ƶ�ʣ������������yes����������no"<<endl;
	string judge;
	cout << "����������ѡ��: ";
	cin >> judge;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	while (judge != "yes" && judge != "no")
	{
		cout << "�������������밴����ȷ��ʽ����" << endl;
		cout << "����������: ";
		cin >> judge;
		while ((ch = getchar()) != '\n'&& ch != EOF);
	}
	if (judge == "yes")
	{
		cout << "���������޸ĺ��Ƶ��(Ƶ�ʱ�����ڵ���1): ";
		int fre;
		cin >> fre;
		while (fre < 1)
		{
			cout << "�������������밴����ȷ��ʽ����" << endl;
			cout << "����������: ";
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
	cout << "��������Ҫɾ���ĵ���(�����ʲ����ڣ���ͣ��3��󷵻�������): ";
	string str;
	cin >> str;
	char ch;
	while ((ch = getchar()) != '\n'&& ch != EOF);
	ChangeToSmall(str);
	if (dic.DeleteWord(str) == 0)
	{
		cout << "��Ǹ��û��������ʣ�������󷵻�������" << endl;
		Sleep(3000);
	}
}

void insertNewWord(Dictionary& dic)
{
	string str;
	cout << "������Ҫ����ĵ���(�������Ѵ��ڣ�����Ƶ�ʼ�1): ";
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
	cout << '*' << setw(18) << ' ' << "��ӭʹ���ֵ�" << setw(19) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << '*' << setw(49) << '*' << endl;
	cout << setfill('*') << setw(50) << '*' << endl;
	cout << "��ѡ������ 1--��ȡ�ı�   0--�˳��ֵ�" << endl << endl;
	cout << "�밴�չ�����ʾ����:  ";
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
	for (int i = 0; i<lists.size(); i++)//�ѷ�Ӣ����ĸ�滻Ϊ�ո�
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

	string temporyList;        //����ַ���
	string s;                  //��ȡ�ַ����ĵ���
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

