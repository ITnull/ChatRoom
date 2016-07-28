// ClientSocket.cpp : ʵ���ļ�
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


// CClientSocket ��Ա����


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	this->m_strName;
	m_List->RemoveAt(m_List->Find(this));
	CString str1 = this->UpdateServerOnline();//���ķ�������������
	this->UpdateUserOline(str1,"0");//֪ͨ�ͻ���ˢ����������
	this->Close();
	//���ٸ��׽���
	delete this;
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	HEADER head;    //����ͻ��˷��͵Ĺ�����һ���Ľṹ��
	int nlen = sizeof HEADER;  //����ṹ���С
	char *pHead = NULL;  //���ڽ��ܵĽṹ��
	pHead = new char[nlen]; //����ͽṹ��һ����С���ڴ�ռ�
	if(!pHead)
	{
		TRACE0("CClientSocket::OnReceive �ڴ治�㣡");
		return;
	}
	memset(pHead,0, sizeof(char)*nlen );  //��ʼ��
	Receive(pHead,nlen);   //�յ����ݣ�����ֵ��pHead�У�ָ�����ܵĿռ��С
	//�����ǽ����մ�ṹ�����ǿ��ת�������ǵĽṹ�壬
	head.type = ((LPHEADER)pHead)->type;
	head.SendLen = ((LPHEADER)pHead)->SendLen;
	//head.to_user ��char[]���ͣ���������г�ʼ�������ܻ����������
	memset(head.to,0,sizeof(head.to)); 
	//�����ܵ�����ת�����󲢸�ֵ��head.to_user������ͬ
	strcpy(head.to,((LPHEADER)pHead)->to);
	memset(head.from,0,sizeof(head.from));
	strcpy(head.from,((LPHEADER)pHead)->from);
	memset(head.beizhu,0,sizeof(head.beizhu));
	strcpy(head.beizhu,((LPHEADER)pHead)->beizhu);
	delete pHead; //ʹ����ϣ�ָ����������
	pHead = NULL;

	//������ʽ��������
	char* tHead = NULL;
	tHead = new char[head.SendLen+1];
	memset(tHead,0,sizeof(char)*(head.SendLen+1));
	if(!tHead)
	{
		TRACE0("CClientSocket::OnRecive �ڴ治�㣡");
		return;
	}
	if( Receive(tHead, head.SendLen)!=head.SendLen)
	{
		AfxMessageBox(_T("������������"));
		delete pHead;
		return;
	}
	//������Ϣ���ͣ���������
	switch(head.type)
	{
	case MSG_LOGOIN: //��½��Ϣ
		Logoin(tHead, head.SendLen,head.from,head.beizhu);
		break;
	case MSG_SEND: //������Ϣ
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
	//���͸��ͻ��˵�½�ɹ��Ƿ����Ϣͷ
	HEADER head2;
	head2.type = MSG_LOGOIN;
	head2.SendLen = nlen;
	memset(head2.to,0,20);
	memset(head2.from,0,20);
	memset(head2.beizhu,0,20);
	strcpy(head2.to,head.from);
	//��֤��½�Ƿ�ɹ�
	for(iter=userlist.begin();iter!=userlist.end();iter++)
	{
		if((CString)head.from == (CString)iter->username&&(CString)head.beizhu ==(CString)iter->password) //��¼�ɹ�
		{ 
			strcpy(head2.beizhu,"yes");//�ɹ�
			Send((char*)&head2, sizeof(head2));
			break;
		}
	}
	if(iter == userlist.end()) //��½ʧ��
	{
		memset(head2.beizhu,0,20);
		strcpy(head2.beizhu,"no");//ʧ��
		Send((char*)&head2, sizeof(head2));
		return;
	}

	CString strTemp(buff);
	m_strName = strTemp;
	//���·����б�����Ǹ��·������˵��������� 
	//str1 ���ص��������û��ַ���
	CString str1 = this->UpdateServerOnline();
	//�����������пͷ��ˣ�from_user ��Ϊ�˲������Լ��������б�
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

	 POSITION ps = m_List->GetHeadPosition();  //ȡ�ã������û��Ķ���
	 CString str(buff);
	 int i =  strcmp(head.to,"Ⱥ��");
	 while(ps!=NULL)
	 {
		CClientSocket* pTemp = (CClientSocket*)m_List->GetNext(ps);
		//ʵ��Ⱥ�ĺ�һ��һ�ؼ������ڴ�
		if(pTemp->m_strName==head.to || pTemp->m_strName==head.from || i==0 )
		{
			pTemp->Send(&head,sizeof(HEADER));  //�ȷ���ͷ��
			pTemp->Send(buff, nlen);			//�ٷ�������
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
	//���͸��ͻ���ע��ɹ��Ƿ����Ϣͷ
	HEADER head3;
	head3.type = MSG_REGIST;
	head3.SendLen = nlen;
	memset(head3.to,0,20);
	memset(head3.from,0,20);
	memset(head3.beizhu,0,20);
	strcpy(head3.to,rhead.from);
	//��֤��½�Ƿ�ɹ�
	for(iter=userlist.begin();iter!=userlist.end();iter++)
	{
		if((CString)rhead.from == (CString)iter->username) //�û��Ѵ���
		{ 
			strcpy(head3.beizhu,"no");//ʧ��
			Send((char*)&head3, sizeof(head3));
			return;
		}
	}
	if(iter == userlist.end()) //û����ͬ���û�������ע��
	{
		UserRegister(CString(from),CString(beizhu));
		User user;
		user.username = from;
		user.password = beizhu;
		userlist.push_back(user); //��ע����û���ӵ�������
		memset(head3.beizhu,0,20);
		strcpy(head3.beizhu,"yes");//�ɹ�
		Send((char*)&head3, sizeof(head3));
	}
}

void CClientSocket::SetMsg(char* buff,int nlen,char to[20],char from[20],char beizhu[20])
{
	HEADER rhead;
	rhead.type = MSG_MUPDATE;
	rhead.SendLen = nlen;
	strcpy(rhead.to,to);  //ԭ����
	strcpy(rhead.from,from); //�û���
	strcpy(rhead.beizhu,beizhu); //�޸�����
	//���͸��ͻ��������޸��Ƿ�ɹ�����Ϣͷ
	HEADER rhead2;
	rhead2.type = MSG_MUPDATE;
	rhead2.SendLen = nlen;
	memset(rhead2.to,0,20);
	memset(rhead2.from,0,20);
	memset(rhead2.beizhu,0,20);
	strcpy(rhead2.to,rhead.from); //���������͸����û���
	//��֤ԭ�����Ƿ���ȷ
	for(iter=userlist.begin();iter!=userlist.end();iter++)
	{
		if((CString)rhead.from == (CString)iter->username&&(CString)rhead.to == (CString)iter->password) //ԭ������ȷ
		{ 
			UserMsgUpdate(CString(from),CString(beizhu));
			iter->password = rhead.beizhu;//��ʱ���»��������е��û�����
			strcpy(rhead2.beizhu,"yes");//�ɹ�
			Send((char*)&rhead2, sizeof(rhead2));
			break;
		}
		if((CString)rhead.from == (CString)iter->username&&(CString)rhead.to != (CString)iter->password) //ԭ�������
		{ 
			strcpy(rhead2.beizhu,"no");//ʧ��
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
		 AfxMessageBox(_T("�û�ȫ���˳���"));
		 delete pSend;
		 return;
	 }
	POSITION pss = m_List->GetHeadPosition();  //ѭ���Կͻ��˷�����Ϣ
	while(pss!=NULL)
	{
		 CClientSocket* pTemp = (CClientSocket*)m_List->GetNext(pss);
		//����Э��ͷ
		pTemp->Send((char*)&head, sizeof(head));
		pTemp->Send(pSend,head.SendLen ); 
	}	
	delete pSend;
 }
CString CClientSocket::UpdateServerOnline()
 {
	 CString strUserInfo = _T("");
	 POSITION ps = m_List->GetHeadPosition();  //���ص�������ͷԪ�ص�λ��
	 while(ps!=NULL)
	 {
		 CClientSocket* pTemp = (CClientSocket*)m_List->GetNext(ps); //ָ����һ��Ԫ��
		 strUserInfo += pTemp->m_strName + _T("#");  //ÿһ����#����
	 }
	((CChatServerDlg*)theApp.GetMainWnd())->UpdateUserInfo(strUserInfo);   //���·�������ʾ

	return strUserInfo;
 }
