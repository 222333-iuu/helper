#include "pch.h"
#include "head.h"
ACTION::ACTION() {

} 


ACTION::ACTION(int s, int t, POINT loca)
{
    sort = s;
    time = t;
    location = loca;
    preornot = 0;
    press = '\0';
}// ���غ������õ���ͬ���ࣨ�ƶ���

ACTION::ACTION(int s, int t, POINT loca, bool pre, char p) 
{
    sort = s;
    time = t;
    location = loca;
    preornot = pre;
    press = p;
}// ���غ������õ���ͬ����

ACTION::ACTION(int s, int t, bool pre, char p)
{
    sort = s;
    time = t;
    GetCursorPos(&location);
    preornot = pre;
    press = p;
}// ���غ������õ���ͬ���ࣨ���룩

ACTION::ACTION(int s, int t, bool pre)
{
    sort = s;
    time = t;
    GetCursorPos(&location);
    preornot = pre;
    press = '\0';
}// ���غ������õ���ͬ���ࣨ���֣�

bool ACTION::when(Timer timer)
{
    if (time >= timer.RealTime()) return 1;
    else return 0;
}

string ACTION::Description() 
{
    string ans = to_string(sort) + " " + to_string(time) + " ";
    if (sort == 0) {
        ans += to_string(location.x) + " " + to_string(location.y) + " ����ƶ� ";
    }
    else if (sort == 1) {
        ans += (preornot ? "1" : "0");
        ans += " ";
        ans += press;
        ans += " " + to_string(location.x) + " " + to_string(location.y) + " ";
        ans += press == 'l' ? "������ " : (press == 'r' ? "����Ҽ� "  : "����м� ");
        ans += preornot ? " ����" : " �ɿ�";
    }
    else if (sort == 2) {
        ans += to_string(int(press));
        ans += " ";
        ans += (preornot ? "1" : "0");
        ans += " ";
        ans += preornot ? " ���̰���" : " �����ɿ�";
        ans += "��Ӧ������";
        if(press != '\n' && press != '\0' && press > 30 && press < 100) ans += press;
        ans += "(code:" + to_string(int(press)) + ")";
    }
    else if (sort == 3) {
        ans += (preornot ? "1" : "0");
        ans += " ";
        ans += (preornot ? "���ֺ��" : "����ǰ��");
    }
    return ans;
}