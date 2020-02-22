#ifndef CAMERA_H
#define CAMERA_H

#include "../DX/Include/d3dx9.h"
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include "EngineApi.h"
#include "Transform.h"
class IMPORTEXPORT Camera
{
public:
	bool isometricView = false;
	Camera();
	~Camera();
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;
	Transform *m_Transform = new Transform();
	void View(LPDIRECT3DDEVICE9 dev, float angleOfView, float width, float height, float minDistance, float maxDistance);
};

#endif