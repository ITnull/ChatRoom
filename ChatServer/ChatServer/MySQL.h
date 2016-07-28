#pragma once
#include"User.h"
#include<mysql.h>
#include<string>
#include<vector>
using namespace std;
extern MYSQL mydata;
extern vector<User>userlist;
extern vector<User>::iterator iter;
void Init();
void LinkDataBase();
void BaseToMem(vector<User>&userlist);
void UserRegister(CString &username,CString &password);
void UserMsgUpdate(CString &username,CString &password);
void DeleteUser(CString &username);

