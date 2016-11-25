#pragma once
#include "stdafx.h"

class GameLoopState;
class DirectX
{
public:
	DirectX();
	virtual const HRESULT init() = 0;
	virtual void clearUp() = 0;
	virtual void setupMatrixPerspective(const D3DXMATRIX& matrix) = 0;

	virtual ~DirectX();
	void initGameLoop();
	void stepGameLoop();
private:
	void updateGame();
	GameLoopState *gameLoop;
	DWORD previous;
	DWORD lag;
};
