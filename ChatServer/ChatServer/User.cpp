#include "StdAfx.h"
#include "User.h"

User::User(void)
{
}
User::User(CString user,CString pass)
{
	username=user;
	password=pass;
}

User::~User(void)
{
}
