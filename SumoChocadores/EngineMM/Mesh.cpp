#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
	Game* game = Game::getInstance();
	Vertex vertexes[] = {
		{ -0.5f,0.5f,0.0f, 0.0f, 0.0f },
		{ 0.5f,0.5f,0.0f, 1.0f, 0.0f },
		{ -0.5f,-0.5f,0.0f,0.0f, 1.0f },
		{ 0.5f,-0.5f,0.0f,1.0f,1.0f }
	};
	WORD indexes[] = { 0,3,2,0,1,3 };
	//dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	game->getDev()->CreateVertexBuffer(4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);
	game->getDev()->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&ind,
		NULL);


	VOID *data;
	vb->Lock(0, 0, &data, 0);
	memcpy(data, vertexes, 4 * sizeof(Vertex));
	vb->Unlock();

	ind->Lock(0, 0, &data, 0);
	memcpy(data, indexes, 6 * sizeof(WORD));
	ind->Unlock();
}

Mesh::Mesh(Vertex _Vertexes[], WORD _WORD[])
{
	Game* game = Game::getInstance();
	game->getDev()->CreateVertexBuffer(
		4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);
	game->getDev()->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&ind,
		NULL);
	VOID *data;
	vb->Lock(0, 0, &data, 0);
	memcpy(data, _Vertexes, 4*sizeof(Vertex));
	vb->Unlock();

	ind->Lock(0, 0, &data, 0);
	memcpy(data, _WORD, 6*sizeof(WORD));
	ind->Unlock();
}

/*Mesh::Mesh(vector<Vertex> _Vertex, vector<WORD> _Word)
{
	
		
}*/


Mesh::~Mesh()
{
	vb->Release();
	ind->Release();
}

void Mesh::editVertex()
{
	Vertex vertexes[] = {
		{ -0.5f,0.5f,0.0f, 0.0f, 0.0f },
		{ 0.5f,0.5f,0.0f, 1.0f, 0.0f },
		{ -0.5f,-0.5f,0.0f,0.0f, 1.0f },
		{ 0.5f,-0.5f,0.0f,1.0f,1.0f }
	};
}

void Mesh::Load3D(const char* newModel)
{
	Game *game = Game::getInstance();
	/*
	FILE* file;
	fopen_s(&file, "TracerGun.obj", "r");

	//feof nos indica si estamos en el fin del archivo
	while (!feof(file))
	{
		//Obtengo la primer palabra despues de donde estoy parado
		//y la guardo en el array de chars
		char lineHeader[128];
		fscanf(file, "%s", lineHeader);

		//Si la primer palabra es V nos encontramos con una posicion
		//del vertice y la guardamos
		if (strcmp(lineHeader, "v") == 0)
		{
			D3DXVECTOR3 position;
			fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			positions.push_back(position);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			Vertex vertex;
			int posIndex, uvIndex, normalIndex;

			fscanf(file, "%d/%d/%d ", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			indexes.push_back(vertexes.size());
			vertexes.push_back(vertex);

			fscanf(file, "%d/%d/%d ", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			indexes.push_back(vertexes.size());
			vertexes.push_back(vertex);

			fscanf(file, "%d/%d/%d\n", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			indexes.push_back(vertexes.size());
			vertexes.push_back(vertex);
		}
	}*/
	FILE* file;
	fopen_s(&file, newModel, "r");

	//feof nos indica si estamos en el fin del archivo
	while (!feof(file))
	{
		//Obtengo la primer palabra despues de donde estoy parado
		//y la guardo en el array de chars
		char lineHeader[128];
		fscanf(file, "%s", lineHeader);

		//Si la primer palabra es V nos encontramos con una posicion
		//del vertice y la guardamos
		if (strcmp(lineHeader, "v") == 0)
		{
			D3DXVECTOR3 position;
			fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);

			bb.xMin = min(position.x, bb.xMin);
			bb.yMin = min(position.y, bb.yMin);
			bb.zMin = min(position.z, bb.zMin);

			bb.xMax = max(position.x, bb.xMax);
			bb.yMax = max(position.y, bb.yMax);
			bb.zMax = max(position.z, bb.zMax);
			positions.push_back(position);

			/*
			bb.xMin = min(posicionXGuardada, bb.xmin)
			positions es un vector donde guard
			*/
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
			indexes.push_back(vertexes.size());
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
			indexes.push_back(vertexes.size());
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
			indexes.push_back(vertexes.size());
			vertexes.push_back(vertex);
		}
	}
	

	game->getDev()->CreateVertexBuffer(vertexes.size() * sizeof(Vertex), 0, CUSTOMFVF, D3DPOOL_MANAGED, &vb, NULL);
	game->getDev()->CreateIndexBuffer(indexes.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ind, NULL);

	VOID* lockedData = NULL;
	vb->Lock(0, 0, (void**)&lockedData, 0);
	memcpy(lockedData, vertexes.data(), vertexes.size() * sizeof(Vertex));
	vb->Unlock();

	ind->Lock(0, 0, (void**)&lockedData, 0);
	memcpy(lockedData, indexes.data(), indexes.size() * sizeof(WORD));
	ind->Unlock();

	game->getDev()->SetRenderState(D3DRS_ZENABLE, true);
	game->getDev()->SetRenderState(D3DRS_ZWRITEENABLE, true);
	game->getDev()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

}

void Mesh::SetBB(BoundingBox _bb)
{
	bb = _bb;
}

BoundingBox Mesh::GetBB()
{
	return bb;
}

LPDIRECT3DVERTEXBUFFER9 Mesh::GetVb()
{
	return vb;
}

LPDIRECT3DINDEXBUFFER9 Mesh::GetInd()
{
	return ind;
}
