#pragma once
#include "afxwin.h"


// CChatWindowDlg 对话框

class CChatWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatWindowDlg)

public:
	CChatWindowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChatWindowDlg();

// 对话框数据
	enum { IDD = IDD_CHATWINDOW };
	void UpdateText(CString& strText);  //跟新聊天记录
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtRecord();
	afx_msg void OnBnClickedBtSendmsg();
	
protected:
	BOOL WChar2MByte(LPCTSTR lpSrc, LPSTR lpDest, int nlen);
public:
	CString m_Send;
	afx_msg void OnBnClickedBtRewrite();
	virtual void OnOK();
};
