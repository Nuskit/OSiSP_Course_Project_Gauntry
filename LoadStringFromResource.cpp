#include "stdafx.h"
#include "LoadStringFromResource.h"

LoadStringFromResource::LoadStringFromResource(unsigned int idResource)
{
	LoadString(, idResource, buffer, LOAD_STRING_BUF_SIZE);
}

LoadStringFromResource::operator const TCHAR*()
{
	return buffer;
}
