
/////////////////////////////////////////////////////////////
////定义协议头 因为直接要传输的类容中有不确定长的的类容
///为了避免浪费空间选择分两部分传输，故定义一个头
/////////////////////////////////////////////////////////////
#pragma once
////////////自定义协议///////////////////

const int MSG_LOGOIN = 0x01; //登录1
const int MSG_SEND = 0x11;   //发送消息17
const int MSG_REGIST = 0x03;  //注册   3
const int MSG_CLOSE = 0x02;  //退出 2
const int MSG_UPDATE = 0x21; //更信息  33
const int MSG_MUPDATE = 0x19; //用户信息更新 25
const int MSG_DELUSER = 0x23; //用户被删除 35

#pragma pack(push,1)
typedef struct tagHeader{
	int type ;//协议类型
	int SendLen; //将要发送内容的长度
	char to[20];
	char from[20];
	char beizhu[20];//密码与登陆是否成功
}HEADER ,*LPHEADER;
#pragma pack(pop)

