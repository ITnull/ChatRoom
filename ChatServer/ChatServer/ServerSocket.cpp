// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	//���ܵ�һ����������
	CClientSocket* theClientSock(0);
	//��ʼ���ڳ�ʼ�����m_listSockets��ֵ��m_pList��
	theClientSock = new CClientSocket(&m_List_Sockets);
	if(!theClientSock)
	{
		AfxMessageBox(_T("�ڴ治��,�ͻ����ӷ�����ʧ�ܣ�"));
		return;
	}
	Accept(*theClientSock); //����
	//����list�б��ڹ���
	m_List_Sockets.AddTail(theClientSock);
	CSocket::OnAccept(nErrorCode);
}

