#include "stdafx.h"
#include "Composite.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Model.h"

void Composite::Add(Component * component)
{
	components.push_back(component);
	component->SetParent(this);
}

void Composite::Remove(Component * component)
{
}

void Composite::Update()
{
	UpdateComposite();

	for (size_t i = 0; i < components.size(); i++)
		components[i]->Update();
}

void Composite::Draw(LPDIRECT3DDEVICE9 dev, Frustrum* frustrum, bool drawChilds)
{
	
	if (GetComponent<MeshRenderer>() && frustrum->BoxInFrustrum(transBB))
		GetComponent<MeshRenderer>()->DibujarMesh(dev); //En ninguna parte le estoy diciendo a los hijos que se dibujen.
	vector<Component*> temporalComponentsVector = GetComponents();
	for (int i = 0; i < temporalComponentsVector.size(); i++)
	{
		Composite * child = dynamic_cast<Composite*>(temporalComponentsVector[i]);
		if (child != nullptr && drawChilds == true)
		{
			child->Draw(dev, frustrum, true);
		}
	}
}

D3DXVECTOR3 Composite::GetWorldPosition()
{
	D3DXVECTOR3 worldPosition = GetComponent<Transform>()->GetPos();
	Composite* _parent = GetParent();

	while (_parent)
	{
		worldPosition.x += _parent->GetComponent<Transform>()->GetPos().x;
		worldPosition.y += _parent->GetComponent<Transform>()->GetPos().y;
		worldPosition.z += _parent->GetComponent<Transform>()->GetPos().z;
		_parent = _parent->GetParent();
	}

	return worldPosition;
}


D3DXVECTOR3 Composite::GetWorldRotation()
{
	D3DXVECTOR3 worldRotation = GetComponent<Transform>()->GetRot();
	Composite* _parent = GetParent();

	while (_parent)
	{
		worldRotation.x += _parent->GetComponent<Transform>()->GetRot().x;
		worldRotation.y += _parent->GetComponent<Transform>()->GetRot().y;
		worldRotation.z += _parent->GetComponent<Transform>()->GetRot().z;
		_parent = _parent->GetParent();
	}

	return worldRotation;
}

string Composite::GetName()
{
	return name;
}

void Composite::SetName(string _name)
{
	name = _name;
}

vector<Component*> Composite::GetComponents()
{
	return components;
}

BoundingBox Composite::getTransBB()
{
	return transBB;
}
BoundingBox Composite::GetTransBBNoParenting()
{
	return transBBNoParenting;
}

void Composite::setTransBB(BoundingBox _transBB)
{
	transBB = _transBB;
}

void Composite::updateBoundingBox()
{
	
	MeshRenderer* lpMeshRenderer = GetComponent<MeshRenderer>();
	Composite *_parent = GetParent();

	if (lpMeshRenderer)
	{
		Model* lpModel = lpMeshRenderer->m_Model;

		Transform* transform = GetComponent<Transform>();

		transBB = lpModel->getBB().Transform(transform->GetWorldMatrix());
		transBBNoParenting = lpModel->getBB().Transform(transform->GetWorldMatrix());
	}

	for (int i = 0; i < components.size(); i++)
	{
		Composite * child = dynamic_cast<Composite*>(components[i]);
		if (child != nullptr)
		{
			transBB.Combine(child->transBB);
		}
	}
	transBB.Refresh();

	if (_parent)
		_parent->updateBoundingBox();
		
}

Composite* Composite::findChild(string childName)
{
	Composite* childFound = NULL;
	vector<Composite*> composites;

	for (int i = 0; i < components.size(); i++)
	{
		Composite * child = dynamic_cast<Composite*>(components[i]);
		if (child != nullptr)
		{
			composites.push_back(child);
		}
	}
	for (int i = 0; i < composites.size(); i++)
	{
		if (childName == composites.at(i)->name)
		{
			childFound = composites.at(i);
			cout << "Child Found" << endl;
		}

		if (childFound != NULL)
			return childFound;
	}

	for (int i = 0; i < composites.size(); i++)
	{
		childFound = composites.at(i)->findChild(childName);
		if (childFound != NULL)
			return childFound;
	}
	return NULL;
}

void Composite::UpdateComposite()
{
	Transform *transform = GetComponent<Transform>();
	transform->CalculateModelMatrix();

	if (transform)
	{
		if (GetParent())
		{
			Transform *transformPadre = GetParent()->GetComponent<Transform>();
			transform->CalculateWorldMatrix(transformPadre->GetWorldMatrix());
		}
		else
		{
			transform->NoParentModelMatrix();
		}
	}
	updateBoundingBox();
}
