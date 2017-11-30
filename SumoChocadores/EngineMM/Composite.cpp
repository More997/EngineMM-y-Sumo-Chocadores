#include "stdafx.h"
#include "Composite.h"


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
	UpdateBB(vectorTrans, scaleV, rotationV);
	transBB = GetBoundingBox()->Transform(vectorTrans, scaleV, rotationV);

}
void Composite::RenderingComposite()
{
}
BoundingBox Composite::GetMeshBB()
{
	return transBB;
}
void Composite::UpdateBB(D3DXVECTOR3 trans, D3DXVECTOR3 scal, D3DXVECTOR3 rot)
{
	for (int i = 0; i < objectComponents.size(); i++)
	{
		transBB.Combine(objectComponents[i]->GetBoundingBox()->Transform(trans, scal, rot));
	}
	if (GetParent())
	{
		GetParent()->UpdateBB(trans, scal, rot);
	}
	transBB.Refresh();
}
void Composite::UpdateComposite()
{
}