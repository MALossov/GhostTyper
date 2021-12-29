#pragma once
#include"Configure.h"
#include "BasicWidget.h"
#include<vector>
#include"PushButton.h"
class Ranking :
    public BasicWidget
{
public:
    Ranking(int row = 0, int col = 0);
    ~Ranking();
    void setRowCount(int row);
    void setColCount(int col);
    void setHeader(const std::string& header);
    void insertData(const std::string& data);

    void show();
    void drawTableGrid();
    void drawTableData();
    void drawButton();
    void drawHeader();
    static  std::vector<std::string>split(std::string str, char separator = '\t');

    void updatePage();

    void eventLoop(const ExMessage& msg);

    void insert(const std::string& data);
    void updateData();
    void clear();
private:
    int m_rows;
    int m_cols;

    //���ӿ�����߶�
    int m_gridW;
    int m_gridH;
    //���ֵĿ�����߶�
    int m_tw;
    int m_th;

    std::string m_header;
    std::vector< std::string> m_datas;

private:  //��ҳ����
    int m_curPage;//��ǰҳ
    int m_maxPage;//���ҳ
    int m_extraData;//�����������ҳ�����һҳʣ���������

    PushButton* m_prevBt;
    PushButton* m_nextBt;
    PushButton* m_firstBt;
    PushButton* m_lastBt;
    PushButton* start;

};
