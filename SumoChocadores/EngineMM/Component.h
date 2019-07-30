#ifndef COMPONENT_H
#define COMPONENT_H

#include "EngineMMAPI.h"
#include "BoundingBox.h" 


class Composite;

class IMPORTEXPORT Component
{
private: 
	Composite* parent;
	
protected:
	float x;
	float y;
	D3DXMATRIX matFinal;
	D3DXVECTOR3 scaleV;
	D3DXVECTOR3 rotationV;
	D3DXVECTOR3 vectorTrans;
	BoundingBox transBB;
	D3DXMATRIX trasl;
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
public:
	Component();
	~Component();
	void setModelScale(float scaleX, float scaleY, float scaleZ);
	virtual void defTransMat();
	void setModelRotZ(float rotZ);
	void setModelRotY(float rotY);
	void setModelRotX(float rotX);
	void setModelPos(float transx, float transy, float transz);
	D3DXVECTOR3 getScaleV();
	D3DXVECTOR3 getRotationV();
	D3DXVECTOR3 getVectorTrans();
	D3DXMATRIX getTransMat();
	void SetParent(Composite* parent);
	D3DXVECTOR3 getVector();
	void setVector(D3DXVECTOR3 _vector);
	Composite* GetParent();
	void SetBoundingBox(BoundingBox _transBB);
	BoundingBox GetBoundingBox();
	virtual void Render();
	virtual void Update();
};
#endif