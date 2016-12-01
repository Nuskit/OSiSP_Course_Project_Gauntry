#include "stdafx.h"
#include "AttackedGyro.h"
#include "TexturedGameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

#define ROTATE_ATTACKED_GYRO_SPEED 0.02f

AttackedGyro::AttackedGyro(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void AttackedGyro::renderCustom(double lagTime)
{
	DirectX& directX = getServiceManager().getDirectX();
	DWORD oldRenderState;
	directX.getRenderState(D3DRS_CULLMODE, oldRenderState);
	directX.setRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	gameObject_->renderCustom(lagTime);
	directX.setRenderState(D3DRS_CULLMODE, oldRenderState);
}

void AttackedGyro::updateCustom()
{
	D3DXMATRIX matRotate, matPosition;
	D3DXMatrixTranslation(&matPosition, -150.f, 70.f, -150.f);
	D3DXMatrixRotationY(&matRotate, ROTATE_ATTACKED_GYRO_SPEED);
	updateView(matPosition*matRotate);
}
