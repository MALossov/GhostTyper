#include "LineEdit.h"
#include"window.h"
#include<conio.h>
#include<easyx.h>
LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), textw(2), m_isPopUp(false)
	, m_title("请输入")
{

}

void LineEdit::show()
{
	
	setfillcolor(RGB(232, 232, 236));
	fillrectangle(120, 225, 120 + 400, 225 + 30);

	//闪烁的小竖线
	setlinecolor(RED);
	line(120 + 2 + 2, 225 + 2, 120 + 2 + 2, 225 + 30 - 2);

	//把文字输出到edit上
	outtextxy(120, 225 + (30 - textheight(m_text.c_str())) / 2, m_text.c_str());


	if (m_isPopUp)
	{
		m_pretext = m_text;
		popInputBox();
		m_isPopUp = false;
	}
}
void LineEdit::eventLoop(const ExMessage& msg)
{
	//判断是否需要弹出输入框
	if (msg.x > m_x && msg.x < m_x + m_w && msg.y > m_y && msg.y < m_y + m_h
		&& msg.message == WM_LBUTTONDOWN)
	{
		m_isPopUp = true;
	}
}
void LineEdit::popInputBox()
{
	char str[128] = { 0 };
	InputBox(str, 128, nullptr, m_title.c_str(), m_text.c_str());
	m_text = str;
	textw = ::textwidth(m_text.c_str());
}
void LineEdit::setInputBoxTitle(const std::string& title)
{
	m_title = title;
}

std::string  LineEdit::text()
{
	return m_text;
}

void LineEdit::clear()
{
	m_text.clear();
	textw = 0;
}

bool LineEdit::textChanged()
{
	if (m_pretext == m_text)
	{
		return false;
	}
	m_pretext = m_text;	//更新,通知一次文本改变即可
	return true;
}
