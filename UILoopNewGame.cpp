#include "stdafx.h"
#include "UILoopNewGame.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "CameraController.h"
#include "ShortcutController.h"
#include "UILoopMainMenu.h"

UILoopNewGame UILoopState::uiStateNewGame;

bool UILoopNewGame::MsgProc(MsgProcParam & msgProc)
{
	switch (msgProc.msg)
	{
	case WM_ACTIVATE:
		handledClipCursosOnCenter();
		break;
	case WM_KILLFOCUS:
		freeClipCursosOnCenter();
		break;
	case WM_MOUSEMOVE:
		if (isHandled)
			changeCameraPosition(LOWORD(msgProc.lParam), HIWORD(msgProc.lParam));
		break;
	case WM_KEYDOWN:
		if (msgProc.wParam == VK_ESCAPE)
			getServiceManager().getWindowInformation().changeState(&UILoopState::uiStateMainMenu);
		else if (!(msgProc.lParam & (1 << 30)))
			getServiceManager().getShortcutController().downKey(msgProc.wParam);
		break;
	case WM_KEYUP:
		getServiceManager().getShortcutController().upKey(msgProc.wParam);
		break;
	}
	return false;
}

void UILoopNewGame::changeCameraPosition(WORD x, WORD y)
{
	getServiceManager().getCameraController().changePosition(x - centerWindow.x, y - centerWindow.y);
}

void UILoopNewGame::enterInitialize()
{
	handledClipCursosOnCenter();
}

void UILoopNewGame::enterReply()
{
	handledClipCursosOnCenter();
}

void UILoopNewGame::exitInitialized()
{
	freeClipCursosOnCenter();
}

void UILoopNewGame::handledClipCursosOnCenter()
{
	if (!isHandled)
	{
		WindowInformation& windowInformation = getServiceManager().getWindowInformation();
		POINT center{ windowInformation.getWidth() / 2,windowInformation.getHeight() / 2 };
		centerWindow = center;
		ClientToScreen(windowInformation.getHWND(), &center);
		RECT centerRect{ center.x, center.y ,
			center.x, center.y };
		GetClipCursor(&oldRect);
		isHandled = true;
		//SetCapture(windowInformation.getHWND());
		ClipCursor(&centerRect);
	}
}

void UILoopNewGame::freeClipCursosOnCenter()
{
	if (isHandled)
	{
		//ReleaseCapture();
		ClipCursor(&oldRect);
		isHandled = false;
	}
}
