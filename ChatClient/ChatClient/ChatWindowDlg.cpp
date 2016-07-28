// ChatWindowDlg.cpp : ʵ���ļ�
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

static CRect rectL; //�и�ǰ�ĳߴ�
static CRect rectS; //�и��ĳߴ�
CString chat_to = _T("");
// CChatWindowDlg �Ի���

IMPLEMENT_DYNAMIC(CChatWindowDlg, CDialogEx)

CChatWindowDlg::CChatWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatWindowDlg::IDD, pParent)
	, m_Send(_T(""))
{            //��ʼ��������Ϣ�Ķ���
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


// CChatWindowDlg ��Ϣ�������


BOOL CChatWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectSepr;   //��ʼ����½�Ի���Ĵ�С
	GetWindowRect(&rectL);
	GetDlgItem(IDC_SEPRATOR2)->GetWindowRect(&rectSepr);//picture�ؼ���rect
	rectS.left = rectL.left;
	rectS.top = rectL.top;
	rectS.right = rectSepr.right;
	rectS.bottom = rectL.bottom;
	SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),NULL);

	//ͨ���ҵ����ھ�����ʸô������еı���
	HWND hWnd = ::FindWindow(NULL,theApp.GetMainSocket()->m_UserName); //�ҿͻ��������洰��
	CChatClientDlg* pWnd; 
	pWnd = ((CChatClientDlg*)CWnd::FromHandle(hWnd)); 
	chat_to = pWnd->list_temp;
	SetWindowText(_T("�� ")+chat_to+_T(" ����"));  //���ô�����

	CString filename = chat_to+_T(".txt");
	ifstream in(filename);
	ifstream in2(filename);
	string strline;
	int i =0,j=0;
	while(getline(in, strline)){    //��ȡ�����¼������
		i++;
	}
	while(getline(in2,strline)){   //��ȡ�����¼
		j++;
		CString abc(strline.c_str());//���ı�ȡ����
		if((i-j)<=5){             //�����촰����ʾ�����2-3�������¼
			CString ab = abc+'\n';   //���ı�ȡһ�����ݺ���
			((CEdit*)GetDlgItem(IDC_ET_CAHTWIND))->ReplaceSel(ab); //һ��һ����ʾ����
		}
	}

	return TRUE;  
}


void CChatWindowDlg::OnBnClickedBtRecord()   //�����¼����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strg;
	if(GetDlgItemText(IDC_BT_RECORD,strg),strg == "�����¼<<")
	{
		SetDlgItemText(IDC_BT_RECORD,_T("�����¼>>"));
	}
	else
	{
		SetDlgItemText(IDC_BT_RECORD,_T("�����¼<<"));
	}
	if(rectL.IsRectNull())
	{
		CRect rectSepr;
		GetWindowRect(&rectL);
		GetDlgItem(IDC_SEPRATOR2)->GetWindowRect(&rectSepr);//picture�ؼ���rect

		rectS.left = rectL.left;
		rectS.top = rectL.top;
		rectS.right = rectSepr.right;
		rectS.bottom = rectL.bottom;
	}
	if(strg == "�����¼<<")     //�Ŵ󴰿ڣ���ʾ�����¼
	{
		SetWindowPos(NULL,500,270,rectL.Width(),rectL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		CString filename = chat_to+_T(".txt");
		ifstream in(filename);
		string strline;
		while(getline(in, strline)) {
			CString abc(strline.c_str());//���ı�ȡ����
			CString ab = abc+'\n';   //���ı�ȡһ�����ݺ���
			((CEdit*)GetDlgItem(IDC_ET_RECORD))->ReplaceSel(ab); //һ��һ����ʾ����
		}
	}
	else     //�������ڣ��ر������¼
	{
		SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		((CEdit*)GetDlgItem(IDC_ET_RECORD))->SetWindowTextW(_T(""));//���edit�ؼ��ڵ�����
	}
}


void CChatWindowDlg::OnBnClickedBtSendmsg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_Send.IsEmpty())
	{
		AfxMessageBox(_T("�������ݲ���Ϊ�գ�"));
		return ;
	}
	char* to = new char[chat_to.GetLength()*2+1];
	memset(to, 0, chat_to.GetLength()*2+1);
	//ת��Ϊ���ֽ�
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
	
	m_Send = theApp.GetMainSocket()->m_UserName+_T("  ") + temp +_T("\r\n") + m_Send +_T("\r\n");//���͵�����
	char* pBuff = new char[m_Send.GetLength()*2];
	memset(pBuff, 0, m_Send.GetLength()*2);	
	WChar2MByte(m_Send.GetBuffer(0), pBuff, m_Send.GetLength()*2);

	theApp.GetMainSocket()->SendMsg(pBuff, m_Send.GetLength()*2,to,from,beizhu);
	delete pBuff;
	m_Send.Empty();
	GetDlgItem(IDC_ET_SENDWIND)->SetFocus(); //�ñ༭�����»�ý���
	UpdateData(0);
}
BOOL CChatWindowDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);  //���ػ�������С
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);   //ת��
	return TRUE;
}
void CChatWindowDlg::UpdateText(CString &strText)
{
	((CEdit*)GetDlgItem(IDC_ET_CAHTWIND))->ReplaceSel(strText);  //������Ϣ
}

void CChatWindowDlg::OnBnClickedBtRewrite()  //�������뷢�͵���Ϣ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_Send.Empty();
	GetDlgItem(IDC_ET_SENDWIND)->SetFocus();
	UpdateData(0);
}


void CChatWindowDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
}

