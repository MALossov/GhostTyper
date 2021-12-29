#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#pragma   warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <window.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "Management.h"

//Management m;

#define GAMEWIDTH		500								 //游戏框宽度                 
#define GAMEHEIGHT		400								 //游戏框高度
#define INFORWIDTH		120								 //信息框宽度
#define INFORHEIGHT		GAMEHEIGHT						 //信息框高度
#define GAP				10								 //缝隙像素
#define WNDWIDTH		(GAP*3+GAMEWIDTH+INFORWIDTH)	 //游戏框宽度
#define WNDHEIGHT		(GAP*2+GAMEHEIGHT)				 //游戏框高度
#define CHARSIZE		25								 //字符边长
#define CHARR			((int)((CHARSIZE/2)*sqrt(2.0)))	 //字符半径
#define MAXLIFE			100								 //最大生命
#define A				'A'								 //字符'A'
#define DIS			    ('a'-'A')						 //大写字母与小写字母ASCII码的差值
#define TYPE			MYCHAR							 //字符结构体
#define PTYPE			PMYCHAR							 //字符结构体指针
#define INITSIZE        10								 //顺序表初始长度
#define INITMAXSPEED    50								 //字符下落初始速度(ms)
#define FINALSPEED      10                               //字符下落末速度(ms)
#define SPEEDCHANGETIME 1000						     //下落速度改变的时间间隔(ms)
#define COLORCHANGETIME 100							     //颜色改变的时间间隔(ms)
#define ADDCHARSTIME    350						         //增加字符的时间间隔(ms)


//字符结构体
typedef struct
{
	char c;         //字符 
	int x;          //字符左上角横坐标
	int y;          //字符左上角纵坐标
	COLORREF color; //字符颜色
	DWORD t1;       //字符下落变化时间初
	DWORD t2;       //当前字符下落变化时间
	DWORD dt;       //字符下落时间间隔
	DWORD ct1;      //字符颜色变化时间初
	DWORD ct2;      //当前字符颜色变化时间
}MYCHAR, * PMYCHAR;

//顺序表结构体
struct
{
	PTYPE* p;       //内容
	int size;       //当前长度
	int maxsize;    //最大长度
}list = { NULL,0,0 };

//游戏信息结构体
struct
{
	int score;     //游戏分数
	int maxscore;  //最高分数
	int remnum;    //消除个数
	int errnum;    //失误个数
	int life;      //当前生命
	int speed;     //当前下落速度
	DWORD t1;      //增加字符时间初
	DWORD t2;      //当前增加字符时间
	DWORD tt1;     //下落速度改变时间初
	DWORD tt2;     //当前下落速度改变时间
	HWND hWnd;     //窗口句柄
}g;


void InitList();    //初始化顺序表
void Add(PTYPE);    //顺序表增加字符
void Remove(int);   //顺序表删除字符
void Des();         //释放顺序表资源
void Welcome();     //初始界面
void InitGame();    //初始化游戏
void KbEvent();     //按键处理
void AddChars();    //每隔一段时间增加字符
void CheckChars();  //检查每个字符的下落
void CheckGame();   //检查游戏字符下落的速度和颜色的改变
void Draw();        //画界面
void Over();        //检查游戏是否结束
void Save();        //保存最高分数


int GameStart()
{
	//Welcome();
	InitGame();
	InitList();
	Draw();

	while (1)
	{
		BeginBatchDraw();
		AddChars();
		CheckChars();
		KbEvent();
		CheckGame();
		EndBatchDraw();
	}

	return 0;
}


void Welcome()
{
	initgraph(WNDWIDTH, WNDHEIGHT);
	loadimage(NULL, "./Resources/BGP.jpg", WNDWIDTH, WNDHEIGHT);

	getch();
}


void InitGame()
{
	mciSendString("close BGM", 0, 0, 0);
	mciSendString("open ./Resources/BGM.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);

	srand((unsigned)time(NULL));

	g.score = 0;
	g.remnum = 0;
	g.errnum = 0;
	g.life = MAXLIFE;
	g.speed = INITMAXSPEED;
	g.t1 = timeGetTime();
	g.t2 = g.t1;
	g.tt1 = timeGetTime();
	g.tt2 = g.tt1;
	g.hWnd = GetHWnd();

	//加载最高分数
	FILE* fp;
	if ((fp = fopen("./Articles/HighestScore.txt", "rt")) == NULL)
	{
		MessageBox(g.hWnd, "游戏加载失败！", "", MB_OK);
		exit(0);
	}
	fscanf(fp, "%d", &g.maxscore);
	fclose(fp);

	setbkmode(0);
}


void AddChars()
{
	g.t2 = timeGetTime();

	if (g.t2 - g.t1 >= ADDCHARSTIME)
	{
		g.t1 = g.t2;
		PTYPE p = (PTYPE)malloc(sizeof(TYPE));
		if (p == NULL)
		{
			MessageBox(g.hWnd, "游戏内存不足！", "", MB_OK);
			exit(0);
		}

		p->c = A + rand() % 26;
		p->x = GAP + 1 + (rand() % (GAMEWIDTH - CHARR * 2 - 1)) + (CHARR - CHARSIZE / 2);
		p->y = GAP + 1 + (CHARR - CHARSIZE / 2);
		p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
		p->t1 = timeGetTime();
		p->t2 = p->t1;
		p->dt = g.speed + rand() % 8;
		p->ct1 = timeGetTime();
		p->ct2 = p->t1;
		Add(p);

		Draw();
	}
}


void KbEvent()
{
	if (kbhit())
	{
		char con = getch();
		bool flag = false;   //标志此次按键是否正确

		//暂停游戏
		if (con == '1')
		{
			while (1)
			{
				con = getch();

				if (con == '1')
				{
					break;
				}
			}
			return;
		}
		//重新开始
		else if (con == '2')
		{
			int ID = MessageBox(g.hWnd, "是否重新开始？", "", MB_YESNO);

			if (ID == IDYES)
			{
				Des();
				InitList();
				InitGame();
				Draw();
			}
			return;
		}

		else if (con == 27)
		{
			int ID = MessageBox(g.hWnd, "您是否要退出游戏？", "", MB_YESNO);

			if (ID == IDYES)
			{
				closegraph();
				mciSendString("close BGM", 0, 0, 0);

				windows w(640, 480, 2);
				w.setWindowTilte("GhostTyper");
				Management m;
				m.run();
			}
			return;
		}

		//检查按键是否正确
		for (int i = 0; i < list.size; i++)
		{
			if (con == list.p[i]->c || con == list.p[i]->c + DIS)
			{
				mciSendString("close true", 0, 0, 0);
				mciSendString("open ./Resources/true.mp3 alias true", 0, 0, 0);
				mciSendString("play true", 0, 0, 0);

				flag = true;
				g.score++;
				g.remnum++;
				Remove(i);

				break;
			}
		}

		//如果按键不正确
		if (!flag)
		{
			mciSendString("close false", 0, 0, 0);
			mciSendString("open ./Resources/false.mp3 alias false", 0, 0, 0);
			mciSendString("play false", 0, 0, 0);

			g.life--;
			g.errnum++;
			g.score--;

			if (g.life < 0)
			{
				g.life = 0;
			}
			if (g.score < 0)
			{
				g.score = 0;
			}

			Over();
		}
	}
}


void CheckChars()
{
	bool flag = false;   //标志当次是否有字符下落

	//检查字符的下落
	for (int i = 0; i < list.size; i++)
	{
		list.p[i]->t2 = timeGetTime();
		if (list.p[i]->t2 - list.p[i]->t1 >= list.p[i]->dt)
		{
			flag = true;
			list.p[i]->t1 = list.p[i]->t2;
			list.p[i]->y += 2;

			//检查是否碰到下边界
			if (list.p[i]->y >= GAP + GAMEHEIGHT - CHARR - CHARSIZE / 2)
			{
				mciSendString("close false", 0, 0, 0);
				mciSendString("open ./Resources/false.mp3 alias false", 0, 0, 0);
				mciSendString("play false", 0, 0, 0);


				g.life--;
				g.errnum++;
				g.score--;

				if (g.life < 0)
				{
					g.life = 0;
				}
				if (g.score < 0)
				{
					g.score = 0;
				}

				Remove(i);
				i--;
			}
		}
	}

	//如果当次有字符下落
	if (flag)
	{
		Over();
		Draw();
	}
}


void CheckGame()
{
	bool flag = false;     //检查本次颜色是否变化   

	//检查字符下落速度
	g.tt2 = timeGetTime();
	if (g.tt2 - g.tt1 >= SPEEDCHANGETIME)
	{
		g.tt1 = g.tt2;
		g.speed--;

		if (g.speed < FINALSPEED)
		{
			g.speed = FINALSPEED;
		}
	}

	//检查颜色变化
	for (int i = 0; i < list.size; i++)
	{
		list.p[i]->ct2 = timeGetTime();
		if (list.p[i]->ct2 - list.p[i]->ct1 >= COLORCHANGETIME)
		{
			list.p[i]->ct1 = list.p[i]->ct2;
			list.p[i]->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			flag = true;
		}
	}

	//如果颜色有变化就画界面
	if (flag)
	{
		Draw();
	}
}


void Draw()
{
	char str[200];    //临时数组
	cleardevice();
	setlinecolor(WHITE);
	rectangle(GAP, GAP, GAP + GAMEWIDTH, GAP + GAMEHEIGHT);  //画游戏框

	//输出字母
	LOGFONT f;
	COLORREF c;
	gettextstyle(&f);
	c = gettextcolor();
	for (int i = 0; i < list.size; i++)
	{
		settextstyle(CHARSIZE, CHARSIZE, "宋体");
		settextcolor(list.p[i]->color);
		sprintf(str, "%c", list.p[i]->c);
		outtextxy(list.p[i]->x, list.p[i]->y, str);
		circle(list.p[i]->x + CHARSIZE / 2, list.p[i]->y + CHARSIZE / 2, CHARR);
	}
	//settextstyle(&f);
	settextstyle(15, 8, "宋体");
	settextcolor(WHITE);

	rectangle(GAP * 2 + GAMEWIDTH, GAP, GAP * 2 + GAMEWIDTH + INFORWIDTH, GAP + INFORHEIGHT);  //画信息框

	sprintf(str, "游戏分数:%d", g.score);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 10, str);

	sprintf(str, "最高分数:%d", g.maxscore);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 40, str);

	sprintf(str, "消除字母:%d", g.remnum);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 70, str);

	sprintf(str, "当前字母:%d", list.size);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 100, str);

	sprintf(str, "失误个数:%d", g.errnum);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 130, str);

	sprintf(str, "速度等级:%d", INITMAXSPEED - g.speed);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 160, str);

	//操作说明
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 340, "1:暂停游戏");
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 370, "2:重新开始");

	//当前生命
	sprintf(str, "当前生命:%d", g.life);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 220, str);
	setfillcolor(RED);
	solidrectangle(GAP * 2 + GAMEWIDTH + 10, GAP + 245, GAP * 2 + GAMEWIDTH + 10 + g.life, GAP + 260);
	rectangle(GAP * 2 + GAMEWIDTH + 10, GAP + 245, GAP * 2 + GAMEWIDTH + 10 + 100, GAP + 260);
}


void InitList()
{
	list.p = (PTYPE*)malloc(INITSIZE * sizeof(PTYPE));
	if (list.p == NULL)
	{
		MessageBox(g.hWnd, "游戏内存不足！", "", MB_OK);
		exit(0);
	}

	list.size = 0;
	list.maxsize = INITSIZE;
}


void Add(PTYPE p)
{
	if (list.size == list.maxsize)
	{
		int newsize = list.size + list.size / 2;
		PTYPE* newbase = (PTYPE*)realloc(list.p, newsize * sizeof(PTYPE));
		if (newbase == NULL)
		{
			MessageBox(g.hWnd, "游戏内存不足！", "", MB_OK);
			exit(0);
		}
		list.p = newbase;
		list.maxsize = newsize;
	}

	list.p[list.size++] = p;
}


void Remove(int c)
{
	PTYPE p = list.p[c];

	for (int i = c + 1; i <= list.size; i++)
	{
		list.p[i - 1] = list.p[i];
	}

	free(p);
	list.size--;
}


void Des()
{
	for (int i = 0; i < list.size; i++)
	{
		free(list.p[i]);
	}
	free(list.p);

	list.size = 0;
	list.maxsize = 0;
}


void Over()
{
	//如果生命为0
	if (g.life == 0)
	{
		mciSendString("close BGM", 0, 0, 0);
		mciSendString("close defeat", 0, 0, 0);
		mciSendString("open ./Resources/defeat.mp3 alias defeat", 0, 0, 0);
		mciSendString("play defeat", 0, 0, 0);

		//如果创造记录
		if (g.score > g.maxscore)
		{
			g.maxscore = g.score;
			Save();
		}

		Draw();
		EndBatchDraw();

		MessageBox(g.hWnd, "游戏结束!", "", MB_OK);
		int ID = MessageBox(g.hWnd, "是否重新开始？", "", MB_YESNO);

		if (ID == IDNO)
		{
			Des();
			mciSendString("close BGM", 0, 0, 0);
			//m.run();
			//fclose(fp);
			//return;
			//exit(0);
			closegraph();

			windows w(640, 480, 2);
			w.setWindowTilte("GhostTyper");
			Management m;
			m.run();
			//return w.exec();

			m.run();
		}
		else if (ID == IDYES)
		{
			Des();
			InitList();
			InitGame();
			Draw();
		}
	}
}


void Save()
{
	FILE* fp;
	if ((fp = fopen("./Articles/HighestScore.txt", "w")) == NULL)
	{
		MessageBox(g.hWnd, "存储分数失败！", "", MB_OK);
		exit(0);
	}
	fprintf(fp, "%d", g.maxscore);
	fclose(fp);
}