#pragma once
#include "stdafx.h"

class DirectX;
class WindowInformation;
class UILoopState;
class UILoopNull;
class World;
class CameraController;
class ShortcutController;
class ServiceManager
{
public:
	static ServiceManager& getInstance();
	~ServiceManager();
	void provide(DirectX* directX);
	void provide(WindowInformation* windowInformation);
	void provide(UILoopState* uiState);
	void provide(World *world);
	void provide(CameraController* camera);
	void provide(ShortcutController* shortcutController);
	DirectX& getDirectX();
	WindowInformation& getWindowInformation();
	UILoopState& getUIState();
	World& getWorld();
	CameraController& getCameraController();
	ShortcutController& getShortcutController();
private:
	ServiceManager();
	ServiceManager(const ServiceManager&);
	DirectX* directX_;
	WindowInformation* windowInformation_;
	UILoopState* uiState_;
	static UILoopNull uiStateNull;
	World* world_;
	CameraController* cameraController_;
	ShortcutController* shortcutController_;
};

ServiceManager& getServiceManager();
