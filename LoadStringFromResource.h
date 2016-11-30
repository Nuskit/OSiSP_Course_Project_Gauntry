#pragma once
#include "stdafx.h"

#define LOAD_STRING_BUF_SIZE 100

//not thread safe
class LoadStringFromResourceW
{
public:
	LoadStringFromResourceW(unsigned int idResource);
	operator LPCTSTR() const;
private:
	TCHAR buffer[LOAD_STRING_BUF_SIZE];
};

class LoadStringFromResourceA
{
public:
	LoadStringFromResourceA(unsigned int idResource);
	operator LPCSTR() const;
private:
	CHAR buffer[LOAD_STRING_BUF_SIZE];
};
