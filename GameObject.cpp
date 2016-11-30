#include "stdafx.h"
#include "GameObject.h"
#include "ServiceManager.h"
#include "DirectX.h"

GameObject::GameObject(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, GameObject* parent) :
	scale_(scale), position_(position), view_(view), parent_(parent)
{
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

D3DXVECTOR3 GameObject::getPosition()
{
	return position_;
}

void GameObject::setPosition(const D3DXVECTOR3 & newPosition)
{
	position_ = newPosition;
}

D3DXVECTOR3 GameObject::getScale()
{
	return scale_;
}

void GameObject::setScale(const D3DXVECTOR3 & newScale)
{
	scale_ = newScale;
}

D3DXVECTOR3 GameObject::getView()
{
	return view_;
}

void GameObject::setView(const D3DXVECTOR3 & newView)
{
	view_ = newView;
}

void GameObject::update()
{
}

void GameObject::render(double lagTime)
{
	setObjectPosition();
	renderCustom();
}

void GameObject::setObjectPosition()
{
	getServiceManager().getDirectX().setWorldTransform(scaleObject()*moveObject()*viewObject());
}

void GameObject::addChildObject(GameObject & childObject)
{
	childGameObjects.push_back(&childObject);
}

void GameObject::removeChildObject(GameObject & childObject)
{
	childGameObjects.remove(&childObject);
}

D3DXMATRIX GameObject::scaleObject()
{
	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, scale_.x, scale_.y, scale_.z);
	return scaleMatrix;
}

D3DXMATRIX GameObject::moveObject()
{
	D3DXMATRIX moveMatrix;
	D3DXMatrixTranslation(&moveMatrix, position_.x, position_.y, position_.z);
	return moveMatrix;
}

D3DXMATRIX GameObject::viewObject()
{
	D3DXMATRIX viewMatrix;
	D3DXMatrixRotationYawPitchRoll(&viewMatrix, view_.x, view_.y, view_.z);
	return viewMatrix;
}
