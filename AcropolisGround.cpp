#include "stdafx.h"
#include "AcropolisGround.h"
#include "TexturedGameObject.h"

AcropolisGround::AcropolisGround(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void AcropolisGround::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void AcropolisGround::updateCustom()
{
}
