
// ChatClientDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
static CRect rL; //�и�ǰ�ĳߴ�
static CRect rS; //�и��ĳߴ�

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


// CChatClientDlg �Ի���



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


// CChatClientDlg ��Ϣ�������

BOOL CChatClientDlg::OnInitDialog()
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
	CRect rectClient;   //��ʼ����½�Ի���Ĵ�С
	GetWindowRect(&rL);
	GetDlgItem(IDC_SEPRATOR3)->GetWindowRect(&rectClient);//picture�ؼ���rect
	rS.left = rL.left;
	rS.top = rL.top;
	rS.right = rL.right;
	rS.bottom = rectClient.bottom;
	SetWindowPos(NULL,1000,200,rS.Width(),rS.Height(),NULL);

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	SetWindowText(m_caption);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(MessageBox(_T("ȷ���˳�������"),LPCTSTR(_T("�ر���ʾ")),MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	CDialogEx::OnClose();
}


void CChatClientDlg::UpdateUserList(CString strInfo)
{
	CString strTmp;
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_LIST_FRIEND);
	pBox->ResetContent();

	CString m_UserName = theApp.GetMainSocket()->m_UserName;
	strInfo = _T("Ⱥ��#") + strInfo;

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSetMsg m_sg;
	m_sg.DoModal();
}


void CChatClientDlg::OnBnClickedBtTools()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strg;
	if(GetDlgItemText(IDC_TOOLS,strg),strg == "С���ߡ�")
	{
		SetDlgItemText(IDC_TOOLS,_T("С���ߡ�"));
	}
	else
	{
		SetDlgItemText(IDC_TOOLS,_T("С���ߡ�"));
	}
	if(rL.IsRectNull())
	{
		CRect rectSepr;
		GetWindowRect(&rL);
		GetDlgItem(IDC_SEPRATOR3)->GetWindowRect(&rectSepr);//picture�ؼ���rect

		rS.left = rL.left;
		rS.top = rL.top;
		rS.right = rectSepr.right;
		rS.bottom = rL.bottom;
	}
	if(strg == "С���ߡ�")     //�Ŵ󴰿ڣ���ʾ�����¼
	{
		SetWindowPos(NULL,500,270,rL.Width(),rL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
		
	}
	else     //�������ڣ��ر������¼
	{
		SetWindowPos(NULL,500,270,rS.Width(),rS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	}
}


void CChatClientDlg::OnBnClickedBtCalculator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCalculator *m_ca;
	m_ca = new CCalculator();
	if(!m_ca->m_hWnd)
		m_ca->Create(IDD_Calculator,this);
	m_ca->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CChatClientDlg::OnBnClickedDateCalculator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDateCaculator *m_dateca;
	m_dateca = new CDateCaculator();
	if(!m_dateca->m_hWnd)
		m_dateca->Create(IDD_DateCaculator,this);
	m_dateca->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnBnClickedBeiwanglu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CBeiwanglu *m_bwl;
	m_bwl = new CBeiwanglu();
	if(!m_bwl->m_hWnd)
		m_bwl->Create(IDD_BEIWANGLU,this);
	m_bwl->ShowWindow(SW_SHOW);
}


void CChatClientDlg::OnBnClickedBtDz()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSrdz *m_dz;
	m_dz = new CSrdz();
	if(!m_dz->m_hWnd)
		m_dz->Create(IDD_DZ,this);
	m_dz->ShowWindow(SW_SHOW);
}
