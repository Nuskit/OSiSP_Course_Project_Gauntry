#include "stdafx.h"
#include "GameObjectTexture.h"
#include "ServiceManager.h"
#include "DirectX.h"
#include "d3dUtility.h"

GameObjectTexture::GameObjectTexture(LPCWSTR nameFile, LPCSTR folder) :meshX(new MeshFromX()),
textures(nullptr), materials(nullptr)
{
	if (getServiceManager().getDirectX().loadMeshFromX(nameFile, *meshX))
		LoadTextureFromX(folder);
	else
	{
		delete meshX;
		//TODO: load null object
		char buf[300];
		sprintf(buf, "Invalid texture folder %s.\n", folder);
		throw std::invalid_argument(buf);
	}
}

void GameObjectTexture::drawTexture()
{
	DirectX& directX = getServiceManager().getDirectX();
	for (DWORD i = 0; i < meshX->NumMaterials; ++i)
	{
		directX.setMaterial(materials[i]);
		if (textures[i])
			directX.setTexture(textures[i]);
		meshX->pMesh->DrawSubset(i);
	}
}

GameObjectTexture::~GameObjectTexture()
{
	delete meshX;
	delete[] textures;
	delete[] materials;
}

void GameObjectTexture::setMaterialEmissive(UINT number,const D3DCOLORVALUE& rgba)
{
	assert(meshX->NumMaterials > number);
	materials[number].Emissive = rgba;
}

void GameObjectTexture::loadExtraTextures(UINT number, LPCWSTR nameFile)
{
	assert(meshX->NumMaterials > number);
	d3d::Release<LPDIRECT3DTEXTURE9>(textures[number]);
	getServiceManager().getDirectX().createTextureFromFile(nameFile, textures[number]);
}

void GameObjectTexture::LoadTextureFromX(LPCSTR folder)
{
	//
	// Извлечение материалов и загрузка текстур
	//
	if (meshX->NumMaterials > 0 && meshX->pMaterials)
	{
		materials = new D3DMATERIAL9[meshX->NumMaterials];
		textures = new LPDIRECT3DTEXTURE9[meshX->NumMaterials];

		D3DXMATERIAL* foundMaterials = (D3DXMATERIAL*)(meshX->pMaterials)->
			GetBufferPointer();

		CHAR pathFullTexture[60];
		DirectX& directX = getServiceManager().getDirectX();

		for (DWORD i = 0; i < meshX->NumMaterials; ++i)
		{
			// При загрузке в свойстве MatD3D не устанавливается
			// значение для фонового света, поэтому установим его
			// сейчас
			foundMaterials[i].MatD3D.Ambient = foundMaterials[i].MatD3D.Diffuse;

			textures[i] = NULL;
			// Сохраняем i-ый материал
			materials[i] = foundMaterials[i].MatD3D;

			// Проверяем, связана ли с i-ым материалом текстура
			if (foundMaterials[i].pTextureFilename != NULL)
			{
				// Да, загружаем текстуру для i-ой подгруппы
				strcpy(pathFullTexture, folder);
				strcat(pathFullTexture, foundMaterials[i].pTextureFilename);
				directX.createTextureFromFile(pathFullTexture, textures[i]);
			}
		}
		d3d::Release<LPD3DXBUFFER>(meshX->pMaterials);
	}
}
