#include "stdafx.h"
#include "Mesher.h"

#include "FVF.h"
#include "Game.h"
//#include  <assimp/Importer.hpp>
Mesher::Mesher()
{
	
	Game* s = Game::getInstance();
	Vertex vertexes[] =
	{ //Creo un modelo de un cuadrado
		{ -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		{ +0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ +0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
	};
	WORD defaultIndexes[] = { 0,3,2,   //Los indices de los vertices del primer triangulo
		0,1,3 }; //Los del segundo triangulo

	s->GetDevice()->CreateVertexBuffer(
		4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		MYFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);
	s->GetDevice()->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib,
		NULL);
	VOID *data;
	vb->Lock(0, 0, &data, 0);
	memcpy(data, vertexes, 4 * sizeof(Vertex));
	vb->Unlock();
	ib->Lock(0, 0, &data, 0);
	memcpy(data, defaultIndexes, 6 * sizeof(WORD));
	ib->Unlock();
	//dev->SetRenderState(D3DRS_LIGHTING, false);
	
}

Mesher::Mesher(/*vector<Vertex>*/ Vertex comingVertexes[], WORD comingWORDs[])
{
	Game* s = Game::getInstance();

	
	s->GetDevice()->CreateVertexBuffer(
		4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		MYFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);
	s->GetDevice()->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib,
		NULL);
	VOID *data;
	vb->Lock(0, 0, &data, 0);
	memcpy(data, comingVertexes, 4 * sizeof(Vertex));
	vb->Unlock();
	ib->Lock(0, 0, &data, 0);
	memcpy(data, comingWORDs, 6 * sizeof(WORD));
	ib->Unlock();
	for (int i = 0; i < 4; i++)
	{
		vertexes.push_back(comingVertexes[i]);
	}
	for (int i = 0; i < 6; i++)
		indexesVector.push_back(vertexes.size());
}
Mesher::~Mesher()
{
	ib->Release();
	vb->Release();
}
void Mesher::EditVertex()
{
	Vertex vertexes[] = {
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.5f,	 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f }
	};
}
void Mesher::Load3D(const char * newModel)
{
	Game* s = Game::getInstance();
	FILE* file;
	fopen_s(&file, newModel, "r");

	//feof nos indica si estamos en el fin del archivo
	while (!feof(file))
	{
		//Obtengo la primer palabra despues de donde estoy parado
		//y la guardo en el array de chars
		char lineHeader[128];
		fscanf(file, "%s", lineHeader); //fscanf

		//Si la primer palabra es V nos encontramos con una posicion
		//del vertice y la guardamos
		if (strcmp(lineHeader, "v") == 0)
		{
			D3DXVECTOR3 position;
			fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);

			boundi.xMin = min(position.x, boundi.xMin);
			boundi.yMin = min(position.y, boundi.yMin);
			boundi.zMin = min(position.z, boundi.zMin);

			boundi.xMax = max(position.x, boundi.xMax);
			boundi.yMax = max(position.y, boundi.yMax);
			boundi.zMax = max(position.z, boundi.zMax);

			positions.push_back(position);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			D3DXVECTOR3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			D3DXVECTOR2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			Vertex vertex;
			int posIndex, uvIndex, normalIndex;

			fscanf(file, "%d/%d/%d ", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			vertex.tu = uvs[uvIndex - 1].x;
			vertex.tv = uvs[uvIndex - 1].y;
			vertex.nx = normals[normalIndex - 1].x;
			vertex.ny = normals[normalIndex - 1].y;
			vertex.nz = normals[normalIndex - 1].z;
			indexesVector.push_back(vertexes.size());
			vertexes.push_back(vertex);

			fscanf(file, "%d/%d/%d ", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			vertex.tu = uvs[uvIndex - 1].x;
			vertex.tv = uvs[uvIndex - 1].y;
			vertex.nx = normals[normalIndex - 1].x;
			vertex.ny = normals[normalIndex - 1].y;
			vertex.nz = normals[normalIndex - 1].z;
			indexesVector.push_back(vertexes.size());
			vertexes.push_back(vertex);

			fscanf(file, "%d/%d/%d\n", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			vertex.tu = uvs[uvIndex - 1].x;
			vertex.tv = uvs[uvIndex - 1].y;
			vertex.nx = normals[normalIndex - 1].x;
			vertex.ny = normals[normalIndex - 1].y;
			vertex.nz = normals[normalIndex - 1].z;
			indexesVector.push_back(vertexes.size());
			vertexes.push_back(vertex);
		}
	}

	boundi.Refresh();

	s->GetDevice()->CreateVertexBuffer(vertexes.size() * sizeof(Vertex), 0, MYFVF, D3DPOOL_MANAGED, &vb, NULL);
	s->GetDevice()->CreateIndexBuffer(indexesVector.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, NULL);

	VOID* lockedData = NULL;
	vb->Lock(0, 0, (void**)&lockedData, 0);
	memcpy(lockedData, vertexes.data(), vertexes.size() * sizeof(Vertex));
	vb->Unlock();

	ib->Lock(0, 0, (void**)&lockedData, 0);
	memcpy(lockedData, indexesVector.data(), indexesVector.size() * sizeof(WORD));
	ib->Unlock();

	s->GetDevice()->SetRenderState(D3DRS_ZENABLE, true);
	s->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);
	s->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
}
void Mesher::SetBoundingBox(BoundingBox _boundi)//No fue usado en 2018/17
{
	boundi = _boundi;
	std::cout << "Se seteo un bounding box y su xMin es de " << boundi.xMax << std::endl;
}
BoundingBox Mesher::GetBoundingBox()
{
	return boundi;
}
BoundingBox Mesher::GetBoundingBoxByCopy()
{
	return boundi;
}

LPDIRECT3DVERTEXBUFFER9 Mesher::GetVb()
{
	return vb;
}
void Mesher::SetVb(LPDIRECT3DVERTEXBUFFER9 _vb)
{
	vb = _vb;
}
LPDIRECT3DINDEXBUFFER9 Mesher::GetIb()
{
	return ib;
}

void Mesher::SetIb(LPDIRECT3DINDEXBUFFER9 _ib)
{
	ib = _ib;
}
