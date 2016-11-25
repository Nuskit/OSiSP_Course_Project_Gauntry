#include "stdafx.h"
#include "GameLoopInitialize.h"
#include "ServiceManager.h"
#include "DirectX.h"
#include "WindowInfromation.h"

#define VISION_ANGLE D3DX_PI / 4
#define CLIPPING_NEAR 1.0f
#define CLIPPING_FAR 100.0f


void GameLoopInitialize::processInput()
{
}

void GameLoopInitialize::update()
{
}

void GameLoopInitialize::render(double lagTime)
{
}

void GameLoopInitialize::enter()
{
	D3DXMATRIX matrixProjection;
	D3DXMatrixPerspectiveFovLH(&matrixProjection, VISION_ANGLE, calculateAspect(), CLIPPING_NEAR, CLIPPING_FAR);

	ServiceManager::getDirectX().setupMatrixPerspective(matrixProjection);
}

void GameLoopInitialize::exit()
{
}

const FLOAT GameLoopInitialize::calculateAspect()
{
	WindowInformation& windowInfromation = ServiceManager::getWindowInformation();
	return static_cast<FLOAT>(windowInfromation.getWidth()) / windowInfromation.getHeight();
}
