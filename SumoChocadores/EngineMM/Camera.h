#pragma once
#include "Game.h"
class Camera
{
public:
	Camera();
	~Camera();
	void createCamera(LPDIRECT3DDEVICE9 dev, D3DXMATRIX _trasl, D3DXMATRIX _rotation);
};

