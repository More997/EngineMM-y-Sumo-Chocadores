#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh(LPDIRECT3DDEVICE9 dev)
{
	Vertex vertexes[] = {
		{ -0.5f,0.5f,-0.5f, D3DCOLOR_XRGB(255,0,0) },
		{ 0.5f,0.5f,-0.5f, D3DCOLOR_XRGB(0,255,0) },
		{ -0.5f,-0.5f,-0.5f, D3DCOLOR_XRGB(0,0,255) },
		{ 0.5f,-0.5f,-0.5f, D3DCOLOR_XRGB(255,255,0) }
	};
	WORD indexes[] = { 0,3,2,0,1,3 };
	//dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	dev->CreateVertexBuffer(4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);
	dev->CreateIndexBuffer(
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


Mesh::~Mesh()
{
	vb->Release();
	ind->Release();
}

LPDIRECT3DVERTEXBUFFER9 Mesh::GetVb()
{
	return vb;
}

LPDIRECT3DINDEXBUFFER9 Mesh::GetInd()
{
	return ind;
}
