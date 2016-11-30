#include "stdafx.h"
#include "LoadStringFromResource.h"

LoadStringFromResourceW::LoadStringFromResourceW(unsigned int idResource)
{
	static HINSTANCE hInstance = GetModuleHandle(NULL);
	LoadStringW(hInstance, idResource, buffer, LOAD_STRING_BUF_SIZE);
}

LoadStringFromResourceW::operator LPCTSTR() const
{
	return buffer;
}

LoadStringFromResourceA::LoadStringFromResourceA(unsigned int idResource)
{
	static HINSTANCE hInstance = GetModuleHandle(NULL);
	LoadStringA(hInstance, idResource, buffer, LOAD_STRING_BUF_SIZE);
}

LoadStringFromResourceA::operator LPCSTR() const
{
	return buffer;
}
