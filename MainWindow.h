#pragma once
#include "stdafx.h"
#include "WindowInfromation.h"

//class Create_D3D9
//{
//public:
//	static VOID Render(MainWindow &);
//	static VOID WINAPI Start_Main_Loop(MainWindow &);
//	static VOID SetupMatrices(MainWindow &);
//};

class MainWindow: public WindowInformation
{
public:
	MainWindow(DWORD width, DWORD height);
	~MainWindow();
	bool workWindowLoop();
	void initWindowLoop();
	virtual HWND getHWND() override;
	virtual const DWORD getWidth() override;
	virtual const DWORD getHeight() override;
	virtual void changeState(UILoopState * uiState) override;
private:
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND createWindowObject();
	DWORD windowWidth;
	DWORD windowHeight;
	HWND hWnd;
	WNDCLASSEX wc;
	//
//	ID3DXFont* MyText;
//
//
//	HRESULT InitD3D();
//	
//	HRESULT InitVB();
//
//	friend VOID WINAPI Create_D3D9::Start_Main_Loop(MainWindow &);
//	friend 	VOID Create_D3D9::Render(MainWindow &);
//	friend 	VOID Create_D3D9::SetupMatrices(MainWindow &);
//	
//
//	VOID createWindowObject();
//	const HRESULT initDirectX();
//public:
//	HRESULT WINAPI Initialization_static_object();
//
//	MainWindow(DWORD width, DWORD height);
//	~MainWindow();
//
//	const HRESULT initApplication();
};
