#pragma once
#include<chrono>
using namespace std::chrono;
/*��ʱ��*/
class Timer
{
public:
    Timer(int64_t ms = 0);
    void startTimer();
    bool timeout();
    void setTime(int64_t ms);
    void killTimer();
public:
    //��̬��ʱ��
    static bool startTimer(int64_t ms, int id);
    //��ʱ�������ID
    inline static size_t maxTimerID() { return 20; };
private:
    int64_t m_ms;	//�ӳٺ�����
    time_point<high_resolution_clock> m_startime;
    time_point<high_resolution_clock> m_endtime;

    bool m_threadIsRun;	//�����߳�����
};

/*ʱ��������������ʱ�䣩*/
class ElapsedTimer
{
public:
    ElapsedTimer();
    void reset();
    //Ĭ���������
    int64_t elapsed() const;
    //΢��
    int64_t elapsed_micro() const;
    //����
    int64_t elapsed_nano() const;
    //��
    int64_t elapsed_seconds() const;
    //��
    int64_t elapsed_minutes() const;
    //ʱ
    int64_t elapsed_hours() const;
private:
    time_point<high_resolution_clock> m_begin;
};

