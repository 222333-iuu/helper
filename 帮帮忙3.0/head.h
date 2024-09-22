#pragma once
#include "pch.h"
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include<vector>
#include "帮帮忙3.0Dlg.h"
#include "帮帮忙3.0.h"
#define WM_USER_UPDATE_TEXT (WM_USER + 1) 
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0)
#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0:1)
using namespace std;

class Timer {
public:
    int SysTime, BeginTime, LastTime;
    int ResponeTime = 10; // 每隔0.01秒响应
    Timer();
    bool ReqRecord();
    int GetTime();
    int RealTime();
    void reset(int = 50);
    void wait(int time);
};//毫秒为单位

class ACTION
{
public:
    POINT location;
    int time, sort; // 0 代表移动，1代表鼠标操作， 2代表键盘点击
    bool preornot;
    char press;
    ACTION();
    ACTION(int s, int t, POINT loca); // 重载函数，得到不同种类
    ACTION(int s, int t, POINT loca ,bool pre, char p); // 重载函数，得到不同种类
    ACTION(int s, int t, bool pre, char p); // 重载函数，得到不同种类
    ACTION(int s, int t, bool pre);
    string Description();//操作描述
    bool when(Timer timer);
};

//函数声明


class FUNC {
public:
    int mode, time;
    bool notend = true;
    FUNC(int m, int t = 0);
    void Translate(CString a);//转换函数
    void replay(vector <ACTION>& eventrem);//复现函数
    void record();//录制函数
    string printtime();//打印日志时间
    vector <ACTION> eventrem;
    Timer timer;
    friend Timer;
    void prereplay();//复现前准备
    void editlog(string tar); //发送消息给窗口
    int translatenum(string a, int& index); // 转换数字
};

static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);//鼠标钩子回调函数
static LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);//键盘钩子回调函数