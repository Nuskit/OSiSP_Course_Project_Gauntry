#include "stdafx.h"
#include "Gyro.h"
#include "TexturedGameObject.h"

#define WALK_GYRO_BORDER 500
#define WALK_GYRO_DELTA 1.f

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
	D3DXMATRIX position = getPosition();
	position._41 = (position._41 > WALK_GYRO_BORDER ? -WALK_GYRO_BORDER : position._41) + WALK_GYRO_DELTA;
	setPosition(position);
}
