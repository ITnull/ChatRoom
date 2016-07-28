#pragma once

// CClientSocket 命令目标

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
public:
	virtual void OnReceive(int nErrorCode);//客户端接收消息  
	BOOL SendMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20]);//客户端发送消息  
	BOOL Logoin(LPSTR lpBuff, int nlen,char from[20],char beizhu[20]);//客户端登录  
	BOOL Register(LPSTR lpBuff, int nlen,char from[20],char beizhu[20]);//客户端注册
	BOOL SetMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20]);//更新信息
	CString m_UserName;
	CString m_UserPassword;
	void SaveMsg(CString fn, char* str);
};


