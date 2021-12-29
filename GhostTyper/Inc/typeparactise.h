#pragma once
#pragma   warning(disable:4996)   //全部关掉


#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <window.h>
#pragma comment(lib,"Imm32.lib")
#include <string>
#include "Management.h"


using namespace std;

int accuracy = 86;
int finishTime = 245;
int finishPercentage = 88;
extern char articlename[10];
extern char names[10];

void GetRank() {
	if (strlen(names) == 0)
		strcpy(names, "NEMO");
	if (strlen(articlename) >= 8)
		articlename[7] = '\0';

	FILE* fRankPt;
	fRankPt = fopen("./Articles/Ranking.txt", "r");
	char tmpline[100], allLine[8000] = "\0";
	bool haveInteruped = 0;

	int acc, num;
	while (fgets(tmpline, 100, fRankPt) != NULL)
	{
		int counterT = 0;
		
		if (tmpline[0] >= '0' && tmpline[0] <= '9') {
			
			
			for (int i = 0;i < strlen(tmpline);i++) {
				if (tmpline[i] == '\t')
					counterT++;
				if (counterT == 0) {
					char numc[10];
					int j = 0;
					for (;tmpline[j] != '\t';j++) {
						numc[j] = tmpline[j];
						i = j;
					}
					numc[j] = '\0';
					num = atoi(numc);
				}
				if (counterT == 4) {
					char numc[10];
					int j = 0;
					for (;tmpline[j+i+1] != '\t';j++)
						numc[j] = tmpline[j + i + 1];
					numc[j] = '\0';
					acc = atoi(numc);
					break;
				}

			}//for循环结束 一轮数据被读取
			
			if (acc <= accuracy && haveInteruped == 0) {//出现第一组比acc大的情况时开始写自己的数据，否则临摹数据
				char tmpp[100];
				haveInteruped = 1;
				sprintf(tmpp, "%d\t%s\t%d\t%s\t%d\t%d\n", num, names, finishPercentage, articlename, accuracy, finishTime);
				strcat(allLine, tmpp);
			}
			if (haveInteruped == 0) strcat(allLine, tmpline);
			if (haveInteruped == 1) {
				char tmpp[100];
				sscanf(tmpline, "%d\t%s\t%d\t%s\t%d\t%d", &num, &names, &finishPercentage, &articlename, &accuracy, &finishTime);
				sprintf(tmpp, "%d\t%s\t%d\t%s\t%d\t%d\n", (++num), names, finishPercentage, articlename, accuracy, finishTime);
				strcat(allLine, tmpp);
			}
		}
	}
	if (haveInteruped == 0) {
		char tmpp[100];
		haveInteruped = 1;
		sprintf(tmpp, "%d\t%s\t%d\t%s\t%d\t%d\n", (++num), names, finishPercentage, articlename, accuracy, finishTime);
		strcat(allLine, tmpp);

	}
	fclose(fRankPt);

	FILE* fRankWritePt;
	fRankWritePt = fopen("./Articles/Ranking.txt", "w+");
	fputs("num\tusername\tcomplete\tpassage\taccuracy\ttime\n", fRankWritePt);
	fputs(allLine, fRankWritePt);

	fclose(fRankWritePt);
	return;

}




char str[20] = { "回到上一页" }, strr[20] = { "回首页" };
IMAGE img;

void InitPage() {
	windows w(640, 480, 2);
	w.setWindowTilte("GhostTyper");
	Management m;
	m.run();
	//return w.exec();

	m.run();
}
void GetIMEString(HWND hWnd, string& str)
{
	HIMC hIMC = ImmGetContext(hWnd);//获取HIMC	
	if (hIMC)
	{
		//这里先说明一下，以输入“中国”为例	
		//切换到中文输入法后，输入“zhongguo”，这个字符串称作IME组成字符串	
		//而在输入法列表中选择的字符串“中国”则称作IME结果字符串	
		static bool flag = false;//输入完成标记：在输入中时，IME组成字符串不为空，置true；输入完成后，IME组成字符串为空，置false	
		DWORD dwSize = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0);	//获取IME组成输入的字符串的长度	
		if (dwSize > 0)//如果IME组成字符串不为空，且没有错误（此时dwSize为负值），则置输入完成标记为true	
		{
			if (flag == false)
			{
				flag = true;
			}
		}
		else if (dwSize == 0 && flag)	//如果IME组成字符串为空，并且标记为true，则获取IME结果字符串	
		{
			int iSize;	//IME结果字符串的大小	
			LPSTR pszMultiByte = NULL;//IME结果字符串指针	
			int ChineseSimpleAcp = 936;//宽字节转换时中文的编码	
			WCHAR* lpWideStr = NULL;//宽字节字符数组	
			dwSize = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);//获取IME结果字符串的大小	
			if (dwSize > 0)	//如果IME结果字符串不为空，且没有错误	
			{
				dwSize += sizeof(WCHAR);//大小要加上NULL结束符	
				//为获取IME结果字符串分配空间	
				if (lpWideStr)
				{
					delete[]lpWideStr;
					lpWideStr = NULL;
				}
				lpWideStr = new WCHAR[dwSize];
				memset(lpWideStr, 0, dwSize);	//清空结果空间	
				ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpWideStr, dwSize);//获取IME结果字符串，这里获取的是宽字节	
				iSize = WideCharToMultiByte(ChineseSimpleAcp, 0, lpWideStr, -1, NULL, 0, NULL, NULL);//计算将IME结果字符串转换为ASCII标准字节后的大小	
				//为转换分配空间	
				if (pszMultiByte)
				{
					delete[] pszMultiByte;
					pszMultiByte = NULL;
				}
				pszMultiByte = new char[iSize + 1];
				WideCharToMultiByte(ChineseSimpleAcp, 0, lpWideStr, -1, pszMultiByte, iSize, NULL, NULL);//宽字节转换	
				pszMultiByte[iSize] = '\0';
				str += pszMultiByte;//添加到string中	
				//释放空间	
				if (lpWideStr)
				{
					delete[]lpWideStr;
					lpWideStr = NULL;
				}
				if (pszMultiByte)
				{
					delete[] pszMultiByte;
					pszMultiByte = NULL;
				}
			}
			flag = false;
		}
		ImmReleaseContext(hWnd, hIMC);//释放HIMC	
	}
}


void cyan(int i, int j, char* str)
{
	setfillcolor(LIGHTCYAN);
	setcolor(LIGHTCYAN);
	fillroundrect(i, j, i + 80, j + 50, 10, 10);
	setbkcolor(LIGHTCYAN);
	setcolor(CYAN);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, _T(str));
}

void white(int i, int j, char* str)
{
	setfillcolor(LIGHTCYAN);
	setcolor(LIGHTCYAN);
	fillroundrect(i, j, i + 80, j + 50, 10, 10);
	setbkcolor(LIGHTCYAN);
	setcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 35;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, _T(str));
}

void numinput(int i, int j, char* le)
{
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, le);
}

void letter(int i, int j, char le)
{
	setfillcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(i, j, i + 40, j + 40, 5, 5);
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWidth = 20;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 10, j + 10, _T(le));
}

void letterwhite(int i, int j, char le)
{
	setfillcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(i, j, i + 40, j + 40, 5, 5);
	setbkcolor(WHITE);
	setcolor(LIGHTBLUE);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWidth = 20;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 10, j + 10, _T(le));
}

void num(int i, int j, char le, char le1)
{
	setfillcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(i, j, i + 40, j + 40, 5, 5);
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 10;
	f.lfWidth = 20;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 10, j + 5, _T(le));
	outtextxy(i + 10, j + 25, _T(le1));
}
void numwhite(int i, int j, char le, char le1)
{
	setfillcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(i, j, i + 40, j + 40, 5, 5);
	setbkcolor(WHITE);
	setcolor(BLUE);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 10;
	f.lfWidth = 20;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 10, j + 5, _T(le));
	outtextxy(i + 10, j + 25, _T(le1));
}


void others(int i, int j, int k, int l,const char* le)
{
	setfillcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(i, j, k, l, 5, 5);
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, _T(le));
}

void chinput(int i, int j, char* le)
{
	setbkcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(100, 100, 140, 140, 5, 5);
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, _T(le));
}

void chinputwhite(int i, int j, char* le)
{
	setbkcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(100, 100, 140, 140, 5, 5);
	setbkcolor(WHITE);
	setcolor(RED);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, _T(le));
}

void letterinput(int i, int j, char le)
{
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, le);
}

void letterinputwhite(int i, int j, char le)
{
	setbkcolor(WHITE);
	setcolor(RED);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(i + 5, j + 10, le);
}

void number(char a)
{
	if (a == '`' || a == '~')
		num(5, 238, '`', '~');
	else if (a == '1' || a == '!')
		num(47, 238, '!', '1');
	else if (a == '2' || a == '@')
		num(89, 238, '@', '2');
	else if (a == '3' || a == '#')
		num(131, 238, '#', '3');
	else if (a == '4' || a == '$')
		num(173, 238, '$', '4');
	else if (a == '5' || a == '%')
		num(215, 238, '%', '5');
	else if (a == '6' || a == '^')
		num(257, 238, '^', '6');
	else if (a == '7' || a == '&')
		num(299, 238, '&', '7');
	else if (a == '8' || a == '*')
		num(341, 238, '*', '8');
	else if (a == '9' || a == '(')
		num(383, 238, '(', '9');
	else if (a == '0' || a == ')')
		num(425, 238, ')', '0');
	else if (a == '-' || a == '_')
		num(467, 238, '_', '-');
	else if (a == '=' || a == '+')
		num(509, 238, '+', '=');
	else if (a == '\\' || a == '\|')
		num(551, 238, '\|', '\\');
	else if (a == '[' || a == '{')
		num(489, 280, '{', '[');
	else if (a == ']' || a == '}')
		num(531, 280, '}', ']');
	else if (a == ';' || a == ':')
		num(468, 322, ':', ';');
	else if (a == '\'' || a == '\"')
		num(510, 322, '\"', '\'');
	else if (a == '<' || a == ',')
		num(405, 364, '<', ',');
	else if (a == '>' || a == '.')
		num(447, 364, '>', '.');
	else if (a == '/' || a == '?')
		num(489, 364, '?', '/');

}

void numberwhite(char a)
{
	if (a == '`' || a == '~')
		numwhite(5, 238, '`', '~');
	else if (a == '1' || a == '!')
		numwhite(47, 238, '!', '1');
	else if (a == '2' || a == '@')
		numwhite(89, 238, '@', '2');
	else if (a == '3' || a == '#')
		numwhite(131, 238, '#', '3');
	else if (a == '4' || a == '$')
		numwhite(173, 238, '$', '4');
	else if (a == '5' || a == '%')
		numwhite(215, 238, '%', '5');
	else if (a == '6' || a == '^')
		numwhite(257, 238, '^', '6');
	else if (a == '7' || a == '&')
		numwhite(299, 238, '&', '7');
	else if (a == '8' || a == '*')
		numwhite(341, 238, '*', '8');
	else if (a == '9' || a == '(')
		numwhite(383, 238, '(', '9');
	else if (a == '0' || a == ')')
		numwhite(425, 238, ')', '0');
	else if (a == '-' || a == '_')
		numwhite(467, 238, '_', '-');
	else if (a == '=' || a == '+')
		numwhite(509, 238, '+', '=');
	else if (a == '\\' || a == '\|')
		numwhite(551, 238, '\|', '\\');
	else if (a == '[' || a == '{')
		numwhite(489, 280, '{', '[');
	else if (a == ']' || a == '}')
		numwhite(531, 280, '}', ']');
	else if (a == ';' || a == ':')
		numwhite(468, 322, ':', ';');
	else if (a == '\'' || a == '\"')
		numwhite(510, 322, '\"', '\'');
	else if (a == '<' || a == ',')
		numwhite(405, 364, '<', ',');
	else if (a == '>' || a == '.')
		numwhite(447, 364, '>', '.');
	else if (a == '/' || a == '?')
		numwhite(489, 364, '?', '/');
}

void word(char a)
{
	if (a == 'Q')
		letter(69, 280, 'Q');
	else if (a == 'W')
		letter(111, 280, 'W');
	else if (a == 'E')
		letter(153, 280, 'E');
	else if (a == 'R')
		letter(195, 280, 'R');
	else if (a == 'T')
		letter(237, 280, 'T');
	else if (a == 'Y')
		letter(279, 280, 'Y');
	else if (a == 'U')
		letter(321, 280, 'U');
	else if (a == 'I')
		letter(363, 280, 'I');
	else if (a == 'O')
		letter(405, 280, 'O');
	else if (a == 'P')
		letter(447, 280, 'P');
	else if (a == 'A')
		letter(90, 322, 'A');
	else if (a == 'S')
		letter(132, 322, 'S');
	else if (a == 'D')
		letter(174, 322, 'D');
	else if (a == 'F')
		letter(216, 322, 'F');
	else if (a == 'G')
		letter(258, 322, 'G');
	else if (a == 'H')
		letter(300, 322, 'H');
	else if (a == 'J')
		letter(342, 322, 'J');
	else if (a == 'K')
		letter(384, 322, 'K');
	else if (a == 'L')
		letter(426, 322, 'L');
	else if (a == 'Z')
		letter(111, 364, 'Z');
	else if (a == 'X')
		letter(153, 364, 'X');
	else if (a == 'C')
		letter(195, 364, 'C');
	else if (a == 'V')
		letter(237, 364, 'V');
	else if (a == 'B')
		letter(279, 364, 'B');
	else if (a == 'N')
		letter(321, 364, 'N');
	else if (a == 'M')
		letter(363, 364, 'M');
	else if (a == ' ')
	{
		setfillcolor(WHITE);
		setcolor(BLACK);
		fillroundrect(153, 406, 447, 446, 5, 5);
	}
}

void whiteword(char a)
{
	if (a == 'Q')
		letterwhite(69, 280, 'Q');
	else if (a == 'W')
		letterwhite(111, 280, 'W');
	else if (a == 'E')
		letterwhite(153, 280, 'E');
	else if (a == 'R')
		letterwhite(195, 280, 'R');
	else if (a == 'T')
		letterwhite(237, 280, 'T');
	else if (a == 'Y')
		letterwhite(279, 280, 'Y');
	else if (a == 'U')
		letterwhite(321, 280, 'U');
	else if (a == 'I')
		letterwhite(363, 280, 'I');
	else if (a == 'O')
		letterwhite(405, 280, 'O');
	else if (a == 'P')
		letterwhite(447, 280, 'P');
	else if (a == 'A')
		letterwhite(90, 322, 'A');
	else if (a == 'S')
		letterwhite(132, 322, 'S');
	else if (a == 'D')
		letterwhite(174, 322, 'D');
	else if (a == 'F')
		letterwhite(216, 322, 'F');
	else if (a == 'G')
		letterwhite(258, 322, 'G');
	else if (a == 'H')
		letterwhite(300, 322, 'H');
	else if (a == 'J')
		letterwhite(342, 322, 'J');
	else if (a == 'K')
		letterwhite(384, 322, 'K');
	else if (a == 'L')
		letterwhite(426, 322, 'L');
	else if (a == 'Z')
		letterwhite(111, 364, 'Z');
	else if (a == 'X')
		letterwhite(153, 364, 'X');
	else if (a == 'C')
		letterwhite(195, 364, 'C');
	else if (a == 'V')
		letterwhite(237, 364, 'V');
	else if (a == 'B')
		letterwhite(279, 364, 'B');
	else if (a == 'N')
		letterwhite(321, 364, 'N');
	else if (a == 'M')
		letterwhite(363, 364, 'M');
	else if (a == ' ')
	{
		setfillcolor(BLUE);
		setcolor(BLACK);
		fillroundrect(153, 406, 447, 446, 5, 5);
	}
}

void keyboard()
{
	num(5, 238, '`', '~');
	num(47, 238, '!', '1');
	num(89, 238, '@', '2');
	num(131, 238, '#', '3');
	num(173, 238, '$', '4');
	num(215, 238, '%', '5');
	num(257, 238, '^', '6');
	num(299, 238, '&', '7');
	num(341, 238, '*', '8');
	num(383, 238, '(', '9');
	num(425, 238, ')', '0');
	num(467, 238, '_', '-');
	num(509, 238, '+', '=');
	num(551, 238, '\|', '\\');
	letter(69, 280, 'Q');
	letter(111, 280, 'W');
	letter(153, 280, 'E');
	letter(195, 280, 'R');
	letter(237, 280, 'T');
	letter(279, 280, 'Y');
	letter(321, 280, 'U');
	letter(363, 280, 'I');
	letter(405, 280, 'O');
	letter(447, 280, 'P');

	letter(90, 322, 'A');
	letter(132, 322, 'S');
	letter(174, 322, 'D');
	letter(216, 322, 'F');
	letter(258, 322, 'G');
	letter(300, 322, 'H');
	letter(342, 322, 'J');
	letter(384, 322, 'K');
	letter(426, 322, 'L'); num(489, 280, '{', '[');
	num(531, 280, '}', ']');
	num(468, 322, ':', ';');
	num(510, 322, '\"', '\'');
	letter(111, 364, 'Z');
	letter(153, 364, 'X');
	letter(195, 364, 'C');
	letter(237, 364, 'V');
	letter(279, 364, 'B');
	letter(321, 364, 'N');
	letter(363, 364, 'M');
	num(405, 364, '<', ',');
	num(447, 364, '>', '.');
	num(489, 364, '?', '/');
	others(5, 280, 67, 320, "Tab");
	others(5, 322, 88, 362, "Caps Lock");
	others(5, 364, 109, 404, "Shift");
	others(5, 406, 62, 446, "Ctrl");
	others(64, 406, 104, 446, " ");
	others(106, 406, 151, 446, "Alt");
	others(153, 406, 447, 446, " ");
	others(449, 406, 489, 446, "Alt");
	others(491, 406, 531, 446, " ");
	others(533, 406, 573, 446, " ");
	others(575, 406, 630, 446, "Ctrl");
	others(531, 364, 630, 404, "Shift");
	IMAGE img;
	loadimage(&img, "./Resources/windos.jpg");
	putimage(64, 406, 40, 40, &img, 0, 0);
	putimage(491, 406, 40, 40, &img, 0, 0);
	loadimage(&img, "./Resources/what.jpg");
	putimage(533, 406, 40, 40, &img, 0, 0);
	others(573, 280, 630, 362, " ");
	others(552, 322, 630, 362, "Enter");
	setfillcolor(WHITE);
	setcolor(BLACK);
	fillroundrect(593, 238, 630, 278, 5, 5);
	fillroundrect(593, 258, 630, 278, 5, 5);
	setbkcolor(WHITE);
	setcolor(BLACK);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 8;
	f.lfWidth = 6;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(595, 240, _T("Back"));
	outtextxy(595, 260, _T("Space"));
}

char* file() {
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("./Articles/word.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF)
	{
		if (a[n] == '+')
			break;
		n++;
	}
	fclose(fp);
	a[n] = '\0';

	return a;
}
int filelength()
{
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("./Articles/word.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF)
	{
		if (a[n] == '+')
			break;
		n++;
	}
	fclose(fp);
	a[n] = '\0';

	return n;
}

char* files() {
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("sentence.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF)
	{
		if (a[n] == '+')
			break;
		n++;
	}
	fclose(fp);
	a[n] = '\0';

	return a;
}

int filelengths()
{
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("sentence.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF && a[n] != '+')
		n++;
	fclose(fp);
	a[n] = '\0';

	return n;

}

char* filea() {
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("passage.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF)
	{
		if (a[n] == '+')
			break;
		n++;
	}
	fclose(fp);
	a[n] = '\0';

	return a;
}

int filelengtha()
{
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("passage.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF && a[n] != '+')
		n++;
	fclose(fp);
	a[n] = '\0';

	return n;

}

char* filec() {
	//char a[800];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("汉字.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF)
	{
		if (a[n] == '+')
			break;
		n++;
	}
	fclose(fp);
	a[n] = '\0';

	return a;
}
int filelengthc()
{
	//char a[8000];
	char* a;
	a = (char*)malloc(80000);
	int n = 0;
	FILE* fp;
	fp = fopen("汉字.txt", "rt");
	if (fp == NULL)
	{
		printf("失败了哟");
		exit(0);
	}
	while ((a[n] = fgetc(fp)) != EOF && a[n] != '+')
		n++;
	fclose(fp);
	a[n] = '\0';
	return n;

}

void game(char* line)
{
	int k = 0;
	char f;
	char a[100];
	struct Game
	{
		char x;
	}al[17][11];
	int i = 0, j = 0;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 11; j++)
		{
			al[i][j].x = '0';
		}
	for (i = 0; i < 100; i++, line++)
		a[i] = *line;
	srand((unsigned)time(NULL));
	i = rand() % 16;
	al[i][0].x = a[k];
	letter(i * 40, 0, al[i][0].x);
	while (1)
	{
		clearrectangle(0, 0, 640, 480);
		if (kbhit())
		{
			f = getch();
			for (i = 15; i >= 0; i--)
				for (j = 9; j >= 0; j--)
				{
					if (f == al[i][j].x)
					{
						al[i][j].x = '0';
						clearrectangle(i * 40, j * 40, (i + 1) * 40, (j + 1) * 40);
					}
				}

		}

		for (i = 15; i >= 0; i--)
			for (j = 9; j >= 0; j--)
				if (al[i][j].x >= 'a' && al[i][j].x <= 'z')
				{

					letter(i * 40, (j + 1) * 40, al[i][j].x);
					al[i][j + 1].x = al[i][j].x;
					al[i][j].x = '0';
				}
		Sleep(500);
		i = rand() % 16;
		k++;
		al[i][0].x = a[k];
		letter(i * 40, 0, al[i][0].x);
	}

}

int wordspratice(char* line, int n)
{
	closegraph();
	initgraph(640, 480);

	loadimage(&img, "./Resources/TyperBG.jpg");
	putimage(0, 0, 640, 480, &img, 0, 0);

	int i, flag = 1, k = 0, d1 = 0, d2 = 0, l = 1, q = 0;
	long j = 0;
	char s;
	char a[80000];
	char b[500];
	MOUSEMSG m;

	BeginBatchDraw();
	keyboard();
	cyan(550, 0, str);
	rectangle(60, 100, 600, 140);
	rectangle(60, 150, 600, 190);
	others(0, 0, 150, 40, "打字速度：     /分");
	others(0, 50, 150, 90, "准确率：       %");
	others(160, 50, 340, 90, "用时：   分    秒");
	others(160, 0, 340, 40, "进度：       %    ");
	time_t timer;
	struct tm* tblock;
	EndBatchDraw();
	j = 0;
	while (1)
	{
		for (i = 0; i < 65 && *line != '\0'; i++, line++)
			a[i] = *line;
		a[65] = '\0';
		if (*line == '\0')
			a[i] = '\0';
		clearrectangle(60, 100, 600, 140);
		others(60, 100, 600, 140, a);
		clearrectangle(60, 150, 600, 190);
		for (i = 0; a[i] != '\0'; i++)
		{
			if (a[i] == ' ')
				whiteword(' ');
			else if (a[i] >= 97 && a[i] <= 122)
				whiteword(a[i] - 32);
			else if (a[i] >= 65 && a[i] <= 90)
				whiteword(a[i]);
			else
				numberwhite(a[i]);
			while (1) {
				if (j == (n - 1))
				{
					MessageBox(NULL, "恭喜你完成全部单词输入", "成功", MB_OK);
					InitPage();
				}

				if (MouseHit())
				{
					m = GetMouseMsg();
					if (m.x >= 550 && m.x <= 640 && m.y >= 0 && m.y <= 50)
					{
						white(550, 0, str);
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							clearrectangle(0, 0, 640, 480);
							InitPage();
						}
					}
					else
						cyan(550, 0, str);
				}

				if (kbhit())
				{
					s = getch();
					if (flag == 1)
					{
						timer = time(NULL);
						tblock = localtime(&timer);
						d2 = tblock->tm_sec;
						d1 = tblock->tm_min;
						Sleep(1000);
					}
					flag = 2;
					word(' ');
					word(a[i] - 32);
					word(a[i]);
					number(a[i]);
					if (s == 8) {
						if (i > 0)
						{
							clearrectangle(58 + 8 * i, 150, 600 + 8 * i, 190);
							i = i - 2;
							q--;
						}
						else if (i <= 0) { i = -1; }
					}
					else
					{
						q++;
						j++;
						if (s == a[i])
						{
							k++;
							letterinput(60 + 8 * i, 150, s);
						}
						else
							letterinputwhite(60 + 8 * i, 150, s);
					}

				}
				timer = time(NULL);
				tblock = localtime(&timer);
				if ((tblock->tm_min - d1) * 60 + tblock->tm_sec - d2 > l && flag != 1)
				{
					clearrectangle(80, 5, 120, 35);
					sprintf(b, "%d", j * 60 / ((tblock->tm_min - d1) * 60 + tblock->tm_sec - d2));
					numinput(80, 0, b);
					l = l + 1;
					clearrectangle(210, 55, 230, 85);
					sprintf(b, "%d", l / 60);
					numinput(210, 50, b);
					clearrectangle(260, 55, 280, 85);
					sprintf(b, "%d", l % 60);
					numinput(260, 50, b);
				}
				if (flag == 2)
				{
					flag = 0;
					break;
				}
			}
			if (j > 0)
			{
				clearrectangle(80, 50, 120, 80);
				sprintf(b, "%d", k * 100 / j);
				numinput(80, 50, b);
			}
			if (q > 0)
			{
				clearrectangle(210, 5, 230, 45);
				sprintf(b, "%d", q * 100 / n);
				numinput(210, 0, b);
			}
		}
	}

}
int article(char* line, int n)
{
	closegraph();
	initgraph(640, 480);

	loadimage(&img, "./Resources/TyperBG.jpg");
	putimage(0, 0, 640, 480, &img, 0, 0);
	

	BeginBatchDraw();
	int i, flag = 1, j = 0, k = 0, d1 = 0, d2 = 0, l = 1, q = 0, i1 = 0;
	char s;
	char a[7000];
	char b[5];
	MOUSEMSG m;
	cyan(550, 0, str);
	for (i1 = 0; i1 < 8; i1++) {
		others(10, 100 + i1 * 45, 630, 140 + i1 * 45, " ");
	}
	i1 = 0;
	others(0, 0, 150, 40, "打字速度：     /分");
	others(0, 50, 150, 90, "准确率：       %");
	others(160, 50, 340, 90, "用时：   分    秒");
	others(160, 0, 340, 40, "进度：       %    ");




	EndBatchDraw();
	time_t timer;
	struct tm* tblock;
	while (1)
	{
		for (i = 0; i < 70 && *line != '\0'; i++, line++)
			a[i] = *line;
		a[70] = '\0';
		if (*line == '\0')
			a[i] = '\0';
		if (i1 == 4)
		{
			for (i1 = 0; i1 < 8; i1++) {
				clearrectangle(10, 100 + i1 * 45, 630, 140 + i1 * 45);
				others(10, 100 + i1 * 45, 630, 140 + i1 * 45, " ");
			}
			i1 = 0;
		}
		others(10, 100 + 90 * i1, 630, 140 + 90 * i1, a);
		clearrectangle(10, 145 + 90 * i1, 630, 185 + 90 * i1);
		for (i = 0; a[i] != '\0'; i++)
		{
			while (1) {
				if (j == (n-1)) {
					MessageBox(NULL,"成功完成训练,分数将计入排行榜","成功",MB_OK);
					accuracy = (k * 100 / j);
					finishTime = l;
					finishPercentage = (q * 100 / n);
					GetRank();
					
					InitPage();

					return(k * 100 / j);
				}
				if (MouseHit())
				{
					m = GetMouseMsg();
					if (m.x >= 550 && m.x <= 640 && m.y >= 0 && m.y <= 50)
					{
						white(550, 0, str);
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							clearrectangle(0, 0, 640, 480);
							if ((q * 100 / n)<75) {
								MessageBox(NULL, "未能成功完成训练，成绩不计入排行榜", "未能成功", MB_OK);
								
							}
							else {
								MessageBox(NULL, "成功完成训练,分数将计入排行榜", "成功", MB_OK);
								accuracy = (k * 100 / j);
								finishTime = l;
								finishPercentage = (q * 100 / n);
								GetRank();
							}
							InitPage();

							return (k * 100 / j);
						}
					}
					else
						cyan(550, 0, str);
				}

				if (kbhit())
				{

					s = getch();
					if (flag == 1)
					{
						timer = time(NULL);
						tblock = localtime(&timer);
						d2 = tblock->tm_sec;
						d1 = tblock->tm_min;
						Sleep(1000);
					}
					flag = 2;
					if (s == 8) {
						if (i > 0)
						{
							clearrectangle(8 + 8 * i, 145 + i1 * 90, 18 + i * 8, 180 + i1 * 90);
							i = i - 2;
							q--;
						}
						else if (i <= 0) { i = -1; }
					}
					else
					{
						q++;
						j++;
						if (s == a[i])
						{
							k++;
							letterinput(10 + 8 * i, 150 + i1 * 90, s);
						}
						else
							letterinputwhite(10 + 8 * i, 150 + i1 * 90, s);
					}

				}
				timer = time(NULL);
				tblock = localtime(&timer);
				if ((tblock->tm_min - d1) * 60 + tblock->tm_sec - d2 > l && flag != 1)
				{
					clearrectangle(80, 5, 120, 35);
					sprintf(b, "%d", j * 60 / ((tblock->tm_min - d1) * 60 + tblock->tm_sec - d2));
					numinput(80, 0, b);
					l = l + 1;
					clearrectangle(210, 55, 230, 85);
					sprintf(b, "%d", l / 60);
					numinput(210, 50, b);
					clearrectangle(260, 55, 280, 85);
					sprintf(b, "%d", l % 60);
					numinput(260, 50, b);
				}
				if (flag == 2)
				{
					flag = 0;
					break;
				}
			}
			if (j > 0)
			{
				clearrectangle(80, 50, 120, 80);
				sprintf(b, "%d", k * 100 / j);
				numinput(80, 50, b);
			}
			if (q > 0)
			{
				clearrectangle(210, 5, 230, 45);
				sprintf(b, "%d", q * 100 / n);
				numinput(210, 0, b);
			}
		}
		i1++;
	}
	}

int judge(char* line, int n)
{
	int i, flag = 1, j = 0, k = 0, d1 = 0, d2 = 0, l = 1, q = 0, i1 = 0, e = 0;
	char s1[20];
	char a[10000];
	char b[50];
	char s[1000];
	MOUSEMSG m;
	cyan(550, 0, str);
	for (i1 = 0; i1 < 8; i1++)
		others(10, 100 + i1 * 45, 630, 140 + i1 * 45, " ");
	i1 = 0;
	others(0, 0, 150, 40, "打字速度：     /分");
	others(0, 50, 150, 90, "准确率：       %");
	others(160, 50, 340, 90, "用时：   分    秒");
	others(160, 0, 340, 40, "进度：       %    ");
	time_t timer;
	struct tm* tblock;
	HWND hWnd = GetHWnd();
	BeginBatchDraw();	// 设置批绘图模式	
	string st;

	while (1)
	{
		for (i = 0; i < 70 && *line != '\0'; i++, line++)
			a[i] = *line;
		a[70] = '\0';
		if (*line == '\0')
			a[i] = '\0';
		if (i1 == 4)
		{
			for (i1 = 0; i1 < 8; i1++)
			{
				clearrectangle(10, 100 + i1 * 45, 630, 140 + i1 * 45);
				others(10, 100 + i1 * 45, 630, 140 + i1 * 45, " ");
			}
			i1 = 0;
		}
		others(10, 100 + 90 * i1, 630, 140 + 90 * i1, a);
		/*clearrectangle(10,145+90*i1,630,185+90*i1);*/
		for (i = 0; a[i] != '\0';) {
			while (true)
			{
				if (MouseHit())
				{
					m = GetMouseMsg();
					if (m.x >= 550 && m.x <= 640 && m.y >= 0 && m.y <= 50)
					{
						white(550, 0, str);
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							clearrectangle(0, 0, 640, 480);
							return 1;
						}
					}
					else
						cyan(550, 0, str);
				}

				if (kbhit())	//如果是ASCII输入	
				{
					char c = getch();
					if (c == '\b')
					{
						if (st.length() > 0)
						{
							if (st.at(st.length() - 1) & 0x8000)
								st.erase(st.end() - 1);
							st.erase(st.end() - 1);
						}
					}
					else if (c == 27) {}
					else {
						st += c;
					}
				}
				else	//除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中	
				{
					GetIMEString(hWnd, st);
					if (flag == 1)
					{
						timer = time(NULL);
						tblock = localtime(&timer);
						d2 = tblock->tm_sec;
						d1 = tblock->tm_min;
						Sleep(1000);
					}

				}
				if (st.length() > 100)
					st = "";
				strcpy(s, st.c_str());
				for (; s[e] != '\0'; e++, i++)
				{
					q++;
					s1[0] = s[e];
					s1[1] = s[e + 1];
					s1[2] = '\0';
					if (a[i] == s[e] && a[i + 1] == s[e + 1])
					{
						chinput(10 + 8 * i, 150 + i1 * 90, s1);
						j++; flag = 2;
					}
					else {
						chinputwhite(10 + 8 * i, 150 + i1 * 90, s1);	flag = 2;
					}
					i++;
					e++;
				}
				FlushBatchDraw();
				timer = time(NULL);
				tblock = localtime(&timer);
				if ((tblock->tm_min - d1) * 60 + tblock->tm_sec - d2 > l && flag != 1)
				{
					clearrectangle(80, 5, 120, 35);
					sprintf(b, "%d", j * 60 / ((tblock->tm_min - d1) * 60 + tblock->tm_sec - d2));
					numinput(80, 0, b);
					l = l + 1;
					clearrectangle(210, 55, 230, 85);
					sprintf(b, "%d", l / 60);
					numinput(210, 50, b);
					clearrectangle(260, 55, 280, 85);
					sprintf(b, "%d", l % 60);
					numinput(260, 50, b);
				}
				if (flag == 2)
				{
					flag = 0;
					break;
				}
			}
			if (j > 0)
			{
				clearrectangle(80, 50, 120, 80);
				sprintf(b, "%d", k * 100 / j);
				numinput(80, 50, b);
			}
			if (q > 0)
			{
				clearrectangle(210, 5, 230, 45);
				sprintf(b, "%d", q * 100 / n);
				numinput(210, 0, b);
			}
		}
		i1++;
	}
}
void ying()
{
	char str1[20] = { "单词练习" }, str2[20] = { "语句练习" }, str3[20] = { "文章练习" };
	initgraph(640, 480,2);
	IMAGE img;
	cyan(170, 210, str1);
	cyan(270, 210, str2);
	cyan(370, 210, str3);
	cyan(550, 0, str);
	MOUSEMSG m;
	loadimage(&img, "./Resources/TyperBG.jpg");
	putimage(0, 0, 640, 480, &img, 0, 0);
	while (1)
	{
		m = GetMouseMsg();
		if (m.x >= 170 && m.x <= 260 && m.y >= 210 && m.y <= 260)
		{
			white(170, 210, str1);
			while (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				keyboard();
				if (wordspratice(file(), filelength()) == 1)
					;
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
				break;
			}
		}
		else if (m.x >= 270 && m.x <= 360 && m.y >= 210 && m.y <= 260)
		{
			white(270, 210, str2);
			while (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				keyboard();
				if (wordspratice(files(), filelengths()) == 1)
					;
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
				break;
			}
		}
		else if (m.x >= 370 && m.x <= 460 && m.y >= 210 && m.y <= 260)
		{
			white(370, 210, str3);
			while (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);

				if (article(filea(), filelengtha()) == 1)
					;
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
				break;
			}
		}
		else if (m.x >= 550 && m.x <= 640 && m.y >= 0 && m.y <= 50)
		{
			white(550, 0, str);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				break;
			}
		}
		else
		{
			cyan(170, 210, str1);
			cyan(270, 210, str2);
			cyan(370, 210, str3);
			cyan(550, 0, str);
		}
	}

}

void pin()
{
	char str1[20] = { "音节练习" }, str2[20] = { "词汇练习" }, str3[20] = { "文章练习" };
	initgraph(640, 480, 2);
	IMAGE img;
	cyan(170, 210, str1);
	cyan(270, 210, str2);
	cyan(370, 210, str3);
	cyan(550, 0, str);
	MOUSEMSG m;
	loadimage(&img, "./Resources/TyperBG.jpg");
	putimage(0, 0, 640, 480, &img, 0, 0);
	while (1)
	{
		m = GetMouseMsg();
		if (m.x >= 170 && m.x <= 260 && m.y >= 210 && m.y <= 260)
		{
			white(170, 210, str1);
			while (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);

				if (judge(file(), filelength()) == 1)
					;
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
				break;
			}
		}
		else if (m.x >= 270 && m.x <= 360 && m.y >= 210 && m.y <= 260)
		{
			white(270, 210, str2);
			while (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				if (judge(filec(), filelengthc()) == 1)
					;
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
				break;
			}
		}
		else if (m.x >= 370 && m.x <= 460 && m.y >= 210 && m.y <= 260)
		{
			white(370, 210, str3);
			while (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);

				if (judge(filec(), filelengthc()) == 1)
					;
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
				break;
			}
		}
		else if (m.x >= 550 && m.x <= 640 && m.y >= 0 && m.y <= 50)
		{
			white(550, 0, str);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				break;
			}
		}
		else
		{
			cyan(170, 210, str1);
			cyan(270, 210, str2);
			cyan(370, 210, str3);
			cyan(550, 0, str);
		}
	}
}
void jiemian1()
{
	char str1[20] = { "英文打字" }, str2[20] = { "拼音打字" }, str3[20] = { "五笔打字" }, str4[20] = { "速度测试" }, str5[20] = { "打字游戏" }, str6[20] = { "上网导航" }, str7[20] = { "打字教程" };
	initgraph(640, 480, 2);
	IMAGE img;
	loadimage(&img, "./Resources/TyperBG.jpg");
	putimage(0, 0, 640, 480, &img, 0, 0);
	cyan(10, 40, str1);
	cyan(10, 100, str2);
	cyan(10, 160, str3);
	cyan(10, 220, str4);
	cyan(10, 280, str5);
	cyan(10, 340, str6);
	cyan(10, 400, str7);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.x >= 10 && m.x <= 90 && m.y >= 40 && m.y <= 90)
		{
			white(10, 40, str1);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				ying();
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
			}
		}
		else if (m.x >= 10 && m.x <= 90 && m.y >= 100 && m.y <= 150)
		{
			white(10, 100, str2);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				pin();
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
			}
		}
		else if (m.x >= 10 && m.x <= 90 && m.y >= 160 && m.y <= 210)
		{
			white(10, 160, str3);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				break;
			}
		}
		else if (m.x >= 10 && m.x <= 90 && m.y >= 220 && m.y <= 270)
		{
			white(10, 220, str4);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				break;
			}
		}
		else if (m.x >= 10 && m.x <= 90 && m.y >= 280 && m.y <= 330)
		{
			white(10, 280, str5);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				game(file());
				loadimage(&img, "./Resources/TyperBG.jpg");
				putimage(0, 0, 640, 480, &img, 0, 0);
			}
		}
		else if (m.x >= 10 && m.x <= 90 && m.y >= 340 && m.y <= 390)
		{
			white(10, 340, str6);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				break;
			}
		}
		else if (m.x >= 10 && m.x <= 90 && m.y >= 400 && m.y <= 450)
		{
			white(10, 400, str7);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				clearrectangle(0, 0, 640, 480);
				break;
			}
		}
		else
		{
			cyan(10, 40, str1);
			cyan(10, 100, str2);
			cyan(10, 160, str3);
			cyan(10, 220, str4);
			cyan(10, 280, str5);
			cyan(10, 340, str6);
			cyan(10, 400, str7);
		}
	}
}

//void main()
//{
//	jiemian1();
//	getch();
//		initgraph(640, 480, 2); // 创建绘图窗口
//		HWND hWnd=GetHWnd();
//	BeginBatchDraw();	// 设置批绘图模式
//	string str;
//	while(true)
//	{
//	if (kbhit())	//如果是ASCII输入
//	{
//	char c=getch();
//	if (c=='\b')
//	{
//	if (str.length()>0)
//	{
//	if (str.at(str.length()-1)&0x8000)
//	str.erase(str.end()-1);
//	str.erase(str.end()-1);
//	}
//	}
//	else if (c==27) {	}
//	else	{
//	str+=c;
//	}
//	}
//	else	//除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中
//	{
//	GetIMEString(hWnd,str);
//	}
//	if (str.length()>100)
//	str="";
//	outtextxy(0,0,str.c_str());
//	FlushBatchDraw();
//	// 延时
//	Sleep(15);
//	cleardevice();
//	}
//	closegraph();
//}