// SetMsg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "SetMsg.h"
#include "afxdialogex.h"
#include "ChatClientDlg.h"
CClientSocket *pSock3;

// CSetMsg �Ի���

IMPLEMENT_DYNAMIC(CSetMsg, CDialogEx)

CSetMsg::CSetMsg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetMsg::IDD, pParent)
	, set_password1(_T(""))
	, set_password2(_T(""))
	, set_password3(_T(""))
{

}

CSetMsg::~CSetMsg()
{
}

void CSetMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ET_OLDKEY, set_password1);
	DDX_Text(pDX, IDC_ET_NEWKEY, set_password2);
	DDX_Text(pDX, IDC_ET_NEWKEY_2, set_password3);
}


BEGIN_MESSAGE_MAP(CSetMsg, CDialogEx)
	ON_BN_CLICKED(IDC_BT_OK, &CSetMsg::OnBnClickedBtOk)
	ON_BN_CLICKED(IDC_BT_CANCEL, &CSetMsg::OnBnClickedBtCancel)
END_MESSAGE_MAP()


// CSetMsg ��Ϣ�������


void CSetMsg::OnBnClickedBtOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(set_password1.IsEmpty()||set_password2.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ��!"));
		return;
	}
	if(set_password1 == set_password2)
	{
		AfxMessageBox(_T("����û�иĶ�!"));
		return;
	}
	if(set_password2!=set_password3)
	{
		AfxMessageBox(_T("������������벻һ��!"));
		return;
	}
	CString username = theApp.GetMainSocket()->m_UserName; //����û���
	char from[20];
	memset(from,0,sizeof(from));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)username,-1,from,260,0,false);
	char to[20];
	memset(to,0,sizeof(to));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)set_password1,-1,to,260,0,false);
	char beizhu[20];
	memset(beizhu,0,sizeof(beizhu));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)set_password2,-1,beizhu,260,0,false);
	char* pBuff = new char[username.GetLength()+1];
	memset(pBuff, 0, username.GetLength());  //����һ�����洢�û������ڴ�ռ�

	if(WChar2MByte(username.GetBuffer(0), pBuff,username.GetLength()+1))

	if(pSock3->SetMsg(pBuff,username.GetLength()+1,to,from,beizhu))
	{
		delete pBuff;
		AfxMessageBox(_T("�޸ĳɹ�!"));
		CDialogEx::OnOK();//�޸ĳɹ��󣬹ر�ע�ᴰ��
	}
	else
	{
		delete pBuff;
		AfxMessageBox(_T("ԭ�������, �޸�ʧ��!"));
		return;
	}

	UpdateData(0);
}

BOOL CSetMsg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	//ӳ��һ�����ַ�����һ���µ��ַ���
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<nlen)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

void CSetMsg::OnBnClickedBtCancel()  //�˳���Ϣ���ô���
{
	CDialogEx::OnOK();
}



BOOL CSetMsg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pSock3 = theApp.GetMainSocket();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
