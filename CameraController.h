#pragma once
#include "stdafx.h"

class CameraController
{
public:
	CameraController();
	void changePosition(int dx, int dy);
	POINT getPosition();
	void clearPosition();
private:
	POINT oldView;
};
