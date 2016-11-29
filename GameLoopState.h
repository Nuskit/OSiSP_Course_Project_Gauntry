#pragma once
#include "stdafx.h"
#include "BaseState.h"

class GameLoopInitialize;
class GameLoopMainMenu;
class GameLoopNewGame;
class GameLoopState : public BaseState
{
public:
	virtual void processInput() = 0;
	virtual void update() = 0;
	void render(double lagTime);
protected:
	virtual void renderFull(double lagTime) = 0;
public:
	static GameLoopInitialize gameStateInitialize;
	static GameLoopMainMenu gameStateMainMenu;
	static GameLoopNewGame gameStateNewGame;
};