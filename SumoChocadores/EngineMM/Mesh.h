#pragma once
#include "Vertex.h"
#include <vector>
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include "FVF.h"
using namespace std;
class IMPORTEXPORT Mesh
{
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ind;
public:
	Mesh();
	~Mesh();
	void editVertex();
	LPDIRECT3DVERTEXBUFFER9 GetVb();
	LPDIRECT3DINDEXBUFFER9 GetInd();
};

