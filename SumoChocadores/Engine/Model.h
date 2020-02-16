#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include"FVF.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include "../Engine/EngineApi.h"
#include "../DX/Include/d3dx9.h"
#include <string>
#include "EngineApi.h"
#include <vector>
#include "Vertex.h"
#include "BoundingBox.h"
using namespace std;

//#include <d3dx9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto

class IMPORTEXPORT Model
{
	LPDIRECT3DINDEXBUFFER9 ib;
	LPDIRECT3DVERTEXBUFFER9 vb;
	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> uvs;
	BoundingBox bb;
public:
	bool _2D;
	vector<Vertex> vertexes;
	vector<WORD> indexes;
	Model();
	~Model();
	void SetTexture(std::string nombreTextura);
	void LoadMesh2D(LPDIRECT3DDEVICE9 dev);
	void LoadMesh3D(LPDIRECT3DDEVICE9 dev, const char* modelName);
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer();
	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer();
	void SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _vb);
	void SetIndexBuffer(LPDIRECT3DINDEXBUFFER9 _ib);
	BoundingBox getBB();
	void SetBB(BoundingBox newBB);
};

#endif // !MODEL_H