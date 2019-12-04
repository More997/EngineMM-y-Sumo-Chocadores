#ifndef CAMERA_H
#define CAMERA_H
#include "Composite.h"
class IMPORTEXPORT Camera :
	public Composite
{
private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

public:
	Camera();
	//Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~Camera();
	//void SetPosition(D3DXVECTOR3 pos);
	//void SetRotation(D3DXVECTOR3 rot);
	//D3DXVECTOR3 GetPosition();
	//D3DXVECTOR3 GetRotation();
	void CreateViewMatrix(D3DXVECTOR3 position, D3DXVECTOR3 rotation);
	D3DXMATRIX GetViewMatrix();
	D3DXMATRIX GetProjection();
	vector<D3DXPLANE> GetFructrumVector();
	void Move(D3DXVECTOR3 trasl, D3DXVECTOR3 escal, D3DXVECTOR3 rot);
	void Update();
};
#endif