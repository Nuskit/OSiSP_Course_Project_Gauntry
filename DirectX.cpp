#include "stdafx.h"
#include "DirectX.h"

#define MS_PER_UPDATE 200

void DirectX::initGameLoop()
{
	previous = GetCurrentTime();
	lag = 0.;
}

void DirectX::stepGameLoop()
{
	double current = GetCurrentTime();
	double elapsed = current - previous;
	previous = current;
	lag += elapsed;

	processInput();
	updateGame();
	render(lag / MS_PER_UPDATE);
}

void DirectX::updateGame()
{
	while (lag >= MS_PER_UPDATE)
	{
		update();
		lag -= MS_PER_UPDATE;
	}
}
