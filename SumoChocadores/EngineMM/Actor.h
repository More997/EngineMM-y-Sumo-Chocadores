#pragma once
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "FVF.h"
class IMPORTEXPORT Actor
{
	Mesh* mesh2;
	D3DXMATRIX matFinal;
	D3DXMATRIX trasl;
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
public:
	Actor();
	void setModelPos(float transx, float transy, float transz);
	void setModelScale(float scaleX, float scaleY, float scaleZ);
	void defTransMat();
	void setModelRot(float rotZ);
	Actor(LPDIRECT3DDEVICE9 dev);
	~Actor();
	void DrawV(LPDIRECT3DDEVICE9 dev);
	void SetMesh(Mesh* mesh);
};
