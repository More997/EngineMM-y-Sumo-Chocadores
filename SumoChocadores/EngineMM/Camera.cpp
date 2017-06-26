#include "stdafx.h"
#include "Camera.h"
Camera::Camera()
{
	_pos = D3DXVECTOR3(0, 0, 0);
	_rot = D3DXVECTOR3(0, 0, 0);
}

Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	_pos = pos;
	_rot = rot;
}

Camera::~Camera()
{
}

void Camera::SetPos(D3DXVECTOR3 pos)
{
	_pos = pos;
}

void Camera::SetRot(D3DXVECTOR3 rot)
{
	_rot = rot;
}

D3DXVECTOR3 Camera::GetPos()
{
	return _pos;
}

D3DXVECTOR3 Camera::GetRot()
{
	return _rot;
}

D3DXMATRIX Camera::GetViewMatrix()
{
	D3DXMATRIX transMat;
	D3DXMatrixIdentity(&transMat);
	transMat._41 = -_pos.x;
	transMat._42 = -_pos.y;
	transMat._43 = -_pos.z;
	D3DXMATRIX rotZMat;
	D3DXMatrixIdentity(&rotZMat);
	rotZMat._11 = cos(-_rot.z);
	rotZMat._12 = sin(-_rot.z);
	rotZMat._21 = -sin(-_rot.z);
	rotZMat._22 = cos(-_rot.z);

	return transMat * rotZMat;
}

void Camera::update(LPDIRECT3DDEVICE9 dev)
{
	D3DXMATRIX view = GetViewMatrix(/*
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0)*/);
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(60),
		(float)640 / 480, //ancho der la pantalla dividido por el alto
		0.0f, //Distancia minima de vision
		50); //Distancia maxima de vision

	dev->SetTransform(D3DTS_VIEW, &view);
	dev->SetTransform(D3DTS_PROJECTION, &projection);
}

