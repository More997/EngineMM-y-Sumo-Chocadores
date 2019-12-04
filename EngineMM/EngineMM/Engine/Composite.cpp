#include <iostream>
#include "stdafx.h"
#include "Composite.h"
#include "BoundingBox.h" //VER ACA POR LINKEO
Composite::Composite() : test(false)
{
	hasMesh = true;
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

void Composite::defineTransformationMatrix(BoundingBox reciving)
{
	defineTransformationMatrix();
}

void Composite::defineTransformationMatrix()
{
	//TODO: En caso de ser un meshrenderer tomar el BB original del mesh y aplicarle la transformacion
	//TODO: En caso de ser un composite agregarle a lo anterior (si es valido) los BB de los hijos
	//PRIMERO COMBINAR Y DESPUES TRANSFORMAR
	if (test)
	{
		bound = GetMeshBoundingBox(); //El problema con el importador parece tener que ver con esto
	}
	Component::defineTransformationMatrix();
	if(hasMesh)
	{
		bound = GetMeshBoundingBox();
		//bound = bound.Transform(GetPosition(), GetRotation(), GetScale());
		bound = bound.Transform(_transformationMatrix);
		UpdateBoundingBox(GetPosition(), GetRotation(), GetScale());
		bound.Refresh();
	}
}

BoundingBox Composite::GetMeshBoundingBox()
{
	BoundingBox bb;
	bb.xMin = bb.xMax = bb.yMin = bb.yMax = bb.zMin = bb.zMax = 0;
	bb.Refresh();
	return bb; //Esto seria overrideado por Mesh renderer
}
vector<Component*> Composite::GetComponents()
{
	return objectComponents;
}
void Composite::UpdateBoundingBox(D3DXVECTOR3 trasl, D3DXVECTOR3 escal, D3DXVECTOR3 rot)
{
	for (int i = 0; i < objectComponents.size(); i++)
	{
		bound.Combine(objectComponents[i]->GetBoundingBox());
	}
	bound.Refresh();
	if (GetParent())
	{
		GetParent()->UpdateBoundingBox(trasl, escal, rot);
	}
	
}

void Composite::SetName(string _name)
{
	name = _name;
}

string Composite::GetName()
{
	return name;
}
Composite * Composite::FindChild(string childName)
{
	Composite* foundChild = NULL;
	vector<Composite*> composites;
	for (int i = 0; i < objectComponents.size(); i++)
	{
		Composite * child = dynamic_cast<Composite*>(objectComponents[i]);
		if (child != nullptr)
		{
			composites.push_back(child);
		}
	}
	for (int i = 0; i < composites.size(); i++)
	{
		if (childName == composites.at(i)->name)
		{
			foundChild = composites.at(i);
			cout << "Hijo encontrado" << endl;
		}
		if (foundChild != NULL)
			return foundChild;
	}
	for (int i = 0; i < composites.size(); i++)
	{
		if (childName == composites.at(i)->name)
		{
			foundChild = composites.at(i);
			std::cout << "Hijo encontrado" << std::endl;
		}

		if (foundChild != NULL)
			return foundChild;
	}
}
void Composite::SetHasMesh(bool _hasMesh)
{
	hasMesh = _hasMesh;
}
void Composite::UpdateComposite()
{
}