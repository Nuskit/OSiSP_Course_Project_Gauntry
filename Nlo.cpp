#include "stdafx.h"
#include "Nlo.h"
#include "TexturedGameObject.h"

Nlo::Nlo(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Nlo::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Nlo::updateCustom()
{
}
