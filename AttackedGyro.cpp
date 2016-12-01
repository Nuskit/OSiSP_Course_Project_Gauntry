#include "stdafx.h"
#include "AttackedGyro.h"
#include "TexturedGameObject.h"

AttackedGyro::AttackedGyro(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void AttackedGyro::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void AttackedGyro::updateCustom()
{
}
