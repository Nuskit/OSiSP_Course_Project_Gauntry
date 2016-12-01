#include "stdafx.h"
#include "EvilDrone.h"
#include "TexturedGameObject.h"

EvilDrone::EvilDrone(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void EvilDrone::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void EvilDrone::updateCustom()
{
}
