#include "stdafx.h"
#include "TileSet.h"


TileSet::TileSet(Vertex seinVertice[], WORD seinIndexes[], int lines, int columns)
{
	Game* s = Game::getInstance();
	buffersVectorSize = 0;
	filaTileMap = lines;
	columnaTileMap = columns;
	vVb.resize(columns);
	vIb.resize(columns);
	//lasCajitas.resize(columns * lines);
	for (int i = 0; i < lines; i++)
	{
		for (int h = 0; h < columns; h++)
		{
			s->GetDevice()->CreateVertexBuffer(4 * sizeof(Vertex),
				D3DUSAGE_WRITEONLY,
				MYFVF,
				D3DPOOL_MANAGED,
				&vVb[h],
				NULL);
			s->GetDevice()->CreateIndexBuffer(6 * sizeof(WORD),
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&vIb[h],
				NULL);
			VOID *data;
			vVb[h]->Lock(0, 0, &data, 0);
			memcpy(data, seinVertice, 4 * sizeof(Vertex));
			vVb[h]->Unlock();
			vIb[h]->Lock(0, 0, &data, 0);
			memcpy(data, seinIndexes, 6 * sizeof(WORD));
			vIb[h]->Unlock();
		}
		for (int w = 0; w < 4; w++)
		{
			vertexes.push_back(seinVertice[w]);
		}
		vVertexes.push_back(vertexes);
		for (int w = 0; w < 6; w++)
		{
			indexes.push_back(vertexes.size());
		}
		vIndexes.push_back(indexes);
	}
	a.resize(lines);
	// lasCajitas.resize(lines);
	for (int i = 0; i < lines; i++)
	{
		a[i].resize(columns);
		// lasCajitas[i].resize(columns);
		for (size_t j = 0; j < columns; j++)
		{
			// a[i][j] = 1;
			a[i][j] = rand() % 2;
			// lasCajitas[i][j] = new BoundingBox();
		}
	}
}
TileSet::~TileSet()
{
}
void TileSet::SetSize(int m, int l)
{
	a.resize(m);
	// lasCajitas.resize(m);
	for (int i = 0; i < m; i++)
	{
		a[i].resize(l);
		lasCajitas[i].resize(l);
		for (size_t j = 0; j < l; j++)
		{
			a[i][j] = rand() % 2;
			// lasCajitas[i][j] = new BoundingBox();
		}
	}
	filaTileMap = m;
	columnaTileMap = l;
}
void TileSet::AddPalette(LPCWSTR seinImage)
{
	Game* s = Game::getInstance();
	_testTexture = NULL;
	_imagen = seinImage;
	D3DXCreateTextureFromFile(s->GetDevice(), _imagen, &_testTexture);
	seinTextureMap.push_back(_testTexture);
}
void TileSet::SetTile(int m, int l, int value)
{
	a[m][l] = value;
}
vector<LPDIRECT3DTEXTURE9> TileSet::GetPaletteVector()
{
	return seinTextureMap;
}
LPDIRECT3DTEXTURE9 TileSet::GetDefaultTexture()
{
	Game* s = Game::getInstance();
	defaultTexture = NULL;
	_imagenDefault = L"TileFeo2.png";
	D3DXCreateTextureFromFile(s->GetDevice(), _imagenDefault, &defaultTexture);
	return defaultTexture;
}
vector<vector<int>> TileSet::GetA()
{
	return a;
}
int TileSet::GetTile(int m, int l)
{
	return a[m][l];
}
LPDIRECT3DTEXTURE9 TileSet::GetTileTexture(int i)
{
	if (/*seinTextureMap[i] != NULL &&*/ i < seinTextureMap.size())
		return seinTextureMap[i];
	else
		return GetDefaultTexture();
}
int TileSet::GetFilas()
{
	return filaTileMap;
}
int TileSet::GetColumnas()
{
	return columnaTileMap;
}
BoundingBox* TileSet::GetBoundingBox()
{
	return &laCajita;
}
vector<vector<BoundingBox*>> TileSet::GetLasCajitas()
{
	return lasCajitas;
}
vector<LPDIRECT3DVERTEXBUFFER9> TileSet::GetVvb()
{
	return vVb;
}
vector<LPDIRECT3DINDEXBUFFER9> TileSet::GetVib()
{
	return vIb;
}