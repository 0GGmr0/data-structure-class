#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
class Book
{
	long int num; //书号
	char bookname[40]; //书名
	char publicname[40]; //出版社
	char name[20]; //作者
	int nums;  //书的数目
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
	cout << "书号:" << num << '\t' << "书名:" << bookname << '\t';
	cout << "出版社:" << publicname << '\t' << "作者:" << name << '\n';
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
	int len;   //记录长度
	char temp[40]; //作为临时存储要交换的内容
	Book b1, b2;
	b1.Setnumszero();
	b2.Setnumszero();
	long nu;
	char bn[40]; //书名
	char pn[40]; //出版社
	char na[20]; //作者
	vector<Book> book;
	ifstream file1;
	ofstream file3;
	char flag = 'y';
	while (flag == 'y' || flag == 'Y') //由 flag 控制循环
	{
		cout << "\t\t 1: 按书名查找一本书!\n";
		cout << "\t\t 2: 按出版社查找一本书!\n";
		cout << "\t\t 3: 按作者查找一本书!\n";
		cout << "\t\t 4: 加入一本新书!\n";
		cout << "\t\t 5: 输出同一出版社出版的所有书名!\n ";
		cout << "\t\t 6: 按列表的格式输出文件中的所有书名!\n ";
		cout << "\t\t 7: 退出!\n 输入选择: ";
		int f;
		cin >> f;
		switch (f)
		{
		case 1:
			cout << "输入要查找的书名：";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//按读方式打开文件
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
				{
					if (strcmp(b1.Getbookname(), bn) == 0) //显示书的信息
						b1.Show();
				}
			}
			file1.close();
			break;

		case 2:
			cout << "请输入出版社名字： ";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//按读方式打开文件
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
				{
					if (strcmp(b1.Getpublicname(), bn) == 0) //显示书的信息
						b1.Show();
				}
			}
			file1.close();
			break;

		case 3:
			cout << "请输入作者名字： ";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//按读方式打开文件
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
				{
					if (strcmp(b1.Getbookname(), bn) == 0) //显示书的信息
						b1.Show();
				}
			}
			file1.close();
			break;

		case 4:
			cout << "输入书号："; cin >> nu;
			cout << "输入书名："; cin >> bn;
			cout << "输入出版社："; cin >> pn;
			cout << "输入作者："; cin >> na;
			b1.Setdata(nu, bn, pn, na);
			b1.Addnums();
			file3.open("book.dat", ios::app | ios::binary);//增补方式打开文件
			file3.write((char*)&b1, sizeof(b1));
			file3.close();
			break;

		case 5://输出同一出版社的所有书名
			cout << "请输入出版社名字： ";
			cin >> bn;
			file1.open("book.dat", ios::in | ios::binary);//按读方式打开文件
			while (!file1.eof())
			{
				int n;
				file1.read((char *)&b1, sizeof(Book));
				n = file1.gcount();
				if (n == sizeof(Book))
					if (strcmp(b1.Getpublicname(), bn) == 0) //显示书的信息
						b1.Showname();
			}
			file1.close();
			break;

		case 6: //按列表的格式输出文件中的所有书名!
			file1.open("book.dat", ios::in | ios::binary);//按读方式打开文件
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
