
/////////////////////////////////////////////////////////////
////����Э��ͷ ��Ϊֱ��Ҫ������������в�ȷ�����ĵ�����
///Ϊ�˱����˷ѿռ�ѡ��������ִ��䣬�ʶ���һ��ͷ
/////////////////////////////////////////////////////////////
#pragma once
////////////�Զ���Э��///////////////////

const int MSG_LOGOIN = 0x01; //��¼1
const int MSG_SEND = 0x11;   //������Ϣ17
const int MSG_REGIST = 0x03;  //ע��   3
const int MSG_CLOSE = 0x02;  //�˳� 2
const int MSG_UPDATE = 0x21; //����Ϣ  33
const int MSG_MUPDATE = 0x19; //�û���Ϣ���� 25
const int MSG_DELUSER = 0x23; //�û���ɾ�� 35

#pragma pack(push,1)
typedef struct tagHeader{
	int type ;//Э������
	int SendLen; //��Ҫ�������ݵĳ���
	char to[20];
	char from[20];
	char beizhu[20];//�������½�Ƿ�ɹ�
}HEADER ,*LPHEADER;
#pragma pack(pop)

