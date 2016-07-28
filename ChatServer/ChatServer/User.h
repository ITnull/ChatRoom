#pragma once
class User
{
public:
	User(void);
	User(CString user,CString pass);
	~User(void);
	CString username;
	CString password;
};

