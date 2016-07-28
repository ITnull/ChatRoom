
// ChatClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "LoginDlg.h"
#include "ClientSocket.h"

// CChatClientApp:
// �йش����ʵ�֣������ ChatClient.cpp
//

class CChatClientApp : public CWinApp
{
public:
	CChatClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public: 
	CClientSocket* GetMainSocket() const;
private:
	CClientSocket* m_Socket;
public:
	virtual int ExitInstance();
};

extern CChatClientApp theApp;