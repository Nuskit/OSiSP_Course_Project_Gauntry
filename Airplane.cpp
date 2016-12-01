#include "stdafx.h"
#include "Airplane.h"
#include "TexturedGameObject.h"

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
}
