// SetMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "SetMsg.h"
#include "afxdialogex.h"
#include "ChatClientDlg.h"
CClientSocket *pSock3;

// CSetMsg 对话框

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


// CSetMsg 消息处理程序


void CSetMsg::OnBnClickedBtOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(set_password1.IsEmpty()||set_password2.IsEmpty())
	{
		AfxMessageBox(_T("密码不能为空!"));
		return;
	}
	if(set_password1 == set_password2)
	{
		AfxMessageBox(_T("密码没有改动!"));
		return;
	}
	if(set_password2!=set_password3)
	{
		AfxMessageBox(_T("两次输入的密码不一致!"));
		return;
	}
	CString username = theApp.GetMainSocket()->m_UserName; //获得用户名
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
	memset(pBuff, 0, username.GetLength());  //开辟一个，存储用户名的内存空间

	if(WChar2MByte(username.GetBuffer(0), pBuff,username.GetLength()+1))

	if(pSock3->SetMsg(pBuff,username.GetLength()+1,to,from,beizhu))
	{
		delete pBuff;
		AfxMessageBox(_T("修改成功!"));
		CDialogEx::OnOK();//修改成功后，关闭注册窗口
	}
	else
	{
		delete pBuff;
		AfxMessageBox(_T("原密码错误, 修改失败!"));
		return;
	}

	UpdateData(0);
}

BOOL CSetMsg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	//映射一个宽字符串到一个新的字符串
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<nlen)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

void CSetMsg::OnBnClickedBtCancel()  //退出信息设置窗口
{
	CDialogEx::OnOK();
}



BOOL CSetMsg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pSock3 = theApp.GetMainSocket();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
