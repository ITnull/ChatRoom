// ChatWindowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatWindowDlg.h"
#include "afxdialogex.h"
#include "ChatClientDlg.h"
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

static CRect rectL; //切割前的尺寸
static CRect rectS; //切割后的尺寸
CString chat_to = _T("");
// CChatWindowDlg 对话框

IMPLEMENT_DYNAMIC(CChatWindowDlg, CDialogEx)

CChatWindowDlg::CChatWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatWindowDlg::IDD, pParent)
	, m_Send(_T(""))
{            //初始化发送消息的对象
}

CChatWindowDlg::~CChatWindowDlg()
{
}

void CChatWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ET_SENDWIND, m_Send);
}


BEGIN_MESSAGE_MAP(CChatWindowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BT_RECORD, &CChatWindowDlg::OnBnClickedBtRecord)
	ON_BN_CLICKED(IDC_BT_SENDMSG, &CChatWindowDlg::OnBnClickedBtSendmsg)
	ON_BN_CLICKED(IDC_BT_REWRITE, &CChatWindowDlg::OnBnClickedBtRewrite)
END_MESSAGE_MAP()


// CChatWindowDlg 消息处理程序


BOOL CChatWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rectSepr;   //初始化登陆对话框的大小
	GetWindowRect(&rectL);
	GetDlgItem(IDC_SEPRATOR2)->GetWindowRect(&rectSepr);//picture控件的rect
	rectS.left = rectL.left;
	rectS.top = rectL.top;
	rectS.right = rectSepr.right;
	rectS.bottom = rectL.bottom;
	SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),NULL);

	//通过找到窗口句柄访问该窗口类中的变量
	HWND hWnd = ::FindWindow(NULL,theApp.GetMainSocket()->m_UserName); //找客户端主界面窗口
	CChatClientDlg* pWnd; 
	pWnd = ((CChatClientDlg*)CWnd::FromHandle(hWnd)); 
	chat_to = pWnd->list_temp;
	SetWindowText(_T("与 ")+chat_to+_T(" 聊天"));  //设置窗口名

	CString filename = chat_to+_T(".txt");
	ifstream in(filename);
	ifstream in2(filename);
	string strline;
	int i =0,j=0;
	while(getline(in, strline)){    //获取聊天记录的行数
		i++;
	}
	while(getline(in2,strline)){   //获取聊天记录
		j++;
		CString abc(strline.c_str());//从文本取数据
		if((i-j)<=5){             //在聊天窗口显示最近的2-3条聊天记录
			CString ab = abc+'\n';   //从文本取一行数据后换行
			((CEdit*)GetDlgItem(IDC_ET_CAHTWIND))->ReplaceSel(ab); //一行一行显示数据
		}
	}

	return TRUE;  
}


void CChatWindowDlg::OnBnClickedBtRecord()   //聊天记录生成
{
	// TODO: 在此添加控件通知处理程序代码
	CString strg;
	if(GetDlgItemText(IDC_BT_RECORD,strg),strg == "聊天记录<<")
	{
		SetDlgItemText(IDC_BT_RECORD,_T("聊天记录>>"));
	}
	else
	{
		SetDlgItemText(IDC_BT_RECORD,_T("聊天记录<<"));
	}
	if(rectL.IsRectNull())
	{
		CRect rectSepr;
		GetWindowRect(&rectL);
		GetDlgItem(IDC_SEPRATOR2)->GetWindowRect(&rectSepr);//picture控件的rect

		rectS.left = rectL.left;
		rectS.top = rectL.top;
		rectS.right = rectSepr.right;
		rectS.bottom = rectL.bottom;
	}
	if(strg == "聊天记录<<")     //放大窗口，显示聊天记录
	{
		SetWindowPos(NULL,500,270,rectL.Width(),rectL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		CString filename = chat_to+_T(".txt");
		ifstream in(filename);
		string strline;
		while(getline(in, strline)) {
			CString abc(strline.c_str());//从文本取数据
			CString ab = abc+'\n';   //从文本取一行数据后换行
			((CEdit*)GetDlgItem(IDC_ET_RECORD))->ReplaceSel(ab); //一行一行显示数据
		}
	}
	else     //收缩窗口，关闭聊天记录
	{
		SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		((CEdit*)GetDlgItem(IDC_ET_RECORD))->SetWindowTextW(_T(""));//清除edit控件内的数据
	}
}


void CChatWindowDlg::OnBnClickedBtSendmsg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_Send.IsEmpty())
	{
		AfxMessageBox(_T("发送内容不能为空！"));
		return ;
	}
	char* to = new char[chat_to.GetLength()*2+1];
	memset(to, 0, chat_to.GetLength()*2+1);
	//转换为多字节
	WChar2MByte(chat_to.GetBuffer(0), to, chat_to.GetLength()*2+1);

	CString m_UserName = theApp.GetMainSocket()->m_UserName;
	char from[20];
	memset(from,0,sizeof(from));
	WChar2MByte(m_UserName.GetBuffer(0), from, m_UserName.GetLength()*2+1);

	char beizhu[20];
	memset(beizhu,0,20);
	CString temp;
	CTime time = CTime::GetCurrentTime();
	temp = time.Format("%H:%M:%S");
	
	m_Send = theApp.GetMainSocket()->m_UserName+_T("  ") + temp +_T("\r\n") + m_Send +_T("\r\n");//发送的内容
	char* pBuff = new char[m_Send.GetLength()*2];
	memset(pBuff, 0, m_Send.GetLength()*2);	
	WChar2MByte(m_Send.GetBuffer(0), pBuff, m_Send.GetLength()*2);

	theApp.GetMainSocket()->SendMsg(pBuff, m_Send.GetLength()*2,to,from,beizhu);
	delete pBuff;
	m_Send.Empty();
	GetDlgItem(IDC_ET_SENDWIND)->SetFocus(); //让编辑框重新获得焦点
	UpdateData(0);
}
BOOL CChatWindowDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);  //返回缓冲区大小
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);   //转换
	return TRUE;
}
void CChatWindowDlg::UpdateText(CString &strText)
{
	((CEdit*)GetDlgItem(IDC_ET_CAHTWIND))->ReplaceSel(strText);  //更新消息
}

void CChatWindowDlg::OnBnClickedBtRewrite()  //重新输入发送的消息
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_Send.Empty();
	GetDlgItem(IDC_ET_SENDWIND)->SetFocus();
	UpdateData(0);
}


void CChatWindowDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::OnOK();
}

