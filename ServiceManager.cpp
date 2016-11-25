#include "stdafx.h"
#include "ServiceManager.h"
#include <stdexcept>

DirectX* ServiceManager::directX_ = nullptr;
WindowInformation* ServiceManager::windowInformation_ = nullptr;

void ServiceManager::provide(DirectX * directX)
{
	directX_ = directX;
}

void ServiceManager::provide(WindowInformation * windowInformation)
{
	windowInformation_ = windowInformation;
}

DirectX& ServiceManager::getDirectX()
{
	if (directX_ == NULL)
		throw std::runtime_error("Don't found directX");
	return *directX_;
}

WindowInformation& ServiceManager::getWindowInformation()
{
	if (windowInformation_ == NULL)
		throw std::runtime_error("Don't found windowInformation");
	return *windowInformation_;
}
