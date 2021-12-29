#pragma once
#include"PushButton.h"
#include"Configure.h"
#include "BasicWidget.h"
#include<vector>
#include<fstream>
#include<sstream>

class ArticleManagement
{
public:
    ArticleManagement();
    ~ArticleManagement();

    void eventLoop(const ExMessage& msg);

    void show();
    void drawPushButton();

private:
    PushButton* add;
    PushButton* del;


};

