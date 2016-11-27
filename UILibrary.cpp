#include "stdafx.h"
#include "UILibrary.h"

#define WIDTH_BUTTON 100

HWND CreateButton(const HWND hWnd, LPCTSTR name, int idButton, int positionX, int positionY)
{
	return CreateWindow(
		L"BUTTON",   // predefined class 
		name,       // button text 
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 
																							 // Size and position values are given explicitly, because 
																							 // the CW_USEDEFAULT constant gives zero values for buttons. 
		positionX,         // starting x position 
		positionY,         // starting y position 
		WIDTH_BUTTON,        // button width 
		HEIGHT_BUTTON,        // button height 
		hWnd,       // parent window 
		(HMENU)idButton,       // No menu 
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // pointer not needed
}
