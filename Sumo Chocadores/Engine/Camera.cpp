#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

D3DXMATRIX GetViewMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXMATRIX transMat;
	D3DXMatrixIdentity(&transMat);
	transMat._41 = -pos.x;
	transMat._42 = -pos.y;
	transMat._43 = -pos.z;

	D3DXMATRIX rotXMat;
	D3DXMatrixIdentity(&rotXMat);
	rotXMat._22 = cos(rot.x);
	rotXMat._23 = sin(rot.x);
	rotXMat._32 = -sin(rot.x);
	rotXMat._33 = cos(rot.x);

	D3DXMATRIX rotYMat;
	D3DXMatrixIdentity(&rotYMat);
	rotXMat._11 = cos(rot.y);
	rotXMat._13 = -sin(rot.y);
	rotXMat._31 = sin(rot.y);
	rotXMat._33 = cos(rot.y);

	D3DXMATRIX rotZMat;
	D3DXMatrixIdentity(&rotZMat);
	rotZMat._11 = cos(rot.z);
	rotZMat._12 = sin(rot.z);
	rotZMat._21 = -sin(rot.z);
	rotZMat._22 = cos(rot.z);


	return transMat * rotXMat * rotYMat * rotZMat;
};

void Camera::View(LPDIRECT3DDEVICE9 dev, float angleOfView, float width, float height, float minDistance, float maxDistance)
{
	//Opcion de camara Isométrica
	if (!isometricView)
	{
		viewMatrix = GetViewMatrix(
			D3DXVECTOR3(m_Transform->GetPos().x, m_Transform->GetPos().y, m_Transform->GetPos().z),
			D3DXVECTOR3(m_Transform->GetRot().x, m_Transform->GetRot().y, m_Transform->GetRot().z));

		D3DXMatrixPerspectiveFovLH(
			&projMatrix,
			D3DXToRadian(angleOfView), //El angulo de apertura de la camara
			(float)width / height, //El ancho de la pantalla dividido el alto (relación de aspect)
			minDistance, //La distancia minima del objeto para verse
			maxDistance); //La distancia maxima del objeto para verse

		dev->SetTransform(D3DTS_VIEW, &viewMatrix);
		dev->SetTransform(D3DTS_PROJECTION, &projMatrix);
	}
	dev->SetRenderState(D3DRS_LIGHTING, false);
}
