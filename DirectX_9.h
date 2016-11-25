#pragma once
#include "stdafx.h"
#include "DirectX.h"

class DirectX_9 :public DirectX
{
public:
	virtual const HRESULT init(HWND hWnd) override;
	virtual void clearUp() override;
	DirectX_9();
protected:
	virtual void processInput() override;
	virtual void update() override;
	virtual void render(double lagTime) override;
private:
	const HRESULT createDevice(HWND hWnd);


	LPDIRECT3D9             pGraphicD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       pGraphicD3DDevice; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9 pGraphicVB;
};
