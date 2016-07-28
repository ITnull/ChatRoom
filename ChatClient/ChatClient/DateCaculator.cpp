// DateCaculator.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "DateCaculator.h"
#include "afxdialogex.h"
#define SYEAP(x)x%100!=0&&x%4==0||x%400==0?1:0
int dayofmonth[13][2]={
	0,0,
		31,31,
		28,29,
		31,31,
		30,30,
		31,31,
		30,30,
		31,31,
		31,31,
		30,30,
		31,31,
		30,30,
		31,31,

};
struct date{
	int day;
	int month;
	int year;

	void nextday(){
		day++;
		if(day>dayofmonth[month][SYEAP(year)]){
			day=1;
			month++;
			if(month>12)
			{
				month=1;
				year++;
			}
		}
	}
};
int buf[5001][13][32];
int abs(int x){
	return x<0?-x:x;
}
// CDateCaculator 对话框

IMPLEMENT_DYNAMIC(CDateCaculator, CDialogEx)

CDateCaculator::CDateCaculator(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDateCaculator::IDD, pParent)
{

}

CDateCaculator::~CDateCaculator()
{
}

void CDateCaculator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, time1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, time2);
}


BEGIN_MESSAGE_MAP(CDateCaculator, CDialogEx)
	ON_BN_CLICKED(IDC_BT_DATECA, &CDateCaculator::OnBnClickedDATECA)
END_MESSAGE_MAP()


// CDateCaculator 消息处理程序


void CDateCaculator::OnBnClickedDATECA()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CTime m_date1; 
	time1.GetTime(m_date1);//今日日期
	int year1 = m_date1.GetYear();
	int month1 = m_date1.GetMonth();
	int day1 = m_date1.GetDay();
	CTime m_date2;
	time2.GetTime(m_date2);//目标日期
	int year2 = m_date2.GetYear();
	int month2 = m_date2.GetMonth();
	int day2 = m_date2.GetDay();

	date tmp;
	int cnt=0;
	tmp.day=1;
	tmp.month=1;
	tmp.year=0;

	while(tmp.year!=5001)
	{
		buf[tmp.year][tmp.month][tmp.day]=cnt;
		tmp.nextday();
		cnt++;
	}
	int dategap = abs(buf[year2][month2][day2]-buf[year1][month1][day1]);
	CString strd,str;
	strd.Format(_T("%d"),dategap);
	str = _T("日期相差：")+strd+_T("天");
	AfxMessageBox(str);
	UpdateData(0);
}


BOOL CDateCaculator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect re;   
	GetWindowRect(&re);
	SetWindowPos(NULL,500,200,re.Width(),re.Height(),NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
