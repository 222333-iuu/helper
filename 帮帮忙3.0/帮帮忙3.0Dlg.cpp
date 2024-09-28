
// 帮帮忙3.0Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "帮帮忙3.0.h"
#include "帮帮忙3.0Dlg.h"
#include "afxdialogex.h"
#include "head.h"
#include "md5.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#define WM_USER_UPDATE_TEXT (WM_USER + 1) 
#pragma warning(disable : 4996)
#endif

extern FUNC tempfunc;

class Timer;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C帮帮忙30Dlg 对话框



C帮帮忙30Dlg::C帮帮忙30Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY30_DIALOG, pParent)
	, m_log(_T(""))
	, m_replaytime(_T("1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C帮帮忙30Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_replaytime);
	DDX_Text(pDX, IDC_EDIT3, m_log);
	DDX_Control(pDX, IDC_BUTTON2, m_lz);
	DDX_Control(pDX, IDC_BUTTON1, m_hy);
	DDX_Control(pDX, IDC_TIPS, m_tips);
	DDX_Control(pDX, IDC_LIST1, m_tasklist);
	DDX_Control(pDX, IDC_CHECK1, m_reqdelete);
}

BEGIN_MESSAGE_MAP(C帮帮忙30Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C帮帮忙30Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_USER_UPDATE_TEXT, &C帮帮忙30Dlg::OnUpdateText)
	ON_BN_CLICKED(IDC_BUTTON2, &C帮帮忙30Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &C帮帮忙30Dlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &C帮帮忙30Dlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &C帮帮忙30Dlg::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &C帮帮忙30Dlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON3, &C帮帮忙30Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &C帮帮忙30Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// C帮帮忙30Dlg 消息处理程序

BOOL C帮帮忙30Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString str5[] = { TEXT("编号"), TEXT("路径"), TEXT("执行次数")}; //构建表格的行列  
	m_tasklist.InsertColumn(0, str5[0], 0, 75);
	m_tasklist.InsertColumn(1, str5[1], 0, 450);
	m_tasklist.InsertColumn(2, str5[2], 0, 150);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C帮帮忙30Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C帮帮忙30Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR C帮帮忙30Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int C帮帮忙30Dlg::replaytime() {
	UpdateData(true);
	try {
		std::string s = (CT2A)m_replaytime;
		int num = std::stoi(s);
		return max(num,1);
	}
	catch (const std::invalid_argument& e) {
		return 1;
	}
}


void C帮帮忙30Dlg::OnBnClickedButton1()
{
	FUNC a(1,replaytime());
	std::string filepath = SelFile(1);
	if (filepath == "") return;
	CString filecontent = readfile(filepath);
	if (filecontent.GetLength() > 10) {
		showwin(0);
		refresh();
		a.Translate(filecontent);
		m_replaytime = TEXT("1");
		UpdateData(false);
		showwin(1);
		m_lz.ShowWindow(true);
		m_hy.ShowWindow(true);
	}
	// TODO: 在此添加控件通知处理程序代码
}

LRESULT C帮帮忙30Dlg::OnUpdateText(WPARAM wParam, LPARAM lParam) {
	BSTR bstrText = reinterpret_cast<BSTR>(lParam);
	if (bstrText != nullptr)
	{
		CString text = CString(bstrText); // 从BSTR创建CString
		if (text == TEXT("/clear")) {
			m_log = TEXT("");
		}
		else {
			m_log = TEXT("\r\n") + m_log;
			m_log = text + m_log;
		}
		//UpdateData(false);
		//UpdateWindow();
		SysFreeString(bstrText); // 释放BSTR字符串  
	}
	return 0;
}

std::string C帮帮忙30Dlg::SelFile(int mode) { // 1打开，0保存
	// 创建文件对话框
	CFileDialog fileDlg(mode, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("文本文件(*.txt)|*.txt||All Files (*.*)|*.*||"), NULL);
	// 显示对话框
	if (fileDlg.DoModal() == IDOK)
	{
		// 获取选中的文件路径
		CString selectedFile = fileDlg.GetPathName();
		std::string s = (CT2A)selectedFile;
		if(mode == 0)s += ".txt";
		return s;
	}
	return "";
}



void C帮帮忙30Dlg::OnBnClickedButton2()
{
	refresh();
	showwin(0);
	FUNC a(0);
	showwin(1);
	UpdateData(false);
	std::string filepath = SelFile(0);
	if (filepath != "") writefile(filepath);
	else MessageBox(TEXT("你已取消保存"));
	m_lz.ShowWindow(true);
	m_hy.ShowWindow(true);
	// TODO: 在此添加控件通知处理程序代码
}

void C帮帮忙30Dlg::writefile(std::string filename) {
	CString FileName(filename.c_str());
	CFile file;
	if (!file.Open(FileName, CFile::modeCreate | CFile::modeWrite))
	{
		TRACE(_T("无法打开文件 %s 进行写入\n"), FileName);
		return;
	}
	string temp;
	CString writeinput;
	CStringA  writeinputA;
	for (auto i : tempfunc.eventrem) {
		temp = i.Description();
		writeinput = temp.c_str();
		writeinput += "\r\n";
		writeinputA = CT2A(writeinput);
		file.Write(writeinputA, writeinputA.GetLength());
	}
	file.Close();
}

CString C帮帮忙30Dlg::readfile(std::string filename) {
	CString filePath;
	filePath = filename.c_str();
	CFile file;
	if (!file.Open(filePath, CFile::modeRead | CFile::typeBinary)) {
		AfxMessageBox(_T("无法打开文件"));
		return 0;
	}

	ULONGLONG fileLength = file.GetLength();
	char* buffer = new char[fileLength + 1]; // +1 是为了字符串的终结符'\0'  
	UINT bytesRead = file.Read(buffer, fileLength);
	if (bytesRead != fileLength) {
		AfxMessageBox(_T("读取文件出错"));
		delete[] buffer;
		file.Close();
		return 0;
	}

	buffer[bytesRead] = '\0'; // 确保字符串正确终结  
	CString content(buffer);

	// 这里处理content字符串  

	//MessageBox(content);
	delete[] buffer;
	file.Close();

	return content;
}

void C帮帮忙30Dlg::refresh() {
	UpdateData(true);
	m_log = TEXT("");
	m_lz.ShowWindow(false);
	m_hy.ShowWindow(false);
	UpdateData(false);
}

void C帮帮忙30Dlg::showwin(int mode) {
	CWnd* pWnd = AfxGetMainWnd();
	if (pWnd != nullptr)
	{
		// 最小化窗口  
		if(mode == 0)pWnd->ShowWindow(SW_MINIMIZE);
		else  pWnd->ShowWindow(SW_RESTORE);
	}
}

void C帮帮忙30Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string filepath = SelFile(1);
	if (filepath == "") return;
	CString Filepath(filepath.c_str());

	int index = m_tasklist.GetItemCount();//将数据加到表格中
	CString tmp;
	tmp.Format(_T("%d"), index + 1);
	m_tasklist.InsertItem(index, tmp);
	m_tasklist.SetItemText(index, 1, Filepath);
	m_tasklist.SetItemText(index, 2, TEXT("1"));
}


void C帮帮忙30Dlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void C帮帮忙30Dlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (editItem.m_hWnd != NULL) {
		editItem.ShowWindow(0);
		if (hitRow != -1) {
			CString text;
			editItem.GetWindowText(text);
			if (text.GetLength() == 0 || !isnum(text)) text = TEXT("1");
			m_tasklist.SetItemText(hitRow, hitCol, text);
		}
	}
	hitCol = hitRow = -1;
}


void C帮帮忙30Dlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	if (m_tasklist.SubItemHitTest(&info) != -1)
	{
		hitRow = info.iItem;
		hitCol = info.iSubItem;
		if (hitCol < 2) return;
		if (editItem.m_hWnd == NULL) {
			RECT rect;
			rect.left = 3;
			rect.top = 3;
			rect.bottom = 3;
			rect.right = 3;
			editItem.Create(WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, this, 101);
			editItem.SetFont(this->GetFont(), FALSE);
		}
		CRect rect;
		m_tasklist.GetSubItemRect(info.iItem, info.iSubItem, LVIR_BOUNDS, rect);
		rect.top += 160;
		rect.left += 1030;
		rect.right += 1030;
		rect.bottom += 160;
		editItem.SetWindowText(TEXT(""));
		editItem.MoveWindow(&rect, TRUE);
		editItem.ShowWindow(TRUE);
		editItem.SetFocus();
	}
}

bool C帮帮忙30Dlg::isnum(CString text) {
	string a = (CT2A)text;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] < '0' || a[i] > '9') return false;
	}
	return true;
}

void C帮帮忙30Dlg::OnBnClickedButton3()
{
	showwin(0);
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_tasklist.GetItemCount(); i++) {
		std::string s = (CT2A)m_tasklist.GetItemText(i, 2);
		int num = std::stoi(s);
		FUNC a(1, num);
		string filename = (CT2A)m_tasklist.GetItemText(i, 1);
		CString filecontent = readfile(filename);
		if (filecontent.GetLength() > 10) {
			a.Translate(filecontent);
		}
		if (!a.notend) break;
	}
	if(m_reqdelete.GetCheck()) m_tasklist.DeleteAllItems();
	showwin(1);
}


void C帮帮忙30Dlg::OnBnClickedButton5()
{
	std::string filepath = SelFile(1);
	if (filepath == "") return;
	CString filecontent = readfile(filepath);
	string s = (CT2A)filecontent;
	MD5 m(s);
	FUNC a(1, 1);
	s = a.printtime() + "md5码为:" + m.out + "\t文件:" + filepath;
	UpdateData(true);
	m_log = TEXT("\r\n") + m_log;
	CString k;
	k = s.c_str();
	m_log = k + m_log;
	UpdateData(false);
}//生成MD5码


//111