#include "stdafx.h"
#include "DirectX.h"
#include "GameLoopInitialize.h"

#define MS_PER_UPDATE 20

DirectX::DirectX():gameLoop_(nullptr)
{
}

void DirectX::changeState(GameLoopState * gameLoop)
{
	if (gameLoop != nullptr)
	{
		gameLoop_->exit();
		gameLoop->enter();
		gameLoop_ = gameLoop;
	}
}

DirectX::~DirectX()
{
	if (gameLoop_)
		gameLoop_->exit();
}

void DirectX::initGameLoop()
{
	gameLoop_ = &GameLoopState::gameStateInitialize;
	gameLoop_->enter();
	previous = GetCurrentTime();
	lag = 0;
}

void DirectX::stepGameLoop()
{
	assert(gameLoop_ != nullptr);
	DWORD current = GetCurrentTime();
	DWORD elapsed = current - previous;
	previous = current;
	lag += elapsed;

	gameLoop_->processInput();
	updateGame();
	gameLoop_->render(static_cast<double>(lag) / MS_PER_UPDATE);
}

void DirectX::updateGame()
{
	while (lag >= MS_PER_UPDATE)
	{
		gameLoop_->update();
		lag -= MS_PER_UPDATE;
	}
}