#include "Student.h"
#include<sstream>
#include<time.h>
Student::Student() :number(number), name(name), intime(intime)
{
	
}

Student::Student(uint32 number, const std::string& name,const std::string& intime)
	:number(number), name(name),intime(intime)
{
}

std::string Student::formatInfo()
{
	std::stringstream ss;
	ss << name <<'\t' << number << '\t' << intime<<std::endl;
	return ss.str();
}

void Student::display()
{
	std::cout << this->number << "\t" << this->name << "\t" << this->number << "\t" << this->intime << "\t" << std::endl;
}



void Student::formatWrite(const std::string& str)
{
	std::stringstream ss(str);
	ss >> this->number >> this->name >> this->number >> this->intime;
}

bool Student::operator==(const Student& right) const
{
	return this->number == right.number;
}

bool Student::operator>(const Student& right) const
{
	return this->number > right.number;
}

bool Student::operator<(const Student& right) const
{
	return this->number < right.number;
}

