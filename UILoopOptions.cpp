#include "stdafx.h"
#include "UILoopOptions.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "UILibrary.h"
#include "LoadStringFromResource.h"
#include "UILoopMainMenu.h"


UILoopOptions UILoopState::uiStateOptions;

void UILoopOptions::enterInitialize()
{
	buttons.push_back(createMenuButton(ID_BUTTON_RETURN, 0));
}

void UILoopOptions::enterReply()
{
	for (auto& button : buttons)
		ShowWindow(button, SW_SHOW);
}

HWND UILoopOptions::createMenuButton(int idResourceButton, int indexNumber)
{
	WindowInformation& windowInfromation = getServiceManager().getWindowInformation();
	HWND button = CreateButton(windowInfromation.getHWND(), LoadStringFromResourceW(idResourceButton), idResourceButton,
		windowInfromation.getWidth() / 3, windowInfromation.getHeight() / 3 + HEIGHT_BUTTON*indexNumber);
	assert(button != NULL);
	return button;
}

void UILoopOptions::exitInitialized()
{
	for (auto& button : buttons)
		ShowWindow(button, SW_HIDE);
}

bool UILoopOptions::MsgProc(MsgProcParam & msgProc)
{
	switch (msgProc.msg)
	{
	case WM_COMMAND:
	{
		switch (msgProc.wParam)
		{
			//TODO: return last state
		case ID_BUTTON_RETURN:
			msgProc.nextState = &UILoopState::uiStateMainMenu;
			return true;
			break;
		}
		break;
	}
	break;
	}
	return false;
}
