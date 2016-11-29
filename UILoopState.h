#pragma once
#include "stdafx.h"
#include "BaseState.h"

class UILoopInitialize;
class UILoopMainMenu;
class UILoopNewGame;
class UILoopOptions;
class UILoopState :public BaseState
{
public:
	typedef struct _MsgProcParam
	{
		HWND hWnd;
		UINT msg; 
		WPARAM wParam; 
		LPARAM lParam;
		LRESULT result;
		UILoopState* nextState;
	}MsgProcParam;
	virtual bool MsgProc(MsgProcParam& msgProc) = 0;
public:
	static UILoopInitialize uiStateInitialize;
	static UILoopMainMenu uiStateMainMenu;
	static UILoopNewGame uiStateNewGame;
	static UILoopOptions uiStateOptions;
};
