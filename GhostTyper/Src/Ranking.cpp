#include "Ranking.h"
#include"PushButton.h"
#include<iostream>
#include"Management.h"
Ranking::Ranking(int row, int col)
	:BasicWidget(0, 0, 0, 0)
	, m_rows(row)
	, m_cols(col)
	, m_curPage(0)
	, m_maxPage(0)
	, m_extraData(0)
{
    m_prevBt = new PushButton("��һҳ");
	m_nextBt = new PushButton("��һҳ");
	m_firstBt = new PushButton("��ҳ");
	m_lastBt = new PushButton("βҳ");
}

Ranking::~Ranking()
{
	delete m_prevBt;
	delete m_nextBt;
	delete m_firstBt;
	delete m_lastBt;
}

void Ranking::setRowCount(int row)
{
	m_rows = row;
}

void Ranking::setColCount(int col)
{
	m_cols = col;
}

void Ranking::setHeader(const std::string& header)
{
	m_header = header;

	m_cols = std::count(m_header.begin(), m_header.end(), '\t') + 3;

	//������ֿ����߶�
	m_gridW = ::textwidth("harry potter");
	m_gridH = ::textheight(m_header.c_str()) + 8;
}

void Ranking::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();
}

void Ranking::show()
{
	drawTableGrid();
	drawTableData();
	drawHeader();
}

void Ranking::drawTableGrid()
{
	setlinecolor(BLACK);
	for (size_t i = 0;i < m_rows + 1;i++)
	{
		line(m_x, m_y + i * m_gridH, /*m_x + m_cols * m_gridW*/496, m_y + i * m_gridH);
	}
	//������
	for (size_t i = 0;i < 6+ 1;i++)
	{
		line(m_x + i * 60, m_y, m_x + i * 60, m_y + m_rows * m_gridH);
	}
	drawButton();
	/*if (m_maxPage > 0)
	{
		drawButton();
	}*/
}

void Ranking::drawTableData()
{
	if (m_datas.size() == 0)
		return;
	//��ֹԽ��
	if (m_rows > m_datas.size() && m_datas.size() != 0)
	{
		m_rows = m_datas.size();
	}

	int begPos = m_curPage * m_rows;//���ݿ�ʼ
	int endPos = m_curPage * m_rows + m_rows;//���ݽ���λ��
	//��������һҳ��ֻ����ʣ�µ�����
	if (m_curPage == m_maxPage)
	{
		endPos = begPos + m_extraData;
	}


	for (size_t i = begPos, r = 0;i < endPos;i++, r++)
	{
		const auto& line_data = split(m_datas[i]);//��
		settextstyle(18, 8,"����");
		//settextcolor(WHITE);
		for (size_t k = 0; k < line_data.size(); k++)//��
		{
			int tx = m_x + k * 60;
			int ty = m_y + r * m_gridH;
			outtextxy(tx, ty, line_data[k].c_str());

		}

	}
}

void Ranking::drawButton()
{
	m_prevBt->move(27, 200);
	m_nextBt->move(27, 250);
	m_firstBt->move(27, 300);
	m_lastBt->move(27, 350);

	m_prevBt->show();
	m_nextBt->show();
	m_firstBt->show();
	m_lastBt->show();

	char str[30] = { 0 };
	sprintf_s(str, "��%dҳ/��%dҳ", m_curPage + 1, m_maxPage + 1);
	outtextxy(8, 400, str);
}

void Ranking::drawHeader()
{
	setlinestyle(PS_SOLID, 2);
	::rectangle(136, 5, 495, 37);

	for (size_t i = 0;i < 6;i++)
	{
		line(136 + i * 60, 5, 136 + i * 60, 37);
	}

	setlinestyle(PS_SOLID, 1);
	outtextxy(137, 15, "����");
	outtextxy(137+58, 15, "�û���");
	outtextxy(137+56+56+5, 15, "��ɶ�");
	outtextxy(137+56+56+76, 15, "����");
	outtextxy(137 + 56+56+56+70, 15, "��ȷ��");
	outtextxy(137 + 140 + 170, 15, "��ʱ");
}

std::vector<std::string> Ranking::split(std::string str, char separator)
{
	std::vector<std::string> res;

	//"Name\tCount\tDatetime";

	for (size_t pos = 0;pos != std::string::npos;)
	{
		//����ָ���ָ��ַ���λ��
		pos = str.find(separator);
		//ȡ���ҵ����ַ���0-10
		res.push_back(str.substr(0, pos));
		//ʣ�µ��ַ������浽str
		str = std::string(str.c_str() + pos + 1);
	}

	return res;
}

void Ranking::updatePage()
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

void Ranking::eventLoop(const ExMessage& msg)
{

	m_prevBt->eventLoop(msg);
	m_nextBt->eventLoop(msg);
	m_firstBt->eventLoop(msg);
	m_lastBt->eventLoop(msg);

	if (m_prevBt->isClicked())
	{
		if (m_curPage != 0)
		{
			m_curPage--;
		}
	}
	if (m_nextBt->isClicked())
	{
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_firstBt->isClicked())
	{
		m_curPage = 0;
	}
	if (m_lastBt->isClicked())
	{
		m_curPage = m_maxPage;
	}
}

void Ranking::insert(const std::string& data)
{
	m_datas.push_back(data);
	updateData();
}

void Ranking::updateData()
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

void Ranking::clear()
{
	m_datas.clear();
	updateData();
}

