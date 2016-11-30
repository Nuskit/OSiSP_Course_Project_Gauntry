#pragma once
#include "stdafx.h"

#define MOVE_DELTA 10.0f
#define MOUSE_SENSITIVITY 0.1f

class GameObject
{
public:
	GameObject(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent = nullptr);
	GameObject(D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent = nullptr);
	GameObject(D3DXVECTOR3 view, GameObject* parent = nullptr);
	GameObject(GameObject* parent = nullptr);
	virtual ~GameObject();
	D3DXMATRIX getPosition();
	void setPosition(const D3DXMATRIX& newPosition);
	void updatePosition(const D3DXMATRIX& positionMatrix);
	D3DXMATRIX getScale();
	void setScale(const D3DXMATRIX& newScale);
	void updateScale(const D3DXMATRIX& scaleMatrix);
	D3DXMATRIX getView();
	void setView(const D3DXMATRIX& newView);
	void updateView(const D3DXMATRIX& viewMatrix);

	void update();
	void render(double lagTime);
	void addChildObject(GameObject& childObject);
	void removeChildObject(GameObject& childObject);
public:
	virtual void renderCustom(double lagTime) = 0;
	virtual void updateCustom() = 0;
private:
	void setObjectPosition();

	D3DXMATRIX scaleMatrix_;
	D3DXMATRIX positionMatrix_;
	D3DXMATRIX viewMatrix_;
	std::list<GameObject*> childGameObjects;
	GameObject* parent_;
};
