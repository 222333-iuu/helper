#include "pch.h"
#include "head.h"
#include "md5.h"

FUNC tempfunc(3);
FUNC& func = tempfunc;
FUNC* funcn;

FUNC::FUNC(int m, int t) { // 0¼�ƣ�1����
    mode = m;
    time = t;
    if(m < 3) func = *this, funcn = this;
    if (m == 0) record();
}


void FUNC::prereplay() {
    for (int i = 0; i < time; i++) {
        editlog("һ���ʼ����");
        timer.wait(1000);
        timer.reset();
        replay(eventrem);
        if (!notend) break;
        if(i < time - 1) editlog("/clear");
        string a = "��ִ�д���:" + to_string(i + 1);
        editlog(a);
    }
}

//��깳�Ӻ���
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MOUSEHOOKSTRUCT* pMouseHookStruct = reinterpret_cast<MOUSEHOOKSTRUCT*>(lParam);
        if (wParam == WM_MOUSEMOVE) {
            if (func.timer.ReqRecord()) {
                POINT mypoint;
                /*mypoint.x = pMouseHookStruct->pt.x, mypoint.y = pMouseHookStruct->pt.y;*/
                GetCursorPos(&mypoint);
                ACTION temp(0, func.timer.RealTime(), mypoint);
                func.editlog(temp.Description());
                func.eventrem.push_back(temp);
            }
        }
        if (wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL) {
            PMSLLHOOKSTRUCT hookStruct = (PMSLLHOOKSTRUCT)lParam;
            int delta = (short)((hookStruct->mouseData >> 16) & 0xffff);
            bool roll = delta > 0 ? 0 : 1;//ǰ��Ϊ0�����Ϊ1
            ACTION temp(3, func.timer.RealTime(), roll);
            func.editlog(temp.Description());
            func.eventrem.push_back(temp);
        }
        if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN || wParam == WM_LBUTTONUP || wParam == WM_RBUTTONUP || wParam == WM_MBUTTONUP) {
            char press;
            POINT loca;
            bool pre;
            if (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP) press = 'l';
            if (wParam == WM_RBUTTONDOWN || wParam == WM_RBUTTONUP) press = 'r';
            if (wParam == WM_MBUTTONDOWN || wParam == WM_MBUTTONUP) press = 'm';
            if (wParam == WM_MBUTTONDOWN || wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN) pre = true;
            else pre = false;
            /*loca.x = pMouseHookStruct->pt.x, loca.y = pMouseHookStruct->pt.y;*/
            GetCursorPos(&loca);
            ACTION temp(1, func.timer.RealTime(), loca, pre, press);
            func.editlog(temp.Description());
            func.eventrem.push_back(temp);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// ���̹��ӻص�����
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (func.mode == 1) {
        KBDLLHOOKSTRUCT* pKeyboardHookStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if ((int)pKeyboardHookStruct->vkCode == 27) {
            funcn -> notend = false;
            func.editlog("�����ж�");
        }
    }
    else if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardHookStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        bool pre = true;
        if (wParam == WM_KEYUP) pre = false;
        if ((int)pKeyboardHookStruct->vkCode == 27) PostQuitMessage(0);
        else {
            char in = (int)pKeyboardHookStruct->vkCode;
            ACTION temp(2, func.timer.RealTime(), pre, in);
            func.editlog(temp.Description());
            func.eventrem.push_back(temp);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

//ת������
void FUNC::Translate(CString content)
{
    CStringArray store;
    int index = 0, emptyline = 0;
    CString takeout;
    while (index < content.GetLength()) {
        takeout = content.Tokenize(TEXT("\n"), index);
        store.Add(takeout);
    }
    int s, t;
    POINT loca;
    bool pre; char p;
    for (int i = 0; i < store.GetSize() ; i++)
    {
        CString line = store.GetAt(i);
        string sline = (CT2A)line;
        int index = 1;
        int type = sline[0] - '0';
        switch (type)
        {
        case 0:
            t = translatenum(sline, index);
            loca.x = translatenum(sline, index);
            loca.y = translatenum(sline, index);
            break;
        case 1:
            t = translatenum(sline, index);
            pre = translatenum(sline, index) == 1 ? true : false;
            index++;
            p = sline[index];
            index++;
            loca.x = translatenum(sline, index);
            loca.y = translatenum(sline, index);
            break;
        case 2:
            t = translatenum(sline, index);
            p = (char)translatenum(sline, index);
            pre = translatenum(sline, index) == 1 ? true : false;
            break;
        case 3:
            t = translatenum(sline, index);
            pre = translatenum(sline, index) == 1 ? true : false;
            break;
        }
        if (type == 0){
            ACTION temp(type, t, loca);
            eventrem.push_back(temp);
        }
        else if (type == 1){
            ACTION temp(type, t, loca, pre, p);
            eventrem.push_back(temp);
        }
        else if (type == 2){
            ACTION temp(type, t, pre, p);
            eventrem.push_back(temp);
        }
        else if(type == 3){
            ACTION temp(type, t, pre);
            eventrem.push_back(temp);
        }
    }
    prereplay();
}

//���ֺ���
void FUNC::replay(vector <ACTION>& eventrem)
{
    MSG msg;
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
    func.editlog("���ֿ�ʼ��");
    for (auto i : eventrem){
        while (1) {
            if (timer.RealTime() >= i.time) {
                switch (i.sort)
                {
                case 0:
                    SetCursorPos(i.location.x, i.location.y);
                    break;
                case 1:
                    switch (i.press) {
                    case 'l':
                        if (i.preornot) {
                            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                        }
                        else {
                            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                        }
                        break;
                    case'r':
                        if (i.preornot) {
                            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                        }
                        else {
                            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                        }
                        break;
                    case'm':
                        if (i.preornot) {
                            mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
                        }
                        else {
                            mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
                        }
                        break;
                    }
                    break;
                case 2:
                    if (i.preornot) {
                        INPUT input[1] = { 0 };
                        // ���¼��̰���  
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wVk = i.press; // ������룬����'A'�������������0x41����VK_A��  
                        input[0].ki.dwFlags = 0; // 0��ʾ���°���  
                        // �����¼����������  
                        SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
                    }
                    else {
                        INPUT input[1] = { 0 };
                        // ���¼��̰���  
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wVk = i.press; // ������룬����'A'�������������0x41����VK_A��  
                        input[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0��ʾ���°���  
                        // �����¼����������  
                        SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
                    }
                    break;
                case 3:
                    if (i.preornot) {
                        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
                    }
                    else {
                        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
                    }
                    break;
                }
            break;
            }
            if (!notend) break;
        }
        editlog(i.Description());
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // ������Ϣ  
            TranslateMessage(&msg);
            // �ַ���Ϣ  
            DispatchMessage(&msg);
        }
        if (!notend) {
            break;
        }
    }
    UnhookWindowsHookEx(keyboardHook);
    if(notend) editlog("������ɣ�");
}

void FUNC::record() {
    editlog("¼�ƿ�ʼ��");
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(mouseHook);
    UnhookWindowsHookEx(keyboardHook);
}


void FUNC::editlog(string tar) {
    if(tar != "/clear")tar = printtime() + tar;
    MD5 m(tar);
    tar = tar + "\tMD5: " + m.out;
    CString ctar(tar.c_str());
    BSTR bstrText = ctar.AllocSysString(); // ����һ��BSTR�ַ���  
    theApp.GetMainWnd()->PostMessage(WM_USER_UPDATE_TEXT, 0, reinterpret_cast<LPARAM>(bstrText));
}


int FUNC::translatenum(string a, int& index) {
    index++;
    int ans = 0;
    bool isfu = false;
    while (index < a.size() && (a[index] >= '0' && a[index] <= '9' || a[index] == '-')) {
        if (a[index] == '-') isfu = true;
        else ans = ans * 10 + a[index] - '0';
        index++;
    }
    if (isfu) ans *= -1;
    return ans;
}

