#include "stdafx.h"
#include "Airplane.h"
#include "TexturedGameObject.h"

#define WALK_AIRPLANE_DELTA 1.f
#define WALK_AIRPLANE_BORDER 700

Airplane::Airplane(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Airplane::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Airplane::updateCustom()
{
	D3DXMATRIX position = getPosition();
	position._43 = (position._43 > WALK_AIRPLANE_BORDER ? -WALK_AIRPLANE_BORDER : position._43) + WALK_AIRPLANE_DELTA;
	setPosition(position);
}
