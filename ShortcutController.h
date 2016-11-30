#pragma once
#include "stdafx.h"

class Player;
class ShortcutController
{
	friend class Player;
public:
	void downKey(WPARAM wParam);
	void upKey(WPARAM wParam);
private:
	std::list<WPARAM> keys;
};