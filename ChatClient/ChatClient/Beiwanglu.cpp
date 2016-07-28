// Beiwanglu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Beiwanglu.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
using namespace std;
static CRect b_rectL; //�и�ǰ�ĳߴ�
static CRect b_rectS; //�и��ĳߴ�

// CBeiwanglu �Ի���

IMPLEMENT_DYNAMIC(CBeiwanglu, CDialogEx)

CBeiwanglu::CBeiwanglu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBeiwanglu::IDD, pParent)
	, m_write(_T(""))
{

}

CBeiwanglu::~CBeiwanglu()
{
}

void CBeiwanglu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, time);
	DDX_Text(pDX, IDC_B_WRITE, m_write);
}


BEGIN_MESSAGE_MAP(CBeiwanglu, CDialogEx)
	ON_BN_CLICKED(IDC_B_SAVE, &CBeiwanglu::OnBnClickedBSave)
	ON_BN_CLICKED(IDC_B_CANSEL, &CBeiwanglu::OnBnClickedBCansel)
	ON_BN_CLICKED(IDC_B_ADD, &CBeiwanglu::OnBnClickedBAdd)
	ON_BN_CLICKED(IDC_B_NOWRITE, &CBeiwanglu::OnBnClickedBNowrite)
	ON_BN_CLICKED(IDC_B_OUT, &CBeiwanglu::OnBnClickedBOut)
	ON_BN_CLICKED(IDC_BUTTON4, &CBeiwanglu::OnBnClickedButton4)
END_MESSAGE_MAP()


// CBeiwanglu ��Ϣ�������


BOOL CBeiwanglu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString bwl = _T("����¼.txt");
	ifstream find(bwl);
	if(!find)
	{
		ofstream file(bwl,ios::out);
	}
	CRect b_rectSepr;   //��ʼ����½�Ի���Ĵ�С
	GetWindowRect(&b_rectL);
	GetDlgItem(IDC_SEPRATOR4)->GetWindowRect(&b_rectSepr);//picture�ؼ���rect
	b_rectS.left = b_rectL.left;
	b_rectS.top = b_rectL.top;
	b_rectS.right = b_rectSepr.right;
	b_rectS.bottom = b_rectL.bottom;
	SetWindowPos(NULL,500,270,b_rectS.Width(),b_rectS.Height(),NULL);
	bwl_record();  //���뱸��¼
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CBeiwanglu::OnBnClickedBSave()
{
	UpdateData();
	if(m_write == _T(""))
	{
		AfxMessageBox(_T("������Ҫ��¼���¼���"));
		return;
	}
	CTime m_date;
	time.GetTime(m_date);
	int year = m_date.GetYear();
	int month = m_date.GetMonth();
	int day = m_date.GetDay();
	int hour = m_date.GetHour();
	int minute = m_date.GetMinute();
	CString ye,mo,da,ho,mi,str;
	ye.Format(_T("%d"),year);
	mo.Format(_T("%d"),month);
	da.Format(_T("%d"),day);
	ho.Format(_T("%d"),hour);
	mi.Format(_T("%d"),minute);
	if(minute<10)
	{
		mi = _T("0")+mi;
	}
	str = ye+_T("��")+mo+_T("��")+da+_T("�� ")+ho+_T(":")+mi+_T("\r\n")+m_write+_T("\r\n")+_T("\r\n");
	ofstream ofs("����¼.txt",ios::app); 
	//�ַ�ת��
	char* temp = new char[str.GetLength()*2];
	memset(temp,0,str.GetLength()*2);
	WideCharToMultiByte(CP_OEMCP, 0, str.GetBuffer(0), -1, temp, str.GetLength()*2, 0, FALSE);
	int len = strlen(temp);
	ofs.write(temp,len);  //д������ʱ��
	ofs.flush();  
	ofs.close(); 
	m_write = _T("");
	SetWindowPos(NULL,500,270,b_rectS.Width(),b_rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	((CEdit*)GetDlgItem(IDC_B_SHOW))->SetWindowTextW(_T(""));//�ڸ���ǰ�����edit�ؼ��ڵ�����
	bwl_record(); //���±���¼
	UpdateData(0);
}


void CBeiwanglu::OnBnClickedBCansel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_write = _T("");
	UpdateData(0);
}


void CBeiwanglu::OnBnClickedBAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetWindowPos(NULL,500,270,b_rectL.Width(),b_rectL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
}




void CBeiwanglu::OnBnClickedBNowrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetWindowPos(NULL,500,270,b_rectS.Width(),b_rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
}


void CBeiwanglu::OnBnClickedBOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void CBeiwanglu::bwl_record()
{
	CString filename = _T("����¼.txt");
	ifstream ins(filename);
	string strline;
	while(getline(ins, strline)){
		CString abc(strline.c_str());//���ı�ȡ����
		CString ab = abc+'\n';   //���ı�ȡһ�����ݺ���
		((CEdit*)GetDlgItem(IDC_B_SHOW))->ReplaceSel(ab); //һ��һ����ʾ����
	}
}

void CBeiwanglu::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("���Ҫ��ձ���¼��"),MB_OKCANCEL);
	fstream file(_T("����¼.txt"),ios::out);
	bwl_record();//���±���¼
}
