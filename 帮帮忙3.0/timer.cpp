#include "pch.h"
#include "head.h"

Timer::Timer() {
    reset();
}

bool Timer::ReqRecord() {
    SysTime = GetTime();
    if (SysTime - LastTime >= ResponeTime) {
        LastTime = SysTime;
        return 1;
    }
    else return 0;
}

int Timer::GetTime() {
    SYSTEMTIME temp;
    GetLocalTime(&temp);
    return ((temp.wHour * 60 + temp.wMinute) * 60 + temp.wSecond) * 1000 + temp.wMilliseconds;
}

int Timer::RealTime() { //�Կ�ʼ��������ʵʱ��
    SysTime = GetTime();
    return SysTime - BeginTime;
}

void Timer::reset(int time) {
    ResponeTime = time;
    BeginTime = GetTime();
    LastTime = GetTime();
}

void Timer::wait(int time) { //����ʱ����
    reset(time);
    int temp = time / 1000;
    while (!ReqRecord()) {
        if (time - RealTime() <= temp * 1000) {
            temp--;
        }
    };
}

string FUNC::printtime() { //��ӡ��־ʱ��
    string ans = "";
    SYSTEMTIME temp;
    GetLocalTime(&temp);
    ans += (temp.wHour >= 10 ? "[" : "[0");
    ans += to_string(temp.wHour);
    ans += (temp.wMinute >= 10 ? ":" : ":0");
    ans += to_string(temp.wMinute);
    ans += (temp.wSecond >= 10 ? ":" : ":0");
    ans += to_string(temp.wSecond);
    ans += "." + to_string(temp.wMilliseconds) + "] ";
    return ans;
}