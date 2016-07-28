#pragma once
#include "afxdtctl.h"


// CDateCaculator 对话框

class CDateCaculator : public CDialogEx
{
	DECLARE_DYNAMIC(CDateCaculator)

public:
	CDateCaculator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDateCaculator();

// 对话框数据
	enum { IDD = IDD_DateCaculator };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl time1;
	CDateTimeCtrl time2;
	afx_msg void OnBnClickedDATECA();
	virtual BOOL OnInitDialog();
};
