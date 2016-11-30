#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GameObjectTexture;
class TexturedGameObject :public GameObject
{
public:
	TexturedGameObject(LPCWSTR nameFile, LPCSTR folder, GameObject* parent = nullptr);
	virtual void renderCustom() override;
	virtual ~TexturedGameObject();
private:
	GameObjectTexture* textureGameObject;
};
