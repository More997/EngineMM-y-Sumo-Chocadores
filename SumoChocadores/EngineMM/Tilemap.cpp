#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap(LPWSTR texA, LPWSTR texB, Mesh * mesh)
{
	Game* game = Game::getInstance();
	D3DXMatrixScaling(&Scale, ancho, alto, 1);

	_mesh = mesh;
	D3DXCreateTextureFromFile(game->getDev(), texA, &tex1);
	D3DXCreateTextureFromFile(game->getDev(), texB, &tex2);
	Texturas = { tex1, tex2 };
}

Tilemap::~Tilemap()
{
}

void Tilemap::RenderingComposite()
{
	Game* game = Game::getInstance();

	game->getDev()->SetFVF(CUSTOMFVF);
	game->getDev()->SetIndices(_mesh->GetInd());
	game->getDev()->SetStreamSource(0, _mesh->GetVb(), 0, sizeof(Vertex));

	for (int iFila = 0; iFila < tileMap.size(); iFila++)
	{
		vector<int>* fila = &tileMap[iFila];

		//Recorremos cada columna del tilemap
		for (int iColumna = 0; iColumna < fila->size(); iColumna++)
		{
			//Accedemos el numero de celda para saber que textura utilizar
			int celda = fila->at(iColumna);
			LPDIRECT3DTEXTURE9 tex = Texturas[celda];
			game->getDev()->SetTexture(0, tex);

			//Creamos una matriz de traslacion para ubicar el tile
			float posX = ancho * iColumna;
			float posY = alto * iFila;
			D3DXMATRIX matTrans;
			D3DXMatrixTranslation(&matTrans, posX, -posY, 3);

			//La componemos con la matriz de escala previamente
			//calculada y dibujamos con esta matriz
			D3DXMATRIX mat = Scale * matTrans;
			game->getDev()->SetTransform(D3DTS_WORLD, &mat);

			//Dibujamos el tile
			game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		}
	}
}