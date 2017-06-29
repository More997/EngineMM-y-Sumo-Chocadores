#pragma once
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "FVF.h"
#include "Textura.h"
class IMPORTEXPORT Actor
{
	Mesh* mesh2;
	Textura* texture;
	D3DXMATRIX matFinal;
	D3DXMATRIX trasl;
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXVECTOR3 vector;
public:
	Actor();
	Actor(Textura* tex);
	void setModelPos(float transx, float transy, float transz);
	void setModelScale(float scaleX, float scaleY, float scaleZ);
	void defTransMat();
	void setModelRot(float rotZ);
	D3DXVECTOR3 getVector(); //Donde ta Vector???
	void setVector(D3DXVECTOR3 _vector); //ponemos al vector aca.
	Actor(LPDIRECT3DDEVICE9 dev);
	~Actor();
	void DrawV(LPDIRECT3DDEVICE9 dev);
	void SetMesh(Mesh* mesh);
};

