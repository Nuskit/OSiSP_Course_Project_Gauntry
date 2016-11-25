#pragma once
#include "stdafx.h"

class GameLoopState
{
public:
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual void render(double lagTime) = 0;
	virtual ~GameLoopState() {};
	virtual void enter() = 0;
	virtual void exit() = 0;
};