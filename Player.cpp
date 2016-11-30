#include "stdafx.h"
#include "Player.h"
#include "Camera.h"
#include "ServiceManager.h"
#include "CameraController.h"
#include "DirectX.h"
#include "ShortcutController.h"

Player::Player():camera_(new Camera())
{

}

Player::~Player()
{
	delete camera_;
}

void Player::renderCustom()
{
	camera_->getViewMatrix();
	getServiceManager().getDirectX().setViewTransform(*(camera_->V));
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
		}
}
