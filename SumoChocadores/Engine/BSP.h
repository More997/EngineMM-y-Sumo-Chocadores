#ifndef BSP_H
#define BSP_H

#include "EngineApi.h"
#include "Transform.h"
#include "Composite.h"
#include <list>

class IMPORTEXPORT BSP
{
	list<Composite*> allObjects;
	list<Composite*> objectsToDraw;
	vector<D3DXPLANE*> BSPplanes;
public:
	vector<Composite*> planos;
	void AddPlaneOrObject(Composite* root);
	void CheckTree(Transform* cameraTrans, Composite* root);
	void LoadPlane(Composite* plane);
	void AddBSP_Object(Composite* object);
	list<Composite*> GetObjectsToDraw();
	void ResetPlanes();
};
#endif