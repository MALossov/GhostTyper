#pragma once
#include"Configure.h"
using uint32 = unsigned int;
class RankingData
{
public:
	RankingData();
	RankingData(int rank,char name[],int complete,char artname[],int correct,float time);
	std::string formatInfo();//格式化数据


		//显示信息
	void display();
	//把学生的所有信息格式化成字符串

	void formatWrite(const std::string& str);


public:
	int rank;//排名
	char name[100];//用户名
	int complete;//完成度
	char artname[100];//文章名称
	int correct;//正确率
	float time;//用时
};

