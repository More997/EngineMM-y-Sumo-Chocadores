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
	void DrawV(LPDIRECT3DDEVICE9 dev, D3DXMATRIX _trasl, D3DXMATRIX _scale,D3DXMATRIX _rotation);
	void SetMesh(Mesh* mesh);
	void Move(LPDIRECT3DDEVICE9 dev);
};

