#include "stdafx.h"
#include "Camera.h"
Camera::Camera():radian(60),ancho (640), alto (480), dismin (0.0f), dismax(50)
{
	_pos = D3DXVECTOR3(0, 0, 0);
	_rot = D3DXVECTOR3(0, 0, 0);
	view = GetViewMatrix();
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(radian),
		(float)ancho / alto, //ancho der la pantalla dividido por el alto
		dismin, //Distancia minima de vision
		dismax); //Distancia maxima de vision
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
/*
Mover el D3DXMATRIX projection en el .h. --Listo
Mover al D3DXMATRIX view al .h. view = GetViewMatrix() asi el BuildViewFrustum tiene acceso. --Listo.
Mover el D3DXMatrixPespectiveFovLH(...) al constructor. --Listo
Crear una funcion que modifique al D 3DXMatrixPespectiveFovLH(...) cuando el usuario quiera. --Listo
Crear el BuildViewFrustum en la camera, asi tiene acceso al D3DXMATRIX projection. --Listo
*/
void Camera::update()
{
	Game* g = Game::getInstance();
	view = GetViewMatrix();	
	g->getDev()->SetTransform(D3DTS_VIEW, &view);
	g->getDev()->SetTransform(D3DTS_PROJECTION, &projection);
}

void Camera::setSize(int _radian, int _ancho, int _alto, float _dismin, float _dismax)
{
	radian = _radian;
	ancho = _ancho;
	alto = _alto;
	dismin = _dismin;
	dismax = _dismax;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(radian),
		(float)ancho / alto, //ancho der la pantalla dividido por el alto
		dismin, //Distancia minima de vision
		dismax); //Distancia maxima de vision
}

D3DMATRIX Camera::getProjection()
{
	return projection;
}
void Camera::BuildViewFrustum()
{
	D3DXMatrixMultiply(&_projection_view, &view, &projection);
	//LeftPlane
	m_Frustum[0].a = _projection_view._14 + _projection_view._11;
	m_Frustum[0].b = _projection_view._24 + _projection_view._21;
	m_Frustum[0].c = _projection_view._34 + _projection_view._31;
	m_Frustum[0].d = _projection_view._44 + _projection_view._41;

	//RightPlane
	m_Frustum[1].a = _projection_view._14 - _projection_view._11;
	m_Frustum[1].b = _projection_view._24 - _projection_view._21;
	m_Frustum[1].c = _projection_view._34 - _projection_view._31;
	m_Frustum[1].d = _projection_view._44 - _projection_view._41;

	// TopPlane
	m_Frustum[2].a = _projection_view._14 - _projection_view._12;
	m_Frustum[2].b = _projection_view._24 - _projection_view._22;
	m_Frustum[2].c = _projection_view._34 - _projection_view._32;
	m_Frustum[2].d = _projection_view._44 - _projection_view._42;

	// BottomPlane
	m_Frustum[3].a = _projection_view._14 + _projection_view._12;
	m_Frustum[3].b = _projection_view._24 + _projection_view._22;
	m_Frustum[3].c = _projection_view._34 + _projection_view._32;
	m_Frustum[3].d = _projection_view._44 + _projection_view._42;

	// NearPlane
	m_Frustum[4].a = _projection_view._13;
	m_Frustum[4].b = _projection_view._23;
	m_Frustum[4].c = _projection_view._33;
	m_Frustum[4].d = _projection_view._43;

	// FarPlane
	m_Frustum[5].a = _projection_view._14 - _projection_view._13;
	m_Frustum[5].b = _projection_view._24 - _projection_view._23;
	m_Frustum[5].c = _projection_view._34 - _projection_view._33;
	m_Frustum[5].d = _projection_view._44 - _projection_view._43;

	for (int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(&m_Frustum[i], &m_Frustum[i]);
	}
}

