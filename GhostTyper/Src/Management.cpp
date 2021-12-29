#pragma once
#include "Management.h"
#include<iostream>
#include<conio.h>
#include<fstream>
#include<sstream>
#include"Student.h"
#include"Timer.h"
#include"LineEdit.h"
#include"ArticleManagement.h"
#include "GAME.h"
#include "typeparactise.h"
#include <thread>
#include<string>


using namespace std;
void Management::menu()
{
	for (auto btn : menu_btns)
	{
		btn->show();
	}
	
}

int Management::mainmenu(const ExMessage& msg)
{
	settextstyle(50, 0, "楷体");
	char title[50] = "打字通";
	outtextxy((windows::width() - textwidth(title)) / 2, 20, title);
	settextstyle(25, 0, "楷体");



	for (auto btn : menu_btns)
	{
		btn->show();
	}
	for (size_t i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->eventLoop(msg);
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return 66;
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::enevtLoop()
{
	m_showTable->eventLoop(m_msg);
	m_showmanage->eventLoop(m_msg);
	m_Ranking->eventLoop(m_msg);
}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open())
	{
		return;
	}
	//读取表头
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;
	

	//读取数据
	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//跳过空行
		if (strlen(data) == 0)
			break;
		//格式化读取
		Student stu;
		stringstream    ss(data);
		ss >> stu.name >>stu.number >> stu.intime;
		vec_stu.push_back(stu);
		//cout  << stu.name << stu.number << stu.intime<<endl;
	}

	read.close();

}

void Management::read(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open())
	{
		return;
	}
	//读取表头
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;


	//读取数据
	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//跳过空行
		if (strlen(data) == 0)
			break;
		//格式化读取
		RankingData rank;
		stringstream    ss(data);
		ss >> rank.rank >>  rank.name>> rank.complete>>rank.artname>>rank.correct>>rank.time;
		vec_rank.push_back(rank);
		//cout  << stu.name << stu.number << stu.intime<<endl;
	}

	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);
	if (!write.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}

	//写表头
	m_header+="\n";
	write.write(m_header.c_str(), m_header.size());

	//写数据
	for (auto& val : vec_stu)
	{
		std::string info = val.formatInfo();
		write.write( info.c_str(),info.size());

	}
	write.close();
}


Management::Management()
{
	readFile("./Articles/ArticleList.txt");
	::loadimage(&m_bk, "./Resources/BG.jpg",windows::width(),windows::height());
	::settextstyle(20,0,"宋体");
	//主界面按钮初始化
	menu_btns.push_back(new PushButton("文章训练"));
	menu_btns.push_back(new PushButton("文章管理"));
	menu_btns.push_back(new PushButton("排行榜"));
	menu_btns.push_back(new PushButton("打字游戏"));
	menu_btns.push_back(new PushButton("单词练习"));
	menu_btns.push_back(new PushButton("退出系统"));
	for (int i = 0;i < menu_btns.size();i++)
	{
		menu_btns[i]->setFixedSize(250, 50);

		int bx=(windows::width()-menu_btns[i]->width())/2;
		int vspace = (windows::height() - menu_btns.size() * menu_btns[i]->heitht() )/ 2;
		int by = vspace+i * menu_btns[i]->heitht();

		menu_btns[i]->move(bx,by);
	}
	//初始化查看表格
	m_showmanage = new ArticleManagement;
	m_showTable = new Table;
	m_Ranking = new Ranking;
	m_showTable->setRowCount(15);
	m_showTable->setHeader(m_header);
	m_showTable->move(136, 40);

	m_Ranking = new Ranking;
	m_Ranking->setRowCount(15);
	m_Ranking->setHeader(m_header);
	m_Ranking->move(136, 40);
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}

	//删除页面
	delEdit = new LineEdit(0, 0, 200, 30);;
	delBtn = new PushButton("删除", 0, 0, 200, 30);
	delTable = new Table;
	delTable->setRowCount(6);
	delTable->setHeader(tableHeader);
	delEdit->setInputBoxTitle("请输入学生学号");

	delEdit->move((windows::width() - (delEdit->width() * 2 + 20)) / 2, windows::height() / 3);
	delBtn->move(delEdit->x() + delEdit->width() + 20, windows::height() / 3);
	delTable->move((windows::width() - delTable->width()) / 2, windows::height() / 3 + 100);
}

void Management::run()
{
	int op=66;
	windows::beginDraw();
	while (true)
	{
		windows::clear();
		drawBackground();
		if (windows::hasMsg())
		{
			m_msg=windows::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:          //按键消息
				switch (m_msg.vkcode)
				{
				case VK_ESCAPE:		//ESC
					op = 66;
					break;
				}
				break;
			default:				//其他的都是鼠标消息了
				this->enevtLoop();
				break;
			}
		}
		switch (op)
		{
		case 66:
			op = mainmenu(m_msg);
			break;
		case Management::Display:
			display();
			break;
		case Management::Add:
			add();
			break;
		case Management::Erase:
			erase();
			break;
		case Management::Modfy:
			modfy();
			break;
		case Management::Wordpractice:
			wordpractice();
			break;
		default:
			//saveFile("./images/change.txt");
			exit(666);
			break;
		}
		windows::flushDraw();
	}
	windows::endDraw();
}

void Management::display()
{
	readFile("./Articles/ArticleList.txt");
	m_showTable->show();
}

void Management::add()
{
	m_showmanage->show();
	settextstyle(50, 0, "黑体");
	char title[50] = "添加文章";
	outtextxy((windows::width() - textwidth(title)) / 2, 50, title);

	m_insertEdit.show();
	//m_insertBtn.show();
	settextstyle(30, 0, "黑体");
	outtextxy(m_insertEdit.x() - 50, m_insertEdit.y() - 150, "请依次输入<文章名称 文章字数 文章入库时间>");

	//点一次会触发多次，所以用定时器来延迟一下
	if (m_insertBtn.isClicked() && Timer::startTimer(200, 0))
	{
	}

	//m_insertEdit.updateText();

	//Student stu;
	//cout << "请依次输入<学号,姓名,班级,数学,语文,英语>" << endl;
	//cin >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.chinese >> stu.english;
	//vec_stu.push_back(stu);
}

void Management::erase()
{
	read("./Articles/Ranking.txt");
	if (!oncerank)
	{
	for (auto& val : vec_rank)
	{
		m_Ranking->insertData(val.formatInfo());
	}
		oncerank = 1;
	}


	m_Ranking->show();
}

void Management::modfy()
{
	GameStart();
}

void Management::updateTableDatas()
{
	m_insertTable.clear();
	for (auto val : vec_stu)
	{
		m_insertTable.insert(val.formatInfo());
	}
}

void Management::wordpractice(){

	wordspratice(file(), filelength());


}


