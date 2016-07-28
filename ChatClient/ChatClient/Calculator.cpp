// Calculator.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include <math.h>
//#include <Windows.h>
// CCalculator �Ի���

IMPLEMENT_DYNAMIC(CCalculator, CDialogEx)

CCalculator::CCalculator(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculator::IDD, pParent)
	, m_str(0.0)
	, sum_point(0)
	, is_point(false)
	, result(0)
	, param(0)
	, fuhao(0)
{

}

CCalculator::~CCalculator()
{
}

void CCalculator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_J_SHOW, m_str);
}


BEGIN_MESSAGE_MAP(CCalculator, CDialogEx)
	ON_BN_CLICKED(IDC_J_1, &CCalculator::OnBnClickedJ1)
	ON_BN_CLICKED(IDC_J_2, &CCalculator::OnBnClickedJ2)
	ON_BN_CLICKED(IDC_J_3, &CCalculator::OnBnClickedJ3)
	ON_BN_CLICKED(IDC_J_4, &CCalculator::OnBnClickedJ4)
	ON_BN_CLICKED(IDC_J_5, &CCalculator::OnBnClickedJ5)
	ON_BN_CLICKED(IDC_J_6, &CCalculator::OnBnClickedJ6)
	ON_BN_CLICKED(IDC_J_7, &CCalculator::OnBnClickedJ7)
	ON_BN_CLICKED(IDC_J_8, &CCalculator::OnBnClickedJ8)
	ON_BN_CLICKED(IDC_J_9, &CCalculator::OnBnClickedJ9)
	ON_BN_CLICKED(IDC_J_0, &CCalculator::OnBnClickedJ0)
	ON_BN_CLICKED(IDC_J_POINT, &CCalculator::OnBnClickedJPoint)
	ON_BN_CLICKED(IDC_J_JIA, &CCalculator::OnBnClickedJJia)
	ON_BN_CLICKED(IDC_J_JIAN, &CCalculator::OnBnClickedJJian)
	ON_BN_CLICKED(IDC_J_CHEN, &CCalculator::OnBnClickedJChen)
	ON_BN_CLICKED(IDC_J_CHU, &CCalculator::OnBnClickedJChu)
	ON_BN_CLICKED(IDC_J_KAIFANG, &CCalculator::OnBnClickedJKaifang)
	ON_BN_CLICKED(IDC_J_PINGFANG, &CCalculator::OnBnClickedJPingfang)
	ON_BN_CLICKED(IDC_J_REWRIGHT, &CCalculator::OnBnClickedJRewright)
	ON_BN_CLICKED(IDC_J_REWRIGHT2, &CCalculator::OnBnClickedJRewright2)
	ON_BN_CLICKED(IDC_J_DENGYU, &CCalculator::OnBnClickedJDengyu)
END_MESSAGE_MAP()


// CCalculator ��Ϣ�������


BOOL CCalculator::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect re;   
	GetWindowRect(&re);
	SetWindowPos(NULL,500,200,re.Width(),re.Height(),NULL);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCalculator::OnBnClickedJ1() //��Ӧ��������ť1���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+1;
	else
	{
		param = m_str+1/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ2()//��Ӧ��������ť2���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+2;
	else
	{
		param = m_str+2/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ3()//��Ӧ��������ť3���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+3;
	else
	{
		param = m_str+3/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ4()//��Ӧ��������ť4���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+4;
	else
	{
		param = m_str+4/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ5()//��Ӧ��������ť5���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+5;
	else
	{
		param = m_str+5/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ6()//��Ӧ��������ť6���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+6;
	else
	{
		param = m_str+6/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ7()//��Ӧ��������ť7���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+7;
	else
	{
		param = m_str+7/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ8()//��Ӧ��������ť8���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+8;
	else
	{
		param = m_str+8/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ9()//��Ӧ��������ť9���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10+9;
	else
	{
		param = m_str+9/pow((double)10,sum_point);
		sum_point++;
	}
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJ0()//��Ӧ��������ť0���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10;
	else
		sum_point++;
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJPoint()//��Ӧ��������ť.���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	is_point = true;
	sum_point = 1;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJJia()//��Ӧ��������ť+���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '+';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJJian()//��Ӧ��������ť-���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '-';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJChen()//��Ӧ��������ť*���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '*';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJChu()//��Ӧ��������ť/���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '/';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJKaifang()  //����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	m_str = sqrt(m_str);
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJPingfang()//ƽ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	m_str = m_str*m_str;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJRewright()//���¿�ʼ����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	m_str = 0;
	param = 0;
	result = 0;
	is_point =  false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJRewright2()//��Ӧ��ť��+/-���¼�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	m_str = 0-m_str;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJDengyu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	param = m_str;
	switch(fuhao)
	{
	case'+':
		result += param;
		m_str = result;
		break;
	case'-':
		result -= param;
		m_str = result;
		break;
	case'*':
		result *= param;
		m_str = result;	
		break;
	case'/':
		if(param)
		{
			result /= param;
			m_str = result;
		}
		else
		{
			m_str = 0;
			AfxMessageBox(_T("��������Ϊ�㣡"));
		}
		break;
	}
	param = 0;
	result = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}
