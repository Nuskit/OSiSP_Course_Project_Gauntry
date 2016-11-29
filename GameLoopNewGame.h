#pragma once
#include "stdafx.h"
#include "GameLoopState.h"

class GameLoopNewGame :public GameLoopState
{
public:
	virtual void processInput() override;
	virtual void update() override;
protected:
	virtual void enterInitialize() override;
	virtual void enterReply() override;
	virtual void exitInitialized() override;
	virtual void renderFull(double lagTime) override;
};