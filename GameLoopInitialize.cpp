#include "stdafx.h"
#include "GameLoopInitialize.h"
#include "ServiceManager.h"
#include "DirectX.h"
#include "WindowInfromation.h"

#define VISION_ANGLE D3DX_PI / 4
#define CLIPPING_NEAR 1.0f
#define CLIPPING_FAR 100.0f

GameLoopInitialize  GameLoopState::gameStateInitialize;

void GameLoopInitialize::processInput()
{
}

void GameLoopInitialize::update()
{
}

void GameLoopInitialize::renderFull(double lagTime)
{
}

void GameLoopInitialize::enterInitialize()
{
	D3DXMATRIX matrixProjection;
	D3DXMatrixPerspectiveFovLH(&matrixProjection, VISION_ANGLE, calculateAspect(), CLIPPING_NEAR, CLIPPING_FAR);

	getServiceManager().getDirectX().setupMatrixPerspective(matrixProjection);
}

const FLOAT GameLoopInitialize::calculateAspect()
{
	WindowInformation& windowInfromation = getServiceManager().getWindowInformation();
	return static_cast<FLOAT>(windowInfromation.getWidth()) / windowInfromation.getHeight();
}

void GameLoopInitialize::enterReply()
{
}

void GameLoopInitialize::exitInitialized()
{
}
