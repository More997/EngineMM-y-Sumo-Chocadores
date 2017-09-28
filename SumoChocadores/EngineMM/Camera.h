#ifndef CAMERA_H
#define CAMERA_H
#include "Game.h"
#include "Composite.h"
class IMPORTEXPORT Camera:
	public Composite
{
private:
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _rot;
public:

	Camera();
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~Camera();
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetRot();
	D3DXMATRIX GetViewMatrix();
	void update();
};
#endif 
