#pragma once
#include "stdafx.h"

class GameObject;
class TexturedGameObject;
class Terrain;
class World
{
public:
	World();
	~World();
	void addObject(GameObject* gameObject);
	void removeObject(GameObject* gameObject);
	void update();
	void render(double lagTime);
private:
	std::list<GameObject*> gameObjects;
	std::vector<TexturedGameObject*> texturedObjects;
	Terrain *terrain;

	//TODO: insert in module entities
private:
	void createChair();
	void createSkyBox();
	void createArcopolis();
	void createAcropolisGround();
	void createDwarf();
	void createNlo();
	void createCar();
	void createEvilDrone();
	void createGyro();
	void createAttackedGyro();
	void createAirplane();
	void createSatellite();
	D3DXVECTOR3 lightDirection;
	float lightTimer;
};
