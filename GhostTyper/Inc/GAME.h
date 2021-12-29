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

#define GAMEWIDTH		500								 //��Ϸ����                 
#define GAMEHEIGHT		400								 //��Ϸ��߶�
#define INFORWIDTH		120								 //��Ϣ����
#define INFORHEIGHT		GAMEHEIGHT						 //��Ϣ��߶�
#define GAP				10								 //��϶����
#define WNDWIDTH		(GAP*3+GAMEWIDTH+INFORWIDTH)	 //��Ϸ����
#define WNDHEIGHT		(GAP*2+GAMEHEIGHT)				 //��Ϸ��߶�
#define CHARSIZE		25								 //�ַ��߳�
#define CHARR			((int)((CHARSIZE/2)*sqrt(2.0)))	 //�ַ��뾶
#define MAXLIFE			100								 //�������
#define A				'A'								 //�ַ�'A'
#define DIS			    ('a'-'A')						 //��д��ĸ��Сд��ĸASCII��Ĳ�ֵ
#define TYPE			MYCHAR							 //�ַ��ṹ��
#define PTYPE			PMYCHAR							 //�ַ��ṹ��ָ��
#define INITSIZE        10								 //˳����ʼ����
#define INITMAXSPEED    50								 //�ַ������ʼ�ٶ�(ms)
#define FINALSPEED      10                               //�ַ�����ĩ�ٶ�(ms)
#define SPEEDCHANGETIME 1000						     //�����ٶȸı��ʱ����(ms)
#define COLORCHANGETIME 100							     //��ɫ�ı��ʱ����(ms)
#define ADDCHARSTIME    350						         //�����ַ���ʱ����(ms)


//�ַ��ṹ��
typedef struct
{
	char c;         //�ַ� 
	int x;          //�ַ����ϽǺ�����
	int y;          //�ַ����Ͻ�������
	COLORREF color; //�ַ���ɫ
	DWORD t1;       //�ַ�����仯ʱ���
	DWORD t2;       //��ǰ�ַ�����仯ʱ��
	DWORD dt;       //�ַ�����ʱ����
	DWORD ct1;      //�ַ���ɫ�仯ʱ���
	DWORD ct2;      //��ǰ�ַ���ɫ�仯ʱ��
}MYCHAR, * PMYCHAR;

//˳���ṹ��
struct
{
	PTYPE* p;       //����
	int size;       //��ǰ����
	int maxsize;    //��󳤶�
}list = { NULL,0,0 };

//��Ϸ��Ϣ�ṹ��
struct
{
	int score;     //��Ϸ����
	int maxscore;  //��߷���
	int remnum;    //��������
	int errnum;    //ʧ�����
	int life;      //��ǰ����
	int speed;     //��ǰ�����ٶ�
	DWORD t1;      //�����ַ�ʱ���
	DWORD t2;      //��ǰ�����ַ�ʱ��
	DWORD tt1;     //�����ٶȸı�ʱ���
	DWORD tt2;     //��ǰ�����ٶȸı�ʱ��
	HWND hWnd;     //���ھ��
}g;


void InitList();    //��ʼ��˳���
void Add(PTYPE);    //˳��������ַ�
void Remove(int);   //˳���ɾ���ַ�
void Des();         //�ͷ�˳�����Դ
void Welcome();     //��ʼ����
void InitGame();    //��ʼ����Ϸ
void KbEvent();     //��������
void AddChars();    //ÿ��һ��ʱ�������ַ�
void CheckChars();  //���ÿ���ַ�������
void CheckGame();   //�����Ϸ�ַ�������ٶȺ���ɫ�ĸı�
void Draw();        //������
void Over();        //�����Ϸ�Ƿ����
void Save();        //������߷���


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

	//������߷���
	FILE* fp;
	if ((fp = fopen("./Articles/HighestScore.txt", "rt")) == NULL)
	{
		MessageBox(g.hWnd, "��Ϸ����ʧ�ܣ�", "", MB_OK);
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
			MessageBox(g.hWnd, "��Ϸ�ڴ治�㣡", "", MB_OK);
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
		bool flag = false;   //��־�˴ΰ����Ƿ���ȷ

		//��ͣ��Ϸ
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
		//���¿�ʼ
		else if (con == '2')
		{
			int ID = MessageBox(g.hWnd, "�Ƿ����¿�ʼ��", "", MB_YESNO);

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
			int ID = MessageBox(g.hWnd, "���Ƿ�Ҫ�˳���Ϸ��", "", MB_YESNO);

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

		//��鰴���Ƿ���ȷ
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

		//�����������ȷ
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
	bool flag = false;   //��־�����Ƿ����ַ�����

	//����ַ�������
	for (int i = 0; i < list.size; i++)
	{
		list.p[i]->t2 = timeGetTime();
		if (list.p[i]->t2 - list.p[i]->t1 >= list.p[i]->dt)
		{
			flag = true;
			list.p[i]->t1 = list.p[i]->t2;
			list.p[i]->y += 2;

			//����Ƿ������±߽�
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

	//����������ַ�����
	if (flag)
	{
		Over();
		Draw();
	}
}


void CheckGame()
{
	bool flag = false;     //��鱾����ɫ�Ƿ�仯   

	//����ַ������ٶ�
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

	//�����ɫ�仯
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

	//�����ɫ�б仯�ͻ�����
	if (flag)
	{
		Draw();
	}
}


void Draw()
{
	char str[200];    //��ʱ����
	cleardevice();
	setlinecolor(WHITE);
	rectangle(GAP, GAP, GAP + GAMEWIDTH, GAP + GAMEHEIGHT);  //����Ϸ��

	//�����ĸ
	LOGFONT f;
	COLORREF c;
	gettextstyle(&f);
	c = gettextcolor();
	for (int i = 0; i < list.size; i++)
	{
		settextstyle(CHARSIZE, CHARSIZE, "����");
		settextcolor(list.p[i]->color);
		sprintf(str, "%c", list.p[i]->c);
		outtextxy(list.p[i]->x, list.p[i]->y, str);
		circle(list.p[i]->x + CHARSIZE / 2, list.p[i]->y + CHARSIZE / 2, CHARR);
	}
	//settextstyle(&f);
	settextstyle(15, 8, "����");
	settextcolor(WHITE);

	rectangle(GAP * 2 + GAMEWIDTH, GAP, GAP * 2 + GAMEWIDTH + INFORWIDTH, GAP + INFORHEIGHT);  //����Ϣ��

	sprintf(str, "��Ϸ����:%d", g.score);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 10, str);

	sprintf(str, "��߷���:%d", g.maxscore);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 40, str);

	sprintf(str, "������ĸ:%d", g.remnum);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 70, str);

	sprintf(str, "��ǰ��ĸ:%d", list.size);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 100, str);

	sprintf(str, "ʧ�����:%d", g.errnum);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 130, str);

	sprintf(str, "�ٶȵȼ�:%d", INITMAXSPEED - g.speed);
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 160, str);

	//����˵��
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 340, "1:��ͣ��Ϸ");
	outtextxy(GAP * 2 + GAMEWIDTH + 10, GAP + 370, "2:���¿�ʼ");

	//��ǰ����
	sprintf(str, "��ǰ����:%d", g.life);
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
		MessageBox(g.hWnd, "��Ϸ�ڴ治�㣡", "", MB_OK);
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
			MessageBox(g.hWnd, "��Ϸ�ڴ治�㣡", "", MB_OK);
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
	//�������Ϊ0
	if (g.life == 0)
	{
		mciSendString("close BGM", 0, 0, 0);
		mciSendString("close defeat", 0, 0, 0);
		mciSendString("open ./Resources/defeat.mp3 alias defeat", 0, 0, 0);
		mciSendString("play defeat", 0, 0, 0);

		//��������¼
		if (g.score > g.maxscore)
		{
			g.maxscore = g.score;
			Save();
		}

		Draw();
		EndBatchDraw();

		MessageBox(g.hWnd, "��Ϸ����!", "", MB_OK);
		int ID = MessageBox(g.hWnd, "�Ƿ����¿�ʼ��", "", MB_YESNO);

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
		MessageBox(g.hWnd, "�洢����ʧ�ܣ�", "", MB_OK);
		exit(0);
	}
	fprintf(fp, "%d", g.maxscore);
	fclose(fp);
}