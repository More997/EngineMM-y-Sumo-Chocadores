#include "stdafx.h"
#include "Transform.h"
#include "Composite.h"


Transform::Transform()
{
	_pos = D3DXVECTOR3(0, 0, 0);
	_sca = D3DXVECTOR3(1, 1, 1);
	_rot = D3DXVECTOR3(0, 0, 0);
}


Transform::~Transform()
{
}

D3DXVECTOR3 Transform::GetPos()
{
	return _pos;
}

D3DXVECTOR3 Transform::GetRot()
{
	return _rot;
}

D3DXVECTOR3 Transform::GetSca()
{
	return _sca;
}

void Transform::SetPos(D3DXVECTOR3 pos)
{
	_pos = pos;
}

void Transform::SetPos(float x, float y, float z)
{
	_pos = D3DXVECTOR3(x, y, z);
}

void Transform::SetRot(D3DXVECTOR3 rot)
{
	//_rot = D3DXVECTOR3(D3DXToRadian(rot.x), D3DXToRadian(rot.y), D3DXToRadian(rot.z));
	_rot = rot;
}

void Transform::SetRot(float x, float y, float z)
{
	//_rot = D3DXVECTOR3(D3DXToRadian(x), D3DXToRadian(y), D3DXToRadian(z));
	_rot = D3DXVECTOR3(x, y, z);
}

void Transform::SetSca(D3DXVECTOR3 sca)
{
	_sca = sca;
}

void Transform::SetSca(float x, float y, float z)
{
	_sca = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR3 Transform::GetRight()
{
	D3DXMATRIX rotMat;

	D3DXMatrixRotationYawPitchRoll(&rotMat, _rot.y, _rot.x, _rot.z);

	D3DXVECTOR3 worldRight(1, 0, 0);
	D3DXVECTOR4 objRight;

	D3DXVec3Transform(&objRight, &worldRight, &rotMat);
	D3DXVECTOR3 right(objRight.x, objRight.y, objRight.z);


	//D3DXVec3Normalize(&right, &right);

	return right;
}

D3DXVECTOR3 Transform::GetUp()
{
	D3DXMATRIX rotMat;

	D3DXMatrixRotationYawPitchRoll(&rotMat, _rot.y, _rot.x, _rot.z);


	D3DXVECTOR3 worldUp(0, 1, 0);
	D3DXVECTOR4 objUp;

	D3DXVec3Transform(&objUp, &worldUp, &rotMat);
	D3DXVECTOR3 up(objUp.x, objUp.y, objUp.z);

	//D3DXVec3Normalize(&up, &up);

	return up;
}

D3DXVECTOR3 Transform::GetForward()
{
	D3DXMATRIX rotMat;

	D3DXMatrixRotationYawPitchRoll(&rotMat, _rot.y, _rot.x, _rot.z);

	D3DXVECTOR3 worldForward(0, 0, 1);
	D3DXVECTOR4 objForward;

	D3DXVec3Transform(&objForward, &worldForward, &rotMat);
	D3DXVECTOR3 forward(objForward.x, objForward.y, objForward.z);

	//D3DXVec3Normalize(&forward, &forward);

	return forward;
}

D3DXMATRIX Transform::GetWorldMatrix()
{
	return worldMatrix;
}

void Transform::CalculateModelMatrix()
{
	D3DXMATRIX transMat;
	D3DXMATRIX scaMat;
	D3DXMATRIX rotXMat;
	D3DXMATRIX rotYMat;
	D3DXMATRIX rotZMat;


	D3DXMatrixTranslation(&transMat, _pos.x, _pos.y, _pos.z);
	D3DXMatrixScaling(&scaMat, _sca.x, _sca.y, _sca.z);
	D3DXMatrixRotationX(&rotXMat, _rot.x);
	D3DXMatrixRotationY(&rotYMat, _rot.y);
	D3DXMatrixRotationZ(&rotZMat, _rot.z);

	localModelMatrix = scaMat * rotXMat * rotYMat * rotZMat * transMat;
}

void Transform::CalculateWorldMatrix(D3DXMATRIX parentMatrix)
{
	worldMatrix = localModelMatrix * parentMatrix;
}

void Transform::NoParentModelMatrix()
{
	worldMatrix = localModelMatrix;
}

void Transform::Move(D3DXVECTOR3 movement)
{
	_pos += movement;
}

void Transform::Move(float x, float y, float z)
{
	_pos += D3DXVECTOR3(x, y, z);
}

void Transform::Rotate(D3DXVECTOR3 rotation)
{
	_rot += rotation;
}

void Transform::Scale(D3DXVECTOR3 scale)
{
	_sca += scale;
}

void Transform::updateTransBB()
{
	GetParent()->UpdateBoundingBox(GetParent()->GetPosition(), GetParent()->GetScale(), GetParent()->GetRotation());
}

