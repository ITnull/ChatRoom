
// ChatClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
//#include "ChatWindowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatClientApp

BEGIN_MESSAGE_MAP(CChatClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChatClientApp ����

CChatClientApp::CChatClientApp()
	: m_Socket(NULL)
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


////////// Ψһ��һ�� CChatClientApp ����

CChatClientApp theApp;


// CChatClientApp ��ʼ��

BOOL CChatClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("ChatClient"));

	//��ʼ��Socket
	if(!AfxSocketInit())
	{
		AfxMessageBox(_T("��ʼ��Socket��ʧ�ܣ�"));
		return false;
	}

	m_Socket = new CClientSocket();
	if(!m_Socket)
	{
		AfxMessageBox(_T("�ڴ治�㣡"));
		return false;
	}

	if(!m_Socket->Create())
	{
		AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
		return false;
	}
	CLoginDlg* m_LoginDlg;
	m_LoginDlg = new CLoginDlg();
	CString m_User;
	if(m_LoginDlg->DoModal()==IDOK)
	{
		//����¼
		delete m_LoginDlg;
		m_Socket->Close();
		return false;
	}
	else
	{
		m_User = m_LoginDlg->m_User;
		delete m_LoginDlg;
	}
	CChatClientDlg dlg;
	dlg.m_caption = m_User;     //���ñ�����
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CChatClientApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_Socket)
	{
		delete m_Socket;
		m_Socket = NULL;
	}
	return CWinApp::ExitInstance();
}
CClientSocket* CChatClientApp::GetMainSocket() const
{
	return m_Socket;
}