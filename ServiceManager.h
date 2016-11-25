#pragma once
#include "stdafx.h"

class DirectX;
class WindowInformation;
class ServiceManager
{
public:
	static void provide(DirectX* directX);
	static void provide(WindowInformation* windowInformation);
	static DirectX& getDirectX();
	static WindowInformation& getWindowInformation();
private:
	static DirectX* directX_;
	static WindowInformation* windowInformation_;
};
