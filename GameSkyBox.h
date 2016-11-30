#pragma once
#include "stdafx.h"
#include "GameObject.h"

class TexturedGameObject;
class SkyBox: public GameObject
{
public:
	SkyBox(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject);
	~SkyBox();
	virtual void renderCustom(double lagTime) override;
	virtual void updateCustom() override;
private:
	TexturedGameObject* gameObject_;
	FLOAT rotateYAngle;
};
