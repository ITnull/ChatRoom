#pragma once
#include "afxwin.h"


// CCalculator 对话框

class CCalculator : public CDialogEx
{
	DECLARE_DYNAMIC(CCalculator)

public:
	CCalculator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCalculator();

// 对话框数据
	enum { IDD = IDD_Calculator };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	double m_str;
	afx_msg void OnBnClickedJ1();
	afx_msg void OnBnClickedJ2();
	afx_msg void OnBnClickedJ3();
	afx_msg void OnBnClickedJ4();
	afx_msg void OnBnClickedJ5();
	afx_msg void OnBnClickedJ6();
	afx_msg void OnBnClickedJ7();
	afx_msg void OnBnClickedJ8();
	afx_msg void OnBnClickedJ9();
	afx_msg void OnBnClickedJ0();
	afx_msg void OnBnClickedJPoint();
	afx_msg void OnBnClickedJJia();
	afx_msg void OnBnClickedJJian();
	afx_msg void OnBnClickedJChen();
	afx_msg void OnBnClickedJChu();
	afx_msg void OnBnClickedJKaifang();
	afx_msg void OnBnClickedJPingfang();
	afx_msg void OnBnClickedJRewright();
	afx_msg void OnBnClickedJRewright2();
	afx_msg void OnBnClickedJDengyu();
	int sum_point;
	bool is_point;
	double result;
	double param;
	char fuhao;
};
