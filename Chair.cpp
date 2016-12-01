#include "stdafx.h"
#include "Chair.h"
#include "TexturedGameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

#define ROTATE_CHAIR_SPEED 0.005f

Chair::Chair(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Chair::renderCustom(double lagTime)
{
	DirectX& directX = getServiceManager().getDirectX();
	DWORD oldRenderState;
	directX.getRenderState(D3DRS_CULLMODE, oldRenderState);
	directX.setRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	gameObject_->renderCustom(lagTime);
	directX.setRenderState(D3DRS_CULLMODE, oldRenderState);
}

void Chair::updateCustom()
{
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, -ROTATE_CHAIR_SPEED);
	updateView(matRotate);
}
