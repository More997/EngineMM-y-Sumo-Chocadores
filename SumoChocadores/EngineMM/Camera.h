#pragma once
#include "Game.h"
class Camera
{
private:
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _rot;
public:

	Camera();
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~Camera();
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetRot();
	D3DXMATRIX GetViewMatrix();
	void update(LPDIRECT3DDEVICE9 dev);
};

