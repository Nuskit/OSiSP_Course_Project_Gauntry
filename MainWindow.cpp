//-----------------------------------------------------------------------------
//All rights reserved.
//-----------------------------------------------------------------------------
#pragma once

#include "stdafx.h"
#include "MainWindow.h"
#include "Direct_Operations.h"



//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT MainWindow::InitD3D()
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	D3DCAPS9 caps; 
	g_pD3D->GetDeviceCaps(
		D3DADAPTER_DEFAULT, // Означает первичный видеоадаптер
		D3DDEVTYPE_HAL, // Задает тип устройства, обычно D3DDEVTYPE_HAL
		&caps); //которая содержит информацию о возможностях первичного видеоадаптера.

	// Поддерживается аппаратная обработка вершин?
	int vp=NULL;
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

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      vp, &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here


	if (FAILED(D3DXCreateFont(g_pd3dDevice, -12, 25, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"System", &MyText)))
		return E_FAIL;

	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	
	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Turn on ambient lighting 
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x0000000);

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID Create_D3D9::SetupMatrices(MainWindow &Game_Window)
{
	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, Game_Window.windowWidth/Game_Window.windowHeight, 1.0f, 30000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);


	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT MainWindow::InitVB()
{
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	if (g_pVB != NULL&&g_pVB != LPDIRECT3DVERTEXBUFFER9(0xCCCCCCCCCCCCCCCC) )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();

	if (MyText != NULL)
		MyText->Release();

	if (Static_Objects != NULL)
		delete[]Static_Objects;
	//добавить удаление объектов
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Create_D3D9::Render(MainWindow &Game_Window)
{
	static BOOL First_Render = true;
	HRESULT Result = S_OK;
	
	if (Result != S_OK)
		MessageBox(0, L"Error", 0, 0);
	
	
    // Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 240), 1.0f, 0);

    // Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		static Terrain TheTerrain(g_pd3dDevice, "Textures\\Terrain\\coastMountain64.raw", 64, 64, 310, 12.0f);
		static Camera TheCamera;
		
			// Обновление матрицы вида согласно новому
			// местоположению и ориентации камеры
			TheCamera.getViewMatrix();
			g_pd3dDevice->SetTransform(D3DTS_VIEW, TheCamera.V);
		static float timeDelta = 0.03f;


		if (::GetAsyncKeyState('W') & 0x8000f)
			TheCamera.walk(800.0f * timeDelta);
		if (::GetAsyncKeyState('S') & 0x8000f)
			TheCamera.walk(-800.0f * timeDelta);
		if (::GetAsyncKeyState('A') & 0x8000f)
			TheCamera.strafe(-800.0f * timeDelta);
		if (::GetAsyncKeyState('D') & 0x8000f)
			TheCamera.strafe(800.0f * timeDelta);
		if (::GetAsyncKeyState('R') & 0x8000f)
			TheCamera.fly(800.0f * timeDelta);
		if (::GetAsyncKeyState('F') & 0x8000f)
			TheCamera.fly(-800.0f * timeDelta);
		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			TheCamera.pitch(1.0f * timeDelta);
		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			TheCamera.pitch(-1.0f * timeDelta);
		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			TheCamera.yaw(-1.0f * timeDelta);
		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			TheCamera.yaw(1.0f * timeDelta);
		if (::GetAsyncKeyState('N') & 0x8000f)
			TheCamera.roll(1.0f * timeDelta);
		if (::GetAsyncKeyState('M') & 0x8000f)
			TheCamera.roll(-1.0f * timeDelta);

		
		static float timer_for_terrain = 1;
		static DWORD redraw_timer = 0;
		timer_for_terrain += 0.001;
		++redraw_timer;
		static D3DXVECTOR3 lightDirection;
		lightDirection = D3DXVECTOR3(cosf(timer_for_terrain), -0.5 + fabs(sinf(timer_for_terrain)), sinf(timer_for_terrain * 2));
		if (timer_for_terrain > 255)
			timer_for_terrain = -255;


		static D3DXVECTOR3 look, position;
		static DWORD scaling,i,timer;
		TheCamera.getLook(&look);
		TheCamera.getPosition(&position);

		timer = timeGetTime();

		static D3DLIGHT9 flashlight = d3d::InitSpotLight(&position,&look, &D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)),
			Sun = d3d::InitPointLight(&D3DXVECTOR3(1000, -8050, 5000), &D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)),
			Big_NLO = d3d::InitPointLight(&position, &D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)),
			Dworf = d3d::InitPointLight(&position, &D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
		
		flashlight.Position = position;
		flashlight.Direction = look;		
		
		if (First_Render)
		{
			flashlight.Range = 2000;
			flashlight.Theta = 0.5;
			flashlight.Phi = 1;

			Sun.Range = 10000;
			Dworf.Range = 5450;
		}

		if (redraw_timer > 10)
		{
			redraw_timer = 0;
			TheTerrain.genTexture(&lightDirection);
		}

		
		if (First_Render)
		{
			g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
			First_Render = false;
		}

		g_pd3dDevice->SetLight(1, &Sun);
		g_pd3dDevice->SetLight(2, &flashlight);
		g_pd3dDevice->SetLight(3, &Dworf);
		g_pd3dDevice->LightEnable(1, true);
		g_pd3dDevice->LightEnable(2, true);
		g_pd3dDevice->LightEnable(3, true);

		
		
		static D3DXMATRIX I = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		
		TheTerrain.draw(&I, false);


		physics ::Check_Camera(TheCamera,&TheTerrain);

		// Set up world matrix
		static D3DXMATRIXA16 matWolrd0, matWorld, matWorld1, matWorld2, matWorld3, matWorld4, matWorld5,matWorld6;


		position = Game_Window.Static_Objects[0].Get_Position();
		D3DXMatrixRotationY(&matWorld4, timer / 500.0f);

		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		scaling = Game_Window.Static_Objects[0].Get_Scaling();
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld4*matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[0].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[0].Material_ALL[i]);
			if (Game_Window.Static_Objects[0].Textures[i]!=NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[0].Textures[i]);

			Game_Window.Static_Objects[0].Mesh->DrawSubset(i);
		}

		D3DXMatrixRotationY(&matWorld4, -(timer / 1000.0f));
		D3DXMatrixRotationX(&matWorld3, 3.14);
		position = Game_Window.Static_Objects[1].Get_Position();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		scaling = Game_Window.Static_Objects[1].Get_Scaling();
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld3*matWorld4*matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[1].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[1].Material_ALL[i]);
			if (Game_Window.Static_Objects[1].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[1].Textures[i]);

			Game_Window.Static_Objects[1].Mesh->DrawSubset(i);
		}

		D3DXMatrixRotationX(&matWorld3, 3.14);
		position = Game_Window.Static_Objects[2].Get_Position();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		if (position.z>8400)
			position.z = -8500;
		else
			position.z += 24;
		position.y += sinf(timer_for_terrain)*3;
		Game_Window.Static_Objects[2].Set_Position(position);
		scaling = Game_Window.Static_Objects[2].Get_Scaling();
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld3*matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[2].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[2].Material_ALL[i]);
			if (Game_Window.Static_Objects[2].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[2].Textures[i]);

			Game_Window.Static_Objects[2].Mesh->DrawSubset(i);
		}

		position = Game_Window.Static_Objects[3].Get_Position();
		scaling = Game_Window.Static_Objects[3].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);

		D3DXMatrixTranslation(&matWorld1, -5000, -1000, -5000);
		D3DXMatrixRotationY(&matWorld3, timer / 2000.0f);

		D3DXMatrixRotationX(&matWorld4, 3.14);
		D3DXMatrixRotationY(&matWorld, 3.14);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld*matWorld4*matWorld1*matWorld3*matWorld5));

		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		for (i = 0; i < Game_Window.Static_Objects[3].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[3].Material_ALL[i]);
			if (Game_Window.Static_Objects[3].Textures[i] != NULL)
			g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[3].Textures[i]);

			Game_Window.Static_Objects[3].Mesh->DrawSubset(i);
		}
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);


		position = Game_Window.Static_Objects[4].Get_Position();
		scaling = Game_Window.Static_Objects[4].Get_Scaling();

		if (position.z>8400)
			position.z = -8500+rand()%3000;
		else
			position.z += 24;
		position.y += cosf(timer_for_terrain) * 3;
		Game_Window.Static_Objects[4].Set_Position(position);
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixRotationX(&matWorld4, 3.14);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld4*matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[4].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[4].Material_ALL[i]);
			if (Game_Window.Static_Objects[4].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[4].Textures[i]);

			Game_Window.Static_Objects[4].Mesh->DrawSubset(i);
		}

		position = Game_Window.Static_Objects[5].Get_Position();
		scaling = Game_Window.Static_Objects[5].Get_Scaling();

		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[5].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[5].Material_ALL[i]);
			if (Game_Window.Static_Objects[5].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[5].Textures[i]);

			Game_Window.Static_Objects[5].Mesh->DrawSubset(i);
		}

		position = Game_Window.Static_Objects[6].Get_Position();
		scaling = Game_Window.Static_Objects[6].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		D3DXMatrixRotationX(&matWorld3, 3.14);
		D3DXMatrixRotationY(&matWorld4, 3.14);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld4*matWorld3*matWorld5));

		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		for (i = 0; i < Game_Window.Static_Objects[6].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[6].Material_ALL[i]);
			if (Game_Window.Static_Objects[6].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[6].Textures[i]);

			Game_Window.Static_Objects[6].Mesh->DrawSubset(i);
		}

		
		position = Game_Window.Static_Objects[7].Get_Position();
		if (position.x<-9400)
			position.x = 9500;
		else
			position.x -= 10;
		Game_Window.Static_Objects[7].Set_Position(position);

		physics ::Position_From_Terrain(Game_Window.Static_Objects[7], &TheTerrain);

		scaling = Game_Window.Static_Objects[7].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y-20, position.z);
		D3DXMatrixRotationX(&matWorld3, 3.14);
		D3DXMatrixRotationY(&matWorld4, -3.14/2);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld4*matWorld3*matWorld5));

		
		for (i = 0; i < Game_Window.Static_Objects[7].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[7].Material_ALL[i]);
			if (Game_Window.Static_Objects[7].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[7].Textures[i]);

			Game_Window.Static_Objects[7].Mesh->DrawSubset(i);
		}
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		position = Game_Window.Static_Objects[8].Get_Position();
		scaling = Game_Window.Static_Objects[8].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixTranslation(&matWorld, -1000, -1000, 0);
		D3DXMatrixRotationY(&matWorld3, -(timer / 2000.0f));
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld*matWorld3*matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[8].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[8].Material_ALL[i]);
			if (Game_Window.Static_Objects[8].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[8].Textures[i]);

			Game_Window.Static_Objects[8].Mesh->DrawSubset(i);
		}

		Big_NLO.Position = position;
		g_pd3dDevice->SetLight(3, &Big_NLO);
		g_pd3dDevice->LightEnable(3, true);

		position = Game_Window.Static_Objects[9].Get_Position();
		scaling = Game_Window.Static_Objects[9].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixRotationZ(&matWorld4, 3.14);
		D3DXMatrixRotationY(&matWorld3, timer / 30000.0f);
			
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld3*matWorld4*matWorld5));

		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		for (i = 0; i < Game_Window.Static_Objects[9].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[9].Material_ALL[i]);
			if (Game_Window.Static_Objects[9].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[9].Textures[i]);

			Game_Window.Static_Objects[9].Mesh->DrawSubset(i);
		}

		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		position = Game_Window.Static_Objects[10].Get_Position();
		scaling = Game_Window.Static_Objects[10].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2* matWorld5));

		for (i = 0; i < Game_Window.Static_Objects[10].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[10].Material_ALL[i]);
			if (Game_Window.Static_Objects[10].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[10].Textures[i]);

			Game_Window.Static_Objects[10].Mesh->DrawSubset(i);
		}

		position = Game_Window.Static_Objects[11].Get_Position();
		scaling = Game_Window.Static_Objects[11].Get_Scaling();
		D3DXMatrixTranslation(&matWorld5, position.x, position.y, position.z);
		D3DXMatrixRotationX(&matWorld3, 3.14);
		D3DXMatrixRotationY(&matWorld4, 3.14/2);
		D3DXMatrixScaling(&matWorld2, scaling, scaling, scaling);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld2*matWorld4*matWorld3*matWorld5));

		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		for (i = 0; i < Game_Window.Static_Objects[11].MaterialAmount; ++i)
		{
			g_pd3dDevice->SetMaterial(&Game_Window.Static_Objects[11].Material_ALL[i]);
			if (Game_Window.Static_Objects[11].Textures[i] != NULL)
				g_pd3dDevice->SetTexture(0, Game_Window.Static_Objects[11].Textures[i]);

			Game_Window.Static_Objects[11].Mesh->DrawSubset(i);
		}
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

/*		static RECT Rect = { 10, 10, 200, 200 };
		static wchar_t a[8] = { 0 };


		Game_Window.MyText->DrawText(NULL, a, -1, &Rect, DT_TOP | DT_LEFT, 0xffff0000);

			for (int i = 0; i < 75;i++)
				Mesh->DrawSubset(i);

		static float y = 0;
		static D3DXMATRIX yRot, xRot;
		



		
		D3DXComputeBoundingBox((D3DXVECTOR3*)v, MyWindow.Mesh->GetNumVertices(), D3DXGetFVFVertexSize(MyWindow.Mesh->GetFVF()), &box.min, &box.max);
		MyWindow.Mesh->UnlockVertexBuffer();


		swprintf(a, L"%3.1f_%3.1f", box.min.x,box.max.x);
		MyWindow.MyText->DrawText(NULL, "", -1, &Rect, DT_TOP | DT_LEFT, 0xffff0000);

		D3DXMatrixRotationY(&xRot, y);

		D3DXMatrixTranslation(&yRot, -0, 0, 1.4f);

		MyWindow.g_pd3dDevice->SetTransform(D3DTS_WORLD, &(yRot*xRot));
		
		D3DXMATRIX V = { 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, -1, 0,0,0};
		MyWindow.g_pd3dDevice->SetTransform(D3DTS_VIEW, &V);

		y += 0.01;
		if (y > 6.28)
			y = 0;


		MyWindow.g_pd3dDevice->SetTransform(D3DTS_WORLD, &(xRot*yRot));
*/
		

		// End the scene*/
		g_pd3dDevice->EndScene();

    }

    // Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
	}
	}

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


HRESULT MainWindow::Initialization_static_object()
{
	HRESULT Result = S_OK;

	Static_Objects = new ObjectFromX[12];
	
	if (SUCCEEDED(Static_Objects[0].LoadingObject(L"Textures//Other//shapes1.x", "Textures//Other//", { -5000, -6050, 2000 }, 50))) //satellite
		if (SUCCEEDED(Static_Objects[1].LoadingObject(L"Textures//chair.x", "Textures//", { -4700.0f, -10.0f, -5500.0f }, 100)))
			if (SUCCEEDED(Static_Objects[2].LoadingObject(L"Textures//airplane_2.x", "Textures//", { 0, -5000, -5000 }, 100)))
				if (SUCCEEDED(Static_Objects[3].LoadingObject(L"Textures//Other//LandShark.x(attacked gyro)", "Textures//Other//", { 0.0f, -250.0f, -0.0f }, 1)))//NLO
					if (SUCCEEDED(Static_Objects[4].LoadingObject(L"Textures//Other//heli.x(gyro)", "Textures//Other//", { 4500.0f, -2250.0f, -6500.0 }, 50)))
						if (SUCCEEDED(Static_Objects[5].LoadingObject(L"Textures//Other//EvilDrone-low.x", "Textures//Other//", { -6500.0f, -250.0f, -6500.0f }, 100)))//small_drone
							if (SUCCEEDED(Static_Objects[6].LoadingObject(L"Textures//Other//DwarfWithEffectInstance.x", "Textures//Other//", { -7500.0f, 90.0f, -2500.0f }, 500)))//dynamic set
								if (SUCCEEDED(Static_Objects[7].LoadingObject(L"Textures//Other//car2.x", "Textures//Other//", { 0, -2000, 0 }, 1)))
									if (SUCCEEDED(Static_Objects[8].LoadingObject(L"Textures//Other//bigship1.x", "Textures//Other//", { 0, -3000, 0 }, 20)))//super NLO
										if (SUCCEEDED(Static_Objects[9].LoadingObject(L"Textures//Other//acropolis_sky.x", "Textures//Other//", { 0, 11000, 0 }, 200)))
											if (SUCCEEDED(Static_Objects[10].LoadingObject(L"Textures//Other//acropolis_ground.x", "Textures//Other//", { -6500.0f, -50.0f, -6500.0f }, 28)))
												if (SUCCEEDED(Static_Objects[11].LoadingObject(L"Textures//Other//acropolis.x", "Textures//Other//", { -6500.0f, 150.0f, -6500.0f }, 150)))

											
											{
		Static_Objects[9].Material_ALL[0].Emissive.b=0.9;
		Static_Objects[9].Material_ALL[0].Emissive.g = 0.9;
		Static_Objects[9].Material_ALL[0].Emissive.r = 0.9;

		D3DXCreateTextureFromFile(g_pd3dDevice, L"Textures//Other//acropolis_sky.JPG", &Static_Objects[9].Textures[0]);
		D3DXCreateTextureFromFile(g_pd3dDevice, L"Textures//Other//greyBricks-lighter-512x512.JPG", &Static_Objects[10].Textures[0]);
		D3DXCreateTextureFromFile(g_pd3dDevice, L"Textures//Other//acropolis.JPG", &Static_Objects[11].Textures[0]);
		

		return S_OK;
										}
	
	return E_FAIL;
}

MainWindow::MainWindow(DWORD width, DWORD height):windowWidth(width>0?width:DEFAULT_WINDOW_WIDTH),windowHeight(height>0 ? height : DEFAULT_WINDOW_HEIGHT)
{
	Static_Objects = NULL;

	g_pD3D = NULL; // Used to create the D3DDevice
	g_pd3dDevice = NULL; // Our rendering device
	g_pVB = NULL; // Buffer to hold vertices

	MyText = NULL;
}

//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
VOID WINAPI MainWindow::Create_Window_object()
{

    // Register the window class
    wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
				LoadResource(NULL,ID_APPLICATION_MENU_NAME), NULL
    };
    RegisterClassEx( &wc );
    // Create the application's window
    hWnd = CreateWindow(ID_APPLICATION_MENU_NAME, ID_APPLICATION_NAME,
                              WS_OVERLAPPEDWINDOW, 0, 0, windowWidth, windowHeight,
                              NULL, NULL, wc.hInstance, NULL );
}

HRESULT WINAPI MainWindow::Initial_D3D9()
{
	// Initialize Direct3D
	if (SUCCEEDED(InitD3D()))

		// Create the vertex buffer
		//		if (SUCCEEDED(InitVB()))
		return S_OK;
	else
		return E_FAIL;
}

VOID WINAPI Create_D3D9::Start_Main_Loop(MainWindow &Game_Window)
{
	MessageBox(Game_Window.hWnd, L"Please,wait,while opening Texture.\r\n This Box must be close for staring.", 0, 0);
	if (SUCCEEDED(Game_Window.Initialization_static_object()))
	{
		// Show the window
		ShowWindow(Game_Window.hWnd, SW_SHOWDEFAULT);
		UpdateWindow(Game_Window.hWnd);

		Create_D3D9::SetupMatrices(Game_Window);
		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				Create_D3D9::Render(Game_Window);
		}
	}

	UnregisterClass(L"Gauntry_Game", Game_Window.wc.hInstance);
}

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	MainWindow Game_Window(1024,768);
	Game_Window.Create_Window_object();

	if (SUCCEEDED(Game_Window.Initial_D3D9()))
			Create_D3D9::Start_Main_Loop(Game_Window);

	return S_OK;
}
