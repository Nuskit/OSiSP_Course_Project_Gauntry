#include "stdafx.h"
#include "UILoopMainMenu.h"
#include "UILibrary.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "LoadStringFromResource.h"
#include "UILoopOptions.h"
#include "UILoopNewGame.h"

UILoopMainMenu UILoopState::uiStateMainMenu;

void UILoopMainMenu::enterInitialize()
{
	buttons.push_back(createMenuButton(ID_BUTTON_NEW_GAME, 0));
	buttons.push_back(createMenuButton(ID_BUTTON_OPTIONS, 1));
	buttons.push_back(createMenuButton(ID_BUTTON_EXIT, 2));
	MessageBeep(MB_OK);
}

void UILoopMainMenu::enterReply()
{
	for (auto& button : buttons)
		ShowWindow(button, SW_SHOW);
}

HWND UILoopMainMenu::createMenuButton(int idResourceButton, int indexNumber)
{
	WindowInformation& windowInfromation = getServiceManager().getWindowInformation();
	HWND button = CreateButton(windowInfromation.getHWND(), LoadStringFromResource(idResourceButton), idResourceButton,
		windowInfromation.getWidth() / 3, windowInfromation.getHeight() / 3 + HEIGHT_BUTTON*indexNumber);
	assert(button != NULL);
	return button;
}

void UILoopMainMenu::exitInitialized()
{
	for (auto& button : buttons)
		ShowWindow(button, SW_HIDE);
}

bool UILoopMainMenu::MsgProc(MsgProcParam & msgProc)
{
	switch (msgProc.msg)
	{
	case WM_COMMAND:
	{
		switch (msgProc.wParam)
		{
		case ID_BUTTON_NEW_GAME:
			msgProc.nextState = &UILoopState::uiStateNewGame;
			return true;
			break;
		case ID_BUTTON_OPTIONS:
			msgProc.nextState = &UILoopState::uiStateOptions;
			return true;
			break;
		case ID_BUTTON_EXIT:
			SendMessage(msgProc.hWnd, WM_CLOSE, 0, 0);
			return true;
			break;
		}
		break;
	}
	break;
	}
	return false;
}
