#include "stdafx.h"
#include "GameLoopNewGame.h"
#include "ServiceManager.h"
#include "World.h"
#include "LoadStringFromResource.h"
#include "TexturedGameObject.h"
#include "WindowInfromation.h"

GameLoopNewGame GameLoopState::gameStateNewGame;

void GameLoopNewGame::enterInitialize()
{
	getServiceManager().provide(new World());
	getServiceManager().getWorld().addObject(
		new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_CHAIR), LoadStringFromResourceA(IDS_TEXTURE_CHAIR_FOLDER)));
}

void GameLoopNewGame::enterReply()
{
}

void GameLoopNewGame::exitInitialized()
{
}

void GameLoopNewGame::processInput()
{
}

void GameLoopNewGame::update()
{
	getServiceManager().getWorld().update();
}

void GameLoopNewGame::renderFull(double lagTime)
{
	getServiceManager().getWorld().render(lagTime);
}
