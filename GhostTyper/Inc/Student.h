#pragma once
#include"Configure.h"
using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 number, const std::string& name, const std::string& intime);
	std::string formatInfo();//格式化数据
 

		//显示信息
	void display();
	//把学生的所有信息格式化成字符串

	void formatWrite(const std::string& str);
public:
	bool operator==(const Student& right) const;
	bool operator>(const Student& right) const;
	bool operator<(const Student& right) const;

public:
	//文章名称            文章字数           文章录入时间
	std::string name;          uint32 number;          std::string intime;
};

