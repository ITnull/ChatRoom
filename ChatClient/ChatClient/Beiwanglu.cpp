// Beiwanglu.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Beiwanglu.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
using namespace std;
static CRect b_rectL; //切割前的尺寸
static CRect b_rectS; //切割后的尺寸

// CBeiwanglu 对话框

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


// CBeiwanglu 消息处理程序


BOOL CBeiwanglu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString bwl = _T("备忘录.txt");
	ifstream find(bwl);
	if(!find)
	{
		ofstream file(bwl,ios::out);
	}
	CRect b_rectSepr;   //初始化登陆对话框的大小
	GetWindowRect(&b_rectL);
	GetDlgItem(IDC_SEPRATOR4)->GetWindowRect(&b_rectSepr);//picture控件的rect
	b_rectS.left = b_rectL.left;
	b_rectS.top = b_rectL.top;
	b_rectS.right = b_rectSepr.right;
	b_rectS.bottom = b_rectL.bottom;
	SetWindowPos(NULL,500,270,b_rectS.Width(),b_rectS.Height(),NULL);
	bwl_record();  //载入备忘录
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CBeiwanglu::OnBnClickedBSave()
{
	UpdateData();
	if(m_write == _T(""))
	{
		AfxMessageBox(_T("请输入要记录的事件！"));
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
	str = ye+_T("年")+mo+_T("月")+da+_T("日 ")+ho+_T(":")+mi+_T("\r\n")+m_write+_T("\r\n")+_T("\r\n");
	ofstream ofs("备忘录.txt",ios::app); 
	//字符转换
	char* temp = new char[str.GetLength()*2];
	memset(temp,0,str.GetLength()*2);
	WideCharToMultiByte(CP_OEMCP, 0, str.GetBuffer(0), -1, temp, str.GetLength()*2, 0, FALSE);
	int len = strlen(temp);
	ofs.write(temp,len);  //写入日期时间
	ofs.flush();  
	ofs.close(); 
	m_write = _T("");
	SetWindowPos(NULL,500,270,b_rectS.Width(),b_rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	((CEdit*)GetDlgItem(IDC_B_SHOW))->SetWindowTextW(_T(""));//在更新前，清除edit控件内的数据
	bwl_record(); //更新备忘录
	UpdateData(0);
}


void CBeiwanglu::OnBnClickedBCansel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_write = _T("");
	UpdateData(0);
}


void CBeiwanglu::OnBnClickedBAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	SetWindowPos(NULL,500,270,b_rectL.Width(),b_rectL.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
}




void CBeiwanglu::OnBnClickedBNowrite()
{
	// TODO: 在此添加控件通知处理程序代码
	SetWindowPos(NULL,500,270,b_rectS.Width(),b_rectS.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
}


void CBeiwanglu::OnBnClickedBOut()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CBeiwanglu::bwl_record()
{
	CString filename = _T("备忘录.txt");
	ifstream ins(filename);
	string strline;
	while(getline(ins, strline)){
		CString abc(strline.c_str());//从文本取数据
		CString ab = abc+'\n';   //从文本取一行数据后换行
		((CEdit*)GetDlgItem(IDC_B_SHOW))->ReplaceSel(ab); //一行一行显示数据
	}
}

void CBeiwanglu::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("真的要清空备忘录吗！"),MB_OKCANCEL);
	fstream file(_T("备忘录.txt"),ios::out);
	bwl_record();//更新备忘录
}
