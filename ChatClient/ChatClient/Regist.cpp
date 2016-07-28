// Regist.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Regist.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
//#include "Header.h"
CClientSocket *pSock2;

// CRegist 对话框

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


// CRegist 消息处理程序


void CRegist::OnBnClickedRegOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(RegistName.IsEmpty())
	{
		AfxMessageBox(_T("用户名不能为空"));
		return;
	}
	if(Password1.IsEmpty()||Password2.IsEmpty())
	{
		AfxMessageBox(_T("密码不能为空"));
		return;
	}
	if(Password1!=Password2)
	{
		AfxMessageBox(_T("两次输入的密码不一致"));
		return;
	}
	char from[20];
	memset(from,0,sizeof(from));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)RegistName,-1,from,260,0,false);
	char beizhu[20];
	memset(beizhu,0,sizeof(beizhu));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)Password1,-1,beizhu,260,0,false);

	char* pBuff = new char[RegistName.GetLength()+1];
	memset(pBuff, 0, RegistName.GetLength());  //开辟一个，存储用户名的内存空间

	if(WChar2MByte(RegistName.GetBuffer(0), pBuff,RegistName.GetLength()+1))
	if(pSock2->Register(pBuff, RegistName.GetLength()+1,from,beizhu))
	{
		AfxMessageBox(_T("注册成功！"));
			delete pBuff;
			CDialogEx::OnOK();//注册成功后，关闭注册窗口
	}
	else
	{
		AfxMessageBox(_T("用户已存在，请重新注册！"));
		delete pBuff;
		return;
	}
}

BOOL CRegist::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	//映射一个宽字符串到一个新的字符串
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<nlen)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

BOOL CRegist::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pSock2 = theApp.GetMainSocket();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRegist::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CRegist::OnBnClickedRegCansel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
