#include "StdAfx.h"
#include "MySQL.h"
MYSQL mydata;
vector<User>userlist;
vector<User>::iterator iter;
void Init()
{
	//��ʼ�����ݿ�  
	mysql_library_init(0, NULL, NULL);
	//��ʼ�����ݽṹ  
	mysql_init(&mydata);
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");
}
void LinkDataBase()
{
	//�������ݿ�
	mysql_real_connect(&mydata, "localhost", "root", "360481", "chat",3306, NULL, 0);
}
void BaseToMem(vector<User>&userlist)
{
	//�����ݿ�����û���Ϣ��vector������
	User user;
	string sqlstr="SELECT * FROM user";
	MYSQL_RES *result = NULL;
	mysql_query(&mydata,sqlstr.c_str());
	result = mysql_store_result(&mydata);
	MYSQL_ROW row = NULL;
	while(row = mysql_fetch_row(result))
	{
		user.username=row[0];
		user.password=row[1];
		userlist.push_back(user);
	}
}
void UserRegister(CString &username,CString &password)
{
	//�û�ע��
	CString sqlstr=_T("insert into user(id,password) values (");
	sqlstr=sqlstr+'"';
	sqlstr=sqlstr+username;
	sqlstr=sqlstr+'"';
	sqlstr=sqlstr+',';
	sqlstr=sqlstr+'"';
	sqlstr=sqlstr+password;
	sqlstr=sqlstr+'"';
	sqlstr=sqlstr+')';
	USES_CONVERSION;
	MYSQL_RES *result = NULL;
	mysql_query(&mydata, T2A(sqlstr));
}
void UserMsgUpdate(CString &username,CString &password)
{
	//�û���������
	CString sqlstr2=_T("update user set password = ");
	sqlstr2=sqlstr2+'"';
	sqlstr2=sqlstr2+password;
	sqlstr2=sqlstr2+'"';
	sqlstr2=sqlstr2+_T("where id = ");
	sqlstr2=sqlstr2+'"';
	sqlstr2=sqlstr2+username;
	sqlstr2=sqlstr2+'"';
	USES_CONVERSION;
	MYSQL_RES *result = NULL;
	mysql_query(&mydata, T2A(sqlstr2));
}
void DeleteUser(CString &username)
{
	CString sqlstr3=_T("delete from user where id = ");
	sqlstr3=sqlstr3+'"';
	sqlstr3=sqlstr3+username;
	sqlstr3=sqlstr3+'"';
	USES_CONVERSION;
	MYSQL_RES *result = NULL;
	mysql_query(&mydata, T2A(sqlstr3));
}