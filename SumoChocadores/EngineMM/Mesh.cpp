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

/*Mesh::Mesh(vector<Vertex> _Vertex, vector<WORD> _Word)
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
	memcpy(data, _Vertex.data(), _Vertex.size());
	vb->Unlock();

	ind->Lock(0, 0, &data, 0);
	memcpy(data, _Word.data(), _Word.size());
	ind->Unlock();
		
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

LPDIRECT3DVERTEXBUFFER9 Mesh::GetVb()
{
	return vb;
}

LPDIRECT3DINDEXBUFFER9 Mesh::GetInd()
{
	return ind;
}
