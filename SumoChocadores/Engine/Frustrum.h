#ifndef FRUSTRUM_H
#define FRUSTRUM_H

#include "BoundingBox.h"

class IMPORTEXPORT Frustrum
{
	LPD3DXPLANE planes[6];
public:
	void UpdatePlanes(D3DXMATRIX viewProj);
	bool BoxInFrustrum(BoundingBox bb);
	Frustrum();
	~Frustrum();
};
#endif

