#ifndef COMPONENT_H
#define COMPONENT_H
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "FVF.h"
#include "Textura.h"
/*
#include "stdafx.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include "EngineMMAPI.h"
*/

class Component
{
private: 
	class Composite* parent;
	D3DXMATRIX matFinal;
	D3DXMATRIX trasl;
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXVECTOR3 vectorTrans;
protected:
	float x;
	float y;
public:
	IMPORTEXPORT Component();
	IMPORTEXPORT  ~Component();
	IMPORTEXPORT void setModelScale(float scaleX, float scaleY, float scaleZ);
	IMPORTEXPORT void defTransMat();
	IMPORTEXPORT void setModelRotZ(float rotZ);
	IMPORTEXPORT void setModelRotY(float rotY);
	IMPORTEXPORT void setModelRotX(float rotX);
	IMPORTEXPORT void setModelPos(float transx, float transy, float transz);
	IMPORTEXPORT D3DXMATRIX getTransMat();
	virtual void Render();
	virtual void Update();
	IMPORTEXPORT void SetParent(Composite* parent);
	IMPORTEXPORT D3DXVECTOR3 getVector();
	IMPORTEXPORT void setVector(D3DXVECTOR3 _vector);
	IMPORTEXPORT Composite* GetParent();
};
#endif
