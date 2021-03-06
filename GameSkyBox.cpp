#include "stdafx.h"
#include "GameSkyBox.h"
#include "TexturedGameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

#define ROTATE_SKYBOX_SPEED 0.0001f

SkyBox::SkyBox(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
	gameObject_(gameObject)
{
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
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, ROTATE_SKYBOX_SPEED);
	updateView(matRotate);
}
