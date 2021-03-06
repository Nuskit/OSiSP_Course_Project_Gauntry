#pragma once
#include "stdafx.h"
#include "GameLoopState.h"

class GameLoopInitialize :public GameLoopState
{
public:
	virtual void processInput() override;
	virtual void update() override;
protected:
	virtual void renderFull(double lagTime) override;
	virtual void enterInitialize() override;
	virtual void enterReply() override;
	virtual void exitInitialized() override;
private:
	const FLOAT calculateAspect();
};