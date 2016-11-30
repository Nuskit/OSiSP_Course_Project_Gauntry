#pragma once
#include "stdafx.h"

class DirectX;
class WindowInformation;
class UILoopState;
class UILoopNull;
class World;
class ServiceManager
{
public:
	static ServiceManager& getInstance();
	void provide(DirectX* directX);
	void provide(WindowInformation* windowInformation);
	void provide(UILoopState* uiState);
	void provide(World *world);
	DirectX& getDirectX();
	WindowInformation& getWindowInformation();
	UILoopState& getUIState();
	World& getWorld();
private:
	ServiceManager();
	ServiceManager(const ServiceManager&);
	DirectX* directX_;
	WindowInformation* windowInformation_;
	UILoopState* uiState_;
	static UILoopNull uiStateNull;
	World* world_;
};

ServiceManager& getServiceManager();
