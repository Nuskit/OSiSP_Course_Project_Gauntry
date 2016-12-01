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
#include "Acropolis.h"
#include "Chair.h"
#include "AcropolisGround.h"
#include "Airplane.h"
#include "Satellite.h"
#include "Dwarf.h"
#include "Gyro.h"
#include "AttackedGyro.h"
#include "Nlo.h"
#include "EvilDrone.h"
#include "Car.h"

#define SCALE_SKYBOX 8.f
#define SCALE_ACROPOLIS 6.f
#define LIGHT_TIMER 0.0005f
#define MAX_TIMER_VALUE 2*M_PI
#define SCALE_CHAIR 2.f
#define SCALE_ACROPOLIS_GROUND 1.f
#define SCALE_AIRPLANE 1.f
#define SCALE_SATELLITE 1.f
#define SCALE_DWARF 10.f
#define SCALE_NLO 1.f
#define SCALE_ATTACKED_GYRO 1.f
#define SCALE_GYRO 1.f
#define SCALE_EVIL_DRONE 1.f
#define SCALE_CAR 0.5f

World::World() :lightTimer(-M_PI)
{
	terrain = new Terrain((char*)(LPCSTR)(LoadStringFromResourceA(ID_TERRAIN_GENERAL)), 64, 64, 16, 1.0f);
	getServiceManager().provide(new CameraController());
	getServiceManager().provide(new ShortcutController());
	addObject(new Player());
	createArcopolis();
	createChair();
	createSkyBox();
	createAcropolisGround();
	createDwarf();
	createNlo();
	createCar();
	createEvilDrone();
	createGyro();
	createAttackedGyro();
	createAirplane();
	createSatellite();
}

World::~World()
{
	for (auto object : gameObjects)
		delete object;
	for (auto texture : texturedObjects)
		delete texture;
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
	lightTimer = ((lightTimer >= MAX_TIMER_VALUE) ? -MAX_TIMER_VALUE : lightTimer) + LIGHT_TIMER;
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

	lightDirection = D3DXVECTOR3(cosf(lightTimer), -0.5f + fabs(sinf(lightTimer)), sinf(lightTimer * 2));
	terrain->genTexture(&lightDirection);
	terrain->draw(&I, true);
}

void World::createChair()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_CHAIR), LoadStringFromResourceA(IDS_TEXTURE_CHAIR_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new Chair(D3DXVECTOR3(SCALE_CHAIR, SCALE_CHAIR, SCALE_CHAIR), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createSkyBox()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_SKYBOX), LoadStringFromResourceA(IDS_TEXTURE_SKYBOX_FOLDER));
	gameObject->loadExtraTextures(0, LoadStringFromResourceW(IDS_TEXTURE_SKYBOX_EXTRA));
	gameObject->setMaterialEmissive(0, D3DCOLORVALUE{ 0.9f,0.9f,0.9f,0.0f });
	texturedObjects.push_back(gameObject);
	addObject(new SkyBox(D3DXVECTOR3(SCALE_SKYBOX, SCALE_SKYBOX, SCALE_SKYBOX), D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
	addObject(new SkyBox(D3DXVECTOR3(SCALE_SKYBOX, SCALE_SKYBOX, SCALE_SKYBOX), D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(0.f, 0.f, 0.f), gameObject));
}

void World::createArcopolis()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_ACROPOLIS), LoadStringFromResourceA(IDS_TEXTURE_ACROPOLIS_FOLDER));
	gameObject->loadExtraTextures(0, LoadStringFromResourceW(IDS_TEXTURE_ACROPOLIS_EXTRA));
	texturedObjects.push_back(gameObject);
	addObject(new Acropolis(D3DXVECTOR3(SCALE_ACROPOLIS, SCALE_ACROPOLIS, SCALE_ACROPOLIS), D3DXVECTOR3(-350.0f, 5.0f, -350.0f),
		D3DXVECTOR3(M_PI_2, M_PI, 0.f), gameObject));
}

void World::createAcropolisGround()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_ACROPOLIS_GROUND), LoadStringFromResourceA(IDS_TEXTURE_ACROPOLIS_GROUND_FOLDER));
	gameObject->loadExtraTextures(0, LoadStringFromResourceW(IDS_TEXTURE_ACROPOLIS_GROUND_EXTRA));
	texturedObjects.push_back(gameObject);
	addObject(new AcropolisGround(D3DXVECTOR3(SCALE_ACROPOLIS_GROUND, SCALE_ACROPOLIS_GROUND, SCALE_ACROPOLIS_GROUND), D3DXVECTOR3(-300.0f, 4.f, -400.0f),
		D3DXVECTOR3(0.f, 0.f, 0.f), gameObject));
}

void World::createDwarf()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_DWARF), LoadStringFromResourceA(IDS_TEXTURE_DWARF_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new Dwarf(D3DXVECTOR3(SCALE_DWARF, SCALE_DWARF, SCALE_DWARF), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createNlo()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_NLO), LoadStringFromResourceA(IDS_TEXTURE_NLO_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new Nlo(D3DXVECTOR3(SCALE_NLO, SCALE_NLO, SCALE_NLO), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createCar()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_CAR), LoadStringFromResourceA(IDS_TEXTURE_CAR_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new Car(D3DXVECTOR3(SCALE_CAR, SCALE_CAR, SCALE_CAR), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createEvilDrone()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_EVIL_DRONE), LoadStringFromResourceA(IDS_TEXTURE_EVIL_DRONE_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new EvilDrone(D3DXVECTOR3(SCALE_EVIL_DRONE, SCALE_EVIL_DRONE, SCALE_EVIL_DRONE), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createGyro()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_GYRO), LoadStringFromResourceA(IDS_TEXTURE_GYRO_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new Gyro(D3DXVECTOR3(SCALE_GYRO, SCALE_GYRO, SCALE_GYRO), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createAttackedGyro()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_ATTACKED_GYRO), LoadStringFromResourceA(IDS_TEXTURE_ATTACKED_GYRO_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new AttackedGyro(D3DXVECTOR3(SCALE_ATTACKED_GYRO, SCALE_ATTACKED_GYRO, SCALE_ATTACKED_GYRO), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createAirplane()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_AIRPLANE), LoadStringFromResourceA(IDS_TEXTURE_AIRPLANE_FOLDER));
	addObject(new Airplane(D3DXVECTOR3(SCALE_AIRPLANE, SCALE_AIRPLANE, SCALE_AIRPLANE), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}

void World::createSatellite()
{
	TexturedGameObject* gameObject = new TexturedGameObject(LoadStringFromResourceW(IDS_TEXTURE_SATELLITE), LoadStringFromResourceA(IDS_TEXTURE_SATELLITE_FOLDER));
	texturedObjects.push_back(gameObject);
	addObject(new Satellite(D3DXVECTOR3(SCALE_SATELLITE, SCALE_SATELLITE, SCALE_SATELLITE), D3DXVECTOR3(-260.f, 0.f, -280.f),
		D3DXVECTOR3(0.f, M_PI, 0.f), gameObject));
}
