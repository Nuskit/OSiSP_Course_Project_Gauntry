#include "stdafx.h"
#include "MainApplication.h"
#include "MainWindow.h"
#include "ServiceManager.h"
#include "DirectX.h"

#define MAX_FRAMERATE 60
#define FRAMERATE_TIME 1000

MainApplication::MainApplication(DWORD width, DWORD height) : mainWindow_(new MainWindow(width,height))
{
	getServiceManager().provide(mainWindow_);
}

MainApplication::~MainApplication()
{
	getServiceManager().getDirectX().clearUp();
	delete mainWindow_;
}

HRESULT MainApplication::initApplication()
{
	HRESULT result = initDirectX();
	if (FAILED(result))
		MessageBox(mainWindow_->getHWND(), L"Failed init directX", L"Error", MB_OK);
	return result;
}

void MainApplication::runMainLoop()
{
	mainWindow_->initWindowLoop();
	int frameRate = 0;
	DWORD startTime = GetCurrentTime();
	getServiceManager().getDirectX().initGameLoop();
	while (mainWindow_->workWindowLoop())
	{
		getServiceManager().getDirectX().stepGameLoop();
		if (++frameRate == MAX_FRAMERATE)
		{
			DWORD lastTime = GetCurrentTime();
			DWORD elapsed = lastTime - startTime;
			frameRate = 0;
			if (elapsed < FRAMERATE_TIME)
				Sleep(FRAMERATE_TIME - elapsed);
			startTime = lastTime;
		}
	}
}

HRESULT MainApplication::initDirectX()
{
	return getServiceManager().getDirectX().init();
}
