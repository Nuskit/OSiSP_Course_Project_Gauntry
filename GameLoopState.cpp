#include "stdafx.h"
#include "GameLoopState.h"
#include "ServiceManager.h"
#include "DirectX.h"

void GameLoopState::render(double lagTime)
{
	DirectX& directX = getServiceManager().getDirectX();
	directX.preRender();
	if (directX.startRender())
	{
		renderFull(lagTime);
		directX.endRender();
	}
	directX.postRender();
}
