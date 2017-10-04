#ifndef TILEMAP_H
#define TILEMAP_H
#include "Composite.h"
#include "Mesh.h"
class IMPORTEXPORT Tilemap:
	public Composite
{
private:
	int cantFilas = 2;
	int cantColumnas = 2;
	float ancho = 0.5f;
	float alto = 0.5f;
	vector<LPDIRECT3DTEXTURE9> Texturas;
	D3DXMATRIX Scale;
	LPDIRECT3DTEXTURE9 tex1;
	LPDIRECT3DTEXTURE9 tex2;
	vector<vector<int>> tileMap =
	{
		{ 1,0,1,0,1 },
		{ 0,1,0,1,0 },
		{ 1,0,1,0,1 },
	};
public:
	Tilemap(LPWSTR texA, LPWSTR texB, Mesh* mesh);
	~Tilemap();
	void RenderingComposite();


};
#endif

