
// ChatServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ServerSocket.h"

// CChatServerApp:
// �йش����ʵ�֣������ ChatServer.cpp
//

class CChatServerApp : public CWinApp
{
public:
	CChatServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	CServerSocket* GetServerSocket() const;
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
private:
	CServerSocket* m_Socket;
};

extern CChatServerApp theApp;