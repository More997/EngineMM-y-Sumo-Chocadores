#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
class IMPORTEXPORT Transform : public Component
{
private:
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _rot;
	D3DXVECTOR3 _sca;
	D3DXMATRIX localModelMatrix;
	D3DXMATRIX worldMatrix;
public:
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetRot();
	D3DXVECTOR3 GetScale();
	void SetPos(D3DXVECTOR3 pos);
	void SetPos(float x, float y, float z);
	void SetRot(D3DXVECTOR3 rot);
	void SetRot(float x, float y, float z);
	void SetScale(D3DXVECTOR3 sca);
	void SetScale(float x, float y, float z);
	D3DXVECTOR3 GetRight();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetForward();
	D3DXMATRIX GetWorldMatrix();
	void CalculateModelMatrix();
	void CalculateWorldMatrix(D3DXMATRIX parentMatrix);
	void NoParentModelMatrix();
	void Move(D3DXVECTOR3 movement);
	void Move(float x, float y, float z);
	void Rotate(D3DXVECTOR3 rotation);
	void Scale(D3DXVECTOR3 scale);
	void updateTransBB();
	Transform();
	~Transform();

};
#endif