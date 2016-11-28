#include "stdafx.h"
#include "UILoopInitialize.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "Defines.h"
#include "UILoopMainMenu.h"


UILoopInitialize UILoopState::uiStateInitialize;


void UILoopInitialize::enterInitialize()
{
		WindowInformation& windowInformation = getServiceManager().getWindowInformation();

		//TODO: Load logo
		MessageBeep(MB_ICONEXCLAMATION);

		timer = SetTimer(windowInformation.getHWND(), TIMER_INITIALIZE_ID, TIMER_INITIALIZE_TIMEOUT, NULL);
		assert(timer != NULL);
}

void UILoopInitialize::enterReply()
{
}

void UILoopInitialize::exitInitialized()
{
	killTimer();
}

void UILoopInitialize::killTimer()
{
	if (timer)
	{
		KillTimer(getServiceManager().getWindowInformation().getHWND(), timer);
		timer = NULL;
	}
}

bool UILoopInitialize::MsgProc(MsgProcParam& msgProc)
{
	switch (msgProc.msg)
	{
	case (WM_TIMER):
		killTimer();
		msgProc.nextState = &UILoopState::uiStateMainMenu;
		return true;
		break;
	}
	return false;
}
