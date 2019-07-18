#ifndef MESH_H
#define MESH_H
#include "Vertex.h"
#include <vector>
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include "FVF.h"
#include "BoundingBox.h"

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
	void setVB(LPDIRECT3DVERTEXBUFFER9 _vb);
	void setInd(LPDIRECT3DINDEXBUFFER9 _ind);
	vector<Vertex> vertexes;
	vector<WORD> indexes;
	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> uvs;
};
#endif

