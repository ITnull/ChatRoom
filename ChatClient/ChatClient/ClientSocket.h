#pragma once

// CClientSocket ����Ŀ��

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
public:
	virtual void OnReceive(int nErrorCode);//�ͻ��˽�����Ϣ  
	BOOL SendMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20]);//�ͻ��˷�����Ϣ  
	BOOL Logoin(LPSTR lpBuff, int nlen,char from[20],char beizhu[20]);//�ͻ��˵�¼  
	BOOL Register(LPSTR lpBuff, int nlen,char from[20],char beizhu[20]);//�ͻ���ע��
	BOOL SetMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20]);//������Ϣ
	CString m_UserName;
	CString m_UserPassword;
	void SaveMsg(CString fn, char* str);
};


