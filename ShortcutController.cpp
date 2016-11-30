#include "stdafx.h"
#include "ShortcutController.h"

void ShortcutController::downKey(WPARAM wParam)
{
	keys.push_back(wParam);
}

void ShortcutController::upKey(WPARAM wParam)
{
	keys.remove(wParam);
}
