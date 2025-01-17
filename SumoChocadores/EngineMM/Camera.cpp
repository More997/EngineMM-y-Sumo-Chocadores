#include "stdafx.h"
#include "Camera.h"
#include <vector>
Camera::Camera():radian(60),ancho (640), alto (480), dismin (0.1f), dismax(500)
{
	_pos = D3DXVECTOR3(0, 0, 0);
	_rot = D3DXVECTOR3(0, 0, 0);
	view = GetViewMatrix();
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(radian),
		(float)ancho / alto, //ancho de la pantalla dividido por el alto
		dismin, //Distancia minima de vision
		dismax); //Distancia maxima de vision
}

void Camera::CreateViewMatrix(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	D3DXQUATERNION rotationQuaternion;
	D3DXMatrixTransformation(&view, NULL, NULL, NULL, NULL, D3DXQuaternionRotationYawPitchRoll(&rotationQuaternion, D3DXToRadian(getRotationV().x), D3DXToRadian(getRotationV().y), D3DXToRadian(getRotationV().z)), &getVectorTrans());
	D3DXMatrixInverse(&view, NULL, &view);
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

D3DXVECTOR3 Camera::GetPos() const
{
	return _pos;
}

D3DXVECTOR3 Camera::GetRot() const
{
	return _rot;
}

D3DXMATRIX Camera::GetViewMatrix() const
{
	/*D3DXMATRIX transMat;
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
	*/
	return view;
}
D3DXMATRIX Camera::GetProjection()
{
	return projection;
}
void Camera::Move(D3DXVECTOR3 traslv, D3DXVECTOR3 scalev, D3DXVECTOR3 rotv)
{
	Component::setModelPos(traslv.x, traslv.y, traslv.z);
	Component::setModelRotX(rotv.x);
	Component::setModelRotY(rotv.y);
	Component::setModelRotZ(rotv.z);
	Component::setModelScale(scalev.x, scalev.y, scalev.z);
	D3DXQUATERNION rotationQuaternion;
	D3DXMatrixTransformation(&matFinal, NULL, NULL, &scalev, NULL, D3DXQuaternionRotationYawPitchRoll(&rotationQuaternion, D3DXToRadian(rotv.x), D3DXToRadian(rotv.y), D3DXToRadian(rotv.z)), &traslv);
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
	Game* s = Game::getInstance();
	CreateViewMatrix(
		getVector(),
		getRotationV());
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(60),
		(float)640 / 480, //ancho de la pantalla dividido por el alto
		0.1f, //Distancia minima de vision
		1000); //Distancia maxima de vision
	view = GetViewMatrix();
	s->getDev()->SetTransform(D3DTS_VIEW, &view);
	s->getDev()->SetTransform(D3DTS_PROJECTION, &projection);
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
		(float)ancho / alto, //ancho de la pantalla dividido por el alto
		dismin, //Distancia minima de vision
		dismax); //Distancia maxima de vision
}

D3DMATRIX Camera::getProjection() const
{
	return projection;
}
vector<D3DXPLANE> Camera::BuildViewFrustum() 
{
	D3DXMatrixMultiply(&_projection_view, &view, &projection);
	vector<D3DXPLANE> m_Frustum(6);
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
	return m_Frustum;
}

