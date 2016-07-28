// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ClientSocket.h"
#include "Header.h"
#include "ChatClientDlg.h"
#include "ChatWindowDlg.h"

#include<fstream>

using namespace std;
// CClientSocket
CString sendmsg = _T("");

CClientSocket::CClientSocket()
	:m_UserName(_T(""))
{
}

CClientSocket::~CClientSocket()
{
}

// 重写OnReceive函数
void CClientSocket::OnReceive(int nErrorCode)
{
	//首先接受head头
	HEADER head ;
	char* pHead = NULL;
	pHead =  new char[sizeof(head)];
	memset(pHead, 0, sizeof(head));

	memset(head.beizhu, 0, sizeof(head.beizhu));
	memset(head.from, 0, sizeof(head.from));
	memset(head.to, 0, sizeof(head.to));
	memset(head.beizhu, 0, sizeof(head.beizhu));

	Receive(pHead, sizeof(head));
	head.type =((LPHEADER)pHead)->type;
	head.SendLen = ((LPHEADER)pHead)->SendLen;
	strcpy(head.from,((LPHEADER)pHead)->from);
	delete pHead;
	pHead = NULL;

	char* pBuff = NULL;
	pBuff = new char[head.SendLen+1];
	memset(pBuff,0,sizeof(char)*(head.SendLen+1));
	if(!pBuff)
	{
		AfxMessageBox(_T("内存不足！"));
		return;
	}
	if(head.SendLen!=Receive(pBuff, head.SendLen))
	{
		AfxMessageBox(_T("收到数据有误！"));
		delete pBuff;
		return;
	}
	CString strText(pBuff);
	switch(head.type)
	{
	case MSG_UPDATE: //更新好友列表
		{
			CString strText(pBuff);
			((CChatClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateUserList(strText);
		}
		break;
	case MSG_SEND:  //显示接收到的消息
		{ 
			CString str(pBuff);
			HWND hWnd=::FindWindow(NULL,_T("与 ")+sendmsg+_T(" 聊天")); //得到对话框的句柄
			if(!FindWindow(NULL,_T("与 ")+sendmsg+_T(" 聊天")))  //当一个主机开了多个客户端的话，群聊可能会失效
			{
				sendmsg = (CString)head.from;
				AfxMessageBox(sendmsg+ _T("消息！"));
				SaveMsg(sendmsg,pBuff); //用户没有开启聊天窗口，也保存聊天消息
				return;
			}
			CChatWindowDlg* pWnd;     
			pWnd = ((CChatWindowDlg*)CWnd::FromHandle(hWnd));
			SaveMsg(sendmsg,pBuff); //保存消息
			pWnd->UpdateText(str);    
		} 
		break;
	case MSG_DELUSER:
		{
			((CChatClientDlg*)(AfxGetApp()->GetMainWnd()))->OnOK();
		}
		break;
	default: break;
	}
	
	delete pBuff;
	CSocket::OnReceive(nErrorCode);
}

BOOL CClientSocket::SendMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20])
{
	//生成协议头
	HEADER head;
	head.type = MSG_SEND;
	head.SendLen = nlen;
	strcpy(head.to,to);
	strcpy(head.from,from);
	memset(head.beizhu,0,20);

	sendmsg = to;    //与"to"聊天

	int i =Send(&head, sizeof(HEADER));
	if(i==SOCKET_ERROR)   
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	};
	if(Send(lpBuff, nlen)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	};
	 
	return  TRUE;
}
//用户登陆
BOOL CClientSocket::Logoin(LPSTR lpBuff, int nlen,char from[20],char beizhu[20])
{
	HEADER m_head;
	m_head.type = MSG_LOGOIN;  //头部类型
	m_head.SendLen = nlen; //长度
	memset(m_head.to,0,20);
	memset(m_head.from,0,20);
	strcpy(m_head.from,from);
	memset(m_head.beizhu,0,20);
	strcpy(m_head.beizhu,beizhu);
	int hSend= 0;
	if((hSend = Send((char*)&m_head, sizeof(m_head)))==SOCKET_ERROR)  //将头部发送过去
		return false;
	if((hSend = Send(lpBuff, nlen))==SOCKET_ERROR)  //头部内存空间，和长度发送过去
		return false;
	//从服务器接受验证型号"yes"成功，否则失败
	HEADER head2;
	int nlen2 = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen2];
	memset(pHead,0, sizeof(char)*nlen2);
	Receive(pHead,nlen2); 
	memset(head2.beizhu,0,sizeof(head2.beizhu));
	strcpy(head2.beizhu,((LPHEADER)pHead)->beizhu);
	CString bz(head2.beizhu);
	if(bz == "yes")
		return TRUE;
	else
		return FALSE;
}
void CClientSocket::SaveMsg(CString fn,char* sm)
{
	CString filename = fn+_T(".txt");
	ifstream find(filename);
	if(!find)
	{
		ofstream file(filename,ios::out);
	}
	ofstream ofs(filename,ios::app); 
	ofs.write(sm,strlen(sm));  
	ofs.flush();  
	ofs.close(); 
}
BOOL CClientSocket::Register(LPSTR lpBuff, int nlen,char from[20],char beizhu[20])
{
	HEADER r_head;
	r_head.type = MSG_REGIST;  //头部类型
	r_head.SendLen = nlen; //长度
	memset(r_head.to,0,20);
	memset(r_head.from,0,20);
	strcpy(r_head.from,from);
	memset(r_head.beizhu,0,20);
	strcpy(r_head.beizhu,beizhu);
	Send(&r_head, sizeof(r_head));  //将头部发送过去
	Send(lpBuff, nlen);

	//从服务器接受验证型号"yes"成功，否则失败
	HEADER r_head2;
	int nlen2 = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen2];
	memset(pHead,0, sizeof(char)*nlen2);
	Receive(pHead,nlen2); 
	memset(r_head2.beizhu,0,sizeof(r_head2.beizhu));
	strcpy(r_head2.beizhu,((LPHEADER)pHead)->beizhu);//是否成功
	CString bz(r_head2.beizhu);
	if(bz == "yes")
		return TRUE;
	else
		return FALSE;
}
BOOL CClientSocket::SetMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20])
{
	HEADER s_head;
	s_head.type = MSG_MUPDATE;  //头部类型
	s_head.SendLen = nlen; //长度
	memset(s_head.to,0,20);
	strcpy(s_head.to,to); //原密码
	memset(s_head.from,0,20);
	strcpy(s_head.from,from); //用户名
	memset(s_head.beizhu,0,20);
	strcpy(s_head.beizhu,beizhu); //修改密码
	Send(&s_head, sizeof(s_head));  //将头部发送过去
	Send(lpBuff, nlen);
	//从服务器接受验证型号"yes"成功，否则失败
	HEADER s_head2;
	int nlen2 = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen2];
	memset(pHead,0, sizeof(char)*nlen2);
	Receive(pHead,nlen2); 
	memset(s_head2.beizhu,0,sizeof(s_head2.beizhu));
	strcpy(s_head2.beizhu,((LPHEADER)pHead)->beizhu);//是否成功
	CString bz(s_head2.beizhu);
	if(bz == "yes")
		return TRUE;
	else
		return FALSE;
	return TRUE;
}