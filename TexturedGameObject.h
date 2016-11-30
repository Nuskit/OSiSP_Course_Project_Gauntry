#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GameObjectTexture;
class TexturedGameObject :public GameObject
{
public:
	TexturedGameObject(LPCWSTR nameFile, LPCSTR folder, GameObject* parent = nullptr);
	virtual ~TexturedGameObject();
	void setMaterialEmissive(UINT number, const D3DCOLORVALUE& rgba);
	void loadExtraTextures(UINT number, LPCWSTR nameFile);
public:
	virtual void renderCustom(double lagTime) override;
	virtual void updateCustom() override;
private:
	GameObjectTexture* textureGameObject;
};
