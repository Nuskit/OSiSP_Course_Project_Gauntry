#include "stdafx.h"
#include "Global_Effect.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D=NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice=NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB=NULL; // Buffer to hold vertices