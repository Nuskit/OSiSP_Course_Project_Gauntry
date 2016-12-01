#include "stdafx.h"
#include "Car.h"
#include "TexturedGameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

#define WALK_CAR_BORDER 500
#define WALK_CAR_DELTA 1.f

Car::Car(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Car::renderCustom(double lagTime)
{
	DirectX& directX = getServiceManager().getDirectX();
	DWORD oldRenderState;
	directX.getRenderState(D3DRS_CULLMODE, oldRenderState);
	directX.setRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	gameObject_->renderCustom(lagTime);
	directX.setRenderState(D3DRS_CULLMODE, oldRenderState);
}

void Car::updateCustom()
{
	D3DXMATRIX position = getPosition();
	position._41 = (position._41 < -WALK_CAR_BORDER ? WALK_CAR_BORDER : position._41) - WALK_CAR_DELTA;
	setPosition(position);
}
