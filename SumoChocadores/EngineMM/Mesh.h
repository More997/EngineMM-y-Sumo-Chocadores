#pragma once
#include "Vertex.h"
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include "FVF.h"
class IMPORTEXPORT Mesh
{
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ind;
public:
	Mesh(LPDIRECT3DDEVICE9 dev);
	~Mesh();
	LPDIRECT3DVERTEXBUFFER9 GetVb();
	LPDIRECT3DINDEXBUFFER9 GetInd();
};

