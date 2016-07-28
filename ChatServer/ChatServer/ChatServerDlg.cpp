
// ChatServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"
#include "MySQL.h"
#include<fstream>
#include<string>
using namespace std;

static CRect rectL; //�и�ǰ�ĳߴ�
static CRect rectS; //�и��ĳߴ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CChatServerDlg �Ի���




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


// CChatServerDlg ��Ϣ�������

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rectSepr;   //��ʼ����½�Ի���Ĵ�С
	GetWindowRect(&rectL);
	GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSepr);//picture�ؼ���rect
	rectS.left = rectL.left;
	rectS.top = rectL.top;
	rectS.right = rectSepr.right;
	rectS.bottom = rectL.bottom;
	SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatServerDlg::UpdateUserInfo( CString strUserInfo) const 
{
	CString strTemp;
	CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ONLINE);
	pList->ResetContent();  //������е�����
	while(!strUserInfo.IsEmpty())
	{
		int n = strUserInfo.Find('#');  //���ҵ�һ�γ���#��λ�ã���ȡ��һ������
		strTemp = strUserInfo.Left(n);	
		pList->AddString(strTemp);  //��������
		strUserInfo = strUserInfo.Right(strUserInfo.GetLength()-n-1); //��ȥ��һ����λ��
	}
}

void CChatServerDlg::OnBnClickedDeleteuser()
{
	CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ONLINE);
	INT nIndex = 0 ;
	nIndex = pList->GetCurSel();
	CString DelUser;
	pList->GetText( nIndex, DelUser );
	DeleteUser(CString(DelUser));//ɾ�����ݿ��е��û���Ϣ
	iter=userlist.begin();
	while(iter != userlist.end())  //��������
	{
		if((CString)DelUser == (CString)iter->username)
			iter = userlist.erase(iter); //ɾ�������е��û�
		else
			iter++;
	}
	//���������û��б�
	CListBox* pList2 = (CListBox*)GetDlgItem(IDC_USER_ALL);
	pList2->ResetContent();  //������е�����
	for(iter=userlist.begin();iter!=userlist.end();iter++)
		pList2->AddString(iter->username);  //��������
	AfxMessageBox(_T("ɾ���ɹ������û��˳��󽫱�ϵͳɾ��!"));
}


void CChatServerDlg::OnBnClickedClose()
{
	CDialogEx::OnOK();//�رշ�����
}


void CChatServerDlg::OnBnClickedAlluser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		GetDlgItem(IDC_SEPRATOR)->GetWindowRect(&rectSepr);//picture�ؼ���rect

		rectS.left = rectL.left;
		rectS.top = rectL.top;
		rectS.right = rectSepr.right;
		rectS.bottom = rectL.bottom;
	}
	if(str == "<")     //�Ŵ󴰿ڣ���ʾ�����¼
	{
		SetWindowPos(NULL,500,270,rectL.Width(),rectL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ALL);
		pList->ResetContent();  //������е�����
		for(iter=userlist.begin();iter!=userlist.end();iter++)
			pList->AddString(iter->username);  //��������
	}
	else     //�������ڣ��ر������¼
	{
		SetWindowPos(NULL,500,270,rectS.Width(),rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ALL);
		pList->ResetContent();  //������е�����
	}
}


void CChatServerDlg::OnBnClickedDeleteuser2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListBox* pList = (CListBox*)GetDlgItem(IDC_USER_ALL);
	INT nIndex = 0 ;
	nIndex = pList->GetCurSel();
	CString DelUser;
	pList->GetText( nIndex, DelUser );
	DeleteUser(CString(DelUser));//ɾ�����ݿ��е��û���Ϣ
	iter=userlist.begin();
	while(iter != userlist.end())  //��������
	{
		if((CString)DelUser == (CString)iter->username)
			iter = userlist.erase(iter); //ɾ�������е��û�
		else
			iter++;
	}
	AfxMessageBox(_T("ɾ���ɹ�!"));
	pList->ResetContent();  //������е�����
	for(iter=userlist.begin();iter!=userlist.end();iter++)
		pList->AddString(iter->username);  //��������
}


void CChatServerDlg::OnLbnSelchangeUserOnline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
