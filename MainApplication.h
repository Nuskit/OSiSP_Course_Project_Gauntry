#pragma once
#include "stdafx.h"

class MainWindow;
class MainApplication
{
public:
	MainApplication(DWORD width, DWORD height);
	HRESULT initApplication();
	void runMainLoop();
	~MainApplication();
private:
	HRESULT initDirectX();
	MainWindow* mainWindow_;
};
