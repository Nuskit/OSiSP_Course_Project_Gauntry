#pragma once
#include "stdafx.h"

class GameObject;
class World
{
public:
	void addObject(GameObject* gameObject);
	void removeObject(GameObject* gameObject);
	void update();
	void render(double lagTime);
private:
	std::list<GameObject*> gameObjects;
};