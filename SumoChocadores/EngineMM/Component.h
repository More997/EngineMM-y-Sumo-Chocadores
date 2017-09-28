#ifndef COMPONENT_H
#define COMPONENT_H

#include "EngineMMAPI.h"

class Composite;

class IMPORTEXPORT Component
{
private: 
	Composite* parent;
	D3DXMATRIX matFinal;
	D3DXMATRIX trasl;
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXVECTOR3 vectorTrans;
protected:
	float x;
	float y;
public:
	Component();
	~Component();
	void setModelScale(float scaleX, float scaleY, float scaleZ);
	void defTransMat();
	void setModelRotZ(float rotZ);
	void setModelRotY(float rotY);
	void setModelRotX(float rotX);
	void setModelPos(float transx, float transy, float transz);
	D3DXMATRIX getTransMat();
	void SetParent(Composite* parent);
	D3DXVECTOR3 getVector();
	void setVector(D3DXVECTOR3 _vector);
	Composite* GetParent();

	virtual void Render();
	virtual void Update();
};
#endif
