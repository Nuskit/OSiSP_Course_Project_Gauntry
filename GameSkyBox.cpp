#include "stdafx.h"
#include "GameSkyBox.h"
#include "TexturedGameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

#define ROTATE_SPEED 0.001f

SkyBox::SkyBox(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject * gameObject) : GameObject(scale, position, view),
	gameObject_(gameObject), rotateYAngle(0.f)
{
}

SkyBox::~SkyBox()
{
	delete gameObject_;
}

void SkyBox::renderCustom(double lagTime)
{
	DirectX& directX = getServiceManager().getDirectX();
	DWORD oldRenderState;
	directX.getRenderState(D3DRS_CULLMODE, oldRenderState);
	directX.setRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	gameObject_->renderCustom(lagTime);
	directX.setRenderState(D3DRS_CULLMODE, oldRenderState);
}

void SkyBox::updateCustom()
{
	rotateYAngle = (rotateYAngle + ROTATE_SPEED) / (2 * M_PI);
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, rotateYAngle);
	updateView(matRotate);
}
