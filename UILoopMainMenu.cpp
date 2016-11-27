#include "stdafx.h"
#include "UILoopMainMenu.h"
#include "UILibrary.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "LoadStringFromResource.h"

void UILoopMainMenu::enter()
{
	buttons.push(createMenuButton(ID_BUTTON_NEW_GAME, 0));
	buttons.push(createMenuButton(ID_BUTTON_OPTIONS, 1));
	buttons.push(createMenuButton(ID_BUTTON_EXIT, 2));
	MessageBeep(MB_OK);
}

HWND UILoopMainMenu::createMenuButton(int idResourceButton, int indexNumber)
{
	WindowInformation& windowInfromation = getServiceManager().getWindowInformation();
	HWND button = CreateButton(windowInfromation.getHWND(), LoadStringFromResource(idResourceButton), idResourceButton,
		windowInfromation.getWidth() / 3, windowInfromation.getHeight() / 3 + HEIGHT_BUTTON*indexNumber);
	assert(button != NULL);
	return button;
}

void UILoopMainMenu::exit()
{
	while (buttons.size() > 0)
		CloseHandle(buttons.top());
}

bool UILoopMainMenu::MsgProc(MsgProcParam & msgProc)
{
	switch (msgProc.msg)
	{
	case WM_COMMAND:
	{
		switch (msgProc.wParam)
		{
		case ID_BUTTON_OPTIONS:
			break;
		case ID_BUTTON_EXIT:
			SendMessage(msgProc.hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	}
	}
	return false;
}
