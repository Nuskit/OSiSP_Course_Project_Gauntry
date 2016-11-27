#pragma once
#include "stdafx.h"
#include "BaseState.h"

class UILoopState :public BaseState
{
public:
	typedef struct _MsgProcParam
	{
		HWND hWnd;
		UINT msg; WPARAM wParam; 
		LPARAM lParam;
		LRESULT result;
	}MsgProcParam;
	virtual bool MsgProc(MsgProcParam& msgProc) = 0;
};
