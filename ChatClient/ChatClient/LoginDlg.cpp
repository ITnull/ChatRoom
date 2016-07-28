// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Regist.h"

static CRect rectLarge; //切割前的尺寸
static CRect rectSmall; //切割后的尺寸
CClientSocket* pSock;
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent), m_User(_T(""))
	, m_IP(0)
	, m_Password(_T(""))
{
	//初始化IP地址
	//DWORD 就是unSigned long
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


// CLoginDlg 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CRect rectSeprator;   //初始化登陆对话框的大小
	GetWindowRect(&rectLarge);
	GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSeprator);//picture控件的rect
	rectSmall.left = rectLarge.left;
	rectSmall.top = rectLarge.top;
	rectSmall.right = rectLarge.right;
	rectSmall.bottom = rectSeprator.bottom;
	SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),NULL);
	//链接服务器
	pSock = theApp.GetMainSocket();
	IN_ADDR addr ;
	addr.S_un.S_addr = htonl(m_IP);  //给在登陆界面的上的IP发送数据
	//inet_ntoa是inet_addr的逆函数
	CString strIP(inet_ntoa(addr));  //这时，strIP=“59.69.74.142”?
	//向服务器发出连接请求并判断是否连接成功
	if(!pSock->Connect(strIP.GetBuffer(0),8989))  
	{
		AfxMessageBox(_T("连接服务器失败！"));
		CDialogEx::OnOK();//退出登录窗口
	}
	pSock->m_UserName = m_User;  //将用户ID传递过去
	pSock->m_UserPassword = m_Password;  //密码

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLoginDlg::OnBnClickedBtIpset()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if(GetDlgItemText(IDC_BT_IPSET,str),str == "∧")
	{
		SetDlgItemText(IDC_BT_IPSET,_T("∨"));
	}
	else
	{
		SetDlgItemText(IDC_BT_IPSET,_T("∧"));
	}
	if(rectLarge.IsRectNull())
	{
		CRect rectSeprator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSeprator);//picture控件的rect

		rectSmall.left = rectLarge.left;
		rectSmall.top = rectLarge.top;
		rectSmall.right = rectLarge.right;
		rectSmall.bottom = rectSeprator.bottom;
	}
	if(str == "∧")   
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
	// TODO: 在此添加控件通知处理程序代码
	bool chekflg = 1;
	UpdateData();
	if(m_User.IsEmpty())
	{
		AfxMessageBox(_T("用户名不能为空！"));
		return;
	}
	if(m_Password.IsEmpty())
		{
		AfxMessageBox(_T("密码不能为空！"));
		return;
	}
	if(m_IP==0)
	{
		AfxMessageBox(_T("无效IP地址"));
		return;
	}
	char from[20];
	memset(from,0,sizeof(from));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)m_User,-1,from,260,0,false);
	char beizhu[20];
	memset(beizhu,0,sizeof(beizhu));
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)m_Password,-1,beizhu,260,0,false);

	pSock->m_UserName = m_User;  //将用户ID传递过去
	pSock->m_UserPassword = m_Password;  //密码
	char* pBuff = NULL;
	pBuff = new char[m_User.GetLength()*2+1];
	memset(pBuff, 0, sizeof(char)*(m_User.GetLength()*2+1));  //开辟一个，存储用户名的内存空间
	if(WChar2MByte(m_User.GetBuffer(0), pBuff, m_User.GetLength()*2+1))
		if(pSock->Logoin(pBuff, m_User.GetLength()*2+1, from,beizhu))
			delete pBuff;	
		else
		{
			delete pBuff;
			AfxMessageBox(_T("用户名或密码错误！"));
			return;
		}
	CDialogEx::OnCancel();
}

void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnOK();     //调试时，去掉注释命令
	CDialogEx::OnClose();
}

BOOL CLoginDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	//映射一个宽字符串到一个新的字符串
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(n<strlen(lpDest))
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

void CLoginDlg::OnBnClickedBtRegist()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegist m_regist;
	m_regist.DoModal();
}
