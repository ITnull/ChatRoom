#pragma once


// CSetMsg �Ի���

class CSetMsg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetMsg)

public:
	CSetMsg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetMsg();

// �Ի�������
	enum { IDD = IDD_SETMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtOk();
	afx_msg void OnBnClickedBtCancel();
	CString set_password1;
	CString set_password2;
	CString set_password3;
	virtual BOOL OnInitDialog();
};
