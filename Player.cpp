#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "ServiceManager.h"
#include "CameraController.h"
#include "DirectX.h"
#include "ShortcutController.h"
#include "d3dUtility.h"
#include "ServiceManager.h"
#include "DirectX.h"

Player::Player():camera_(new Camera())
{

}

Player::~Player()
{
	delete camera_;
}

void Player::renderCustom(double lagTime)
{
	camera_->getViewMatrix();
	getServiceManager().getDirectX().setViewTransform(*(camera_->V));
	
	static D3DXVECTOR3 look, position;
	camera_->getLook(&look);
	camera_->getPosition(&position);

	static D3DLIGHT9 flashLight = d3d::InitSpotLight(&position, &look, &D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	flashLight.Position = position;
	flashLight.Direction = look;
	flashLight.Range = 200;
	flashLight.Theta = 0.5;
	flashLight.Phi = 1;

	
	getServiceManager().getDirectX().setLight(2, flashLight);
	getServiceManager().getDirectX().enableLight(2, true);
}

void Player::updateCustom()
{
	POINT newView = getServiceManager().getCameraController().getPosition();
	getServiceManager().getCameraController().clearPosition();
	camera_->yaw(MOUSE_SENSITIVITY * newView.x);
	camera_->pitch(MOUSE_SENSITIVITY * newView.y);

	for (auto key:getServiceManager().getShortcutController().keys)
		switch (key)
		{
		case (0x57):
			camera_->walk(MOVE_DELTA);
			break;
		case (0x53):
			camera_->walk(-MOVE_DELTA);
			break;
		case (0x41):
			camera_->strafe(-MOVE_DELTA);
			break;
		case (0x44):
			camera_->strafe(MOVE_DELTA);
			break;
		case (VK_UP):
			camera_->pitch(MOUSE_SENSITIVITY);
			break;
		case (VK_DOWN):
			camera_->pitch(-MOUSE_SENSITIVITY);
			break;
		case (VK_LEFT):
			camera_->yaw(-MOUSE_SENSITIVITY);
			break;
		case (VK_RIGHT):
			camera_->yaw(MOUSE_SENSITIVITY);
			break;
		}
}
