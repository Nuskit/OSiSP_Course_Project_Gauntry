#pragma once

#include <d3dx9mesh.h>
#include <d3dx9core.h>
#include <d3d9.h>
#include "d3dUtility.h"
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

extern LPDIRECT3D9             g_pD3D; // Used to create the D3DDevice
extern LPDIRECT3DDEVICE9       g_pd3dDevice; // Our rendering device
extern LPDIRECT3DVERTEXBUFFER9 g_pVB; // Buffer to hold vertices