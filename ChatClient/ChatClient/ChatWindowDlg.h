#pragma once
#include "afxwin.h"


// CChatWindowDlg �Ի���

class CChatWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatWindowDlg)

public:
	CChatWindowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatWindowDlg();

// �Ի�������
	enum { IDD = IDD_CHATWINDOW };
	void UpdateText(CString& strText);  //���������¼
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
