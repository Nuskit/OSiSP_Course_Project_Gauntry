#pragma once
#include "stdafx.h"

class BaseState
{
public:
	void enter();
	void exit();
	virtual ~BaseState() {};
protected:
	virtual void enterInitialize() = 0;
	virtual void enterReply() = 0;
	virtual void exitInitialized() = 0;
	bool isInitialize();
private:
	void setInitialized();
	bool isInit = false;
};