// Srdz.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Srdz.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
using namespace std;
static CString hh;


// CSrdz �Ի���

IMPLEMENT_DYNAMIC(CSrdz, CDialogEx)

CSrdz::CSrdz(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSrdz::IDD, pParent)
	, lj_str(_T(""))
{
	CString filename = _T("����·��.txt");
	ifstream ins(filename);
	string strline;
	getline(ins, strline);
	CString abc(strline.c_str());
	lj_str = abc;
}

CSrdz::~CSrdz()
{
}

void CSrdz::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DZ_LJ, lj_str);
}


BEGIN_MESSAGE_MAP(CSrdz, CDialogEx)
	ON_BN_CLICKED(IDC_DZ_OPEN, &CSrdz::OnBnClickedDzOpen)
	ON_BN_CLICKED(IDC_DZ_CANCEL, &CSrdz::OnBnClickedDzCancel)
END_MESSAGE_MAP()


// CSrdz ��Ϣ�������


void CSrdz::OnBnClickedDzOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	char* temp = new char[lj_str.GetLength()*2];
	memset(temp,0,lj_str.GetLength()*2);
	WideCharToMultiByte(CP_OEMCP, 0, lj_str.GetBuffer(0), -1, temp, lj_str.GetLength()*2, 0, FALSE);
	WinExec(temp,SW_SHOW); //"C:\\Windows\\System32\\calc.exe"
	fstream file(_T("����·��.txt"),ios::out); //�����
	ofstream ofs("����·��.txt",ios::app);  //�����
	int len = strlen(temp);
	ofs.write(temp,len);  //д������ʱ��
	ofs.flush();  
	ofs.close(); 
	CSrdz();
	CDialogEx::OnOK();
	UpdateData(0);
}


void CSrdz::OnBnClickedDzCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL CSrdz::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString lj = _T("����·��.txt");
	ifstream find(lj);
	if(!find)
	{
		ofstream file(lj,ios::out);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
