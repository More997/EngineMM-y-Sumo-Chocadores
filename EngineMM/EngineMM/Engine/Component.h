#ifndef COMPONENT_H
#define COMPONENT_H
#include "stdafx.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include "EngineAPI.h"
#include "BoundingBox.h"

class IMPORTEXPORT Component
{
private:
	class Composite* parent;
	D3DXVECTOR3 translationVector;
	D3DXVECTOR3 scaleVector;
	D3DXVECTOR3 rotationVector;
	D3DXMATRIX _translation;
	D3DXMATRIX _scale;
	D3DXMATRIX _rotation;
	
	float scaleXData;
	float scaleYData;
	float scaleZData;
	float rotationXData;
	float rotationYData;
	float rotationZData;
	
protected:
	float x;
	float y;
	D3DXMATRIX _transformationMatrix;
	BoundingBox bound;

public:
	Component();
	~Component();
	void SetModelPosition(float translationX, float translationY, float translationZ);
	void SetModelScale(float scale, float scaleY, float scaleZ);
	void SetModelRotation(float rotationX, float rotationY, float rotationZ);
	void SetModelRotationX(float rotationX);
	void SetModelRotationY(float rotationY);
	void SetVectorPosition(D3DXVECTOR3);
	float GetScaleX() const;
	float GetScaleY() const;
	float GetScaleZ() const;
	D3DXMATRIX GetRotationMatrix();
	float GetRotationX() const;
	float GetRotationY() const;
	float GetRotationZ() const;
	virtual void defineTransformationMatrix();
	D3DXMATRIX GetTransformationMatrix();
	virtual void Update();
	virtual void Render();
	void Move(float, float);
	void SetParent(Composite* parent);
	Composite* GetParent();
    void SetBoundingBox(BoundingBox _bound);
	BoundingBox GetBoundingBox();
	D3DXVECTOR3 GetPosition() const;
	D3DXVECTOR3* GetPositionByReference();
	D3DXVECTOR3 GetScale() const;
	D3DXVECTOR3 GetRotation() const;
};
#endif