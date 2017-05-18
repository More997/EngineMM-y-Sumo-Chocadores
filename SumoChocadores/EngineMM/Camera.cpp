#include "stdafx.h"
#include "Camera.h"

D3DXMATRIX GetViewMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXMATRIX transMat;
	D3DXMatrixIdentity(&transMat);
	transMat._41 = -pos.x;
	transMat._42 = -pos.y;
	transMat._43 = -pos.z;

	D3DXMATRIX rotZMat;
	D3DXMatrixIdentity(&rotZMat);
	rotZMat._11 = cos(-rot.z);
	rotZMat._12 = sin(-rot.z);
	rotZMat._21 = -sin(-rot.z);
	rotZMat._22 = cos(-rot.z);

	return transMat * rotZMat;
};
Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::createCamera(LPDIRECT3DDEVICE9 dev, D3DXMATRIX _trasl,	D3DXMATRIX _rotation)
{
	//Camara
	D3DXMATRIX view = GetViewMatrix(
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0));
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(60),
		(float)640 / 480, //ancho der la pantalla dividido por el alto
		0.0f, //Distancia minima de vision
		50); //Distancia maxima de vision

	dev->SetTransform(D3DTS_VIEW, &view);
	dev->SetTransform(D3DTS_PROJECTION, &projection);

	dev->Clear(0, NULL, D3DCLEAR_TARGET, /*D3DCOLOR_XRGB(255, 0, 0)*/ D3DCOLOR_ARGB(0, 100, 0, 100), 1.0f, 0);
	dev->BeginScene();
}
