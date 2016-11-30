#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Camera;
class Player :public GameObject
{
public:
	Player();
	~Player();
protected:
	virtual void renderCustom(double lagTime) override;
	virtual void updateCustom() override;
private:
	Camera* camera_;
};
