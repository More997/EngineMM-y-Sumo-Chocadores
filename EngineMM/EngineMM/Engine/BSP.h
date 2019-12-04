#ifndef BSP_H
#define BSP_H
#include "Composite.h"
#include <list>
#include "MeshRenderer.h"
class IMPORTEXPORT BSP
{
private:
	list<Composite*> allObjects;
	list<Composite*> objectsToDraw;
	vector<D3DXPLANE*> BSPPlanes;
public:
	BSP();
	vector<Composite*> planos;
	void AddPlaneOrObject(Composite* root);
	void CheckTree(Composite* cameraPosition, Composite* root);
	void LoadPlane(Composite* plane);
	void AddBSPObject(Composite* object);
	list<Composite*> GetObjectsToDraw();
	void ResetPlanes();
};
#endif