#pragma once
//#include <d3d9.h> //Busca el header de directx en los path
//#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
//#include "EngineAPI.h"
#include "Vertex.h"
#include <vector>
#include "FVF.h"
#include "BoundingBox.h"
using namespace std;
class IMPORTEXPORT Mesher
{
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;
	BoundingBox boundi;
	//WORD indexes;
public:
	Mesher();
	Mesher(/*vector<Vertex>*/ Vertex comingVertexes[], WORD comingWORDs[]);
	~Mesher();
	void EditVertex();
	void Load3D(const char* newModel);
	void SetBoundingBox(BoundingBox _boundi);//No fue usado en 2018/17
	BoundingBox GetBoundingBox();
	BoundingBox GetBoundingBoxByCopy();
	LPDIRECT3DVERTEXBUFFER9 GetVb();
	void SetVb(LPDIRECT3DVERTEXBUFFER9 _vb);
	LPDIRECT3DINDEXBUFFER9 GetIb();
	void SetIb(LPDIRECT3DINDEXBUFFER9 _ib);
	//Creo un vector para cada cosa
	vector<Vertex> vertexes;
	vector<WORD> indexesVector;
	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> uvs;
	
};