#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
class Book
{
	long int num; //���
	char bookname[40]; //����
	char publicname[40]; //������
	char name[20]; //����
	int nums;  //�����Ŀ
public:
	Book() { num = 0; bookname[0] = 0; publicname[0] = 0; name[0] = 0; }
	char * Getbookname(void) { return bookname; }
	char * Getpublicname(void) { return publicname; }
	char * Getname(void) { return name; }
	long Getnum(void) { return num; }
	void Setdata(long, char *, char *, char *);
	void Setbookname(const char *);
	void Show(void);
	int Getnums(void) { return nums; }
	void Showname(void);
	void Setnumszero(void) { nums = 0; }
	void Addnums(void) { nums++; }
	Book(long, char *, char *, char *);
};
void Book::Setdata(long nu, char *bn, char *p, char *n)
{
	num = nu; strcpy(bookname, bn);
	strcpy(publicname, p); strcpy(name, n);
}
void Book::Show(void)
{
	cout << "���:" << num << '\t' << "����:" << bookname << '\t';
	cout << "������:" << publicname << '\t' << "����:" << name << '\n';
}
void Book::Showname(void)
{
	cout << bookname << endl;
}
Book::Book(long nu, char * bp, char *p, char *n)
{
	Setdata(nu, bp, p, n);
}
void Book::Setbookname(const char *str)
{
	strcpy(bookname, str);
}

int main(void)
{
	int len;   //��¼����
	char temp[40]; //��Ϊ��ʱ�洢Ҫ����������
	Book b1, b2;
	b1.Setnumszero();
	b2.Setnumszero();
	long nu;
	char bn[40]; //����
	char pn[40]; //������
	char na[20]; //����
	vector<Book> book;
	ifstream file1;
	ofstream file3;
	char flag = 'y';
	while (flag == 'y' || flag == 'Y') //�� flag ����ѭ��
	{
		cout << "\t\t 1: ����������һ����!\n";
		cout << "\t\t 2: �����������һ����!\n";
		cout << "\t\t 3: �����߲���һ����!\n";
		cout << "\t\t 4: ����һ������!\n";
		cout << "\t\t 5: ���ͬһ������������������!\n ";
		cout << "\t\t 6: ���б�ĸ�ʽ����ļ��е���������!\n ";
		cout << "\t\t 7: �˳�!\n ����ѡ��: ";
		int f;
		cin >> f;
		switch (f)
		{
		case 1:
			cout << "����Ҫ���ҵ�������";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//������ʽ���ļ�
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
				{
					if (strcmp(b1.Getbookname(), bn) == 0) //��ʾ�����Ϣ
						b1.Show();
				}
			}
			file1.close();
			break;

		case 2:
			cout << "��������������֣� ";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//������ʽ���ļ�
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
				{
					if (strcmp(b1.Getpublicname(), bn) == 0) //��ʾ�����Ϣ
						b1.Show();
				}
			}
			file1.close();
			break;

		case 3:
			cout << "�������������֣� ";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//������ʽ���ļ�
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
				{
					if (strcmp(b1.Getbookname(), bn) == 0) //��ʾ�����Ϣ
						b1.Show();
				}
			}
			file1.close();
			break;

		case 4:
			cout << "������ţ�"; cin >> nu;
			cout << "����������"; cin >> bn;
			cout << "��������磺"; cin >> pn;
			cout << "�������ߣ�"; cin >> na;
			b1.Setdata(nu, bn, pn, na);
			b1.Addnums();
			file3.open("book.dat", ios::app | ios::binary);//������ʽ���ļ�
			file3.write((char*)&b1, sizeof(b1));
			file3.close();
			break;

		case 5://���ͬһ���������������
			cout << "��������������֣� ";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//������ʽ���ļ�
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
					if (strcmp(b1.Getpublicname(), bn) == 0) //��ʾ�����Ϣ
						b1.Showname();
			}
			file1.close();
			break;

		case 6: //���б�ĸ�ʽ����ļ��е���������!
			file1.open("book.dat", ios::in | ios::binary);//������ʽ���ļ�
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
					book.push_back(b1);
			}
			len = book.size();
			for (int i = 0; i < len - 1; i++)
				for (int j = i; j < len; j++)
					if (strcmp(book[i].Getbookname(), book[j].Getbookname()) > 0)
					{
						strcpy(temp,book[i].Getbookname());
						book[i].Setbookname(book[j].Getbookname());
						book[j].Setbookname(temp);
					}
			for (int i = 0; i < len; i++)
				book[i].Showname();
			file1.close();
			break;

		default: flag = 'n';
		}
	}
	return 0;
}
