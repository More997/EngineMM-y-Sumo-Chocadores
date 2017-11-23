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
	transBB.Transform(vectorTrans, rotationV, scaleV);
	/*
	if (GetParent())
	{
		BoundingBox* parentBB = GetParent()->GetBoundingBox();
		parentBB->Combine(transBB);
	}
	*/
	for (int i = 0; i < objectComponents.size(); i++)
	{
		transBB.Combine(objectComponents[i]->GetBoundingBox()->Transform(getVectorTrans(), getRotationV(), getScaleV()));
	}
	transBB.Refresh();
}
void Composite::RenderingComposite()
{
}
void Composite::UpdateComposite()
{
}