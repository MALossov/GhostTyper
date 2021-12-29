#pragma   warning(disable:4996)   //全部关掉
#include "ArticleManagement.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

extern void InitPage();

bool itis;
ArticleManagement::ArticleManagement()
{
	add = (new PushButton("增加"));
	del = (new PushButton("删除"));

}

ArticleManagement::~ArticleManagement()
{
	delete add;
	delete del;
}

void ArticleManagement::eventLoop(const ExMessage& msg)
{
	add->eventLoop(msg);
	del->eventLoop(msg);

	if (add->isClicked())
	{
		char name[10];
		if (InputBox(name, 10, "请输入想添加的文章名称(不要超过十位）", 0, 0, 0, 0, 0)) 
			if(strlen(name) == 0) 
				MessageBox(NULL, "请输入正确长度的文章名称", "错误！", MB_OK);
			else
			{

			FILE* f1;
			f1 = fopen("./Articles/ArticleList.txt", "a+");
			char existnames[100];
			int flag = 1;
			bool canInput = 1;
			while (fgets(existnames, 100, f1) != NULL) {
				flag = memcmp(existnames, name, strlen(name));
				if (flag == 0) {
					MessageBox(NULL, "文章名称重复，无法录入！", "错误！", MB_OK);
					canInput = 0;
					break;
				}
			}

			if (canInput) {
				char article[8000];
				InputBox(article, 8000, "请输入文章内容", "ArticleInput", 0, 400, 300);
				int len = strlen(article);

				char content[100];

				sprintf(content, "%s\t%d\t", name, len);


				//strcpy(content, name);
				//strcat(content, "\t");
				char tmp[20];
				//strcat(content, itoa(len, tmp, 20));
				//strcat(content, "\t");

				time_t timep;
				struct tm* p;
				time(&timep);
				p = gmtime(&timep);
				int time[3];
				time[0] = 1 + p->tm_mon;/*获取当前月份,范围是0-11,所以要加1*/
				time[1] = 1900 + p->tm_year;/*获取当前年份,从1900开始，所以要加1900*/
				time[2] = p->tm_mday;//当前月份的天数
				sprintf(tmp, "%d年%d月%d日\n", time[1], time[0], time[2]);
				strcat(content, tmp);

				MessageBox(NULL, content, "输入内容", MB_OK);
				for (int kk = 0; kk < strlen(article); kk++)
					if (article[kk] == '\n' || article[kk] == '\r')
						article[kk] = ' ';

				fputs(content, f1);
				fclose(f1);

				FILE* FWRITER;
				char passagearea[50] = "./Articles/";
				strcat(passagearea, name);
				strcat(passagearea, ".txt");

				FWRITER = fopen(passagearea, "w+");

				fputs(article, FWRITER);
				fclose(FWRITER);

				InitPage();
			}
		}
				
		
		
	}
	if (del->isClicked())
	{
		char name[10];
		if (InputBox(name, 10, "请输入想删除的文章名称（不要超过十位）【支持缺省末尾名称输入！】", 0, 0, 0, 0, 0)) 
			if (strlen(name) == 0)
				MessageBox(NULL, "请输入正确长度的文章名称", "错误！", MB_OK);
			else {

			FILE* f1;
			f1 = fopen("./Articles/ArticleList.txt", "r");
			char existnames[100];
			int flag = 1;
			bool canInput = 1;
			while (fgets(existnames, 100, f1) != NULL) {
				flag = memcmp(existnames, name, strlen(name));
				if (flag == 0) {
					canInput = 0;
				}
			}
			fclose(f1);
			if (canInput)
			{
				MessageBox(NULL, "未找到同名文章，无法删除！", "Error", MB_OK);
			}
			else {
				FILE* f1;
				f1 = fopen("./Articles/ArticleList.txt", "r");

				char tmpline[100];
				char resultlines[8000] = "\0";
				int flag = 1;
				char filenamerslt[20];
				while (fgets(tmpline, 100, f1) != NULL) {
					flag = memcmp(tmpline, name, strlen(name));
					if (flag != 0) {
						strcat(resultlines, tmpline);
					}
					else {
						int i = 0;
						for (; tmpline[i] != '\t'; i++)
							filenamerslt[i] = tmpline[i];
						filenamerslt[i] = '\0';
					}
				}
				fclose(f1);
				f1 = fopen("./Articles/ArticleList.txt", "w+");
				fputs(resultlines, f1);
				fclose(f1);
				char filename[50] = "./Articles/";
				strcat(filename, filenamerslt);
				strcat(filename, ".txt");
				remove(filename);
				MessageBox(NULL, "找到同名文章，已经删除！", "删除成功", MB_OK);

				InitPage();


			}
		}

	}


}

void ArticleManagement::show()
{
	drawPushButton();
}

void ArticleManagement::drawPushButton()
{
	add->move(180, 300);
	del->move(345, 300);

	add->show();
	del->show();
}

