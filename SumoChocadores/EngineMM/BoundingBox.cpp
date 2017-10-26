#include "stdafx.h"
#include "BoundingBox.h"


BoundingBox::BoundingBox() : xMin(+10000000), yMin(+10000000), zMin(+10000000),
							 xMax(-10000000), yMax(-10000000), zMax(-10000000)
{

}

/*
void BoundingBox::Refresh()
{
	vertexes[0] = D3DXVECTOR3(xMax, yMax, zMax);
	vertexes[1] = D3DXVECTOR3(xMax, yMax, zMin);
	vertexes[2] = D3DXVECTOR3(xMin, yMax, zMax);
	vertexes[3] = D3DXVECTOR3(xMin, yMax, zMin);
	vertexes[4] = D3DXVECTOR3(xMax, yMin, zMax);
	vertexes[5] = D3DXVECTOR3(xMax, yMin, zMin);
	vertexes[6] = D3DXVECTOR3(xMin, yMin, zMax);
	vertexes[7] = D3DXVECTOR3(xMin, yMin, zMin);
}

BoundingBox BoundingBox::Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sca)
{
	D3DXMATRIX matTrans;
	D3DXMATRIX matSca;
	D3DXMATRIX matRotX;
	D3DXMATRIX matRotY;
	D3DXMATRIX matRotZ;
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&matSca, sca.x, sca.y, sca.z);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(rot.x));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(rot.y));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(rot.z));
	D3DXMATRIX mat = matRotX * matRotY * matRotZ * matSca * matTrans;

	return Transform(mat);
}

BoundingBox BoundingBox::Transform(D3DXMATRIX mat)
{
	BoundingBox bb;

	for (int i = 0; i < 8; i++)
	{
		D3DXVECTOR4 transVertex;
		D3DXVec3Transform(&transVertex, &vertexes[i], &mat);

		bb.xMin = min(transVertex.x, bb.xMin);
		bb.yMin = min(transVertex.y, bb.yMin);
		bb.zMin = min(transVertex.z, bb.zMin);

		bb.xMax = max(transVertex.x, bb.xMax);
		bb.yMax = max(transVertex.y, bb.yMax);
		bb.zMax = max(transVertex.z, bb.zMax);
	}

	return bb;
}

 void BoundingBox::Combine(BoundingBox otherBb)
{
	xMin = min(xMin, otherBb.xMin);
	yMin = min(yMin, otherBb.yMin);
	zMin = min(zMin, otherBb.zMin);

	xMax = max(xMax, otherBb.xMax);
	yMax = max(yMax, otherBb.yMax);
	zMax = max(zMax, otherBb.zMax);
}
*/