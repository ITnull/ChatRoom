#pragma once
#include "afxdtctl.h"


// CDateCaculator �Ի���

class CDateCaculator : public CDialogEx
{
	DECLARE_DYNAMIC(CDateCaculator)

public:
	CDateCaculator(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDateCaculator();

// �Ի�������
	enum { IDD = IDD_DateCaculator };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl time1;
	CDateTimeCtrl time2;
	afx_msg void OnBnClickedDATECA();
	virtual BOOL OnInitDialog();
};
