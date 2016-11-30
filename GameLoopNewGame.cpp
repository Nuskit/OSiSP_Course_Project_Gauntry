#include "stdafx.h"
#include "GameLoopNewGame.h"
#include "ServiceManager.h"
#include "World.h"
#include "LoadStringFromResource.h"
#include "TexturedGameObject.h"
#include "WindowInfromation.h"
#include "Player.h"
#include "CameraController.h"
#include "ShortcutController.h"

GameLoopNewGame GameLoopState::gameStateNewGame;

void GameLoopNewGame::enterInitialize()
{
	getServiceManager().provide(new World());
	getServiceManager().provide(new CameraController());
	getServiceManager().provide(new ShortcutController());
	getServiceManager().getWorld().addObject(new Player());
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
