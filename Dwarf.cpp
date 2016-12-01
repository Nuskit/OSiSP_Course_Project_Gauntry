#include "stdafx.h"
#include "Dwarf.h"
#include "TexturedGameObject.h"

Dwarf::Dwarf(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Dwarf::renderCustom(double lagTime)
{
	gameObject_->renderCustom(lagTime);
}

void Dwarf::updateCustom()
{
}
