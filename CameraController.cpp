#include "stdafx.h"
#include "CameraController.h"

CameraController::CameraController()
{
	clearPosition();
}

void CameraController::changePosition(int dx, int dy)
{
	oldView.x += dx;
	oldView.y += dy;
}

POINT CameraController::getPosition()
{
	return oldView;
}

void CameraController::clearPosition()
{
	oldView.x = 0;
	oldView.y = 0;
}
