
// ChatServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "MySQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatServerApp

BEGIN_MESSAGE_MAP(CChatServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChatServerApp ����

CChatServerApp::CChatServerApp()
	: m_Socket(NULL)
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CChatServerApp ����

CChatServerApp theApp;


// CChatServerApp ��ʼ��

BOOL CChatServerApp::InitInstance()
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
	SetRegistryKey(_T("Chat"));
	WSAData wsData;
	if(!AfxSocketInit(&wsData))
	{
		AfxMessageBox(_T("Socket ���ʼ������"));
		return false;
	}

	//������������Socket������TCP
	m_Socket = new CServerSocket();
	if(!m_Socket)
	{
		AfxMessageBox(_T("��̬�����������׽��ֳ���"));
		return false;
	}
	if(!m_Socket->Create(8989))
	{
		AfxMessageBox(_T("�����׽��ִ���"));
		m_Socket->Close();
		return false;
	}

//	if(!m_Socket->Bind())

	if(!m_Socket->Listen())
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
		m_Socket->Close();
		return false;
	}

	Init();
	LinkDataBase();
	BaseToMem(userlist);

	CChatServerDlg dlg;
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



int CChatServerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_Socket)
	{
		delete m_Socket;
		m_Socket = NULL;
	}
	return CWinApp::ExitInstance();
}

CServerSocket* CChatServerApp::GetServerSocket() const
{
	ASSERT(m_Socket);
	return m_Socket;
}