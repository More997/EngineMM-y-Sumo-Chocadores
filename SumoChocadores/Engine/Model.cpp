#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"

#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\cimport.h>

Model::Model()
{
}


Model::~Model()
{
}

void Model::SetTexture(std::string nombreTextura)
{

}

void Model::LoadMesh2D(LPDIRECT3DDEVICE9 dev)
{
	_2D = true;

	//Creamos un modelo de triangulo
	Vertex vertexes[] =
	{
		{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f ,0.0f },
		{ 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f ,0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f ,1.0f },
		{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f ,1.0f }
	};

	WORD indexes[] = { 0,3,2,   //Los indices de los vertices del primer triangulo
	0,1,3 }; //Los del segundo triangulo

	//Reservamos espacion en VRAM para
	//mas adelante subir el modelo

	dev->CreateVertexBuffer(
		4 * sizeof(Vertex), //La cantidad de bytes a reservar, los suficientes para el modelo
		D3DUSAGE_WRITEONLY, //El uso que le vamos a dar
		MYFVF,				//El formato de cada vertice
		D3DPOOL_MANAGED,	//Lo subimos a la VRAM
		&vb,				//El punto al buffer
		NULL);				//Recursos compartidos que no utilizamos


	dev->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib,
		NULL);



	//Tengo un punto a la memoria del VB en el VRAM
	VOID* data;

	vb->Lock(0, 0, &data, 0);

	//Copiamos el array de vertices que esta en la RAM del CPU
	//a el puntero del VB en la VRAM, especificando cuantos
	//bytes vamos a copiar
	memcpy(data, vertexes, 4 * sizeof(Vertex));

	//Libremos el sector de la VRAM que bloqueamos
	//para el proceso de copiado
	vb->Unlock();

	//Hacemos lo mismo de arriba pero para los indices
	ib->Lock(0, 0, &data, 0);
	memcpy(data, indexes, 6 * sizeof(WORD));
	ib->Unlock();

}

void Model::LoadMesh3D(LPDIRECT3DDEVICE9 dev, const char * modelName)
{
	_2D = false;

	FILE* file;
	fopen_s(&file, modelName, "r");

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

			bool pushVertexes = false;

			if (pushVertexes == false)
			{
				indexes.push_back(vertexes.size());
				vertexes.push_back(vertex);
			}

			fscanf(file, "%d/%d/%d ", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			vertex.tu = uvs[uvIndex - 1].x;
			vertex.tv = uvs[uvIndex - 1].y;
			vertex.nx = normals[normalIndex - 1].x;
			vertex.ny = normals[normalIndex - 1].y;
			vertex.nz = normals[normalIndex - 1].z;


			if (pushVertexes == false)
			{
				indexes.push_back(vertexes.size());
				vertexes.push_back(vertex);
			}

			fscanf(file, "%d/%d/%d\n", &posIndex, &uvIndex, &normalIndex);
			vertex.x = positions[posIndex - 1].x;
			vertex.y = positions[posIndex - 1].y;
			vertex.z = positions[posIndex - 1].z;
			vertex.tu = uvs[uvIndex - 1].x;
			vertex.tv = uvs[uvIndex - 1].y;
			vertex.nx = normals[normalIndex - 1].x;
			vertex.ny = normals[normalIndex - 1].y;
			vertex.nz = normals[normalIndex - 1].z;

			if (pushVertexes == false)
			{
				indexes.push_back(vertexes.size());
				vertexes.push_back(vertex);
			}
		}
	}


	bb.Refresh();


	dev->CreateVertexBuffer(vertexes.size() * sizeof(Vertex), 0, MYFVF, D3DPOOL_MANAGED, &vb, NULL);
	dev->CreateIndexBuffer(indexes.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, NULL);

	VOID* lockedData = NULL;
	vb->Lock(0, 0, (void**)&lockedData, 0);
	memcpy(lockedData, vertexes.data(), vertexes.size() * sizeof(Vertex));
	vb->Unlock();

	ib->Lock(0, 0, (void**)&lockedData, 0);
	memcpy(lockedData, indexes.data(), indexes.size() * sizeof(WORD));
	ib->Unlock();

	dev->SetRenderState(D3DRS_ZENABLE, true);
	dev->SetRenderState(D3DRS_ZWRITEENABLE, true);
	dev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

}

LPDIRECT3DVERTEXBUFFER9 Model::GetVertexBuffer()
{
	return vb;
}

LPDIRECT3DINDEXBUFFER9 Model::GetIndexBuffer()
{
	return ib;
}

void Model::SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _vb)
{
	vb = _vb;
}

void Model::SetIndexBuffer(LPDIRECT3DINDEXBUFFER9 _ib)
{
	ib = _ib;
}

BoundingBox Model::getBB()
{
	return bb;
}

void Model::SetBB(BoundingBox newBB)
{
	bb = newBB;
}

