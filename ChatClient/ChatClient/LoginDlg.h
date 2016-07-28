#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_User;
	DWORD m_IP;
	afx_msg void OnBnClickedBtIpset();
	afx_msg void OnBnClickedBtLogin();
	afx_msg void OnClose();
	CString m_Password;
	afx_msg void OnBnClickedBtRegist();
};
