
// ChatServerDlg.h : ͷ�ļ�
//

#pragma once


// CChatServerDlg �Ի���
class CChatServerDlg : public CDialogEx
{
// ����
public:
	CChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void UpdateUserInfo(CString strUserInfo) const;

// �Ի�������
	enum { IDD = IDD_CHATSERVER_DIALOG };

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
	afx_msg void OnBnClickedDeleteuser();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedAlluser();
	afx_msg void OnBnClickedDeleteuser2();
	afx_msg void OnLbnSelchangeUserOnline();
};
