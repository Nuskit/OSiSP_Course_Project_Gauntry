#pragma once
#include "stdafx.h"

class DirectX;
class WindowInformation;
class UILoopState;
class UILoopNull;
class ServiceManager
{
public:
	static ServiceManager& getInstance();
	void provide(DirectX* directX);
	void provide(WindowInformation* windowInformation);
	void provide(UILoopState* uiState);
	DirectX& getDirectX();
	WindowInformation& getWindowInformation();
	UILoopState& getUIState();
private:
	ServiceManager();
	ServiceManager(const ServiceManager&);
	DirectX* directX_;
	WindowInformation* windowInformation_;
	UILoopState* uiState_;
	static UILoopNull uiStateNull;
};

ServiceManager& getServiceManager();
