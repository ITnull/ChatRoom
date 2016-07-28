
// ChatClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"
#include "SetMsg.h"
#include "Calculator.h"
#include "SetMsg.h"
#include "DateCaculator.h"
#include "Beiwanglu.h"
#include "Srdz.h"
#include <Windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
static CRect rL; //切割前的尺寸
static CRect rS; //切割后的尺寸

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


// CChatClientDlg 对话框



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatClientDlg::IDD, pParent)
	, m_caption(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_LBN_DBLCLK(IDC_LIST_FRIEND, &CChatClientDlg::OnDblclkListFriend)
	ON_BN_CLICKED(IDC_BT_SETMSG, &CChatClientDlg::OnBnClickedBtSetmsg)
	ON_BN_CLICKED(IDC_TOOLS, &CChatClientDlg::OnBnClickedBtTools)
	ON_BN_CLICKED(IDC_CALCULATOR, &CChatClientDlg::OnBnClickedBtCalculator)
	ON_BN_CLICKED(IDC_DATE_CALCULATOR, &CChatClientDlg::OnBnClickedDateCalculator)
	ON_BN_CLICKED(IDC_BEIWANGLU, &CChatClientDlg::OnBnClickedBeiwanglu)
	ON_BN_CLICKED(IDC_BT_DZ, &CChatClientDlg::OnBnClickedBtDz)
END_MESSAGE_MAP()


// CChatClientDlg 消息处理程序

BOOL CChatClientDlg::OnInitDialog()
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
	CRect rectClient;   //初始化登陆对话框的大小
	GetWindowRect(&rL);
	GetDlgItem(IDC_SEPRATOR3)->GetWindowRect(&rectClient);//picture控件的rect
	rS.left = rL.left;
	rS.top = rL.top;
	rS.right = rL.right;
	rS.bottom = rectClient.bottom;
	SetWindowPos(NULL,1000,200,rS.Width(),rS.Height(),NULL);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	SetWindowText(m_caption);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CChatClientDlg::OnPaint()
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(MessageBox(_T("确定退出聊天吗？"),LPCTSTR(_T("关闭提示")),MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	CDialogEx::OnClose();
}


void CChatClientDlg::UpdateUserList(CString strInfo)
{
	CString strTmp;
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_LIST_FRIEND);
	pBox->ResetContent();

	CString m_UserName = theApp.GetMainSocket()->m_UserName;
	strInfo = _T("群聊#") + strInfo;

	while(!strInfo.IsEmpty())
	{
		int n = strInfo.Find('#');
		if(n==-1)
			break;
		strTmp = strInfo.Left(n);
		if(strTmp!=m_UserName)
		{
			pBox->AddString(strTmp);
		}
		strInfo = strInfo.Right(strInfo.GetLength()-n-1);
	}
}


void CChatClientDlg::OnDblclkListFriend()
{
	// TODO: 在此添加控件通知处理程序代码
	CChatWindowDlg *m_ChatDlg;
	m_ChatDlg = new CChatWindowDlg();
	if(!m_ChatDlg->m_hWnd)
	{
		CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_FRIEND);
		INT nIndex = 0 ;
		nIndex = pList->GetCurSel();
		pList->GetText( nIndex, list_temp );
		m_ChatDlg->Create(IDD_CHATWINDOW,this);
	}
	m_ChatDlg->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnBnClickedBtSetmsg()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetMsg m_sg;
	m_sg.DoModal();
}


void CChatClientDlg::OnBnClickedBtTools()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strg;
	if(GetDlgItemText(IDC_TOOLS,strg),strg == "小工具∧")
	{
		SetDlgItemText(IDC_TOOLS,_T("小工具∨"));
	}
	else
	{
		SetDlgItemText(IDC_TOOLS,_T("小工具∧"));
	}
	if(rL.IsRectNull())
	{
		CRect rectSepr;
		GetWindowRect(&rL);
		GetDlgItem(IDC_SEPRATOR3)->GetWindowRect(&rectSepr);//picture控件的rect

		rS.left = rL.left;
		rS.top = rL.top;
		rS.right = rectSepr.right;
		rS.bottom = rL.bottom;
	}
	if(strg == "小工具∧")     //放大窗口，显示聊天记录
	{
		SetWindowPos(NULL,500,270,rL.Width(),rL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		
	}
	else     //收缩窗口，关闭聊天记录
	{
		SetWindowPos(NULL,500,270,rS.Width(),rS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	}
}


void CChatClientDlg::OnBnClickedBtCalculator()
{
	// TODO: 在此添加控件通知处理程序代码
	CCalculator *m_ca;
	m_ca = new CCalculator();
	if(!m_ca->m_hWnd)
		m_ca->Create(IDD_Calculator,this);
	m_ca->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CChatClientDlg::OnBnClickedDateCalculator()
{
	// TODO: 在此添加控件通知处理程序代码
	CDateCaculator *m_dateca;
	m_dateca = new CDateCaculator();
	if(!m_dateca->m_hWnd)
		m_dateca->Create(IDD_DateCaculator,this);
	m_dateca->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnBnClickedBeiwanglu()
{
	// TODO: 在此添加控件通知处理程序代码
	CBeiwanglu *m_bwl;
	m_bwl = new CBeiwanglu();
	if(!m_bwl->m_hWnd)
		m_bwl->Create(IDD_BEIWANGLU,this);
	m_bwl->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnBnClickedBtDz()
{
	// TODO: 在此添加控件通知处理程序代码
	CSrdz *m_dz;
	m_dz = new CSrdz();
	if(!m_dz->m_hWnd)
		m_dz->Create(IDD_DZ,this);
	m_dz->ShowWindow(SW_SHOW);
}
