#include "stdafx.h"
#include "DirectX.h"
#include "GameLoopState.h"
#include "GameLoopInitialize.h"

#define MS_PER_UPDATE 100

DirectX::DirectX():gameLoop(nullptr)
{
}

DirectX::~DirectX()
{
	if (gameLoop)
		gameLoop->exit();
	delete gameLoop;
}

void DirectX::initGameLoop()
{
	gameLoop = new GameLoopInitialize();
	gameLoop->enter();
	previous = GetCurrentTime();
	lag = 0;
}

void DirectX::stepGameLoop()
{
	assert(gameLoop != nullptr);
	DWORD current = GetCurrentTime();
	DWORD elapsed = current - previous;
	previous = current;
	lag += elapsed;

	gameLoop->processInput();
	updateGame();
	gameLoop->render(static_cast<double>(lag) / MS_PER_UPDATE);
}

void DirectX::updateGame()
{
	while (lag >= MS_PER_UPDATE)
	{
		gameLoop->update();
		lag -= MS_PER_UPDATE;
	}
}