#pragma once
#include "stdafx.h"

#define LOAD_STRING_BUF_SIZE 100

//not thread safe
class LoadStringFromResource
{
public:
	LoadStringFromResource(unsigned int idResource);
	operator LPCWSTR() const;
private:
	TCHAR buffer[LOAD_STRING_BUF_SIZE];
};
