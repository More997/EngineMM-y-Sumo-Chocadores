#ifndef GAME_H
#define GAME_H
#include "stdafx.h"
#include <d3d9.h> //Busca el header de DirectX en los path
#pragma comment (lib, "d3d9.lib") //incluyo la lib a mi proyecto
#include "EngineAPI.h"

#include "Input.h"
#include "Composite.h"
#include "Camera.h"
//#include "Tilemap.h"
//#include "Time.h"
#include "Frustrum.h"
#include "BSP.h"

#include <list>


#include "Material.h"
#include "Model.h"
#include "MeshRenderer.h"



class IMPORTEXPORT Game
{
protected:
	Composite* root = new Composite();
	Camera* camera = new Camera();
	BSP* bsp = new BSP();
	list<Composite*> objectsToDraw;

	Composite* objeto;
	Transform* objetoTransform;

	MeshRenderer* objetoMeshR;

	Model* objetoModel;
	Material* objetoMaterial;






public:
	Game();
	~Game();
	virtual void LoadContent(LPDIRECT3DDEVICE9 dev) = 0;
	virtual void Update(LPDIRECT3DDEVICE9 dev) = 0;
	void Run(HINSTANCE hInstance, int nCmdShow);
	Input* m_Input;
	Frustrum* frustum = new Frustrum();


};
#endif