#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GameObjectTexture;
class TexturedGameObject :public GameObject
{
public:
	TexturedGameObject(LPCWSTR nameFile, LPCSTR folder, GameObject* parent = nullptr);
	virtual ~TexturedGameObject();
protected:
	virtual void renderCustom() override;
	virtual void updateCustom() override;
private:
	GameObjectTexture* textureGameObject;
};
