// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Regist.h"

static CRect rectLarge; //�и�ǰ�ĳߴ�
static CRect rectSmall; //�и��ĳߴ�
CClientSocket* pSock;
// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent), m_User(_T(""))
	, m_IP(0)
	, m_Password(_T(""))
{
	//��ʼ��IP��ַ
	//DWORD ����unSigned long
	m_IP = ntohl(inet_addr("127.0.0.1"));
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IP_ADDR, m_IP);
	DDX_Text(pDX, IDC_ET_USER, m_User);
	DDX_Text(pDX, IDC_ET_PASSWORD, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BT_IPSET, &CLoginDlg::OnBnClickedBtIpset)
	ON_BN_CLICKED(IDC_BT_LOGIN, &CLoginDlg::OnBnClickedBtLogin)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BT_REGIST, &CLoginDlg::OnBnClickedBtRegist)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectSeprator;   //��ʼ����½�Ի���Ĵ�С
	GetWindowRect(&rectLarge);
	GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSeprator);//picture�ؼ���rect
	rectSmall.left = rectLarge.left;
	rectSmall.top = rectLarge.top;
	rectSmall.right = rectLarge.right;
	rectSmall.bottom = rectSeprator.bottom;
	SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),NULL);
	//���ӷ�����
	pSock = theApp.GetMainSocket();
	IN_ADDR addr ;
	addr.S_un.S_addr = htonl(m_IP);  //���ڵ�½������ϵ�IP��������
	//inet_ntoa��inet_addr���溯��
	CString strIP(inet_ntoa(addr));  //��ʱ��strIP=��59.69.74.142��?
	//��������������������ж��Ƿ����ӳɹ�
	if(!pSock->Connect(strIP.GetBuffer(0),8989))  
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));
		CDialogEx::OnOK();//�˳���¼����
	}
	pSock->m_UserName = m_User;  //���û�ID���ݹ�ȥ
	pSock->m_UserPassword = m_Password;  //����

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLoginDlg::OnBnClickedBtIpset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	if(GetDlgItemText(IDC_BT_IPSET,str),str == "��")
	{
		SetDlgItemText(IDC_BT_IPSET,_T("��"));
	}
	else
	{
		SetDlgItemText(IDC_BT_IPSET,_T("��"));
	}
	if(rectLarge.IsRectNull())
	{
		CRect rectSeprator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSeprator);//picture�ؼ���rect

		rectSmall.left = rectLarge.left;
		rectSmall.top = rectLarge.top;
		rectSmall.right = rectLarge.right;
		rectSmall.bottom = rectSeprator.bottom;
	}
	if(str == "��")   
	{
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	}
}

void CLoginDlg::OnBnClickedBtLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool chekflg = 1;
	UpdateData();
	if(m_User.IsEmpty())
	{
		AfxMessageBox(_T("�û�������Ϊ�գ�"));
		return;
	}
	if(m_Password.IsEmpty())
		{
		AfxMessageBox(_T("���벻��Ϊ�գ�"));
		return;
	}
	if(m_IP==0)
	{
		AfxMessageBox(_T("��ЧIP��ַ"));
		return;
	}
	char from[20];
	memset(from,0,sizeof(from));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)m_User,-1,from,260,0,false);
	char beizhu[20];
	memset(beizhu,0,sizeof(beizhu));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)m_Password,-1,beizhu,260,0,false);

	pSock->m_UserName = m_User;  //���û�ID���ݹ�ȥ
	pSock->m_UserPassword = m_Password;  //����
	char* pBuff = NULL;
	pBuff = new char[m_User.GetLength()*2+1];
	memset(pBuff, 0, sizeof(char)*(m_User.GetLength()*2+1));  //����һ�����洢�û������ڴ�ռ�
	if(WChar2MByte(m_User.GetBuffer(0), pBuff, m_User.GetLength()*2+1))
		if(pSock->Logoin(pBuff, m_User.GetLength()*2+1, from,beizhu))
			delete pBuff;	
		else
		{
			delete pBuff;
			AfxMessageBox(_T("�û������������"));
			return;
		}
	CDialogEx::OnCancel();
}

void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnOK();     //����ʱ��ȥ��ע������
	CDialogEx::OnClose();
}

BOOL CLoginDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	//ӳ��һ�����ַ�����һ���µ��ַ���
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<strlen(lpDest))
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

void CLoginDlg::OnBnClickedBtRegist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegist m_regist;
	m_regist.DoModal();
}
