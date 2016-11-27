#pragma once
#include "stdafx.h"
#include "UILoopState.h"
#include <stack>

class UILoopMainMenu :public UILoopState
{
public:
	virtual void enter() override;
	virtual void exit() override;
	virtual bool MsgProc(MsgProcParam & msgProc) override;
private:
	HWND createMenuButton(int idResourceButton, int indexNumber);
	std::stack<HWND> buttons;
};