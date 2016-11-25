#pragma once
#include "stdafx.h"

class WindowInformation
{
public:
	virtual const DWORD getWidth() = 0;
	virtual const DWORD getHeight() = 0;
	virtual HWND getHWND() = 0;
	virtual ~WindowInformation() {};
};