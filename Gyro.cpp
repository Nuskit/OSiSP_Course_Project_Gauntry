#include "stdafx.h"
#include "Gyro.h"
#include "TexturedGameObject.h"

Gyro::Gyro(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Gyro::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Gyro::updateCustom()
{
}
