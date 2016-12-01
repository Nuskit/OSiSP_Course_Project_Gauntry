#include "stdafx.h"
#include "Car.h"
#include "TexturedGameObject.h"

Car::Car(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Car::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Car::updateCustom()
{
}
