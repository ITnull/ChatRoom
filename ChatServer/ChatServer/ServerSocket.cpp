// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//接受到一个连接请求
	CClientSocket* theClientSock(0);
	//初始化在初始化里把m_listSockets赋值到m_pList里
	theClientSock = new CClientSocket(&m_List_Sockets);
	if(!theClientSock)
	{
		AfxMessageBox(_T("内存不足,客户连接服务器失败！"));
		return;
	}
	Accept(*theClientSock); //接受
	//加入list中便于管理
	m_List_Sockets.AddTail(theClientSock);
	CSocket::OnAccept(nErrorCode);
}

