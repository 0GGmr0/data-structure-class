#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "Assistance.h"
struct student
{
private:
	string id;
	string name;
	string gender;
	string classroom;
	string phone;
public:
	student(string Id = "", string Name = "", string Gender = "", string Classroom = "", string Phone = "")
		:id(Id), name(Name), gender(Gender), classroom(Classroom), phone(Phone) {}

	student(const struct student& s) :id(s.id), name(s.name), gender(s.gender), classroom(s.classroom), phone(s.phone) {}

	friend istream& operator >> (istream& in, struct student& s)
	{
		in >> s.id >> s.name >> s.gender >> s.classroom >> s.phone;
		return in;
	}

	friend ostream& operator<<(ostream& out, const struct student& s)
	{
		out << s.id << "\t" << s.name << "\t" << s.gender << "\t" << s.classroom << "\t" << s.phone << endl;
		return out;
	}

	friend bool operator<(const struct student& s1, const struct student& s2) {
		if (s1.id < s2.id)
			return true;
		else if (s1.name < s2.name)
			return true;
		else if (s1.gender < s2.gender)
			return true;
		else if (s1.phone == s2.phone)
			return true;
		else if (s1.classroom == s2.classroom)
			return true;
		else
			return false;
	}

	friend bool operator!=(const struct student& s1, const struct student& s2) {
		if (s1.id == s2.id && s1.name == s2.name && s1.gender == s2.gender && s1.phone == s2.phone && s1.classroom == s2.classroom)
			return false;
		else
			return true;
	}
};

//学号、姓名、性别、班级和电话号码等。用描述学生信息的结构体作为线性表的数据元素类型测试顺序表。

#endif // !STUDENT_H

