#include "stdafx.h"
#include "Component.h"

Component::Component()
{
}
Component::~Component()
{
}
void Component::Update()
{
}

void Component::Draw(LPDIRECT3DDEVICE9 dev, Frustrum* frustrum)
{
}

void Component::SetParent(Composite* parent)
{
	this->parent = parent;
}

Composite * Component::GetParent()
{
	return parent;
}