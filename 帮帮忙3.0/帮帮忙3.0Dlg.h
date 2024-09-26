
// 帮帮忙3.0Dlg.h: 头文件
//

#pragma once
#include "head.h"

// C帮帮忙30Dlg 对话框
class C帮帮忙30Dlg : public CDialogEx
{
	// 构造
public:
	C帮帮忙30Dlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY30_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_replaytime;
	int replaytime(); //获取还原次数
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnUpdateText(WPARAM wParam, LPARAM lParam); //获取录制、还原时传来的信息
	std::string SelFile(int mode); //文件选择
	afx_msg void OnBnClickedButton2();
	CString m_log;
	void writefile(std::string filename);
	CString readfile(std::string filename);
	void refresh(); //每次完成后刷新页面，重置控件状态
	void showwin(int mode = 0); //设置窗口最大最小化
	CButton m_lz;
	CButton m_hy;
	CStatic m_tips;
	CListCtrl m_tasklist;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit editItem;
	int hitRow;
	int hitCol;
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	bool isnum(CString text);
	afx_msg void OnBnClickedButton3();
	CButton m_reqdelete;
	afx_msg void OnBnClickedButton5();
};


