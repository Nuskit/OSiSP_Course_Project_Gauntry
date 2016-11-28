#include "stdafx.h"
#include "UILoopState.h"

bool UILoopState::isInitialize()
{
	return isInit;
}

void UILoopState::setInitialized()
{
	isInit = true;
}

void UILoopState::enter()
{
	if (isInitialize())
		enterReply();
	else
	{
		enterInitialize();
		setInitialized();
	}
}

void UILoopState::exit()
{
	if (isInitialize())
		exitInitialized();
}
