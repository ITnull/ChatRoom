// Calculator.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include <math.h>
//#include <Windows.h>
// CCalculator 对话框

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


// CCalculator 消息处理程序


BOOL CCalculator::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect re;   
	GetWindowRect(&re);
	SetWindowPos(NULL,500,200,re.Width(),re.Height(),NULL);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCalculator::OnBnClickedJ1() //响应单击“按钮1”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ2()//响应单击“按钮2”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ3()//响应单击“按钮3”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ4()//响应单击“按钮4”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ5()//响应单击“按钮5”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ6()//响应单击“按钮6”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ7()//响应单击“按钮7”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ8()//响应单击“按钮8”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ9()//响应单击“按钮9”事件
{
	// TODO: 在此添加控件通知处理程序代码
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

void CCalculator::OnBnClickedJ0()//响应单击“按钮0”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	if(!is_point)
		param = m_str*10;
	else
		sum_point++;
	m_str = param;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJPoint()//响应单击“按钮.”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	is_point = true;
	sum_point = 1;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJJia()//响应单击“按钮+”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '+';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJJian()//响应单击“按钮-”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '-';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJChen()//响应单击“按钮*”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '*';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJChu()//响应单击“按钮/”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	result = m_str;
	fuhao = '/';
	m_str = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJKaifang()  //开方
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	m_str = sqrt(m_str);
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJPingfang()//平方
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	m_str = m_str*m_str;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJRewright()//重新开始计算
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	m_str = 0;
	param = 0;
	result = 0;
	is_point =  false;
	sum_point = 0;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJRewright2()//响应按钮“+/-”事件
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	m_str = 0-m_str;
	UpdateData(FALSE);
}

void CCalculator::OnBnClickedJDengyu()
{
	// TODO: 在此添加控件通知处理程序代码
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
			AfxMessageBox(_T("除数不能为零！"));
		}
		break;
	}
	param = 0;
	result = 0;
	is_point = false;
	sum_point = 0;
	UpdateData(FALSE);
}
