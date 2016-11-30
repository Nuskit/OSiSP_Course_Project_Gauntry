#include "stdafx.h"
#include "TexturedGameObject.h"
#include "GameObjectTexture.h"

TexturedGameObject::TexturedGameObject(LPCWSTR nameFile, LPCSTR folder, GameObject* parent) : GameObject(parent),
	textureGameObject(new GameObjectTexture(nameFile, folder))
{
}

TexturedGameObject::~TexturedGameObject()
{
	delete textureGameObject;
}

void TexturedGameObject::setMaterialEmissive(UINT number, const D3DCOLORVALUE & rgba)
{
	textureGameObject->setMaterialEmissive(number, rgba);
}

void TexturedGameObject::loadExtraTextures(UINT number, LPCWSTR nameFile)
{
	textureGameObject->loadExtraTextures(number, nameFile);
}

void TexturedGameObject::updateCustom()
{
}

void TexturedGameObject::renderCustom(double lagTime)
{
	textureGameObject->drawTexture();
}
