// Regist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Regist.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
//#include "Header.h"
CClientSocket *pSock2;

// CRegist �Ի���

IMPLEMENT_DYNAMIC(CRegist, CDialogEx)

CRegist::CRegist(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegist::IDD, pParent)
	, RegistName(_T(""))
	, Password1(_T(""))
	, Password2(_T(""))
{

}

CRegist::~CRegist()
{
}

void CRegist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_REG_NAME, RegistName);
	DDX_Text(pDX, IDC_REG_PASSWORD, Password1);
	DDX_Text(pDX, IDC_REG_PSSWORD2, Password2);
}


BEGIN_MESSAGE_MAP(CRegist, CDialogEx)
	ON_BN_CLICKED(IDC_REG_OK, &CRegist::OnBnClickedRegOk)
	ON_BN_CLICKED(IDC_REG_CANSEL, &CRegist::OnBnClickedRegCansel)
END_MESSAGE_MAP()


// CRegist ��Ϣ�������


void CRegist::OnBnClickedRegOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(RegistName.IsEmpty())
	{
		AfxMessageBox(_T("�û�������Ϊ��"));
		return;
	}
	if(Password1.IsEmpty()||Password2.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ��"));
		return;
	}
	if(Password1!=Password2)
	{
		AfxMessageBox(_T("������������벻һ��"));
		return;
	}
	char from[20];
	memset(from,0,sizeof(from));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)RegistName,-1,from,260,0,false);
	char beizhu[20];
	memset(beizhu,0,sizeof(beizhu));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)Password1,-1,beizhu,260,0,false);

	char* pBuff = new char[RegistName.GetLength()+1];
	memset(pBuff, 0, RegistName.GetLength());  //����һ�����洢�û������ڴ�ռ�

	if(WChar2MByte(RegistName.GetBuffer(0), pBuff,RegistName.GetLength()+1))
	if(pSock2->Register(pBuff, RegistName.GetLength()+1,from,beizhu))
	{
		AfxMessageBox(_T("ע��ɹ���"));
			delete pBuff;
			CDialogEx::OnOK();//ע��ɹ��󣬹ر�ע�ᴰ��
	}
	else
	{
		AfxMessageBox(_T("�û��Ѵ��ڣ�������ע�ᣡ"));
		delete pBuff;
		return;
	}
}

BOOL CRegist::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	//ӳ��һ�����ַ�����һ���µ��ַ���
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<nlen)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

BOOL CRegist::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pSock2 = theApp.GetMainSocket();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRegist::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CRegist::OnBnClickedRegCansel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
