#include "stdafx.h"
#include "Camera.h"
#include "Game.h"
Camera::Camera()
{
	view = GetViewMatrix();
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(60),
		(float)640 / 480, //ancho der la pantalla dividido por el alto
		0.1f, //Distancia minima de vision
		500); //Distancia maxima de vision
}
Camera::~Camera()
{
}
void Camera::CreateViewMatrix(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	D3DXQUATERNION rotationQuaternion;
	D3DXMatrixTransformation(&view, NULL, NULL, NULL, NULL, D3DXQuaternionRotationYawPitchRoll(&rotationQuaternion, D3DXToRadian(GetRotation().x), D3DXToRadian(GetRotation().y), D3DXToRadian(GetRotation().z)), &GetPosition());
	D3DXMatrixInverse(&view, NULL, &view);
}
D3DXMATRIX Camera::GetViewMatrix()
{
	return view;
}

D3DXMATRIX Camera::GetProjection()
{
	return projection;
}

vector<D3DXPLANE> Camera::GetFructrumVector()
{
	D3DXMATRIX viewProjection;
	D3DXMatrixMultiply(&viewProjection, &view, &projection);
	vector<D3DXPLANE> fructrumVector(6);

	//Plano izquierdo
	fructrumVector[0].a = viewProjection._11 + viewProjection._14;
	fructrumVector[0].b = viewProjection._21 + viewProjection._24;
	fructrumVector[0].c = viewProjection._31 + viewProjection._34;
	fructrumVector[0].d = viewProjection._41 + viewProjection._44;

	// Plano derecho
	fructrumVector[1].a = viewProjection._14 - viewProjection._11;
	fructrumVector[1].b = viewProjection._24 - viewProjection._21;
	fructrumVector[1].c = viewProjection._34 - viewProjection._31;
	fructrumVector[1].d = viewProjection._44 - viewProjection._41;

	// Top
	fructrumVector[2].a = viewProjection._14 - viewProjection._12;
	fructrumVector[2].b = viewProjection._24 - viewProjection._22;
	fructrumVector[2].c = viewProjection._34 - viewProjection._32;
	fructrumVector[2].d = viewProjection._44 - viewProjection._42;

	// Bottom
	fructrumVector[3].a = viewProjection._14 + viewProjection._12;
	fructrumVector[3].b = viewProjection._24 + viewProjection._22;
	fructrumVector[3].c = viewProjection._34 + viewProjection._32;
	fructrumVector[3].d = viewProjection._44 + viewProjection._42;

	// Near
	fructrumVector[4].a = viewProjection._14 + viewProjection._13;
	fructrumVector[4].b = viewProjection._24 + viewProjection._23;
	fructrumVector[4].c = viewProjection._34 + viewProjection._33;
	fructrumVector[4].d = viewProjection._44 + viewProjection._43;

	// Far
	fructrumVector[5].a = viewProjection._14 - viewProjection._13;
	fructrumVector[5].b = viewProjection._24 - viewProjection._23;
	fructrumVector[5].c = viewProjection._34 - viewProjection._33;
	fructrumVector[5].d = viewProjection._44 - viewProjection._43;

	for (int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(&fructrumVector[i], &fructrumVector[i]);
	}
	return fructrumVector;
}
void Camera::Move(D3DXVECTOR3 trasl, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//Component::Move(trasl, escal, rot);
	Component::SetModelPosition(trasl.x, trasl.y, trasl.z);
	Component::SetModelRotation(rot.x, rot.y, rot.z);
	Component::SetModelScale(scale.x, scale.y, scale.z);
	D3DXQUATERNION rotationQuaternion;
	D3DXMatrixTransformation(&_transformationMatrix, NULL, NULL, &scale, NULL, D3DXQuaternionRotationYawPitchRoll(&rotationQuaternion, D3DXToRadian(rot.x), D3DXToRadian(rot.y), D3DXToRadian(rot.z)), &trasl);
}
void Camera::Update()
{
	Game* s = Game::getInstance();
	CreateViewMatrix(
		GetPosition(),
		GetRotation());
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(60),
		(float)640 / 480, //ancho de la pantalla dividido por el alto
		0.1f, //Distancia minima de vision
		1000); //Distancia maxima de vision
	view = GetViewMatrix();
	s->GetDevice()->SetTransform(D3DTS_VIEW, &view);
	s->GetDevice()->SetTransform(D3DTS_PROJECTION, &projection);
}