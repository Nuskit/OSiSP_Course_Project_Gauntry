#pragma once
#include "stdafx.h"
#include "DirectX.h"

class DirectX_9 :public DirectX
{
public:
	DirectX_9();
	virtual void clearUp() override;
	virtual const HRESULT init() override;
	virtual void setupMatrixPerspective(const D3DXMATRIX& matrix) override;
	virtual void preRender() override;
	virtual bool startRender() override;
	virtual void endRender() override;
	virtual void postRender() override;
private:
	const HRESULT createDevice();

	LPDIRECT3D9             pGraphicD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       pGraphicD3DDevice; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9 pGraphicVB;
};
