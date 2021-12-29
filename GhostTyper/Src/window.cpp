#include "window.h"
#include<iostream>

windows::windows(int w, int h, int flag)
{
    m_handle=::initgraph(w, h, flag);
    ::setbkmode(TRANSPARENT);
}

void windows::setWindowTilte(const std::string& title)
{
    ::SetWindowText(m_handle, title.c_str());
}

int windows::exec()
{
    return getchar();
}

int windows::width()
{
    return ::getwidth();
}

int windows::height()
{
    return ::getheight();
}

void windows::clear()
{
    ::cleardevice();
}

void windows::beginDraw()
{
    ::BeginBatchDraw();
}

void windows::flushDraw()
{
    ::FlushBatchDraw();
}

void windows::endDraw()
{
    ::EndBatchDraw();
}
