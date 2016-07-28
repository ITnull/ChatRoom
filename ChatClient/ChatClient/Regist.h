#pragma once


// CRegist 对话框

class CRegist : public CDialogEx
{
	DECLARE_DYNAMIC(CRegist)

public:
	CRegist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegist();

// 对话框数据
	enum { IDD = IDD_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	DECLARE_MESSAGE_MAP()
public:
	CString RegistName;
	CString Password1;
	CString Password2;
	afx_msg void OnBnClickedRegOk();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedRegCansel();
};
