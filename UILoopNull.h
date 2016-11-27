#pragma once
#include "stdafx.h"
#include "UILoopState.h"

class UILoopNull :public UILoopState
{
public:
	virtual void enter() override;
	virtual void exit() override;
	virtual bool MsgProc(MsgProcParam& msgProc) override;
};
