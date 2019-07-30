#ifndef TILESET_H
#define TILESET_H
#include<iostream>
#include<vector>
//#include "Vertex.h"
#include "../DX/Include/d3dx9.h"
#include <string>
#include"Composite.h"
#include "FVF.h"
#include "Game.h"
class IMPORTEXPORT Tileset : public Composite
{
protected:
	LPCWSTR _imagen;
	LPCWSTR _imagenDefault;
	LPDIRECT3DTEXTURE9 _testTexture;
	LPDIRECT3DTEXTURE9 defaultTexture;
	vector<vector<int>> a;
	vector<LPDIRECT3DTEXTURE9> seinTextureMap;
	int filaTileMap;
	int columnaTileMap;
	int buffersVectorSize;
	vector<LPDIRECT3DVERTEXBUFFER9> vVb; // vector de vertex buffer
	vector<LPDIRECT3DINDEXBUFFER9> vIb; // vector de index buffer
	vector<Vertex> vertexes;
	vector<WORD> indexes;
	BoundingBox laCajita;
	vector<vector<BoundingBox*>> lasCajitas;
public:
	vector<vector<Vertex>> vVertexes;
	vector<vector<WORD>> vIndexes;
	vector<vector<D3DXVECTOR3>> vPositions;
	vector<vector<D3DXVECTOR3>> vNormals;
	vector<vector<D3DXVECTOR2>> vUvs;
	Tileset(Vertex seinVertice[], WORD seinIndexes[], int lines, int columns);
	~Tileset();
	void SetSize(int m, int l); // Filas y columnas TileMap
	void AddPalette(LPCWSTR seinImage);
	void SetTile(int m, int l, int value);
	vector<LPDIRECT3DTEXTURE9> GetPaletteVector();
	LPDIRECT3DTEXTURE9 GetDefaultTexture();
	vector<vector<int>> GetA();
	int GetTile(int m, int l); // Filas y columnas TileMap
	LPDIRECT3DTEXTURE9 GetTileTexture(int i);
	int GetFilas();
	int GetColumnas();
	BoundingBox* GetBoundingBox();
	vector<vector<BoundingBox*>> GetLasCajitas();
	vector<LPDIRECT3DVERTEXBUFFER9> GetVvb();
	vector<LPDIRECT3DINDEXBUFFER9> GetVib();
};
#endif
