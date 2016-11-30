#include "stdafx.h"
#include "DirectX_9.h"
#include "d3dUtility.h"
#include "ServiceManager.h"
#include "WindowInfromation.h"

DirectX_9::DirectX_9():pGraphicD3D(NULL), pGraphicD3DDevice(NULL), pGraphicVB(NULL)
{
}

const HRESULT DirectX_9::init()
{
	// Create the D3D object.
	if (NULL == (pGraphicD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	return createDevice();
}

void DirectX_9::setupMatrixPerspective(const D3DXMATRIX& matrix)
{
	pGraphicD3DDevice->SetTransform(D3DTS_PROJECTION, &matrix);
	pGraphicD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}

const HRESULT DirectX_9::createDevice()
{
	
	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	D3DCAPS9 caps;
	pGraphicD3D->GetDeviceCaps(
		D3DADAPTER_DEFAULT, // Означает первичный видеоадаптер
		D3DDEVTYPE_HAL, // Задает тип устройства, обычно D3DDEVTYPE_HAL
		&caps); //которая содержит информацию о возможностях первичного видеоадаптера.

	// Включаем, если есть, аппаратную обработку вершин
	int vp = NULL;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// да, сохраняем в vp флаг поддержки аппаратной
		// обработки вершин.
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// Нет, сохраняем в vp флаг использования программной
		// обработки вершин.
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (FAILED(pGraphicD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, getServiceManager().getWindowInformation().getHWND(),
		vp, &d3dpp, &pGraphicD3DDevice)))
	{
		return E_FAIL;
	}
	// Device state would normally be set here


	//if (FAILED(D3DXCreateFont(pGraphicD3DDevice, -12, 25, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
	//	OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
	//	L"System", &MyText)))
	//	return E_FAIL;

	pGraphicD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pGraphicD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pGraphicD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// Turn on the zbuffer
	pGraphicD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Turn on ambient lighting 
	pGraphicD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x0000000);

	return S_OK;
}

void DirectX_9::setMaterial(const D3DMATERIAL9 & material)
{
	pGraphicD3DDevice->SetMaterial(&material);
}

void DirectX_9::setTexture(const LPDIRECT3DTEXTURE9 & texture)
{
	pGraphicD3DDevice->SetTexture(0, texture);
}

void DirectX_9::setWorldTransform(const D3DXMATRIX & worldMatrix)
{
	pGraphicD3DDevice->SetTransform(D3DTS_WORLD, &worldMatrix);
}

HRESULT DirectX_9::createTextureFromFile(LPCSTR pSrcFile, LPDIRECT3DTEXTURE9 & pTexture)
{
	return D3DXCreateTextureFromFileA(pGraphicD3DDevice, pSrcFile, &pTexture);
}

void DirectX_9::preRender()
{
	// Clear the backbuffer to a blue color
	pGraphicD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 240), 1.0f, 0);
}

bool DirectX_9::startRender()
{
	return SUCCEEDED(pGraphicD3DDevice->BeginScene());
}

void DirectX_9::endRender()
{
	pGraphicD3DDevice->EndScene();
}

void DirectX_9::postRender()
{
	// Present the backbuffer contents to the display
	pGraphicD3DDevice->Present(NULL, NULL, NULL, NULL);
}

bool DirectX_9::loadMeshFromX(LPCWSTR pFilename, MeshFromX& loadedMesh, DWORD Options)
{
	return (SUCCEEDED(D3DXLoadMeshFromX(
		pFilename, Options, pGraphicD3DDevice, &loadedMesh.pAdjacency,
		&loadedMesh.pMaterials, &loadedMesh.pEffectInstances,
		&loadedMesh.NumMaterials, &loadedMesh.pMesh))
		);
}

void DirectX_9::clearUp()
{
		d3d::Release<LPDIRECT3D9>(pGraphicD3D);
		d3d::Release<LPDIRECT3DDEVICE9>(pGraphicD3DDevice);
		d3d::Release<LPDIRECT3DVERTEXBUFFER9>(pGraphicVB);
	//if (Static_Objects != NULL)
	//	delete[]Static_Objects;
	////добавить удаление объектов
}
