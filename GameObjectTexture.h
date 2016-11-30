#pragma once
#include "stdafx.h"

//TODO: set general directX textures
struct _MeshFromX;
class GameObjectTexture
{
public:
	GameObjectTexture(LPCWSTR nameFile, LPCSTR folder);
	void drawTexture();
	~GameObjectTexture();
private:
	void LoadTextureFromX(LPCSTR folder);
	struct _MeshFromX* meshX;
	LPDIRECT3DTEXTURE9* textures;
	D3DMATERIAL9* materials;
};
