#pragma once
#include "stdafx.h"

class BaseState
{
public:
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual ~BaseState() {};
};