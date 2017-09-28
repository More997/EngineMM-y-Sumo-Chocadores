#include "stdafx.h"
#include "Component.h"
#include "Composite.h"
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "FVF.h"
#include "Textura.h"


Component::Component() :vectorTrans(0, 0, 0)
{
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);
	defTransMat();
}



Component::~Component()
{
}

void Component::setModelScale(float scaleX, float scaleY, float scaleZ)
{
	D3DXMatrixScaling(&scale, scaleX, scaleY, scaleZ); 
}

void Component::defTransMat()
{
	matFinal = scale * rotation * trasl;

	if (parent != NULL)
		matFinal = (parent->getTransMat() * matFinal);
}

void Component::setModelRotZ(float rotZ)
{
	D3DXMatrixRotationZ(&rotation, rotZ);
}

void Component::setModelRotY(float rotY)
{
	D3DXMatrixRotationY(&rotation, rotY);
}

void Component::setModelRotX(float rotX)
{
	D3DXMatrixRotationX(&rotation, rotX);
}

void Component::setModelPos(float transX, float transY, float transZ)
{
	vectorTrans.x = transX;
	vectorTrans.y = transY;
	vectorTrans.z = transZ;
	D3DXMatrixTranslation(&trasl, transX, transY, transZ);
}
D3DXMATRIX Component::getTransMat()
{
	return matFinal;
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

void Component::SetParent(Composite* parent)
{
	this->parent = parent;
}