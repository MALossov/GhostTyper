#pragma once
#include "BasicWidget.h"
#include<thread>
#pragma comment(lib,"Imm32.lib")
#include<easyx.h>
#include<iostream>
class LineEdit :
    public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 100, int h = 30);
	void show();

	void eventLoop(const ExMessage& msg);

	//�������������
	void popInputBox();
	void setInputBoxTitle(const std::string& title);
	std::string text();
	void clear();
	//�ı��Ƿ�ı���
	bool textChanged();
private:
	std::string m_pretext;	//��һ�ε�����
	std::string m_text;		//�б༭���е�����
	int textw;

	std::string m_title;	//�б༭������������

	bool m_isPopUp;	//�Ƿ񵯳�
};

