
// ChatClientDlg.h : ͷ�ļ�
//

#pragma once
#include "ChatWindowDlg.h"

// CChatClientDlg �Ի���
class CChatClientDlg : public CDialogEx
{
// ����
public:
	CChatClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATCLIENT };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	CString m_caption;
	void UpdateUserList(CString strInfo);
	afx_msg void OnDblclkListFriend();
	CString list_temp;

	afx_msg void OnBnClickedBtSetmsg();
	afx_msg void OnBnClickedBtTools();
	afx_msg void OnBnClickedBtCalculator();
	virtual void OnOK();
	afx_msg void OnBnClickedDateCalculator();
	afx_msg void OnBnClickedBeiwanglu();
	afx_msg void OnBnClickedBtDz();
};
