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

void TexturedGameObject::renderCustom()
{
	textureGameObject->drawTexture();
}
