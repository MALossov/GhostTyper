#pragma once
#include"Configure.h"
using uint32 = unsigned int;
class RankingData
{
public:
	RankingData();
	RankingData(int rank,char name[],int complete,char artname[],int correct,float time);
	std::string formatInfo();//��ʽ������


		//��ʾ��Ϣ
	void display();
	//��ѧ����������Ϣ��ʽ�����ַ���

	void formatWrite(const std::string& str);


public:
	int rank;//����
	char name[100];//�û���
	int complete;//��ɶ�
	char artname[100];//��������
	int correct;//��ȷ��
	float time;//��ʱ
};

