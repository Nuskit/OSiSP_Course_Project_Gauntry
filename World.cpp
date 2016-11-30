#include "stdafx.h"
#include "World.h"
#include "CameraController.h"
#include "ShortcutController.h"
#include "Player.h"
#include "ServiceManager.h"
#include "LoadStringFromResource.h"
#include "Terrain.h"
#include "TexturedGameObject.h"
#include "GameSkyBox.h"

#define SCALE_SKYBOX 8.f

World::World()
{
	terrain = new Terrain((char*)(LPCSTR)(LoadStringFromResourceA(ID_TERRAIN_GENERAL)), 64, 64, 16, 1.0f);
	D3DXVECTOR3 lightDirection = D3DXVECTOR3(1.f, 1.f, 1.f);
	terrain->genTexture(&lightDirection);
	getServiceManager().provide(new CameraController());
	getServiceManager().provide(new ShortcutController());
	addObject(new Player());
	//addObject(createChair());
	//addObject(createArcopolis());
	createSkyBox();
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
	terrain->draw(&I, true);
}

GameObject* World::createChair()
{
	return new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_CHAIR), LoadStringFromResourceA(IDS_TEXTURE_CHAIR_FOLDER));
}

void World::createSkyBox()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_SKYBOX), LoadStringFromResourceA(IDS_TEXTURE_SKYBOX_FOLDER));
	gameObject->loadExtraTextures(0, LoadStringFromResourceW(IDS_TEXTURE_SKYBOX_EXTRA));
	gameObject->setMaterialEmissive(0, D3DCOLORVALUE{ 0.9f,0.9f,0.9f,0.0f });
	addObject(new SkyBox(D3DXVECTOR3(SCALE_SKYBOX, SCALE_SKYBOX, SCALE_SKYBOX), D3DXVECTOR3(0.f, 0.f, 0.f), 
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
	addObject(new SkyBox(D3DXVECTOR3(SCALE_SKYBOX, SCALE_SKYBOX, SCALE_SKYBOX), D3DXVECTOR3(0.f, 0.f, 0.f), 
		D3DXVECTOR3(0.f, 0.f, 0.f), gameObject));
}

GameObject* World::createArcopolis()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_ACROPOLIS), LoadStringFromResourceA(IDS_TEXTURE_ACROPOLIS_FOLDER));
	gameObject->loadExtraTextures(0, LoadStringFromResourceW(IDS_TEXTURE_ACROPOLIS_EXTRA));
	return gameObject;
}
