#include "stdafx.h"
#include "Composite.h"


void Composite::SetName(string _name)
{
	name = _name;
}

string Composite::GetName()
{
	return name;
}

Composite::Composite()
{
}
Composite::~Composite()
{
}
void Composite::Add(Component * comp)
{
	objectComponents.push_back(comp);
	comp->SetParent(this); 
}
void Composite::Remove(Component * component)
{
}
void Composite::Update()
{
	UpdateComposite();

	for (size_t i = 0; i < objectComponents.size(); i++)
		objectComponents[i]->Update();

}
void Composite::Render()
{
	Component::Render();
	RenderingComposite();

	for (size_t i = 0; i < objectComponents.size(); i++)
		objectComponents[i]->Render();

}
void Composite::defTransMat()
{
	Component::defTransMat();
	transBB = GetMeshBB();
	transBB = transBB.Transform(matFinal);
	UpdateBB(vectorTrans, scaleV, rotationV);
}
void Composite::RenderingComposite()
{
}
BoundingBox Composite::GetMeshBB()
{
	BoundingBox _transBB;
	_transBB.xMin = _transBB.xMax = _transBB.yMin = _transBB.yMax = _transBB.zMin = _transBB.zMax = 0;
	_transBB.Refresh();
	return _transBB;
}
void Composite::UpdateBB(D3DXVECTOR3 trans, D3DXVECTOR3 scal, D3DXVECTOR3 rot)
{
	for (int i = 0; i < objectComponents.size(); i++)
	{
		transBB.Combine(objectComponents[i]->GetBoundingBox());
	}
	transBB.Refresh();
	if (GetParent())
	{
		GetParent()->UpdateBB(trans, scal, rot);
	}
}
void Composite::UpdateComposite()
{
}