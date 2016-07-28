#pragma once

// CClientSocket 命令目标
#include "stdafx.h"
class CClientSocket : public CSocket
{
public:
	CClientSocket(CPtrList* List);
	virtual ~CClientSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	CPtrList* m_List;//保存服务器Socket中List的东西
	CString m_strName;//连接名称
public:
	void Logoin(char* buff,int nlen,char from[20],char beizhu[20]);  //处理登录消息
	void Register(char* buff,int nlen,char from[20],char beizhu[20]);
	void SetMsg(char* buff,int nlen,char to[20],char from[20],char beizhu[20]);
	void MSGTranslate(char* buff,int nlen,char to[20],char from[20],char beizhu[20]); //转发消息
	void UpdateUserOline(CString strUserInfo,char from[20]);//更新服务器端的在线用户
	CString UpdateServerOnline();//服务器端更新
private:
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);//多字节的转换  
};


