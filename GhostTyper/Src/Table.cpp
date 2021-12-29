#pragma once
#pragma   warning(disable:4996) 
#include "Table.h"
#include<iostream>

extern int article(char* line, int n);
extern char* filea();
extern int filelengtha();
extern void getRank();

char names[10];
char articlename[10];

bool once = 0;

Table::Table(int row, int col)
	:BasicWidget(0,0,0,0)
	,m_rows(row)
	,m_cols(col)
	,m_curPage(0)
	,m_maxPage(0)
	,m_extraData(0)
{
	m_prevBtn =new PushButton("��һҳ");
	m_nextBtn = new PushButton("��һҳ");
	m_firstBtn = new PushButton("��ҳ");
	m_lastBtn = new PushButton("βҳ");
	start = new PushButton("��ʼѵ��");
}

Table::~Table()
{
	delete m_prevBtn;
	delete m_nextBtn;
	delete m_firstBtn;
	delete m_lastBtn;
	delete start;
}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::setHeader(const std::string& header)
{
	m_header = header;

	m_cols=std::count(m_header.begin(), m_header.end(), '\t')+3;

	//������ֿ����߶�
	m_gridW=::textwidth("harry potter");
	m_gridH=::textheight(m_header.c_str())+8;


}

void Table::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();
}

void Table::show()
{
	
	drawTableGrid();
	drawTableData();
	drawHeader();
}

void Table::drawTableGrid()
{
    //ȷ�����������
	//������
	setlinecolor(BLACK);
	for (size_t i = 0;i < m_rows + 1;i++)
	{
		line(m_x, m_y+i*m_gridH,m_x+ m_cols * m_gridW, m_y+i*m_gridH);
	}
	//������
	for (size_t i = 0;i < m_cols + 1;i++)
	{
		line(m_x+i*m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	drawButton();
	/*if (m_maxPage > 0)
	{
		drawButton();
	}*/
}

void Table::drawTableData()
{
	if (m_datas.size() == 0)
		return;
	//��ֹԽ��
	if (m_rows > m_datas.size()&&m_datas.size()!=0)
	{
		m_rows = m_datas.size();
	}

	int begPos=m_curPage*m_rows;//���ݿ�ʼ
	int endPos = m_curPage*m_rows+m_rows;//���ݽ���λ��
	//��������һҳ��ֻ����ʣ�µ�����
	if (m_curPage == m_maxPage)
	{
		endPos = begPos + m_extraData;
	}
	

	for (size_t i = begPos,r=0;i < endPos;i++,r++)
	{
			const auto& line_data = split(m_datas[i]);//��
			for (size_t k = 0; k < line_data.size(); k++)//��
			{
				int tx = m_x + k * m_gridW;
				int ty = m_y + r * m_gridH;
				outtextxy(tx, ty, line_data[k].c_str());
				
			}
	
	}
}

void Table::drawButton()
{
	m_prevBtn->move(27,200);
	m_nextBtn->move(27,250);
	m_firstBtn->move(27, 300);
	m_lastBtn->move(27, 350);
	start->move(27, 150);

	m_prevBtn->show();
	m_nextBtn->show();
	m_firstBtn->show();
	m_lastBtn->show();
	start->show();

	char str[30] = { 0 };
	sprintf_s(str, "��%dҳ/��%dҳ",m_curPage+1,m_maxPage+1);
	outtextxy(8, 400, str);
}

void Table::drawHeader()
{
	setlinestyle(PS_SOLID, 2);
	::rectangle(136, 5, 495, 37);

	for (size_t i = 0;i < m_cols;i++)
	{
		line(136 + i * m_gridW, 5, 136 + i * m_gridW, 37);
	}

	setlinestyle(PS_SOLID, 1);

	//��ͷ����
	outtextxy(137, 15, "��������");
	outtextxy(137+120, 15, "��������");
	outtextxy(137+120+120, 15, "¼��ʱ��");
}

std::vector<std::string> Table::split(std::string str, char separator)
{
	std::vector<std::string> res;

	//"Name\tCount\tDatetime";

	for (size_t pos = 0;pos !=std::string::npos;)
	{
	//����ָ���ָ��ַ���λ��
	pos = str.find(separator);
	//ȡ���ҵ����ַ���0-10
	res.push_back(str.substr(0,pos));
	//ʣ�µ��ַ������浽str
	str = std::string(str.c_str()+pos+1);

	

	}

	return res;
}

void Table::updatePage()
{
	if (m_rows >= m_datas.size())
	{
		m_maxPage = 0;
		m_extraData = m_datas.size();
	}
	else
	{
	m_maxPage = m_datas.size() / m_rows;
	m_extraData = m_datas.size() % m_rows;

	}
	
}

void Table::eventLoop(const ExMessage& msg)
{
	m_prevBtn->eventLoop(msg);
	m_nextBtn->eventLoop(msg);
	m_firstBtn->eventLoop(msg);
	m_lastBtn->eventLoop(msg);
	start->eventLoop(msg);

	if (start->isClicked())
	{


		if (!once) {
			MessageBox(NULL, "ע�⣺�˸��Ҳ�������������У������˸�����൱�ڰװ��˷���ȷ�ʣ�", "�����ʹ���˸����", MB_OK);
			once = 1;
		}
		if (InputBox(names, 10, "�������û�����������ʮλ��", 0, 0, 0, 0, 0)) 
		{

			if (InputBox(articlename, 10, "��������Ҫѵ������������", 0, 0, 0, 0, 0)) 
				if (strlen(articlename) == 0 || strlen(names) == 0)
					MessageBox(NULL, "��������ȷ���ȵ����»����û�����", "����", MB_OK);
				else {


				FILE* f1;
				f1 = fopen("./Articles/ArticleList.txt", "a+");
				char existnames[200];
				int flag = 1;
				bool canInput = 1;
				char filenamerslt[20] = "\0";
				while (fgets(existnames, 199, f1) != NULL) {
					flag = memcmp(existnames, articlename, strlen(articlename));
					if (flag == 0) {
						canInput = 0;
						int i = 0;
						for (; existnames[i] != '\t'; i++)
							filenamerslt[i] = existnames[i];
						filenamerslt[i] = '\0';
						break;
					}

				}
				if (filenamerslt[0] == '\0') {
					canInput == 1;
				}
				else {
					strcpy(articlename, filenamerslt);
				}
				fclose(f1);


				if (canInput)
				{
					MessageBox(NULL, "δ�ҵ�ͬ�����£��޷���ʼ��ϰ��", "Error", MB_OK);
				}
				else {
					char article[8000] = "\0";

					FILE* FREADER;
					char passagearea[50] = "./Articles/";
					strcat(passagearea, articlename);
					strcat(passagearea, ".txt");
					FREADER = fopen(passagearea, "r");

					char tmpline[8000];
					while (fgets(tmpline, 8000, FREADER) != NULL) {
						strcat(article, tmpline);
					}
					fclose(FREADER);


					FILE* FWRITER;
					FWRITER = fopen("passage.txt", "w+");
					fputs(article, FWRITER);
					fputc('+', FWRITER);
					fclose(FWRITER);
				}

				if (!canInput)
					article(filea(), filelengtha());

			}
		}
	}

	if (m_prevBtn->isClicked())
	{
		if (m_curPage != 0)
		{
			m_curPage--;
		}
	}
	if (m_nextBtn->isClicked())
	{
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_firstBtn->isClicked())
	{
		m_curPage = 0;
	}
	if (m_lastBtn->isClicked())
	{
		m_curPage = m_maxPage;
	}

}

void Table::insert(const std::string& data)
{
	m_datas.push_back(data);
	updateData();
}

void Table::updateData()
{
	//�������ҳ��
	if (m_rows >= m_datas.size())
	{
		m_maxPage = 0;
		m_extraData = m_datas.size();
	}
	else
	{
		m_extraData = m_datas.size() % m_rows;	//�������¶���������
		m_maxPage = m_datas.size() / m_rows;
	}
}

void Table::clear()
{
	m_datas.clear();
	updateData();
}
