#include "stdafx.h"
#include "ServiceManager.h"
#include "UILoopNull.h"

#include "DirectX.h"
#include "WindowInfromation.h"
#include "World.h"

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

ServiceManager::~ServiceManager()
{
	delete directX_;
	delete windowInformation_;
	delete world_;
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

void ServiceManager::provide(CameraController * camera)
{
	cameraController_ = camera;
}

void ServiceManager::provide(ShortcutController * shortcutController)
{
	shortcutController_ = shortcutController;
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

CameraController & ServiceManager::getCameraController()
{
	assert(cameraController_ != nullptr);
	return *cameraController_;
}

ShortcutController & ServiceManager::getShortcutController()
{
	assert(shortcutController_ != nullptr);
	return *shortcutController_;
}

ServiceManager::ServiceManager() :directX_(nullptr), windowInformation_(nullptr), uiState_(&uiStateNull), world_(nullptr),
cameraController_(nullptr), shortcutController_(nullptr)
{
}
