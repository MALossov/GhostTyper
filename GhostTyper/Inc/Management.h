#pragma once
#include"window.h"
#include<vector>
#include"PushButton.h"
#include"Student.h"
#include"Table.h"
#include"LineEdit.h"
#include"ArticleManagement.h"
#include"Ranking.h"
#include"RankingData.h"
class Management
{
	enum Operator
	{
		Display,
		Add,
		Erase,
		Modfy,
		Wordpractice = 4,
		Menu = 66
	};
public:
	Management();
	void run();//����������
	void display();//����ѵ��
	void add();//���¹���
	void erase();//���а�
	void modfy();//������Ϸ
	void menu();//�˵�
	void wordpractice();//������ϰ
	int mainmenu(const ExMessage& msg);
	bool oncerank = 0;


	void drawBackground();
	void enevtLoop();

	


	void readFile(const std::string& fileName);
	void read(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateTableDatas();


public://ɾ��ѧ��ҳ��
	LineEdit* delEdit;
	PushButton* delBtn;
	Table* delTable;

private:
	IMAGE m_bk;
	ExMessage m_msg;
public:
	std::string tableHeader;	//��ͷ

	int m_prevStuCnt;	//��һ��ѧ��������

	Table		m_insertTable;
	LineEdit	m_insertEdit;		//���ѧ���༭��
	PushButton	m_insertBtn;		//���ѧ��ȷ�ϰ�ť
	std::vector<PushButton*>menu_btns;

private://��ȡ�ļ� ������Ϣ
	std::string m_header;
	std::vector<Student>vec_stu;
	std::vector<RankingData>vec_rank;

private:
	Table* m_showTable;

private:
	ArticleManagement* m_showmanage;

private:
	Ranking* m_Ranking;
};

