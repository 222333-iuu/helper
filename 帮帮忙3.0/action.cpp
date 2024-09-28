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
}// 重载函数，得到不同种类（移动）

ACTION::ACTION(int s, int t, POINT loca, bool pre, char p) 
{
    sort = s;
    time = t;
    location = loca;
    preornot = pre;
    press = p;
}// 重载函数，得到不同种类

ACTION::ACTION(int s, int t, bool pre, char p)
{
    sort = s;
    time = t;
    GetCursorPos(&location);
    preornot = pre;
    press = p;
}// 重载函数，得到不同种类（输入）

ACTION::ACTION(int s, int t, bool pre)
{
    sort = s;
    time = t;
    GetCursorPos(&location);
    preornot = pre;
    press = '\0';
}// 重载函数，得到不同种类（滚轮）

bool ACTION::when(Timer timer)
{
    if (time >= timer.RealTime()) return 1;
    else return 0;
}

string ACTION::Description() 
{
    string ans = to_string(sort) + " " + to_string(time) + " ";
    if (sort == 0) {
        ans += to_string(location.x) + " " + to_string(location.y) + " 鼠标移动 ";
    }
    else if (sort == 1) {
        ans += (preornot ? "1" : "0");
        ans += " ";
        ans += press;
        ans += " " + to_string(location.x) + " " + to_string(location.y) + " ";
        ans += press == 'l' ? "鼠标左键 " : (press == 'r' ? "鼠标右键 "  : "鼠标中键 ");
        ans += preornot ? " 按下" : " 松开";
    }
    else if (sort == 2) {
        ans += to_string(int(press));
        ans += " ";
        ans += (preornot ? "1" : "0");
        ans += " ";
        ans += preornot ? " 键盘按下" : " 键盘松开";
        ans += "对应按键：";
        if(press != '\n' && press != '\0' && press > 30 && press < 100) ans += press;
        ans += "(code:" + to_string(int(press)) + ")";
    }
    else if (sort == 3) {
        ans += (preornot ? "1" : "0");
        ans += " ";
        ans += (preornot ? "滚轮后滚" : "滚轮前滚");
    }
    return ans;
}