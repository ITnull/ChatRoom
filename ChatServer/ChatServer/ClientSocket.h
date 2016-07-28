#pragma once

// CClientSocket ����Ŀ��
#include "stdafx.h"
class CClientSocket : public CSocket
{
public:
	CClientSocket(CPtrList* List);
	virtual ~CClientSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	CPtrList* m_List;//���������Socket��List�Ķ���
	CString m_strName;//��������
public:
	void Logoin(char* buff,int nlen,char from[20],char beizhu[20]);  //�����¼��Ϣ
	void Register(char* buff,int nlen,char from[20],char beizhu[20]);
	void SetMsg(char* buff,int nlen,char to[20],char from[20],char beizhu[20]);
	void MSGTranslate(char* buff,int nlen,char to[20],char from[20],char beizhu[20]); //ת����Ϣ
	void UpdateUserOline(CString strUserInfo,char from[20]);//���·������˵������û�
	CString UpdateServerOnline();//�������˸���
private:
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);//���ֽڵ�ת��  
};


