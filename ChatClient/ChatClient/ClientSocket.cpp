// ClientSocket.cpp : ʵ���ļ�
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

// ��дOnReceive����
void CClientSocket::OnReceive(int nErrorCode)
{
	//���Ƚ���headͷ
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
		AfxMessageBox(_T("�ڴ治�㣡"));
		return;
	}
	if(head.SendLen!=Receive(pBuff, head.SendLen))
	{
		AfxMessageBox(_T("�յ���������"));
		delete pBuff;
		return;
	}
	CString strText(pBuff);
	switch(head.type)
	{
	case MSG_UPDATE: //���º����б�
		{
			CString strText(pBuff);
			((CChatClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateUserList(strText);
		}
		break;
	case MSG_SEND:  //��ʾ���յ�����Ϣ
		{ 
			CString str(pBuff);
			HWND hWnd=::FindWindow(NULL,_T("�� ")+sendmsg+_T(" ����")); //�õ��Ի���ľ��
			if(!FindWindow(NULL,_T("�� ")+sendmsg+_T(" ����")))  //��һ���������˶���ͻ��˵Ļ���Ⱥ�Ŀ��ܻ�ʧЧ
			{
				sendmsg = (CString)head.from;
				AfxMessageBox(sendmsg+ _T("��Ϣ��"));
				SaveMsg(sendmsg,pBuff); //�û�û�п������촰�ڣ�Ҳ����������Ϣ
				return;
			}
			CChatWindowDlg* pWnd;     
			pWnd = ((CChatWindowDlg*)CWnd::FromHandle(hWnd));
			SaveMsg(sendmsg,pBuff); //������Ϣ
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
	//����Э��ͷ
	HEADER head;
	head.type = MSG_SEND;
	head.SendLen = nlen;
	strcpy(head.to,to);
	strcpy(head.from,from);
	memset(head.beizhu,0,20);

	sendmsg = to;    //��"to"����

	int i =Send(&head, sizeof(HEADER));
	if(i==SOCKET_ERROR)   
	{
		AfxMessageBox(_T("���ʹ���"));
		return FALSE;
	};
	if(Send(lpBuff, nlen)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ʹ���"));
		return FALSE;
	};
	 
	return  TRUE;
}
//�û���½
BOOL CClientSocket::Logoin(LPSTR lpBuff, int nlen,char from[20],char beizhu[20])
{
	HEADER m_head;
	m_head.type = MSG_LOGOIN;  //ͷ������
	m_head.SendLen = nlen; //����
	memset(m_head.to,0,20);
	memset(m_head.from,0,20);
	strcpy(m_head.from,from);
	memset(m_head.beizhu,0,20);
	strcpy(m_head.beizhu,beizhu);
	int hSend= 0;
	if((hSend = Send((char*)&m_head, sizeof(m_head)))==SOCKET_ERROR)  //��ͷ�����͹�ȥ
		return false;
	if((hSend = Send(lpBuff, nlen))==SOCKET_ERROR)  //ͷ���ڴ�ռ䣬�ͳ��ȷ��͹�ȥ
		return false;
	//�ӷ�����������֤�ͺ�"yes"�ɹ�������ʧ��
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
	r_head.type = MSG_REGIST;  //ͷ������
	r_head.SendLen = nlen; //����
	memset(r_head.to,0,20);
	memset(r_head.from,0,20);
	strcpy(r_head.from,from);
	memset(r_head.beizhu,0,20);
	strcpy(r_head.beizhu,beizhu);
	Send(&r_head, sizeof(r_head));  //��ͷ�����͹�ȥ
	Send(lpBuff, nlen);

	//�ӷ�����������֤�ͺ�"yes"�ɹ�������ʧ��
	HEADER r_head2;
	int nlen2 = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen2];
	memset(pHead,0, sizeof(char)*nlen2);
	Receive(pHead,nlen2); 
	memset(r_head2.beizhu,0,sizeof(r_head2.beizhu));
	strcpy(r_head2.beizhu,((LPHEADER)pHead)->beizhu);//�Ƿ�ɹ�
	CString bz(r_head2.beizhu);
	if(bz == "yes")
		return TRUE;
	else
		return FALSE;
}
BOOL CClientSocket::SetMsg(LPSTR lpBuff, int nlen,char to[20],char from[20],char beizhu[20])
{
	HEADER s_head;
	s_head.type = MSG_MUPDATE;  //ͷ������
	s_head.SendLen = nlen; //����
	memset(s_head.to,0,20);
	strcpy(s_head.to,to); //ԭ����
	memset(s_head.from,0,20);
	strcpy(s_head.from,from); //�û���
	memset(s_head.beizhu,0,20);
	strcpy(s_head.beizhu,beizhu); //�޸�����
	Send(&s_head, sizeof(s_head));  //��ͷ�����͹�ȥ
	Send(lpBuff, nlen);
	//�ӷ�����������֤�ͺ�"yes"�ɹ�������ʧ��
	HEADER s_head2;
	int nlen2 = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen2];
	memset(pHead,0, sizeof(char)*nlen2);
	Receive(pHead,nlen2); 
	memset(s_head2.beizhu,0,sizeof(s_head2.beizhu));
	strcpy(s_head2.beizhu,((LPHEADER)pHead)->beizhu);//�Ƿ�ɹ�
	CString bz(s_head2.beizhu);
	if(bz == "yes")
		return TRUE;
	else
		return FALSE;
	return TRUE;
}