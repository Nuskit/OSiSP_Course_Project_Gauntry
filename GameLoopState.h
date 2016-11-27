#pragma once
#include "stdafx.h"
#include "BaseState.h"

class GameLoopState : public BaseState
{
public:
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual void render(double lagTime) = 0;
};