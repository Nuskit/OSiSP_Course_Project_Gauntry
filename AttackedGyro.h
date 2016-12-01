#pragma once
#include "stdafx.h"
#include "GameObject.h"

class TexturedGameObject;
class AttackedGyro : public GameObject
{
public:
	AttackedGyro(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject);
	virtual void renderCustom(double lagTime) override;
	virtual void updateCustom() override;
private:
	TexturedGameObject* gameObject_;
};
