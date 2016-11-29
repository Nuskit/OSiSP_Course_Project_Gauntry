#pragma once
#include "stdafx.h"

class Camera
{
public:
	enum CameraType { LANDOBJECT, AIRCRAFT };
	LPD3DXMATRIX V;

	Camera();
	Camera(CameraType cameraType);
	~Camera();
	void strafe(float units); // влево/вправо
	void fly(float units); // вверх/вниз
	void walk(float units); // вперед/назад
	void pitch(float angle); // вращение относительно
													 // правого вектора
	void yaw(float angle); // вращение относительно
												 // верхнего вектора
	void roll(float angle); // вращение относительно
													// вектора взгляда
	void getViewMatrix();
	void setViewMatrix();
	void setCameraType(CameraType cameraType);
	void getPosition(D3DXVECTOR3* pos);
	void setPosition(D3DXVECTOR3* pos);
	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);
private:
	CameraType _cameraType;
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;
};
