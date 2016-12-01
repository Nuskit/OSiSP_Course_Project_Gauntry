#include "stdafx.h"
#include "Satellite.h"
#include "TexturedGameObject.h"

#define ROTATE_SATELLITE_SPEED 0.01f

Satellite::Satellite(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Satellite::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Satellite::updateCustom()
{
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, ROTATE_SATELLITE_SPEED);
	updateView(matRotate);
}
