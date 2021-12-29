#pragma once
#include"Configure.h"
#include "BasicWidget.h"
#include<vector>
#include"PushButton.h"

class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void setRowCount(int row);
    void setColCount(int col);
    void setHeader(const std::string&header);
    void insertData(const std::string& data);

    void show();
    void drawTableGrid();
    void drawTableData();
    void drawButton();
    void drawHeader();
    static  std::vector<std::string>split(std::string str, char separator='\t'  );

    void updatePage();
    
    void eventLoop(const ExMessage& msg);

    void insert(const std::string& data);
    void updateData();
    void clear();
private:
    int m_rows;
    int m_cols;

    //格子宽度与高度
    int m_gridW;
    int m_gridH;
    //文字的宽度与高度
    int m_tw;
    int m_th;

    std::string m_header;
   std::vector< std::string> m_datas;

private:  //分页处理
    int m_curPage;//当前页
    int m_maxPage;//最大页
    int m_extraData;//如果不是整数页，最后一页剩余多少数据

    PushButton* m_prevBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
    PushButton* start;

};
