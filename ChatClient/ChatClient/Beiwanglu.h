#pragma once
#include "afxdtctl.h"


// CBeiwanglu 对话框

class CBeiwanglu : public CDialogEx
{
	DECLARE_DYNAMIC(CBeiwanglu)

public:
	CBeiwanglu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBeiwanglu();

// 对话框数据
	enum { IDD = IDD_BEIWANGLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDateTimeCtrl time;
	afx_msg void OnBnClickedBSave();
	afx_msg void OnBnClickedBCansel();
	afx_msg void OnBnClickedBAdd();
	afx_msg void OnBnClickedBNowrite();
	CString m_write;
	afx_msg void OnBnClickedBOut();
	void bwl_record();
	afx_msg void OnBnClickedButton4();
};
