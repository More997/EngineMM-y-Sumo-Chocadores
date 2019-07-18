#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <vector>
#include "Component.h"
using namespace std;
class IMPORTEXPORT Composite :
	public Component
{
private:
	string name;
	template<class T>
	void GetComponentsInParent(vector<T*>*);
	vector<Component*>objectComponents;
protected:
	virtual void UpdateComposite(); 
public:
	void SetName(string _name);
	string GetName();
	Composite();
	~Composite();
	void Add(Component* comp);
	void Remove(Component * component); 
	void Update();
	void Render() override final;
	virtual void defTransMat();
	virtual void RenderingComposite();
	virtual BoundingBox GetMeshBB();
	template<class T> 
	T* GetComponent();
	template<class T>
	 T* GetComponentInParent();
	template<class T> 
	T* GetComponentInChildren();
	template<class T> 
	vector<T*>* GetComponentsInParent();
	void UpdateBB(D3DXVECTOR3 trans, D3DXVECTOR3 scal, D3DXVECTOR3 rot);
};
template<class T>
inline T* Composite::GetComponent()
{
	for (size_t i = 0; i < objectComponents.size(); i++)
	{
		T* comp = dynamic_cast<T*>(objectComponents[i]);
		if (comp != nullptr) return comp;
	}

	return nullptr;
}
template<class T>
inline T * Composite::GetComponentInParent()
{
	T* comp = dynamic_cast<T*>(this);

	//Verifico si yo soy el tipo que esta buscando
	if (comp != nullptr)
	{
		return comp;
	}
	//Si no verifico si tengo padre para preguntarle a el
	else if (GetParent() != nullptr)
	{
		return GetParent()->GetComponentInParent<T>();
	}
	//Si no no esta lo que se esta buscando
	else
	{
		return nullptr;
	}
}
template<class T>
inline T * Composite::GetComponentInChildren()
{
	T* comp = dynamic_cast<T*>(this);
	if (comp) return comp;
	for (size_t i = 0; i < components.size(); i++)
	{
		Component* child = components[i];
		Composite* compositeChild = dynamic_cast<Composite*>(child);
		if (compositeChild)
		{
			T* childComp = compositeChild->GetComponentInChildren<T>();
			if (childComp) return childComp;
		}
		else
		{
			T* childComp = dynamic_cast<T*>(child);
			if (childComp) return childComp;
		}
	}
	return nullptr;
}
template<class T>
inline vector<T*>* Composite::GetComponentsInParent()
{
	vector<T*>* vec = new vector<T*>();
	GetComponentsInParent<T*>(vec);
	return vec;
}
template<class T>
inline void Composite::GetComponentsInParent(vector<T*>* vec)
{
	T* vec = dynamic_cast<T*>(this);
	if (comp) vec->push_back(comp);
	if (GetParent()) GetParent()->GetComponentsInParent(vec);
}

#endif