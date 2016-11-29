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
	virtual void preRender() = 0;
	virtual bool startRender() = 0;
	virtual void endRender() = 0;
	virtual void postRender() = 0;
	void changeState(GameLoopState* uiState);
	virtual ~DirectX();
	void initGameLoop();
	void stepGameLoop();
private:
	void updateGame();
	GameLoopState *gameLoop_;
	DWORD previous;
	DWORD lag;
};
