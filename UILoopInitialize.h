#pragma once
#include "stdafx.h"
#include "UILoopState.h"

class UILoopInitialize :public UILoopState
{
public:
	virtual bool MsgProc(MsgProcParam& msgProc) override;
protected:
	virtual void enterInitialize() override;
	virtual void enterReply() override;
	virtual void exitInitialized() override;
private:
	void killTimer();
	UINT_PTR timer;
};
