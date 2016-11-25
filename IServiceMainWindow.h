#pragma once

#include "stdafx.h"

class IServiceMainWindow
{
public:
	virtual HWND getHWND() = 0;
	virtual void setHWND(HWND hwnd) = 0;
};
