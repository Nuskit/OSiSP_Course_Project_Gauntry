#pragma once
#include "stdafx.h"

class GameObject;
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
	Terrain *terrain;

	//TODO: insert in module entities
private:
	GameObject* createChair();
	void createSkyBox();
	GameObject* createArcopolis();
};
