#ifndef COMPONENT_H
#define COMPONENT_H

#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include <d3dx9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include "EngineApi.h"
#include "Model.h"
#include "Frustrum.h"
class IMPORTEXPORT Component
{
	class Composite* parent;
public:
	Component();
	~Component();
	virtual void Update();
	virtual void Draw(LPDIRECT3DDEVICE9 dev, Frustrum* frustrum, bool drawChilds);
	void SetParent(Composite* parent);
	Composite* GetParent();
};

#endif