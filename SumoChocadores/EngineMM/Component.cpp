#include "stdafx.h"
#include "Component.h"
#include "Composite.h"
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "FVF.h"
#include "Textura.h"
#include "MeshRender.h"

Component::Component() :vectorTrans(0, 0, 0), scaleV(1,1,1)
{
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);
	
}



Component::~Component()
{
}

void Component::setModelScale(float scaleX, float scaleY, float scaleZ)
{
	D3DXMatrixScaling(&scale, scaleX, scaleY, scaleZ); 
	scaleV.x = scaleX;
	scaleV.y = scaleY;
	scaleV.z = scaleZ;
	defTransMat();
}

void Component::defTransMat()
{
	matFinal = trasl * rotation * scale;
	/*D3DXQUATERNION rotQuaternion;
	D3DXMatrixTransformation(&matFinal, NULL, NULL, &scaleV, NULL,
		D3DXQuaternionRotationYawPitchRoll(&rotQuaternion, D3DXToRadian(rotationV.x), 
		D3DXToRadian(rotationV.y), D3DXToRadian(rotationV.z)), &vectorTrans);
	*/
	if (parent != NULL)
	{
		matFinal = (parent->getTransMat() * matFinal);
	}
	
}
void Component::setModelRotZ(float rotZ)
{
	D3DXMatrixRotationZ(&rotation, rotZ);
	rotationV.z = rotZ;
	D3DXMatrixRotationZ(&testRotZ, D3DXToRadian(rotationV.z));
	rotation = testRotX*testRotY*testRotZ;
}
void Component::setModelRotY(float rotY)
{
	D3DXMatrixRotationY(&rotation, rotY);
	rotationV.y = rotY;
	D3DXMatrixRotationZ(&testRotY, D3DXToRadian(rotationV.y));
	rotation = testRotX*testRotY*testRotZ;
}
void Component::setModelRotX(float rotX)
{
	D3DXMatrixRotationX(&rotation, rotX);
	rotationV.x = rotX;
	D3DXMatrixRotationZ(&testRotX, D3DXToRadian(rotationV.x));
	rotation = testRotX*testRotY*testRotZ;
}
void Component::setModelPos(float transX, float transY, float transZ)
{
	vectorTrans.x = transX;
	vectorTrans.y = transY;
	vectorTrans.z = transZ;
	D3DXMatrixTranslation(&trasl, transX, transY, transZ);
}
D3DXVECTOR3 Component::getScaleV()
{
	return scaleV;
}
D3DXVECTOR3 Component::getRotationV()
{
	return rotationV;
}
D3DXVECTOR3 Component::getVectorTrans()
{
	return vectorTrans;
}
D3DXMATRIX Component::getTransMat()
{
 	return matFinal;
}
D3DXMATRIX Component::getRotMat()
{
	return rotation;
}
void Component::Render()
{
	defTransMat();
}
void Component::Update()
{
}
D3DXVECTOR3 Component::getVector()
{
	return vectorTrans; 
}

void Component::setVector(D3DXVECTOR3 _vector)
{
	setModelPos(_vector.x, _vector.y, _vector.z);
}
Composite* Component::GetParent()
{
	return parent;
}

void Component::SetBoundingBox(BoundingBox _transBB)
{
	transBB = _transBB;
}

BoundingBox Component::GetBoundingBox()
{
	return transBB;
}

void Component::SetParent(Composite* parent)
{
	this->parent = parent;
}

