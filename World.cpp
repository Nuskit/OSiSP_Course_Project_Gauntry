#include "stdafx.h"
#include "World.h"
#include "GameObject.h"
#include "CameraController.h"
#include "ShortcutController.h"
#include "Player.h"
#include "ServiceManager.h"
#include "LoadStringFromResource.h"
#include "Terrain.h"

World::World()
{
	terrain = new Terrain((char*)(LPCSTR)(LoadStringFromResourceA(ID_TERRAIN_GENERAL)), 64, 64, 310, 1.0f);
	D3DXVECTOR3 lightDirection = D3DXVECTOR3(1.f, 1.f, 1.f);
	terrain->genTexture(&lightDirection);
	getServiceManager().provide(new CameraController());
	getServiceManager().provide(new ShortcutController());
	addObject(new Player());
}

World::~World()
{
	for (auto object: gameObjects)
		delete object;
	delete &getServiceManager().getCameraController();
	delete &getServiceManager().getShortcutController();
	delete terrain;
}

void World::addObject(GameObject* gameObject)
{
	assert(gameObject != nullptr);
	gameObjects.push_back(gameObject);
}

void World::removeObject(GameObject* gameObject)
{
	assert(gameObject != nullptr);
	gameObjects.remove(gameObject);
}

void World::update()
{
	for (auto gameObject : gameObjects)
		gameObject->update();
}

void World::render(double lagTime)
{
	static D3DXMATRIX I = { 
		1, 0, 0, 0, 
		0, 1, 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1 
	};
	for (auto gameObject : gameObjects)
		gameObject->render(lagTime);
	terrain->draw(&I, false);
}
