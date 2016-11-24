#pragma once

#include "stdafx.h"
#include "Global_Effect.h"
#include "Direct_Operations.h"

class MainWindow;

class Create_D3D9
{
public:
	static VOID Render(MainWindow &);
	static VOID WINAPI Start_Main_Loop(MainWindow &);
	static VOID SetupMatrices(MainWindow &);
};

enum
{
	DEFAULT_WINDOW_WIDTH=1024,
	DEFAULT_WINDOW_HEIGHT=768
};

class MainWindow
{
private:
	ObjectFromX *Static_Objects;

	DWORD windowWidth;
	DWORD windowHeight;
	HWND hWnd;
	WNDCLASSEX wc;

	ID3DXFont* MyText;


	HRESULT InitD3D();
	
	HRESULT InitVB();

	friend VOID WINAPI Create_D3D9::Start_Main_Loop(MainWindow &);
	friend 	VOID Create_D3D9::Render(MainWindow &);
	friend 	VOID Create_D3D9::SetupMatrices(MainWindow &);
	
public:
	HRESULT WINAPI Initialization_static_object();

	MainWindow(DWORD width, DWORD height);
	~MainWindow();

	VOID WINAPI Create_Window_object();
	HRESULT WINAPI Initial_D3D9();
};







