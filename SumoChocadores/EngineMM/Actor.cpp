#include "stdafx.h"
#include "Actor.h"
#define CUSTOMFVF (D3DFVF_XYZ| D3DFVF_DIFFUSE)
struct Vertex {
	FLOAT x, y, z, rhw;
	DWORD color;
};
Actor::Actor()
{
}

Actor::Actor(LPDIRECT3DDEVICE9 dev)
{
	Vertex vertexes[] = {
		{ 0.0f,0.0f,0.0f, D3DCOLOR_XRGB(255,0,0) },
		{ 100.0f,0.0f,0.0f, D3DCOLOR_XRGB(0,255,0) },
		{ 0.0f,100.0f,0.0f, D3DCOLOR_XRGB(0,0,255) },
		{ 100.0f,100.0f,0.0f, D3DCOLOR_XRGB(255,255,0) }

		
	};
	WORD indexes[] = { 0,3,2,0,1,3 };
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
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
	dev->SetRenderState(D3DRS_LIGHTING, false);

}


Actor::~Actor()
{
	vb->Release();
	ind->Release();
}

void Actor::DrawV(LPDIRECT3DDEVICE9 dev)
{
	dev->SetFVF(CUSTOMFVF);
	dev->SetStreamSource(0, vb, 0, sizeof(Vertex));
	//dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	dev->SetIndices(ind);
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
