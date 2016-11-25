//-----------------------------------------------------------------------------
//All rights reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "MainWindow.h"
#include "LoadStringFromResource.h"

enum
{
	DEFAULT_WINDOW_WIDTH = 1024,
	DEFAULT_WINDOW_HEIGHT = 768
};

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MainWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND MainWindow::createWindowObject()
{
	// Register the window class
	wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MainWindow::MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		LoadStringFromResource(ID_APPLICATION_MENU_NAME), NULL
	};
	RegisterClassEx(&wc);
	// Create the application's window
	return CreateWindow(LoadStringFromResource(ID_APPLICATION_MENU_NAME), LoadStringFromResource(ID_APPLICATION_NAME),
		WS_OVERLAPPEDWINDOW, 0, 0, windowWidth, windowHeight, NULL, NULL, wc.hInstance, NULL);
}

MainWindow::MainWindow(DWORD width, DWORD height) : windowWidth(width>0 ? width : DEFAULT_WINDOW_WIDTH), windowHeight(height>0 ? height : DEFAULT_WINDOW_HEIGHT),
hWnd(createWindowObject())
{
}

HWND MainWindow::getHWND()
{
	return hWnd;
}

bool MainWindow::workWindowLoop()
{
	//if (SUCCEEDED(Game_Window.Initialization_static_object()))

	//Create_D3D9::SetupMatrices(Game_Window);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void MainWindow::initWindowLoop()
{
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	UnregisterClass(LoadStringFromResource(ID_APPLICATION_NAME), wc.hInstance);
}
