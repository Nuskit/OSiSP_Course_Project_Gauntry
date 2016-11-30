#pragma once
#include "stdafx.h"

typedef struct _MeshFromX
{
	LPD3DXBUFFER pAdjacency;
	LPD3DXBUFFER pMaterials;
	LPD3DXBUFFER pEffectInstances;
	DWORD NumMaterials;
	LPD3DXMESH pMesh;
}MeshFromX;

class GameLoopState;
class DirectX
{
public:
	DirectX();
	virtual const HRESULT init() = 0;
	virtual void clearUp() = 0;
	virtual void setupMatrixPerspective(const D3DXMATRIX& matrix) = 0;
	virtual void preRender() = 0;
	virtual bool startRender() = 0;
	virtual void endRender() = 0;
	virtual void postRender() = 0;
	virtual bool loadMeshFromX(LPCWSTR pFilename, MeshFromX& loadedMesh, DWORD Options = D3DXMESH_MANAGED) = 0;
	//only v_9
	virtual HRESULT createTextureFromFile(LPCSTR pSrcFile, LPDIRECT3DTEXTURE9& pTexture) = 0;
	virtual void setWorldTransform(const D3DXMATRIX& worldMatrix) = 0;
	//only v_9
	virtual void setMaterial(const D3DMATERIAL9& material) = 0;
	//only v_9
	virtual void setTexture(const LPDIRECT3DTEXTURE9& texture) = 0;
	void changeState(GameLoopState* uiState);
	virtual ~DirectX();
	void initGameLoop();
	void stepGameLoop();
private:
	void updateGame();
	GameLoopState *gameLoop_;
	DWORD previous;
	DWORD lag;
};