#include "stdafx.h"
#include "ServiceManager.h"
#include "UILoopNull.h"

UILoopNull ServiceManager::uiStateNull;

ServiceManager& getServiceManager()
{
	return ServiceManager::getInstance();
}

ServiceManager& ServiceManager::getInstance()
{
	static ServiceManager serviceManager;
	return serviceManager;
}

void ServiceManager::provide(DirectX * directX)
{
	directX_ = directX;
}

void ServiceManager::provide(WindowInformation * windowInformation)
{
	windowInformation_ = windowInformation;
}

void ServiceManager::provide(UILoopState * uiState)
{
	uiState_ = (uiState == nullptr) ? &uiStateNull : uiState;
}

void ServiceManager::provide(World * world)
{
	world_ = world;
}

DirectX& ServiceManager::getDirectX()
{
	assert(directX_ != nullptr);
	return *directX_;
}

WindowInformation& ServiceManager::getWindowInformation()
{
	assert(windowInformation_ != nullptr);
	return *windowInformation_;
}

UILoopState& ServiceManager::getUIState()
{
	assert(uiState_ != nullptr);
	return *uiState_;
}

World & ServiceManager::getWorld()
{
	assert(world_ != nullptr);
	return *world_;
}

ServiceManager::ServiceManager() :directX_(nullptr), windowInformation_(nullptr), uiState_(&uiStateNull), world_(nullptr)
{
}
