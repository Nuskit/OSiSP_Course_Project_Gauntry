#include "stdafx.h"
#include "Chair.h"
#include "TexturedGameObject.h"

#define ROTATE_CHAIR_SPEED 0.005f

Chair::Chair(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Chair::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Chair::updateCustom()
{
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, -ROTATE_CHAIR_SPEED);
	updateView(matRotate);
}
