#pragma once
#include "afxcoll.h"
#include "ClientSocket.h"
// CServerSocket ����Ŀ��

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	CPtrList m_List_Sockets;//������������������пͻ������ӳɹ����Socket
};


