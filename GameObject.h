#pragma once
#include "stdafx.h"

#define MOVE_DELTA 0.5f
#define MOUSE_SENSITIVITY 0.05f

class GameObject
{
public:
	GameObject(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent = nullptr);
	GameObject(D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent = nullptr);
	GameObject(D3DXVECTOR3 view, GameObject* parent = nullptr);
	GameObject(GameObject* parent = nullptr);
	virtual ~GameObject();
	D3DXVECTOR3 getPosition();
	void setPosition(const D3DXVECTOR3& newPosition);
	D3DXVECTOR3 getScale();
	void setScale(const D3DXVECTOR3& newScale);
	D3DXVECTOR3 getView();
	void setView(const D3DXVECTOR3& newView);

	void update();
	void render(double lagTime);
	void addChildObject(GameObject& childObject);
	void removeChildObject(GameObject& childObject);
protected:
	virtual void renderCustom() = 0;
	virtual void updateCustom() = 0;
private:
	D3DXMATRIX scaleObject();
	D3DXMATRIX moveObject();
	D3DXMATRIX viewObject();
	void setObjectPosition();

	D3DXVECTOR3 scale_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 view_;
	std::list<GameObject*> childGameObjects;
	GameObject* parent_;
};
