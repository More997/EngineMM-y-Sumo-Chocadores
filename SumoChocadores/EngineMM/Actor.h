#pragma once
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

class IMPORTEXPORT Actor
{
	Mesh* mesh2;
public:
	Actor();
	Actor(LPDIRECT3DDEVICE9 dev);
	~Actor();
	void DrawV(LPDIRECT3DDEVICE9 dev);
	void SetMesh(Mesh* mesh);
	void Move();
	D3DXMATRIX GetViewMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	D3DXMATRIX GetModelMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sca);
};

