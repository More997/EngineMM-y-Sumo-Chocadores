#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
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
};
#endif