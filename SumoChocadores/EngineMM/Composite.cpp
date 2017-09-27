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
	comp->SetParent(this); //Me pongo a mi mismo como padre del componente.
}
void Composite::Remove(Component * component)
{
	//Porque pide un componente como parametro si lo que hace es remover? Preguntar.
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
void Composite::RenderingComposite()
{
	//Es virtual!
}
void Composite::UpdateComposite()
{
	// Y esto que hace? Preguntar.
}