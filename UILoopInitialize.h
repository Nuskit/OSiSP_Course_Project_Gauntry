#pragma once
#include "stdafx.h"
#include "UILoopState.h"

class UILoopStateInitialize :public UILoopState
{
public:
	virtual void enter() override;
	virtual void exit() override;
	virtual bool MsgProc(MsgProcParam& msgProc) override;
private:
	void killTimer();
	UINT_PTR timer;
};
