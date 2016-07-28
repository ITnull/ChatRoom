#pragma once
#include "afxcoll.h"
#include "ClientSocket.h"
// CServerSocket 命令目标

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	CPtrList m_List_Sockets;//用来保存服务器与所有客户端连接成功后的Socket
};


