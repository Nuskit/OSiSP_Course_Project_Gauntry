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
	void strafe(float units); // �����/������
	void fly(float units); // �����/����
	void walk(float units); // ������/�����
	void pitch(float angle); // �������� ������������
													 // ������� �������
	void yaw(float angle); // �������� ������������
												 // �������� �������
	void roll(float angle); // �������� ������������
													// ������� �������
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
