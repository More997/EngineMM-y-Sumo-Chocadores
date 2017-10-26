#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "Composite.h"
class IMPORTEXPORT BoundingBox :
	public Composite
{
private:
	D3DXVECTOR3 vertexes[8];
public:
	float xMax, xMin,
		  yMax, yMin,
		  zMax, zMin;
	BoundingBox();
	~BoundingBox();
	/*void Refresh();
	BoundingBox Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sca);
	BoundingBox Transform(D3DXMATRIX mat);
	void Combine(BoundingBox otherBb);*/
};
#endif 
