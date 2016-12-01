#include "stdafx.h"
#include "GameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

GameObject::GameObject(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent) : parent_(parent)
{
	D3DXMatrixTranslation(&positionMatrix_, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMatrix_, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&viewMatrix_, view.x, view.y, view.z);
	if (parent)
		parent->addChildObject(*this);
}

GameObject::GameObject(D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent) :
	GameObject(D3DXVECTOR3(1., 1., 1.), position, view, parent)
{
}

GameObject::GameObject(D3DXVECTOR3 view, GameObject* parent) :
	GameObject(D3DXVECTOR3(0., 0., 0.), view, parent)
{
}

GameObject::GameObject(GameObject * parent) :
	GameObject(D3DXVECTOR3(1., 1., 1.), parent)
{
}

GameObject::~GameObject()
{
	if (parent_)
		parent_->removeChildObject(*this);
}

D3DXMATRIX GameObject::getPosition()
{
	return positionMatrix_;
}

void GameObject::setPosition(const D3DXMATRIX & newPosition)
{
	positionMatrix_ = newPosition;
}

D3DXMATRIX GameObject::getScale()
{
	return scaleMatrix_;
}

void GameObject::setScale(const D3DXMATRIX & newScale)
{
	scaleMatrix_ = newScale;
}

D3DXMATRIX GameObject::getView()
{
	return viewMatrix_;
}

void GameObject::setView(const D3DXMATRIX & newView)
{
	viewMatrix_ = newView;
}

void GameObject::update()
{
	updateCustom();
}

void GameObject::render(double lagTime)
{
	setObjectPosition();
	renderCustom(lagTime);
}

void GameObject::setObjectPosition()
{
	getServiceManager().getDirectX().setWorldTransform(getScale()*getView()*getPosition());
}

void GameObject::addChildObject(GameObject & childObject)
{
	childGameObjects.push_back(&childObject);
}

void GameObject::removeChildObject(GameObject & childObject)
{
	childGameObjects.remove(&childObject);
}

void GameObject::updateScale(const D3DXMATRIX& scaleMatrix)
{
	scaleMatrix_ *= scaleMatrix;
}

void GameObject::updatePosition(const D3DXMATRIX& positionMatrix)
{
	positionMatrix_ *= positionMatrix;
}

void GameObject::updateView(const D3DXMATRIX& viewMatrix)
{
	viewMatrix_ *= viewMatrix;
}
