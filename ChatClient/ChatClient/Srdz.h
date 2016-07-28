#pragma once


// CSrdz 对话框

class CSrdz : public CDialogEx
{
	DECLARE_DYNAMIC(CSrdz)

public:
	CSrdz(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSrdz();

// 对话框数据
	enum { IDD = IDD_DZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString lj_str;
	afx_msg void OnBnClickedDzOpen();
	afx_msg void OnBnClickedDzCancel();
	virtual BOOL OnInitDialog();
};
