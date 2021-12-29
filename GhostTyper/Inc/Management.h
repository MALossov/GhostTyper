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
	void run();//启动管理类
	void display();//文章训练
	void add();//文章管理
	void erase();//排行榜
	void modfy();//打字游戏
	void menu();//菜单
	void wordpractice();//单词练习
	int mainmenu(const ExMessage& msg);
	bool oncerank = 0;


	void drawBackground();
	void enevtLoop();

	


	void readFile(const std::string& fileName);
	void read(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateTableDatas();


public://删除学生页面
	LineEdit* delEdit;
	PushButton* delBtn;
	Table* delTable;

private:
	IMAGE m_bk;
	ExMessage m_msg;
public:
	std::string tableHeader;	//表头

	int m_prevStuCnt;	//上一次学生的数量

	Table		m_insertTable;
	LineEdit	m_insertEdit;		//添加学生编辑框
	PushButton	m_insertBtn;		//添加学生确认按钮
	std::vector<PushButton*>menu_btns;

private://读取文件 保存信息
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

