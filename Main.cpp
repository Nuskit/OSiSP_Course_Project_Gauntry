#include "stdafx.h"
#include "MainApplication.h"
#include "ServiceManager.h"
#include "DirectX_9.h"
#include "World.h"

void InitServiceManager();

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);
	InitServiceManager();
	MainApplication GameApplication(1024, 768);
	if (SUCCEEDED(GameApplication.initApplication()))
		GameApplication.runMainLoop();
	return S_OK;
}

void InitServiceManager()
{
	getServiceManager().provide(new DirectX_9());
}
