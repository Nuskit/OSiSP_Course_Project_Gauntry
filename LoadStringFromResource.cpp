#include "stdafx.h"
#include "LoadStringFromResource.h"

LoadStringFromResource::LoadStringFromResource(unsigned int idResource)
{
	static HINSTANCE hInstance = GetModuleHandle(NULL);
	LoadString(hInstance, idResource, buffer, LOAD_STRING_BUF_SIZE);
}

LoadStringFromResource::operator LPCTSTR() const
{
	return buffer;
}
