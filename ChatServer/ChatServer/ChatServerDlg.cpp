
// ChatServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"
#include "MySQL.h"
#include<fstream>
#include<string>
using namespace std;

static CRect rectL; //切割前的尺寸
static CRect rectS; //切割后的尺寸

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatServerDlg 对话框




CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DELETEUSER, &CChatServerDlg::OnBnClickedDeleteuser)
	ON_BN_CLICKED(IDC_CLOSE, &CChatServerDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_ALLUSER, &CChatServerDlg::OnBnClickedAlluser)
	ON_BN_CLICKED(IDC_DELETEUSER2, &CChatServerDlg::OnBnClickedDeleteuser2)
	ON_LBN_SELCHANGE(IDC_USER_ONLINE, &CChatServerDlg::OnLbnSelchangeUserOnline)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rectSepr;   //初始化登陆对话框的大小
	GetWindowRect(&rectL);
	GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSepr);//picture控件的rect
	rectS.left = rectL.left;
	rectS.top = rectL.top;
	rectS.right = rectSepr.right;
	rectS.bottom = rectL.bottom;
	SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatServerDlg::UpdateUserInfo( CString strUserInfo) const 
{
	CString strTemp;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ONLINE);
	pList->ResetContent();  //清除所有的数据
	while(!strUserInfo.IsEmpty())
	{
		int n = strUserInfo.Find('#');  //查找第一次出现#的位置，读取第一次数据
		strTemp = strUserInfo.Left(n);	
		pList->AddString(strTemp);  //加入数据
		strUserInfo = strUserInfo.Right(strUserInfo.GetLength()-n-1); //减去第一个的位置
	}
}

void CChatServerDlg::OnBnClickedDeleteuser()
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ONLINE);
	INT nIndex = 0 ;
	nIndex = pList->GetCurSel();
	CString DelUser;
	pList->GetText( nIndex, DelUser );
	DeleteUser(CString(DelUser));//删除数据库中的用户信息
	iter=userlist.begin();
	while(iter != userlist.end())  //遍历容器
	{
		if((CString)DelUser == (CString)iter->username)
			iter = userlist.erase(iter); //删除容器中的用户
		else
			iter++;
	}
	//更新所有用户列表
	CListBox* pList2 = (CListBox*)GetDlgItem(IDC_USER_ALL);
	pList2->ResetContent();  //清除所有的数据
	for(iter=userlist.begin();iter!=userlist.end();iter++)
		pList2->AddString(iter->username);  //加入数据
	AfxMessageBox(_T("删除成功，该用户退出后将被系统删除!"));
}


void CChatServerDlg::OnBnClickedClose()
{
	CDialogEx::OnOK();//关闭服务器
}


void CChatServerDlg::OnBnClickedAlluser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if(GetDlgItemText(IDC_ALLUSER,str),str == "<")
	{
		SetDlgItemText(IDC_ALLUSER,_T(">"));
	}
	else
	{
		SetDlgItemText(IDC_ALLUSER,_T("<"));
	}
	if(rectL.IsRectNull())
	{
		CRect rectSepr;
		GetWindowRect(&rectL);
		GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSepr);//picture控件的rect

		rectS.left = rectL.left;
		rectS.top = rectL.top;
		rectS.right = rectSepr.right;
		rectS.bottom = rectL.bottom;
	}
	if(str == "<")     //放大窗口，显示聊天记录
	{
		SetWindowPos(NULL,500,270,rectL.Width(),rectL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ALL);
		pList->ResetContent();  //清除所有的数据
		for(iter=userlist.begin();iter!=userlist.end();iter++)
			pList->AddString(iter->username);  //加入数据
	}
	else     //收缩窗口，关闭聊天记录
	{
		SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ALL);
		pList->ResetContent();  //清除所有的数据
	}
}


void CChatServerDlg::OnBnClickedDeleteuser2()
{
	// TODO: 在此添加控件通知处理程序代码
	CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ALL);
	INT nIndex = 0 ;
	nIndex = pList->GetCurSel();
	CString DelUser;
	pList->GetText( nIndex, DelUser );
	DeleteUser(CString(DelUser));//删除数据库中的用户信息
	iter=userlist.begin();
	while(iter != userlist.end())  //遍历容器
	{
		if((CString)DelUser == (CString)iter->username)
			iter = userlist.erase(iter); //删除容器中的用户
		else
			iter++;
	}
	AfxMessageBox(_T("删除成功!"));
	pList->ResetContent();  //清除所有的数据
	for(iter=userlist.begin();iter!=userlist.end();iter++)
		pList->AddString(iter->username);  //加入数据
}


void CChatServerDlg::OnLbnSelchangeUserOnline()
{
	// TODO: 在此添加控件通知处理程序代码
}
