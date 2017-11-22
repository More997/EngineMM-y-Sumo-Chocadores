#pragma once
#include "Vertex.h"
#include "BoundingBox.h"
#include <vector>
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include "FVF.h"

using namespace std;
class IMPORTEXPORT Mesh
{
	BoundingBox bb;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ind;
public:
	Mesh();
	Mesh(Vertex _Vertexes[], WORD _WORD[]);
	~Mesh();
	void editVertex();
	void Load3D(const char* newModel);
	void SetBB(BoundingBox _bb);
	BoundingBox GetBB();
	LPDIRECT3DVERTEXBUFFER9 GetVb();
	LPDIRECT3DINDEXBUFFER9 GetInd();
	vector<Vertex> vertexes;
	vector<WORD> indexes;
	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> uvs;
};

