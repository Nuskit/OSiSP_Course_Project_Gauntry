#pragma once
#include "stdafx.h"

class UILoopState;
class WindowInformation
{
public:
	WindowInformation() :uiState_(nullptr) {};
	virtual const DWORD getWidth() = 0;
	virtual const DWORD getHeight() = 0;
	virtual HWND getHWND() = 0;
	virtual void changeState(UILoopState* uiState) = 0;
	virtual ~WindowInformation() {};
protected:
	UILoopState* uiState_;
};