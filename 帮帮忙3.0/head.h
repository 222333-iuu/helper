#pragma once
#include "pch.h"
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include<vector>
#include "���æ3.0Dlg.h"
#include "���æ3.0.h"
#define WM_USER_UPDATE_TEXT (WM_USER + 1) 
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0)
#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0:1)
using namespace std;

class Timer {
public:
    int SysTime, BeginTime, LastTime;
    int ResponeTime = 10; // ÿ��0.01����Ӧ
    Timer();
    bool ReqRecord();
    int GetTime();
    int RealTime();
    void reset(int = 50);
    void wait(int time);
};//����Ϊ��λ

class ACTION
{
public:
    POINT location;
    int time, sort; // 0 �����ƶ���1������������ 2������̵��
    bool preornot;
    char press;
    ACTION();
    ACTION(int s, int t, POINT loca); // ���غ������õ���ͬ����
    ACTION(int s, int t, POINT loca ,bool pre, char p); // ���غ������õ���ͬ����
    ACTION(int s, int t, bool pre, char p); // ���غ������õ���ͬ����
    ACTION(int s, int t, bool pre);
    string Description();//��������
    bool when(Timer timer);
};

//��������


class FUNC {
public:
    int mode, time;
    bool notend = true;
    FUNC(int m, int t = 0);
    void Translate(CString a);//ת������
    void replay(vector <ACTION>& eventrem);//���ֺ���
    void record();//¼�ƺ���
    string printtime();//��ӡ��־ʱ��
    vector <ACTION> eventrem;
    Timer timer;
    friend Timer;
    void prereplay();//����ǰ׼��
    void editlog(string tar); //������Ϣ������
    int translatenum(string a, int& index); // ת������
};

static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);//��깳�ӻص�����
static LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);//���̹��ӻص�����