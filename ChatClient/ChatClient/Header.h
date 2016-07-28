#pragma once
////////////自定义协议///////////////////

const int MSG_LOGOIN = 0x01; //登录    1
const int MSG_SEND = 0x11;   //发送消息   17
const int MSG_REGIST = 0x03;  //注册   3
const int MSG_CLOSE = 0x02;  //退出   2
const int MSG_UPDATE = 0x21; //更新信息   33
const int MSG_MUPDATE = 0x19; //用户信息更新 25
const int MSG_DELUSER = 0x23; //用户被删除 35

#pragma pack(push,1)   
typedef struct tagHeader{
	int type ;//协议类型
	int SendLen; //将要发送内容的长度
	char to[20];//接受者
	char from[20];//发送者用户名
	char beizhu[20];//存放密码等
}HEADER ,*LPHEADER;
#pragma pack(pop)
