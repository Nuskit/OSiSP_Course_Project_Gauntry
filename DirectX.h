#pragma once
#include "stdafx.h"

class DirectX
{
public:
	virtual const HRESULT init(HWND hWnd) = 0;
	virtual void clearUp() = 0;
	virtual ~DirectX() {};
	void initGameLoop();
	void stepGameLoop();
protected:
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual void render(double lagTime) = 0;
private:
	void updateGame();
	double previous;
	double lag;
};
