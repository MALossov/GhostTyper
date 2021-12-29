#pragma once
#include"Configure.h"
using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 number, const std::string& name, const std::string& intime);
	std::string formatInfo();//��ʽ������
 

		//��ʾ��Ϣ
	void display();
	//��ѧ����������Ϣ��ʽ�����ַ���

	void formatWrite(const std::string& str);
public:
	bool operator==(const Student& right) const;
	bool operator>(const Student& right) const;
	bool operator<(const Student& right) const;

public:
	//��������            ��������           ����¼��ʱ��
	std::string name;          uint32 number;          std::string intime;
};

