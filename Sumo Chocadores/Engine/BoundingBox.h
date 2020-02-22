#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "EngineApi.h"
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

class IMPORTEXPORT BoundingBox
{
	D3DXVECTOR3 vertexes[8];
public:
	BoundingBox();

	float xMin, xMax,
		yMin, yMax,
		zMin, zMax;

	void Refresh();
	BoundingBox Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sca);
	BoundingBox Transform(D3DXMATRIX mat);
	void Combine(BoundingBox otherBb);
	D3DXVECTOR3 GetVertex(int index);
};
#endif