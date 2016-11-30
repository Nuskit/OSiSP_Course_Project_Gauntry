#include "stdafx.h"
#include "World.h"
#include "GameObject.h"

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
	for (auto gameObject : gameObjects)
		gameObject->render(lagTime);
}
