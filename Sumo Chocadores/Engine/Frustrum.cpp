#include "stdafx.h"
#include "Frustrum.h"
#include <iostream>


Frustrum::Frustrum()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		planes[i] = new D3DXPLANE();
	}
}

Frustrum::~Frustrum()
{
}

void Frustrum::UpdatePlanes(D3DXMATRIX viewProj)
{
	planes[0]->a = viewProj._14 + viewProj._11;
	planes[0]->b = viewProj._24 + viewProj._21;
	planes[0]->c = viewProj._34 + viewProj._31;
	planes[0]->d = viewProj._44 + viewProj._41;

	planes[1]->a = viewProj._14 - viewProj._11;
	planes[1]->b = viewProj._24 - viewProj._21;
	planes[1]->c = viewProj._34 - viewProj._31;
	planes[1]->d = viewProj._44 - viewProj._41;

	planes[2]->a = viewProj._14 + viewProj._12;
	planes[2]->b = viewProj._24 + viewProj._22;
	planes[2]->c = viewProj._34 + viewProj._32;
	planes[2]->d = viewProj._44 + viewProj._42;

	planes[3]->a = viewProj._14 - viewProj._12;
	planes[3]->b = viewProj._24 - viewProj._22;
	planes[3]->c = viewProj._34 - viewProj._32;
	planes[3]->d = viewProj._44 - viewProj._42;

	planes[4]->a = viewProj._13;
	planes[4]->b = viewProj._23;
	planes[4]->c = viewProj._33;
	planes[4]->d = viewProj._43;

	planes[5]->a = viewProj._14 - viewProj._13;
	planes[5]->b = viewProj._24 - viewProj._23;
	planes[5]->c = viewProj._34 - viewProj._33;
	planes[5]->d = viewProj._44 - viewProj._43;

	for (int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(planes[i], planes[i]);
	}
}

bool Frustrum::BoxInFrustrum(BoundingBox bb)
{
	bool draw = true;

	D3DXVECTOR3 vertexes[8];

	vertexes[0] = D3DXVECTOR3(bb.xMax, bb.yMax, bb.zMax);
	vertexes[1] = D3DXVECTOR3(bb.xMax, bb.yMax, bb.zMin);
	vertexes[2] = D3DXVECTOR3(bb.xMin, bb.yMax, bb.zMax);
	vertexes[3] = D3DXVECTOR3(bb.xMin, bb.yMax, bb.zMin);
	vertexes[4] = D3DXVECTOR3(bb.xMax, bb.yMin, bb.zMax);
	vertexes[5] = D3DXVECTOR3(bb.xMax, bb.yMin, bb.zMin);
	vertexes[6] = D3DXVECTOR3(bb.xMin, bb.yMin, bb.zMax);
	vertexes[7] = D3DXVECTOR3(bb.xMin, bb.yMin, bb.zMin);

	int cont;

	for (int j = 0; j < 8; j++)
	{
		cont = 0;
		for (int i = 0; i < 6; i++)
		{
			if (D3DXPlaneDotCoord(planes[i], &vertexes[j]) > 0.0f)
				cont++;
		}
		if (cont == 6) {
			//std::cout << "Se dibuja" << std::endl;
			return true;
		}
	}
	//std::cout << "No se dibuja" << std::endl;
	return false;
}