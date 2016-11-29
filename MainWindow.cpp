#include "stdafx.h"
#include "MainWindow.h"
#include "LoadStringFromResource.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "UILoopInitialize.h"
#include "DirectX.h"
#include "LinkUIGameState.h"

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
	default:
	{
		UILoopState::MsgProcParam msgProc{ hWnd, msg, wParam,lParam,0,nullptr };
		if (getServiceManager().getUIState().MsgProc(msgProc))
		{
			if (msgProc.nextState != nullptr)
				getServiceManager().getWindowInformation().changeState(msgProc.nextState);
			
			return msgProc.result;
		}
		else
			return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	}
	return 0;
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

void MainWindow::changeState(UILoopState * uiState)
{
	assert(uiState != nullptr);
	uiState_->exit();
	uiState_ = uiState;
	getServiceManager().provide(uiState);
	uiState->enter();
	getServiceManager().getDirectX().changeState(GetLinkUiToGameStates(uiState));
	//delete oldState;
}

const DWORD MainWindow::getWidth()
{
	return windowWidth;
}

const DWORD MainWindow::getHeight()
{
	return windowHeight;
}

HWND MainWindow::getHWND()
{
	return hWnd;
}

MainWindow::MainWindow(DWORD width, DWORD height) :windowWidth(width > 0 ? width : DEFAULT_WINDOW_WIDTH),
windowHeight(height > 0 ? height : DEFAULT_WINDOW_HEIGHT), hWnd(createWindowObject())
{
}

bool MainWindow::workWindowLoop()
{
	InvalidateRect(hWnd, NULL, false);
	UpdateWindow(hWnd);
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
	uiState_ = &UILoopState::uiStateInitialize;
	getServiceManager().provide(uiState_);
	uiState_->enter();

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	uiState_->exit();
	//delete uiState_;
	UnregisterClass(LoadStringFromResource(ID_APPLICATION_NAME), wc.hInstance);
}
