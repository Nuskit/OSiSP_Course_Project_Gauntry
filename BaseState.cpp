#include "stdafx.h"
#include "BaseState.h"

bool BaseState::isInitialize()
{
	return isInit;
}

void BaseState::setInitialized()
{
	isInit = true;
}

void BaseState::enter()
{
	if (isInitialize())
		enterReply();
	else
	{
		enterInitialize();
		setInitialized();
	}
}

void BaseState::exit()
{
	if (isInitialize())
		exitInitialized();
}
