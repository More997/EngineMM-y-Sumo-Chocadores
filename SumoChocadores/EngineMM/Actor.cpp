#include "stdafx.h"
#include "Actor.h"

Actor::Actor()
{
}

Actor::Actor(LPDIRECT3DDEVICE9 dev)
{
}


Actor::~Actor()
{

}

void Actor::DrawV(LPDIRECT3DDEVICE9 dev)
{
	dev->SetFVF(CUSTOMFVF);
	dev->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));
	dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	dev->SetIndices(mesh2->GetInd());
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void Actor::SetMesh(Mesh * mesh)
{
	mesh2 = mesh;
}

void Actor::Move()
{

}

D3DXMATRIX Actor::GetViewMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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


D3DXMATRIX Actor::GetModelMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sca)
{
	D3DXMATRIX transMat;
	D3DXMatrixIdentity(&transMat);
	transMat._41 = pos.x;
	transMat._42 = pos.y;
	transMat._43 = pos.z;

	D3DXMATRIX scaMat;
	D3DXMatrixIdentity(&scaMat);
	scaMat._11 = sca.x;
	scaMat._22 = sca.y;
	scaMat._33 = sca.z;

	D3DXMATRIX rotZMat;
	D3DXMatrixIdentity(&rotZMat);
	rotZMat._11 = cos(rot.z);
	rotZMat._12 = sin(rot.z);
	rotZMat._21 = -sin(rot.z);
	rotZMat._22 = cos(rot.z);

	return scaMat * rotZMat * transMat;
};

