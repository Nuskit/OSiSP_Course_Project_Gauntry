#include "stdafx.h"
#include "UILoopInitialize.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"
#include "Defines.h"
#include "UILoopMainMenu.h"

void UILoopStateInitialize::enter()
{
	WindowInformation& windowInformation = getServiceManager().getWindowInformation();

	//TODO: Load logo
	MessageBeep(MB_ICONEXCLAMATION);

	timer = SetTimer(windowInformation.getHWND(), TIMER_INITIALIZE_ID, TIMER_INITIALIZE_TIMEOUT, NULL);
	assert(timer != NULL);
}

void UILoopStateInitialize::exit()
{
	killTimer();
}

void UILoopStateInitialize::killTimer()
{
	if (timer)
	{
		KillTimer(NULL, timer);
		timer = NULL;
	}
}

bool UILoopStateInitialize::MsgProc(MsgProcParam& msgProc)
{
	switch (msgProc.msg)
	{
	case (WM_TIMER):
		killTimer();
		getServiceManager().getWindowInformation().changeState(new UILoopMainMenu());
		break;
	}
	return false;
}
