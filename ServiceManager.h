#pragma once
#include "stdafx.h"

class DirectX;
class ServiceManager
{
public:
	static void provide(DirectX* directX);
	static DirectX& getDirectX();
private:
	static DirectX* directX_;
};
