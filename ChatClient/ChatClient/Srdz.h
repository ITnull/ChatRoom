#pragma once


// CSrdz �Ի���

class CSrdz : public CDialogEx
{
	DECLARE_DYNAMIC(CSrdz)

public:
	CSrdz(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSrdz();

// �Ի�������
	enum { IDD = IDD_DZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString lj_str;
	afx_msg void OnBnClickedDzOpen();
	afx_msg void OnBnClickedDzCancel();
	virtual BOOL OnInitDialog();
};
