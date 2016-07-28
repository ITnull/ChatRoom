// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ClientSocket.h"
#include "Header.h"
#include "ChatServerDlg.h"
#include "MySQL.h"



// CClientSocket

CClientSocket::CClientSocket(CPtrList* List)
	: m_List(List)
	, m_strName(_T(""))
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	this->m_strName;
	m_List->RemoveAt(m_List->Find(this));
	CString str1 = this->UpdateServerOnline();//更改服务器在线名单
	this->UpdateUserOline(str1,"0");//通知客户端刷新在线名单
	this->Close();
	//销毁该套接字
	delete this;
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	HEADER head;    //定义客户端发送的过来的一样的结构体
	int nlen = sizeof HEADER;  //计算结构体大小
	char *pHead = NULL;  //用于接受的结构体
	pHead = new char[nlen]; //申请和结构体一样大小的内存空间
	if(!pHead)
	{
		TRACE0("CClientSocket::OnReceive 内存不足！");
		return;
	}
	memset(pHead,0, sizeof(char)*nlen );  //初始化
	Receive(pHead,nlen);   //收到内容，并赋值到pHead中，指定接受的空间大小
	//以下是将接收大结构体进行强制转换成我们的结构体，
	head.type = ((LPHEADER)pHead)->type;
	head.SendLen = ((LPHEADER)pHead)->SendLen;
	//head.to_user 是char[]类型，如果不进行初始化，可能会有乱码出现
	memset(head.to,0,sizeof(head.to)); 
	//讲接受的数据转换过后并赋值到head.to_user，以下同
	strcpy(head.to,((LPHEADER)pHead)->to);
	memset(head.from,0,sizeof(head.from));
	strcpy(head.from,((LPHEADER)pHead)->from);
	memset(head.beizhu,0,sizeof(head.beizhu));
	strcpy(head.beizhu,((LPHEADER)pHead)->beizhu);
	delete pHead; //使用完毕，指针变量的清除
	pHead = NULL;

	//接受正式数据内容
	char* tHead = NULL;
	tHead = new char[head.SendLen+1];
	memset(tHead,0,sizeof(char)*(head.SendLen+1));
	if(!tHead)
	{
		TRACE0("CClientSocket::OnRecive 内存不足！");
		return;
	}
	if( Receive(tHead, head.SendLen)!=head.SendLen)
	{
		AfxMessageBox(_T("接收数据有误！"));
		delete pHead;
		return;
	}
	//根据消息类型，处理数据
	switch(head.type)
	{
	case MSG_LOGOIN: //登陆消息
		Logoin(tHead, head.SendLen,head.from,head.beizhu);
		break;
	case MSG_SEND: //发送消息
		MSGTranslate(tHead, head.SendLen,head.to,head.from,head.beizhu);
		break;
	case MSG_REGIST:
		Register(pHead, head.SendLen,head.from,head.beizhu);
		break;
	case MSG_MUPDATE:
		SetMsg(pHead, head.SendLen,head.to,head.from,head.beizhu);
		break;
	default : break;
	}
	delete pHead; 
	CSocket::OnReceive(nErrorCode);
}
void CClientSocket::Logoin(char* buff,int nlen,char from[20],char beizhu[20])
{
	HEADER head;
	head.type = MSG_LOGOIN;
	head.SendLen = nlen;
	strcpy(head.from,from);
	strcpy(head.beizhu,beizhu);
	//发送给客户端登陆成功是否的消息头
	HEADER head2;
	head2.type = MSG_LOGOIN;
	head2.SendLen = nlen;
	memset(head2.to,0,20);
	memset(head2.from,0,20);
	memset(head2.beizhu,0,20);
	strcpy(head2.to,head.from);
	//验证登陆是否成功
	for(iter=userlist.begin();iter!=userlist.end();iter++)
	{
		if((CString)head.from == (CString)iter->username&&(CString)head.beizhu ==(CString)iter->password) //登录成功
		{ 
			strcpy(head2.beizhu,"yes");//成功
			Send((char*)&head2, sizeof(head2));
			break;
		}
	}
	if(iter == userlist.end()) //登陆失败
	{
		memset(head2.beizhu,0,20);
		strcpy(head2.beizhu,"no");//失败
		Send((char*)&head2, sizeof(head2));
		return;
	}

	CString strTemp(buff);
	m_strName = strTemp;
	//更新服务列表，这个是更新服务器端的在线名单 
	//str1 返回的是所有用户字符串
	CString str1 = this->UpdateServerOnline();
	//更新在线所有客服端，from_user 是为了不更新自己的在线列表，
	this->UpdateUserOline(str1,from);
}
void CClientSocket::MSGTranslate(char* buff,int nlen,char to[20],char from[20],char beizhu[20])
{
	 HEADER head;
	 head.type = MSG_SEND;
	 head.SendLen = nlen;
	 strcpy(head.to,to);
	 strcpy(head.from,from);
	 memset(head.beizhu,0,20);

	 POSITION ps = m_List->GetHeadPosition();  //取得，所有用户的队列
	 CString str(buff);
	 int i =  strcmp(head.to,"群聊");
	 while(ps!=NULL)
	 {
		CClientSocket* pTemp = (CClientSocket*)m_List->GetNext(ps);
		//实现群聊和一对一关键就在于此
		if(pTemp->m_strName==head.to || pTemp->m_strName==head.from || i==0 )
		{
			pTemp->Send(&head,sizeof(HEADER));  //先发送头部
			pTemp->Send(buff, nlen);			//再发送内容
		}
	 }
}
void CClientSocket::Register(char* buff,int nlen,char from[20],char beizhu[20])
{
	HEADER rhead;
	rhead.type = MSG_REGIST;
	rhead.SendLen = nlen;
	strcpy(rhead.from,from);
	strcpy(rhead.beizhu,beizhu);
	//发送给客户端注册成功是否的消息头
	HEADER head3;
	head3.type = MSG_REGIST;
	head3.SendLen = nlen;
	memset(head3.to,0,20);
	memset(head3.from,0,20);
	memset(head3.beizhu,0,20);
	strcpy(head3.to,rhead.from);
	//验证登陆是否成功
	for(iter=userlist.begin();iter!=userlist.end();iter++)
	{
		if((CString)rhead.from == (CString)iter->username) //用户已存在
		{ 
			strcpy(head3.beizhu,"no");//失败
			Send((char*)&head3, sizeof(head3));
			return;
		}
	}
	if(iter == userlist.end()) //没有相同的用户，可以注册
	{
		UserRegister(CString(from),CString(beizhu));
		User user;
		user.username = from;
		user.password = beizhu;
		userlist.push_back(user); //将注册的用户添加到容器中
		memset(head3.beizhu,0,20);
		strcpy(head3.beizhu,"yes");//成功
		Send((char*)&head3, sizeof(head3));
	}
}

void CClientSocket::SetMsg(char* buff,int nlen,char to[20],char from[20],char beizhu[20])
{
	HEADER rhead;
	rhead.type = MSG_MUPDATE;
	rhead.SendLen = nlen;
	strcpy(rhead.to,to);  //原密码
	strcpy(rhead.from,from); //用户名
	strcpy(rhead.beizhu,beizhu); //修改密码
	//发送给客户端密码修改是否成功的消息头
	HEADER rhead2;
	rhead2.type = MSG_MUPDATE;
	rhead2.SendLen = nlen;
	memset(rhead2.to,0,20);
	memset(rhead2.from,0,20);
	memset(rhead2.beizhu,0,20);
	strcpy(rhead2.to,rhead.from); //服务器发送给的用户名
	//验证原密码是否正确
	for(iter=userlist.begin();iter!=userlist.end();iter++)
	{
		if((CString)rhead.from == (CString)iter->username&&(CString)rhead.to == (CString)iter->password) //原密码正确
		{ 
			UserMsgUpdate(CString(from),CString(beizhu));
			iter->password = rhead.beizhu;//及时更新缓存容器中的用户密码
			strcpy(rhead2.beizhu,"yes");//成功
			Send((char*)&rhead2, sizeof(rhead2));
			break;
		}
		if((CString)rhead.from == (CString)iter->username&&(CString)rhead.to != (CString)iter->password) //原密码错误
		{ 
			strcpy(rhead2.beizhu,"no");//失败
			Send((char*)&rhead2, sizeof(rhead2));
			return;
		}
	}
}

BOOL CClientSocket::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
 {
	 int n = 0;
	 n = WideCharToMultiByte(CP_OEMCP,0, srcBuff, -1, destBuff,0, 0, FALSE );
	 int aa = strlen(destBuff);
	 if(n<strlen(destBuff))
		return FALSE;

	 WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);

	 return TRUE;
 }
void CClientSocket::UpdateUserOline(CString strUserInfo,char from[20])
 {
	 HEADER head;
	 head.type = MSG_UPDATE;
	 head.SendLen = strUserInfo.GetLength()*2;
	 memset(head.from, 0, sizeof(head.from));
	 memset(head.beizhu,0,sizeof(head.beizhu));
	 memset(head.to,0,sizeof(head.to));
	 strcpy(head.from,from);
	 char *pSend = new char[head.SendLen];
	 memset(pSend, 0, head.SendLen);

	 if( !WChar2MByte(strUserInfo.GetBuffer(0), pSend, head.SendLen))
	 {
		 AfxMessageBox(_T("用户全部退出！"));
		 delete pSend;
		 return;
	 }
	POSITION pss = m_List->GetHeadPosition();  //循环对客户端发送消息
	while(pss!=NULL)
	{
		 CClientSocket* pTemp = (CClientSocket*)m_List->GetNext(pss);
		//发送协议头
		pTemp->Send((char*)&head, sizeof(head));
		pTemp->Send(pSend,head.SendLen ); 
	}	
	delete pSend;
 }
CString CClientSocket::UpdateServerOnline()
 {
	 CString strUserInfo = _T("");
	 POSITION ps = m_List->GetHeadPosition();  //返回的是链表头元素的位置
	 while(ps!=NULL)
	 {
		 CClientSocket* pTemp = (CClientSocket*)m_List->GetNext(ps); //指向下一个元素
		 strUserInfo += pTemp->m_strName + _T("#");  //每一次用#结束
	 }
	((CChatServerDlg*)theApp.GetMainWnd())->UpdateUserInfo(strUserInfo);   //更新服务器显示

	return strUserInfo;
 }
