#include "stdafx.h"
#include "ServiceManager.h"
#include <stdexcept>

DirectX* ServiceManager::directX_ = nullptr;

void ServiceManager::provide(DirectX * directX)
{
	directX_ = directX;
}

DirectX& ServiceManager::getDirectX()
{
	if (directX_ == NULL)
		throw std::runtime_error("Don't found directX");
	return *directX_;
}
