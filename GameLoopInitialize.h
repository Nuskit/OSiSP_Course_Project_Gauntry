#pragma once
#include "stdafx.h"
#include "GameLoopState.h"

class GameLoopInitialize :public GameLoopState
{
public:
	virtual void processInput() override;
	virtual void update() override;
	virtual void render(double lagTime) override;
	virtual void enter() override;
	virtual void exit() override;
private:
	const FLOAT calculateAspect();
};