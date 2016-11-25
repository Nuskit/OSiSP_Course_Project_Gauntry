#include "stdafx.h"
#include "MainApplication.h"
#include "MainWindow.h"
#include "ServiceManager.h"
#include "DirectX.h"

MainApplication::MainApplication(DWORD width, DWORD height) : mainWindow_(new MainWindow(width,height))
{
}

MainApplication::~MainApplication()
{
	delete mainWindow_;
	ServiceManager::getDirectX().clearUp();
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
	ServiceManager::getDirectX().initGameLoop();
	while (mainWindow_->workWindowLoop())
	{
		ServiceManager::getDirectX().stepGameLoop();
	}
}

HRESULT MainApplication::initDirectX()
{
	return ServiceManager::getDirectX().init(mainWindow_->getHWND());
}
